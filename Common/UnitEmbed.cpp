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
  GetWindowPlacement(  Handle, &Place );     //��¼����λ��
  Parent = GetParent( Handle );
  //��ȡ����״̬
  WStyle = GetWindowLong(Handle,GWL_STYLE); //ls
}

void MWindow::RestWindow()
{
  if( Handle==NULL )
    return;
  SetWindowLong( Handle,GWL_STYLE , WStyle ); //ls
  SetWindowPlacement(  Handle, &Place );      //���д���λ��
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

  //�ҵ������������ƵĴ���
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

  //ȡ��Ϊƥ��Ĵ�������
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
//ö�ٴ��ڻص����������ܣ��ҵ����Ӵ�ƥ��Ĵ���caption
//---------------------------------------------------------------------------
bool  CALLBACK  EnumFunc(HWND  hWnd,   LPARAM lParam)
{
  char aWindowName[255];
  ::GetWindowText(hWnd, aWindowName, 255);

  if( hWnd == NULL )
  {
    gFindWindow = NULL;
    return false ;       //��ѯ����
  }
  else if (  IsMatchString( UpperCase( aWindowName ), UpperCase(gNeedFindWindow) ) )
  {
    gFindWindow = hWnd;
    return false;            //��ѯ����
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
//���ܣ�����Ӧ�ó���Ƕ�����
//˵����(1)aAppTitle--����ʶ���ǣ����硰Maxwell��
//      (2)aAppClass--��ע����е�Ӧ�ó���������硰����һ�����ڼ�¼Application������������
//      (3)aPanel--����Ƕ��λ��
//ʹ�ã�(1)���� SnapWndByTitle��ʼ�����ã�release�����ͷű�Ƕ��Ĵ���
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

  fSnapAction=NULL;            //�����Ĳ�����ť

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
       fSnapAction->Caption = "�ͷ�"+fAppTitle;
       fSnapAction->Hint = "�ͷ�"+fAppTitle;
    }
  }
  else
  {
    if( fSnapAction!=NULL )
    {
       fSnapAction->Caption = "Ƕ��"+fAppTitle;
       fSnapAction->Hint = "Ƕ��"+fAppTitle;
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
        //throw Exception( "��������"+AdvanceWindowTitle+"!" );   //����Exception����ĳЩ��������

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
//���ܣ�����Ƿ��Ѿ��󶨴��ڣ����True������Ҫ�����������ڡ�
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
  //fPanel->Caption = "��������������Ӧ�ó��򴰿�("+fAppTitle+")!���Ժ�";

  if( fProcessCaption )
    fProcessCaption->Caption="��������������Ӧ�ó��򴰿�("+fAppTitle+")!���Ժ�";

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
//���ƣ�Message_SafeSendText
//���ܣ��� aDlgHandle��aControlID����������Text����ȷ��
//------------------------------------------------------------------------------
void MEmbedWindow::Message_SafeSendText( HWND aDlgHandle, int aControlID, String aStr,
                                         int aWaitSec, int aSleepDelta  )
{
  //----������Dlgд�ı�����----------
  HWND aDlgItem = GetDlgItem( aDlgHandle, aControlID );    //��д��
  if( aDlgItem==NULL )
    return;
  SendMessage( aDlgItem, WM_SETTEXT, aStr.Length(), long(aStr.c_str()));

  // SendDlgItemMessage( aDlgHandle, aControlID,WM_SETTEXT, aStr.Length(), long(aStr.c_str()) );     //ԭ����д��

  //----��ȡ-------
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
      if( MessageDlg("�����ı�("+aStr+")��δ�ɹ����Ƿ�����ȴ�",                //debugnow
          mtInformation, TMsgDlgButtons() << mbOK << mbNo, 0) == mrNo  )
      {
        return;
        //throw Exception("�����ı�("+aStr+")!");    //����Exception����ĳЩ��������
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

  MessagePost(aMsg, wParam, lParam);        //����DLL�Ի���
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
      if( MessageDlg("Ӧ�ó���("+aWindowName+")��δ�������Ƿ�����ȴ�",
          mtInformation, TMsgDlgButtons() << mbOK << mbNo, 0) == mrNo  )
      {
        return NULL;
        //throw Exception("�޷��ҵ�Ӧ�ó���("+fAppTitle+")!");   //����Exception����ĳЩ��������
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
  //-------����Ӧ�ó��򴰿ڣ��粻����������Ӧ�ó���-------------
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

  //-------�ȴ�ֱ��ץ������-------------------------------------
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

      //throw Exception("�޷��ҵ�Ӧ�ó���("+fAppTitle+")!");        //����Exception����ĳЩ��������

/*    if( aDelta > aWaitSec )
      if( MessageDlg("Ӧ�ó���("+fAppTitle+")��δ�������Ƿ�����ȴ�",            //20150827
          mtInformation, TMsgDlgButtons() << mbOK << mbNo, 0) == mrNo  )
      {
        EndFindWindow();
        throw Exception("�޷��ҵ�Ӧ�ó���("+fAppTitle+")!");
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
    gError->Warn1("Ӧ�ó�����Ƕ�룡");
    return false;
  }

  //if( Embeded == true )
  //  throw Exception("Ӧ�ó�����Ƕ�룡");

  fAppWindow->Handle = FindEmbedWindow(aWaitSec);
  fAppWindow->SaveWindow();
  return true;
}

//------------------------------------------------------------------------------
//���ƣ�SnapWndByTitle
//���ܣ���ָ�����ƣ�AppTitle����Ӧ�ó��򴰿�Ƕ�뵽ָ������aPanel��
//������(1)AppTitle (2)aPanel  (3)aWaitSec:�ȴ������ʱ��
//------------------------------------------------------------------------------
void MEmbedWindow::_SnapWndByTitle( long aWaitSec, bool isLaunch )
{
  fAutoLaunch = isLaunch;

  //����Ӧ�ó���
  if( LaunchWndByTitle(aWaitSec)==false )
    return;

  if( fAppWindow->Handle==NULL )
    return;

  //�޸�Ӧ�ó���Ĵ�������
  ::Sleep(C_SLEEP_TIME/2);
  SetWindowLong( fAppWindow->Handle,GWL_STYLE,-1778384896 );

  if( fAppWindow->Handle!=NULL && fPanel->Handle!=NULL )
  {
    //��Proe����Ƕ�뵽Panel��
    ::Sleep(C_SLEEP_TIME);
    Embeded = ::SetParent( fAppWindow->Handle,fPanel->Handle );
  }

  if( !Embeded )  return;

  //if( !fEmbeded )
  //{
  //  throw Exception("������Ƕ�룡");
  //}

  //�г�Form1����ά��ͼ��,ʹproe��ʾ������form����ʾ
  Refresh();
}

//------------------------------------------------------------------------------

bool MEmbedWindow::SnapWndByTitle( long aWaitSec, bool isLaunch )
{

  //-------�ȴ�ֱ��ץ������-------------------------------------
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
      if( MessageDlg("Ӧ�ó���("+fAppTitle+")��δǶ�룬�Ƿ�����ȴ�?",
          mtInformation, TMsgDlgButtons() << mbOK << mbNo, 0) == mrNo  )
      {
        EndFindWindow(); 
        return false;
        //throw Exception("�޷�Ƕ��Ӧ�ó���("+fAppTitle+")!");    ����Exception����ĳЩ����µ�����
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

  //-------�ȴ�ֱ��ץ������-------------------------------------
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
      if( MessageDlg("Ӧ�ó���("+fAppTitle+")��δǶ�룬�Ƿ�����ȴ�?",
          mtInformation, TMsgDlgButtons() << mbOK << mbNo, 0) == mrNo  )
      {
        //EndFindWindow();
        throw Exception("�޷�Ƕ��Ӧ�ó���("+fAppTitle+")!");
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

  SetWindowPlacement( fAppWindow->Handle, &aPlace );       //���д���λ��*/

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

  SetWindowPlacement(  fAppWindow->Handle, &aPlace );       //���д���λ��
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

  //��Proe����Ƕ�뵽Panel��
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

String MEmbedWindow::GetRegister_AppCmd( String aAppName )                  //��ȡע����е�������Ϣ
{
   return   ReadRegistry( aAppName );
}

void MEmbedWindow::SetRegister_AppCmd( String aAppName,String aAppValue )    //����ע����е�������Ϣ'
{
     WriteRegistry( aAppName,aAppValue );
}
void MEmbedWindow::SetCfgDialog(String AppName )
{
  fCfgDialog->Title = "��ѡ��"+AppName+"��ݷ�ʽ��";
  fCfgDialog->Filter = "*.lnk|*.lnk";
}
//------------------------------------------------------------------------------
//���ƣ�MEmbedWindow::StartApplication
//------------------------------------------------------------------------------
bool MEmbedWindow::StartApplication( String aAppClassName )
{
  if( aAppClassName=="" )
    return false;

  //ע������aAppStartCmd
  String aAppStartCmd = GetRegister_AppCmd(aAppClassName);
  try
  {
    if (!FileExists(aAppStartCmd) )
    {
      if ( MessageDlg("�Ƿ�����"+aAppClassName+"������Ϣ��",                    //debugnow
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

    //throw Exception( "Ӧ�ó���("+fAppTitle+")��������Ϣ("+aAppStartCmd+          //����Exception����ĳЩ��������
    //                 ")����ȷ����ʹ�����ù�������ע�����ִ�б���������");
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

    //throw Exception("Ӧ�ó���("+aAppStartCmd+")�޷�������");
  //IsAutoStartApplication = RunAppByLnk(aAppStartCmd);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void MEmbedWindow::MessageSend(unsigned int aMsg,unsigned int wParam,long lParam)
{
  if( fAppWindow==NULL || fAppWindow->Handle == NULL )
    return;
    //throw Exception("����("+fAppTitle+")");
  SendMessage( fAppWindow->Handle, aMsg, wParam, lParam );

}

void MEmbedWindow::MessagePost(unsigned int aMsg,unsigned int wParam,long lParam )
{
  if( fAppWindow==NULL || fAppWindow->Handle == NULL )
    return;
    //throw Exception("����("+fAppTitle+")");
  PostMessage( fAppWindow->Handle, aMsg, wParam, lParam );
}

//------------------------------------------------------------------------------
//���ƣ�MEmbedWindow_UG
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
    gError->Warn1("DLL�ļ�("+aDllFileName+")�����ڣ�" );
    return;
  }
    //throw Exception( "DLL�ļ�("+aDllFileName+")�����ڣ�" );

  //������·����dll�ļ�
  if( String_HasChineseCharacter(aDllFileName) )
  {
    gError->Warn("UG������Dll�ļ�("+aDllFileName+")�������ַ������޸ĺ���ִ�иù��ܣ�");
    return;
  }
    //throw Exception( "UG������Dll�ļ�("+aDllFileName+")�������ַ������޸ĺ���ִ�иù��ܣ�" );

  //if( String_HasChineseCharacter(aDllFileName)
  //{
  //   //������·����dll�ļ�
  //    String aNewDllFileName = TempPath+ "\\" + ExtractFileName(aDllFileName);
  //    if( !FileExists(aNewDllFileName) )
  //      CopyFileAlways( aDllFileName, aNewDllFileName );
  //}
  //else
  //  aNewDllFileName = aDllFileName;

  //gError->Warn( "1" );
  ::Sleep(1000);
  HWND aDlgHandle = MessagePostUntilFindWindow( 273, 1089, 0,"Execute User Function" );   //����DLL�Ի��� 

  ::Sleep(1000);
  if ( fAppClass == "UG NX 2")
    Message_SafeSendText( aDlgHandle, 1148,aDllFileName );      //UG2.0
  else
    Message_SafeSendText( aDlgHandle, 1152,aDllFileName );        //UG1.0

  SendMessage( aDlgHandle, 273, 1, 3344666);           //���͡�OK����Ϣ
  //MessageSend (273, 1, 3344666);           //���͡�OK����Ϣ
}

//------------------------------------------------------------------------------
//���ƣ�MEmbedWindow_ANSYS
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
//���ƣ�SendAnsysCmd
//���ܣ���Ansysϵͳ���Ͳ�������
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
//���ƣ�SendAnsysCmd
//���ܣ���Ansysϵͳ���Ͳ���������
//˵������������ø÷�ʽ�����齫�������ɽű��ļ����á�����ִ�нű�
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

//����PPT
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

//����Word
void MEmbedWord::ResetApplication()
{
  String aStr = ApplicationPath()+"\\killword.bat";
  WinExec( aStr.c_str(),SW_HIDE );
  G_Word->ConfirmRun();
}



