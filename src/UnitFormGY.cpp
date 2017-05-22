//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitFormGY.h"
#include "UnitTool_ClassExtend.h"
#include "UnitTestInstance.h"
#include "math.h"
#include "UnitFormLaserSetting.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormGYDesign *FormGYDesign;

//---------------------------------------------------------------------------
__fastcall TFormGYDesign::TFormGYDesign(TComponent* Owner)
        : TForm(Owner)
{
    Project = new MPartProject;
    Project->LayersDataHolder = TreeView1;

    fProjects = new MPartProjects;

    fCurrentOpenCliFile = "";
    fCurrTreeNode = NULL;
    CurrentProject = NULL;
}
//---------------------------------------------------------------------------
void  TFormGYDesign::Init()
{
    gError->StatusBar = StatusBar1;
}
//----------------------------参数----------------------------------------------
int  TFormGYDesign::readInstanceType()
{
    return ComboBox1->ItemIndex;
}

void TFormGYDesign::writeInstanceType(int aType)
{
    ComboBox1->ItemIndex = aType;
}
//------------------------------------------------------------------------------
int TFormGYDesign::readAngle()
{
     try
     {
         float  aValue = StrToFloat(CBoxAngle->Text);
         return Floor(aValue);
     }
     catch(Exception& e)
     {
     }

     throw Exception("输入的角度格式有误!");
}

void  TFormGYDesign::writeAngle(int aAngle)
{
    CBoxAngle->Text = IntToStr(aAngle);
}


double TFormGYDesign::readLimitedDis()
{
     return StrToFloat(EditLimitedDis->Text);
}

void TFormGYDesign::writeLimitedDis(double aLimitedDis)
{
    EditLimitedDis->Text = FloatToStr(aLimitedDis);
}

int TFormGYDesign::readLimitedNum()
{
    return StrToInt(EditLimitedNum->Text);
}

void TFormGYDesign::writeLimitedNum(int aLimitedNum)
{
    EditLimitedNum->Text = IntToStr(aLimitedNum);
}

double TFormGYDesign::readOffsetDis()
{
     return StrToFloat(EditLinesOffset->Text);
}

void TFormGYDesign::writeOffsetDis(double aOffsetDis)
{
     EditLinesOffset->Text = FloatToStr(aOffsetDis);
}

double TFormGYDesign::readDistanceLines()
{
     return StrToFloat(EditLinesDis->Text);
}

void TFormGYDesign::writeDistanceLines(double aDistanceLines)
{
     EditLinesDis->Text = FloatToStr(aDistanceLines);
}

//---------------------------------------------------------------------------
void  TFormGYDesign::DrawGridLine(int aViewPortX,int aViewPortY,int aWidth,int aHeight)
{
     MPolyLines*  aPaths = new MPolyLines();

     MPolyLine*  aItem = aPaths->NewPolyLine();
     aItem->Points->New2DPoint(aWidth/2.0*(-1),aHeight/2.0*(-1));
     aItem->Points->New2DPoint(aWidth/2.0,aHeight/2.0*(-1));
     aItem->Points->New2DPoint(aWidth/2.0,aHeight/2.0);
     aItem->Points->New2DPoint(aWidth/2.0*(-1),aHeight/2.0);
     aItem->Points->New2DPoint(aWidth/2.0*(-1),aHeight/2.0*(-1));

     MHatchLines* aHatchLines = new MHatchLines();

     int  aRowNum = aWidth / 10 - 1;
     int  aColNum = aHeight / 10 - 1;

     //行填充
     for(int i=0; i < aRowNum ; i++)
     {
         int  aSX = aWidth/2.0*(-1);
         int  aSY = aHeight/2.0 - 10*(i+1);
         int  aEX = aWidth/2.0;
         int  aEY = aSY;

         aHatchLines->NewHatchLine(aSX,aSY,aEX,aEY);
     }

     //列填充
     for(int i=0; i < aColNum ; i++)
     {
         int  aSX = aWidth/2.0 - 10*(i+1);
         int  aSY = aHeight/2.0*(-1);
         int  aEX = aSX;
         int  aEY = aHeight/2.0;

         aHatchLines->NewHatchLine(aSX,aSY,aEX,aEY);
     }

     ShowImageInfo(Image1,aViewPortX,aViewPortY,aPaths,aHatchLines,1);
}


void __fastcall TFormGYDesign::OpenFileClick(TObject *Sender)
{
    //1.1 获取文件
    String  aOutDir = ApplicationPath() + "\\TestModel";

    //加载模型到List中
    OpenDialog1->Title = "指定几何切片文件";
    OpenDialog1->Filter = "几何切片文件(*.cli)|*.cli";
    OpenDialog1->InitialDir = aOutDir;
    if(OpenDialog1->Execute() != mrOk)   return;

    String  aFileName = OpenDialog1->FileName;
    fCurrentOpenCliFile = aFileName;

    //2、加载到TreeView中
    //2.1 创建根节点
    TreeView1->Items->Clear();
    Project->MainItems->Clear();
    fCurrTreeNode= NULL;
    Image1->Canvas->FillRect(Image1->Canvas->ClipRect);  //清Image;

    InsertCatalogNode(NULL, ExtractFileName(aFileName),"0");  //根节点

    gError->Warn1("正在加载切片数据");
    Project->LoadLayerDatasFromCLiFile(aFileName);   //加载到树上了
    gError->Warn1("加载切片数据--------完成");

    //层厚,层数,类型
    if(Project->MainItems->Count > 1)
          Edit_LayerThick->Text = Project->MainItems->Items[1]->AbsoluteHeight;
    else
          Edit_LayerThick->Text = "";
    Edit1->Text =  IntToStr(TreeView1->Items->Count - 1);

    ComboBox1->ItemIndex = Project->PartID;
}

//---------------------------------------------------------------------------
//插入目录节点
MLayerDataTreeNode*  TFormGYDesign::InsertCatalogNode(MLayerDataTreeNode*  aParentDM,
                                          String aNodeName,String aType)
{
    MTreeNodes_LayerData*  aMainItems = Project->MainItems;
    //申请一个ID
    int aMaxID = StrToInt(aMainItems->MaxID);
    aMainItems->MaxID = IntToStr(aMaxID + 1);

    MLayerDataTreeNode* aItem = aMainItems->NewLayerData_AT(IntToStr(aMaxID),
                      aNodeName,aType,"",0,"","");
    //树
    TTreeView*  aTree = TreeView1;
    if(aParentDM == NULL) //根节点
    {
         TTreeNode* aNewNode = aTree->Items->Add(NULL,aItem->NodeName);
         aNewNode->Data = (void*)aItem;
         aNewNode->ImageIndex = 0;
         aNewNode->SelectedIndex = 0;
         aItem->TreeNode = aNewNode;
         aItem->ParentName = "";
    }
    else //子节点
    {
        if(aParentDM->TreeNode == NULL)
              throw Exception("aParentDM->TreeNode == NULL");
        TTreeNode*  aNewNode = aTree->Items->AddChild(aParentDM->TreeNode,aItem->NodeName);
        aNewNode->Data = (void*)aItem;
        aItem->TreeNode = aNewNode;
        aNewNode->ImageIndex = 1;
        aNewNode->SelectedIndex = 1;

        if(aParentDM->TreeNode->Data != NULL)
        {
            MLayerDataTreeNode* aData = (MLayerDataTreeNode*)(aParentDM->TreeNode->Data);
            aItem->ParentName = aData->LayerDataID;
        }
    }
    aTree->FullExpand();
    return aItem;
}

//生成工艺切片文件
void __fastcall TFormGYDesign::BitBtn5Click(TObject *Sender)
{
    if(TreeView1->Items->Count < 2)
           throw Exception("请先打开轮廓文件");

    OutCliFileToFile(StrToInt(Edit1->Text));

    DoClickTreeNode(GetSelectedLayerDataItem(TreeView1));
}

//---------------------------------------------------------------------------
String  TFormGYDesign::GetDefaultGYName(int  iShapeType)
{
    String  aDefaultFileName = "";
    //2、CLI 主体结构
    if(iShapeType == 0)  //矩形
    {
        aDefaultFileName = "GY_GeoRectangle";
    }
    else if(iShapeType == 1)  //正三角
    {
        aDefaultFileName = "GY_GeoTriangle";
    }
    else if(iShapeType == 2)  //圆形
    {
        aDefaultFileName = "GY_GeoCircle";
    }
    else if(iShapeType == 3)  //工件
    {
        aDefaultFileName = "GY_GeoPartI";
    }
    else if(iShapeType == 4)  //4X4
    {
        aDefaultFileName = "GY_Geo4X4Part";
    }
    return aDefaultFileName;
}


void  TFormGYDesign::OutCliFileToFile(int nLayerNum)
{
     String  aOutDir = ApplicationPath() + "\\TestModel";

     TStringList*  aCLIFile = new TStringList;

     //文件头
     GetCLIFileHeader(aCLIFile,nLayerNum,Project->PartID);     //文件头,层数

     if(Angle == 0 || Angle == 90) //零度或90度方式
     {
         int  aAngle= Angle;
         for(int i=0; i < nLayerNum; i++)
         {
              //加载路径
              MPolyLines*  fPaths = Project->MainItems->Items[i+1]->PolyLines;
              LoadModelPaths(fPaths);  //创建偏置路径，创建填充路径

              MPolyLines*  aVirtualEdges = GetScanEdges(fPaths);  //获得填充路径

              MHatchLines* fHatchLines = Project->MainItems->Items[i+1]->HatchLines;
              CalculateHatchLines(aVirtualEdges,aAngle,fHatchLines);

              OutGYGeometryToFile(aCLIFile,i+1,fPaths,fHatchLines);   //输出一层

              aAngle += 90;            //改变填充角度
              aAngle = aAngle%180;
         }

     }
     else  //非正交方式
     {
         int  Angle = 13;
         for(int i=0; i < nLayerNum; i++) //层数
         {
             //加载路径
             MPolyLines*  fPaths = Project->MainItems->Items[i+1]->PolyLines;
             LoadModelPaths(fPaths);  //创建偏置路径，创建填充路径

             MPolyLines*  aVirtualEdges = GetScanEdges(fPaths);  //获得填充路径

             MHatchLines* fHatchLines = Project->MainItems->Items[i+1]->HatchLines;
             CalculateHatchLines(aVirtualEdges,Angle,fHatchLines);

             OutGYGeometryToFile(aCLIFile,i+1,fPaths,fHatchLines);   //输出一层

             Angle += 13;            //改变填充角度
             Angle = Angle%90;
         }
     }

    OutCLITrailToFile(aCLIFile);

         //4、保存
    SaveDialog1->InitialDir = aOutDir;
    SaveDialog1->DefaultExt = "cli";
    SaveDialog1->Filter = "工艺切片文件(*.cli)|*.cli";
    SaveDialog1->FileName = GetDefaultGYName(Project->PartID);
    if(SaveDialog1->Execute() == mrOk)
    {
        String  aFileName = SaveDialog1->FileName;
        aCLIFile->SaveToFile(aFileName);
        ShowMessage("["+ComboBox1->Text + "]切片工艺几何轮廓数据完成!");
    }

    delete aCLIFile;
}

void  TFormGYDesign::OutGYGeometryToFile(TStringList* aFile,int aLayerNo,
                     MPolyLines*  fPaths,MHatchLines* fHatchLines,bool bHatchLine_Pre)
{
     //2、输出每层信息
    String  aStr;

    aStr.sprintf("$$LAYER/%.3f ",LayerThick*aLayerNo);
    aFile->Add(aStr);

    if(bHatchLine_Pre) //先填充线
    {
        fHatchLines->OutPutContours2CLI(aFile);
        fPaths->OutPutContours2CLI(aFile);
    }
    else
    {
        fPaths->OutPutContours2CLI(aFile);
        fHatchLines->OutPutContours2CLI(aFile);
    }
}

double TFormGYDesign::readLayerThick()
{
     return StrToFloat(Edit_LayerThick->Text);
}

void   TFormGYDesign::writeLayerThick(double aLayerThick)
{
     Edit_LayerThick->Text = FloatToStr(aLayerThick);
}

MPolyLines*  TFormGYDesign::GetScanEdges(MPolyLines*  fPaths)
{
    if(fPaths->Count == 0)  return NULL;

    MPolyLines*  aPaths = new MPolyLines();
    for(int i=0; i < fPaths->Count; i++)
    {
        MPolyLine* aItem = fPaths->Items[i];
        if(aItem->PathType == 2)
        {
            aPaths->Add(aItem);
        }
    }

    return aPaths;
}


//aPath: [in] 输入的路径
//aPaths [out] 输出的路径
//aNum: 边界个数
//aLimitedDis: 边界之间的距离，
void TFormGYDesign::PathOffset(const TPath& aPath,TPaths& aPaths,int aNum,double aLimitedDis)
{
    if(aNum < 2) return;

    aPaths.set_length(aNum-1);
    TClipperOffset*  co = new TClipperOffset(0.1,0.25);
    TPaths solution;
    for(int i=1; i < aNum; i++)
    {
        co->AddPath(aPath,jtMiter,etClosedPolygon);
        co->Execute(solution, aLimitedDis);     //向内部收缩

        aPaths[i-1] = solution[0];
    }
}


void  TFormGYDesign::LoadModelPaths(MPolyLines*  fPaths)
{
    if(fPaths->Count == 0) return;

    int iNum = fPaths->Count;
    if(iNum == 1) //只有1个轮廓线
    {
        MPolyLine* aItem = fPaths->Items[0];                                    //其中的一个轮廓

        int aScale = 1;
        //先转化
        TPath  aPath;
        aItem->PolyLineToPath(aPath,aScale);
        TPaths  aOffPaths;

        //最外边界
        PathOffset(aPath,aOffPaths,LimitedNum,aScale*LimitedDis*(-1));
        fPaths->AddPaths(aOffPaths,aScale,1);

        //虚的边界
        PathOffset(aPath,aOffPaths,2,OffsetDis*aScale);
        fPaths->AddPaths(aOffPaths,aScale,2);

        /*
         MPolyLine* aItem = fPaths->Items[0];                                    //其中的一个轮廓

        //先转化
        TPath  aPath;
        aItem->PolyLineToPath(aPath,1000);
        TPaths  aOffPaths;

        //最外边界
        PathOffset(aPath,aOffPaths,LimitedNum,1000*LimitedDis*(-1));
        fPaths->AddPaths(aOffPaths,1000,1);

        //虚的边界
        PathOffset(aPath,aOffPaths,2,OffsetDis*1000);
        fPaths->AddPaths(aOffPaths,1000,2);
        */
     }
     else  //多个轮廓线，第一个轮廓是外轮廓，其余为内轮廓
     {
        for(int i=0; i < iNum; i++)
        {
            int aScale = 1;
            MPolyLine* aItem = fPaths->Items[i];
            //先转化
            TPath  aPath;
            aItem->PolyLineToPath(aPath,aScale);
            TPaths  aOffPaths;

            if(i==0) //最外边界
            {
                PathOffset(aPath,aOffPaths,LimitedNum,aScale*LimitedDis*(-1));
                fPaths->AddPaths(aOffPaths,1000,1);

                //填充线的偏移
                PathOffset(aPath,aOffPaths,2,OffsetDis*aScale);
                fPaths->AddPaths(aOffPaths,aScale,2);
            }
            else //内部，要往外扩
            {
                PathOffset(aPath,aOffPaths,2,LimitedDis*aScale);
                fPaths->AddPaths(aOffPaths,aScale,1);

                //填充线的偏移
                PathOffset(aPath,aOffPaths,2,OffsetDis*(-1.0*aScale));
                fPaths->AddPaths(aOffPaths,aScale,2);
            }
        }
    }
}

float TFormGYDesign::GetDistanceBetweenScanLines(float aDistanceLines,int aAngle)
{
    int aTheta = aAngle % 90;

    if( aAngle - 90 == 0 || aTheta == 0)  //垂直或水平
             return aDistanceLines;

    return aDistanceLines/cos(degToRad(aTheta));
}


//------------------------------------------------------------------------------
//aAngle: 角度
//基本设计过程：首先求出模型的最大Bmax与Bmin的和，然后计算扫描线的截距，从而求出扫描线的根数；
//然后对于每一个扫描线，进行边界求交运算，然后对交点进行排序，最后按照从奇数落笔，偶数台笔的顺序输出；
void  TFormGYDesign::CalculateHatchLines(MPolyLines* aEdges,int aAngle,MHatchLines* fHatchLines)
{
    if(aEdges == NULL || aEdges->Count == 0)  return;

    fHatchLines->Clear();  //填充线清空

    //找三个量：截距的范围;扫描线截距;最大截距;
    double aBmax;
    float aHeightOfJieJu = GetDistanceBmax2Bmin(aEdges->Items[0],aAngle,aBmax);
    float aDeltaJieJu = GetDistanceBetweenScanLines(DistanceLines,aAngle);
    int   aLineCount = Floor(aHeightOfJieJu / aDeltaJieJu);   //线的条数

    M2DPoints*  aIntPoints = new M2DPoints();

    for(int i=0; i < aLineCount; i++)
    {
        double aB = aBmax - aDeltaJieJu*(i+1);                                  //从上往下计算截距
        //if Angle == 90-----,  else ----------
        double aK = GetLine_K(aAngle);                                          //斜率

        //每一条扫描线与所有的边求交
        GetIntPointsFromEdges(aIntPoints,aB,aK,aEdges);

        if(aIntPoints->Count % 2 == 0) //偶数
        {
            if(fabs(aK-1e10)<=1e-5)   //纵线,按纵坐标排序
            {
                 SortList(aIntPoints, 1);
            }
            else   //按横坐标排序
            {
                 SortList(aIntPoints, 0);
            }

            for(int i=0; i < aIntPoints->Count; )
            {
                M2DPoint*  aFirst = aIntPoints->Items[i];   //奇数
                M2DPoint*  aSecond = aIntPoints->Items[i+1]; //偶数
                i = i+2;
                fHatchLines->NewHatchLine(aFirst->X,aFirst->Y,aSecond->X,aSecond->Y);
            }
            aIntPoints->Clear();
        }
        else
        {
            aIntPoints->Clear();
            throw Exception("找到奇数个交点");
        }
    }
}

//坐标排序
//aBase = 0: X, 1:Y
void  TFormGYDesign::SortList(M2DPoints*  aSortList, int aBase)
{
    int  aCount = aSortList->Count;
    for(int limit = aCount - 1; limit>0; limit--)  //循环次数：1 2  3 4 5
    {
        for(int i = 0; i < limit; i++)
        {
            if(aBase == 0)    //基于X坐标比较
            {
                if(aSortList->Items[i]->X > aSortList->Items[i+1]->X)
                {
                   float xSave = aSortList->Items[i]->X;
                   float ySave = aSortList->Items[i]->Y;
                   aSortList->Items[i]->X = aSortList->Items[i+1]->X;
                   aSortList->Items[i]->Y = aSortList->Items[i+1]->Y;
                   aSortList->Items[i+1]->Y = ySave;
                   aSortList->Items[i+1]->X = xSave;
                }
            }
            else  //基于Y坐标比较
            {
                if(aSortList->Items[i]->Y > aSortList->Items[i+1]->Y)
                {
                   float xSave = aSortList->Items[i]->X;
                   float ySave = aSortList->Items[i]->Y;
                   aSortList->Items[i]->X = aSortList->Items[i+1]->X;
                   aSortList->Items[i]->Y = aSortList->Items[i+1]->Y;
                   aSortList->Items[i+1]->Y = ySave;
                   aSortList->Items[i+1]->X = xSave;
                }
            }
        }
    }
}

//返回线与轮廓的所有的交点
void  TFormGYDesign::GetIntPointsFromEdges(M2DPoints* aIntPoints,double aB,
                             double aK,MPolyLines* aEdges)
{
      M2DPoint* aPoint = new M2DPoint(NULL);

      for(int i=0; i < aEdges->Count; i++)   //轮廓环
      {
           //取出一个
           MPolyLine*  aItem = aEdges->Items[i];
           int  aEdgeNum = aItem->Points->Count - 1;  //边

           for(int j=0; j < aEdgeNum; j++)  //边数
           {
               //取出一条边
               double  aSX = aItem->Points->Items[j]->X;
               double  aSY = aItem->Points->Items[j]->Y;
               double  aEX = aItem->Points->Items[(j+1)%aEdgeNum]->X;
               double  aEY = aItem->Points->Items[(j+1)%aEdgeNum]->Y;

               int iRet = GetLine2Line(aK,aB,aSX,aSY,aEX,aEY,aPoint);      //获得线与线的交点

               if(iRet == 1) //有交点
               {
                   aIntPoints->New2DPoint(aPoint->X,aPoint->Y);
               }
           }
      }

      delete aPoint;
}

//求线与线的交点； 返回值(0: 无交点，1：有交点
int  TFormGYDesign::GetLine2Line(double aK,double aB,
                  double aSX,double aSY,double aEX,double aEY,M2DPoint*  APoint)
{
    //已知斜率，B,  求与直线的交点 (0,aB),aK  ;  aSX,aSY,aEX,aEY
    //直线方程                     P0+ sD0  , P1 + tD1
    if(fabs(aSX - aEX) <= 1e-5)  //纵线
    {
        if(fabs(aK-1e10)<=1e-5)   //纵线
        {
            return 0;
        }

        //有效范围
        double  aYmax = aSY > aEY ? aSY: aEY;
        double  aYmin = aSY > aEY ? aEY: aSY;
        double  aIntY = aK * aSX + aB;
        if(aIntY > aYmin && aIntY < aYmax)   //找到一个
        {
            APoint->X = aSX;
            APoint->Y = aIntY;

            return 1;
        }
        return 0;
    }
    else  if(fabs(aSY - aEY) <= 1e-5)   //横线
    {
        if(aK == 0.0) //横线
        {
            return 0;
        }

        double  aXmax = aSX > aEX ? aSX: aEX;
        double  aXmin = aSX > aEX ? aEX: aSX;

        double aIntX;
        if(fabs(aK-1e10)<=1e-5)   //纵线
        {
            aIntX = aB;
        }
        else
        {
            aIntX = (aEY - aB) /aK;
        }

        if(aIntX > aXmin && aIntX < aXmax)   //找到一个
        {
            APoint->X = aIntX;
            APoint->Y = aEY;

            return 1;
        }
        return 0;
    }
    else //斜线
    {
        double aLineK2 = (aEY - aSY)/(aEX - aSX);
        double aIntX;
        if(fabs(aLineK2 - aK) < 1e-5) //平行
        {
            return 0;  //不相交
        }
        else if(fabs(aK-1e10)<=1e-5)   //纵线
        {
            aIntX = aB;
        }
        else
        {
            aIntX = (aSY - aLineK2*aSX - aB)/(aK - aLineK2);
        }

        double aIntY = aSY + aLineK2*(aIntX - aSX);
        double  aYmax = aSY > aEY ? aSY: aEY;
        double  aYmin = aSY > aEY ? aEY: aSY;

        if(aIntY >= aYmin && aIntY <= aYmax)   //找到一个
        {
              APoint->X = aIntX;
              APoint->Y = aIntY;

              return 1;
        }
        return 0;
    }
}


float  TFormGYDesign::GetLine_K(int aAngle)
{
    int aTheta = aAngle;

    if( aTheta - 90 == 0)  //垂直
          return  1e10;

    aTheta = aAngle % 90;
    return tan(degToRad(aTheta));
}

//------------------------------------------------------------------------------
//从上向下，从右向左的顺序填充
float  TFormGYDesign::GetDistanceBmax2Bmin(MPolyLine* aEdges,int aAngle,double& Bmax)
{
    int aTheta = aAngle % 90;   //0~90之间

    if(InstanceType == 0 || InstanceType == 3 || InstanceType == 4) //矩形
    {
        if(aTheta == 0 && aAngle == 90) //垂直
        {
            Bmax = aEdges->Points->MaxX;
            return fabs(aEdges->Points->MaxX - aEdges->Points->MinX);
        }
        else if(aTheta == 0) //水平
        {
            Bmax = aEdges->Points->MaxY;
            return fabs(aEdges->Points->MaxY - aEdges->Points->MinY);
        }
        else  //其他角度
        {
            Bmax = aEdges->Points->MaxY - tan(degToRad(aTheta))* aEdges->Points->MinX;
            float Bmin = aEdges->Points->MinY - tan(degToRad(aTheta))* aEdges->Points->MaxX;

            return fabs(Bmax - Bmin);
        }
    }
    else if(InstanceType == 1) //三角形
    {
        if(aTheta == 0 && aAngle == 90) //垂直
        {
            Bmax = aEdges->Points->MaxX;
            return fabs(aEdges->Points->MaxX - aEdges->Points->MinX);
        }
        else if(aTheta == 0) //水平
        {
            Bmax = aEdges->Points->MaxY;
            return fabs(aEdges->Points->MaxY - aEdges->Points->MinY);
        }
        else  //其他角度
        {
            double  aHeight1 = aEdges->Points->MaxY;
            double  aHeight2 = aEdges->Points->MaxY - tan(degToRad(aTheta))* aEdges->Points->MinX;

            if(aHeight1 > aHeight2)
                 Bmax = aHeight1;
            else
                 Bmax = aHeight2;

            float Bmin = aEdges->Points->MinY - tan(degToRad(aTheta))* aEdges->Points->MaxX;
            return fabs(Bmax - Bmin);
        }
    }
    else if(InstanceType == 2) //圆形
    {
        if(aTheta == 0 && aAngle == 90) //垂直
        {
            Bmax = aEdges->Points->MaxX;
            return fabs(aEdges->Points->MaxX - aEdges->Points->MinX);
        }
        else if(aTheta == 0) //水平
        {
            Bmax = aEdges->Points->MaxY;
            return fabs(aEdges->Points->MaxY - aEdges->Points->MinY);
        }
        else  //其他角度
        {
            double  aHeight = aEdges->Points->MaxX / cos(degToRad(aTheta));
            Bmax = aHeight;

            return fabs(2*Bmax);
        }
    }
    else
        throw Exception("未识别的类型");
}

//------------------------------------------------------------------------------
void __fastcall TFormGYDesign::TreeView1Click(TObject *Sender)
{
    DoClickTreeNode(GetSelectedLayerDataItem(TreeView1));
}
//---------------------------------------------------------------------------
//显示
void  TFormGYDesign::DoClickTreeNode(MLayerDataTreeNode* aDMNode)
{
    fCurrTreeNode = aDMNode;

    if(aDMNode == NULL)  return;
    if(aDMNode->Type == "0")  return;

    ShowImageInfo(this->Image1, 1.1*(aDMNode->MaxX - aDMNode->MinX), 1.1*(aDMNode->MaxY - aDMNode->MinY),
              aDMNode->PolyLines,aDMNode->HatchLines,1);
}

//打印排版
void __fastcall TFormGYDesign::BitBtn3Click(TObject *Sender)
{
    String  aOutDir = ApplicationPath() + "\\TestModel";

    //加载模型到List中
    OpenDialog1->Title = "指定工艺切片文件";
    OpenDialog1->Filter = "工艺切片文件(*.cli)|*.cli";
    OpenDialog1->InitialDir = aOutDir;
    OpenDialog1->Options += TOpenOptions()<<ofAllowMultiSelect;
    if(OpenDialog1->Execute() != mrOk)   return;

    TStrings*  aFileList = OpenDialog1->Files;    //获取文件列表
    fProjects->LoadPartProjectsFromFileStrings(aFileList);
    fProjects->AddToListBox(this->ListBox1);

    DrawBackImage();
    DrawImage(ListBox1,true);
}
//---------------------------------------------------------------------------
//擦除了背景
void TFormGYDesign::DrawBackImage()
{
    WindowRangel = gIniFile->ReadString("Project","WindowRange","150");
    WorkArea = gIniFile->ReadString("Project","WorkArea","125");

    DrawGridLine(WindowRangel*2,WindowRangel*2,WorkArea*2,WorkArea*2);
}


void __fastcall TFormGYDesign::ListBox1Click(TObject *Sender)
{
     OnClickListBox(GetSelectedPartProject(ListBox1));
}

void TFormGYDesign::DrawImage(TListBox* aListBox,bool bAll)
{
    for(int i=0; i < aListBox->Items->Count; i++)
    {
        if(bAll) //全显示红的
        {
            DrawImage((MPartProject*)aListBox->Items->Objects[i],false,true);
        }
        else
        {
          if(i == aListBox->ItemIndex)    //当前选中的AMProject
                DrawImage((MPartProject*)aListBox->Items->Objects[i],false,true);
          else
                DrawImage((MPartProject*)aListBox->Items->Objects[i],false,false);
        }
    }
}

void  TFormGYDesign::DrawImage(MPartProject* aItem,bool bClearBackImage,bool  bCurrent)
{
     if(aItem == NULL)  return;

     double aMinX = aItem->PartMinX;
     double aMaxX = aItem->PartMaxX;
     double aMinY = aItem->PartMinY;
     double aMaxY = aItem->PartMaxY;

     //创建一个包围框
     String  aSum = "$$POLYLINE/1 1 5  ";

     String  aData;
     aData.sprintf("  %.3f  %.3f",aMinX,aMinY);
     aSum+=aData;
     aData.sprintf("  %.3f  %.3f",aMaxX,aMinY);
     aSum+=aData;
     aData.sprintf("  %.3f  %.3f",aMaxX,aMaxY);
     aSum+=aData;
     aData.sprintf("  %.3f  %.3f",aMinX,aMaxY);
     aSum+=aData;
     aData.sprintf("  %.3f  %.3f",aMinX,aMinY);
     aSum+=aData;

     MPolyLines*  fPaths = new MPolyLines();
     MPolyLine* aLineItem = fPaths->NewPolyLine();
     aLineItem->LoadPolyLineData(aSum);

     ShowImageInfo(Image1,WindowRangel*2,WindowRangel*2,fPaths,NULL,1,bClearBackImage,bCurrent);
}
//---------------------------------------------------------------------------
void  TFormGYDesign::OnClickListBox(MPartProject* aItem)
{
     if(aItem == NULL) return;

     if(aItem != CurrentProject)  //切换了
     {
         if(CurrentProject == NULL)  //第一次点击
         {
             CurrentProject = aItem;
             if(CBox_Pens->Items->Count > 0)
             {
                 CBox_Pens->ItemIndex = 0;
                 DoComboBoxChange(GetSelectedLaserPen(CBox_Pens));
             }
         }
         else  //保存
         {
             //保存原来的
             CurrentProject->LaserPen = GetSelectedLaserPen(CBox_Pens);   //保存

             //处理现在的
             CurrentProject = aItem;
             if(CurrentProject->LaserPen != NULL)
             {
                CBox_Pens->ItemIndex = CurrentProject->LaserPen->PenID - 1;
                DoComboBoxChange(GetSelectedLaserPen(CBox_Pens));
             }
             else
             {
                CBox_Pens->ItemIndex = 0;
                DoComboBoxChange(GetSelectedLaserPen(CBox_Pens));
             }
         }
     }

     DrawBackImage();  //重画背景
     DrawImage(ListBox1);
}

//物理大小
void __fastcall TFormGYDesign::FormShow(TObject *Sender)
{
    int  aClientWidth = this->ClientWidth;
    int  aClientHeight = this->ClientHeight;

    int  aImageSize = aClientWidth > aClientHeight ?  aClientHeight: aClientWidth;  //取小的

    this->Image1->Width = aImageSize;
    this->Image1->Height = aImageSize;

    //加载Pen信息
    FormLaserSetting->LaserPens->ToComboBox(CBox_Pens);
    if(CBox_Pens->Items->Count > 0)
    {
        CBox_Pens->ItemIndex = 0;
        DoComboBoxChange(GetSelectedLaserPen(CBox_Pens));
    }
}

//---------------------------------------------------------------------------
void __fastcall TFormGYDesign::BitBtn1Click(TObject *Sender)
{
    DrawBackImage();
    DrawImage(ListBox1,true);
}
//---------------------------------------------------------------------------
void __fastcall TFormGYDesign::BitBtn4Click(TObject *Sender)
{
    if(ListBox1->ItemIndex < 0 || ListBox1->ItemIndex > ListBox1->Count-1)
         throw Exception("请先选择要移动的Part");

    //平移保存
    //BitBtn4->Enabled = false;

    DoPartMove(GetSelectedPartProject(ListBox1),
                    StrToFloat(this->EditMoveX->Text),StrToFloat(this->EditMoveY->Text));

    this->EditMoveX->Text = "0";
    this->EditMoveY->Text = "0";
    //BitBtn4->Enabled = true;

    //刷新当前
    DrawBackImage();
    DrawImage(ListBox1,false);
}
//---------------------------------------------------------------------------
void  TFormGYDesign::DoPartMove(MPartProject* aItem,double aMoveX,double aMoveY)
{
    if(aItem == NULL)
    {
        this->EditMoveX->Text = "0";
        this->EditMoveY->Text = "0";
        BitBtn4->Enabled = true;
        throw Exception("请先选择要移动的零件");
    }

    aItem->DoMovePart(aMoveX,aMoveY);
}

//------------------------------------------------------------------------------
void __fastcall TFormGYDesign::BitBtn6Click(TObject *Sender)
{
    String  aOutDir = ApplicationPath() + "\\TestModel";

    //工艺保存
    //先找到最大层，然后枚举每一个，输出
    int  aMaxLayerNum = MaxLayerNum;
    if(aMaxLayerNum < 0)  throw Exception("请先进行排版，然后再进行工艺输出");

    double  aMinLayerThick = MinLayerThick;

    TStringList* aFileList = new TStringList;
    GetCLIFileHeader(aFileList,aMaxLayerNum,-1);

    for(int i=0; i < aMaxLayerNum; i++)
    {
        TStringList*  aLayers = OutputMultiPartByLayer(i,aMinLayerThick);  //输出一层
        aFileList->AddStrings(aLayers);
    }

    OutCLITrailToFile(aFileList);

    //4、保存
    SaveDialog1->InitialDir = aOutDir;
    SaveDialog1->DefaultExt = "mix";
    SaveDialog1->Filter = "工艺切片排版文件(*.mix)|*.mix";
    SaveDialog1->FileName = "MultiPart_GY_CLI";
    if(SaveDialog1->Execute() == mrOk)
    {
        String  aFileName = SaveDialog1->FileName;
        aFileList->SaveToFile(aFileName);
        ShowMessage("工艺切片排版文件生成完成!" + aFileName);
    }

    delete aFileList;
}
//---------------------------------------------------------------------------
//要求：厚度为整数比
int TFormGYDesign::readMaxLayerNum()
{
    return (int)(PartMaxHeight/MinLayerThick);
}

double  TFormGYDesign::readPartMaxHeight()
{
    if(ListBox1->Count == 0) throw Exception("没有加载零件");

    double  aMax = -MAXFLOAT;
    for(int i=0; i < ListBox1->Count; i++)
    {
        MPartProject* aItem = (MPartProject*)ListBox1->Items->Objects[i];
        if(aItem->MainItems->Count <= 1)  throw Exception("获取模型信息失败:readPartMaxHeight");

        if(aMax < StrToFloat(aItem->MainItems->LastItem()->AbsoluteHeight))
              aMax = StrToFloat(aItem->MainItems->LastItem()->AbsoluteHeight);
    }

    return aMax;
}

double  TFormGYDesign::readMinLayerThick()
{
    double  aMin = MAXFLOAT;

    for(int i=0; i < ListBox1->Count; i++)
    {
        MPartProject* aItem = (MPartProject*)ListBox1->Items->Objects[i];
        if(aMin > StrToFloat(aItem->MainItems->Items[0]->AbsoluteHeight))
            aMin = StrToFloat(aItem->MainItems->Items[0]->AbsoluteHeight);
    }
    return aMin;
}

//iLayers: 基于0的
/* 以前的
TStringList* TFormGYDesign::OutputMultiPartByLayer(int iLayers,double iLayerThick)
{
    TStringList* aFileList = new TStringList;

    for(int i=0; i < ListBox1->Count; i++)
    {
        MAMProject* aItem = (MAMProject*)ListBox1->Items->Objects[i];

        if(i==0)  //第一个
        {
           aFileList->Add("$$LAYER/" + FloatToStr(iLayerThick* (iLayers+1)));
        }

        if(iLayers < aItem->MainItems->Count)
        {
           MLayerDataTreeNode* aLayerItem = aItem->MainItems->Items[iLayers];

           if(ComboBox2->ItemIndex == 0) //先扫描线
           {
               aLayerItem->HatchLines->OutPutContours2CLI(aFileList);
               aLayerItem->PolyLines->OutPutContours2CLI(aFileList);
           }
           else
           {
               aLayerItem->PolyLines->OutPutContours2CLI(aFileList);
               aLayerItem->HatchLines->OutPutContours2CLI(aFileList);
           }
        }
    }

    return aFileList;
}
*/

//iLayers: 基于0的,输出一层的信息
TStringList* TFormGYDesign::OutputMultiPartByLayer(int iLayers,double iLayerThick)
{
    //层索引号
    double  aCurrentHeight = iLayerThick* (iLayers+1);
    //找比较接近的那个层

    //输出所有Part的给定厚度的信息
    TStringList* aFileList = new TStringList;

    //层号
    aFileList->Add("$$LAYER/" + FloatToStr(iLayerThick* (iLayers+1)));

    for(int i=0; i < ListBox1->Count; i++)
    {
        MPartProject* aItem = (MPartProject*)ListBox1->Items->Objects[i];

        MLayerDataTreeNode* aLayerItem =  aItem->FindLayerDataTreeNodeByHeight(aCurrentHeight);
        if( aLayerItem == NULL)   //没有找到
                continue;

        aFileList->Add("Power="+aItem->LaserPen->PenPower);
        aFileList->Add("Speed="+aItem->LaserPen->PenSpeed);

        if(ComboBox2->ItemIndex == 0) //先扫描线
        {
            aLayerItem->HatchLines->OutPutContours2CLI(aFileList);
            aLayerItem->PolyLines->OutPutContours2CLI(aFileList);
        }
        else
        {
            aLayerItem->PolyLines->OutPutContours2CLI(aFileList);
            aLayerItem->HatchLines->OutPutContours2CLI(aFileList);
        }
    }
    return aFileList;
}

//------------------------------------------------------------------------------
//上移
void __fastcall TFormGYDesign::N1Click(TObject *Sender)
{
    if(ListBox1->ItemIndex == 0) return;

    fProjects->MoveTo(GetSelectedPartProject(ListBox1),ListBox1->ItemIndex -1);
    fProjects->AddToListBox(ListBox1,true);
}
//---------------------------------------------------------------------------

void __fastcall TFormGYDesign::N2Click(TObject *Sender)
{
     MPartProject* aItem =  GetSelectedPartProject(ListBox1);
     if(aItem == NULL)
     {
         throw Exception("请先选择所要移除的文件!!!");
     }

     fProjects->DelObject(aItem);
     DelStringsItemByObject(ListBox1->Items,(void*)GetSelectedPartProject(ListBox1));

     CurrentProject = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TFormGYDesign::FormClose(TObject *Sender,
      TCloseAction &Action)
{
     this->TreeView1->Items->Clear();
     this->ListBox1->Items->Clear();
     fProjects->Clear();

     CurrentProject = NULL; 
}
//---------------------------------------------------------------------------


void __fastcall TFormGYDesign::ListBox1DragDrop(TObject *Sender,
      TObject *Source, int X, int Y)
{
     if(Source != (TObject*)ListBox1 || ListBox1->ItemIndex == -1)
           return;

     TListBox*  aSourceListBox = (TListBox*)Source;
     int iIndex = aSourceListBox->ItemAtPos(Point(X,Y),true);
     if( iIndex != -1)
     {
        fProjects->MoveTo(GetSelectedPartProject(ListBox1),iIndex);
        fProjects->AddToListBox(ListBox1,true);
     }
}
//---------------------------------------------------------------------------
void __fastcall TFormGYDesign::ListBox1DragOver(TObject *Sender,
      TObject *Source, int X, int Y, TDragState State, bool &Accept)
{
     Accept = (Source == ListBox1);
}

//--------------------激光笔的设置-----------------------------------------
void __fastcall TFormGYDesign::Button1Click(TObject *Sender)
{
    if(FormLaserSetting->ShowModal() == mrOk)
    {
       if(FormLaserSetting->fSelectedLaserPen != NULL)
       {
           CBox_Pens->ItemIndex = FormLaserSetting->fSelectedLaserPen->PenID - 1;
           DoComboBoxChange(FormLaserSetting->fSelectedLaserPen);
       }
       else
           DoComboBoxChange(GetSelectedLaserPen(CBox_Pens));
    }
}

//---------------------------------------------------------------------------
void __fastcall TFormGYDesign::CBox_PensChange(TObject *Sender)
{
    DoComboBoxChange(GetSelectedLaserPen(CBox_Pens));
}

void  TFormGYDesign::DoComboBoxChange(MLaserPen* aPen)
{
    if(aPen == NULL) return;

    Edit2->Text = aPen->PenPower;
    Edit11->Text = aPen->PenSpeed;

    if(CurrentProject!=NULL)
         CurrentProject->LaserPen = aPen;
}

//---------------------------------------------------------------------------
void __fastcall TFormGYDesign::Button2Click(TObject *Sender)
{
    OpenDialog1->Filter = "工艺切片排版文件(*.dat)|*.dat";
    if(OpenDialog1->Execute() != mrOk)
           return;

    String  aBatFile =  OpenDialog1->FileName;
    TStringList*  aModels = new TStringList;
    aModels->LoadFromFile(aBatFile);

    String  aPath =  ExtractFilePath_Format(aBatFile) + "\\";  

    TStringList* aListGroup = NULL;
    fProjects->Clear();
    for(int i=0;i< aModels->Count;i++)
    {
        String  aFileLine = aModels->Strings[i];

        if(HasSubString(aFileLine,"node") == false)
              continue;

        //拆分
        aListGroup = splitToStrings(aFileLine,",");  //拆分

        String  aModelFile = Get_ListItemStr_ByName( aListGroup, "File", "=", "unKnown");   //未知类型
        String  aTrueModelFile = aPath + aModelFile;

        String  aMovX = Get_ListItemStr_ByName( aListGroup, "MovX", "=", "unKnown" );
        String  aMovY = Get_ListItemStr_ByName( aListGroup, "MovY", "=", "unKnown");   //NodeName
        String  aPenIndex = Get_ListItemStr_ByName( aListGroup, "PenIndex", "=", "unKnown");

        //加载到内部
        MPartProject* aItem = fProjects->NewPartProject();      //创建一个工程
        aItem->LoadGYInfoFromFile(aTrueModelFile);

        //设置笔
        CBox_Pens->ItemIndex = StrToInt(aPenIndex) - 1;
        aItem->LaserPen = GetSelectedLaserPen(CBox_Pens);

        //平移
        aItem->DoMovePart(StrToFloat(aMovX),StrToFloat(aMovY));
    }

    fProjects->AddToListBox(this->ListBox1,true);

    delete aListGroup;
    delete aModels;

    DrawBackImage();
    DrawImage(ListBox1,true);

    //保存
    //BitBtn6Click(NULL);
}
//---------------------------------------------------------------------------

