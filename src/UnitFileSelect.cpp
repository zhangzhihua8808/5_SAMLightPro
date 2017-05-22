//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitFileSelect.h"
#include "UnitTool_Single.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormFileCombine *FormFileCombine;
//---------------------------------------------------------------------------
__fastcall TFormFileCombine::TFormFileCombine(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormFileCombine::Button1Click(TObject *Sender)
{
    SetFileName(Edit1); 
}
//---------------------------------------------------------------------------
void  TFormFileCombine::SetFileName(TEdit* aEdit)
{
    String  aOutDir = ApplicationPath() + "\\TestModel";

    OpenDialog1->Filter = "模型文件(*.cli)|*.cli";
    OpenDialog1->InitialDir = aOutDir;
    OpenDialog1->DefaultExt = ".cli";

    if(OpenDialog1->Execute() != mrOk)
         return;

    aEdit->Text = OpenDialog1->FileName;
}
void __fastcall TFormFileCombine::Button2Click(TObject *Sender)
{
     SetFileName(Edit2);
}
//---------------------------------------------------------------------------
void __fastcall TFormFileCombine::Button3Click(TObject *Sender)
{
     SetFileName(Edit3);    
}
//---------------------------------------------------------------------------
void __fastcall TFormFileCombine::Button4Click(TObject *Sender)
{
     SetFileName(Edit4);    
}
//---------------------------------------------------------------------------
