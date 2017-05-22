//---------------------------------------------------------------------------


#pragma hdrstop

#include "UnitTool_ClassExtend.h"
#include "UnitMath.h"
#include "values.h"
#include "UnitFormInfo.h"
#include "3DP_Def.h"
#include "UnitTool_Single.h"
#include "math.h"
#include "UnitGenDXFThread.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")
#pragma comment(lib,"glaux.lib")
//#pragma comment(lib,"glut32.lib")

//------------------------MManualProject----------------------------------------
//Word PPT 的基类
MAMProject::MAMProject()
{
    fProjectName = "";                                                      //工程名称，与RootNode的NodeName相同； "在新建的时候"
    fProjectFileName = "";                                                  //like ; XXX.3dmanual

    fMainItems = new MTreeNodes_LayerData();
    fMainItems->Project = this;

    fCurLayerDataItem = NULL;
    fLayersDataHolder = NULL;
    fLayerDataSelect = NULL;

    fProjectType = "1";

    fLayers = 0;
    fUnit = 1.0;

    fMinZ = 0.0;
    fPartID = -1;
}

void  MAMProject::DoMovePart(double  aPartMoveX,double aPartMoveY)
{
    if(MainItems->Count <= 1)
          throw Exception("请先加载模型");

    MainItems->DoMovePart(aPartMoveX,aPartMoveY);   //实现数据的移动
}

void MAMProject::DoScalePart(double aPartScaleX,double aPartScaleY)
{
    if(MainItems->Count <= 1)
          throw Exception("请先加载模型");

    MainItems->DoScalePart(aPartScaleX,aPartScaleY);   //实现数据的移动
}

MAMProject::~MAMProject()
{
    delete fMainItems;
}

double   MAMProject::readMinX()
{
    return fMainItems->MinX;
}

double   MAMProject::readMaxX()
{
    return fMainItems->MaxX;
}

double   MAMProject::readMinY()
{
    return fMainItems->MinY;
}

double   MAMProject::readMaxY()
{
    return fMainItems->MaxY;
}

double   MAMProject::readMaxZ()
{
    return fMainItems->MaxZ;
}

void  MAMProject::writeCurLayerDataItem(MLayerDataTreeNode* aItem)
{
    if(aItem == NULL)  return;

    if(aItem->TreeNode != NULL)
        aItem->TreeNode->Selected = true;
}

//1、根据文件类型，进行处理，可能为 jpg,cnc, cli,dxf等
//2、对于多层文件，对模型进行文件分割，挂接
void  MAMProject::ModelFile_PreProcess(MLayerDataTreeNode* aDMNode,String aModelFileName)
{
    if(ExtractFileExt(aModelFileName).UpperCase() == ".MIX")
    {
        LoadLayerDatasFromCLiFile(aModelFileName);
    }
    else
          throw Exception("不支持的类型，敬请期待");
}

//拆分，合成
//bool bSaveCtStruct: 是否保存目录结构
void  MAMProject::LoadLayerDatasFromCLiFile(String aCliFile,bool bSaveCtStruct,bool bConvertDXF)
{
    if(fMainItems->Count == 0)  return;
    if(fMainItems->Count > 1)
    {
        //Clear, 确保只有一个
        for(int i=1; i < fMainItems->Count;)
        {
           //先清资源，然后再删除
           MLayerDataTreeNode*  aItem = fMainItems->Items[i];
           aItem->Dispose();  //释放资源

           fMainItems->Delete(i);
        }
    }

    TStringList*  aFileStrings = new TStringList;
    aFileStrings->LoadFromFile(aCliFile);

    //get head
    LoadCLiHeaderInfoFromStrings(aFileStrings);   //获得单位和层数
    LoadCLiLayerInfoFromStrings(aFileStrings,bConvertDXF);

    fMainItems->ToTreeView(fLayersDataHolder,bSaveCtStruct);
    fMainItems->ToComboBox(fLayerDataSelect);

    delete aFileStrings;

    //数据进行转换
    if(bConvertDXF)
    {
       TGenDXFThread*  aThread = new TGenDXFThread(true,this,bSaveCtStruct,aCliFile);
       aThread->Resume();
       /*
       TStringList*  aSubFile = new TStringList;
       for(int i=1; i < fMainItems->Count; i++)
       {
           MLayerDataTreeNode* aItem = fMainItems->Items[i];

           CopyStrings(aSubFile,aFileStrings,aItem->iBeginLine,aItem->iEndLine);

           //String aLayerEdgeFileName = aLayerPath+"\\Edge_Layer_"+ aItem->LayerNo +".dxf";

           String  aLayerFileName = aItem->ConvertCli2Dxf(aSubFile,aLayerPath); //填充线的文件
           aItem->DXFFileName = aLayerFileName;   //Layer_i_1.dxf;Layer_i_2.dxf;Layer_i_3.dxf

           String aSingleCLiFileName = aSingleCLiPath + "\\Cli_"+aItem->LayerNo +".dat";
           aSubFile->SaveToFile(aSingleCLiFileName);

           aSubFile->Clear();

           gError->WarnAdd1_Percent("正在生成节点打印文件,请稍后!",i,fMainItems->Count);
       }
       delete aSubFile;

       */
    }


    //if(bSaveCtStruct)
    //     SaveCatalogStruct();
}


//----------------判断是不是二进制文件------------------------------------
bool  MAMProject::IsBinaryCliFile(String  aFileName)
{
    if(FileExists(aFileName) == false)
            throw Exception(aFileName + " 文件不存在");

    //1.打开二进制格式CLI文件
    FILE *stream = fopen(aFileName.c_str(),"rb");
    if(stream == NULL)
    {
       throw Exception("打开文件错误");
    }

    //读取文件头
    char  Header[14*16+2];
    fread(Header,sizeof(char),sizeof(Header),stream);

    String  aStr = String(Header);
    TStrings* aCliHeadeList = splitToStrings_Mask( aStr,"\n");    //拆分

    if(aCliHeadeList->Count == 9 && aCliHeadeList->Strings[1] == "$$BINARY")
    {
        delete aCliHeadeList;
        fclose(stream);
        return true;
    }

    delete aCliHeadeList;
    fclose(stream);
    return false;


}

//如果CLIFile是AscII码，复制到temp文件夹，返回FileName
//如果是二进制文件，保存到temp文件夹，返回FileName
//保证出口相同
String MAMProject::ConvertBinaryToAscIICLiFile(String  aCLiFileName)
{
    //1、判断是不是Binary File
    bool  IsBinary = IsBinaryCliFile(aCLiFileName);

    String aOutDir = ApplicationPath() + "\\Temp";

    String aFileName = ExtractFileName(aCLiFileName);
    String aRetFileName = aOutDir + "\\" + aFileName;
    if(IsBinary == false) //ascii形式
    {
        CopyFileAlways(aCLiFileName,aRetFileName);
        return aRetFileName;
    }

    DoFileFormatConvert(aCLiFileName,aRetFileName);
    return aRetFileName;

}

void  MAMProject::DoFileFormatConvert(String aSrcFile,String aDestFile)
{
    if(FileExists(aSrcFile) == false)
            throw Exception(aSrcFile + " 文件不存在");

    //1.打开二进制格式CLI文件
    FILE *stream = fopen(aSrcFile.c_str(),"rb");
    if(stream == NULL)
    {
       throw Exception("打开文件错误");
    }

    BinaryCLIFileHeadProcess(stream);

    //层信息清空
    fMainItems->Clear();
    for(int i=0; i < this->fLayers; i++)
    {
        MLayerDataTreeNode* aItem = fMainItems->NewLayerData();
        aItem->Unit = this->fUnit;   //单位

        aItem->LoadSingleCliData(stream);
    }

    fclose(stream);
}

    //0 $$HEADERSTART
    //1 $$BINARY
    //2 $$UNITS/00000000.005000
    //3 $$VERSION/200
    //4 $$LABEL/1,part1
    //5 $$DATE/090317
    //6 $$DIMENSION/00000000.000000,00000000.000000,00000000.000000,00000010.000000,00000012.000000,00000009.742200
    //7 $$LAYERS/000007
    //8 $$HEADEREND
void MAMProject::BinaryCLIFileHeadProcess(FILE* stream)
{
    //读取文件头
    char  Header[14*16+2];
    fread(Header,sizeof(char),sizeof(Header),stream);

    String  aStr = String(Header);
    TStrings* aCliHeadeList = splitToStrings_Mask( aStr,"\n");    //拆分

    if(aCliHeadeList->Count != 9)
          throw Exception("读取文件格式出错，文件头解析错误");

    //单位
    String aKey,aValue;
    SplitStrTo2Str(aCliHeadeList->Strings[2],"/",aKey,aValue,true);
    fUnit = StrToFloat(aValue);

    //层数
    SplitStrTo2Str(aCliHeadeList->Strings[7],"/",aKey,aValue,true);
    fLayers = StrToInt(aValue);
}


void MAMProject::LoadCLiHeaderInfoFromStrings(TStrings* aStrings)
{
   if(aStrings == NULL || aStrings->Count ==0)  return;

   for(int i=0; i < aStrings->Count; i++)
   {
      String  aLine = aStrings->Strings[i];
      String  aKey,aValue;
      if( HasSubString(aLine,"$$HEADEREND"))  //结束
      {
          break;
      }
      else if( HasSubString(aLine,"$$UNITS")) //单位 mm
      {
          SplitStrTo2Str(aLine,"/",aKey,aValue,true);
          fUnit = StrToFloat(aValue);
      }
      else if(HasSubString( aLine,"$$LAYERS"))  //层
      {
          SplitStrTo2Str(aLine,"/",aKey,aValue,true);
          fLayers = StrToInt(aValue);
      }
      else if(HasSubString( aLine,"$$LABEL"))  //PartID
      {
          SplitStrTo2Str(aLine,"/",aKey,aValue,true);
          fPartID = StrToInt(aValue);
      }
   }
}

//用于打印的: 要转化为dxf文件
void MAMProject::LoadCLiLayerInfoFromStrings(TStrings* aStrings,bool  bConvertDxf)
{
    if(aStrings == NULL || aStrings->Count ==0)  return;
    if(fLayers == 0)   throw Exception("CLI 文件错误");

    int iLayerNo = 1;
    int aMaxID = 1;

    bool bBegin = false;
    bool bEnd = false;
    String aAbsoluteHeight;
    String  aKey,aValue;
    int  iBgIndex,iEndIndex;

    //String  aLayerFileName;
    //String  aLayerEdgeFileName;
    //String  aLayerPath;
    //String  aSingleCLiFileName;
    //String  aSingleCLiPath;

    /*
    if(bConvertDxf)   //新建的时候：创建目录
    {
        aLayerPath= ProjectDirName(fProjectFileName) + "\\_Layer";
        DelDirFiles(aLayerPath);
        CheckAndMakeDirectory(aLayerPath);

        aSingleCLiPath= ProjectDirName(fProjectFileName) + "\\_Cli";
        DelDirFiles(aSingleCLiPath);
        CheckAndMakeDirectory(aSingleCLiPath);
    }
    */

    for(int i=0; i <  aStrings->Count; i++)
    {
        String  aLine = aStrings->Strings[i];
        if(HasSubString( aLine,"$$LAYER/") == false)  continue;

        //获取该层的绝对高度
        if(bBegin == false)
        {
            SplitStrTo2Str(aLine,"/",aKey,aValue,true);
            aAbsoluteHeight = aValue;
            iBgIndex = i;
            bBegin = true;

            if(iLayerNo == fLayers) //最后一层
            {
                bEnd = true;
                iEndIndex = aStrings->Count-2;
            }
        }
        else
        {
            bEnd = true;
            iEndIndex = i-1;
        }

        if(bBegin && bEnd) //首尾都找到了
        {
            //处理
            bBegin = false;
            bEnd = false;

            MLayerDataTreeNode* aRoot = fMainItems->Items[0];
            String aParentName = "";
            if(aRoot != NULL)  //没有根节点
                  aParentName = aRoot->LayerDataID;

            String  aName = "第 "+ IntToStr(iLayerNo) + " 层轮廓";
            String  aNoPathDXFFile = "";//"Layer_"+IntToStr(iLayerNo) +".dxf";
            String  aNoPathCLIFile = "Cli_"+IntToStr(iLayerNo) +".dat";

            MLayerDataTreeNode* aItem = fMainItems->NewLayerData_MT(aMaxID,aName,"1",
                             aParentName,"1",aNoPathCLIFile,aNoPathDXFFile);
            aItem->AbsoluteHeight = aAbsoluteHeight;
            aItem->LayerNo = iLayerNo;

            aMaxID++;
            fMainItems->Add(aItem);

            aItem->iBeginLine = iBgIndex;
            aItem->iEndLine = iEndIndex;

            /*
            if(bConvertDxf)   //新建的时候
            {
                 TStringList*  aSubFile = new TStringList;
                 CopyStrings(aSubFile,aStrings,iBgIndex,iEndIndex);

                 aLayerEdgeFileName = aLayerPath+"\\Edge_Layer_"+IntToStr(iLayerNo) +".dxf";
                 //处理
                 aLayerFileName = aItem->ConvertCli2Dxf(aSubFile,aLayerPath); //填充线的文件
                 aItem->DXFFileName = aLayerFileName;   //Layer_i_1.dxf;Layer_i_2.dxf;Layer_i_3.dxf

                 aSingleCLiFileName = aSingleCLiPath + "\\Cli_"+IntToStr(iLayerNo) +".dat";
                 aSubFile->SaveToFile(aSingleCLiFileName);

                 delete aSubFile;
            }
            */

            i = iEndIndex;
            iLayerNo++;  //层号
            gError->Warn1("正在加载节点:" + IntToStr(fMainItems->Count) + "/" + IntToStr(fLayers+1));
        }
    }

}




//边界的文件
void  MAMProject::ConvertEdgeCli2Dxf(TStrings* aSubFileStrings,String aSaveFileName)
{
}







//设置工程信息(新建)
void  MAMProject::SetPrjInformation(String aPrjFileName,String aPrjName)
{
    ProjectFileName = aPrjFileName;
    ProjectName = aPrjName;
}

String MAMProject::readConfigFileName()
{
    return ReplaceStr(ProjectFileName,C_PrjExt,".cfg",false);
}



//不带斜杠
String  MAMProject::readPrjLocation()
{
    if(ProjectFileName == "")   throw Exception("工程名为空");

    return ExtractFilePath_Format(ProjectFileName);
}

void MAMProject::CheckMainStruct( TStrings* aStrings, int& iTreeBegin, int& iTreeEnd )
{
    //1、获取要提取的数据段
    iTreeBegin = GetIndexFromStrings_ByName(aStrings,"BEGINTREE","",0);
    iTreeEnd =  GetIndexFromStrings_ByName(aStrings,"ENDTREE","",0);
}

String  MAMProject::SaveCatalogStruct(String  aOutFileName)
{
    //先保存数据
    //TStrings*  aList = fMainItems->SaveCatalogDatas();
    //if(aOutFileName == "")
    //    aOutFileName = CfgFileName;
    //aList->SaveToFile(aOutFileName);


    //保存结构
    TStrings* aList = fMainItems->SaveCatalogStruct();
    aList->Insert(0,"BeginTree");
    aList->Add("EndTree");

    //TStringList*  aData = new TStringList;
    //aData->LoadFromFile(aOutFileName);
    //aList->AddStrings(aData);

    if(aOutFileName == "")
        aOutFileName = CfgFileName;
    aList->SaveToFile(aOutFileName);

    delete aList;
    //delete aData;
    return "";
}


//------------------------------------------------------------------------------
//用于打开工程
void  MAMProject::LoadLayerDataItemsFromFile()
{
     LoadLayerDataItemsFromFile(CfgFileName,LayersDataHolder);
}

//用于打开工程
//aCfgFName: 配置文件
//aTree: output
void MAMProject::LoadLayerDataItemsFromFile( String aModelFileName, TTreeView* aTree)
{
    TStringList* aNodeItems = CheckAndLoadFromFile(aModelFileName);

    //加载主树MainItems
    LoadLayerDataItemsFromFile( aNodeItems );
    delete aNodeItems;

    //整个工程数据层的个数，不包括工程根节点
    fLayers = MainItems->Count - 1;

    if(aTree != NULL)
         MainItems->ToTreeView(aTree);

    if(fLayerDataSelect != NULL)
        MainItems->ToComboBox(fLayerDataSelect);
}





//只加载数据项
void  MAMProject::LoadLayerDatasFromFile(String aCfgFile)
{
/*
    TStringList* aNodeItems = CheckAndLoadFromFile(aCfgFile);

    //LoadLayerStr
    //保存为dxf
    String  aLayerPath = ProjectLocation + "\\_Layer";
    DelDirFiles(aLayerPath);
    CheckAndMakeDirectory(aLayerPath);
    int  aBeginSearch = 0;
    int  aEndSearch;

    for(int i = 0; i < MainItems->Count; i++)  //层
    {
         MLayerDataTreeNode*  aItem = MainItems->Items[i];   //第一个节点
         if(aItem->Type == "0")
              continue;

         //aItem->LoadSingleCliData(aNodeItems);
         aItem->GetCliDataStrings(aNodeItems,aBeginSearch,aEndSearch);   //装载到CliDataStrings中

         String  aLayerFileName = aLayerPath+"\\Layer_"+IntToStr(i) +".dxf";
         ConvertCli2Dxf(aItem->CliDataStrings,aLayerFileName);

         gError->WarnAdd1_Percent("正在装载和保存DXF文件",i,MainItems->Count);

         aBeginSearch = aEndSearch;
     }

     gError->WarnAdd1("装载和保存DXF文件完成");

    delete aNodeItems;
*/
}

//------------------------------------------------------------------------------
//用于打开工程
void MAMProject::LoadLayerDataItemsFromFile(TStrings* aStrings)
{
     int iTreeBegin;
     int iTreeEnd;
     CheckMainStruct( aStrings, iTreeBegin, iTreeEnd );

     String  aName, aValue;
     MainItems->Clear();

     //生成节点参数
     for(int i = iTreeBegin+1; i < iTreeEnd; i++)
     {
          SplitStrTo2Str( aStrings->Strings[i], ",", aName, aValue );
          if( aName.UpperCase() != "NODE" )     //过滤
                    continue;
          MainItems->NewLayerDataItem(aValue); //添加

          gError->WarnAdd1_Percent("正在加载层数据信息,请稍后",i,iTreeEnd - iTreeBegin - 1);
     }

     //LoadLayerStr
/*
     int  iBeginSearch = iTreeEnd+1;
     int  iEndSearchItem;
     for(int i = 0; i < MainItems->Count; i++)  //层
     {
         MLayerDataTreeNode*  aItem = MainItems->Items[i];   //第一个节点
         if(aItem->Type == "0")  //根节点
              continue;

         aItem->LoadSingleCliData(aStrings,iBeginSearch,iEndSearchItem);

         gError->WarnAdd1_Percent("正在加载层数据信息,请稍后",i,MainItems->Count);

         iBeginSearch = iEndSearchItem+1;
     }
*/
     //gError->WarnAdd1("加载层数据信息完成");
}

double   MAMProject::readMiddleX()
{
    return (PartMinX + PartMaxX)/2.0;
}

double   MAMProject::readMiddleY()
{
    return (PartMinY + PartMaxY)/2.0;
}

double   MAMProject::readPartDimX()
{
    return  PartMaxX - PartMinX;
}

double   MAMProject::readPartDimY()
{
    return PartMaxY - PartMinY;
}

//--------------------------MLayerDataTreeNode---------------------------------
MLayerDataTreeNode::MLayerDataTreeNode(MTreeNodes_LayerData* aItems)
{
   fItems = aItems;

   fLayerDataID = "";

   fCLIFileName = "";
   fDXFFileName = "";
   fParentName = "";
   fImageIndex = 0;
   fTreeNode = NULL;
   fNodeName = "";

   fPolyLines = new MPolyLines;             //有很多polyline
   fHatchLines = new MHatchLines;           //有很多hatchLine
   fCliDataStr = new TStringList;

   fPartDatas_InOut = new MPartDatas_LayerDataTreeNode;
}

//释放资源
void  MLayerDataTreeNode::Dispose()
{
    fPolyLines->Dispose();
    delete fPolyLines;

    fHatchLines->Dispose();
    delete fHatchLines;

    fCliDataStr->Clear();
    delete  fCliDataStr;

    fPartDatas_InOut->Dispose();
    delete fPartDatas_InOut;
}

void  MLayerDataTreeNode::DxfOutFromStrings(TStringList* aRetStrings,TStrings*  aStrList)
{
   if(aStrList == NULL || aStrList->Count < 1)  return;

    for(int i=0; i < aStrList->Count; i++)
    {
        String  aStr = aStrList->Strings[i];
        DxfOutFromString(aRetStrings,aStr);
    }

    aRetStrings->Add("0");
    aRetStrings->Add("ENDSEC");
}

void MLayerDataTreeNode::DxfOutFromString(TStringList* aRetStrings,String  aStr)
{
    if(HasSubString(aStr,"$$POLYLINE/1"))
    {
        DxfOutFromPOLYLINE(aRetStrings,aStr);
    }
    else if(HasSubString(aStr,"$$HATCHES/1"))
    {
        DxfOutFromHATCHES(aRetStrings,aStr);
    }
}

void MLayerDataTreeNode::DxfOutFromPOLYLINE(TStringList* aResult,String aStr)
{
    TStrings* aTempStrList = splitToStrings_Mask( aStr, " ");

    int iPointCount = StrToInt(aTempStrList->Strings[2]);
    if(iPointCount > 0)  //写头信息
    {
        aResult->Add("   0");
        aResult->Add(" POLYLINE");
        aResult->Add(" 5");
        aResult->Add(" F1");
        aResult->Add(" 8");
        aResult->Add(" 0");
        aResult->Add(" 66");
        aResult->Add(" 1");
    }
    for(int i=0; i < iPointCount; i++)
    {
        String  xValue = aTempStrList->Strings[3 + i*2];
        String  yValue = aTempStrList->Strings[3 + i*2 + 1];

        aResult->Add(" 0");
        aResult->Add(" VERTEX");
        aResult->Add(" 8");
        aResult->Add(" 0");
        aResult->Add(" 10");
        aResult->Add(xValue);
        aResult->Add(" 20");
        aResult->Add(yValue);
        aResult->Add(" 30");
        aResult->Add("0.0");
    }
    aResult->Add(" 0");
    aResult->Add("SEQEND");

    delete aTempStrList;
}

void  MLayerDataTreeNode::DxfOutFromHATCHES(TStringList* aResult,String aStr)
{
    TStrings* aTempStrList = splitToStrings_Mask( aStr, " ");

    int iLineCount = StrToInt(aTempStrList->Strings[1]);
    if(iLineCount > 0)  //写头信息
    {
        aResult->Add("   0");
        aResult->Add(" LINE");
        aResult->Add(" 5");
        aResult->Add(" F1");
        aResult->Add(" 8");
        aResult->Add(" 0");
    }
    for(int i=0; i < iLineCount; i++)
    {
        String  xValue = aTempStrList->Strings[2 + i*4];
        String  yValue = aTempStrList->Strings[2 + i*4 + 1];

        aResult->Add(" 10");
        aResult->Add(xValue);
        aResult->Add(" 20");
        aResult->Add(yValue);
        aResult->Add(" 30");
        aResult->Add("0.0");

        xValue = aTempStrList->Strings[4 + i*4];
        yValue = aTempStrList->Strings[4 + i*4 + 1];

        aResult->Add(" 11");
        aResult->Add(xValue);
        aResult->Add(" 21");
        aResult->Add(yValue);
        aResult->Add(" 31");
        aResult->Add("0.0");
    }

    delete aTempStrList;
}

//填充线的文件
//提取一层的文件信息，然后构建：laser,path格式
String  MLayerDataTreeNode::ConvertCli2Dxf(TStringList* aSubFileStrings,String  aLayerPath)
{
    //1、找到有多少Part
    if(aSubFileStrings==NULL || aSubFileStrings->Count == 0) return "";

    fPartDatas_InOut->Clear();

    MPartData_LayerDataTreeNode*  aItem = NULL;
    String aKey,aValue;
    TStringList*  aFileList = NULL;

    String  aRet = "";
    int  iNum = 1;

    for(int i=0; i < aSubFileStrings->Count; i++)
    {
        String  aStr = aSubFileStrings->Strings[i];
        if( HasSubString(aStr,"$$LAYER"))
              continue;
        else if( HasSubString(aStr,"Power")) //i,i+1
        {
            aItem = fPartDatas_InOut->NewPartData_LayerDataTreeNode();
            SplitStrTo2Str(aStr,"=",aKey,aValue,true);
            aItem->LaserPower = StrToFloat(aValue);
        }
        else if(HasSubString(aStr,"Speed"))
        {
            SplitStrTo2Str(aStr,"=",aKey,aValue,true);
            aItem->LaserSpeed = StrToFloat(aValue);

            if(aFileList == NULL)                       //第一个
                 aFileList = new TStringList;
            else
            {
                 //多余一个的保存
                 TStringList*  aAddLists = new TStringList;
                 aAddLists->LoadFromFile(ApplicationPath() + "\\system\\dxfHead.dxf");
                 DxfOutFromStrings(aAddLists,aFileList);
                 aAddLists->Add("0");
                 aAddLists->Add("EOF");

                 String  aSubFileName = "Layer_"+ LayerNo + "_" + IntToStr(iNum)+".dxf";
                 aAddLists->SaveToFile(aLayerPath + "\\"+ aSubFileName);
                 aRet = aRet + aSubFileName;
                 aRet = aRet + ";";
                 delete aAddLists;

                 iNum++;

                 aFileList->Clear();
            }
        }
        else
        {
             aFileList->Add(aStr);
        }
    }

    //多余一个的保存
    TStringList*  aAddLists = new TStringList;
    aAddLists->LoadFromFile(ApplicationPath() + "\\system\\dxfHead.dxf");
    DxfOutFromStrings(aAddLists,aFileList);
    aAddLists->Add("0");
    aAddLists->Add("EOF");

    String  aSubFileName = "Layer_"+ LayerNo + "_" + IntToStr(iNum)+".dxf";
    aAddLists->SaveToFile(aLayerPath + "\\"+ aSubFileName);
    aRet = aRet + aSubFileName;


    delete aAddLists;
    delete aFileList;
    return aRet;
}


//用于二进制文件的处理
void MLayerDataTreeNode::LoadSingleCliData(FILE* stream)
{

}

void  MLayerDataTreeNode::GetCliDataStrings(TStrings*  aStrings,int aItemBeginSearch,int& iItemEnd)
{
    int iTreeBegin = aItemBeginSearch;
    int iTreeEnd;

    CheckSubStruct(aStrings,iTreeBegin, iTreeEnd );

    CopyStrings(CliDataStrings,aStrings,iTreeBegin+1,iTreeEnd-1);
    iItemEnd = iTreeEnd;
}

MLayerDataTreeNode::~MLayerDataTreeNode()
{
    fPolyLines->Clear();
    delete fPolyLines;

    fHatchLines->Clear();
    delete fHatchLines;

    fCliDataStr->Clear();
    delete fCliDataStr;
}

void MLayerDataTreeNode::CheckSubStruct( TStrings* aStrings, int& iTreeBegin, int& iTreeEnd )
{
    //1、获取要提取的数据段
    iTreeBegin = GetIndexFromStrings_ByName(aStrings,"Bgn" + Name,fLayerDataID,iTreeBegin);
    iTreeEnd =  GetIndexFromStrings_ByName(aStrings,"End" + Name,fLayerDataID,iTreeBegin);
}


void  MLayerDataTreeNode::LoadSingleCliData(TStrings* aStrings,int aItemBeginSearch,int& iItemEnd)
{
     GetCliDataStrings(aStrings,aItemBeginSearch,iItemEnd);    //装载到CliDataStrings
     ProcessCliData(CliDataStrings);
}

void  MLayerDataTreeNode::SaveToCliDataStrings(TStrings* aStrings)
{
     CliDataStrings->Clear();
     CliDataStrings->AddStrings(aStrings);
}

void MLayerDataTreeNode::ProcessCliData(TStrings* aStrings)
{
     if(aStrings==NULL || aStrings->Count <=0)  return;

     fPartDatas_InOut->Clear();
     MPartData_LayerDataTreeNode*  aItem = NULL;
     String aKey,aValue;

     PolyLines->Clear();
     HatchLines->Clear();

     for(int i=0; i < aStrings->Count; i++)
     {
         String  aLine = aStrings->Strings[i];

         if(HasSubString(aLine,"Power"))
         {
             aItem = fPartDatas_InOut->NewPartData_LayerDataTreeNode();
             SplitStrTo2Str(aLine,"=",aKey,aValue,true);
             aItem->LaserPower = StrToFloat(aValue);
         }
         else if(HasSubString(aLine,"Speed"))
         {
             SplitStrTo2Str(aLine,"=",aKey,aValue,true);
             aItem->LaserSpeed = StrToFloat(aValue);
         }
         else if(HasSubString( aLine,"$$LAYER/"))
         {
             String aKey,aValue;
             SplitStrTo2Str(aLine,"/",aKey,aValue,true);
             AbsoluteHeight = aValue;
         }
         else if(HasSubString( aLine,"$$POLYLINE/"))
         {
             MPolyLine* aItem = PolyLines->NewPolyLine();
             aItem->LoadPolyLineData(aLine);
         }
         else if(HasSubString( aLine,"$$HATCHES/"))
         {
             LoadHatchLine(aLine);
         }
     }
}

void  MLayerDataTreeNode::LoadHatchLine(String aLine)
{
    TStrings* aTempStrList = splitToStrings_Mask( aLine, " ");
    int iLineCount = StrToInt(aTempStrList->Strings[1]);

    for(int i=0; i <  iLineCount; i++)
    {
        String  xStartValue = aTempStrList->Strings[2 + i*4];
        String  yStartValue = aTempStrList->Strings[2 + i*4 + 1];
        String  xEndValue = aTempStrList->Strings[2 + i*4 + 2];
        String  yEndValue = aTempStrList->Strings[2 + i*4 + 3];

        HatchLines->NewHatchLine(StrToFloat(xStartValue),StrToFloat(yStartValue),
                                 StrToFloat(xEndValue),StrToFloat(yEndValue));
    }
    if(aTempStrList)
    {
        delete  aTempStrList;
        aTempStrList = NULL;
    }
}

double MLayerDataTreeNode::readMinX()
{
    double aMin = MAXFLOAT;

    if(fPolyLines->Count !=0)
    {
        for(int i=0; i < fPolyLines->Count; i++)
        {
            MPolyLine* aItem = fPolyLines->Items[i];
            if(aMin > aItem->Points->MinX)
                  aMin = aItem->Points->MinX;
        }
    }
    else  //填充线
    {
        for(int i=0; i < fHatchLines->Count;i++)
        {
           MHatchLine* aItem = fHatchLines->Items[i];
           if(aMin > aItem->Points->MinX)
              aMin = aItem->Points->MinX;
        }
    }

    return aMin;
}

double MLayerDataTreeNode::readMaxX()
{
    double aMax = -MAXFLOAT;

    if(fPolyLines->Count !=0)
    {
        for(int i=0; i < fPolyLines->Count; i++)
        {
            MPolyLine* aItem = fPolyLines->Items[i];
            if(aMax < aItem->Points->MaxX)
                  aMax = aItem->Points->MaxX;
        }
    }
    else  //填充线
    {
        for(int i=0; i < fHatchLines->Count;i++)
        {
           MHatchLine* aItem = fHatchLines->Items[i];
           if(aMax < aItem->Points->MaxX)
              aMax = aItem->Points->MaxX;
        }
    }


    return aMax;
}

double MLayerDataTreeNode::readRotateX()
{
    return (MinX + MaxX)/2.0;
}

double MLayerDataTreeNode::readRotateY()
{
    return (MinY + MaxY)/2.0;
}

double MLayerDataTreeNode::readMinY()
{
   double aMin = MAXFLOAT;

   if(fPolyLines->Count !=0)
   {
      for(int i=0; i < fPolyLines->Count; i++)
      {
          MPolyLine* aItem = fPolyLines->Items[i];
          if(aMin > aItem->Points->MinY)
                aMin = aItem->Points->MinY;
      }
    }
    else
    {
       for(int i=0; i < fHatchLines->Count;i++)
        {
           MHatchLine* aItem = fHatchLines->Items[i];
           if(aMin > aItem->Points->MinY)
              aMin = aItem->Points->MinY;
        }
    }

    return aMin;
}

double MLayerDataTreeNode::readMaxY()
{
    double aMax = -MAXFLOAT;

     if(fPolyLines->Count !=0)
    {
      for(int i=0; i < fPolyLines->Count; i++)
      {
          MPolyLine* aItem = fPolyLines->Items[i];
          if(aMax < aItem->Points->MaxY)
                aMax = aItem->Points->MaxY;
      }
    }
    else
    {
       for(int i=0; i < fHatchLines->Count;i++)
        {
           MHatchLine* aItem = fHatchLines->Items[i];
           if(aMax < aItem->Points->MaxY)
              aMax = aItem->Points->MaxY;
        }
    }

    return aMax;
}

double MLayerDataTreeNode::readSizeX()
{
    return MaxX - MinX;
}

double MLayerDataTreeNode::readSizeY()
{
    return  MaxY - MinY;
}

//DM作为一个树节点
String MLayerDataTreeNode::SaveCatalogStruct()
{
    String  aParentID= "";
    String  aImageIndex;

    if(TreeNode->Parent != NULL)  //不是根节点
    {
          MLayerDataTreeNode*  aParentNodeData = (MLayerDataTreeNode*)TreeNode->Parent->Data;
          if(aParentNodeData == NULL)
                 throw Exception("MDataModuleTreeNode->aParentNodeData is null");
          aParentID = aParentNodeData->fLayerDataID;
    }
    if(TreeNode != NULL)
         aImageIndex = TreeNode->Level;
    else
         aImageIndex = fImageIndex;


    return "Node,NodeId=" + LayerDataID +
                ",Name=" + Name +
                ",Type=" + Type +
                +",PARENT=" +aParentID+
                ",ImageIndex=" + aImageIndex+
                ",CLIFileName=" + CLIFileName+
                ",DXFFileName=" + DXFFileName;
}

String MLayerDataTreeNode::SaveCatalogData()
{
    TStrings*  aDatas = new TStringList;

    aDatas->Add("$$LAYER/" + fAbsoluteHeight);                                  //层信息
    aDatas->AddStrings(fPolyLines->OutPolyLine());                              //PolyLine 输出
    aDatas->AddStrings(fHatchLines->OutHatchLine());                            //HatchLine

    aDatas->Insert(0,"Bgn" + this->Name + "," + this->LayerDataID);
    aDatas->Add("End" + this->Name + "," + this->LayerDataID);

    String  aRet = aDatas->Text;

    delete  aDatas;
    return  aRet;
}


MLayerDataTreeNode* MLayerDataTreeNode::readParent()
{
    if( ParentName == "" || Items == NULL )
       return NULL;

    return (MLayerDataTreeNode*)Items->Items_ByName[ ParentName ];
}

void MLayerDataTreeNode::DrawInOpenGL()
{
    glBegin(GL_LINE_LOOP);						// Draw A Quad
         glColor3f(0.0f,1.0f,0.0f);			// Set The Color To Red
         glVertex3f(Items->MinX,Items->MinY,0.0f);      //左下
         glVertex3f(Items->MinX,Items->MaxY,0.0f);      //左上
         glVertex3f(Items->MaxX,Items->MaxY,0.0f);      //右上
         glVertex3f(Items->MaxX,Items->MinY,0.0f);      //右下
         glVertex3f(Items->MinX,Items->MinY,0.0f);
    glEnd();
}

void MLayerDataTreeNode::DoMovePart(double  aPartMoveX,double aPartMoveY)
{
    PolyLines->DoMovePart(aPartMoveX,aPartMoveY);
    HatchLines->DoMovePart(aPartMoveX,aPartMoveY);
}

void MLayerDataTreeNode::DoScalePart(double aPartScaleX,double aPartScaleY)
{
    PolyLines->DoScalePart(aPartScaleX,aPartScaleY,RotateX,RotateY);
    HatchLines->DoScalePart(aPartScaleX,aPartScaleY,RotateX,RotateY);
}

//-----------------------------M2DPoint----------------------------------------
M2DPoint::M2DPoint(M2DPoints* aItems)
{
    fItems = aItems;

    fX = 0.0;
    fY = 0.0;
}

String  M2DPoint::OutPoint()
{
    String aX;

    aX.sprintf("%.3f  %.3f",fX,fY);

    return aX;//FloatToStr(fX) + " " + FloatToStr(fY);
}

void M2DPoint::DoScalePart(double aPartScaleX,double aPartScaleY,
                                           double aRotateX,double aRotateY)
{
    if(fabs(aPartScaleX-1.0) > 1e-4) //X轴变换
    {
        fX = aPartScaleX * fX + (1.0 - aPartScaleX)* aRotateX;
    }
    if(fabs(aPartScaleY-1.0) > 1e-4) //Y轴变换
    {
        fY = aPartScaleY * fY + (1.0 - aPartScaleY)* aRotateY;
    }
}

//-----------------------------M2DPoints----------------------------------------
M2DPoints::M2DPoints()
{
}

M2DPoint*  M2DPoints::New2DPoint(double aX,double aY)
{
   M2DPoint*  aItem = new M2DPoint(this);

   aItem->X = aX;
   aItem->Y = aY;

   this->Add(aItem);

   return aItem;
}

String   M2DPoints::OutPoints()
{
   String  aRet;

   for(int i=0; i < Count; i++)
   {
       M2DPoint* aItem = Items[i];
       String aStr = aItem->OutPoint() + " ";
       aRet += aStr;
   }
   return aRet;
}

double M2DPoints::readMinX()
{
   double  aMin = MAXFLOAT;

   for(int i=0; i < Count; i++)
   {
       M2DPoint* aItem = Items[i];
       if(aItem->X < aMin)
           aMin = aItem->X;
   }

   return aMin;


}

double M2DPoints::readMaxX()
{
   double  aMax = -MAXFLOAT;

   for(int i=0; i < Count; i++)
   {
       M2DPoint* aItem = Items[i];
       if(aItem->X > aMax)
           aMax = aItem->X;
   }

   return aMax;
}

double M2DPoints::readMinY()
{
   double  aMin = MAXFLOAT;

   for(int i=0; i < Count; i++)
   {
       M2DPoint* aItem = Items[i];
       if(aItem->Y < aMin)
           aMin = aItem->Y;
   }

   return aMin;
}

double M2DPoints::readMaxY()
{
   double  aMax = -MAXFLOAT;

   for(int i=0; i < Count; i++)
   {
       M2DPoint* aItem = Items[i];
       if(aItem->Y > aMax)
           aMax = aItem->Y;
   }

   return aMax;
}

//----------------------------MPolyLine-----------------------------------------
MPolyLine::MPolyLine(MPolyLines* aItems)
{
    fPoints = new M2DPoints();

    fItems = aItems;

    fPathType = -1;
}

void MPolyLine::Dispose()
{
    fPoints->Clear();
    delete fPoints;
}

String  MPolyLine::OutPolyLine()
{
    String  aHead = "$$POLYLINE/1 1 ";
    String  aCount = IntToStr(fPoints->Count);

    String  aPoints = fPoints->OutPoints();

    return aHead + aCount + " " + aPoints;
}

String  MPolyLine::OutPutContour2CLI()
{
    String  str,tempstr;

    int  numC = Points->Count;       //长方形，5个点
    //int  startNum = rand()% numC;    //0-5

    //多边形头
    str = "$$POLYLINE/1 ";
    tempstr.sprintf("%d %d  ",rand()%2,numC);
    str += tempstr;

    for(int i= 0; i < numC; i++)
    {
       //输出当前x，y坐标
       tempstr.sprintf("%.3f %.3f ",Points->Items[i]->X,Points->Items[i]->Y);
       str += tempstr;
    }
    //重复起始点
    //tempstr.sprintf("%.3f %.3f ",Points->Items[startNum]->X,Points->Items[startNum]->Y);
    //str += tempstr;

    return str;
}

void MPolyLine::LoadPolyLineData(String aLine)
{
    TStrings* aTempStrList = splitToStrings_Mask( aLine, " ");
    int iPointCount = StrToInt(aTempStrList->Strings[2]);

    Points->Clear();
    for(int i=0; i < iPointCount; i++)
    {
        String  xValue = aTempStrList->Strings[3 + i*2];
        String  yValue = aTempStrList->Strings[3 + i*2 + 1];

        Points->New2DPoint(StrToFloat(xValue),StrToFloat(yValue));
    }

    if(aTempStrList)
    {
        delete aTempStrList;
        aTempStrList = NULL;
    }
}

void  MPolyLine::PolyLineToPath(TPath& aPath,int scale)
{
    aPath.set_length(Points->Count);

    for(int i=0; i < Points->Count; i++)
    {
        M2DPoint*  aItem = Points->Items[i];

        aPath[i] = IntPoint(aItem->X*scale,aItem->Y*scale);
    }
}

void MPolyLine::DrawInOpenGL()
{
    glBegin(GL_LINE_LOOP);						// Draw A Quad
         glColor3f(0.0f,1.0f,0.0f);			// Set The Color To Red
         for(int  i=0; i < Points->Count; i++)
         {
             M2DPoint*  aItem = Points->Items[i];
             glVertex3f(aItem->X,aItem->Y,0.0f);
         }
    glEnd();
}

void MPolyLine::DoMovePart(double  aPartMoveX,double aPartMoveY)
{
    for(int  i=0; i < Points->Count; i++)
    {
        M2DPoint*  aItem = Points->Items[i];
        aItem->X += aPartMoveX;
        aItem->Y += aPartMoveY;
    }
}

void MPolyLine::DoScalePart(double aPartScaleX,double aPartScaleY,double aRotateX,double aRotateY)
{
    //旋转中心
    for(int  i=0; i < Points->Count; i++)
    {
        M2DPoint*  aItem = Points->Items[i];

        aItem->DoScalePart(aPartScaleX,aPartScaleY,aRotateX,aRotateY);
    }
}



//--------------------Polylines--------------------------------------------
MPolyLines::MPolyLines()
{
    TInitOptions InitOptions = TInitOptions()<<ioPreserveCollinear;
    fClipper = new TClipper(InitOptions);
}

void MPolyLines::Dispose()
{
    for(int i=0; i < Count; i++)
    {
        MPolyLine* aItem = Items[i];
        aItem->Dispose();
    }

    Clear();

    delete fClipper;
}

MPolyLine*  MPolyLines::NewPolyLine()
{
   MPolyLine*  aItem = new MPolyLine(this);

   Add(aItem);

   return aItem;
}

double MPolyLines::readMinX()
{
    double aMin = MAXFLOAT;

    for(int i=0; i < Count; i++)
    {
        MPolyLine* aItem = Items[i];
        if(aMin > aItem->Points->MinX)
              aMin = aItem->Points->MinX;
    }

    return aMin;
}

double MPolyLines::readMaxX()
{
    double aMax = -MAXFLOAT;

    for(int i=0; i < Count; i++)
    {
        MPolyLine* aItem = Items[i];
        if(aMax < aItem->Points->MaxX)
              aMax = aItem->Points->MaxX;
    }

    return aMax;
}

double MPolyLines::readMinY()
{
    double aMin = MAXFLOAT;

    for(int i=0; i < Count; i++)
    {
        MPolyLine* aItem = Items[i];
        if(aMin > aItem->Points->MinY)
              aMin = aItem->Points->MinY;
    }

    return aMin;
}

double MPolyLines::readMaxY()
{
    double aMax = -MAXFLOAT;

    for(int i=0; i < Count; i++)
    {
        MPolyLine* aItem = Items[i];
        if(aMax < aItem->Points->MaxY)
              aMax = aItem->Points->MaxY;
    }
    return aMax;
}


//int aType: Path的类型
void  MPolyLines::AddPaths(const TPaths& aPaths,int aScale,int aType)
{
   MPolyLine*  aItem = NewPolyLine();
   aItem->PathType = aType;
   for(int i=0; i < aPaths.Length; i++)
   {
       TPath aPath = aPaths[i];

       PathToPoints(aPath,aItem->Points,aScale);
   }
}

void MPolyLines::PathToPoints(const TPath& aPath,M2DPoints* aPoints,int aScale)
{
    aPoints->Clear();
    for(int i=0; i < aPath.Length; i++)
    {
        aPoints->New2DPoint(aPath[i].X*1.0/aScale,aPath[i].Y*1.0/aScale);
    }
    aPoints->New2DPoint(aPath[0].X*1.0/aScale,aPath[0].Y*1.0/aScale);
}

TStrings*   MPolyLines::OutPolyLine()
{
    TStrings* aDatas = new TStringList;

    for(int i=0; i < Count; i++)
    {
        MPolyLine*  aItem = Items[i];
        aDatas->Add(aItem->OutPolyLine());
    }

    return aDatas;
}

void MPolyLines::OutPutContours2CLI(TStrings*  aCLIFile)
{
    for(int i= Count-1; i >= 0; i--)
    {
        MPolyLine*  aItem = Items[i];
        if(aItem->PathType == 2) continue;                   //跳过虚线

        aCLIFile->Add(aItem->OutPutContour2CLI());
    }
}


void  MPolyLines::DoMovePart(double  aPartMoveX,double aPartMoveY)
{
   for(int i=0; i < Count; i++)
    {
        MPolyLine*  aItem = Items[i];
        aItem->DoMovePart(aPartMoveX,aPartMoveY);
    }
}

void  MPolyLines::DoScalePart(double aPartScaleX,double aPartScaleY,double aRotateX,double aRotateY)
{
    for(int i=0; i < Count; i++)
    {
        MPolyLine*  aItem = Items[i];
        aItem->DoScalePart(aPartScaleX,aPartScaleY,aRotateX,aRotateY);
    }
}

void MPolyLines::DrawInOpenGL()
{
    for(int i=0; i < Count; i++)
    {
        MPolyLine*  aItem = Items[i];
        aItem->DrawInOpenGL();
    }
}

//-----------------------------MHatchLine---------------------------------------
//代表一条填充线
MHatchLine::MHatchLine(MHatchLines*  aItems)
{
    fItems = aItems;

    fPoints = new M2DPoints();
}

MHatchLine::~MHatchLine()
{
    fPoints->Clear();
    delete fPoints;
}

void MHatchLine::Dispose()
{
    fPoints->Clear();
    delete fPoints;
}

String  MHatchLine::OutHatchLine()
{
    String  aHead = "$$HATCHES/1 1 ";
    String  aPoints = fPoints->OutPoints();

    return aHead + aPoints;
}

void  MHatchLine::DrawInOpenGL()
{
    glBegin(GL_LINES);						// Draw A Quad
         glColor3f(0.0f,0.0f,1.0f);			// Set The Color To Red
         for(int  i=0; i < Points->Count;)
         {
             //第一个点
             M2DPoint*  aItem = Points->Items[i];
             glVertex3f(aItem->X,aItem->Y,0.0f);

             //第二个点
             aItem = Points->Items[i+1];
             glVertex3f(aItem->X,aItem->Y,0.0f);

             i += 2;
         }
    glEnd();
}

void MHatchLine::DoMovePart(double  aPartMoveX,double aPartMoveY)
{
   for(int i=0; i < Points->Count; i++)
   {
       M2DPoint*  aItem = Points->Items[i];
       aItem->X += aPartMoveX;
       aItem->Y += aPartMoveY;
   }
}

void MHatchLine::DoScalePart(double aPartScaleX,double aPartScaleY,double aRotateX,double aRotateY)
{
   //旋转中心

   for(int i=0; i < Points->Count; i++)
   {
       M2DPoint*  aItem = Points->Items[i];

       aItem->DoScalePart(aPartScaleX,aPartScaleY,aRotateX,aRotateY);
   }
}

//-------------------------MHatchLines--------------------------------------------
MHatchLines::MHatchLines()
{
}

void MHatchLines::Dispose()
{
    for(int i=0; i < Count; i++)
    {
        MHatchLine* aItem = Items[i];
        aItem->Dispose();
    }

    Clear();
}


MHatchLine*  MHatchLines::NewHatchLine(double aStartPointX,double aStartPointY,
                                double aEndPointX,double aEndPointY)
{
    MHatchLine*  aItem = new MHatchLine(this);

    aItem->Points->New2DPoint(aStartPointX,aStartPointY);
    aItem->Points->New2DPoint(aEndPointX,aEndPointY);

    Add(aItem);

    return aItem;
}

void MHatchLines::DrawInOpenGL()
{
    for(int i=0; i < Count; i++)
    {
        MHatchLine*  aItem = Items[i];
        aItem->DrawInOpenGL();
    }
}

void MHatchLines::DoMovePart(double  aPartMoveX,double aPartMoveY)
{
    for(int i=0; i < Count; i++)
    {
        MHatchLine*  aItem = Items[i];
        aItem->DoMovePart(aPartMoveX,aPartMoveY);
    }
}

void MHatchLines::DoScalePart(double aPartScaleX,double aPartScaleY,double aRotateX,double aRotateY)
{
    for(int i=0; i < Count; i++)
    {
        MHatchLine*  aItem = Items[i];
        aItem->DoScalePart(aPartScaleX,aPartScaleY,aRotateX,aRotateY);
    }
}

void MHatchLines::OutPutContours2CLI(TStrings*  aCLIFile)
{
    for(int i = Count-1; i >= 0; i--)
    {
        MHatchLine*  aItem = Items[i];
        aCLIFile->Add(aItem->OutHatchLine());
    }
}

//------------------------------------------------------------------------------

TStrings*  MHatchLines::OutHatchLine()
{
    TStrings* aDatas = new TStringList;

    for(int i=0; i < Count; i++)
    {
        MHatchLine* aItem =  Items[i];

        aDatas->Add(aItem->OutHatchLine());
    }

    return aDatas;
}


//-------------------------MLaserPen--------------------------------------------
MLaserPen::MLaserPen(MLaserPens*  aItems)
{
    fPenID = 0;
    fPenName = "Default";
    fPenPower = "1";
    fPenSpeed = "500";
    fPenFreq = "5";   //频率

    fItems = aItems;
}

bool  MLaserPen::IsEqual(MLaserPen* aPen)
{
    return fPenID == aPen->PenID && fPenPower == aPen->PenPower
                   && fPenSpeed == aPen->PenSpeed && fPenFreq == aPen->PenFreq;
}

void MLaserPen::ToListView( TListView* aList )
{
  TListItem* aItem = ListView_FindByData( aList, (void*)this );
  if( aItem == NULL )
    ListView_AddItems( aList, FullName(), "@@", (void*)this );
  else
    ListView_SetItems( aItem, FullName(), "@@", (void*)this );
}

//图片映射，映射字符串
String  MLaserPen::FullName()
{
    return  IntToStr(fPenID) + "@@" + fPenName + "@@"
                + fPenPower  + "@@" + fPenSpeed  + "@@" + fPenFreq;
}

String  MLaserPen::SaveToString()
{
    return "Node,ID=" + IntToStr(fPenID) +   ",Name=" + this->fPenName +
               ",Power=" + this->fPenPower + ",Speed=" + this->fPenSpeed+
               ",Frequency=" + this->fPenFreq;
}


//----------------------------MLaserPens----------------------------------------
MLaserPens::MLaserPens()
{
}

MLaserPen*  MLaserPens::NewItem(int aID)
{
    MLaserPen*  aItem = new MLaserPen(this);
    aItem->PenID = aID;

    Add(aItem);

    return aItem;
}

void MLaserPens::LoadFromFile(String  aFileName)
{
    if(FileExists(aFileName))   //加载
    {
       TStrings*  aStrings = new TStringList;
       aStrings->LoadFromFile(aFileName);

       LoadFromStrings(aStrings);

       delete aStrings;
    }
    else   //创建
    {
       Clear();
       for(int i=1; i < 11; i++)   //创建10种笔
       {
           NewItem(i);
       }
    }
}

void MLaserPens::LoadFromStrings(TStrings* aStrings)
{
    if(aStrings == NULL || aStrings->Count < 1) return;

    Clear();

    String  aName,aValue;
    for(int i=0; i < aStrings->Count; i++)
    {
        String  aStr = aStrings->Strings[i];
        SplitStrTo2Str( aStr, ",", aName, aValue );
        if( aName.UpperCase() != "NODE" )     //过滤
                    continue;

        LoadItemFromString(aValue);
    }
}



void  MLaserPens::LoadItemFromString(String  aText)
{
    TStringList* aListGroup = NULL;

     try
     {
         aListGroup = splitToStrings(aText,",");  //拆分

         String  aID = Get_ListItemStr_ByName( aListGroup, "ID", "=", "unKnown");   //未知类型
         String  aName = Get_ListItemStr_ByName( aListGroup, "Name", "=", "unKnown" );
         String  aPower = Get_ListItemStr_ByName( aListGroup, "Power", "=", "unKnown");
         String  aSpeed = Get_ListItemStr_ByName( aListGroup, "Speed", "=", "unKnown");
         String  aFreq = Get_ListItemStr_ByName( aListGroup, "Frequency", "=", "unKnown");

         MLaserPen* aItem = NewItem(StrToInt(aID));
         aItem->PenName = aName;
         aItem->PenPower = aPower;
         aItem->PenSpeed = aSpeed;
         aItem->PenFreq = aFreq;

         delete aListGroup;
     }
     catch( Exception& e)
     {
        delete aListGroup;
        gError->Warn( "MLaserPens::LoadItemFromString出错!" + e.Message );
     }
}

void  MLaserPens::SaveToFile(String  aFileName)
{
     TStrings* aFile = new TStringList;

     for(int i=0; i < Count; i++)
     {
         MLaserPen*  aItem = Items[i];
         String  aItemStr = aItem->SaveToString();

         aFile->Add(aItemStr);
     }

     aFile->SaveToFile(aFileName);
}




void  MLaserPens::ToListView(TListView* aList)
{
    if( aList==NULL )   return;

    aList->ReadOnly = true;
    ListView_InitForGrid(aList);
    ListView_AddTitles( aList, "笔;名称;功率[瓦];速度[mm/s];频率[kHz]", "50;100;100;100;0", ";" );

    for( int i=0; i<Count; i++ )
    {
      MLaserPen* aItem = Items[i];
      if( aItem==NULL ) continue;

      aItem->ToListView(aList);
    }
    ListView_Refresh(aList);
}

void   MLaserPens::ToComboBox(TComboBox* aCBox)
{
    if(aCBox == NULL)  return;

    aCBox->Items->Clear();

    for(int i=0; i < Count; i++)
    {
       MLaserPen* aItem = Items[i];
       ObjectToComboBox(aCBox,(TObject*)aItem,"笔 " + IntToStr(aItem->PenID));   //显示模块名
    }
}


//--------------------------------MConfigVar------------------------------------
MConfigVar::MConfigVar(MConfigVars* aItems)
{
    fConfigVarType = "";
    fConfigVarName = "";
    fConfigVarCode = "";
    fConfigVarKey = "";
    fConfigVarValue = "";

    fItems = aItems;
}

//-----------------------------MConfigVars--------------------------------------
MConfigVars::MConfigVars()
{
}

MConfigVar*  MConfigVars::NewItem(String aVarType,String aVarName,String aVarCode,
                                    String aVarKey,String aVarValue)
{
    MConfigVar*  aItem = new MConfigVar(this);

    aItem->ConfigVarType = aVarType;
    aItem->ConfigVarName = aVarName;
    aItem->ConfigVarCode = aVarCode;
    aItem->ConfigVarKey = aVarKey;
    aItem->ConfigVarValue = aVarValue;

    this->Add(aItem);

    return aItem;
}

MConfigVar*  MConfigVars::FindItemByName(String  aType,String aName)
{
    for(int i=0; i < Count; i++)
    {
        MConfigVar* aItem = this->Items[i];
        if(aItem->ConfigVarType.Trim() == aType.Trim()
                        && aItem->ConfigVarName.Trim() == aName.Trim())
        {
            return aItem;
        }
    }
    return NULL;
}

void MConfigVars::LoadFromFile(String  aFileName)
{
    if(FileExists(aFileName))   //加载
    {
       TStrings*  aStrings = new TStringList;
       aStrings->LoadFromFile(aFileName);

       LoadFromStrings(aStrings);

       delete aStrings;
    }
}



void MConfigVars::LoadFromStrings(TStrings* aStrings)
{
    if(aStrings == NULL || aStrings->Count < 1) return;

    Clear();

    String  aName,aValue;
    for(int i=0; i < aStrings->Count; i++)
    {
        String  aStr = aStrings->Strings[i];
        SplitStrTo2Str( aStr, ",", aName, aValue );
        if( aName.UpperCase() != "NODE" )     //过滤
                    continue;

        LoadItemFromString(aValue);
    }
}

void  MConfigVars::LoadItemFromString(String  aText)
{
    TStringList* aListGroup = NULL;

     try
     {
         aListGroup = splitToStrings(aText,",");  //拆分

         String  aType = Get_ListItemStr_ByName( aListGroup, "NodeType", "=", "unKnown");   //未知类型
         String  aName = Get_ListItemStr_ByName( aListGroup, "NodeName", "=", "unKnown" );
         String  aCode = Get_ListItemStr_ByName( aListGroup, "NodeCode", "=", "unKnown");
         String  aKey = Get_ListItemStr_ByName( aListGroup, "NodeKey", "=", "unKnown");
         String  aValue = Get_ListItemStr_ByName( aListGroup, "NodeValue", "=", "unKnown");

         NewItem(aType,aName,aCode,aKey,aValue);

         delete aListGroup;
     }
     catch( Exception& e)
     {
        delete aListGroup;
        gError->Warn( "MLaserPens::LoadItemFromString(String  aText)" + e.Message );
     }
}


//----------------------------MPrint9BlocksTest---------------------------------
//主要用于测试块的打印，每次打印之前先扫描一次
MPrint9BlocksTest::MPrint9BlocksTest()
{
    Blocks = new MGroupPrint9Blocks;
}

MPrint9BlocksTest::~MPrint9BlocksTest()
{
    Blocks->Clear();
    delete Blocks;
}

void  MPrint9BlocksTest::FreshBlocks(String  aFileName)
{
    if(!FileExists(aFileName))  throw Exception("没有找到文件:" + aFileName);

    TStringList*  aFileLines = new TStringList;
    aFileLines->LoadFromFile(aFileName);

    String aName,aValue;
    Blocks->ClearGroups();

    for(int i=0; i < aFileLines->Count; i++)
    {
        String  aStr = aFileLines->Strings[i];
        SplitStrTo2Str( aStr, ",", aName, aValue );

        if( aName.UpperCase() != "GROUP" )     //过滤
                    continue;
        LoadGroupPrint9BlockFromText(aValue);
    }
    delete aFileLines;
}

void  MPrint9BlocksTest::LoadGroupPrint9BlockFromText(String aText)
{
     String aName,aValue,aID;

     SplitStrTo2Str( aText, ",", aName, aValue );  //aName="ID=XX"
     SplitStrTo2Str( aName, "=", aName, aID );

     LoadGroupPrint9BlockFromText(aID,aValue);
}


void  MPrint9BlocksTest::LoadGroupPrint9BlockFromText(String aID,String aItemList)
{
     MGroupPrint9Block* aItem = Blocks->NewGroupPrint9Block(StrToInt(aID));

     aItem->ItemList->AddStrings(splitToStrings(aItemList,","));
}


//----------------------------MGroupPrint9Block---------------------------------
MGroupPrint9Block::MGroupPrint9Block(MGroupPrint9Blocks* aItems)
{
    Items = aItems;
    GroupID = -1;
    ItemList = new TStringList;
}

MGroupPrint9Blocks::MGroupPrint9Blocks()
{
}

MGroupPrint9Block*   MGroupPrint9Blocks::NewGroupPrint9Block(int aGroupID)
{
    MGroupPrint9Block* aItem = new  MGroupPrint9Block(this);

    aItem->GroupID = aGroupID;

    this->Add(aItem);

    return aItem;
}

void  MGroupPrint9Blocks::ClearGroups()
{
    for(int i=0; i < Count; i++)
    {
        MGroupPrint9Block* aItem = Items[i];
        aItem->ItemList->Clear();
    }

    Clear();
}


//-----------CLI数据------------------------------------------------------------

/*
void MTreeNode_ModeObject::ToListBox(TListBox* aList)
{
    ObjectToListBox(aList,(TObject*)this,Name);   //显示模块名
}

void  MTreeNode_ModeObject::LocateDataElement()
{
    try
    {
        G_Word->SelBMS( TrueBookMarkNames );
    }
    catch( Exception& e )
    {
    }
}


String  MTreeNode_ModeObject::SaveItemStruct()
{
    return "Node,NodeId=" + fDataElementID +
               ",Name=" + Name +
               ",Type=" + Type;
}

void  MTreeNode_ModeObject::DeleteTreeNodeItem()
{
    try
    {
       G_Word->DelBMVals( TrueBookMarkNames );

       TStrings*  aVarNames = G_Word->GetVarNames("");
       String  aBookMark = BookMark();
       DelVarStringsIfIn(aBookMark,aVarNames);
    }
    catch( Exception& e )
    {
    }
}



String MTreeNode_ModeObject::InstPath()
{
   CheckAndMakeDirectory(ApplicationPath()+"\\DE实例化\\"+DataElementID);
   return ApplicationPath()+"\\DE实例化\\"+DataElementID;
}

void MTreeNode_ModeObject::ToListView_Instance( TListView* aList )
{
  TListItem* aItem = ListView_FindByData( aList, (void*)this );
  if( aItem == NULL )
    ListView_AddItems( aList, FullName_Instance(), "@@", (void*)this );
  else
    ListView_SetItems( aItem, FullName_Instance(), "@@", (void*)this );
}

//图片映射，映射字符串
String  MTreeNode_ModeObject::FullName_Instance()
{
    return  InstanceMapType + "@@" + InstanceMapString;
}

//--------------------------------MDataElement_Objects--------------------------
MTreeNodes_ModeObject::MTreeNodes_ModeObject(MDataModuleTreeNode* aOwner)
{
     fOwner = aOwner;
}

int  MTreeNodes_ModeObject::readMaxID()
{
     if(fOwner == NULL)
          throw Exception("MTreeNodes_ModeObject* fOwner == NULL in MDataElement_Objects");

     int aMaxID = gIniFile->ReadInteger("DataElement","DataElementID",-1);
     if(aMaxID == -1)   //没有,要写
     {
         aMaxID = 0;
         gIniFile->WriteInteger("DataElement","DataElementID",aMaxID);
     }

     return aMaxID;
}

void MTreeNodes_ModeObject::ToListView_Instance( TListView* aList )
{
    if( aList==NULL )
           return;

    aList->ReadOnly = true;
    ListView_InitForGrid(aList);
    ListView_AddTitles( aList, "映射类型;映射方式", "100;0", ";" );

    for( int i=0; i<Count; i++ )
    {
      MTreeNode_ModeObject* aItem = Items[i];
      if( aItem==NULL )
        continue;

      aItem->ToListView_Instance(aList);
    }
    ListView_Refresh(aList);
}


TStrings*  MTreeNodes_ModeObject::SaveItemsStruct()
{
    TStrings*  aList = new TStringList;

    for(int i=0; i < Count; i++)
    {
        MTreeNode_ModeObject*  aItem = Items[i];
        aList->Add(aItem->SaveItemStruct());
    }

    return aList;
}

void MTreeNodes_ModeObject::writeMaxID( int aID )
{
    if(fOwner == NULL)
          throw Exception("MDataModule_Object* fOwner == NULL in MDataElement_Objects");

    gIniFile->WriteInteger("DataElement","DataElementID",aID);
}

// aInfos: 返回的信息
void MTreeNodes_ModeObject::InstanceInsertObjectNodes( TStrings* aInfos,bool IsSmartUpdate )
{
  for( int i=0; i<Count; i++ )
  {
     MTreeNode_ModeObject* aModeNode = Items[i];

     String  aMapMode = G_Word->GetVarVal_NoExp(aModeNode->BookMark() + "_MapMode",false);
     if(aMapMode == "手动模式")
          continue;

     String aInfo = "";
     try
     {
       aInfo = aModeNode->InstanceInsertObjectNode(IsSmartUpdate);
       aInfos->Add( aModeNode->DataElementID + "=" + aInfo );
     }
     catch( Exception& e )
     {
       aModeNode->InstanceErrorCode = aInfo;
     }
  }
}


//------------------------------------------------------------------------------
//用于模板文件的节点创建： Node,aText
void  MTreeNodes_ModeObject::NewDataElement(String aText)
{
     TStringList* aListGroup = NULL;

     try
     {
         aListGroup = splitToStrings(aText,",");  //拆分

         String  aType = Get_ListItemStr_ByName( aListGroup, "Type", "=", "unKnown");   //未知类型
         String  aId = Get_ListItemStr_ByName( aListGroup, "NodeId", "=", "unKnown" );
         String  aName = Get_ListItemStr_ByName( aListGroup, "Name", "=", "unKnown");

         NewDataElement_AT(aId, aName, aType);   //添加到集合中

         delete aListGroup;
     }
     catch( Exception& e)
     {
        delete aListGroup;
        gError->Warn( "MDataElement_Objects::NewModeNodeItem出错!" + e.Message );
     }
}

//类型需要扩展；
MTreeNode_ModeObject* MTreeNodes_ModeObject::NewDataElement_AT(
                           String aID,String aName,  String aType)
{
    MTreeNode_ModeObject*  aItem = NewDataElement_MT(aID,aName,aType);

    Add(aItem);     //加入集合

    return aItem;
}

//这个函数不添加元素到集合中，需手动添加；
MTreeNode_ModeObject*  MTreeNodes_ModeObject::NewDataElement_MT(
                   String aID,String aName, String aType)
{
    if(aID == "unKnown" && aName == "unKnown" && aType == "unKnown")
            throw Exception("未知的DataElement类型");

    MTreeNode_ModeObject*  aItem = new MTreeNode_ModeObject(this);

    aItem->DataElementID = aID;
    aItem->Name = aName;
    aItem->NodeName = aName;
    aItem->Type = aType;

    return aItem;
}


void  MTreeNodes_ModeObject::ToListBox(TListBox* aList,bool bClear)
{
     if(aList == NULL)  return;

     if(bClear)
         aList->Items->Clear();

     for(int i=0; i < Count; i++)
     {
         MTreeNode_ModeObject* aItem = Items[i];
         aItem->ToListBox(aList);
     }
}

//--------------------------MParaMapElementItem---------------------------------
MParaMapElementItem::MParaMapElementItem( MParaMapElementItems* aItems )
{
     fItems = aItems;

      fSystemName = "";                                                    //系统名
      fConfig = "";                                                        //配置项
      fParaStatus = "";                                                    //------fParaStatus  : 参数状态，
      fParaValue = "";
      fUnit = "";                                                          //-------fUnit : "单位",
}

String   MParaMapElementItem::readSearchString()
{
     return "%" + fSystemName + "." + fConfig + "." + fParaStatus  + "." + Name + "%";
}

String  MParaMapElementItem::readParaValueString()
{
    return fParaValue + fUnit;
}

void  MParaMapElementItem::ToListView( TListView* aList)
{
    ListView_AddItems( aList, FullName(), "@@", (void*)this );
}

String  MParaMapElementItem::FullName()
{
    return  fSystemName + "@@" + fConfig + "@@" + fParaStatus + "@@" + Name
                 + "@@" + fParaValue + "@@" + fUnit;
}

//------------------------------MParaMapElementItems----------------------------
MParaMapElementItems::MParaMapElementItems()
{
}

MParaMapElementItem* MParaMapElementItems::NewParaMapElementItem(
                   String aSystem,String aParaStatus,String aParaName,
                   String aValue,String aUnit,String aConfig)
{
    MParaMapElementItem* aItem = new MParaMapElementItem( this );

    aItem->SystemName = aSystem;
    aItem->ParaStatus = aParaStatus;
    aItem->Name = aParaName;
    aItem->ParaValue = aValue;
    aItem->Unit = aUnit;
    aItem->Config = aConfig;

    Add(aItem);

    return aItem;
}

void MParaMapElementItems::ToListView( TListView* aList )
{
    if( aList==NULL )
           return;

    aList->ReadOnly = true;
    ListView_InitForGrid(aList);
    ListView_AddTitles( aList, "所属系统;配置项;参数状态;参数名;参数值;单位", "100;100;100;150;100;0", ";" );
    for( int i=0; i<Count; i++ )
    {
      MParaMapElementItem* aItem = Items[i];
      if( aItem == NULL )
        continue;

      aItem->ToListView(aList);
    }
    ListView_Refresh(aList);
}



//----------------------MExcelImporter------------------------------------------
MExcelImporter::MExcelImporter()
{
  fFileName = "";
  fProBar = NULL;
  fStatusBar = NULL;
}

//-------------------------------------------------------------
//功能：从Excel文件读取一个Product实例,并将其数据读取到t_Product_*数据表
//说明：将Excel文件读入的信息直接以结构树的方式存入到数据库
//-------------------------------------------------------------
bool MExcelImporter::ImportToListView
     ( String aFileName, TProgressBar* aProgressBar, TStatusBar* aStatusBar,TListView*  aLV)
{
  fFileName = aFileName;
  fProBar = aProgressBar;
  fStatusBar = aStatusBar;

  return ImportToListView(aLV);
}

bool MExcelImporter::ImportToListView(TListView*  aLV)
{
  _ImportToListView( G_Excel,aLV );
  return true;
}

void MExcelImporter::_ImportToListView( MExcelFun* aExcel,TListView*  aLV )
{
   throw Exception( "虚函数ImportToDB未定义！");
}

//------------------------------------------------------------------------------
//功能：确定数据标题的"列"
//------------------------------------------------------------------------------
int MExcelImporter::FindTitleCol( MExcelFun* aExcel, String aTitle, int aRowTitle )
{
  try
  {
     for(int iColumn = 1; iColumn < 50; iColumn++)
     {
         String aItemName = Trim( aExcel->GetSheetCellValue(aRowTitle,iColumn) );           //10
         if( UpperCase(aItemName) == UpperCase(aTitle) )
           return iColumn;
     }
     return -1;
  }
  catch( Exception& e )
  {
    return -1;
  }
}

//------------------------------------------------------------------------------
//获取数据：
//------------------------------------------------------------------------------
int  MExcelImporter::GetRowCount( MExcelFun* aExcel, int aBgnRow )
{
  gError->Warn1("获取记录总数");

  int aRow=aBgnRow;
  for( ;; )
  {
     String aLevelStr = aExcel->GetSheetCellValue( aRow,2 );
     if( aLevelStr.Trim() == "" )    //结束标志
        break;
     gError->Warn1( "获取记录总数"+IntToStr(aRow) );
     aRow = aRow+1;
     Application->ProcessMessages();
   }
   gError->Warn1("获取数据进度结束");
   return aRow-aBgnRow+1;
}


//-------------------------MMapElement_ExcelImporter----------------------------
MMapElement_ExcelImporter::MMapElement_ExcelImporter()
{
    fMapElementItems = new MParaMapElementItems();
}

void MMapElement_ExcelImporter::ReplaceMapPara_NoExp ()
{
  try
  {
    for(int i=0; i<MapElementItems->Count; i++ )
    {
      MParaMapElementItem* aMapItem = (MParaMapElementItem*)MapElementItems->Items[i];
      gError->WarnAdd1_Percent( "正在替换参数(" +aMapItem->SearchString+ ")为(" +
                                aMapItem->ReplaceString+ ")", i ,MapElementItems->Count );
      G_Word->ReplaceContentStr( aMapItem->SearchString,aMapItem->ReplaceString );
    }
  }
  catch( Exception& e )
  {
    gError->Warn( "参数替换出错！"+e.Message );
  }
}

//Old: "系统.状态.参数名"------------> "系统.配置项.状态.参数名"
void MMapElement_ExcelImporter::_ImportToListView(MExcelFun* aExcel,TListView*  aLV)
{
    if( FileExists(FileName) == false )
       throw Exception( "文件(" +FileName+ ")不存在!" );

    //1、打开Excel
    aExcel->ConfirmOpenFile(FileName);

    try
    {
       if(IsNeededFile(aExcel) == false)                                        //add by zzh0918
           throw Exception("该文件不是所需的文件类型！！！");

      //激活第i页
      aExcel->WorkSheets_Item[0].Exec(Procedure("Activate"));
      int iRows = aExcel->Rows_Record(aExcel->WorkSheets_Item[0]);

      //获得系统个数
      int  iColumnSysName_PM = FindColSysName(aExcel);
      int  iColumnParaName_PM = FindColParaName(aExcel);
      int  iColumnParaType_PM = FindColParaType(aExcel);
      int  iColumnConfig_PM = FindColConfig(aExcel);
      int  iColumnParaUnit_PM =  FindColParaUnit(aExcel);
      int  iColumnParaValue_PM = FindColParaValue(aExcel);

      TStrings*  aSystemNames = aExcel->GetSheetCellsValue(iColumnSysName_PM,2,iRows);     //系统
      TStrings*  aParaStatus = aExcel->GetSheetCellsValue(iColumnParaType_PM,2,iRows);     //状态
      TStrings*  aParaNames = aExcel->GetSheetCellsValue(iColumnParaName_PM,2,iRows);      //名称
      TStrings*  aParaConfigs = aExcel->GetSheetCellsValue(iColumnConfig_PM,2,iRows);       //配置
      TStrings*  aUnits = aExcel->GetSheetCellsValue(iColumnParaUnit_PM,2,iRows);          //单位
      TStrings*  aParaValues = aExcel->GetSheetCellsValue(iColumnParaValue_PM,2,iRows);

      fMapElementItems->Clear();

      for(int i=0; i < aParaNames->Count; i++)
      {
          MapElementItems->NewParaMapElementItem(aSystemNames->Strings[i],
                                                aParaStatus->Strings[i],aParaNames->Strings[i],
                                                aParaValues->Strings[i],aUnits->Strings[i],
                                                aParaConfigs->Strings[i]);
      }

       delete aSystemNames;
       delete aParaNames;
       delete aParaStatus;
       delete aUnits;
       delete aParaConfigs;
       delete aParaValues;

    }
    __finally            //20151011
    {
       aExcel->QuitExcel();
    }

    if(aLV != NULL)
        MapElementItems->ToListView(aLV);
}

int MMapElement_ExcelImporter::FindColSysName(MExcelFun* aExcel)
{
    int  aCol = FindTitleCol(aExcel,"所属系统",1);
    if( aCol<=0 )
        throw Exception( "Excel文件格式不对！没有'所属系统'！" );
    return aCol;
}


int MMapElement_ExcelImporter::FindColParaType(MExcelFun* aExcel)
{
    int  aCol = FindTitleCol(aExcel,"参数状态",1);
    if( aCol<=0 )
        throw Exception( "Excel文件格式不对！没有'类型'！" );
    return aCol;
}

int  MMapElement_ExcelImporter::FindColParaName(MExcelFun* aExcel)
{
    int  aCol = FindTitleCol(aExcel,"参数名",1);
    if( aCol<=0 )
        throw Exception( "Excel文件格式不对！没有'参数名'！" );
    return aCol;
}

int  MMapElement_ExcelImporter::FindColParaValue(MExcelFun* aExcel)
{
    int  aCol = FindTitleCol(aExcel,"参数值",1);
    if( aCol<=0 )
        throw Exception( "Excel文件格式不对！没有'参数值'！" );
    return aCol;
}

int MMapElement_ExcelImporter::FindColParaUnit(MExcelFun* aExcel)
{
    int  aCol = FindTitleCol(aExcel,"单位英文",1);
    if( aCol<=0 )
        throw Exception( "Excel文件格式不对！没有'单位英文'！" );
    return aCol;
}

int MMapElement_ExcelImporter::FindColConfig(MExcelFun* aExcel)
{
    int  aCol = FindTitleCol(aExcel,"配置项",1);
    if( aCol<=0 )
        throw Exception( "Excel文件格式不对！没有'配置项'！" );
    return aCol;
}

bool MMapElement_ExcelImporter::IsNeededFile(MExcelFun* aExcel)
{
    if( FileExists(FileName) == false )
       throw Exception( "文件(" +FileName+ ")不存在!" );

    //测试,会抛出异常
    try
    {
        FindColParaName(aExcel);
        return true;
    }
    catch(...)
    {
        aExcel->QuitExcel();
        return false;
    }
}

*/


//------------------------------MDMSourceItem----------------------------------
MDMSourceItem::MDMSourceItem( MDMSourceItems* aItems)
{
    fItems = aItems;

    fFileName = "";

    fCLIPart = new MAMProject();
}

void MDMSourceItem::ToListBox(TListBox* aList)
{
}

//---------------------------------MDMSourceItems---------------------------------
MDMSourceItems::MDMSourceItems()
{
}

MDMSourceItem*   MDMSourceItems::NewNameItem(String aFileName)
{
     MDMSourceItem* aItem = new MDMSourceItem(this);
     aItem->FileName = aFileName;     //数据层

     Add(aItem);

     return aItem;
}

int  MDMSourceItems::IndexByName(String  aName)
{
     int  iIndex = -1;

     for(int i=0; i < Count; i++)
     {
         MDMSourceItem* aItem = (MDMSourceItem*)Items[i];

         if(IsEqualByCase(aItem->FileName,aName,true))
         {
             iIndex = i;
             break;
         }
     }
     return iIndex;
}

void  MDMSourceItems::ToListBox(TListBox* aList,bool bClear)
{
     if(aList == NULL)  return;

     if(bClear)
         aList->Items->Clear();

     for(int i=0; i < Count; i++)
     {
         MDMSourceItem* aItem = Items[i];
         aItem->ToListBox(aList);
     }
}





//--------------------------MDMSource-------------------------------------------
MDMSource::MDMSource()
{
    fItems = new MDMSourceItems();
}


//------------------------------------------------------------------------------
//清空ListBox
void  MDMSource::DeleteFileNames(TListBox* aList)
{
     if(aList == NULL || aList->Items == NULL)  return;

     for(int i=0; i < aList->Items->Count; i++)
     {
          DelStringsItemByObject(aList->Items,(void*)aList->Items->Objects[i]);
     }
}

void MDMSource::DeleteSelectedFileNameItem(TListBox* aList)
{
     if(aList == NULL)    return;

     MDMSourceItem*  aItem = GetSelectedDMSourceItem(aList);
     if(aItem == NULL)
     {
         throw Exception("请先选择所要删除的文件!!!");
     }

     DelStringsItemByObject(aList->Items,(void*)GetListBoxSelectedNodeData(aList));
}

void  MDMSource::MergeStepNamesAndShow(TListBox* aList,String aStepName,String aTitle,
                               String aFileName,String aRemark,bool isMaskMerge)
{
/*
     if(aList == NULL)
           return;

     LoadFileNamesFromListBox(aList);   //fItems
     if(isMaskMerge)  //合并
     {
          if(fItems->IndexByName(aStepName) < 0) //不存在
               fItems->NewNameItem(aStepName,aFileName,aTitle,aRemark);
     }
     else
          fItems->NewNameItem(aStepName,aFileName,aTitle,aRemark);

     aList->Items->Clear();
     fItems->ToListBox(aList);
*/
}


//----------------------MTreeNodes_LayerData-----------------------------------
MTreeNodes_LayerData::MTreeNodes_LayerData()
{
    fProject = NULL;
}

void MTreeNodes_LayerData::DoMovePart(double  aPartMoveX,double aPartMoveY)
{
   for(int i= 0; i < Count; i++)
   {
       MLayerDataTreeNode* aItem = Items[i];
       if(aItem->Type == "0")
             continue;

       aItem->DoMovePart(aPartMoveX,aPartMoveY);

       gError->WarnAdd1_Percent( "正在移动切片层数据", i ,Count );
   }
   gError->WarnAdd1("移动切片层数据完成");
}

void MTreeNodes_LayerData::DoScalePart(double aPartScaleX,double aPartScaleY)
{
   for(int i= 0; i < Count; i++)
   {
       MLayerDataTreeNode* aItem = Items[i];
       if(aItem->Type == "0")
             continue;

       aItem->DoScalePart(aPartScaleX,aPartScaleY);

       gError->WarnAdd1_Percent( "正在缩放切片层数据", i ,Count );
   }
   gError->WarnAdd1("缩放切片层数据完成");
}

void  MTreeNodes_LayerData::ToComboBox(TComboBox* aCBox)
{
    if(aCBox == NULL)  return;

    aCBox->Items->Clear();
    aCBox->Items->BeginUpdate();

    for(int i = 1; i < Count; i++)
    {
         MLayerDataTreeNode* aItem = Items[i];
         ObjectToComboBox(aCBox,(TObject*)aItem,aItem->Name);   //显示模块名
    }
    aCBox->Items->EndUpdate();
}

void  MTreeNodes_LayerData::NewLayerDataItem(String aText)
{
    TStringList* aListGroup = NULL;

     try
     {
         aListGroup = splitToStrings(aText,",");  //拆分

         String  aType = Get_ListItemStr_ByName( aListGroup, "Type", "=", "unKnown");   //未知类型
         String  aId = Get_ListItemStr_ByName( aListGroup, "NodeId", "=", "unKnown" );
         String  aName = Get_ListItemStr_ByName( aListGroup, "Name", "=", "unKnown");   //NodeName
         String  aParentName = Get_ListItemStr_ByName( aListGroup, "PARENT", "=", "unKnown");
         String  aImageIndex = Get_ListItemStr_ByName(aListGroup, "ImageIndex", "=", "unKnown");
         String  aCLIFile = Get_ListItemStr_ByName(aListGroup, "CLIFileName", "=", "");
         String  aDXFFile = Get_ListItemStr_ByName(aListGroup, "DXFFileName", "=", "");

         NewLayerData_AT(aId, aName, aType,aParentName,aImageIndex,aCLIFile,aDXFFile);   //添加到集合中

         delete aListGroup;
     }
     catch( Exception& e)
     {
        delete aListGroup;
        gError->Warn( "MDataElement_Objects::NewModeNodeItem出错!" + e.Message );
     }
}

bool MTreeNodes_LayerData::IsEqualByName(String aName,MObject* aEntity,bool IsUppercase)
{
     return IsEqualByCase( aName, ((MLayerDataTreeNode*)aEntity)->LayerDataID, IsUppercase  );
}


MLayerDataTreeNode*  MTreeNodes_LayerData::NewLayerData_AT(String aID,String aName, String aType,
                              String aParentName,String aImageIndex,String aCliFile,String aDXFFile)   //在末尾添加,自动加入集合中
{
    MLayerDataTreeNode*  aItem = NewLayerData_MT(aID,aName,aType,aParentName,aImageIndex,aCliFile,aDXFFile);
    Add(aItem);     //加入集合

    return aItem;
}

//-----------------------------------与二进制文件读取有关-----------------------
MLayerDataTreeNode*  MTreeNodes_LayerData::NewLayerData()
{
    MLayerDataTreeNode*  aItem = new MLayerDataTreeNode(this);
    Add(aItem);     //加入集合

    return aItem;
}

MLayerDataTreeNode*  MTreeNodes_LayerData::NewLayerData_MT(String aID,String aName, String aType,
                              String aParentName,String aImageIndex,String aCLiFile,String aDXFFile)   //手动方式，手动加入集合中
{
    if(aID == "unKnown" && aName == "unKnown" && aType == "unKnown")
            throw Exception("未知的DataElement类型");

    MLayerDataTreeNode*  aItem = new MLayerDataTreeNode(this);

    aItem->LayerDataID = aID;
    aItem->Name = aName;
    aItem->NodeName = aName;
    aItem->Type = aType;
    aItem->ParentName = aParentName;
    aItem->ImageIndex = StrToIntDef(aImageIndex,0);
    aItem->CLIFileName = aCLiFile;
    aItem->DXFFileName = aDXFFile;

    return aItem;
}

void MTreeNodes_LayerData::ToTreeView(TTreeView* aTree,bool  bContructTree)
{
    if(aTree == NULL || aTree->Items == NULL)  return;

    //初始化
    aTree->Items->Clear();
    aTree->ReadOnly = true;  //只读方式
    aTree->HideSelection = false;

    aTree->Items->BeginUpdate();

    //采用先添加再调整方式
    for(int i = 0; i < Count; i++)
     {
         MLayerDataTreeNode* aItem = Items[i];

         TTreeNode* aNewNode = aTree->Items->Add(NULL,aItem->NodeName); //caption
         aNewNode->Data = (void*)aItem;
         aNewNode->ImageIndex = aItem->ImageIndex;
         aNewNode->SelectedIndex = aItem->ImageIndex;
         aItem->TreeNode = aNewNode;  //可以获取层次，及节点LevelIndex;

         if(bContructTree)
         {
             if(aItem->Parent != NULL)
             {
                 TTreeNode* aNodePar = FindTreeViewNodeByData(aTree,(void*)aItem->Parent);
                 if(aNodePar != NULL)
                     aNewNode->MoveTo(aNodePar,naAddChild);
             }
         }

         gError->WarnAdd1_Percent("正在生成树节点",i,Count);
     }

     aTree->Items->EndUpdate();
     aTree->FullExpand(); //展开
}

TStrings* MTreeNodes_LayerData::SaveCatalogStruct()
{
    TStrings*  aList = new TStringList;

    for(int i=0; i < Count; i++)
    {
        MLayerDataTreeNode*  aItem = Items[i];
        aList->Add(aItem->SaveCatalogStruct());

        gError->WarnAdd1_Percent("正在保存层数据",i,Count);
    }
    gError->WarnAdd1("层数据保存完成!!");

    return aList;
}


TStrings*  MTreeNodes_LayerData::SaveCatalogDatas()
{
    TStrings*  aList = new TStringList;

    for(int i=1; i < Count; i++)
    {
        MLayerDataTreeNode*  aItem = Items[i];

        gError->Warn1("正在保存数据:" + IntToStr(i) + "/" + IntToStr(Count));

        //aItem->ProcessCliData(aItem->CliDataStrings);
        //aItem->CliDataStrings->Clear();

        aList->Add(aItem->SaveCatalogData());
    }

    return aList;
}

String  MTreeNodes_LayerData::readMaxID()
{
     int aMaxID = gIniFile->ReadInteger("DataModule","DataModuleID",-1);
     if(aMaxID == -1)   //没有,要写
     {
         aMaxID = 0;
         gIniFile->WriteInteger("DataModule","DataModuleID",aMaxID);
     }

     return IntToStr(aMaxID);
}

void    MTreeNodes_LayerData::writeMaxID(String aID)
{
     int aMaxID = StrToInt(aID);
     gIniFile->WriteString("DataModule","DataModuleID",aMaxID);
}

double MTreeNodes_LayerData::readMinX()
{
     double aMin = MAXFLOAT;

     for(int i=0; i < Count; i++)
     {
         MLayerDataTreeNode* aItem = Items[i];
         if(aMin > aItem->MinX)
               aMin = aItem->MinX;
     }

     return aMin;
}

double MTreeNodes_LayerData::readMaxX()
{
     double aMax = -MAXFLOAT;

     for(int i=0; i < Count; i++)
     {
         MLayerDataTreeNode* aItem = Items[i];
         if(aMax < aItem->MaxX)
               aMax = aItem->MaxX;
     }

     return aMax;
}

double MTreeNodes_LayerData::readMinY()
{
    double aMin = MAXFLOAT;

     for(int i=0; i < Count; i++)
     {
         MLayerDataTreeNode* aItem = Items[i];
         if(aMin > aItem->MinY)
               aMin = aItem->MinY;
     }

     return aMin;
}

double MTreeNodes_LayerData::readMaxY()
{
     double aMax = -MAXFLOAT;

     for(int i=0; i < Count; i++)
     {
         MLayerDataTreeNode* aItem = Items[i];
         if(aMax < aItem->MaxY)
               aMax = aItem->MaxY;
     }

     return aMax;
}

double MTreeNodes_LayerData::readMaxZ()
{
     MLayerDataTreeNode* aItem = LastItem();
     return StrToFloat(aItem->AbsoluteHeight);
}

//-------------------------OpenGL-----------------------------------------------
CGLView::CGLView()
{
    m_hWnd = NULL;
    m_hDC = NULL;
    m_hGLRC = NULL;

    fWindowRange = 150;
    fWorkArea = 125;
    fCurDrawLayer = NULL;
}

CGLView::~CGLView()
{
    DisableOpenGL();
}

//重要函数
bool CGLView::SetupGLContext()
{
    if(m_hWnd == NULL)   return false;

    //1、获得DC
    m_hDC = ::GetDC(m_hWnd);
    //2、设置最佳的像素格式
    SetPixelFormat(m_hDC);
    m_hGLRC = ::wglCreateContext(m_hDC);
    if (m_hGLRC)
    {
        // try to make it the thread's current rendering context
        if(false == wglMakeCurrent(m_hDC, m_hGLRC))
        {
            MessageBox(m_hWnd, _T("Failed wglMakeCurrent"), _T("Error!"), MB_ICONERROR);
            return false;
        }
    }
    else
    {
        ShowMessage(":-)~ m_hGLRC == NULL");
        return false;
    }

    wglMakeCurrent(m_hDC, m_hGLRC);
    glShadeModel(GL_SMOOTH);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);					// Black Background
    glClearDepth(1.0f);							// Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);						// Enables Depth Testing
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);			// Really Nice Perspective Calculations


    return true;
}

//OK
int CGLView::SetPixelFormat(HDC hdc)
{
    PIXELFORMATDESCRIPTOR pfd = {
              sizeof(PIXELFORMATDESCRIPTOR),    // size of this pfd
              1,                                // version number
              PFD_DRAW_TO_WINDOW |              // support window
              PFD_SUPPORT_OPENGL |              // support OpenGL
              PFD_DOUBLEBUFFER,                 // double buffered
              PFD_TYPE_RGBA,                    // RGBA type
              24,                               // 24-bit color depth
              0, 0, 0, 0, 0, 0,                 // color bits ignored
              0,                                // no alpha buffer
              0,                                // shift bit ignored
              0,                                // no accumulation buffer
              0, 0, 0, 0,                       // accum bits ignored
              32,                               // 32-bit z-buffer
              0,                                // no stencil buffer
              0,                                // no auxiliary buffer
              PFD_MAIN_PLANE,                   // main layer
              0,                                // reserved
              0, 0, 0                           // layer masks ignored
      };

      int  iPixelFormat;
      // get the device context's best, available pixel format match
      if((iPixelFormat = ChoosePixelFormat(hdc, &pfd)) == 0)
      {
              MessageBox(m_hWnd, _T("ChoosePixelFormat Failed"), NULL, MB_ICONERROR);
              return 0;
      }

      // make that match the device context's current pixel format
      if(::SetPixelFormat(hdc, iPixelFormat, &pfd) == FALSE)
      {
              MessageBox(m_hWnd, _T("SetPixelFormat Failed"), NULL, MB_ICONERROR);
              return 0;
      }

      return 1;
}

//------------------------------------------------------------------------------
void CGLView::Resize(unsigned short iWidth, unsigned short iHeight)
{
   if(iHeight == 0)   iHeight = 1;

    double aspect = 1;//(double)iWidth/(double)iHeight;

    //1、设置视口
    glViewport(0, 0, iWidth, iHeight);

    //2、投影变换
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();

    //gluPerspective(45.0f,(GLfloat)iWidth/(GLfloat)iHeight,0.1f,100.0f);

    GLfloat nRange = WindowRange;
    if (iWidth <= iHeight)
          ::glOrtho (-nRange, nRange, -aspect* nRange,aspect* nRange, -1.0f, 1.0f);   //-10,10,-10,10,0.1,100f
    else
          ::glOrtho (-aspect*nRange,nRange*aspect, -nRange,nRange,  -1.0f, 1.0f);

    //3、模型变换
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();
}

//---------------------------------------------------------------------------
void CGLView::RenderGLScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    DrawObjects();

    glFlush();
    SwapBuffers(m_hDC);
}


//---------------------------------------------------------------------------
//用于绘制显示列表
void CGLView::DrawObjects()
{
    //绘制边界
    glBegin(GL_LINE_LOOP);						// Draw A Quad
          glColor3f(1.0f,0.0f,0.0f);			// Set The Color To Red
          glVertex3f( WorkArea,WorkArea, 0.0f);			// Top Right Of The Quad (Front)
          glVertex3f(-1.0*WorkArea, WorkArea, 0.0f);			// Top Left Of The Quad (Front)
          glVertex3f(-1.0*WorkArea,-1.0*WorkArea, 0.0f);			// Bottom Left Of The Quad (Front)
          glVertex3f( WorkArea,-1.0*WorkArea, 0.0f);			// Bottom Right Of The Quad (Front)
    glEnd();

    //绘制刻度线
    int    xIndex[] = {-12,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1,0,1,2,3,4,5,6,7,8,9,10,11,12};
    float  xWidth = 10.0;
    float  yBegin = -1.0*WorkArea;
    float  yEnd = yBegin + 2;
    float  xBegin = WorkArea - 2;
    float  xEnd = xBegin + 2;

    int iSize = (int)(WorkArea/10);

    //X轴
    for(int i=0; i < iSize*2; i++)
    {
        glBegin(GL_LINES);
        glColor3f(0.0f,1.0f,1.0f);

        glVertex3f(xIndex[i]*xWidth,yBegin, 0.0f);
        glVertex3f(xIndex[i]*xWidth,yEnd, 0.0f);
        glEnd();
    }

    //Y轴
    for(int i=0; i < iSize*2; i++)
    {
        glBegin(GL_LINES);
        glColor3f(0.0f,1.0f,1.0f);

        glVertex3f(xBegin,xIndex[i]*xWidth, 0.0f);
        glVertex3f(xEnd,xIndex[i]*xWidth, 0.0f);
        glEnd();
    }   


    //绘制中心线
    glBegin(GL_LINES);
         glColor3f(0.0f,0.0f,1.0f);			// Set The Color To 黄
         glVertex3f( 0.0f,-1.0f*WorkArea+3, 0.0f);			// Top Right Of The Quad (Front)
         glVertex3f(0.0f,WorkArea-3, 0.0f);			// Top Left Of The Quad (Front)
         glVertex3f(-1.0*WorkArea+3,0.0, 0.0f);			// Bottom Left Of The Quad (Front)
         glVertex3f( WorkArea-3,0.0f, 0.0f);			// Bottom Right Of The Quad (Front)
    glEnd();


    //绘制
    if(CurDrawLayer != NULL)
    {
       if(CurDrawLayer->Type == "0")
       {
           CurDrawLayer->DrawInOpenGL();
       }
       else
       {
           CurDrawLayer->PolyLines->DrawInOpenGL();
           CurDrawLayer->HatchLines->DrawInOpenGL();
       }
    }
}

void CGLView::DisableOpenGL()
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(m_hGLRC);
    ReleaseDC(m_hWnd,m_hDC);
}

//----------------------------MPartDatas_LayerDataTreeNode--------------------------
MPartDatas_LayerDataTreeNode::MPartDatas_LayerDataTreeNode()
{
}

void  MPartDatas_LayerDataTreeNode::Dispose()
{
    for(int i=0; i < Count; i++)
    {
       MPartData_LayerDataTreeNode* aItem = Items[i];
       aItem->Dispose();
    }

    Clear();
}

MPartData_LayerDataTreeNode*  MPartDatas_LayerDataTreeNode::NewPartData_LayerDataTreeNode()
{
     MPartData_LayerDataTreeNode* aItem = new MPartData_LayerDataTreeNode(this);

     Add(aItem);

     return aItem;
}

void  MPartDatas_LayerDataTreeNode::ToListView(TListView* aList)
{
    if( aList==NULL )   return;

    aList->ReadOnly = true;
    ListView_InitForGrid(aList);
    ListView_AddTitles( aList, "功率[W];速度[mm/s]", "80;0", ";" );

    for( int i=0; i<Count; i++ )
    {
      MPartData_LayerDataTreeNode* aItem = Items[i];
      if( aItem==NULL ) continue;

      aItem->ToListView(aList);
    }
    ListView_Refresh(aList);
}

//-------------------------MPartData_LayerDataTreeNode------------------------------
MPartData_LayerDataTreeNode::MPartData_LayerDataTreeNode(MPartDatas_LayerDataTreeNode*  aItems)
{
      fPolyLines = new MPolyLines();             //有很多polyline
      fHatchLines = new MHatchLines();           //有很多hatchLine

      fLaserPower = 0.0;     //代表该打印文件的激光功率，激光速度，从而可以得到Pen
      fLaserSpeed = 0.0;
      bFinishPrint = false;  //没有打印

      fItems = aItems;
}

void MPartData_LayerDataTreeNode::Dispose()
{
     fPolyLines->Dispose();
     delete fPolyLines;

     fHatchLines->Dispose();
     delete fHatchLines;
}


void MPartData_LayerDataTreeNode::ToListView( TListView* aList )
{
  TListItem* aItem = ListView_FindByData( aList, (void*)this );
  if( aItem == NULL )
    ListView_AddItems( aList, FullName(), "@@", (void*)this );
  else
    ListView_SetItems( aItem, FullName(), "@@", (void*)this );
}

String  MPartData_LayerDataTreeNode::FullName()
{
    return  FloatToStr(fLaserPower)  + "@@" + FloatToStr(fLaserSpeed);
}


//用于排版的Part的集合
//-------------------------MPartProjects----------------------------------------
MPartProjects::MPartProjects()
{
}

MPartProject* MPartProjects::NewPartProject()
{
    MPartProject*  aItem = new MPartProject(this);

    Add(aItem);

    return aItem;
}

void MPartProjects::LoadPartProjectsFromFileStrings(TStrings* aFiles)
{
    if(aFiles->Count == 0)  return;

    for(int i=0; i < aFiles->Count; i++)
    {
        String aFileName = aFiles->Strings[i];   //取出一个文件

        MPartProject* aItem = NewPartProject();      //创建一个工程
        aItem->LoadGYInfoFromFile(aFileName);
    }
}


void MPartProjects::AddToListBox(TListBox*  aListBox,bool bClear)
{
     if(aListBox == NULL)  return;

    if(bClear)
         aListBox->Items->Clear();

     for(int i=0; i < Count; i++)
     {
         MPartProject* aItem = Items[i];
         aItem->ToListBox(aListBox);
     }
}

//------------------------------MPartProject------------------------------------
MPartProject::MPartProject(MPartProjects* aItems)
{
     fItems = aItems;
     fLaserPens = new MLaserPens();

     fProjectName = "";
     fLayers = 0;
     fUnit = 1.0;
     fPartID = -1;
     fMainItems = new MTreeNodes_LayerData();
     fLayersDataHolder = NULL;

     fLaserPen = NULL;
}

MLayerDataTreeNode* MPartProject::FindLayerDataTreeNodeByHeight(double aAbsoluteHeight)
{
    MLayerDataTreeNode*  aItem = NULL;

    for(int i = 0; i < MainItems->Count; i++)  //层
    {
         aItem = MainItems->Items[i];   //第一个节点
         if(aItem->Type == "0")
              continue;

         if(StrToFloat(aItem->AbsoluteHeight) - aAbsoluteHeight > 0.001)
              return NULL;

         if(fabs(StrToFloat(aItem->AbsoluteHeight) - aAbsoluteHeight) < 0.001)
             return aItem;
    }
    return aItem;
}

void  MPartProject::DoMovePart(double  aPartMoveX,double aPartMoveY)
{
    if(MainItems->Count <= 1)
          throw Exception("请先加载模型");

    MainItems->DoMovePart(aPartMoveX,aPartMoveY);   //实现数据的移动
}

//从文件加载层信息
void  MPartProject::LoadCLiLayerInfoFromStrings(TStrings* aStrings)
{
    if(aStrings == NULL || aStrings->Count ==0)  return;
    if(fLayers == 0)   throw Exception("CLI 文件错误");

    int iLayerNo = 1;
    int aMaxID = 1;

    bool bBegin = false;
    bool bEnd = false;
    String aAbsoluteHeight;
    String  aKey,aValue;
    int  iBgIndex,iEndIndex;

    String  aLayerFileName;
    String  aLayerEdgeFileName;
    String  aLayerPath;
    String  aSingleCLiFileName;
    String  aSingleCLiPath;

    for(int i=0; i <  aStrings->Count; i++)
    {
        String  aLine = aStrings->Strings[i];
        if(HasSubString( aLine,"$$LAYER/") == false)  continue;

        //获取该层的绝对高度
        if(bBegin == false)
        {
            SplitStrTo2Str(aLine,"/",aKey,aValue,true);
            aAbsoluteHeight = aValue;
            iBgIndex = i;
            bBegin = true;

            if(iLayerNo == fLayers) //最后一层
            {
                bEnd = true;
                iEndIndex = aStrings->Count-2;
            }
        }
        else
        {
            bEnd = true;
            iEndIndex = i-1;
        }

        if(bBegin && bEnd) //首尾都找到了
        {
            //处理
            bBegin = false;
            bEnd = false;

            MLayerDataTreeNode* aRoot = fMainItems->Items[0];
            String aParentName = "";
            if(aRoot != NULL)  //没有根节点
                  aParentName = aRoot->LayerDataID;

            String  aName = "第 "+ IntToStr(iLayerNo) + " 层轮廓";
            String  aNoPathDXFFile = "Layer_"+IntToStr(iLayerNo) +".dxf";
            String  aNoPathCLIFile = "Cli_"+IntToStr(iLayerNo) +".dat";

            MLayerDataTreeNode* aItem = fMainItems->NewLayerData_MT(aMaxID,aName,"1",
                             aParentName,"1",aNoPathCLIFile,aNoPathDXFFile);
            aItem->AbsoluteHeight = aAbsoluteHeight;
            aItem->LayerNo = iLayerNo;

            aMaxID++;

            //加载数据
            TStringList*  aSubFile = new TStringList;
            CopyStrings(aSubFile,aStrings,iBgIndex,iEndIndex);
            aItem->ProcessCliData(aSubFile);
            delete aSubFile;


            fMainItems->Add(aItem);

            i = iEndIndex;
            iLayerNo++;  //层号
            gError->Warn1("正在加载节点:" + IntToStr(fMainItems->Count) + "/" + IntToStr(fLayers));
        }
    }

}


//-----------------用于排版-----------------------------------------------------
void  MPartProject::LoadGYInfoFromFile(String aFileName)
{
    fProjectName = ExtractFileName(aFileName);

    TStringList* aNodeItems = CheckAndLoadFromFile(aFileName);

    //get head
    LoadCLiHeaderInfoFromStrings(aNodeItems);   //获得单位和层数
    LoadCLiLayerInfoFromStrings(aNodeItems);
    delete aNodeItems;
}

void MPartProject::LoadCLiHeaderInfoFromStrings(TStrings* aStrings)
{
   if(aStrings == NULL || aStrings->Count ==0)  return;

   for(int i=0; i < aStrings->Count; i++)
   {
      String  aLine = aStrings->Strings[i];
      String  aKey,aValue;
      if( HasSubString(aLine,"$$HEADEREND"))  //结束
      {
          break;
      }
      else if( HasSubString(aLine,"$$UNITS")) //单位 mm
      {
          SplitStrTo2Str(aLine,"/",aKey,aValue,true);
          fUnit = StrToFloat(aValue);
      }
      else if(HasSubString( aLine,"$$LAYERS"))  //层
      {
          SplitStrTo2Str(aLine,"/",aKey,aValue,true);
          fLayers = StrToInt(aValue);
      }
      else if(HasSubString( aLine,"$$LABEL"))  //PartID
      {
          SplitStrTo2Str(aLine,"/",aKey,aValue,true);
          fPartID = StrToInt(aValue);
      }
   }
}

void  MPartProject::ToListBox(TListBox* aList)
{
    ObjectToListBox(aList,(TObject*)this,ProjectName);   //显示模块名
}

//拆分，合成
//bool bSaveCtStruct: 是否保存目录结构
void  MPartProject::LoadLayerDatasFromCLiFile(String aCliFile)
{
    if(fMainItems->Count == 0)  return;
    if(fMainItems->Count > 1)
    {
        //Clear, 确保只有一个
        for(int i=1; i < fMainItems->Count;)
        {
           //先清资源，然后再删除
           MLayerDataTreeNode*  aItem = fMainItems->Items[i];
           aItem->Dispose();  //释放资源

           fMainItems->Delete(i);
        }
    }

    TStrings*  aFileStrings = new TStringList;
    aFileStrings->LoadFromFile(aCliFile);

    //get head
    LoadCLiHeaderInfoFromStrings(aFileStrings);   //获得单位和层数
    LoadCLiLayerInfoFromStrings(aFileStrings);
    delete aFileStrings;

    fMainItems->ToTreeView(fLayersDataHolder,false);
}

double   MPartProject::readMinX()
{
    return fMainItems->MinX;
}

double   MPartProject::readMaxX()
{
    return fMainItems->MaxX;
}

double   MPartProject::readMinY()
{
    return fMainItems->MinY;
}

double   MPartProject::readMaxY()
{
    return fMainItems->MaxY;
}




