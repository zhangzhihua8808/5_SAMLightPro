//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitFrameWiperAndMotor.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrameWiperAndMotor *FrameWiperAndMotor;
//---------------------------------------------------------------------------
__fastcall TFrameWiperAndMotor::TFrameWiperAndMotor(TComponent* Owner)
        : TFrame(Owner)
{
}
//---------------------------------------------------------------------------
