//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitFormSamLight.h"
#include "UnitTool_Single.h"
#include "UnitTool_Class.h"
#include "UnitTool_ClassExtend.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "SAMLIGHT_CLIENT_CTRL_OCXLib_OCX"
#pragma resource "*.dfm"


TFormSamLight *FormSamLight;
String gNeedFindWindow = "";
HWND gFindWindow = NULL;
bool gIsLike = true;

//---------------------------------------------------------------------------
__fastcall TFormSamLight::TFormSamLight(TComponent* Owner)
        : TForm(Owner)
{
    fIsConnected = false;
    fIsDebug = true;
    fConnectStatus = "Not Connected";
    fStatusPanel = NULL;
    fOperatePanel = NULL;

    fIp = gIniFile->ReadString("SamLight","IP","127.0.0.1");
    fPort = gIniFile->ReadString("SamLight","Port","350");
}

//------------------------------------------------------------------------------
bool IsMatchString( String aStr1, String aStr2 )
{
  if( gIsLike )
    return UpperCase(aStr1).Pos( UpperCase( aStr2 ) ) > 0;
    //return IsLike( aStr1, aStr2 );
  else
    return aStr1==aStr2;
}

//---------------------------------------------------------------------------
//ö�ٴ��ڻص����������ܣ��ҵ����Ӵ�ƥ��Ĵ���caption
//---------------------------------------------------------------------------
bool CALLBACK  EnumFunc( HWND hWnd, LPARAM lParam )
{
  char aWindowName[255];
  ::GetWindowText( hWnd, aWindowName, 255 );

  if( hWnd == NULL )
  {
    gFindWindow = NULL;
    return false ;       //��ѯ����
  }
  else if( IsMatchString( UpperCase( aWindowName ), UpperCase(gNeedFindWindow) ) )
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

//---------------------------------------------------------------------------
//��������
bool  TFormSamLight::ConfirmSamLightRun()
{
    String  aProcessName = "sam_light.exe";
    int     iTryTime = 0;

    try
    {
        //���̲�����
        int aStep = 1;
        if(ProcessExists1(aProcessName) == false)
        {
           char*  aPath = getenv("SCAPS_SAM");
           String aPathStr = String(aPath).Trim();
           aPathStr = aPathStr + "\\samlight\\"+aProcessName;

           WinExec(aPathStr.c_str(), SW_NORMAL);
           ::Sleep(5000);

           aStep = 2;
        }
        if(aStep == 2)  //�����������Ĺ���
        {
           //�Ҵ�������
           while(FindWindow("SAMLight - [���˵� ]") == NULL && iTryTime < 100)
           {
               iTryTime++;
               ::Sleep(500);
           }
           //��ʱ�ļ��
           if(iTryTime>=100)
           {
               gError->Warn("����sam_lightʧ�ܣ�");
               return false;
           }
        }
        return true;
    }
    catch(Exception& ae)
    {
        throw Exception("ConfirmApplication����!ConfirmSamApplication:"+ae.Message);
    }
}

//---------------------------------------------------------------------------
void  TFormSamLight::Init(String aIP,String aPort)
{
    fIp = aIP;
    fPort = aPort;
    fConnectStatus = "Not Connected";
    fIsConnected = false;
}

//---------------------------------------------------------------------------
bool  TFormSamLight::GetRealRunning()
{
    //long int aHead = 0;

    //ScSamlightClientCtrl1->ScGetHead(&aHead);

    //if(aHead == -1)  //û��ʵ�￨
    //     return false;

    return true;
}


//------------------------------����--------------------------------------------
void  TFormSamLight::SamLightConnect()
{
    ConfirmSamLightRun();

    if(fIsConnected)
        ScSamlightClientCtrl1->ScCloseEthernetConnection();

    long res = ScSamlightClientCtrl1->ScOpenTCPConnection(WideString(IP).c_bstr(),StrToInt(Port.c_str()));
    if(res == 1)
    {
       fIsConnected = true;
       fConnectStatus = "Connected";
       StatusInfo = "�񾵿��ƿ����ӳɹ�(IP:" + IP + ",Port:" + Port + ")";

       String  aSamLightShow = gIniFile->ReadString("SamLight","IsShow","true");
       //��ʾ����
       if(aSamLightShow.UpperCase() != "TRUE")
            ScSamlightClientCtrl1->ScShowApp(0);      //0: ���أ�5: ��ʾ
       else
            ScSamlightClientCtrl1->ScShowApp(5);
    }
    else
    {
       fIsConnected = false;
       fConnectStatus = "Not Connected";
       StatusInfo = "�񾵿��ƿ�����ʧ��(IP:" + IP + ",Port:" + Port + ")";
    }
}

//----------------------------�Ͽ�----------------------------------------------
void  TFormSamLight::SamLightDisConnect()
{
    if(fIsConnected)
    {
        ScSamlightClientCtrl1->ScCloseEthernetConnection();

        fIsConnected = false;
        fConnectStatus = "Not Connected";
        StatusInfo = "�񾵿��ƿ����ӶϿ�";
    }
}

//------------------------------------------------------------------------------
void  TFormSamLight::SamLightClose()
{
    if(IsRunning == true)
        ScSamlightClientCtrl1->ScShutDown();
}

//------------------------------------------------------------------------------
bool  TFormSamLight::readIsRunning()
{
    if(fIsConnected == false)
         return false;

    if(ScSamlightClientCtrl1->ScIsRunning() == 0)     //ֻ�ܱ�֤COM������
          return false;

    if(GetRealRunning() == false)                     //�Ƿ���������
    {
         throw Exception("��SamLight ���ƿ�û������!");
         //return false;
    }

    return true;
}

//����һ���Ի�����Ϊ����ͨ��ʹ��
void  TFormSamLight::ExecuteTest()
{
    if(IsRunning == true)
        ScSamlightClientCtrl1->ScExecCommand(1);
    else
        throw Exception("SamLight ���û������!");
}

//------------------------------------------------------------------------------
//This resets the marking sequence to its initial state. This is important
//for jobs using the beat count and beat offset parameters.
void  TFormSamLight::DoResetSequence()
{
    if(IsRunning == true)
        ScSamlightClientCtrl1->ScExecCommand(2);
    else
        throw Exception("SamLight DoResetSequence!");
}


//��̬�ĸı��ı���
void TFormSamLight::DoChangeTextByName(String aEntityName,String aText)
{
    if(IsRunning)
       ScSamlightClientCtrl1->ScChangeTextByName(WideString(aEntityName),WideString(aText));
    else
       throw Exception("SamLight DoChangeTextByName!");
}

void    TFormSamLight::writeStatusPanel(String aText)
{
    if(fStatusPanel == NULL)
          return;

    fStatusPanel->Text = aText;
}

void  TFormSamLight::writeOperatePanel(String aText)
{
    if(fOperatePanel == NULL)
         return;

    fOperatePanel->Text = aText;
}

void  TFormSamLight::TranslateEntity(String  entityName,double aX,double aY)
{
    if(IsRunning)
    {
       ScSamlightClientCtrl1->ScTranslateEntity(WideString(entityName),aX,aY,0);
    }
}



//entity_name_to_mark : ҪMark��ʵ�����ƣ����Ϊ"", MarkALL
long TFormSamLight::mark_entity(String entity_name_to_mark)
{
     if(IsRunning == false)
        return 0;

     StatusInfo = "Sending Objects!";

     long mark_flags = 0x0 ;
     ScSamlightClientCtrl1->ScSetMarkFlags(mark_flags);

     //��������
     ScSamlightClientCtrl1->ScMarkEntityByName(WideString(entity_name_to_mark),0);
     StatusInfo = "Marking!";



     long i = 0;

     //��ֹ����
     //enable_all_windows(0);
     while(1)
     {
	  i++;
	  MSG	msg;
	  if (PeekMessage(&msg,(HWND)NULL,0,0,PM_REMOVE))
	  {
	  	::SendMessage(msg.hwnd,msg.message,msg.wParam,msg.lParam);
	  }
	  if(i%10==0)
	  {
	  	if(ScSamlightClientCtrl1->ScIsMarking()==0)  //���
		      break;
	  }
      }
      ScSamlightClientCtrl1->ScStopMarking();
      StatusInfo = "Idle!";

      //�������
      //enable_all_windows(1);
      return 1;
}

void TFormSamLight::OnStopMarking()
{
      if(IsRunning)
          ScSamlightClientCtrl1->ScStopMarking();
      else
          throw Exception("SAM light û�����У�");
}

//ɾ����ǰ��JOB
void TFormSamLight::OnNewJob()
{
    if(IsRunning)
      	ScSamlightClientCtrl1->ScExecCommand(3);
}

void  TFormSamLight::ImportFile(String  aEntityName, String aFileName)
{
     if(IsRunning)
     {
        long flags = scComSAMLightClientCtrlImportFlagKeepOrder|scComSAMLightClientCtrlImportFlagReadPenInfo;  //
        long  ret = ScSamlightClientCtrl1->ScImport(WideString(aEntityName),WideString(aFileName),WideString("dxf"),0.1,flags);
        if( ret == 0)
            throw Exception("����ʧ��!");

         // now we transform it to fit inside 0,0,20,20
         /*
         double outline_min_x,outline_min_y,outline_max_x,outline_max_y;
         outline_min_x = ScSamlightClientCtrl1->ScGetEntityOutline(WideString(aEntityName),0);
         outline_min_y = ScSamlightClientCtrl1->ScGetEntityOutline(WideString(aEntityName),1);
         outline_max_x = ScSamlightClientCtrl1->ScGetEntityOutline(WideString(aEntityName),3);
         outline_max_y = ScSamlightClientCtrl1->ScGetEntityOutline(WideString(aEntityName),4);

         // first we scale it that the larger side has 20
         double scale_x = 20. / (outline_max_x-outline_min_x);
         double scale_y = 20. / (outline_max_y-outline_min_y);
         double scale = scale_x;
         if(scale_y < scale)
            scale = scale_y;
         ScSamlightClientCtrl1->ScScaleEntity(WideString(aEntityName),scale,scale,1.0);

         outline_min_x = ScSamlightClientCtrl1->ScGetEntityOutline(WideString(aEntityName),0);
         outline_min_y = ScSamlightClientCtrl1->ScGetEntityOutline(WideString(aEntityName),1);
         ScSamlightClientCtrl1->ScTranslateEntity(WideString(aEntityName),-outline_min_x,-outline_min_y,0.);
         */
     }
}

void TFormSamLight::ScGetWorkingArea(double& minx,double& miny,double& minz,
                                          double& maxx,double& maxy,double& maxz)
{
     minx = ScSamlightClientCtrl1->ScGetWorkingArea(0);
     miny = ScSamlightClientCtrl1->ScGetWorkingArea(1);
     minz = ScSamlightClientCtrl1->ScGetWorkingArea(2);
     maxx = ScSamlightClientCtrl1->ScGetWorkingArea(3);
     maxy = ScSamlightClientCtrl1->ScGetWorkingArea(4);
     maxz = ScSamlightClientCtrl1->ScGetWorkingArea(5);
}

void TFormSamLight::ScGetEntityOutline2D(String EntityName, double* MinX,
                    double* MinY, double* MaxX, double* MaxY )
{
     ScSamlightClientCtrl1->ScGetEntityOutline2D(WideString(EntityName),MinX,
                MinY,MaxX,MaxY);
}

void  TFormSamLight::RedLightControl(bool bOpen)
{
    if(IsRunning)
    {
      if(bOpen)
      {
         //ScSamlightClientCtrl1->ScSetPen(1);    //����һ�ű�
         ScSamlightClientCtrl1->ScSetLongValue(8,1);   //���ù��������
         ScSamlightClientCtrl1->ScSetLongValue(9,5);   //Enable set
         ScSamlightClientCtrl1->ScSetLongValue(4,4);
      }
      else
      {
         ScSamlightClientCtrl1->ScSetLongValue(4,0);
      }
    }
}

//��ȡ��������
long  TFormSamLight::ReadInputOp()
{
   if(IsRunning)
   {
      return ScSamlightClientCtrl1->ScGetLongValue(4);
   }
   else
      throw Exception("SAM light û�����У�");

}

long TFormSamLight::ReadScanHeadStatus()
{
   if(IsRunning)
       return  ScSamlightClientCtrl1->ScGetLongValue(2);
   else
      throw Exception("SAM light û�����У�");
}

//CmdID: 48����ʾ��ӡ�Ի���
//
long TFormSamLight::ScExecCommand(long CmdID)
{
   if(IsRunning)
       return  ScSamlightClientCtrl1->ScExecCommand(CmdID);
   else
      throw Exception("SAM light û�����У�");
}

//-----------------------------���������-------------------------------------
double  TFormSamLight::ReadLaserMaxPower()
{
   if(IsRunning)
        return ScSamlightClientCtrl1->ScGetDoubleValue(20); //�����
   else
        throw Exception("SAM light û�����У�");
}

void   TFormSamLight::writeLaserMaxPower(double aMaxPower)
{
   if(IsRunning)
        ScSamlightClientCtrl1->ScSetDoubleValue(20,aMaxPower); //�����
   else
        throw Exception("SAM light û�����У�");
}

void  TFormSamLight::SetPen(long aPenID)
{
   if(IsRunning)
        ScSamlightClientCtrl1->ScSetPen(aPenID);
   else
        throw Exception("SAM light û�����У�");
}

void  TFormSamLight::SetLaserPen(long  aPenID, double  aPower,double aSpeed,double aFreq)
{
    if(IsRunning)
    {
        ScSamlightClientCtrl1->ScSetPen(aPenID);
        ScSamlightClientCtrl1->ScSetDoubleValue(17,aPower);
        ScSamlightClientCtrl1->ScSetDoubleValue(4,aSpeed);
        ScSamlightClientCtrl1->ScSetDoubleValue(6,aFreq*1000);
    }
    else
        throw Exception("SAM light û�����У�");
}

MLaserPen*  TFormSamLight::GetLaserPen(long  aPenID)
{
    if(IsRunning)
    {
        MLaserPen*  aPen = new  MLaserPen(NULL);

        ScSamlightClientCtrl1->ScSetPen(aPenID);
        double aPower = ScSamlightClientCtrl1->ScGetDoubleValue(17);
        double aSpeed = this->ScSamlightClientCtrl1->ScGetDoubleValue(4);
        double aFreq = this->ScSamlightClientCtrl1->ScGetDoubleValue(6)/1000.0;

        aPen->PenID = aPenID;
        aPen->PenPower = aPower;
        aPen->PenSpeed = aSpeed;
        aPen->PenFreq = aFreq;

        return aPen;
    }
    else
         throw Exception("SAM light û������");
}





//long ScOpticMatrixTranslate(double X, double Y, double Z)
//long ScOpticMatrixRotate(double CenterX, double CenterY, double Angle)
//long ScOpticMatrixScale(double ScaleX, double ScaleY)
//long ScOpticMatrixReset()

//long ScSetHead (long HeadID)

//long ScIsMarking()    : �������ڼ�����Ƿ����  WaitForMarkEnd = 0 ��ScMarkEntityByName��
//long ScStopMarking()
//long ScSetMarkFlags(long Flags)
//long ScGetMarkFlags()
//long ScSwitchLaser(long on_off)
//long ScMoveAbs(double x,double y,double z)
//long ScSetPen(long pen),long ScGetPen(long *pen)  : start from 1
//long ScMarkEntityByName(BSTR EntityName, long WaitForMarkEnd)


//long ScTranslateEntity(BSTR EntityName, double X, double Y, double Z)
//long ScScaleEntity(BSTR EntityName, double ScaleX, double ScaleY, double ScaleZ)
//long ScRotateEntity(BSTR EntityName, double X, double Y, double Angle)
//long ScDeleteEntity(BSTR EntityName)
//long ScImport(BSTR EntityName, BSTR FileName,BSTR Type, double Resolution, long Flags)




