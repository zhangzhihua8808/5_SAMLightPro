//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitTestInstance.h"
#include "UnitTool_ClassExtend.h"
#include "math.h"
#include "UnitTool_Single.h"
#include "UnitFileSelect.h"
#include "UnitModelLoad.h"


//���������Ҫ�����������������;
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormTestInstance *FormTestInstance;

//����
const int    scale = 1000;    //�Ŵ�1000��,����Int��ʹ��
//---------------------------------------------------------------------------
__fastcall TFormTestInstance::TFormTestInstance(TComponent* Owner)
        : TForm(Owner)
{
    fPaths = new MPolyLines();

    String  aOutDir = ApplicationPath() + "\\TestModel";
    CheckAndMakeDirectory(aOutDir);     //��鴴��Ŀ¼
}
//----------------------------����----------------------------------------------
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


    //��������ӳ��ģʽ
    SetMapMode(aPBox->Canvas->Handle,MM_ANISOTROPIC);

    //��PBox��ʵ�ʿ���ӳ�䵽ָ���Ŀ���
    SetWindowExtEx(aPBox->Canvas->Handle,iMaxSize,iMaxSize,NULL);

    //�����ӿڣ�X�������ң�Y��������
    SetViewportExtEx(aPBox->Canvas->Handle,aPBox->Width,-aPBox->Height,NULL);

    //����ԭ���λ��
    SetWindowOrgEx(aPBox->Canvas->Handle,0,0,NULL);

    //�ӿ�ԭ���λ�ã�����PBox����һ��������ԭ���Ӧ
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
    if(aFile == NULL)  throw Exception("GetCLIFileHeader ����ΪNULL");

    //1������ļ�ͷ
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
   //��β
    aFile->Add("$$GEOMETRYEND");
}

//---------------------------------------------------------------------------
//Ԥ�������������Ϣ//��ʾ
void  ShowImageInfo(TImage* aImage, int aWidth,int aHeight,
                    MPolyLines*  aPaths,MHatchLines*  aLines,int aScale,bool bClear,bool bCurrent)
{
    SetViewPort(aImage,aWidth*aScale,aHeight*aScale,bClear);   //����ʾ����Ŵ󣬱��ڿ����

    aImage->Canvas->Pen->Width = 0.01;
    //���Ʊ߽�
    if(bCurrent)
       aImage->Canvas->Pen->Color = clRed;
    else
       aImage->Canvas->Pen->Color = clBlack;

    if(aPaths != NULL)
    {
        for(int i=0; i < aPaths->Count; i++)
        {
            MPolyLine*  aItemPath = aPaths->Items[i];                               //ȡ��һ���߽���
            if(aItemPath->PathType == 2)  //��·��
                    continue;

            M2DPoint*  AInitPoint = aItemPath->Points->Items[0];                            //ȡ����һ����

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

    for(int i=0; i < 4; i++)     //��
    {
         MPolyLine* aBase = new MPolyLine(NULL);
         aBase->Points->New2DPoint(-5,-5);                    //����
         aBase->Points->New2DPoint(5,-5);                   //����
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
//���������ļ�����������
void __fastcall TFormTestInstance::BitBtn4Click(TObject *Sender)
{
    CreateSampleFigureData(ComboBox1->ItemIndex);
}

void TFormTestInstance::CreateSampleFigureData(int iShapeType)
{
    String  aOutDir = ApplicationPath() + "\\TestModel";

    //���������
    int  iLayerNum = StrToInt(Edit1->Text.c_str());
    double fLayerThick = StrToFloat(Edit_LayerThick->Text);

    TStringList*  aFile = new TStringList;
    String  aDefaultFileName;
    TStringList*  aGeo;

    //1��CLI ͷ�ṹ
    GetCLIFileHeader(aFile,iLayerNum,iShapeType);

    //2��CLI ����ṹ
    if(iShapeType == 0)  //����
    {
        aDefaultFileName = "GeoRectangle";
        aGeo = CreateRectangleFigureToFile(iLayerNum,fLayerThick);
    }
    else if(iShapeType == 1)  //������
    {
        aDefaultFileName = "GeoTriangle";
        aGeo = CreateTriangleFigureToFile(iLayerNum,fLayerThick);
    }
    else if(iShapeType == 2)  //Բ��
    {
        aDefaultFileName = "GeoCircle";
        aGeo = CreateCircleFigureToFile(iLayerNum,fLayerThick,100);
    }
    else if(iShapeType == 3)  //����
    {
        aDefaultFileName = "GeoPartI";
        aGeo = CreatePart1FigureToFile(iLayerNum,fLayerThick,30);

    }
    else if(iShapeType == 4)  //4X4
    {
        aDefaultFileName = "Geo4X4Part";
        aGeo = Create4X4PartFigueToFile(iLayerNum,fLayerThick);
    }
    else if(iShapeType == 5)  //��ƽ��
    {
        aFile->Clear();

        GetCLIFileHeader(aFile,21,iShapeType);

        aDefaultFileName = "GY_TestFocus";

        double  dlayerThick = StrToFloat(Edit3->Text);
        double  aLineSpace = StrToFloat(Edit4->Text);
        aGeo = CreateTestFocusToFile(aLineSpace,dlayerThick);
    }


    //3��CLIβ�ṹ
    aFile->AddStrings(aGeo);
    OutCLITrailToFile(aFile);

    //4������
    SaveDialog1->InitialDir = aOutDir;
    SaveDialog1->DefaultExt = "cli";
    SaveDialog1->Filter = "��Ƭ�ļ�(*.cli)|*.cli";
    SaveDialog1->FileName = aDefaultFileName;
    if(SaveDialog1->Execute() == mrOk)
    {
        String  aFileName = SaveDialog1->FileName;
        aFile->SaveToFile(aFileName);
        ShowMessage("["+ComboBox1->Text + "]��Ƭ���������������!");
    }

    delete aFile;
}

//------------------------------------------------------------------------------
//����
//iLayers: ����
//iLayerThick: ���
TStringList*  TFormTestInstance::CreateRectangleFigureToFile(int iLayers,double iLayerThick)
{
    TStringList* aFileList = new TStringList;

    for(int i=0; i < iLayers; i++)
    {
        aFileList->Add("$$LAYER/" + FloatToStr(iLayerThick* (i+1)));

        String  aPre = "$$POLYLINE/1 1 ";
        //����
        int aPointNum = 5;   //����
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

    //1\ ��������
    int  XPosIndex[] = {10,9,8,7,6,5,4,3,2,1,0,-1,-2,-3,-4,-5,-6,-7,-8,-9,-10};
    double YStart = -10.0;
    double YEnd = 10.0;
    int  iLayerNum = 21;  //������

    MHatchLines*  aHatchLines = new MHatchLines();

    for(int i=0; i < iLayerNum; i++)
    {
       if( i == 10)  //�м��������߳���
            aHatchLines->NewHatchLine(0.0,YStart - 5.0,0.0,YEnd + 5.0);
       else
            aHatchLines->NewHatchLine(XPosIndex[i]*iLineSpace,YStart,XPosIndex[i]*iLineSpace,YEnd);
    }


    //2�����ɷֲ�����
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
    //������
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

//PointNum�� ��ɢ�ص���
TStringList*  TFormTestInstance::CreateCircleFigureToFile(int iLayers,double iLayerThick,int PointNum)
{
    TStringList* aFileList = new TStringList;

    for(int i=0; i < iLayers; i++)
    {
        aFileList->Add("$$LAYER/" + FloatToStr(iLayerThick* (i+1)));

        String  aPre = "$$POLYLINE/1 1 ";
        //Բ��
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
    //��������
    MPolyLine*  aPath = new MPolyLine(NULL);
    aPath->PathType = 0;                                                        //����߽�
    aPath->Points->New2DPoint(-20.0,-5.0);                   //����
    aPath->Points->New2DPoint(-10.0,-5.0);

    double  aRadio = 14.5;
    double  aEdgeNum = EdgeNum;
    double  aAngle = 88.0/aEdgeNum;  //ûһС��
    for(int i = aEdgeNum; i > 1; i--)
    {
        double  aX = aRadio* cos(degToRad(46 + aAngle* (i-1)));
        double  aY = aRadio* sin(degToRad(46 + aAngle* (i-1)))-15.5;
        aPath->Points->New2DPoint(aX,aY);
    }
    aPath->Points->New2DPoint(10.0,-5.0);                   //����
    aPath->Points->New2DPoint(20.0,-5.0);

    //�Գ���ȥ
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
    //��������
    MPolyLine*  aPath = new MPolyLine(NULL);
    aPath->PathType = 0;                                                        //����߽�
    aPath->Points->New2DPoint(0.0,0.0);                    //����
    aPath->Points->New2DPoint(45.0,0.0);                   //����
    aPath->Points->New2DPoint(45.0,43.8);
    aPath->Points->New2DPoint(0.0,43.8);
    aPath->Points->New2DPoint(0.0,0.0);

    TStringList* aFileList = new TStringList;

    for(int i=0; i < iLayers; i++)
    {
        aFileList->Add("$$LAYER/" + FloatToStr(iLayerThick* (i+1)));

        String  aPre = "$$POLYLINE/1 1 5 ";              //������
        String  aPoints = aPath->Points->OutPoints();
        aFileList->Add(aPre+aPoints);

        //����һ��
        double  aHeight[4] = {1+5,1+15+0.5, 1+0.5+1+25 , 1+0.5+1+0.3+35};
        for(int i=0; i < 4; i++)              //��
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

    int  aImageSize = aClientWidth > aClientHeight ?  aClientHeight: aClientWidth;  //ȡС��

    this->Image1->Width = aImageSize;
    this->Image1->Height = aImageSize;

    ComboBox1Change(NULL);
}
//---------------------------------------------------------------------------

void __fastcall TFormTestInstance::BitBtn1Click(TObject *Sender)
{
   //Ԥ��
   PreViewSampleFigureData(ComboBox1->ItemIndex);
}
//---------------------------------------------------------------------------
void  TFormTestInstance::PreViewSampleFigureData(int iShapeType)
{
    //1���������
    if(iShapeType == 0)  //����
    {
        Image1->Picture = NULL;
        CreateSingleRectangleFigure();

        double aWidth = Width >= Height ? Width: Height;

        ShowImageInfo(Image1,int(aWidth*1.1),int(aWidth*1.1),fPaths,NULL,1);
        return;
    }
    else if(iShapeType == 1)  //������
    {
        Image1->Picture = NULL;
        CreateSingleTriangleFigure();
    }
    else if(iShapeType == 2)  //Բ��
    {
        Image1->Picture = NULL;
        CreateSingleCircleFigure(100);
    }
    else if(iShapeType == 3)  //����
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
    else if(iShapeType == 5) //��ƽ��
    {
        fPaths->Clear();

        Image1->Picture = NULL;
        Image1->Picture->LoadFromFile(ApplicationPath() + "\\system\\TestFocus.jpg");
        return;
    }

    //2��
    ShowImageInfo(Image1,100,100,fPaths,NULL,100);
}

void  TFormTestInstance::CreateSingleRectangleFigure()
{
    String  aPre = "$$POLYLINE/1 1 ";
    //����
    int aPointNum = 5;   //����
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
    //Բ��
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
    //��������
    MPolyLine*  aPath = new MPolyLine(NULL);
    aPath->PathType = 0;                                                        //����߽�
    aPath->Points->New2DPoint(-20.0,-5.0);                   //����
    aPath->Points->New2DPoint(-10.0,-5.0);

    double  aRadio = 14.5;
    double  aEdgeNum = EdgeNum;
    double  aAngle = 88.0/aEdgeNum;  //ûһС��
    for(int i = aEdgeNum; i > 1; i--)
    {
        double  aX = aRadio* cos(degToRad(46 + aAngle* (i-1)));
        double  aY = aRadio* sin(degToRad(46 + aAngle* (i-1)))-15.5;
        aPath->Points->New2DPoint(aX,aY);
    }
    aPath->Points->New2DPoint(10.0,-5.0);                   //����
    aPath->Points->New2DPoint(20.0,-5.0);

    //�Գ���ȥ
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
    if(ComboBox1->ItemIndex == 5) //��ƽ��
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

