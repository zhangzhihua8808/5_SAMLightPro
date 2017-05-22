//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitFormTCP.h"
#include "UnitTool_Single.h"
#include "UnitFormMain.h"
#include "UnitFormSamLight.h"
#include "UnitFormPMac.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormTCPConnect *FormTCPConnect;
//---------------------------------------------------------------------------
__fastcall TFormTCPConnect::TFormTCPConnect(TComponent* Owner)
        : TForm(Owner)
{
    SamLightIP = "127.0.0.1";
    SamLightPort = "350";
    PMacDevice = "0";
}
//---------------------------------------------------------------------------
void TFormTCPConnect::Init()
{
    //先初始值，然后读取变量
    load_variables();

    //当前的状态
    SamLightStatus = FormSamLight->ConnectStatus;
    PMacStatus = FormPmac->ConnectStatus;
}

long TFormTCPConnect::load_variables()
{
     //load_variables
     String  aVarFile = ApplicationPath() + "\\system\\RemoteLink.bin";
     ifstream  in(aVarFile.c_str() ,ios_base::in | ios_base::binary);
     if(!in)  return 0; //文件不存在

     SamLightIP = load_string(in);
     SamLightPort = load_string(in);
     PMacDevice = load_string(in);

     in.close();

     return 1;
}

long  TFormTCPConnect::save_variables()
{
     String  aVarFile = ApplicationPath() + "\\system\\RemoteLink.bin";
     ofstream  out(aVarFile.c_str(),ios_base::out | ios_base::binary);
     if(!out)  return 0; //文件不存在

     save_string(out,SamLightIP);
     save_string(out,SamLightPort);
     save_string(out,PMacDevice);

     out.close();

     return 1;
}

//------------------------------------------------------------------------------
String TFormTCPConnect::readSamLightIP()
{
    return Ed_SamIP->Text;
}

void   TFormTCPConnect::writeSamLightIP(String aIp)
{
    Ed_SamIP->Text = aIp;
}

//------------------------------------------------------------------------------
String  TFormTCPConnect::readSamLightPort()
{
    return Ed_SamPort->Text;
}

void   TFormTCPConnect::writeSamLightPort(String  aPort)
{
    Ed_SamPort->Text = aPort;
}

//------------------------------------------------------------------------------
void   TFormTCPConnect::writeSamLightStatus(String aStatus)
{
    Ed_SamStatus->Text = aStatus;
    if(aStatus == "Connected")
    {
        Ed_SamStatus->Color = clGreen;
        Btn_Connect->Enabled = false;
        BtnDisconnect->Enabled = true;
        Btn_Test->Enabled = true;
    }
    else
    {
        Ed_SamStatus->Color = clRed;
        Btn_Connect->Enabled = true;
        BtnDisconnect->Enabled = false;
        Btn_Test->Enabled = false;
    }
}

void  TFormTCPConnect::writePMacStatus(String aStatus)
{
    Ed_PMacStatus->Text = aStatus;

    if(aStatus == "Connected")
    {
        Ed_PMacStatus->Color = clGreen;
    }
    else
    {
        Ed_PMacStatus->Color = clRed;
    }
}

String  TFormTCPConnect::readPMacDevice()
{
    return StrToInt(Ed_DeviceID->Text);
}

void  TFormTCPConnect::writePMacDevice(String aDevice)
{
    Ed_DeviceID->Text = aDevice;
}

//---------------------------------------------------------------------------
//确定,并连接;
void __fastcall TFormTCPConnect::BitBtn1Click(TObject *Sender)
{
    save_variables();

    //samLight的连接
    if(FormSamLight->IsConnected == false)
    {
        Btn_Connect->Click();
    }
    //PMAC的连接
    if( FormPmac->IsOpened == false)
    {
        FormPmac->PMacOpen();
    }
}


//SamLight 连接
void __fastcall TFormTCPConnect::Btn_ConnectClick(TObject *Sender)
{
    FormSamLight->Init(SamLightIP,SamLightPort);
    FormSamLight->SamLightConnect();

    SamLightStatus = FormSamLight->ConnectStatus;
}
//---------------------------------------------------------------------------
//SamLight 断开
void __fastcall TFormTCPConnect::BtnDisconnectClick(TObject *Sender)
{
    FormSamLight->SamLightDisConnect();

    SamLightStatus = FormSamLight->ConnectStatus;
}


//---------------------------------------------------------------------------
void __fastcall TFormTCPConnect::Btn_TestClick(TObject *Sender)
{
    if(FormSamLight->IsRunning)
        FormSamLight->ExecuteTest();
}
//---------------------------------------------------------------------------

void __fastcall TFormTCPConnect::Button3Click(TObject *Sender)
{
    if(FormPmac->IsOpened == false)
    {
       FormPmac->PMacOpen();
       PMacStatus = FormPmac->ConnectStatus;
    }
}
//---------------------------------------------------------------------------

