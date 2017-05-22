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
//枚举窗口回调函数，功能：找到与子串匹配的窗口caption
//---------------------------------------------------------------------------
bool CALLBACK  EnumFunc( HWND hWnd, LPARAM lParam )
{
  char aWindowName[255];
  ::GetWindowText( hWnd, aWindowName, 255 );

  if( hWnd == NULL )
  {
    gFindWindow = NULL;
    return false ;       //查询结束
  }
  else if( IsMatchString( UpperCase( aWindowName ), UpperCase(gNeedFindWindow) ) )
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

//---------------------------------------------------------------------------
//启动程序
bool  TFormSamLight::ConfirmSamLightRun()
{
    String  aProcessName = "sam_light.exe";
    int     iTryTime = 0;

    try
    {
        //进程不存在
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
        if(aStep == 2)  //经历了启动的过程
        {
           //找窗口连接
           while(FindWindow("SAMLight - [主菜单 ]") == NULL && iTryTime < 100)
           {
               iTryTime++;
               ::Sleep(500);
           }
           //超时的检查
           if(iTryTime>=100)
           {
               gError->Warn("启动sam_light失败！");
               return false;
           }
        }
        return true;
    }
    catch(Exception& ae)
    {
        throw Exception("ConfirmApplication出错!ConfirmSamApplication:"+ae.Message);
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

    //if(aHead == -1)  //没有实物卡
    //     return false;

    return true;
}


//------------------------------连接--------------------------------------------
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
       StatusInfo = "振镜控制卡连接成功(IP:" + IP + ",Port:" + Port + ")";

       String  aSamLightShow = gIniFile->ReadString("SamLight","IsShow","true");
       //显示控制
       if(aSamLightShow.UpperCase() != "TRUE")
            ScSamlightClientCtrl1->ScShowApp(0);      //0: 隐藏，5: 显示
       else
            ScSamlightClientCtrl1->ScShowApp(5);
    }
    else
    {
       fIsConnected = false;
       fConnectStatus = "Not Connected";
       StatusInfo = "振镜控制卡连接失败(IP:" + IP + ",Port:" + Port + ")";
    }
}

//----------------------------断开----------------------------------------------
void  TFormSamLight::SamLightDisConnect()
{
    if(fIsConnected)
    {
        ScSamlightClientCtrl1->ScCloseEthernetConnection();

        fIsConnected = false;
        fConnectStatus = "Not Connected";
        StatusInfo = "振镜控制卡连接断开";
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

    if(ScSamlightClientCtrl1->ScIsRunning() == 0)     //只能保证COM在运行
          return false;

    if(GetRealRunning() == false)                     //是否连接上了
    {
         throw Exception("与SamLight 控制卡没有连接!");
         //return false;
    }

    return true;
}

//弹出一个对话框，作为测试通信使用
void  TFormSamLight::ExecuteTest()
{
    if(IsRunning == true)
        ScSamlightClientCtrl1->ScExecCommand(1);
    else
        throw Exception("SamLight 软件没有运行!");
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


//动态的改变文本；
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



//entity_name_to_mark : 要Mark的实体名称，如果为"", MarkALL
long TFormSamLight::mark_entity(String entity_name_to_mark)
{
     if(IsRunning == false)
        return 0;

     StatusInfo = "Sending Objects!";

     long mark_flags = 0x0 ;
     ScSamlightClientCtrl1->ScSetMarkFlags(mark_flags);

     //立即返回
     ScSamlightClientCtrl1->ScMarkEntityByName(WideString(entity_name_to_mark),0);
     StatusInfo = "Marking!";



     long i = 0;

     //禁止操作
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
	  	if(ScSamlightClientCtrl1->ScIsMarking()==0)  //完成
		      break;
	  }
      }
      ScSamlightClientCtrl1->ScStopMarking();
      StatusInfo = "Idle!";

      //允许操作
      //enable_all_windows(1);
      return 1;
}

void TFormSamLight::OnStopMarking()
{
      if(IsRunning)
          ScSamlightClientCtrl1->ScStopMarking();
      else
          throw Exception("SAM light 没有运行！");
}

//删除当前的JOB
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
            throw Exception("导入失败!");

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
         //ScSamlightClientCtrl1->ScSetPen(1);    //设置一号笔
         ScSamlightClientCtrl1->ScSetLongValue(8,1);   //设置光耦输出组
         ScSamlightClientCtrl1->ScSetLongValue(9,5);   //Enable set
         ScSamlightClientCtrl1->ScSetLongValue(4,4);
      }
      else
      {
         ScSamlightClientCtrl1->ScSetLongValue(4,0);
      }
    }
}

//读取光耦输入
long  TFormSamLight::ReadInputOp()
{
   if(IsRunning)
   {
      return ScSamlightClientCtrl1->ScGetLongValue(4);
   }
   else
      throw Exception("SAM light 没有运行！");

}

long TFormSamLight::ReadScanHeadStatus()
{
   if(IsRunning)
       return  ScSamlightClientCtrl1->ScGetLongValue(2);
   else
      throw Exception("SAM light 没有运行！");
}

//CmdID: 48：显示打印对话框；
//
long TFormSamLight::ScExecCommand(long CmdID)
{
   if(IsRunning)
       return  ScSamlightClientCtrl1->ScExecCommand(CmdID);
   else
      throw Exception("SAM light 没有运行！");
}

//-----------------------------最大功率设置-------------------------------------
double  TFormSamLight::ReadLaserMaxPower()
{
   if(IsRunning)
        return ScSamlightClientCtrl1->ScGetDoubleValue(20); //最大功率
   else
        throw Exception("SAM light 没有运行！");
}

void   TFormSamLight::writeLaserMaxPower(double aMaxPower)
{
   if(IsRunning)
        ScSamlightClientCtrl1->ScSetDoubleValue(20,aMaxPower); //最大功率
   else
        throw Exception("SAM light 没有运行！");
}

void  TFormSamLight::SetPen(long aPenID)
{
   if(IsRunning)
        ScSamlightClientCtrl1->ScSetPen(aPenID);
   else
        throw Exception("SAM light 没有运行！");
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
        throw Exception("SAM light 没有运行！");
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
         throw Exception("SAM light 没有运行");
}





//long ScOpticMatrixTranslate(double X, double Y, double Z)
//long ScOpticMatrixRotate(double CenterX, double CenterY, double Angle)
//long ScOpticMatrixScale(double ScaleX, double ScaleY)
//long ScOpticMatrixReset()

//long ScSetHead (long HeadID)

//long ScIsMarking()    : 可以用于检查打标是否完成  WaitForMarkEnd = 0 在ScMarkEntityByName中
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




