//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitNewProject.h"
#include "UnitTool_Single.h"
#include "UnitTool_Class.h"
#include "3DP_Def.h"
#include "UnitFormMain.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TFormNewProject *FormNewProject;
//---------------------------------------------------------------------------
__fastcall TFormNewProject::TFormNewProject(TComponent* Owner)
        : TForm(Owner)
{

}
//------------------------------------------------------------------------------
void TFormNewProject::Init()
{
     ProjectName = "";
     Description = "";
     SayWhat = "";

     ProjectFileName = "";                                                     //XXX.3dmanual
}
//------------------------------------------------------------------------------
String  TFormNewProject::readDescription()
{
     Memo_Des->Lines->Delimiter = '@';
     return Memo_Des->Lines->DelimitedText;
}

void  TFormNewProject::writeDescription(String  aDes)
{
     TStrings*  aList = new TStringList;
     aList->Delimiter = '@';
     aList->DelimitedText = aDes;

     Memo_Des->Lines = aList;
}

//------------------------------------------------------------------------------
String  TFormNewProject::readSayWhat()
{
     Memo_Say->Lines->Delimiter = '@';
     return Memo_Say->Lines->DelimitedText;
}

void  TFormNewProject::writeSayWhat(String aSayWhat)
{
     TStrings*  aList = new TStringList;
     aList->Delimiter = '@';
     aList->DelimitedText = aSayWhat;

     Memo_Say->Lines = aList;
}
//------------------------------------------------------------------------------
//��������
String  TFormNewProject::readProjectName()
{
    return EditProjectName->Text;
}

void  TFormNewProject::writeProjectName(String aProjectName)
{
    EditProjectName->Text = aProjectName;
}

//------------------------------------------------------------------------------
//����Ŀ¼
String  TFormNewProject::readProjectLocation()
{
    return GetSaveProjectDir();
}

//------------------------------------------------------------------------------
//ָ��Ŀ¼���ɹ��ã�
void __fastcall TFormNewProject::BitBtn_OKClick(TObject *Sender)
{
    //1�����
    CheckNULLStr( ProjectName, "�������Ʋ���Ϊ�գ�" );

    //2������
    String  aProjectFileName;
    if(IsProjectExists(aProjectFileName) == true)
    {
        if(!(MessageDlg("�����ļ�("+aProjectFileName+")�Ѿ����ڣ��Ƿ񸲸�?",
               mtInformation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes ) )
        return;
    }

    //��������Ŀ¼���ļ�
    CheckAndMakeDirectory(ProjectLocation + "\\" + ProjectName);
    save_variables(aProjectFileName);

    //2�������ļ����Խ�����
    fProjectFileName = aProjectFileName;

    ModalResult = mrOk;
}

void  TFormNewProject::save_variables(String  aFileName)
{
    String  aVarFile = aFileName;
    ofstream  out(aVarFile.c_str(),ios_base::out | ios_base::binary);
    if(!out)  return; //�ļ�������

    save_string(out,ProjectName);
    save_string(out,Description);
    save_string(out,SayWhat);

    out.close();
}

bool  TFormNewProject::IsProjectExists(String& aProjectFileName)
{
    CheckNULLStr( ProjectName, "�������Ʋ���Ϊ�գ�" );
    
    aProjectFileName = ProjectLocation + "\\" + ProjectName + "\\" + ProjectName +  C_PrjExt;
    if(FileExists(aProjectFileName))
         return true;
    return false;
}

//---------------------------------------------------------------------------
//�س����ɹ��ã�
void __fastcall TFormNewProject::FormShow(TObject *Sender)
{
     ::SetWindowPos( Handle,HWND_NOTOPMOST,0, 0, Width, Height, SWP_NOMOVE);
}
//---------------------------------------------------------------------------

