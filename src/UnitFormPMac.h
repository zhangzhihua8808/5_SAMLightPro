//---------------------------------------------------------------------------

#ifndef UnitFormPMacH
#define UnitFormPMacH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "PCOMMSERVERLib_OCX.h"
#include <OleCtrls.hpp>
#include <ComCtrls.hpp>

class MConfigVar;
//---------------------------------------------------------------------------
class TFormPmac : public TForm
{
__published:	// IDE-managed Components
        TPmacDevice *PmacDevice1;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
        __fastcall TFormPmac(TComponent* Owner);

    private:
        bool   fIsOpened;
        long int  fDevice;
        String  fConnectStatus;
        void    writeStatusPanel(String aText);
        TStatusPanel*  fStatusPanel;
        TStrings*  fMotorHomeMap;
        float  fFirstGearPos;
    public:
       __property  bool   IsOpened = {read=fIsOpened,write=fIsOpened};
       __property  String ConnectStatus = {read=fConnectStatus,write=fConnectStatus};
       __property  String StatusInfo = {write=writeStatusPanel};
       __property  TStatusPanel* StatusPanel = {read=fStatusPanel,write=fStatusPanel};
       __property  float  FirstGearPos = {read=fFirstGearPos,write=fFirstGearPos};
    public:
       void  Init();
       void  PMacOpen();
       void  PMacClose();

       void  MotorJogInc(int  iMotorNumber);   //正向运动；
       void  MotorJobDec(int  iMotorNumber);
       void  MotorStop(int  iMotorNumber); //停止
       String  GetVarValueTrimCRLF(String  VarName);


       void  MotorHome(int iMotorNumber);
       void  MotorHomeUntilFinish(int iMotorNumber);


       //void  LightControl(bool  bOn = true);
       //void  DoProgramUntilFinish(String  aChar,String aProgramID,String  aPos);
       //bool  IsActionFinish(String  aVarName);
       //void  DownLoadFile(String  aFileName,short& aSuccess);

       void  MotorRalateModeUntilFinish(int iMotorNumber,int iPulseCount,String aVarName,String aVarValue="1");
       void  MotorAbsoluteModeUntilFinish(int iMotorNumber,int iPos,String aVarName,String aVarValue="1");
       void  SendCommand(String aCmdStr);
       void  WaitCommandFinish(String aVarName, String  aFinishSymbol);
       
       void  VarNameSet(String aVarName,String  bOn);


       void  SendCommand(MConfigVar*  aCmd);
       void  SpreadPowder(int aGear);
       float ReadO2Percent();
       float ReadPresureValue();
       int  GetConfigVarValue(MConfigVar*  aCmd);
};


//OpenPmacDevice()--------------ClosePmacDevice()
//PmacSelect()
//LockPmac()--------------------ReleasePmac()     //禁止干扰
//PmacSetCriticalVars()                           //例程优化
//PmacAbortDPRTest()                              //停止测试DPR
//PmacConfigure()                                 //配置对话框弹出
//PmacGetDpramAvailable()                         //是否可利用？
//PmacInBootStrapMode()                           //是否处于BootStrap模式,用于更新固件
//PmacDPRTest()

/*ascII 通信函数*/
//PmacFlush()                                     //取消命令，清除队列
//PmacGetAsciiComm(),Set                              //返回当前的通信模式
//PmacBUSGetBuffer()                              //查询响应
//PmacGetControlResponse(),PmacGetControlResponseEx(): //发送一个控制字符and 返回响应
//PmacGetLineEx()                                 //获取a line response
//PmacGetResponseEx()                             //
//PmacReadReady()
//PmacSendCharA()
//PmacSendCommand();                        //发送一个字符串，清除响应，better than GetResponse
//PmacSendLineA()

//PmacAbortDownload();     //放弃下载
//PmacAddDownloadFile() ,PmacMultiDownload()       //download each file listed within a text file;
//PmacGetVariable()            //获得变量

//---------------------------------------------------------------------------
extern PACKAGE TFormPmac *FormPmac;
//---------------------------------------------------------------------------
#endif



