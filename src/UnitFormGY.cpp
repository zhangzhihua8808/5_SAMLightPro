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
//----------------------------����----------------------------------------------
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

     throw Exception("����ĽǶȸ�ʽ����!");
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

     //�����
     for(int i=0; i < aRowNum ; i++)
     {
         int  aSX = aWidth/2.0*(-1);
         int  aSY = aHeight/2.0 - 10*(i+1);
         int  aEX = aWidth/2.0;
         int  aEY = aSY;

         aHatchLines->NewHatchLine(aSX,aSY,aEX,aEY);
     }

     //�����
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
    //1.1 ��ȡ�ļ�
    String  aOutDir = ApplicationPath() + "\\TestModel";

    //����ģ�͵�List��
    OpenDialog1->Title = "ָ��������Ƭ�ļ�";
    OpenDialog1->Filter = "������Ƭ�ļ�(*.cli)|*.cli";
    OpenDialog1->InitialDir = aOutDir;
    if(OpenDialog1->Execute() != mrOk)   return;

    String  aFileName = OpenDialog1->FileName;
    fCurrentOpenCliFile = aFileName;

    //2�����ص�TreeView��
    //2.1 �������ڵ�
    TreeView1->Items->Clear();
    Project->MainItems->Clear();
    fCurrTreeNode= NULL;
    Image1->Canvas->FillRect(Image1->Canvas->ClipRect);  //��Image;

    InsertCatalogNode(NULL, ExtractFileName(aFileName),"0");  //���ڵ�

    gError->Warn1("���ڼ�����Ƭ����");
    Project->LoadLayerDatasFromCLiFile(aFileName);   //���ص�������
    gError->Warn1("������Ƭ����--------���");

    //���,����,����
    if(Project->MainItems->Count > 1)
          Edit_LayerThick->Text = Project->MainItems->Items[1]->AbsoluteHeight;
    else
          Edit_LayerThick->Text = "";
    Edit1->Text =  IntToStr(TreeView1->Items->Count - 1);

    ComboBox1->ItemIndex = Project->PartID;
}

//---------------------------------------------------------------------------
//����Ŀ¼�ڵ�
MLayerDataTreeNode*  TFormGYDesign::InsertCatalogNode(MLayerDataTreeNode*  aParentDM,
                                          String aNodeName,String aType)
{
    MTreeNodes_LayerData*  aMainItems = Project->MainItems;
    //����һ��ID
    int aMaxID = StrToInt(aMainItems->MaxID);
    aMainItems->MaxID = IntToStr(aMaxID + 1);

    MLayerDataTreeNode* aItem = aMainItems->NewLayerData_AT(IntToStr(aMaxID),
                      aNodeName,aType,"",0,"","");
    //��
    TTreeView*  aTree = TreeView1;
    if(aParentDM == NULL) //���ڵ�
    {
         TTreeNode* aNewNode = aTree->Items->Add(NULL,aItem->NodeName);
         aNewNode->Data = (void*)aItem;
         aNewNode->ImageIndex = 0;
         aNewNode->SelectedIndex = 0;
         aItem->TreeNode = aNewNode;
         aItem->ParentName = "";
    }
    else //�ӽڵ�
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

//���ɹ�����Ƭ�ļ�
void __fastcall TFormGYDesign::BitBtn5Click(TObject *Sender)
{
    if(TreeView1->Items->Count < 2)
           throw Exception("���ȴ������ļ�");

    OutCliFileToFile(StrToInt(Edit1->Text));

    DoClickTreeNode(GetSelectedLayerDataItem(TreeView1));
}

//---------------------------------------------------------------------------
String  TFormGYDesign::GetDefaultGYName(int  iShapeType)
{
    String  aDefaultFileName = "";
    //2��CLI ����ṹ
    if(iShapeType == 0)  //����
    {
        aDefaultFileName = "GY_GeoRectangle";
    }
    else if(iShapeType == 1)  //������
    {
        aDefaultFileName = "GY_GeoTriangle";
    }
    else if(iShapeType == 2)  //Բ��
    {
        aDefaultFileName = "GY_GeoCircle";
    }
    else if(iShapeType == 3)  //����
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

     //�ļ�ͷ
     GetCLIFileHeader(aCLIFile,nLayerNum,Project->PartID);     //�ļ�ͷ,����

     if(Angle == 0 || Angle == 90) //��Ȼ�90�ȷ�ʽ
     {
         int  aAngle= Angle;
         for(int i=0; i < nLayerNum; i++)
         {
              //����·��
              MPolyLines*  fPaths = Project->MainItems->Items[i+1]->PolyLines;
              LoadModelPaths(fPaths);  //����ƫ��·�����������·��

              MPolyLines*  aVirtualEdges = GetScanEdges(fPaths);  //������·��

              MHatchLines* fHatchLines = Project->MainItems->Items[i+1]->HatchLines;
              CalculateHatchLines(aVirtualEdges,aAngle,fHatchLines);

              OutGYGeometryToFile(aCLIFile,i+1,fPaths,fHatchLines);   //���һ��

              aAngle += 90;            //�ı����Ƕ�
              aAngle = aAngle%180;
         }

     }
     else  //��������ʽ
     {
         int  Angle = 13;
         for(int i=0; i < nLayerNum; i++) //����
         {
             //����·��
             MPolyLines*  fPaths = Project->MainItems->Items[i+1]->PolyLines;
             LoadModelPaths(fPaths);  //����ƫ��·�����������·��

             MPolyLines*  aVirtualEdges = GetScanEdges(fPaths);  //������·��

             MHatchLines* fHatchLines = Project->MainItems->Items[i+1]->HatchLines;
             CalculateHatchLines(aVirtualEdges,Angle,fHatchLines);

             OutGYGeometryToFile(aCLIFile,i+1,fPaths,fHatchLines);   //���һ��

             Angle += 13;            //�ı����Ƕ�
             Angle = Angle%90;
         }
     }

    OutCLITrailToFile(aCLIFile);

         //4������
    SaveDialog1->InitialDir = aOutDir;
    SaveDialog1->DefaultExt = "cli";
    SaveDialog1->Filter = "������Ƭ�ļ�(*.cli)|*.cli";
    SaveDialog1->FileName = GetDefaultGYName(Project->PartID);
    if(SaveDialog1->Execute() == mrOk)
    {
        String  aFileName = SaveDialog1->FileName;
        aCLIFile->SaveToFile(aFileName);
        ShowMessage("["+ComboBox1->Text + "]��Ƭ���ռ��������������!");
    }

    delete aCLIFile;
}

void  TFormGYDesign::OutGYGeometryToFile(TStringList* aFile,int aLayerNo,
                     MPolyLines*  fPaths,MHatchLines* fHatchLines,bool bHatchLine_Pre)
{
     //2�����ÿ����Ϣ
    String  aStr;

    aStr.sprintf("$$LAYER/%.3f ",LayerThick*aLayerNo);
    aFile->Add(aStr);

    if(bHatchLine_Pre) //�������
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


//aPath: [in] �����·��
//aPaths [out] �����·��
//aNum: �߽����
//aLimitedDis: �߽�֮��ľ��룬
void TFormGYDesign::PathOffset(const TPath& aPath,TPaths& aPaths,int aNum,double aLimitedDis)
{
    if(aNum < 2) return;

    aPaths.set_length(aNum-1);
    TClipperOffset*  co = new TClipperOffset(0.1,0.25);
    TPaths solution;
    for(int i=1; i < aNum; i++)
    {
        co->AddPath(aPath,jtMiter,etClosedPolygon);
        co->Execute(solution, aLimitedDis);     //���ڲ�����

        aPaths[i-1] = solution[0];
    }
}


void  TFormGYDesign::LoadModelPaths(MPolyLines*  fPaths)
{
    if(fPaths->Count == 0) return;

    int iNum = fPaths->Count;
    if(iNum == 1) //ֻ��1��������
    {
        MPolyLine* aItem = fPaths->Items[0];                                    //���е�һ������

        int aScale = 1;
        //��ת��
        TPath  aPath;
        aItem->PolyLineToPath(aPath,aScale);
        TPaths  aOffPaths;

        //����߽�
        PathOffset(aPath,aOffPaths,LimitedNum,aScale*LimitedDis*(-1));
        fPaths->AddPaths(aOffPaths,aScale,1);

        //��ı߽�
        PathOffset(aPath,aOffPaths,2,OffsetDis*aScale);
        fPaths->AddPaths(aOffPaths,aScale,2);

        /*
         MPolyLine* aItem = fPaths->Items[0];                                    //���е�һ������

        //��ת��
        TPath  aPath;
        aItem->PolyLineToPath(aPath,1000);
        TPaths  aOffPaths;

        //����߽�
        PathOffset(aPath,aOffPaths,LimitedNum,1000*LimitedDis*(-1));
        fPaths->AddPaths(aOffPaths,1000,1);

        //��ı߽�
        PathOffset(aPath,aOffPaths,2,OffsetDis*1000);
        fPaths->AddPaths(aOffPaths,1000,2);
        */
     }
     else  //��������ߣ���һ��������������������Ϊ������
     {
        for(int i=0; i < iNum; i++)
        {
            int aScale = 1;
            MPolyLine* aItem = fPaths->Items[i];
            //��ת��
            TPath  aPath;
            aItem->PolyLineToPath(aPath,aScale);
            TPaths  aOffPaths;

            if(i==0) //����߽�
            {
                PathOffset(aPath,aOffPaths,LimitedNum,aScale*LimitedDis*(-1));
                fPaths->AddPaths(aOffPaths,1000,1);

                //����ߵ�ƫ��
                PathOffset(aPath,aOffPaths,2,OffsetDis*aScale);
                fPaths->AddPaths(aOffPaths,aScale,2);
            }
            else //�ڲ���Ҫ������
            {
                PathOffset(aPath,aOffPaths,2,LimitedDis*aScale);
                fPaths->AddPaths(aOffPaths,aScale,1);

                //����ߵ�ƫ��
                PathOffset(aPath,aOffPaths,2,OffsetDis*(-1.0*aScale));
                fPaths->AddPaths(aOffPaths,aScale,2);
            }
        }
    }
}

float TFormGYDesign::GetDistanceBetweenScanLines(float aDistanceLines,int aAngle)
{
    int aTheta = aAngle % 90;

    if( aAngle - 90 == 0 || aTheta == 0)  //��ֱ��ˮƽ
             return aDistanceLines;

    return aDistanceLines/cos(degToRad(aTheta));
}


//------------------------------------------------------------------------------
//aAngle: �Ƕ�
//������ƹ��̣��������ģ�͵����Bmax��Bmin�ĺͣ�Ȼ�����ɨ���ߵĽؾ࣬�Ӷ����ɨ���ߵĸ�����
//Ȼ�����ÿһ��ɨ���ߣ����б߽������㣬Ȼ��Խ��������������մ�������ʣ�ż��̨�ʵ�˳�������
void  TFormGYDesign::CalculateHatchLines(MPolyLines* aEdges,int aAngle,MHatchLines* fHatchLines)
{
    if(aEdges == NULL || aEdges->Count == 0)  return;

    fHatchLines->Clear();  //��������

    //�����������ؾ�ķ�Χ;ɨ���߽ؾ�;���ؾ�;
    double aBmax;
    float aHeightOfJieJu = GetDistanceBmax2Bmin(aEdges->Items[0],aAngle,aBmax);
    float aDeltaJieJu = GetDistanceBetweenScanLines(DistanceLines,aAngle);
    int   aLineCount = Floor(aHeightOfJieJu / aDeltaJieJu);   //�ߵ�����

    M2DPoints*  aIntPoints = new M2DPoints();

    for(int i=0; i < aLineCount; i++)
    {
        double aB = aBmax - aDeltaJieJu*(i+1);                                  //�������¼���ؾ�
        //if Angle == 90-----,  else ----------
        double aK = GetLine_K(aAngle);                                          //б��

        //ÿһ��ɨ���������еı���
        GetIntPointsFromEdges(aIntPoints,aB,aK,aEdges);

        if(aIntPoints->Count % 2 == 0) //ż��
        {
            if(fabs(aK-1e10)<=1e-5)   //����,������������
            {
                 SortList(aIntPoints, 1);
            }
            else   //������������
            {
                 SortList(aIntPoints, 0);
            }

            for(int i=0; i < aIntPoints->Count; )
            {
                M2DPoint*  aFirst = aIntPoints->Items[i];   //����
                M2DPoint*  aSecond = aIntPoints->Items[i+1]; //ż��
                i = i+2;
                fHatchLines->NewHatchLine(aFirst->X,aFirst->Y,aSecond->X,aSecond->Y);
            }
            aIntPoints->Clear();
        }
        else
        {
            aIntPoints->Clear();
            throw Exception("�ҵ�����������");
        }
    }
}

//��������
//aBase = 0: X, 1:Y
void  TFormGYDesign::SortList(M2DPoints*  aSortList, int aBase)
{
    int  aCount = aSortList->Count;
    for(int limit = aCount - 1; limit>0; limit--)  //ѭ��������1 2  3 4 5
    {
        for(int i = 0; i < limit; i++)
        {
            if(aBase == 0)    //����X����Ƚ�
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
            else  //����Y����Ƚ�
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

//�����������������еĽ���
void  TFormGYDesign::GetIntPointsFromEdges(M2DPoints* aIntPoints,double aB,
                             double aK,MPolyLines* aEdges)
{
      M2DPoint* aPoint = new M2DPoint(NULL);

      for(int i=0; i < aEdges->Count; i++)   //������
      {
           //ȡ��һ��
           MPolyLine*  aItem = aEdges->Items[i];
           int  aEdgeNum = aItem->Points->Count - 1;  //��

           for(int j=0; j < aEdgeNum; j++)  //����
           {
               //ȡ��һ����
               double  aSX = aItem->Points->Items[j]->X;
               double  aSY = aItem->Points->Items[j]->Y;
               double  aEX = aItem->Points->Items[(j+1)%aEdgeNum]->X;
               double  aEY = aItem->Points->Items[(j+1)%aEdgeNum]->Y;

               int iRet = GetLine2Line(aK,aB,aSX,aSY,aEX,aEY,aPoint);      //��������ߵĽ���

               if(iRet == 1) //�н���
               {
                   aIntPoints->New2DPoint(aPoint->X,aPoint->Y);
               }
           }
      }

      delete aPoint;
}

//�������ߵĽ��㣻 ����ֵ(0: �޽��㣬1���н���
int  TFormGYDesign::GetLine2Line(double aK,double aB,
                  double aSX,double aSY,double aEX,double aEY,M2DPoint*  APoint)
{
    //��֪б�ʣ�B,  ����ֱ�ߵĽ��� (0,aB),aK  ;  aSX,aSY,aEX,aEY
    //ֱ�߷���                     P0+ sD0  , P1 + tD1
    if(fabs(aSX - aEX) <= 1e-5)  //����
    {
        if(fabs(aK-1e10)<=1e-5)   //����
        {
            return 0;
        }

        //��Ч��Χ
        double  aYmax = aSY > aEY ? aSY: aEY;
        double  aYmin = aSY > aEY ? aEY: aSY;
        double  aIntY = aK * aSX + aB;
        if(aIntY > aYmin && aIntY < aYmax)   //�ҵ�һ��
        {
            APoint->X = aSX;
            APoint->Y = aIntY;

            return 1;
        }
        return 0;
    }
    else  if(fabs(aSY - aEY) <= 1e-5)   //����
    {
        if(aK == 0.0) //����
        {
            return 0;
        }

        double  aXmax = aSX > aEX ? aSX: aEX;
        double  aXmin = aSX > aEX ? aEX: aSX;

        double aIntX;
        if(fabs(aK-1e10)<=1e-5)   //����
        {
            aIntX = aB;
        }
        else
        {
            aIntX = (aEY - aB) /aK;
        }

        if(aIntX > aXmin && aIntX < aXmax)   //�ҵ�һ��
        {
            APoint->X = aIntX;
            APoint->Y = aEY;

            return 1;
        }
        return 0;
    }
    else //б��
    {
        double aLineK2 = (aEY - aSY)/(aEX - aSX);
        double aIntX;
        if(fabs(aLineK2 - aK) < 1e-5) //ƽ��
        {
            return 0;  //���ཻ
        }
        else if(fabs(aK-1e10)<=1e-5)   //����
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

        if(aIntY >= aYmin && aIntY <= aYmax)   //�ҵ�һ��
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

    if( aTheta - 90 == 0)  //��ֱ
          return  1e10;

    aTheta = aAngle % 90;
    return tan(degToRad(aTheta));
}

//------------------------------------------------------------------------------
//�������£����������˳�����
float  TFormGYDesign::GetDistanceBmax2Bmin(MPolyLine* aEdges,int aAngle,double& Bmax)
{
    int aTheta = aAngle % 90;   //0~90֮��

    if(InstanceType == 0 || InstanceType == 3 || InstanceType == 4) //����
    {
        if(aTheta == 0 && aAngle == 90) //��ֱ
        {
            Bmax = aEdges->Points->MaxX;
            return fabs(aEdges->Points->MaxX - aEdges->Points->MinX);
        }
        else if(aTheta == 0) //ˮƽ
        {
            Bmax = aEdges->Points->MaxY;
            return fabs(aEdges->Points->MaxY - aEdges->Points->MinY);
        }
        else  //�����Ƕ�
        {
            Bmax = aEdges->Points->MaxY - tan(degToRad(aTheta))* aEdges->Points->MinX;
            float Bmin = aEdges->Points->MinY - tan(degToRad(aTheta))* aEdges->Points->MaxX;

            return fabs(Bmax - Bmin);
        }
    }
    else if(InstanceType == 1) //������
    {
        if(aTheta == 0 && aAngle == 90) //��ֱ
        {
            Bmax = aEdges->Points->MaxX;
            return fabs(aEdges->Points->MaxX - aEdges->Points->MinX);
        }
        else if(aTheta == 0) //ˮƽ
        {
            Bmax = aEdges->Points->MaxY;
            return fabs(aEdges->Points->MaxY - aEdges->Points->MinY);
        }
        else  //�����Ƕ�
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
    else if(InstanceType == 2) //Բ��
    {
        if(aTheta == 0 && aAngle == 90) //��ֱ
        {
            Bmax = aEdges->Points->MaxX;
            return fabs(aEdges->Points->MaxX - aEdges->Points->MinX);
        }
        else if(aTheta == 0) //ˮƽ
        {
            Bmax = aEdges->Points->MaxY;
            return fabs(aEdges->Points->MaxY - aEdges->Points->MinY);
        }
        else  //�����Ƕ�
        {
            double  aHeight = aEdges->Points->MaxX / cos(degToRad(aTheta));
            Bmax = aHeight;

            return fabs(2*Bmax);
        }
    }
    else
        throw Exception("δʶ�������");
}

//------------------------------------------------------------------------------
void __fastcall TFormGYDesign::TreeView1Click(TObject *Sender)
{
    DoClickTreeNode(GetSelectedLayerDataItem(TreeView1));
}
//---------------------------------------------------------------------------
//��ʾ
void  TFormGYDesign::DoClickTreeNode(MLayerDataTreeNode* aDMNode)
{
    fCurrTreeNode = aDMNode;

    if(aDMNode == NULL)  return;
    if(aDMNode->Type == "0")  return;

    ShowImageInfo(this->Image1, 1.1*(aDMNode->MaxX - aDMNode->MinX), 1.1*(aDMNode->MaxY - aDMNode->MinY),
              aDMNode->PolyLines,aDMNode->HatchLines,1);
}

//��ӡ�Ű�
void __fastcall TFormGYDesign::BitBtn3Click(TObject *Sender)
{
    String  aOutDir = ApplicationPath() + "\\TestModel";

    //����ģ�͵�List��
    OpenDialog1->Title = "ָ��������Ƭ�ļ�";
    OpenDialog1->Filter = "������Ƭ�ļ�(*.cli)|*.cli";
    OpenDialog1->InitialDir = aOutDir;
    OpenDialog1->Options += TOpenOptions()<<ofAllowMultiSelect;
    if(OpenDialog1->Execute() != mrOk)   return;

    TStrings*  aFileList = OpenDialog1->Files;    //��ȡ�ļ��б�
    fProjects->LoadPartProjectsFromFileStrings(aFileList);
    fProjects->AddToListBox(this->ListBox1);

    DrawBackImage();
    DrawImage(ListBox1,true);
}
//---------------------------------------------------------------------------
//�����˱���
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
        if(bAll) //ȫ��ʾ���
        {
            DrawImage((MPartProject*)aListBox->Items->Objects[i],false,true);
        }
        else
        {
          if(i == aListBox->ItemIndex)    //��ǰѡ�е�AMProject
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

     //����һ����Χ��
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

     if(aItem != CurrentProject)  //�л���
     {
         if(CurrentProject == NULL)  //��һ�ε��
         {
             CurrentProject = aItem;
             if(CBox_Pens->Items->Count > 0)
             {
                 CBox_Pens->ItemIndex = 0;
                 DoComboBoxChange(GetSelectedLaserPen(CBox_Pens));
             }
         }
         else  //����
         {
             //����ԭ����
             CurrentProject->LaserPen = GetSelectedLaserPen(CBox_Pens);   //����

             //�������ڵ�
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

     DrawBackImage();  //�ػ�����
     DrawImage(ListBox1);
}

//�����С
void __fastcall TFormGYDesign::FormShow(TObject *Sender)
{
    int  aClientWidth = this->ClientWidth;
    int  aClientHeight = this->ClientHeight;

    int  aImageSize = aClientWidth > aClientHeight ?  aClientHeight: aClientWidth;  //ȡС��

    this->Image1->Width = aImageSize;
    this->Image1->Height = aImageSize;

    //����Pen��Ϣ
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
         throw Exception("����ѡ��Ҫ�ƶ���Part");

    //ƽ�Ʊ���
    //BitBtn4->Enabled = false;

    DoPartMove(GetSelectedPartProject(ListBox1),
                    StrToFloat(this->EditMoveX->Text),StrToFloat(this->EditMoveY->Text));

    this->EditMoveX->Text = "0";
    this->EditMoveY->Text = "0";
    //BitBtn4->Enabled = true;

    //ˢ�µ�ǰ
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
        throw Exception("����ѡ��Ҫ�ƶ������");
    }

    aItem->DoMovePart(aMoveX,aMoveY);
}

//------------------------------------------------------------------------------
void __fastcall TFormGYDesign::BitBtn6Click(TObject *Sender)
{
    String  aOutDir = ApplicationPath() + "\\TestModel";

    //���ձ���
    //���ҵ����㣬Ȼ��ö��ÿһ�������
    int  aMaxLayerNum = MaxLayerNum;
    if(aMaxLayerNum < 0)  throw Exception("���Ƚ����Ű棬Ȼ���ٽ��й������");

    double  aMinLayerThick = MinLayerThick;

    TStringList* aFileList = new TStringList;
    GetCLIFileHeader(aFileList,aMaxLayerNum,-1);

    for(int i=0; i < aMaxLayerNum; i++)
    {
        TStringList*  aLayers = OutputMultiPartByLayer(i,aMinLayerThick);  //���һ��
        aFileList->AddStrings(aLayers);
    }

    OutCLITrailToFile(aFileList);

    //4������
    SaveDialog1->InitialDir = aOutDir;
    SaveDialog1->DefaultExt = "mix";
    SaveDialog1->Filter = "������Ƭ�Ű��ļ�(*.mix)|*.mix";
    SaveDialog1->FileName = "MultiPart_GY_CLI";
    if(SaveDialog1->Execute() == mrOk)
    {
        String  aFileName = SaveDialog1->FileName;
        aFileList->SaveToFile(aFileName);
        ShowMessage("������Ƭ�Ű��ļ��������!" + aFileName);
    }

    delete aFileList;
}
//---------------------------------------------------------------------------
//Ҫ�󣺺��Ϊ������
int TFormGYDesign::readMaxLayerNum()
{
    return (int)(PartMaxHeight/MinLayerThick);
}

double  TFormGYDesign::readPartMaxHeight()
{
    if(ListBox1->Count == 0) throw Exception("û�м������");

    double  aMax = -MAXFLOAT;
    for(int i=0; i < ListBox1->Count; i++)
    {
        MPartProject* aItem = (MPartProject*)ListBox1->Items->Objects[i];
        if(aItem->MainItems->Count <= 1)  throw Exception("��ȡģ����Ϣʧ��:readPartMaxHeight");

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

//iLayers: ����0��
/* ��ǰ��
TStringList* TFormGYDesign::OutputMultiPartByLayer(int iLayers,double iLayerThick)
{
    TStringList* aFileList = new TStringList;

    for(int i=0; i < ListBox1->Count; i++)
    {
        MAMProject* aItem = (MAMProject*)ListBox1->Items->Objects[i];

        if(i==0)  //��һ��
        {
           aFileList->Add("$$LAYER/" + FloatToStr(iLayerThick* (iLayers+1)));
        }

        if(iLayers < aItem->MainItems->Count)
        {
           MLayerDataTreeNode* aLayerItem = aItem->MainItems->Items[iLayers];

           if(ComboBox2->ItemIndex == 0) //��ɨ����
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

//iLayers: ����0��,���һ�����Ϣ
TStringList* TFormGYDesign::OutputMultiPartByLayer(int iLayers,double iLayerThick)
{
    //��������
    double  aCurrentHeight = iLayerThick* (iLayers+1);
    //�ұȽϽӽ����Ǹ���

    //�������Part�ĸ�����ȵ���Ϣ
    TStringList* aFileList = new TStringList;

    //���
    aFileList->Add("$$LAYER/" + FloatToStr(iLayerThick* (iLayers+1)));

    for(int i=0; i < ListBox1->Count; i++)
    {
        MPartProject* aItem = (MPartProject*)ListBox1->Items->Objects[i];

        MLayerDataTreeNode* aLayerItem =  aItem->FindLayerDataTreeNodeByHeight(aCurrentHeight);
        if( aLayerItem == NULL)   //û���ҵ�
                continue;

        aFileList->Add("Power="+aItem->LaserPen->PenPower);
        aFileList->Add("Speed="+aItem->LaserPen->PenSpeed);

        if(ComboBox2->ItemIndex == 0) //��ɨ����
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
//����
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
         throw Exception("����ѡ����Ҫ�Ƴ����ļ�!!!");
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

//--------------------����ʵ�����-----------------------------------------
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
    OpenDialog1->Filter = "������Ƭ�Ű��ļ�(*.dat)|*.dat";
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

        //���
        aListGroup = splitToStrings(aFileLine,",");  //���

        String  aModelFile = Get_ListItemStr_ByName( aListGroup, "File", "=", "unKnown");   //δ֪����
        String  aTrueModelFile = aPath + aModelFile;

        String  aMovX = Get_ListItemStr_ByName( aListGroup, "MovX", "=", "unKnown" );
        String  aMovY = Get_ListItemStr_ByName( aListGroup, "MovY", "=", "unKnown");   //NodeName
        String  aPenIndex = Get_ListItemStr_ByName( aListGroup, "PenIndex", "=", "unKnown");

        //���ص��ڲ�
        MPartProject* aItem = fProjects->NewPartProject();      //����һ������
        aItem->LoadGYInfoFromFile(aTrueModelFile);

        //���ñ�
        CBox_Pens->ItemIndex = StrToInt(aPenIndex) - 1;
        aItem->LaserPen = GetSelectedLaserPen(CBox_Pens);

        //ƽ��
        aItem->DoMovePart(StrToFloat(aMovX),StrToFloat(aMovY));
    }

    fProjects->AddToListBox(this->ListBox1,true);

    delete aListGroup;
    delete aModels;

    DrawBackImage();
    DrawImage(ListBox1,true);

    //����
    //BitBtn6Click(NULL);
}
//---------------------------------------------------------------------------

