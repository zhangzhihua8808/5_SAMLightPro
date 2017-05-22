//---------------------------------------------------------------------------

#ifndef UnitFormMechConfigH
#define UnitFormMechConfigH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFormMechConfig : public TForm
{
__published:	// IDE-managed Components
        TToolBar *ToolBar1;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TPanel *Panel1;
        TGroupBox *GroupBox1;
        TLabel *Label1;
        TEdit *Edit_WorkAreaLength;
        TLabel *Label2;
        TEdit *Edit_WorkAreaWidth;
        TGroupBox *GroupBox2;
        TEdit *Edit_ZInitPos;
        TLabel *Label3;
        TLabel *Label4;
        TEdit *Edit_BaseBoardThick;
        TCheckBox *CBox_WorkArea;
        TLabel *Label5;
        TEdit *Edit1;
        void __fastcall CBox_WorkAreaClick(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
private:	// User declarations
public:
        void  Init();
public:		// User declarations
        __fastcall TFormMechConfig(TComponent* Owner);

    protected:
        String  readWorkAreaLength();
        void    writeWorkAreaLength(String aLength);

        String  readZInitPosition();
        void    writeZInitPosition(String aString);

        String  readBasePanelThick();
        void    writeBasePanelThick(String  aThick);

        String  readFocalOffset();
        void    writeFocalOffset(String aValue);

        bool    readEnabled();
        void    writeEnabled(bool bEnable);
    public:
        __property  bool     EnableModify = {read=readEnabled,write=writeEnabled};
        __property  String   WorkAreaLength={read=readWorkAreaLength,write=writeWorkAreaLength};
        __property  String   ZInitPosition = {read=readZInitPosition,write=writeZInitPosition};
        __property  String   BasePanelThick={read=readBasePanelThick,write=writeBasePanelThick};
        __property  String   FocalOffset = {read=readFocalOffset,write=writeFocalOffset};
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMechConfig *FormMechConfig;
//---------------------------------------------------------------------------
#endif
