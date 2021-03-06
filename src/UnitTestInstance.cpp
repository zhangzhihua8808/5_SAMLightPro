//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitTestInstance.h"
#include "UnitTool_ClassExtend.h"
#include "math.h"
#include "UnitTool_Single.h"
#include "UnitFileSelect.h"
#include "UnitModelLoad.h"


//这个窗口主要负责：零件轮廓的生成;
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormTestInstance *FormTestInstance;

//常量
const int    scale = 1000;    //放大1000倍,都以Int型使用
//---------------------------------------------------------------------------
__fastcall TFormTestInstance::TFormTestInstance(TComponent* Owner)
        : TForm(Owner)
{
    fPaths = new MPolyLines();

    String  aOutDir = ApplicationPath() + "\\TestModel";
    CheckAndMakeDirectory(aOutDir);     //检查创建目录
}
//----------------------------参数----------------------------------------------
int  TFormTestInstance::readInstanceType()
{
    return ComboBox1->ItemIndex;
}

void TFormTestInstance::writeInstanceType(int aType)
{
    ComboBox1->ItemIndex = aType;
}

double TFormTestInstance::readWidth()
{
    return StrToFloat(EditWidth->Text);
}

void  TFormTestInstance::writeWidth(double aWidth)
{
    EditWidth->Text = FloatToStr(aWidth);
}

double TFormTestInstance::readHeight()
{
    return StrToFloat(EditHeight->Text);
}

void TFormTestInstance::writeHeight(double aHeight)
{
     EditHeight->Text = FloatToStr(aHeight);
}

double TFormTestInstance::readLayerThick()
{
     return StrToFloat(Edit_LayerThick->Text);
}

void   TFormTestInstance::writeLayerThick(double aLayerThick)
{
     Edit_LayerThick->Text = FloatToStr(aLayerThick);
}

//------------------------------------------------------------------------------
void SetViewPort(TImage* aPBox,int aDrawWidth,int aDrawHeight,bool  bClear)
{
    int  iMaxSize = aDrawWidth > aDrawHeight ? aDrawWidth : aDrawHeight;


    //设置坐标映射模式
    SetMapMode(aPBox->Canvas->Handle,MM_ANISOTROPIC);

    //将PBox的实际宽高映射到指定的宽高
    SetWindowExtEx(aPBox->Canvas->Handle,iMaxSize,iMaxSize,NULL);

    //设置视口：X从左向右，Y从下向上
    SetViewportExtEx(aPBox->Canvas->Handle,aPBox->Width,-aPBox->Height,NULL);

    //窗口原点的位置
    SetWindowOrgEx(aPBox->Canvas->Handle,0,0,NULL);

    //视口原点的位置，就是PBox中哪一点和上面的原点对应
    SetViewportOrgEx(aPBox->Canvas->Handle,aPBox->Width/2.0,aPBox->Height/2.0,NULL);

    if(bClear)
          aPBox->Canvas->FillRect(aPBox->Canvas->ClipRect);
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
//------------------------------------------------------------------------------
void GetCLIFileHeader(TStringList* aFile,int aLayerNum,String aPartID)
{
    if(aFile == NULL)  throw Exception("GetCLIFileHeader 参数为NULL");

    //1、输出文件头
    aFile->Add("$$HEADERSTART");
    aFile->Add("$$ASCII");
    aFile->Add("$$UNITS/1");
    aFile->Add("$$VERSION/200");
    aFile->Add("$$LABEL/"+ aPartID);
    aFile->Add("$$LAYERS/" + IntToStr(aLayerNum));
    aFile->Add("$$HEADEREND");
    aFile->Add("$$GEOMETRYSTART");
}

void OutCLITrailToFile(TStringList* aFile)
{
   //结尾
    aFile->Add("$$GEOMETRYEND");
}

//---------------------------------------------------------------------------
//预览并输出单层信息//显示
void  ShowImageInfo(TImage* aImage, int aWidth,int aHeight,
                    MPolyLines*  aPaths,MHatchLines*  aLines,int aScale,bool bClear,bool bCurrent)
{
    SetViewPort(aImage,aWidth*aScale,aHeight*aScale,bClear);   //把显示区域放大，便于看清楚

    aImage->Canvas->Pen->Width = 0.01;
    //绘制边界
    if(bCurrent)
       aImage->Canvas->Pen->Color = clRed;
    else
       aImage->Canvas->Pen->Color = clBlack;

    if(aPaths != NULL)
    {
        for(int i=0; i < aPaths->Count; i++)
        {
            MPolyLine*  aItemPath = aPaths->Items[i];                               //取出一条边界线
            if(aItemPath->PathType == 2)  //虚路径
                    continue;

            M2DPoint*  AInitPoint = aItemPath->Points->Items[0];                            //取出第一个点

            aImage->Canvas->MoveTo(AInitPoint->X*aScale,AInitPoint->Y*aScale);
            for(int j=1; j < aItemPath->Points->Count; j++)
            {
                M2DPoint*  APoint = aItemPath->Points->Items[j];
                aImage->Canvas->LineTo(APoint->X*aScale,APoint->Y*aScale);
            }
        }
    }

    if(aLines != NULL)
    {
        for(int i=0; i < aLines->Count; i++)
        {
           MHatchLine*  aLine = aLines->Items[i];
           aImage->Canvas->MoveTo(aLine->Points->Items[0]->X*aScale,aLine->Points->Items[0]->Y*aScale);
           aImage->Canvas->LineTo(aLine->Points->Items[1]->X*aScale,aLine->Points->Items[1]->Y*aScale);
        }
    }
}

void  TFormTestInstance::BaseMoveToPosition(double aHeight,TStringList*  aFileList)
{
    double  aWidth[] = {1+5,1+1.5+15,1+1.5+1+25,1+1.5+1+0.5+35};

    for(int i=0; i < 4; i++)     //列
    {
         MPolyLine* aBase = new MPolyLine(NULL);
         aBase->Points->New2DPoint(-5,-5);                    //左下
         aBase->Points->New2DPoint(5,-5);                   //左下
         aBase->Points->New2DPoint(5,5);
         aBase->Points->New2DPoint(-5,5);
         aBase->Points->New2DPoint(-5,-5);

         aBase->DoMovePart(aWidth[i],aHeight);

         String  aPre = "$$POLYLINE/1 1 5 ";
         String  aPoints = aBase->Points->OutPoints();
         aFileList->Add(aPre + aPoints);
    }
}

//------------------------------------------------------------------------------
//创建样件的几何轮廓数据
void __fastcall TFormTestInstance::BitBtn4Click(TObject *Sender)
{
    CreateSampleFigureData(ComboBox1->ItemIndex);
}

void TFormTestInstance::CreateSampleFigureData(int iShapeType)
{
    String  aOutDir = ApplicationPath() + "\\TestModel";

    //层数，层厚
    int  iLayerNum = StrToInt(Edit1->Text.c_str());
    double fLayerThick = StrToFloat(Edit_LayerThick->Text);

    TStringList*  aFile = new TStringList;
    String  aDefaultFileName;
    TStringList*  aGeo;

    //1、CLI 头结构
    GetCLIFileHeader(aFile,iLayerNum,iShapeType);

    //2、CLI 主体结构
    if(iShapeType == 0)  //矩形
    {
        aDefaultFileName = "GeoRectangle";
        aGeo = CreateRectangleFigureToFile(iLayerNum,fLayerThick);
    }
    else if(iShapeType == 1)  //正三角
    {
        aDefaultFileName = "GeoTriangle";
        aGeo = CreateTriangleFigureToFile(iLayerNum,fLayerThick);
    }
    else if(iShapeType == 2)  //圆形
    {
        aDefaultFileName = "GeoCircle";
        aGeo = CreateCircleFigureToFile(iLayerNum,fLayerThick,100);
    }
    else if(iShapeType == 3)  //工件
    {
        aDefaultFileName = "GeoPartI";
        aGeo = CreatePart1FigureToFile(iLayerNum,fLayerThick,30);

    }
    else if(iShapeType == 4)  //4X4
    {
        aDefaultFileName = "Geo4X4Part";
        aGeo = Create4X4PartFigueToFile(iLayerNum,fLayerThick);
    }
    else if(iShapeType == 5)  //焦平面
    {
        aFile->Clear();

        GetCLIFileHeader(aFile,21,iShapeType);

        aDefaultFileName = "GY_TestFocus";

        double  dlayerThick = StrToFloat(Edit3->Text);
        double  aLineSpace = StrToFloat(Edit4->Text);
        aGeo = CreateTestFocusToFile(aLineSpace,dlayerThick);
    }


    //3、CLI尾结构
    aFile->AddStrings(aGeo);
    OutCLITrailToFile(aFile);

    //4、保存
    SaveDialog1->InitialDir = aOutDir;
    SaveDialog1->DefaultExt = "cli";
    SaveDialog1->Filter = "切片文件(*.cli)|*.cli";
    SaveDialog1->FileName = aDefaultFileName;
    if(SaveDialog1->Execute() == mrOk)
    {
        String  aFileName = SaveDialog1->FileName;
        aFile->SaveToFile(aFileName);
        ShowMessage("["+ComboBox1->Text + "]切片几何轮廓数据完成!");
    }

    delete aFile;
}

//------------------------------------------------------------------------------
//轮廓
//iLayers: 层数
//iLayerThick: 层厚
TStringList*  TFormTestInstance::CreateRectangleFigureToFile(int iLayers,double iLayerThick)
{
    TStringList* aFileList = new TStringList;

    for(int i=0; i < iLayers; i++)
    {
        aFileList->Add("$$LAYER/" + FloatToStr(iLayerThick* (i+1)));

        String  aPre = "$$POLYLINE/1 1 ";
        //矩形
        int aPointNum = 5;   //矩形
        String  aSum = aPre + IntToStr(aPointNum) + "  ";

        String  aData;
        aData.sprintf("  %.3f  %.3f",Width/2.0*(-1),Height/2.0*(-1));
        aSum+=aData;
        aData.sprintf("  %.3f  %.3f",Width/2.0,Height/2.0*(-1));
        aSum+=aData;
        aData.sprintf("  %.3f  %.3f",Width/2.0,Height/2.0);
        aSum+=aData;
        aData.sprintf("  %.3f  %.3f",Width/2.0*(-1),Height/2.0);
        aSum+=aData;
        aData.sprintf("  %.3f  %.3f",Width/2.0*(-1),Height/2.0*(-1));
        aSum+=aData;
        aFileList->Add(aSum);
    }

    return aFileList;
}


TStringList*  TFormTestInstance::CreateTestFocusToFile(double iLineSpace,double iLayerThick)
{

    //1\ 创建数据
    int  XPosIndex[] = {10,9,8,7,6,5,4,3,2,1,0,-1,-2,-3,-4,-5,-6,-7,-8,-9,-10};
    double YStart = -10.0;
    double YEnd = 10.0;
    int  iLayerNum = 21;  //线条数

    MHatchLines*  aHatchLines = new MHatchLines();

    for(int i=0; i < iLayerNum; i++)
    {
       if( i == 10)  //中间那条，线长点
            aHatchLines->NewHatchLine(0.0,YStart - 5.0,0.0,YEnd + 5.0);
       else
            aHatchLines->NewHatchLine(XPosIndex[i]*iLineSpace,YStart,XPosIndex[i]*iLineSpace,YEnd);
    }


    //2、生成分层数据
    TStringList* aFileList = new TStringList;

    for(int i=0; i < iLayerNum; i++)
    {
        aFileList->Add("$$LAYER/" + FloatToStr(iLayerThick* (i+1)));

        String  aLine = aHatchLines->Items[i]->OutHatchLine();
        aFileList->Add(aLine);
    }

    delete aHatchLines;

    return aFileList;
}

TStringList*  TFormTestInstance::CreateTriangleFigureToFile(int iLayers,double iLayerThick)
{
    //三角形
    TStringList* aFileList = new TStringList;

    for(int i=0; i < iLayers; i++)
    {
        aFileList->Add("$$LAYER/" + FloatToStr(iLayerThick* (i+1)));

        String  aPre = "$$POLYLINE/1 1 ";

        int aPointNum = 4;
        String aSum = aPre + IntToStr(aPointNum) + "  ";

        String aData;
        aData.sprintf("  %.3f  0.0",Width/2.0*(-1));
        aSum+=aData;
        aData.sprintf("  %.3f  0.0",Width/2.0);
        aSum+=aData;
        aData.sprintf("  0.0   %.3f",Width*1.732/2.0);
        aSum+=aData;
        aData.sprintf("  %.3f  0.0",Width/2.0*(-1));
        aSum+=aData;
        aFileList->Add(aSum);
     }
    return aFileList;
}

//PointNum： 离散地点数
TStringList*  TFormTestInstance::CreateCircleFigureToFile(int iLayers,double iLayerThick,int PointNum)
{
    TStringList* aFileList = new TStringList;

    for(int i=0; i < iLayers; i++)
    {
        aFileList->Add("$$LAYER/" + FloatToStr(iLayerThick* (i+1)));

        String  aPre = "$$POLYLINE/1 1 ";
        //圆形
        int  aPointNum = PointNum;
        String aSum = aPre + IntToStr(aPointNum+1) + "  ";
        double aRadio = Width / 2.0;
        double aAngle = degToRad(360.0/aPointNum);

        String aData;
        for(int i=0; i <= aPointNum; i++)
        {
           aData.sprintf("  %.3f  %.3f",aRadio* sin(aAngle*i), aRadio* cos(aAngle*i));
           aSum+=aData;
        }
        aFileList->Add(aSum);
     }
    return aFileList;
}



TStringList*  TFormTestInstance::CreatePart1FigureToFile(int iLayers,double iLayerThick,int EdgeNum)
{
    //生成数据
    MPolyLine*  aPath = new MPolyLine(NULL);
    aPath->PathType = 0;                                                        //最外边界
    aPath->Points->New2DPoint(-20.0,-5.0);                   //左下
    aPath->Points->New2DPoint(-10.0,-5.0);

    double  aRadio = 14.5;
    double  aEdgeNum = EdgeNum;
    double  aAngle = 88.0/aEdgeNum;  //没一小份
    for(int i = aEdgeNum; i > 1; i--)
    {
        double  aX = aRadio* cos(degToRad(46 + aAngle* (i-1)));
        double  aY = aRadio* sin(degToRad(46 + aAngle* (i-1)))-15.5;
        aPath->Points->New2DPoint(aX,aY);
    }
    aPath->Points->New2DPoint(10.0,-5.0);                   //左下
    aPath->Points->New2DPoint(20.0,-5.0);

    //对称上去
    M2DPoints*   aTemp = new M2DPoints();
    for(int i=0; i < aPath->Points->Count; i++)
    {
        M2DPoint* aPoint = aPath->Points->Items[i];
        aTemp->New2DPoint(aPoint->X,aPoint->Y*(-1));
    }

    for(int i= aTemp->Count-1; i>=0; i--)
    {
        M2DPoint* aPoint = aTemp->Items[i];
        aPath->Points->New2DPoint(aPoint->X,aPoint->Y);
    }
    aPath->Points->New2DPoint(-20.0,-5.0);
    aTemp->Clear();
    delete aTemp;

    TStringList* aFileList = new TStringList;

    for(int i=0; i < iLayers; i++)
    {
        aFileList->Add("$$LAYER/" + FloatToStr(iLayerThick* (i+1)));

        String  aPre = "$$POLYLINE/1 1 ";
        int  aPointNum = aPath->Points->Count;
        String aSum = aPre + IntToStr(aPointNum) + "  ";
        aSum += aPath->Points->OutPoints();

        aFileList->Add(aSum);

     }

    aPath->Points->Clear();
    delete aPath;
    return aFileList;
}

TStringList*  TFormTestInstance::Create4X4PartFigueToFile(int iLayers,double iLayerThick)
{
    //生成数据
    MPolyLine*  aPath = new MPolyLine(NULL);
    aPath->PathType = 0;                                                        //最外边界
    aPath->Points->New2DPoint(0.0,0.0);                    //左下
    aPath->Points->New2DPoint(45.0,0.0);                   //左下
    aPath->Points->New2DPoint(45.0,43.8);
    aPath->Points->New2DPoint(0.0,43.8);
    aPath->Points->New2DPoint(0.0,0.0);

    TStringList* aFileList = new TStringList;

    for(int i=0; i < iLayers; i++)
    {
        aFileList->Add("$$LAYER/" + FloatToStr(iLayerThick* (i+1)));

        String  aPre = "$$POLYLINE/1 1 5 ";              //外轮廓
        String  aPoints = aPath->Points->OutPoints();
        aFileList->Add(aPre+aPoints);

        //最下一行
        double  aHeight[4] = {1+5,1+15+0.5, 1+0.5+1+25 , 1+0.5+1+0.3+35};
        for(int i=0; i < 4; i++)              //行
        {
            BaseMoveToPosition(aHeight[i],aFileList);
        }
    }

    aPath->Points->Clear();
    delete aPath;
    return aFileList;
}

void __fastcall TFormTestInstance::FormShow(TObject *Sender)
{
    int  aClientWidth = this->ClientWidth;
    int  aClientHeight = this->ClientHeight;

    int  aImageSize = aClientWidth > aClientHeight ?  aClientHeight: aClientWidth;  //取小的

    this->Image1->Width = aImageSize;
    this->Image1->Height = aImageSize;

    ComboBox1Change(NULL);
}
//---------------------------------------------------------------------------

void __fastcall TFormTestInstance::BitBtn1Click(TObject *Sender)
{
   //预览
   PreViewSampleFigureData(ComboBox1->ItemIndex);
}
//---------------------------------------------------------------------------
void  TFormTestInstance::PreViewSampleFigureData(int iShapeType)
{
    //1、获得数据
    if(iShapeType == 0)  //矩形
    {
        Image1->Picture = NULL;
        CreateSingleRectangleFigure();

        double aWidth = Width >= Height ? Width: Height;

        ShowImageInfo(Image1,int(aWidth*1.1),int(aWidth*1.1),fPaths,NULL,1);
        return;
    }
    else if(iShapeType == 1)  //正三角
    {
        Image1->Picture = NULL;
        CreateSingleTriangleFigure();
    }
    else if(iShapeType == 2)  //圆形
    {
        Image1->Picture = NULL;
        CreateSingleCircleFigure(100);
    }
    else if(iShapeType == 3)  //工件
    {
        Image1->Picture = NULL;
        CreateSinglePart1Figure(30);
    }
    else if(iShapeType == 4)  //4X4
    {
        fPaths->Clear();

        Image1->Picture = NULL;
        Image1->Picture->LoadFromFile(ApplicationPath() + "\\system\\Shape4X4.jpg");
        return;
    }
    else if(iShapeType == 5) //焦平面
    {
        fPaths->Clear();

        Image1->Picture = NULL;
        Image1->Picture->LoadFromFile(ApplicationPath() + "\\system\\TestFocus.jpg");
        return;
    }

    //2、
    ShowImageInfo(Image1,100,100,fPaths,NULL,100);
}

void  TFormTestInstance::CreateSingleRectangleFigure()
{
    String  aPre = "$$POLYLINE/1 1 ";
    //矩形
    int aPointNum = 5;   //矩形
    String  aSum = aPre + IntToStr(aPointNum) + "  ";

    String  aData;
    aData.sprintf("  %.3f  %.3f",Width/2.0*(-1),Height/2.0*(-1));
    aSum+=aData;
    aData.sprintf("  %.3f  %.3f",Width/2.0,Height/2.0*(-1));
    aSum+=aData;
    aData.sprintf("  %.3f  %.3f",Width/2.0,Height/2.0);
    aSum+=aData;
    aData.sprintf("  %.3f  %.3f",Width/2.0*(-1),Height/2.0);
    aSum+=aData;
    aData.sprintf("  %.3f  %.3f",Width/2.0*(-1),Height/2.0*(-1));
    aSum+=aData;

    fPaths->Clear();

    MPolyLine* aItem = fPaths->NewPolyLine();
    aItem->LoadPolyLineData(aSum);
}

void  TFormTestInstance::CreateSingleTriangleFigure()
{
    String  aPre = "$$POLYLINE/1 1 ";

    int aPointNum = 4;
    String aSum = aPre + IntToStr(aPointNum) + "  ";

    String aData;
    aData.sprintf("  %.3f  0.0",Width/2.0*(-1));
    aSum+=aData;
    aData.sprintf("  %.3f  0.0",Width/2.0);
    aSum+=aData;
    aData.sprintf("  0.0   %.3f",Width*1.732/2.0);
    aSum+=aData;
    aData.sprintf("  %.3f  0.0",Width/2.0*(-1));
    aSum+=aData;

    fPaths->Clear();

    MPolyLine* aItem = fPaths->NewPolyLine();
    aItem->LoadPolyLineData(aSum);
}

void  TFormTestInstance::CreateSingleCircleFigure(int PointNum)
{
    String  aPre = "$$POLYLINE/1 1 ";
    //圆形
    int  aPointNum = PointNum;
    String aSum = aPre + IntToStr(aPointNum+1) + "  ";
    double aRadio = Width / 2.0;
    double aAngle = degToRad(360.0/aPointNum);

    String aData;
    for(int i=0; i <= aPointNum; i++)
    {
       aData.sprintf("  %.3f  %.3f",aRadio* sin(aAngle*i), aRadio* cos(aAngle*i));
       aSum+=aData;
    }

    fPaths->Clear();

    MPolyLine* aItem = fPaths->NewPolyLine();
    aItem->LoadPolyLineData(aSum);
}

void  TFormTestInstance::CreateSinglePart1Figure(int EdgeNum)
{
    //生成数据
    MPolyLine*  aPath = new MPolyLine(NULL);
    aPath->PathType = 0;                                                        //最外边界
    aPath->Points->New2DPoint(-20.0,-5.0);                   //左下
    aPath->Points->New2DPoint(-10.0,-5.0);

    double  aRadio = 14.5;
    double  aEdgeNum = EdgeNum;
    double  aAngle = 88.0/aEdgeNum;  //没一小份
    for(int i = aEdgeNum; i > 1; i--)
    {
        double  aX = aRadio* cos(degToRad(46 + aAngle* (i-1)));
        double  aY = aRadio* sin(degToRad(46 + aAngle* (i-1)))-15.5;
        aPath->Points->New2DPoint(aX,aY);
    }
    aPath->Points->New2DPoint(10.0,-5.0);                   //左下
    aPath->Points->New2DPoint(20.0,-5.0);

    //对称上去
    M2DPoints*   aTemp = new M2DPoints();
    for(int i=0; i < aPath->Points->Count; i++)
    {
        M2DPoint* aPoint = aPath->Points->Items[i];
        aTemp->New2DPoint(aPoint->X,aPoint->Y*(-1));
    }

    for(int i= aTemp->Count-1; i>=0; i--)
    {
        M2DPoint* aPoint = aTemp->Items[i];
        aPath->Points->New2DPoint(aPoint->X,aPoint->Y);
    }
    aPath->Points->New2DPoint(-20.0,-5.0);
    aTemp->Clear();
    delete aTemp;

    String  aPre = "$$POLYLINE/1 1 ";
    int  aPointNum = aPath->Points->Count;
    String aSum = aPre + IntToStr(aPointNum) + "  ";
    aSum += aPath->Points->OutPoints();

    fPaths->Clear();

    MPolyLine* aItem = fPaths->NewPolyLine();
    aItem->LoadPolyLineData(aSum);

    delete aPath;
}


void __fastcall TFormTestInstance::FormClose(TObject *Sender,
      TCloseAction &Action)
{
    fPaths->Clear();
    Image1->Picture = NULL;
}
//---------------------------------------------------------------------------


void __fastcall TFormTestInstance::ComboBox1Change(TObject *Sender)
{
    if(ComboBox1->ItemIndex == 5) //焦平面
    {
        fPaths->Clear();

        Image1->Picture = NULL;
        Image1->Picture->LoadFromFile(ApplicationPath() + "\\system\\TestFocus.jpg");

        this->PageControl2->Visible = true;
        SetOnlyPageControlVis(TabSheet1,true,true);
    }
    else
    {
        fPaths->Clear();
        Image1->Picture = NULL;

        this->PageControl2->Visible = false;
    }
}
//---------------------------------------------------------------------------


