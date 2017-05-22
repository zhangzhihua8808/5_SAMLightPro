//---------------------------------------------------------------------------

#ifndef UnitFormLaserPenH
#define UnitFormLaserPenH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>

class MLaserPen;
//---------------------------------------------------------------------------
class TFormLaserPen : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TEdit *Edit_PenID;
        TLabel *Label2;
        TToolBar *ToolBar1;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TEdit *Edit_PenName;
        TLabel *Label3;
        TEdit *Edit_PenPower;
        TLabel *Label4;
        TEdit *Edit_Speed;
        TLabel *Label5;
        TEdit *Edit_PenFreq;
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall Edit_PenPowerExit(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormLaserPen(TComponent* Owner);

   private:
      double  fMaxPower;
   protected:
      String readPenName();
      void   writePenName(String  aPenName);
      String readPenPower();
      void   writePenPower(String aPenPower);
      String readPenSpeed();
      String readPenFreq();
      void   writePenSpeed(String aSpeed);
      void   writePenFreq(String aFreq);
      void   writePenID(String aID);
   public:
      __property  String  PenName = {read=readPenName,write=writePenName};
      __property  String  PenPower = {read=readPenPower,write=writePenPower};
      __property  String  PenSpeed = {read=readPenSpeed,write=writePenSpeed};
      __property  String  PenFreq = {read=readPenFreq,write=writePenFreq};
      __property  String  PenID = {write=writePenID};
   public:
      void  Init(MLaserPen* aItem ,double  aMaxPower);
      void  SetCaption(String  aPenID);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormLaserPen *FormLaserPen;
//---------------------------------------------------------------------------
#endif
