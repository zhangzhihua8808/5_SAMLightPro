//---------------------------------------------------------------------------

#ifndef UnitFormTCPH
#define UnitFormTCPH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>

//---------------------------------------------------------------------------
class TFormTCPConnect : public TForm
{
__published:	// IDE-managed Components
        TButton *Button1;
        TButton *Button2;
        TToolBar *ToolBar1;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TTabSheet *TabSheet2;
        TButton *Btn_Connect;
        TLabel *Label4;
        TLabel *Label6;
        TEdit *Ed_SamStatus;
        TEdit *Ed_SamPort;
        TEdit *Ed_SamIP;
        TButton *BtnDisconnect;
        TLabel *Label7;
        TButton *Btn_Test;
        TLabel *Label1;
        TEdit *Ed_DeviceID;
        TLabel *Label2;
        TButton *Button3;
        TLabel *Label3;
        TEdit *Ed_PMacStatus;
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall Btn_ConnectClick(TObject *Sender);
        void __fastcall BtnDisconnectClick(TObject *Sender);
        void __fastcall Btn_TestClick(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormTCPConnect(TComponent* Owner);

   protected:
       String  readSamLightIP();
       void    writeSamLightIP(String aIp);

       String  readSamLightPort();
       void    writeSamLightPort(String  aPort);

       void    writeSamLightStatus(String aStatus);
       void    writePMacStatus(String aStatus);

       String  readPMacDevice();
       void    writePMacDevice(String aDevice);

       long    load_variables();
       long    save_variables();
   public:
       __property  String  SamLightIP = {read=readSamLightIP,write=writeSamLightIP};
       __property  String  SamLightPort = {read=readSamLightPort,write=writeSamLightPort};
       __property  String  SamLightStatus = {write=writeSamLightStatus};
       __property  String  PMacStatus = {write=writePMacStatus};
       __property  String  PMacDevice = {read=readPMacDevice,write=writePMacDevice};

   public:
       void  Init();
};
//---------------------------------------------------------------------------
extern PACKAGE TFormTCPConnect *FormTCPConnect;
//---------------------------------------------------------------------------
#endif
