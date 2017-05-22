//---------------------------------------------------------------------------

#ifndef UnitNewProjectH
#define UnitNewProjectH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>

//---------------------------------------------------------------------------
class TFormNewProject : public TForm
{
  __published:	// IDE-managed Components
        TToolBar *ToolBar1;
        TToolButton *ToolButton1;
        TBitBtn *BitBtn_OK;
        TBitBtn *BitBtn_Cancel;
        TPanel *Panel1;
        TLabel *Label1;
        TLabel *Label2;
        TEdit *EditProjectName;
        TLabel *Label3;
        TMemo *Memo_Des;
        TMemo *Memo_Say;
        void __fastcall BitBtn_OKClick(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        
  private:	// User declarations
  public:		// User declarations
        __fastcall TFormNewProject(TComponent* Owner);


  private:
       String  readProjectName();                                               //工程名称
       void    writeProjectName(String aProjectName);

       String  readDescription();
       void    writeDescription(String  aDes);

       String  readSayWhat();
       void    writeSayWhat(String aSayWhat);

       String  fProjectFileName;                                                //XXX.3dmanual
       bool    IsProjectExists(String& aProjectFileName);
  public:
       __property  String  ProjectName = {read=readProjectName,write=writeProjectName};       //工程名称
       __property  String  Description = {read=readDescription,write=writeDescription};       //工程简介
       __property  String  SayWhat = {read=readSayWhat,write=writeSayWhat};                   //工程说明
       __property  String  ProjectFileName = {read=fProjectFileName,write=fProjectFileName};  //完整路径
       __property  String  ProjectLocation = {read=readProjectLocation};
  public:
       void Init();
       void save_variables(String  aFileName);
       String  readProjectLocation();
};
//---------------------------------------------------------------------------
extern PACKAGE TFormNewProject *FormNewProject;
//---------------------------------------------------------------------------
#endif
