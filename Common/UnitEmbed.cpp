//------------------------------------------------------------------------------
//#include "UnitAll.h"

#pragma hdrstop

#include "UnitWordFun.h"
#include "UnitPptFun.h"
#include "UnitEmbed.h"

#pragma package(smart_init)

//------------------------------------------------------------------------------
MWindow::MWindow()
{
  fHandle = NULL;
  fParent = NULL;
  fWStyle = 0;
  fPlace.length = sizeof(WINDOWPLACEMENT);
}

MWindow::~MWindow()
{
  //delete fRect;
}

void MWindow::SaveWindow()
{
  GetWindowPlacement(  Handle, &Place );     //记录窗口位置
  Parent = GetParent( Handle );
  //获取窗口状态
  WStyle = GetWindowLong(Handle,GWL_STYLE); //ls
}

void MWindow::RestWindow()
{
  if( Handle==NULL )
    return;
  SetWindowLong( Handle,GWL_STYLE , WStyle ); //ls
  SetWindowPlacement(  Handle, &Place );      //还有窗口位置
  ::SetParent( Handle,Parent );
}

//------------------------------------------------------------------------------
void MWindows::GetAllWindowCaptions_1()
{
  Flush();

  HWND aNextHandle;
  char szText[255];
  HWND aCurHandle = GetWindow(Application->Handle, GW_HWNDFIRST);
  for( ; aCurHandle != NULL ; )
  {
    if ( GetWindowText(aCurHandle, szText, 255)>0 )
    {
      MWindow* aWindow = new MWindow;
      aWindow->Handle = aCurHandle;
      aWindow->Name = String(szText);
      Add( aWindow );
    }
    aCurHandle=GetWindow(aCurHandle, GW_HWNDNEXT);
  }
}

void MWindows::GetAllWindowCaptions()
{
  Flush();
  HWND aNextHandle;
  HWND aCurHandle = Application->Handle;

  for(;;)
  {
    if( aCurHandle == NULL )
      break;

    char szText[255];
    GetWindowText(aCurHandle, szText, 255);

    MWindow* aWindow = new MWindow;
    aWindow->Handle = aCurHandle;
    aWindow->Name = String(szText);
    Add( aWindow );

    aNextHandle = GetNextWindow( aCurHandle, GW_HWNDNEXT );
    if( aNextHandle == NULL || aNextHandle== Application->Handle )
      break;
    aCurHandle = aNextHandle;
  }
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
int MWindows::FindWindowLike_No(String aWindowName)
{
  GetAllWindowCaptions();

  TStrings* aFindWindows = new TStringList;

  //找到所有类似名称的窗口
  for( int i=0; i<Count; i++ )
  {
    if( IsLike( Items[i]->Name, aWindowName ) )
      aFindWindows->Add( IntToStr( i ) );
  }

  if(  aFindWindows->Count <= 0 )
  {
    delete aFindWindows;
    return -1;
  }

  //取最为匹配的窗口名称
  int iMatch = 0;
  for( int i=1; i<aFindWindows->Count; i++ )
  {
    String aNameMatch = Items[iMatch]->Name;
    int iCur = StrToInt( aFindWindows->Strings[i] );
    String aNameCur = Items[iCur]->Name;

    if( aNameMatch.Length() < aNameCur.Length() )
      iMatch = iCur;
  }

  int aWindowNo =StrToInt(aFindWindows->Strings[iMatch]);
  delete aFindWindows;
  return aWindowNo;
}

//------------------------------------------------------------------------------
String gNeedFindWindow="";
HWND gFindWindow=NULL;
bool gIsLike = true;

bool IsMatchString( String aStr1, String aStr2 )
{
  if( gIsLike )
    return ( UpperCase(aStr1).Pos( UpperCase( aStr2 ) ) > 0  );
    //return IsLike( aStr1, aStr2 );
  else
    return aStr1==aStr2;
}

//---------------------------------------------------------------------------
//枚举窗口回调函数，功能：找到与子串匹配的窗口caption
//---------------------------------------------------------------------------
bool  CALLBACK  EnumFunc(HWND  hWnd,   LPARAM lParam)
{
  char aWindowName[255];
  ::GetWindowText(hWnd, aWindowName, 255);

  if( hWnd == NULL )
  {
    gFindWindow = NULL;
    return false ;       //查询结束
  }
  else if (  IsMatchString( UpperCase( aWindowName ), UpperCase(gNeedFindWindow) ) )
  {
    gFindWindow = hWnd;
    return false;            //查询结束
  }
  else
    return true;
}

HWND FindWindow(String aWindowName)
{
  return FindWindowLike(aWindowName, false);
}

HWND FindWindowLike(String aWindowName)
{
  return FindWindowLike(aWindowName, true);
}

HWND FindWindowLike(String aWindowName, bool IsLike)
{
  gIsLike = IsLike;
  gFindWindow = NULL;
  gNeedFindWindow = aWindowName;
  EnumWindows( (WNDENUMPROC)EnumFunc, NULL );

  return gFindWindow;
}



//------------------------------------------------------------------------------
//功能：处理应用程序嵌入的类
//说明：(1)aAppTitle--窗口识别标记，例如“Maxwell”
//      (2)aAppClass--在注册表中的应用程序类别，例如“”，一般用于记录Application的主程序所在
//      (3)aPanel--窗口嵌入位置
//使用：(1)调用 SnapWndByTitle后开始其作用，release用于释放被嵌入的窗口
//------------------------------------------------------------------------------
MEmbedWindow::MEmbedWindow( String aAppTitle, String aAppClass, TPanel* aPanel )
{
  GetSleepTime();

  fAutoLaunch = true;

  fWindows = new MWindows;
  fAppWindow = new MWindow;
  fAppTitle = aAppTitle;
  fAppTitle1 = "";
  fAppClass = aAppClass;

  fPanel = aPanel;
  if(fPanel!=NULL)
  {
    fOldDoOnResize = fPanel->OnResize;
    fPanel->OnResize = DoOnResize;
    //fOldPanelCaption = fPanel->Caption;
  }

  fProcessCaption=NULL;
  fProcessBar=NULL;
  //fBar=NULL;

  IsAutoStartApplication=false;
  fEmbeded=false;
  fCfgDialog = new TOpenDialog(NULL);

  CloseAll=false;

  fSnapAction=NULL;            //关联的操作按钮

  fApplicationExeName="";
  AdvanceWindowTitle="";
}

void MEmbedWindow::GetSleepTime()
{
  C_SLEEP_TIME = 300;

  String aConfigFileName = ApplicationPath() + "\\config.sys";
  if( !FileExists( aConfigFileName ) )
    return;

  TStrings* aStrings = new TStringList;

  try
  {
    aStrings->LoadFromFile( aConfigFileName );
    C_SLEEP_TIME = Get_ListItemFloat_ByName( aStrings, "SnapSleepTime", "=", 300 );
  }
  catch( Exception& e )
  {
  }
  delete aStrings;
}

void MEmbedWindow::Close()
{
  if( fAppWindow==NULL || fAppWindow->Handle==0 )
    return;
    
  if( IsAutoStartApplication )
    SendMessage( fAppWindow->Handle,WM_CLOSE,0,0);
  Release();
}

MEmbedWindow::~MEmbedWindow()
{
  Close();
  delete fWindows;
  delete fAppWindow;
  delete  fCfgDialog;
}

void  MEmbedWindow::writeEmbeded(bool aEmbeded)
{
  fEmbeded = aEmbeded;
  SetSnapAction(fEmbeded);
}

void  MEmbedWindow::SetSnapAction(bool aEmbeded)
{
  if( fEmbeded==true )
  {
    if( fSnapAction!=NULL )
    {
       fSnapAction->Caption = "释放"+fAppTitle;
       fSnapAction->Hint = "释放"+fAppTitle;
    }
  }
  else
  {
    if( fSnapAction!=NULL )
    {
       fSnapAction->Caption = "嵌入"+fAppTitle;
       fSnapAction->Hint = "嵌入"+fAppTitle;
    }
  }
}

//----------------------SnapAction----------------------------------------------
void  MEmbedWindow::writeSnapAction(TAction* aSnapAction)
{
  fSnapAction = aSnapAction;

  if( fSnapAction==NULL || fSnapAction->OnExecute!=NULL )
    return;
  fSnapAction->OnExecute = DoSnapAction;
}

void __fastcall MEmbedWindow::DoSnapAction(TObject *Sender)
{
  if( !Embeded )
  {
    if( !HasBindWindow() )
    {

      if(  AdvanceWindowTitle!="" && FindWindowLike( AdvanceWindowTitle ) == NULL )
        return;
        //throw Exception( "请先启动"+AdvanceWindowTitle+"!" );   //怀疑Exception导致某些程序死机

      if( ApplicationExeName!="" )
        WinExec( ApplicationExeName.c_str() , 0 );

      ::Sleep(200);
      SnapWndByTitle(1000000,false);
      if( Embeded )
        IsAutoStartApplication=true;
    }
    else
      Snap();
  }
  else
  {
    Release();
  }
}


//------------------------------------------------------------------------------
//功能：检测是否已经绑定窗口，如果True，则不需要重新搜索窗口。
//------------------------------------------------------------------------------
MEmbedWindow::HasBindWindow()
{
  return fAppWindow->Handle!=NULL;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void __fastcall MEmbedWindow::DoOnResize(TObject *Sender)
{
   Refresh();
   if( fOldDoOnResize != NULL )
     fOldDoOnResize(Sender);
}

void MEmbedWindow::InitFindWindow( int aWaitSec )
{
  //fPanel->Caption = "正在启动并连接应用程序窗口("+fAppTitle+")!请稍候";

  if( fProcessCaption )
    fProcessCaption->Caption="正在启动并连接应用程序窗口("+fAppTitle+")!请稍候";

  if( fProcessBar )
    fProcessBar->Max = aWaitSec;
}

void MEmbedWindow::EndFindWindow()
{
  if( fProcessBar )
    fProcessBar->Position = 0;
  if( fProcessCaption )
    fProcessCaption->Caption="";
}

//------------------------------------------------------------------------------
//名称：Message_SafeSendText
//功能：向 aDlgHandle的aControlID输入条发送Text，并确认
//------------------------------------------------------------------------------
void MEmbedWindow::Message_SafeSendText( HWND aDlgHandle, int aControlID, String aStr,
                                         int aWaitSec, int aSleepDelta  )
{
  //----发送向Dlg写文本操作----------
  HWND aDlgItem = GetDlgItem( aDlgHandle, aControlID );    //新写法
  if( aDlgItem==NULL )
    return;
  SendMessage( aDlgItem, WM_SETTEXT, aStr.Length(), long(aStr.c_str()));

  // SendDlgItemMessage( aDlgHandle, aControlID,WM_SETTEXT, aStr.Length(), long(aStr.c_str()) );     //原来的写法

  //----获取-------
  String aStrGet =  Message_GetText(  aDlgHandle, aControlID );

  TTime aTimeOld = Now();
  TTime aTimeNew;
  //InitFindWindow (aWaitSec);

  while( aStrGet == "" )
  {
    if( CloseAll == true )
      break;
        
    //SendDlgItemMessage( aDlgHandle, aControlID,WM_SETTEXT, aStr.Length(), long(aStr.c_str()) );
    aTimeNew = Now();
    int aDelta = DateTimeToTimeStamp( aTimeNew ).Time  - DateTimeToTimeStamp( aTimeOld ).Time;
    //fBar->Position = aDelta;
    Application->ProcessMessages();

    if( aDelta > aWaitSec )
      if( MessageDlg("设置文本("+aStr+")尚未成功，是否继续等待",                //debugnow
          mtInformation, TMsgDlgButtons() << mbOK << mbNo, 0) == mrNo  )
      {
        return;
        //throw Exception("设置文本("+aStr+")!");    //怀疑Exception导致某些程序死机
      }
      else
        aTimeOld = Now();

    Sleep((unsigned int)aSleepDelta);

    aStrGet =  Message_GetText( aDlgHandle, aControlID);
    Application->ProcessMessages();
  }
  //EndFindWindow();
  return;
}

String MEmbedWindow::Message_GetText( HWND aDlgHandle, int aControlID )
{
  char aChar[255];
  long aPtr;
  SendDlgItemMessage( aDlgHandle, aControlID,WM_GETTEXT, 256, (long)aChar );

  //HWND aControlHandle = GetDlgItem( aDlgHandle,aControlID );
  //char aChar[512];
  //GetWindowText( aControlHandle, aChar, 512 );

  String aStr = aChar;
  return aStr;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
HWND MEmbedWindow::MessagePostUntilFindWindow( unsigned int aMsg, unsigned int wParam, long lParam,
                                 String aWindowName, int aWaitSec, int aSleepDelta )
{

  MessagePost(aMsg, wParam, lParam);        //启动DLL对话框
  HWND aHandle = FindWindow(NULL,aWindowName.c_str());  //fWindows->FindWindowLike( aWindowName );

  TTime aTimeOld = Now();
  TTime aTimeNew;
  //InitFindWindow (aWaitSec);

  while( aHandle == NULL )
  {
    if( CloseAll == true )
      break;

    aTimeNew = Now();
    int aDelta = DateTimeToTimeStamp( aTimeNew ).Time  - DateTimeToTimeStamp( aTimeOld ).Time;    
    //fBar->Position = aDelta;
    Application->ProcessMessages();

    if( aDelta > aWaitSec )
      if( MessageDlg("应用程序("+aWindowName+")尚未启动，是否继续等待",
          mtInformation, TMsgDlgButtons() << mbOK << mbNo, 0) == mrNo  )
      {
        return NULL;
        //throw Exception("无法找到应用程序("+fAppTitle+")!");   //怀疑Exception导致某些程序死机
      }
      else
        aTimeOld = Now();

    Sleep((unsigned int)aSleepDelta);
    aHandle = FindWindow(NULL,aWindowName.c_str());;
    Application->ProcessMessages();
  }
  //EndFindWindow();
  return aHandle;
}

//------------------------------------------------------------------------------
HWND MEmbedWindow::FindEmbedWindow( int aWaitSec )
{
  //-------查找应用程序窗口，如不存在则启动应用程序-------------
  HWND aHandle = FindWindowLike( fAppTitle );

  if( aHandle==NULL && fAppTitle1!="" )
    aHandle = FindWindowLike( fAppTitle1 );

  if( AutoLaunch == false )
    return aHandle;

  if( aHandle==NULL )
  {
    if( StartApplication( fAppClass ) == false )
      return NULL;
  }
  else
    return aHandle;

  //-------等待直到抓到窗口-------------------------------------
  TTime aTimeOld = Now();
  TTime aTimeNew;
  InitFindWindow (aWaitSec);
  int aDelta;
  while( aHandle == NULL )
  {
    if( CloseAll == true )
      break;

    aTimeNew = Now();
    aDelta = DateTimeToTimeStamp( aTimeNew ).Time  - DateTimeToTimeStamp( aTimeOld ).Time;

    if( ProcessBar )
      ProcessBar->Position = aDelta;
    Application->ProcessMessages();

    if( aDelta > aWaitSec )
      return NULL;

      //throw Exception("无法找到应用程序("+fAppTitle+")!");        //怀疑Exception导致某些程序死机

/*    if( aDelta > aWaitSec )
      if( MessageDlg("应用程序("+fAppTitle+")尚未启动，是否继续等待",            //20150827
          mtInformation, TMsgDlgButtons() << mbOK << mbNo, 0) == mrNo  )
      {
        EndFindWindow();
        throw Exception("无法找到应用程序("+fAppTitle+")!");
      }
      else
        aTimeOld = Now();*/

    Sleep( (unsigned int)C_SLEEP_TIME );
    aHandle = FindWindowLike( fAppTitle );
    Application->ProcessMessages();
  }
  EndFindWindow();

  Sleep( (unsigned int)(C_SLEEP_TIME*20) );

  //?? return NULL;
  return aHandle;
}

bool MEmbedWindow::LaunchWndByTitle( long aWaitSec )
{
  if( fAppTitle=="" || fPanel == NULL || Embeded==true )  //|| fAppWindow->Handle!=NULL )
  {
    gError->Warn1("应用程序已嵌入！");
    return false;
  }

  //if( Embeded == true )
  //  throw Exception("应用程序已嵌入！");

  fAppWindow->Handle = FindEmbedWindow(aWaitSec);
  fAppWindow->SaveWindow();
  return true;
}

//------------------------------------------------------------------------------
//名称：SnapWndByTitle
//功能：将指定名称（AppTitle）的应用程序窗口嵌入到指定区域（aPanel）
//参数：(1)AppTitle (2)aPanel  (3)aWaitSec:等待的最大时间
//------------------------------------------------------------------------------
void MEmbedWindow::_SnapWndByTitle( long aWaitSec, bool isLaunch )
{
  fAutoLaunch = isLaunch;

  //启动应用程序
  if( LaunchWndByTitle(aWaitSec)==false )
    return;

  if( fAppWindow->Handle==NULL )
    return;

  //修改应用程序的窗口类型
  ::Sleep(C_SLEEP_TIME/2);
  SetWindowLong( fAppWindow->Handle,GWL_STYLE,-1778384896 );

  if( fAppWindow->Handle!=NULL && fPanel->Handle!=NULL )
  {
    //将Proe窗口嵌入到Panel中
    ::Sleep(C_SLEEP_TIME);
    Embeded = ::SetParent( fAppWindow->Handle,fPanel->Handle );
  }

  if( !Embeded )  return;

  //if( !fEmbeded )
  //{
  //  throw Exception("请重新嵌入！");
  //}

  //切除Form1的三维视图区,使proe显示区域在form中显示
  Refresh();
}

//------------------------------------------------------------------------------

bool MEmbedWindow::SnapWndByTitle( long aWaitSec, bool isLaunch )
{

  //-------等待直到抓到窗口-------------------------------------
  TTime aTimeOld = Now();
  TTime aTimeNew;

  InitFindWindow (aWaitSec);
  int aDelta;
  for( ;; )
  {
    _SnapWndByTitle( aWaitSec, isLaunch );
    if( fAppTitle=="" || Embeded )
      break;

    aTimeNew = Now();
    aDelta = DateTimeToTimeStamp( aTimeNew ).Time  - DateTimeToTimeStamp( aTimeOld ).Time;

    if( ProcessBar )
      ProcessBar->Position = aDelta;
    Application->ProcessMessages();

    if( aDelta > aWaitSec )
      if( MessageDlg("应用程序("+fAppTitle+")尚未嵌入，是否继续等待?",
          mtInformation, TMsgDlgButtons() << mbOK << mbNo, 0) == mrNo  )
      {
        EndFindWindow(); 
        return false;
        //throw Exception("无法嵌入应用程序("+fAppTitle+")!");    怀疑Exception引起某些情况下的死机
      }
      else
      {
        ResetApplication();
        aTimeOld = Now();
      }

    Sleep( (unsigned int)C_SLEEP_TIME );
    Application->ProcessMessages();
  }
  //Sleep((unsigned int)C_SLEEP_TIME);
  EndFindWindow();
  return true;
}

/*void MEmbedWindow::SnapWndByTitle( long aWaitSec, bool isLaunch )
{

  //-------等待直到抓到窗口-------------------------------------
  TTime aTimeOld = Now();
  TTime aTimeNew;

  InitFindWindow (aWaitSec);
  int aDelta;
  for( ;; )
  {
    _SnapWndByTitle( aWaitSec, isLaunch );
    if( fAppTitle=="" || Embeded )
      break;

    aTimeNew = Now();
    aDelta = DateTimeToTimeStamp( aTimeNew ).Time  - DateTimeToTimeStamp( aTimeOld ).Time;

    if( ProcessBar )
      ProcessBar->Position = aDelta;
    Application->ProcessMessages();

    if( aDelta > aWaitSec )
      if( MessageDlg("应用程序("+fAppTitle+")尚未嵌入，是否继续等待?",
          mtInformation, TMsgDlgButtons() << mbOK << mbNo, 0) == mrNo  )
      {
        //EndFindWindow();
        throw Exception("无法嵌入应用程序("+fAppTitle+")!");
      }
      else
        aTimeOld = Now();

    Sleep( (unsigned int)C_SLEEP_TIME );
    Application->ProcessMessages();
  }
  //Sleep((unsigned int)C_SLEEP_TIME);
  EndFindWindow();
} */

void MEmbedWindow::Minimized()
{
  if( fAppWindow==NULL || fAppWindow->Handle==0 )
    return;

  ShowWindow( fAppWindow->Handle,SW_MINIMIZE );

  /*WINDOWPLACEMENT aPlace;
  aPlace.length =  sizeof(WINDOWPLACEMENT);
  aPlace.rcNormalPosition.left = 0;
  aPlace.rcNormalPosition.right = 1;
  aPlace.rcNormalPosition.top = 0;
  aPlace.rcNormalPosition.bottom = 1;

  SetWindowPlacement( fAppWindow->Handle, &aPlace );       //还有窗口位置*/

}

void MEmbedWindow::Maxmized()
{
  if( fAppWindow==NULL || fAppWindow->Handle==0 )
    return;
  ShowWindow( fAppWindow->Handle,SW_MAXIMIZE );
}

void MEmbedWindow::Refresh()
{
  WINDOWPLACEMENT aPlace;
  aPlace.length =  sizeof(WINDOWPLACEMENT);
  aPlace.rcNormalPosition.left = 0;
  aPlace.rcNormalPosition.right = fPanel->Width;
  aPlace.rcNormalPosition.top = 0;
  aPlace.rcNormalPosition.bottom = fPanel->Height;

  SetWindowPlacement(  fAppWindow->Handle, &aPlace );       //还有窗口位置
  //SetWindowPos( fAppWindow->Handle, HWND_TOP, 0 , 0 , fPanel->Width , fPanel->Height , SWP_SHOWWINDOW );
}

void MEmbedWindow::Release()
{ 
  fAppWindow->RestWindow();
  Embeded=false;
}

void MEmbedWindow::Snap()
{
  SetWindowLong( fAppWindow->Handle,GWL_STYLE,-1778384896 );
  //::Sleep(C_SLEEP_TIME);

  //将Proe窗口嵌入到Panel中
  Embeded = ::SetParent( fAppWindow->Handle,fPanel->Handle );
  Refresh();
}

void MEmbedWindow::SnapParent()
{
  ::SetParent( fAppWindow->Handle,fPanel->Handle );
}

HWND MEmbedWindow::AppWindowHandle()
{
  if( fAppWindow==NULL )
    return NULL ;
   return fAppWindow->Handle;
}

void MEmbedWindow::ReleaseParent()
{
  ::SetParent( fAppWindow->Handle,fAppWindow->Parent );
}

String MEmbedWindow::GetRegister_AppCmd( String aAppName )                  //获取注册表中的启动信息
{
   return   ReadRegistry( aAppName );
}

void MEmbedWindow::SetRegister_AppCmd( String aAppName,String aAppValue )    //设置注册表中的启动信息'
{
     WriteRegistry( aAppName,aAppValue );
}
void MEmbedWindow::SetCfgDialog(String AppName )
{
  fCfgDialog->Title = "请选择"+AppName+"快捷方式！";
  fCfgDialog->Filter = "*.lnk|*.lnk";
}
//------------------------------------------------------------------------------
//名称：MEmbedWindow::StartApplication
//------------------------------------------------------------------------------
bool MEmbedWindow::StartApplication( String aAppClassName )
{
  if( aAppClassName=="" )
    return false;

  //注册表查找aAppStartCmd
  String aAppStartCmd = GetRegister_AppCmd(aAppClassName);
  try
  {
    if (!FileExists(aAppStartCmd) )
    {
      if ( MessageDlg("是否配置"+aAppClassName+"启动信息？",                    //debugnow
            mtConfirmation,TMsgDlgButtons() <<mbYes<<mbNo,0) == mrNo )
        return false;

      SetCfgDialog(aAppClassName);
      if ( fCfgDialog->Execute() )
      {
        aAppStartCmd =   fCfgDialog->FileName ;
        SetRegister_AppCmd(aAppClassName, fCfgDialog->FileName );
      }
    }
    return StartApplicationByCmd(aAppStartCmd);
  }
  catch(Exception &exception)
  {
    return false;

    //throw Exception( "应用程序("+fAppTitle+")的启动信息("+aAppStartCmd+          //怀疑Exception导致某些程序死机
    //                 ")不正确，请使用配置工具重新注册后在执行本功操作！");
  }
}

bool MEmbedWindow::StartApplicationByCmd( String aAppStartCmd )
{
  HINSTANCE  RunResult =  RunAppByLnk(aAppStartCmd) ;
  if ( (int)RunResult > 32  )
  {
    IsAutoStartApplication = true;
    return true;
  }
  else
    return false;

    //throw Exception("应用程序("+aAppStartCmd+")无法启动！");
  //IsAutoStartApplication = RunAppByLnk(aAppStartCmd);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void MEmbedWindow::MessageSend(unsigned int aMsg,unsigned int wParam,long lParam)
{
  if( fAppWindow==NULL || fAppWindow->Handle == NULL )
    return;
    //throw Exception("窗口("+fAppTitle+")");
  SendMessage( fAppWindow->Handle, aMsg, wParam, lParam );

}

void MEmbedWindow::MessagePost(unsigned int aMsg,unsigned int wParam,long lParam )
{
  if( fAppWindow==NULL || fAppWindow->Handle == NULL )
    return;
    //throw Exception("窗口("+fAppTitle+")");
  PostMessage( fAppWindow->Handle, aMsg, wParam, lParam );
}

//------------------------------------------------------------------------------
//名称：MEmbedWindow_UG
//------------------------------------------------------------------------------
MEmbedWindow_UG::MEmbedWindow_UG(String aAppTitle, String aAppClass,TPanel* aPanel) :
  MEmbedWindow( aAppTitle, aAppClass, aPanel )
{
  //fTempPath = C_PATH_UGTEMP;
}

void MEmbedWindow_UG::RunDll( String aDllFileName )
{
  if( !FileExists( aDllFileName ) )
  {
    gError->Warn1("DLL文件("+aDllFileName+")不存在！" );
    return;
  }
    //throw Exception( "DLL文件("+aDllFileName+")不存在！" );

  //带中文路径的dll文件
  if( String_HasChineseCharacter(aDllFileName) )
  {
    gError->Warn("UG不允许Dll文件("+aDllFileName+")带中文字符！请修改后再执行该功能！");
    return;
  }
    //throw Exception( "UG不允许Dll文件("+aDllFileName+")带中文字符！请修改后再执行该功能！" );

  //if( String_HasChineseCharacter(aDllFileName)
  //{
  //   //带中文路径的dll文件
  //    String aNewDllFileName = TempPath+ "\\" + ExtractFileName(aDllFileName);
  //    if( !FileExists(aNewDllFileName) )
  //      CopyFileAlways( aDllFileName, aNewDllFileName );
  //}
  //else
  //  aNewDllFileName = aDllFileName;

  //gError->Warn( "1" );
  ::Sleep(1000);
  HWND aDlgHandle = MessagePostUntilFindWindow( 273, 1089, 0,"Execute User Function" );   //启动DLL对话框 

  ::Sleep(1000);
  if ( fAppClass == "UG NX 2")
    Message_SafeSendText( aDlgHandle, 1148,aDllFileName );      //UG2.0
  else
    Message_SafeSendText( aDlgHandle, 1152,aDllFileName );        //UG1.0

  SendMessage( aDlgHandle, 273, 1, 3344666);           //发送“OK”消息
  //MessageSend (273, 1, 3344666);           //发送“OK”消息
}

//------------------------------------------------------------------------------
//名称：MEmbedWindow_ANSYS
//------------------------------------------------------------------------------
MEmbedWindow_ANSYS::MEmbedWindow_ANSYS(String aAppTitle, String aAppClass,TPanel* aPanel) :
  MEmbedWindow( aAppTitle, aAppClass, aPanel )
{
}

void MEmbedWindow_ANSYS::SendCmd( String aStrCmd )
{
  if ( aStrCmd == "" )
    return;

  HWND AnsysInputHwnd = FindWindow( NULL,"ANSYS Input" );
  HWND AnsCommandHWd = GetDlgItem( AnsysInputHwnd,2 );

  SendMessage( AnsCommandHWd,WM_SETTEXT,aStrCmd.Length(),long(aStrCmd.c_str()) );
  PostMessage( AnsCommandHWd,273,475,1 );
}

void MEmbedWindow_ANSYS::SendCmds( TStrings* aCmds, int aDelay )
{
   for( int i = 0 ; i < aCmds->Count ; i++ )
   {
     SendAnsysCmd( aCmds->Strings[i] );
     ::Sleep(aDelay);
   }
}


//------------------------------------------------------------------------------
//名称：SendAnsysCmd
//功能：向Ansys系统发送操作命令
//------------------------------------------------------------------------------
void SendAnsysCmd( String Cmd )
{
  if ( Cmd == "" )
    return;

  HWND AnsysInputHwnd = FindWindow(NULL,"ANSYS Input");
  HWND AnsCommandHWd = GetDlgItem(AnsysInputHwnd,2);

  char * InputStr;
  StrCopy(InputStr,Cmd.c_str());
  SendMessage(AnsCommandHWd,WM_SETTEXT,StrLen(InputStr),long(InputStr));
  PostMessage(AnsCommandHWd,273,475,1);
}

//------------------------------------------------------------------------------
//名称：SendAnsysCmd
//功能：向Ansys系统发送操作命令流
//说明：不建议采用该方式，建议将命令做成脚本文件，用　发送执行脚本
//------------------------------------------------------------------------------
void SendAnsysCmd( TStrings *Cmds, int aDelay )
{
   for( int i = 0 ; i < Cmds->Count ; i++ )
   {
     SendAnsysCmd( Cmds->Strings[i] );
     ::Sleep(aDelay);
   }
}

//------------------------------------------------------------------------------
MEmbedWindow_MAXWELL::MEmbedWindow_MAXWELL(String aAppTitle, String aAppClass,TPanel* aPanel) :
    MEmbedWindow( aAppTitle, aAppClass,aPanel )
{
}

//----------------PPT-----------------------------------------------------------
MEmbedPPt::MEmbedPPt( TPanel* aPanel,String aAppTitle, String aAppClass):
	MEmbedWindow( aAppTitle, aAppClass,aPanel )
{
    fAppClass = "PP9FrameClass";    // PP97FrameClass  PP9FrameClass PP10FrameClass PP11FrameClass PP12FrameClass
    G_PPT->ConfirmRun();
}

//重启PPT
void MEmbedPPt::ResetApplication()
{
  String aStr = ApplicationPath()+"\\killPPT.bat";
  WinExec( aStr.c_str(),SW_HIDE );
  G_PPT->ConfirmRun();
}

//----------------Word----------------------------------------------------------
MEmbedWord::MEmbedWord( TPanel* aPanel,String aAppTitle, String aAppClass ):
	MEmbedWindow( aAppTitle, aAppClass,aPanel )
{
  fAppClass = "OpusApp";
  G_Word->ConfirmRun();
}

//重启Word
void MEmbedWord::ResetApplication()
{
  String aStr = ApplicationPath()+"\\killword.bat";
  WinExec( aStr.c_str(),SW_HIDE );
  G_Word->ConfirmRun();
}



