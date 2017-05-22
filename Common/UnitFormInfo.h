//---------------------------------------------------------------------------

#ifndef UnitFormInfoH
#define UnitFormInfoH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TInfoForm : public TForm
{
__published:	// IDE-managed Components
        TImage *Image1;
        TLabel *Label1;
        TCheckBox *CheckBox1;
        TBevel *Bevel1;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TInfoForm(TComponent* Owner);

   protected:
        bool   IsDelete();
   public:
     __property  bool  Delete={read=IsDelete};

   public:
       void  Init(String  aCaption,String aMainInfo, String  aCheckInfo,bool bCheckVisible=true);
};
//---------------------------------------------------------------------------
extern PACKAGE TInfoForm *InfoForm;
//---------------------------------------------------------------------------
#endif
