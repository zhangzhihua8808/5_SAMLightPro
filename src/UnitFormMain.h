//---------------------------------------------------------------------------

#ifndef UnitFormMainH
#define UnitFormMainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
#include <ToolWin.hpp>
#include <ImgList.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <Buttons.hpp>
#include <CheckLst.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <OleCtrls.hpp>
#include <Dialogs.hpp>

#include <stdio.h>


class MAMProject;
class MLayerDataTreeNode;
class CGLView;
class MConfigVars;
class MLaserPen;
class MPolyLines;

enum RunState
{
    ready,
    running,
    pause,
    stop
};

//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// IDE-managed Components
        TMainMenu *MainMenu1;
        TPopupMenu *PopupMenu1;
        TActionList *ActionList1;
        TStatusBar *StatusBar1;
        TMenuItem *N2;
        TMenuItem *N4;
        TImageList *ImageList_TreeNode;
        TImageList *ImageList2;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TTreeView *TreeView1;
        TPanel *Panel1;
        TPanel *ModelShow;
        TPageControl *PageControl2;
        TTabSheet *TabSheet4;
        TAction *A_NewProject;
        TAction *A_OpenProject;
        TAction *A_SaveProject;
        TAction *A_CloseProject;
        TAction *A_ExitSystem;
        TMenuItem *N1;
        TMenuItem *N7;
        TMenuItem *N8;
        TMenuItem *N9;
        TMenuItem *N10;
        TMenuItem *N11;
        TAction *A_TCPConnect;
        TPanel *Panel2;
        TPanel *Panel3;
        TMenuItem *N12;
        TAction *A_WaterSystem;
        TAction *A_GasSystem;
        TAction *A_Motor;
        TAction *A_HandControl;
        TAction *A_PMAC;
        TAction *A_Mirror;
        TBitBtn *BitBtn4;
        TAction *A_MechConfig;
        TAction *A_Mach_Mirror;
        TAction *A_Mach_PMAC;
        TAction *A_Mach_Laser;
        TAction *A_Mach_IO;
        TAction *A_RemoteIP;
        TAction *A_IO_Monitor;
        TAction *A_UserSetting;
        TAction *A_LaserSetting;
        TAction *A_SystemSet;
        TAction *A_OP_Auto;
        TAction *A_OP_Manual;
        TAction *A_WiperAndMotor;
        TTabSheet *TabSheet3;
        TAction *A_DoorOP;
        TAction *A_LoadCLIFile;
        TOpenDialog *OpenDialog1;
        TMenuItem *N28;
        TMemo *Memo2;
        TToolBar *ToolBar1;
        TBitBtn *BitBtn9;
        TBitBtn *BitBtn10;
        TBitBtn *BitBtn11;
        TGroupBox *GroupBox1;
        TLabel *Label6;
        TLabel *Label7;
        TEdit *Edit_LayerThick;
        TLabel *Label8;
        TEdit *Edit_LayerSize;
        TLabel *Label9;
        TLabel *Label10;
        TLabel *Label11;
        TEdit *Edit_XMin;
        TEdit *Edit_YMin;
        TLabel *Label12;
        TEdit *Edit_XMax;
        TEdit *Edit_YMax;
        TComboBox *CBox_LayerDatas;
        TTimer *Timer1;
        TGroupBox *GroupBox3;
        TPanel *MainControlPanel;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TBitBtn *BitBtn3;
        TPanel *Panel4;
        TTabSheet *TabSheet5;
        TPanel *Panel5;
        TBitBtn *BitBtn6;
        TLabel *Label_Logo;
        TToolButton *ToolButton1;
        TBitBtn *BitBtn14;
        TAction *A_ImportFile;
        TBitBtn *BitBtn15;
        TBitBtn *BitBtn12;
        TMenuItem *N6;
        TMenuItem *N13;
        TMenuItem *N14;
        TGroupBox *GroupBox4;
        TBitBtn *BitBtn16;
        TBitBtn *BitBtn13;
        TBitBtn *BitBtn17;
        TBitBtn *BitBtn18;
        TGroupBox *GroupBox5;
        TGroupBox *GroupBox6;
        TBitBtn *BitBtn19;
        TBitBtn *BitBtn20;
        TBitBtn *BitBtn21;
        TCheckBox *CheckBox1;
        TLabel *Label3;
        TEdit *Edit12;
        TLabel *Label30;
        TGroupBox *GroupBox7;
        TLabel *Label4;
        TLabel *Label31;
        TBitBtn *BitBtn22;
        TBitBtn *BitBtn23;
        TBitBtn *BitBtn24;
        TCheckBox *CheckBox2;
        TEdit *Edit1;
        TTrackBar *TrackBar1;
        TLabel *Label32;
        TBitBtn *BitBtn25;
        TGroupBox *GroupBox8;
        TGroupBox *GroupBox9;
        TBitBtn *BitBtn27;
        TLabel *Label1;
        TEdit *Edit_Z_DownDz;
        TGroupBox *GroupBox10;
        TTrackBar *TrackBar2;
        TLabel *Label5;
        TBitBtn *BitBtn28;
        TGroupBox *GroupBox12;
        TBitBtn *BitBtn5;
        TLabel *Label25;
        TEdit *Edit7;
        TTimer *Timer2;
        TShape *Shape1;
        TLabel *Label34;
        TComboBox *CBox_CycleTime;
        TGroupBox *GroupBox14;
        TShape *GasStatus;
        TLabel *Label22;
        TEdit *EditO2;
        TLabel *Label17;
        TEdit *Edit_Presure;
        TComboBox *ComboBox1;
        TLabel *Label16;
        TMenuItem *N3;
        TMenuItem *N15;
        TMenuItem *N5;
        TLabel *Label37;
        TTimer *Timer3;
        TGroupBox *GroupBox13;
        TLabel *Label23;
        TLabel *Label24;
        TLabel *Label27;
        TComboBox *ComboBox2;
        TEdit *EditCycleTime;
        TEdit *EditDownUnit;
        TListView *ListView1;
        TImageList *ImageList1;
        TShape *Shape2;
        TShape *Shape3;
        TBitBtn *BitBtn7;
        TBitBtn *BitBtn8;
        void __fastcall A_OpenProjectExecute(TObject *Sender);
        void __fastcall A_CloseProjectExecute(TObject *Sender);
        void __fastcall A_ExitSystemExecute(TObject *Sender);
        void __fastcall A_NewProjectExecute(TObject *Sender);
        void __fastcall FormResize(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall A_LoadCLIFileExecute(TObject *Sender);
        void __fastcall TreeView1CustomDrawItem(TCustomTreeView *Sender,
          TTreeNode *Node, TCustomDrawState State, bool &DefaultDraw);
        void __fastcall BitBtn4Click(TObject *Sender);
        void __fastcall TreeView1ContextPopup(TObject *Sender,
          TPoint &MousePos, bool &Handled);
        void __fastcall TreeView1Click(TObject *Sender);
        void __fastcall CBox_LayerDatasChange(TObject *Sender);
        void __fastcall FormPaint(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall Btn_MoveClick(TObject *Sender);
        void __fastcall Btn_ScaleClick(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall BitBtn6Click(TObject *Sender);
        void __fastcall A_MechConfigExecute(TObject *Sender);
        void __fastcall A_Mach_LaserExecute(TObject *Sender);
        void __fastcall BitBtn16Click(TObject *Sender);
        void __fastcall BitBtn13Click(TObject *Sender);
        void __fastcall BitBtn17Click(TObject *Sender);
        void __fastcall BitBtn18Click(TObject *Sender);
        void __fastcall BitBtn19MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall BitBtn19MouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall BitBtn20MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall BitBtn21Click(TObject *Sender);
        void __fastcall BitBtn19Click(TObject *Sender);
        void __fastcall BitBtn22Click(TObject *Sender);
        void __fastcall BitBtn22MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall BitBtn22MouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall BitBtn24Click(TObject *Sender);
        void __fastcall BitBtn23Click(TObject *Sender);
        void __fastcall BitBtn23MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall BitBtn20Click(TObject *Sender);
        void __fastcall BitBtn25Click(TObject *Sender);
        void __fastcall BitBtn28Click(TObject *Sender);
        void __fastcall BitBtn5Click(TObject *Sender);
        void __fastcall BitBtn27Click(TObject *Sender);
        void __fastcall ComBox_PowerChange(TObject *Sender);
        void __fastcall Timer2Timer(TObject *Sender);
        void __fastcall N15Click(TObject *Sender);
        void __fastcall EditCycleTimeExit(TObject *Sender);
        void __fastcall ComboBox3Change(TObject *Sender);
        void __fastcall BitBtn12Click(TObject *Sender);
        void __fastcall N5Click(TObject *Sender);
        void __fastcall Timer3Timer(TObject *Sender);
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall BitBtn3Click(TObject *Sender);
        void __fastcall BitBtn7Click(TObject *Sender);
        void __fastcall BitBtn8Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormMain(TComponent* Owner);

    private:
       MAMProject*  fProject;
       MConfigVars*  fConfigVars;
       RunState state;
       RunState ScanState;

       CGLView*  m_pGLView;
       TStatusPanel* readSamStatusPanel();
       TStatusPanel* readPmacStatusPanel();
       void  writeThick(String aThick);
       void  writeSize(String aSize);
       void  writeMinX(String aMinX);
       void  writeMaxX(String aMaxX);
       void  writeMaxY(String aMaxY);
       void  writeMinY(String aMinY);

       void writePartMinX(String aMinX);
       void writePartMaxX(String aMaxX);
       void writePartMinY(String aMinY);
       void writePartMaxY(String aMaxY);
       void writePartMinZ(String aMinZ);
       void writePartMaxZ(String aMaxZ);
       void writePartMoveX(String aMoveX);
       void writePartMoveY(String aMoveY);
       void writePartScaleX(String aScaleX);
       void writePartScaleY(String aScaleY);
       void writePartRotateX(String aRotateX);
       void writePartRotateY(String aRotateY);

       String readPartMoveX();
       String readPartMoveY();
       String readPartScaleX();
       String readPartScaleY();
    public:
       __property  MAMProject*    Project = {read=fProject};
       __property  MConfigVars*   ConfigVars = {read=fConfigVars};
       __property  TStatusPanel*  SamStatusPanel = {read=readSamStatusPanel};
       __property  TStatusPanel*  PMacStatusPanel = {read=readPmacStatusPanel};
       __property  String   LayerThick = {write= writeThick};
       __property  String   LayerSize = {write=writeSize};
       __property  String   LayerMinX = {write=writeMinX};
       __property  String   LayerMaxX = {write=writeMaxX};
       __property  String   LayerMinY = {write=writeMinY};
       __property  String   LayerMaxY = {write=writeMaxY};

       //__property  String   PartMinX = {write=writePartMinX};
       //__property  String   PartMaxX = {write=writePartMaxX};
       //__property  String   PartMinY = {write=writePartMinY};
       //__property  String   PartMaxY = {write=writePartMaxY};
      // __property  String   PartMinZ = {write=writePartMinZ};
       //__property  String   PartMaxZ = {write=writePartMaxZ};
      // __property  String   PartRotateX = {write=writePartRotateX};
      // __property  String   PartRotateY = {write=writePartRotateY};

       //__property  String   PartMoveX = {write=writePartMoveX,read=readPartMoveX};
      // __property  String   PartMoveY = {write=writePartMoveY,read=readPartMoveY};
       //__property  String   PartScaleX = {write=writePartScaleX,read=readPartScaleX};
      // __property  String   PartScaleY = {write=writePartScaleY,read=readPartScaleY};
    public:
        void WMNCLButtonDblClk(TMessage& Msg);
        void  CloseProject();
    protected:
        BEGIN_MESSAGE_MAP
                VCL_MESSAGE_HANDLER(WM_NCLBUTTONDBLCLK,TMessage,WMNCLButtonDblClk)
        END_MESSAGE_MAP(TForm)
   private:
        bool IsCanCloseProject();
public:
     MLayerDataTreeNode*  InsertCatalogNode(MLayerDataTreeNode*  aParentDM,
                                             String aNodeName,String aType);
     void  LoadModelFileToTreeNode(MLayerDataTreeNode* aDMNode);

     //void  DoDBClickTreeView(MLayerDataTreeNode* aDMNode);
     //void  RootTreeNodeProcess(MLayerDataTreeNode* aDMNode);
     //void  LayerDataTreeNodeProcess(MLayerDataTreeNode* aDMNode);

    void   ProcessPopMenu(MLayerDataTreeNode* aDMNode);
    void   DoClickTreeNode(MLayerDataTreeNode* aDMNode);
    void   ComBoxChange(MLayerDataTreeNode* aDMNode);
    void   DoPartMove(double  aPartMoveX,double aPartMoveY);
    void   DoPartScale(double aPartScaleX,double aPartScaleY);

    void   DoPrintJob(MLayerDataTreeNode* aDMNode,bool  bOpenAndClose);

    void   DoComboBoxChange(MLaserPen* aItem);
    void   DoComboBoxEdgeChange(MLaserPen* aItem);

    void   SwitchButtonTextInit();
    void   OpenGLWindowInit();

    void  PrintJobByNo(int iNoJob);
    void  DoPrintJob(MLayerDataTreeNode* aDMNode,bool  bOpenAndClose,double aMX,double aMY);


    void TestReadBinaryCLiFile(String aFileName);
    void ProcessCLIHeader(char Header[]);
    void CliFileLayerRead(FILE* stream,MPolyLines*  aPolyLines);

    void  SetButtonImage(TBitBtn* aButton,String  aImageFileName,String aText);
    void  SetCurrentStatus(TBitBtn* aButton,TShape* aShape,bool  bRun, String aText);
    void  ButtonEnableBySifu(bool   bRun);
    void  ButtonEnableBySifuMove(bool bRun);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;


//---------------------------------------------------------------------------
#endif
