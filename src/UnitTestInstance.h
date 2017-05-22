//---------------------------------------------------------------------------

#ifndef UnitTestInstanceH
#define UnitTestInstanceH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include <Dialogs.hpp>

#include "clipper.hpp"
#include <ImgList.hpp>
using namespace Clipper;

class M2DPoints;
class MPolyLines;
class MHatchLines;
class MPolyLine;
class M2DPoint;
//---------------------------------------------------------------------------
class TFormTestInstance : public TForm
{
__published:	// IDE-managed Components
        TImage *Image1;
        TGroupBox *GroupBox2;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TComboBox *ComboBox1;
        TEdit *EditHeight;
        TEdit *EditWidth;
        TToolBar *ToolBar1;
        TBitBtn *BitBtn2;
        TToolButton *ToolButton1;
        TPanel *Panel1;
        TSplitter *Splitter1;
        TGroupBox *GroupBox4;
        TLabel *Label10;
        TEdit *Edit_LayerThick;
        TSaveDialog *SaveDialog1;
        TToolButton *ToolButton2;
        TBitBtn *BitBtn1;
        TLabel *Label4;
        TEdit *Edit1;
        TBitBtn *BitBtn4;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TPanel *Panel2;
        TPageControl *PageControl2;
        TTabSheet *TTestFocus;
        TLabel *Label6;
        TEdit *Edit3;
        TLabel *Label7;
        TEdit *Edit4;
        void __fastcall BitBtn4Click(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall ComboBox1Change(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormTestInstance(TComponent* Owner);

    private:
        MPolyLines*  fPaths;
    protected:
        int  readInstanceType();
        void writeInstanceType(int aType);

        double readWidth();
        void  writeWidth(double aWidth);

        double readHeight();
        void writeHeight(double aHeight);

        double readLayerThick();
        void   writeLayerThick(double aLayerThick);
    public:
        __property  int  InstanceType = {read=readInstanceType,write=writeInstanceType};
        __property  double Width = {read=readWidth,write=writeWidth};
        __property  double Height = {read=readHeight,write=writeHeight};
        __property  double LayerThick = {read=readLayerThick,write=writeLayerThick};


        void  BaseMoveToPosition(double aHeight,TStringList*  aFileList); 

        //生成轮廓数据
        TStringList*  CreateRectangleFigureToFile(int iLayers,double iLayerThick);
        TStringList*  CreateTriangleFigureToFile(int iLayers,double iLayerThick);
        TStringList*  CreateCircleFigureToFile(int iLayers,double iLayerThick,int aPointNum);
        TStringList*  CreatePart1FigureToFile(int iLayers,double iLayerThick,int EdgeNum);
        TStringList*  Create4X4PartFigueToFile(int iLayers,double iLayerThick);
        TStringList*  CreateTestFocusToFile(double iLineSpace,double iLayerThick);

        void  CreateSampleFigureData(int iShapeType);
        void  PreViewSampleFigureData(int iShapeType);

        //矩形
        void  CreateSingleRectangleFigure();
        void  CreateSingleTriangleFigure();
        void  CreateSingleCircleFigure(int aPointNum);
        void  CreateSinglePart1Figure(int aEdgeNum);

        //分层文件输出


};
//---------------------------------------------------------------------------
extern PACKAGE TFormTestInstance *FormTestInstance;

void  GetCLIFileHeader(TStringList* aFile, int aLayerNum,String aPartID="-1");
void  OutCLITrailToFile(TStringList* aFile);
void  SetViewPort(TImage* aPBox,int aDrawWidth,int aDrawHeight,bool  bClear=true);
void  ShowImageInfo(TImage* aImage, int aWidth,int aHeight,
                                    MPolyLines*  aPaths,MHatchLines*  aLine,int aScale,bool bClear=true,bool bCurrent=false);


//---------------------------------------------------------------------------
#endif
