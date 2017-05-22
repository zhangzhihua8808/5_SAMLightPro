//---------------------------------------------------------------------------

#ifndef UnitPPTFunH
#define UnitPPTFunH

#include <IniFiles.hpp>
#include <ComCtrls.hpp>
#include "UnitOfficeFun.h"

const String C_PrePViewName = "TManualPView";
const String C_PViewCodeStart = "PViewCodeStart 该语句不能删除";
const String C_PViewCodeEnd = "PViewCodeEnd 该语句不能删除";
const String C_PViewWebCodeStart = "<script>//";
const String C_PViewWebCodeEnd = "</script>";
const String C_PViewLab = "&";
const String C_AnimateLab = "%";                               //Animation标志
const String C_PpsLab = "@";                                   //PPS标志
const String C_ViewLab = "#";                                  //View标志
const String C_AlterStr = "PPS_0+ALTERNATE_REPRESENTATION$";
const int C_PosDelta = 0;
const String C_AnoteViewLab = "!";                                 //
const String C_DrwLab = "^";
const String C_BomLab = "~";
const String C_Sub_InitBomLvw = "Init_BomLvw";
const String C_BomCtrlSubName = "_BomTab";
const String C_PViewClsID ="CLSID:F07443A6-02CF-4215-9413-55EE10D509CC";
const String C_WMClsID = "CLSID:6BF52A52-394A-11D3-B153-00C04F79FAA6";
const String C_BomTabClsID ="CLSID:0002E559-0000-0000-C000-000000000046";
const String UpBGColor = "BackColor=16777152";
const String DownBGColor = "BackColor=12648384";

class MPPtFun  : public MOfficeFun
{
   public:
        void InitVBS(bool IsOnlyRun = true);
   public:
	void ConfirmRun();
	void Quit();
        void Open( String  aName );
   public:     
     void SaveAll();
     void CloseAll();
     bool IsModify();
     void NewFile( String aName );
     
  public:
    void  Save( String aFileName );
    void  Close( String aFileName );          

  public:    
    int PresentCount();
    int ActPreSlidesCount();
    String ActPreFullFileName();
    int ActWinSelSRCount();
    int ActWinSelType();
    int ActWinSelShapeRangeType();
    String ActWinSelShapeRangeName();
    String ActWinSelSlideRangeName();

    void ChangePviewPvsPath();
    void SingleProeInst();

  public:
    void InsertPic( String aName,float aLeft=65, float aTop=102,float aWidth=65,float aHeight=102 );
    void  SaveAsHtml(String aWebName);

    String  SlidesName( int aIndex );
    int  ActPreSlideShapeCount(int aIndex);
    int  SlideShapesHasTitle(int aSlideId);

  public:
    String SlideShapesTitleAltTxt(int aSlideId);
    void SlidesSelect( int aSlideId );
    String SlideShapeName( int aSlideId,int aShapeId);
    int SlideShapeType( int aSlideId,int aShapeId);
        
  public:
        String SlideShapeUrl( int aSlideId,int aShapeId);
        String SlideShapeAltTxt( int aSlideId,int aShapeId);

  public:
        String ActPreName();
        String ActPreName_NoExt();

  public:
    String InsertMedia(String aFileName,String MediaClassName = MediaClassType);
        
  public:
    //100,100,300,300
    TStrings* GetPViewNameList(  bool IsAddNew = true);
    TStrings* InsertPView( String aFileName,String AltText,float aL=100,float aT=100,float aW=300,float aH=300,String PviewClassName = PViewClassType);

  public:
    void SetPviewCode(String aSlideName,String aCodeFileName,String aPVName );
    void SetCodeSeg( String aPVName,String aCodeFileName );

  public:
    void InsertHTextBox( );
  public:
    void DelSelShape();
  public:
    String AddSlide( int aId,int  aLayoutType);
    void  SlideRangeLayoutSet( int aType );
  public:
    String GetActWinSelTextRangText();
    void SetActWinSelTextRangText( String aTxt );
  public:
    void SetHyperlinkInfo(String AddressStr,String TextToDisplayStr,String SubAddressStr,String ScreenTipStr);

  public:
    int  SlideShowWinCount();

  public:
    void SetActPreSlidesAdvOnClick(String OnClickVal  ,String OnTimeVal,String AdvanceTimeVal );
    void  ActPreSlideShowSetRun();
    void SlideShowWinView(String aProcedureName);
    void AddOleTitleObj( MOleTitleObj * aObj );
    void AddScrollBar(MOleFrmScrollBar * aSB );
    void AddTextBox(MOleFrmTextBox * aTxt ); //--------臧霖----20130820

  public:
    String SetPVProperty(String aAltTxt,String aFileName = "" );
    String GetPVAltTxt();
    String GetPVUrl();

  public:
    String AddOleObj( MOleObj* aObj );
    Variant  GetSelOleObjProp( String aName );
    void SetSelOleObj( String aNameValue);
    void SetSelOleObjUrl( String aUrl);
    void UpdateOleObj( String aSlideName,String aCtrlName ,String PropertyStr);
        
  public:
    String GetSlideNewPViewName();
    String GetSlideNewPViewName(Variant aSlide,TStrings * aNameList);
    String GroupPviewNameList(String PViewName,int aSlideIndex );

  public:
    void UnGroup( Variant aCurSlide );
    void UnGroup(int aSlideIndex);
    void UnGroup(String aSlideName);

  public:
    int SlideNameToId( String aSlideName);
        
  public:
    void GroupPview( int aSlideIndex );
    void GroupPview( Variant aCurSlide );

  public:
    void GroupByCtrlName( String PViewName,int aSlideIndex );
    void GroupByCtrlName( TStrings * PViewNameList,int aSlideIndex ); 
    void ReViewActPpt(int aSleepCount  =800);

  public:
    Variant GetSlide( int i );
    Variant CurSlide();
    String CurSlideName();
    int CurSlideId();

  public:
    int GetRelDelta(TStrings * aNameList );

     //2014  
  public:
   String GetActivePPTFileName();
   String GetActivePPTFileName_NoExt();

  
  //---------------BookMark---------------
  public:
    bool IsBMExist(   String aBMName ){ return true; };
    void InsertFiledTitleNewBM( String aStr, String aNewBm,
                                    int aPos=-1, int aEndPos=-1  ){};
    void InsertPicNewBm( String aPicFName, String aNewBm, String aTitle,
                          String aSubTitle="图", int aPos=-1, int aEndPos = -1 ){};
};

/*
private:
       void SetCodeSeg( String aPVName,String aCodeFileName );
       void SetCodeSeg( String aPVName,TStrings* aCodeList);
   public:
        ~MPPtFun();
        void InitVBS(bool IsOnlyRun = true);
	void ConfirmRun();
	void Quit();
        void Open( String  aName );
	void SaveAll();
        bool IsModify();
	void CloseAll();
        void NewFile( String aName );
        String NewSlide();
        int PresentCount();
        int ActPreSlidesCount();
        int ActWinSelSRCount();
        int ActWinSelType();
        int ActWinSelShapeRangeType();
        String ActWinSelShapeRangeName();
        String ActWinSelSlideRangeName();
        void InsertPic( String aName,float aLeft=65, float aTop=102,float aWidth=65,float aHeight=102 );
        void  SaveAsHtml(String aWebName);
        String  SlidesName( int aIndex );
        int  ActPreSlideShapeCount(int aIndex);
        int  SlideShapesHasTitle(int aSlideId);
        String SlideShapesTitleAltTxt(int aSlideId);
        void SlidesSelect( int aSlideId );
        String SlideShapeName( int aSlideId,int aShapeId);
        int SlideShapeType( int aSlideId,int aShapeId);
        String SlideShapeUrl( int aSlideId,int aShapeId);
        String SlideMMUrl( int aSlideId,int aShapeId);
        String SlideShapeAltTxt( int aSlideId,int aShapeId);

    public:
        String ActPreName();

        String ActPreName_NoExt();
        String ActPreFullFileName();
        void SingleProeInst();
       
    public:
        String InsertMedia(String aFileName ,String MediaClassName = MediaClassType);
        //100,100,300,300
        TStrings * GetPViewNameList(  bool IsAddNew = true);
        TStrings *  InsertPView( String aFileName,String AltText,bool IsSingle,float aL=100,float aT=100,float aW=300,float aH=300,String PviewClassName = PViewClassType);
        void SetPviewCode(String aSlideName,String aCodeFileName,String aPVName );
        void SetPviewCode(String aSlideName,TStrings* aCodeList ,String aPVName);
        void InsertHTextBox( );
        void DelSelShape();
        String AddSlide( int aId,int  aLayoutType);
        void  SlideRangeLayoutSet( int aType );
        String GetActWinSelTextRangText();
        void SetActWinSelTextRangText( String aTxt );
        void SetHyperlinkInfo(String AddressStr,String TextToDisplayStr,String SubAddressStr,String ScreenTipStr);
        
     public:
        int  SlideShowWinCount();

     public:
        void SetActPreSlidesAdvOnClick(String OnClickVal  ,String OnTimeVal,String AdvanceTimeVal );
        void  ActPreSlideShowSetRun();
        void SlideShowWinView(String aProcedureName);
        void AddOleTitleObj( MOleTitleObj * aObj );
        void AddScrollBar(MOleFrmScrollBar * aSB );
        void AddTextBox(MOleFrmTextBox * aTxt ); //--------臧霖----20130820
        String AddOleObj( MOleObj* aObj );
        void  AddProp( MOleObj* aObj );
        String SetPVProperty(String aAltTxt,String aFileName = "" );
        Variant  GetSelOleObjProp( String aName );
        String GetPVAltTxt();
        String GetPVUrl();
        void SetSelOleObj( String aNameValue);
        void SetSelOleObjUrl( String aUrl);

     public:
        String GetSlideNewPViewName();
        String GetSlideNewPViewName(Variant aSlide,TStrings * aNameList);
        String GroupPviewNameList(String PViewName,int aSlideIndex );

     public:
        void UnGroup( Variant aCurSlide );
        void UnGroup(int aSlideIndex);
        void UnGroup(String aSlideName);

     public:
        int SlideNameToId( String aSlideName);
        
     public:
        void GroupPview( int aSlideIndex );
        void GroupPview( Variant aCurSlide );

     public:
        void GroupByCtrlName( String PViewName,int aSlideIndex );
        void GroupByCtrlName( TStrings * PViewNameList,int aSlideIndex );
        void UpdateOleObj( String aSlideName,String aCtrlName ,String PropertyStr);

        void ReViewActPpt(int aSleepCount  =800);

     public:
       Variant GetSlide( int i );
       Variant CurSlide();
       String CurSlideName();
       int CurSlideId();

     public:
       int GetRelDelta(TStrings * aNameList );

     //2014  
     public:
       String GetActivePPTFileName();
       String GetActivePPTFileName_NoExt();

       void InsertBomByListView( String aName ,float aLeft=400, float aTop=200 );
       void InsertBomTitleByExcelTab( String aName ,float aLeft=425, float aTop=0 ); //30,330, 470
       void InsertBomByExcelTab( String aName ,float aLeft=337, float aTop=30,float aWidth=377 , float aHeight=470 );
       void InsertCheckBox( String aName,float aLeft=350, float aTop=37,float aWidth=78 , float aHeight=22);

       void ChangePviewPvsPath();

*/

extern Variant PptApp;
extern MPPtFun * G_PPT;

HWND RunPPTByOle();


#endif
