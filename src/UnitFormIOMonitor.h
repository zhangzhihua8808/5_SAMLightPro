//---------------------------------------------------------------------------

#ifndef UnitFormIOMonitorH
#define UnitFormIOMonitorH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
//---------------------------------------------------------------------------
class TFormIOMonitor : public TForm
{
__published:	// IDE-managed Components
        TToolBar *ToolBar1;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
private:	// User declarations

public:
        void  Init();
public:		// User declarations
        __fastcall TFormIOMonitor(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormIOMonitor *FormIOMonitor;
//---------------------------------------------------------------------------
#endif
