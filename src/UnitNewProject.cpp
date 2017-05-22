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
//工程名称
String  TFormNewProject::readProjectName()
{
    return EditProjectName->Text;
}

void  TFormNewProject::writeProjectName(String aProjectName)
{
    EditProjectName->Text = aProjectName;
}

//------------------------------------------------------------------------------
//工作目录
String  TFormNewProject::readProjectLocation()
{
    return GetSaveProjectDir();
}

//------------------------------------------------------------------------------
//指定目录（可共用）
void __fastcall TFormNewProject::BitBtn_OKClick(TObject *Sender)
{
    //1、检查
    CheckNULLStr( ProjectName, "工程名称不能为空！" );

    //2、测试
    String  aProjectFileName;
    if(IsProjectExists(aProjectFileName) == true)
    {
        if(!(MessageDlg("工程文件("+aProjectFileName+")已经存在，是否覆盖?",
               mtInformation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes ) )
        return;
    }

    //创建工程目录及文件
    CheckAndMakeDirectory(ProjectLocation + "\\" + ProjectName);
    save_variables(aProjectFileName);

    //2、工程文件可以建立了
    fProjectFileName = aProjectFileName;

    ModalResult = mrOk;
}

void  TFormNewProject::save_variables(String  aFileName)
{
    String  aVarFile = aFileName;
    ofstream  out(aVarFile.c_str(),ios_base::out | ios_base::binary);
    if(!out)  return; //文件不存在

    save_string(out,ProjectName);
    save_string(out,Description);
    save_string(out,SayWhat);

    out.close();
}

bool  TFormNewProject::IsProjectExists(String& aProjectFileName)
{
    CheckNULLStr( ProjectName, "工程名称不能为空！" );
    
    aProjectFileName = ProjectLocation + "\\" + ProjectName + "\\" + ProjectName +  C_PrjExt;
    if(FileExists(aProjectFileName))
         return true;
    return false;
}

//---------------------------------------------------------------------------
//回车（可共用）
void __fastcall TFormNewProject::FormShow(TObject *Sender)
{
     ::SetWindowPos( Handle,HWND_NOTOPMOST,0, 0, Width, Height, SWP_NOMOVE);
}
//---------------------------------------------------------------------------

