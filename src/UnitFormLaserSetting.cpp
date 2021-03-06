//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitFormLaserSetting.h"
#include "UnitTool_ClassExtend.h"
#include "UnitFormLaserPen.h"
#include "UnitFormSamLight.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormLaserSetting *FormLaserSetting;
//---------------------------------------------------------------------------
__fastcall TFormLaserSetting::TFormLaserSetting(TComponent* Owner)
        : TForm(Owner)
{
     fLaserPens = new  MLaserPens;
     fSelectedLaserPen = NULL;

     fLaserPens->LoadFromFile(ApplicationPath() + "\\LaserPen.txt");
     fLaserPens->ToListView(ListView1);
}
//---------------------------------------------------------------------------
void TFormLaserSetting::Init()
{
     FormSamLight->LaserMaxPower = 500.0;
     String aMaxPower =  FloatToStr(FormSamLight->LaserMaxPower);
     LaserMaxPower = aMaxPower;
     fSelectedLaserPen = NULL;
}

String  TFormLaserSetting::readLaserMaxPower()
{
     return Edit_LaserMaxPower->Text;
}

void    TFormLaserSetting::writeLaserMaxPower(String aPower)
{
    Edit_LaserMaxPower->Text = aPower;
}

void __fastcall TFormLaserSetting::ListView1DblClick(TObject *Sender)
{
    //双击，编辑
    EditLaserPen(GetSelectedLaserPen(ListView1));
}
//---------------------------------------------------------------------------
void __fastcall TFormLaserSetting::Button2Click(TObject *Sender)
{
   EditLaserPen(GetSelectedLaserPen(ListView1));
}
//---------------------------------------------------------------------------
void TFormLaserSetting::EditLaserPen(MLaserPen* aItem)
{
   if(aItem == NULL)  throw Exception("请先选择编辑项");

   //选中
   fSelectedLaserPen = aItem;

   FormLaserPen->Init(aItem,StrToFloat(LaserMaxPower));
   if(FormLaserPen->ShowModal() != mrOk)  return;

   //更新
   aItem->PenName = FormLaserPen->PenName;
   aItem->PenPower = FormLaserPen->PenPower;
   aItem->PenSpeed = FormLaserPen->PenSpeed;
   aItem->PenFreq = FormLaserPen->PenFreq;

   aItem->ToListView(ListView1);
}

//------------------关闭--------------------------------------------------------
void __fastcall TFormLaserSetting::BitBtn1Click(TObject *Sender)
{
   FormSamLight->LaserMaxPower = StrToFloat(LaserMaxPower);
   fLaserPens->SaveToFile(ApplicationPath() + "\\LaserPen.txt");

   fSelectedLaserPen = GetSelectedLaserPen(ListView1);

/*
   //设置
   for(int i=0; i < fLaserPens->Count; i++)
   {
       MLaserPen*  aPen = fLaserPens->Items[i];

       MLaserPen*  aTargetPen = FormSamLight->GetLaserPen(aPen->PenID);
       if(aPen->IsEqual(aTargetPen))
       {
           delete aTargetPen;
           continue;
       }
       FormSamLight->SetLaserPen(aPen->PenID,StrToFloat(aPen->PenPower),StrToFloat(aPen->PenSpeed),
            StrToFloat(aPen->PenFreq));
   }
*/
}
//---------------------------------------------------------------------------


