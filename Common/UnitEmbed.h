//---------------------------------------------------------------------------

#ifndef UnitEmbedH
#define UnitEmbedH

//#include <vcl.h>
#include "COMMON_FUNC.hpp"
//#include <ComCtrls.hpp>
//#include <Dialogs.hpp>
#include "UnitTool_Class.h"
#include "UnitTool_Single.h"

#include <math.hpp>

const String C_PATH_UGTEMP = "c:\\UG_TempPath";
const String C_PROE_TITLE = "Pro/ENGINEER";

void SendAnsysCmd( String Cmd );
void SendAnsysCmd( TStrings *Cmds, int aDelay=300 );
bool  CALLBACK  EnumFunc(HWND  hWnd,   LPARAM lParam);
HWND FindWindowLike(String aWindowName);
HWND FindWindowLike(String aWindowName, bool IsLike);
HWND FindWindow(String aWindowName);


class MObject;
class MWindow;
class MPPtFun;


extern MPPtFun* G_PPT;
extern String gNeedFindWindow;
extern HWND gFindWindow;


class MWindow : public MObject
{
  //----Handle----
  private:
    HWND   fHandle;
  public:
    __property HWND Handle={read=fHandle,write=fHandle};

  //----Place----
  private:
    WINDOWPLACEMENT   fPlace;
  public:
    __property WINDOWPLACEMENT Place={read=fPlace,write=fPlace};

  //----Parent----
  private:
    HWND   fParent;
  public:
    __property HWND Parent={read=fParent,write=fParent};

  //----WStyle----
  private:
    LONG   fWStyle;
  public:
    __property LONG WStyle={read=fWStyle,write=fWStyle};
  public:
    MWindow();
    ~MWindow();
    
  public:
    void SaveWindow();
    void RestWindow();
};


class MWindows : public MObjectList_Temp<MWindow>
{
  private:

  public:
    //HWND FindWindowLike(String aWindowName);
  public:  
    void GetAllWindowCaptions();
    void GetAllWindowCaptions_1();
 
  private:
    int FindWindowLike_No(String aWindowName);
};

//------------------------------------------------------------------------------
//���ܣ� �ҵ����� fAppTitle �ľ��fAppWindow, Ƕ�뵽���� fPanel��
//       ��������ڸô��ڣ� ����fAppClassӦ�ó�����ٴ���
//------------------------------------------------------------------------------
class MEmbedWindow
{
  public:
    int C_SLEEP_TIME;
  protected:
    void GetSleepTime();

  public:
    bool CloseAll;

  //----AutoLaunch----
  private:
    bool   fAutoLaunch;
  public:
    __property bool AutoLaunch={read=fAutoLaunch,write=fAutoLaunch};

  //---------SnapButton-------------

  //----SnapAction----        //��Ӧ�û������ϵ�Snap��ť
  private:
    TAction*   fSnapAction;
  protected:
    void  writeSnapAction(TAction* aSnapAction );
  public:
    __property TAction* SnapAction={read=fSnapAction,write=writeSnapAction};

  //----ApplicationExeName----����//��Ƕ�봰�ڵ�Exe�ļ����ƣ�������������
  private:
    String   fApplicationExeName;
  public:
    __property String ApplicationExeName={read=fApplicationExeName,write=fApplicationExeName};

  public:                         //������Application����
    String AdvanceWindowTitle;

  private:
    void  SetSnapAction(bool aEmbeded);
  public:
    void __fastcall DoSnapAction(TObject *Sender);

  //---------------------------------------------
  protected:
    MWindows* fWindows;         //��¼�Ͳ���ϵͳ����

    String fAppClass;            //Ӧ�ó������

    MWindow* fAppWindow;
  public:
    __property MWindow* AppWindow={read=fAppWindow};

  public:
    String fAppTitle;           //��Ҫ���ҵ�Ӧ�ó���Title
    String fAppTitle1;           //��Ҫ���ҵ�Ӧ�ó���Title    

  //----ProcessCaption----    //��ʾ���ȵ�caption��Bar
  private:
    TStaticText*   fProcessCaption;
  public:
    __property TStaticText* ProcessCaption={read=fProcessCaption,write=fProcessCaption};
  //----ProcessBar----
  private:
    TProgressBar*   fProcessBar;
  public:
    __property TProgressBar* ProcessBar={read=fProcessBar,write=fProcessBar};

  //----Panel----        //Ƕ������
  private:
    TPanel*   fPanel;
  public:
    __property TPanel* Panel={read=fPanel,write=fPanel};

  //private:
  //  String fOldPanelCaption;    //Ƕ�������ԭCaption
  //  TProgressBar* fBar;         //������

    TNotifyEvent fOldDoOnResize;

    bool IsAutoStartApplication;  //�Ƿ��ɳ������Application
    TOpenDialog * fCfgDialog; //���ô���

  public:
    String GetRegister_AppCmd(String aAppName);                  //��ȡע����е�������Ϣ
    void SetRegister_AppCmd( String aAppName,String aAppValue );    //����ע����е�������Ϣ

  private:
    void __fastcall DoOnResize(TObject *Sender);

  public:
    HasBindWindow();

  //----Embeded----
  private:
    bool   fEmbeded;
  protected:
    void  writeEmbeded(bool aEmbeded);
  public:
    __property bool Embeded={read=fEmbeded,write=writeEmbeded};

  public:
    MEmbedWindow(String aAppTitle, String aAppClass,TPanel* aPanel);
    ~MEmbedWindow();

  public:
    void SnapParent();
    void ReleaseParent();
    HWND AppWindowHandle();

  public:
    __property String AppTitle={read=fAppTitle,write=fAppTitle};
    __property String AppTitle1={read=fAppTitle1,write=fAppTitle1};    
    __property String AppClass={read=fAppClass,write=fAppClass};

  public:
    bool StartApplication( String aAppClassName );
    bool StartApplicationByCmd( String aAppFileName );

  public:
    bool LaunchWndByTitle( long aWaitSec=100000 );
    void _SnapWndByTitle( long aWaitSec=100000, bool isLaunch=true );

    //void SnapWndByTitle( long aWaitSec, bool isLaunch=true );       //����Exception����ĳЩ����µ�����
    bool SnapWndByTitle( long aWaitSec, bool isLaunch=true );

    void Refresh();
    void Minimized();
    void Maxmized();
    void Release();
    void Snap();
    
  public:
    void Close();
    void Init();

  private:
    HWND FindEmbedWindow( int aWaitSec );
    void InitFindWindow( int aWaitSec );
    void EndFindWindow();
    void SetCfgDialog(String AppName );

  public:
    void MessageSend(unsigned int aMsg,unsigned int wParam,long lParam);
    void MessagePost(unsigned int aMsg,unsigned int wParam,long lParam);

  public:
    HWND MessagePostUntilFindWindow( unsigned int aMsg, unsigned int wParam, long lParam,
                                 String aWindowName, int aWaitSec=100000, int aSleepDelta=0 );

    void Message_SafeSendText( HWND aDlgHandle, int AControlID, String aStr, int aWaitSec=100000, int aSleepDelta=0  );
    String Message_GetText( HWND aDlgHandle, int aControlID );
  public:
    virtual void ResetApplication(){};  
};

class MEmbedWindows : public MObjectList_Temp<MEmbedWindow>
{
};

class MEmbedWindow_UG : public MEmbedWindow
{
  //----TempPath----
  //private:
  //  String   fTempPath;
  //public:
  //  __property String TempPath={read=fTempPath,write=fTempPath};

  public:
    MEmbedWindow_UG(String aAppTitle, String aAppClass,TPanel* aPanel);
  public:
    void RunDll( String aDllFileName );
};

class MEmbedWindow_ANSYS : public MEmbedWindow
{
  public:
    MEmbedWindow_ANSYS(String aAppTitle, String aAppClass,TPanel* aPanel);
  public:
    void SendCmd( String aStrCmd );
    void SendCmds( TStrings* aStrings, int aDelay );
};

//------------------------------------------------------------------------------
//���ܣ�MaxWell��
//------------------------------------------------------------------------------
class MEmbedWindow_MAXWELL : public MEmbedWindow
{
  public:
    MEmbedWindow_MAXWELL(String aAppTitle, String aAppClass,TPanel* aPanel);
    //virtual ~MEmbedWindow_MAXWELL();
};

//------------------------------------------------------------------------------
//���ܣ�PPTǶ����
//------------------------------------------------------------------------------
class MEmbedPPt : public MEmbedWindow
{
  public:
    MEmbedPPt( TPanel* aPanel,String aAppTitle="Microsoft PowerPoint", String aAppClass="");
  public:
    virtual void ResetApplication();    
};

//------------------------------------------------------------------------------
//���ܣ�PPTǶ����
//------------------------------------------------------------------------------
class MEmbedWord : public MEmbedWindow
{
  public:
    MEmbedWord( TPanel* aPanel,String aAppTitle="Microsoft Word", String aAppClass="");
  public:
    virtual void ResetApplication();
};

#endif
