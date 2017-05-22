//---------------------------------------------------------------------------

//#include <unitall.h>
#pragma hdrstop

#include "UnitDirectory.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormDirectory *FormDirectory;

//---------------------------------------------------------------------------
__fastcall TFormDirectory::TFormDirectory(TComponent* Owner)
        : TForm(Owner)
{
     BorderStyle = bsSizeable;
}
//---------------------------------------------------------------------------
void __fastcall TFormDirectory::FormShow(TObject *Sender)
{
     ::SetWindowPos( Handle,
                  HWND_NOTOPMOST,0, 0, Width, Height, SWP_NOMOVE);
}
//---------------------------------------------------------------------------

