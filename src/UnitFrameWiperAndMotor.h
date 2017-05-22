//---------------------------------------------------------------------------


#ifndef UnitFrameWiperAndMotorH
#define UnitFrameWiperAndMotorH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TFrameWiperAndMotor : public TFrame
{
__published:	// IDE-managed Components
        TGroupBox *GroupBox1;
        TButton *Button4;
        TLabel *Label2;
        TTrackBar *TrackBar1;
        TEdit *Ed_Dose;
        TLabel *Label3;
        TEdit *Ed_Y_Pos;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label1;
        TButton *Button1;
        TButton *Button2;
        TButton *Button3;
        TEdit *Edit1;
        TGroupBox *GroupBox2;
        TLabel *Label6;
        TEdit *Edit2;
        TLabel *Label7;
        TButton *Button5;
        TButton *Button6;
        TButton *Button7;
        TLabel *Label8;
        TEdit *Edit3;
        TLabel *Label9;
        TLabel *Label10;
        TEdit *Edit4;
        TLabel *Label11;
        TLabel *Label12;
        TEdit *Edit5;
        TUpDown *UpDown1;
private:	// User declarations
public:		// User declarations
        __fastcall TFrameWiperAndMotor(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrameWiperAndMotor *FrameWiperAndMotor;
//---------------------------------------------------------------------------
#endif
