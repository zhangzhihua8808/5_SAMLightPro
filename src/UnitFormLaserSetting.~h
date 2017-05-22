//---------------------------------------------------------------------------

#ifndef UnitFormLaserSettingH
#define UnitFormLaserSettingH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include <ExtCtrls.hpp>

class MLaserPens;
class MLaserPen;
//---------------------------------------------------------------------------
class TFormLaserSetting : public TForm
{
__published:	// IDE-managed Components
        TToolBar *ToolBar1;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TPanel *Panel1;
        TPanel *Panel2;
        TLabel *Label1;
        TEdit *Edit_LaserMaxPower;
        TListView *ListView1;
        TButton *Button2;
        void __fastcall ListView1DblClick(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormLaserSetting(TComponent* Owner);

    public:
       void Init();
       void EditLaserPen(MLaserPen* aItem);

       MLaserPen*   fSelectedLaserPen;
    private:
       MLaserPens*   fLaserPens;
    protected:
       String  readLaserMaxPower();
       void    writeLaserMaxPower(String aPower);
    public:
       __property  String  LaserMaxPower = {read=readLaserMaxPower,write=writeLaserMaxPower};
       __property  MLaserPens*  LaserPens = {read=fLaserPens};
};
//---------------------------------------------------------------------------
extern PACKAGE TFormLaserSetting *FormLaserSetting;
//---------------------------------------------------------------------------
#endif
