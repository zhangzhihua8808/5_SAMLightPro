//---------------------------------------------------------------------------

#ifndef UnitFormGYH
#define UnitFormGYH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <ImgList.hpp>

#include "clipper.hpp"
#include <Menus.hpp>
using namespace Clipper;


class MPartProjects;
class MPartProject;
class MLayerDataTreeNode;
class MPolyLines;
class MHatchLines;
class MPolyLine;
class M2DPoints;
class M2DPoint;
class MLaserPen;
//---------------------------------------------------------------------------
class TFormGYDesign : public TForm
{
__published:	// IDE-managed Components
        TToolBar *ToolBar1;
        TBitBtn *BitBtn2;
        TToolButton *ToolButton1;
        TBitBtn *BitBtn5;
        TToolButton *ToolButton2;
        TBitBtn *BitBtn3;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TPanel *Panel1;
        TGroupBox *GroupBox1;
        TLabel *Label5;
        TLabel *Label6;
        TEdit *EditLimitedDis;
        TEdit *EditLimitedNum;
        TGroupBox *GroupBox3;
        TLabel *Label7;
        TLabel *Label8;
        TLabel *Label9;
        TEdit *EditLinesDis;
        TEdit *EditLinesOffset;
        TComboBox *CBoxAngle;
        TGroupBox *GroupBox4;
        TLabel *Label11;
        TEdit *Edit_LayerThick;
        TComboBox *ComboBox2;
        TEdit *Edit1;
        TTabSheet *TabSheet2;
        TPanel *Panel2;
        TGroupBox *GroupBox5;
        TLabel *Label12;
        TLabel *Label13;
        TEdit *EditMoveX;
        TEdit *EditMoveY;
        TListBox *ListBox1;
        TBitBtn *OpenFile;
        TOpenDialog *OpenDialog1;
        TTabSheet *TabSheet3;
        TTreeView *TreeView1;
        TImageList *ImageList_TreeNode;
        TLabel *Label10;
        TLabel *Label1;
        TComboBox *ComboBox1;
        TLabel *Label2;
        TSaveDialog *SaveDialog1;
        TSplitter *Splitter1;
        TImage *Image1;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn4;
        TBitBtn *BitBtn6;
        TPopupMenu *PopupMenu1;
        TMenuItem *N1;
        TMenuItem *N2;
        TStatusBar *StatusBar1;
        TGroupBox *GroupBox2;
        TLabel *Label29;
        TLabel *Label33;
        TEdit *Edit2;
        TEdit *Edit11;
        TButton *Button1;
        TComboBox *CBox_Pens;
        TLabel *Label3;
        TButton *Button2;
        void __fastcall OpenFileClick(TObject *Sender);
        void __fastcall BitBtn5Click(TObject *Sender);
        void __fastcall TreeView1Click(TObject *Sender);
        void __fastcall BitBtn3Click(TObject *Sender);
        void __fastcall ListBox1Click(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall BitBtn4Click(TObject *Sender);
        void __fastcall BitBtn6Click(TObject *Sender);
        void __fastcall N1Click(TObject *Sender);
        void __fastcall N2Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall ListBox1DragDrop(TObject *Sender, TObject *Source,
          int X, int Y);
        void __fastcall ListBox1DragOver(TObject *Sender, TObject *Source,
          int X, int Y, TDragState State, bool &Accept);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall CBox_PensChange(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormGYDesign(TComponent* Owner);


     protected:
        int  readInstanceType();
        void writeInstanceType(int aType);

        double readLimitedDis();
        void writeLimitedDis(double aLimitedDis);

        int readLimitedNum();
        void writeLimitedNum(int aLimitedNum);

        double readOffsetDis();
        void writeOffsetDis(double aOffsetDis);

        double readDistanceLines();
        void writeDistanceLines(double aDistanceLines);

         int   readAngle();
        void  writeAngle(int aAngle);

        String  GetDefaultGYName(int  iShapeType);

        double readLayerThick();
        void   writeLayerThick(double aLayerThick);

        int   readMaxLayerNum();
        double  readMinLayerThick();
        double  readPartMaxHeight();
     public:
        __property  double LimitedDis = {read=readLimitedDis,write=writeLimitedDis};
        __property  int LimitedNum = {read=readLimitedNum,write=writeLimitedNum};
        __property  double OffsetDis = {read=readOffsetDis,write=writeOffsetDis};
        __property  double DistanceLines = {read=readDistanceLines,write=writeDistanceLines};
        __property  int Angle = {read=readAngle,write=writeAngle};
        __property  int  InstanceType = {read=readInstanceType,write=writeInstanceType};
        __property  double LayerThick = {read=readLayerThick,write=writeLayerThick};
        __property  int   MaxLayerNum = {read=readMaxLayerNum};     //最大层数
        __property  double  MinLayerThick={read=readMinLayerThick};   //最小层厚
        __property  double  PartMaxHeight = {read=readPartMaxHeight};


        //变量
        MPartProject*  Project;                                                 //用于工艺
        MPartProjects* fProjects;                                               //用于排版
        MPartProject*  CurrentProject;   //用于排版


        String   fCurrentOpenCliFile;
        MLayerDataTreeNode* fCurrTreeNode;
        String  WindowRangel;
        String  WorkArea;

        

        void  Init();
        MLayerDataTreeNode*  InsertCatalogNode(MLayerDataTreeNode*  aParentDM,
                                          String aNodeName,String aType);

        void  OutCliFileToFile(int nLayerNum);

        //MPolyLines*  fPaths;
        //MHatchLines* fHatchLines;

        void  LoadModelPaths(MPolyLines*  fPaths);
        void  PathOffset(const TPath& aPath,TPaths& aPaths,int aNum,double aLimitedDis);
        MPolyLines*  GetScanEdges(MPolyLines*  fPaths);
        void  CalculateHatchLines(MPolyLines* aEdges,int aAngle,MHatchLines* fHatchLines);
        float  GetDistanceBmax2Bmin(MPolyLine* aEdges,int aAngle,double& Bmax);
        float GetDistanceBetweenScanLines(float aDistanceLines,int aAngle);
        float GetLine_K(int aAngle);
        void  GetIntPointsFromEdges(M2DPoints* aIntPoints,double aB,
                             double aK,MPolyLines* aEdges);
        void  SortList(M2DPoints*  aSortList, int aBase);
        int  GetLine2Line(double aK,double aB,double aSX,double aSY,double aEX,
                                      double aEY,M2DPoint*  APoint);
        void OutGYGeometryToFile(TStringList* aFile,int aLayerNo,MPolyLines*  fPaths,
                        MHatchLines* fHatchLines,bool bHatchLine_Pre=true);

        void  DrawGridLine(int aViewPortX,int aViewPortY,int aWidth,int aHeight);
        void  DoClickTreeNode(MLayerDataTreeNode* aDMNode);

        void  OnClickListBox(MPartProject* aItem);
        void  DrawBackImage();
        void  DrawImage(TListBox* aListBox,bool bAll=false);
        void  DrawImage(MPartProject* aItem,bool bClearBackImage,bool  bCurrent);
        void  DoPartMove(MPartProject* aItem,double aMoveX,double aMoveY);
        TStringList* OutputMultiPartByLayer(int iLayers,double iLayerThick);

        void  DoComboBoxChange(MLaserPen* aPen);

};
//---------------------------------------------------------------------------
extern PACKAGE TFormGYDesign *FormGYDesign;
//---------------------------------------------------------------------------
#endif
