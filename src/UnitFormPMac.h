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

       void  MotorJogInc(int  iMotorNumber);   //�����˶���
       void  MotorJobDec(int  iMotorNumber);
       void  MotorStop(int  iMotorNumber); //ֹͣ
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
//LockPmac()--------------------ReleasePmac()     //��ֹ����
//PmacSetCriticalVars()                           //�����Ż�
//PmacAbortDPRTest()                              //ֹͣ����DPR
//PmacConfigure()                                 //���öԻ��򵯳�
//PmacGetDpramAvailable()                         //�Ƿ�����ã�
//PmacInBootStrapMode()                           //�Ƿ���BootStrapģʽ,���ڸ��¹̼�
//PmacDPRTest()

/*ascII ͨ�ź���*/
//PmacFlush()                                     //ȡ������������
//PmacGetAsciiComm(),Set                              //���ص�ǰ��ͨ��ģʽ
//PmacBUSGetBuffer()                              //��ѯ��Ӧ
//PmacGetControlResponse(),PmacGetControlResponseEx(): //����һ�������ַ�and ������Ӧ
//PmacGetLineEx()                                 //��ȡa line response
//PmacGetResponseEx()                             //
//PmacReadReady()
//PmacSendCharA()
//PmacSendCommand();                        //����һ���ַ����������Ӧ��better than GetResponse
//PmacSendLineA()

//PmacAbortDownload();     //��������
//PmacAddDownloadFile() ,PmacMultiDownload()       //download each file listed within a text file;
//PmacGetVariable()            //��ñ���

//---------------------------------------------------------------------------
extern PACKAGE TFormPmac *FormPmac;
//---------------------------------------------------------------------------
#endif



