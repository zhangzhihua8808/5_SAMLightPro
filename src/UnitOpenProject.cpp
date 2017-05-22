//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitOpenProject.h"
#include "UnitTool_Single.h"
#include "UnitTool_Class.h"
#include "3DP_Def.h"
#include "UnitFormMain.h"
#include "UnitTool_classExtend.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TFormOpenProject *FormOpenProject;
//---------------------------------------------------------------------------
__fastcall TFormOpenProject::TFormOpenProject(TComponent* Owner)
        : TForm(Owner)
{
    fProject = NULL;
}
//------------------------------------------------------------------------------
void TFormOpenProject::Init(MAMProject*  aProject)
{
     fProject = aProject;

     EditProjectName->Text = "";
     Memo_Des->Lines->Clear();
     Memo_Say->Lines->Clear();

     fProjectFileName = "";                                                     //XXX.3dmanual
}

//------------------------------------------------------------------------------
String  TFormOpenProject::readDescription()
{
     Memo_Des->Lines->Delimiter = '@';
     return Memo_Des->Lines->DelimitedText;
}

void  TFormOpenProject::writeDescription(String  aDes)
{
     TStrings*  aList = new TStringList;
     aList->Delimiter = '@';
     aList->DelimitedText = aDes;

     Memo_Des->Lines = aList;
}

//------------------------------------------------------------------------------
String  TFormOpenProject::readSayWhat()
{
     Memo_Say->Lines->Delimiter = '@';
     return Memo_Say->Lines->DelimitedText;
}

void  TFormOpenProject::writeSayWhat(String aSayWhat)
{
     TStrings*  aList = new TStringList;
     aList->Delimiter = '@';
     aList->DelimitedText = aSayWhat;

     Memo_Say->Lines = aList;
}

//------------------------------------------------------------------------------
//��������
String  TFormOpenProject::readProjectName()
{
    return EditProjectName->Text;
}

void  TFormOpenProject::writeProjectName(String aProjectName)
{
    EditProjectName->Text = aProjectName;
}

//------------------------------------------------------------------------------
String  TFormOpenProject::readProjectLocation()
{
    if(fProjectFileName == "")  return "";

    return ExtractFileDir(fProjectFileName);
}

//------------------------------------------------------------------------------
void __fastcall TFormOpenProject::FormShow(TObject *Sender)
{
     ::SetWindowPos( Handle,HWND_NOTOPMOST,0, 0, Width, Height, SWP_NOMOVE);

     BitBtn1->Click();
}
//---------------------------------------------------------------------------
//�򿪹���
void __fastcall TFormOpenProject::BitBtn1Click(TObject *Sender)
{
     OpenDialog1->Filter = "Project File(*"+C_PrjExt+")|*"+C_PrjExt;
     if( OpenDialog1->Execute() != true )
           return;

     String  a3dManualFile = OpenDialog1->FileName;     //�����ļ�
     fProject->ProjectFileName = a3dManualFile;

     load_variables(a3dManualFile);
}

//------------------------------------------------------------------------------
void  TFormOpenProject::load_variables(String  aFileName)
{
     //load_variables
     String  aVarFile = aFileName;
     ifstream  in(aVarFile.c_str() ,ios_base::in | ios_base::binary);
     if(!in)  return; //�ļ�������

     ProjectName = load_string(in);
     Description = load_string(in);
     SayWhat = load_string(in);

     in.close();
}

void  TFormOpenProject::save_variables(String  aFileName)
{
     String  aVarFile = aFileName;
     ofstream  out(aVarFile.c_str(),ios_base::out | ios_base::binary);
     if(!out)  return; //�ļ�������

     save_string(out,ProjectName);
     save_string(out,Description);
     save_string(out,SayWhat);

     out.close();
}
//---------------------------------------------------------------------------
void __fastcall TFormOpenProject::BitBtn_OKClick(TObject *Sender)
{
     CheckNULLStr( ProjectName, "�������Ʋ���Ϊ�գ�" );
     CheckNULLStr(fProject->ProjectFileName,"�����ļ�����Ϊ��");

     save_variables(fProject->ProjectFileName);
     fProject->ProjectName = ProjectName;

     ModalResult = mrOk;
}
//---------------------------------------------------------------------------

