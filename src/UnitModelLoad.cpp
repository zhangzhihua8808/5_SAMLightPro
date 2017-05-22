//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitModelLoad.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormLoadModel *FormLoadModel;
//---------------------------------------------------------------------------
__fastcall TFormLoadModel::TFormLoadModel(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void  TFormLoadModel::Init(String  aModelFileName)
{
    Edit1->Text = aModelFileName;
}

//-----------模型文件-----------------------------------------------------------
String  TFormLoadModel::readModelFile()
{
    return Edit1->Text;
}

void  TFormLoadModel::writeModelFile(String aModelFile)
{
    Edit1->Text = aModelFile;
}

void __fastcall TFormLoadModel::Button1Click(TObject *Sender)
{
    OpenDialog1->Filter = "工艺模型文件(*.mix)|*.mix";
    if(OpenDialog1->Execute() != mrOk)   return;

    ModelFileName = OpenDialog1->FileName;
}
//---------------------------------------------------------------------------

