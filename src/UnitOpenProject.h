//---------------------------------------------------------------------------

#ifndef UnitOpenProjectH
#define UnitOpenProjectH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>


class MAMProject;
//---------------------------------------------------------------------------
class TFormOpenProject : public TForm
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
        TBitBtn *BitBtn1;
        TToolButton *ToolButton2;
        TOpenDialog *OpenDialog1;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall BitBtn_OKClick(TObject *Sender);
        
  private:	// User declarations
  public:		// User declarations
        __fastcall TFormOpenProject(TComponent* Owner);


  private:
       String  readProjectName();                                               //工程名称
       void  writeProjectName(String aProjectName);

       String  readProjectLocation();                                           //工程位置
       String  fProjectFileName;                                                //XXX.3dmanual

       String  readDescription();
       void    writeDescription(String  aDes);
       String  readSayWhat();
       void    writeSayWhat(String aSayWhat);

       MAMProject*  fProject;
  public:
       __property  String  ProjectName = {read=readProjectName,write=writeProjectName};
       __property  String  ProjectLocation = {read=readProjectLocation};
       __property  String  ProjectFileName = {read=fProjectFileName,write=fProjectFileName};  //完整路径
       __property  String  Description = {read=readDescription,write=writeDescription};
       __property  String  SayWhat = {read=readSayWhat,write=writeSayWhat};
       __property  MAMProject*  Project = {read=fProject};
  public:
       void Init(MAMProject*  aProject);
       void load_variables(String  aFileName);
       void  save_variables(String  aFileName);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormOpenProject *FormOpenProject;
//---------------------------------------------------------------------------
#endif
