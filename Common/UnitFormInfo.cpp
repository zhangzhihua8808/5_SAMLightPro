//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitFormInfo.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TInfoForm *InfoForm;
//---------------------------------------------------------------------------
__fastcall TInfoForm::TInfoForm(TComponent* Owner)
        : TForm(Owner)
{
    
}
//---------------------------------------------------------------------------
bool  TInfoForm::IsDelete()
{
    return CheckBox1->Checked;
}

void  TInfoForm::Init(String  aCaption,String aMainInfo, String  aCheckInfo,bool bCheckVisible)
{
    this->Caption = aCaption;
    this->Label1->Text = aMainInfo;
    this->CheckBox1->Text = aCheckInfo;
    this->CheckBox1->Visible = bCheckVisible;
}

void __fastcall TInfoForm::FormShow(TObject *Sender)
{
    ::SetWindowPos( Handle,
                  HWND_NOTOPMOST,0, 0, Width, Height, SWP_NOMOVE);

}
//---------------------------------------------------------------------------

