//---------------------------------------------------------------------------

#ifndef UnitModelLoadH
#define UnitModelLoadH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TFormLoadModel : public TForm
{
__published:	// IDE-managed Components
        TToolBar *ToolBar1;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TLabel *Label1;
        TEdit *Edit1;
        TButton *Button1;
        TOpenDialog *OpenDialog1;
        void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormLoadModel(TComponent* Owner);

        void  Init(String  aModelFileName);

   protected:
        String  readModelFile();
        void    writeModelFile(String aModelFile);
   public:
        __property  String  ModelFileName = {read=readModelFile,write=writeModelFile};
};
//---------------------------------------------------------------------------
extern PACKAGE TFormLoadModel *FormLoadModel;
//---------------------------------------------------------------------------
#endif
