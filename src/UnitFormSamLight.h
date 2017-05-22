//---------------------------------------------------------------------------

#ifndef UnitFormSamLightH
#define UnitFormSamLightH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "SAMLIGHT_CLIENT_CTRL_OCXLib_OCX.h"
#include <OleCtrls.hpp>
#include <ComCtrls.hpp>

class  MLaserPen;
//---------------------------------------------------------------------------
class TFormSamLight : public TForm
{
__published:	// IDE-managed Components
        TScSamlightClientCtrl *ScSamlightClientCtrl1;
private:	// User declarations

public:		// User declarations
        __fastcall TFormSamLight(TComponent* Owner);

   private:
       String  fIp;
       String  fPort;
       bool    fIsConnected;
       String  fConnectStatus;

       bool    fIsDebug;
       bool    readIsRunning();

       TStatusPanel*  fStatusPanel;
       void    writeStatusPanel(String aText);

       TStatusPanel*  fOperatePanel;
       void  writeOperatePanel(String aText);
       double  ReadLaserMaxPower();
       void    writeLaserMaxPower(double aMaxPower);
   public:
       __property  String IP = {read=fIp,write=fIp};
       __property  String Port = {read=fPort,write=fPort};
       __property  bool   IsConnected = {read=fIsConnected,write=fIsConnected};
       __property  String ConnectStatus = {read=fConnectStatus,write=fConnectStatus};
       __property  bool   IsDebug = {read=fIsDebug,write=fIsDebug};
       __property  bool   IsRunning = {read=readIsRunning};
       __property  TStatusPanel* StatusPanel = {read=fStatusPanel,write=fStatusPanel};
       __property  TStatusPanel* OperatePanel = {read=fOperatePanel,write=fOperatePanel};

       __property  String StatusInfo = {write=writeStatusPanel};
       __property  String OperateInfo = {write=writeOperatePanel};
       __property  double LaserMaxPower = {read=ReadLaserMaxPower,write=writeLaserMaxPower};
   public:
       void  Init(String aIP,String aPort);
       void  SamLightConnect();
       void  SamLightDisConnect();

       void  SamLightClose();
       void  ExecuteTest();
       void  DoResetSequence();
       void  DoChangeTextByName(String aEntityName,String aText);
       long  mark_entity(String entity_name_to_mark);
       void  OnStopMarking();
       void  OnNewJob();
       void  ImportFile(String  aEntityName, String aFileName);
       bool  ConfirmSamLightRun();

       bool  GetRealRunning();

       void ScGetWorkingArea(double& minx,double& miny,double& minz,
                             double& maxx,double& maxy,double& maxz);
       void ScGetEntityOutline2D(String EntityName, double *MinX, double *MinY, double
                             *MaxX, double *MaxY );

       void  RedLightControl(bool bOpen= true);
       long  ReadInputOp();
       long  ReadScanHeadStatus();
       long  ScExecCommand(long CmdID);
       void  SetLaserPen(long  aPenID, double  aPower,double aSpeed,double aFreq);
       void  SetPen(long aPenID);
       void  TranslateEntity(String  entityName,double aX,double aY);
       MLaserPen*  GetLaserPen(long  aPenID);

};
//---------------------------------------------------------------------------
extern PACKAGE TFormSamLight *FormSamLight;

HWND FindWindowLike(String aWindowName, bool IsLike);
HWND FindWindowLike(String aWindowName);
HWND FindWindow(String aWindowName);
bool  CALLBACK  EnumFunc(HWND  hWnd,   LPARAM lParam);

extern String gNeedFindWindow;
extern HWND gFindWindow;
//---------------------------------------------------------------------------
#endif
