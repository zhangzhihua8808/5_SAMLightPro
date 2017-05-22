//---------------------------------------------------------------------------

#ifndef UnitWordFunH
#define UnitWordFunH

#include <IniFiles.hpp>
#include <ComCtrls.hpp>
#include <Grids.hpp>

//#include "UnitClass_DataModule.h"
#include "UnitOfficeFun.h"     

extern const String DataInfo; //= "DataInfo";
extern const String DataValue; //= "DataValue";
//extern const int PortNumRow;  //= 1;
//extern const int PortNumCol;  //= 2;

//---------------------------------------------------------------------------

//String TrimAll(String astr) ;
//String ReplaceSymbByDL( String aPName );
//const String C_BMLab ="BMPM__" ;

//void CheckCursorPosition();

void BookMarkToNameAndRange( String aBookMark, String& aName,
                                             int& aBgn, int& aEnd );
String BookMarkToName( String aBookMark );
String WordToPDF( String aWordFileName, String aPDFFileDir, bool AskOverwrite);
void ConfirmDeleteWordFile( String aFileName );

TTreeNode * GetTN( TTreeNodes * I_Tree,String aName );
void MapBMToTV( TStrings * aBMInfo,TTreeView * aTV );
TTreeNode *  GetNodeChild( TTreeNode *aPNode ,String aChildName );


//------------------------------------------------------------------------------
class MWordFun  : public MOfficeFun
{
  //------------add by zzh
  private:
    String    FFileName;
  protected:
    Variant   readWord_App();
    Variant   readDocuments();
    int       readDocCount();
  public:
    __property  Variant  Word_App = {read=readWord_App};
    __property  Variant  Documents = {read=readDocuments};
    __property  int      DocCount = {read=readDocCount};

  public:
    void  SetActiveDocument();

  public:
    String HasWord;

  public:
    MWordFun();
    ~MWordFun();

  public:
    void Init();

  public:
    void CloseGrammaCheck();
    void CloseGrammaCheck_NoExp(bool IsShowError);

    bool IsModify();
    bool IsModify_NoExp(bool IsShowError);

  public:
    void SetColumn( TStrings* aBookMarks, int aCol ){};
    void MaskShrinkBM();

  //add by zzh123
  public:
    void AddVBS_StringsStrToWordStr( String aStringsStr );

    TStrings*  GetVarNames(String aFileName);
    TStrings* GetVarsNameAndValue( String aFileName );
    void  AddVarsNameAndValue(TStrings*  aNameValueList,String aWordFileName);

    void UpdatePictureTitle(String aBMName,String  aTitle);
    void UpdatePictureTitle(String aBMName,String  aTitle,bool bOnly,String aSubTitle="图");

    void FlushTableItemAndAddPictures(String aTableBM,int aRow,int aCol,TStrings* aFileList);
    void FlushTableItemAndAddText(String aTableBM, int aRow,int aCol,String aText);
    void Add_a_RowInTable(String aTableBM);

    void NewLine();
    void ClearFormat();

  public:
    void ConfirmRun();
    bool IsRun();

   private:
     void InitVBS(bool IsOnlyRun = true);

   public:
     void DelTableItems_Merge(String aTableBM,bool IsDelTitle );
     int InsertTableItem_Merge( String aTableBM, TStrings* aFiledValues );
     void ConverToPdf();

    //aKeyValue ：书签名和值
    // void CreateWordFile(  String aDotFileName ,String aFileName,TStrings* aKeyValue,bool IsQuit );

  public:
    //aPortValue ：端口名 和 值,由端口可定位多个书签(端口_1,端口_2......)
    void CreateWordFileByTemplate( String aDotFileName,
                                   String aFileName, bool IsQuit );
    void CreateWordFileByTemplateAndReplaceBookMarks
       ( String aDotFileName ,String aFileName,TStrings* aPortValue,bool IsQuit);

  public:

    void  ClearDoc();

    void SetDocReadOnly_NoExp( bool IsReadOnly, bool IsShow );
    void SetDocReadOnly( bool IsReadOnly);

  //-------------------Var---------------------------------------
  public:

    void AddVar( String aVarName,String aVarVal);
    void AddVar( String aWordFileName, String aVarName,String aVarVal);
    void DelVarVals(String aWordFileName, TStrings* aVarNames );
    void DelVarVal(String aWordFileName,String aVarName);

    String GetVarVal( String aVarName );
    String GetVarVal_NoExp( String aVarName, bool IsShowError );

  //-------------------BookMarks--------------------------------

  public:
    bool HasBM( String aBMName );

  public:
    void AddBMByPos( String aBMName, int aStPos,int aEndPos );
    void AddBM( String aBMName );
    String AddBMBySel( String aBMName );

    String MaskAddBM( String aBMName, String aSp="_" );
    String MaskGetBMName( String aBMName, String aSp="_" );

    void SetBMRangeBySel( String aName );

  public:
    String GetBookMark( String aName );
    String GetBMNameBySel();
    String GetBMNameOfCursor();

    void GetBMRange( String aBMName,int &aStartPos,int &aEndPos,
                                                String aFileName = "");

    TStrings * GetBookmarkNames(String aFileName ="" );
    TStrings * GetBookmarkTrueNames(String aFileName  );

    String GetPortNameByBmName( String aBMName );

  public:
    void GotoBM( String aBMName );
    void GotoBMAndSelRange( String aBookMark );
    void GotoBMAndSelRange1( String aBookMark );

  public:
    void RenameBM( String aOldBM, String aNewBM );

  public:
    void DelBMVal( String aBMName );
    void DelBMVals( TStrings* aBMNames );

    void DelBM( String aBMName );
    void InitBM();
    String GetPreBMNameofCursor();

  public:
    void SelBMS( TStrings* aBMNames );

    void CopyBMToNewFile( String aBMName,String aNewFile );
    void CopyBMSToNewFile( TStrings* aBMList,String aNewWordFile);  //分BM保存
    void SaveBMS_SelectionToNewFile( TStrings* aBMList,String aNewWordFile);  //整体保存

  public:
     void ReplaceBookMark( TStrings * aNames, TStrings* aValues, String aFileName = "" );   //aNames:标签名称; aValues:值名称; aFileName:文档名称,""为当前
     void ReplaceBookMark( TStrings * aParaValueNameAndValues,String aFileName="" );
     void ReplaceBookMark( TStrings * aVBS,String aDocName,String aBMName,String aValue);

  public:
    void SelRange( int aStartPos,int aEndPos );
    void UnSelRange();
    void DelSel();

  public:
    void MoveDown();
    void CheckCursorPosition();
    int  GetCurPos();

  public:
    void Open(String aFileName);
    void Open_NoExp(  String aFileName, bool IsShowError );
    void Save();

  public:
    void Save( String aFileName,bool IsClose );

    void CloseActiveDoc( );
    void CloseAll();
    void Quit();
    void MaskQuit();

    void Save( String aFileName );
    void Close( String aFileName );
    void Close_NoExp( String aFileName, bool IsShow );

  public:
    String GetActiveDocFileName();

  public:
    String RotStr( String aSrc );
    int LeftPos( String aSrc,String aSub);

  public:
    void SelMoveRight();
    void SelMoveRight(int aCount);

  //---------------Picture-----------------------

  public:
    void NewFile( String aFileName );
    void InsertFile( String aFileName );

    void InsertFile_BM( String aBMName ,String aWordFileName );
    void UpdateFile_BM( String aBMName ,String aWordFileName );
    void UpdateTableFile_BM( String aBMName ,String aWordFileName );

    void CombinBMIntoFile( TStrings* aBMList,String aNewWordFile );

    void  UpdateTableTitle(String aBMName,String  aTitle);

  public:
    void UpdatePic( String aPicFName,String aBMName );

    void InsertPicNewBm( String aPicFName, String aBMName,
                                   String aSubTitle="" ,String aTitle="" );

    void  InsertPicTitle( String aTitle, String aSubTitle);
    void  InsertPicTitle( String aTitle  ,String aSubTitle , bool bOnly );

    void InsertPic( String aPicFName ); //当前位置
    void InsertPic( String aPicFName,String aBMName );
    void InsertPic( String aPicFName,int aPos,int aEndPos = -1,
                     String aNewBm="",String aTitle="",String aSubTitle="" );

    //void InsertPic( String aPicFName,int aPos,int aEndPos = -1,
    //                String aNewBm="",String aTitle="",String aSubTitle="" );

    void InsertPics( TStrings* aPicNames  );
    void InsertPic_Group( TStrings* aBMNames, String aPicFName,String aBMName );

    //void InsertPic( String aPicFName );
    //void InsertPic( String aPicFName,String aBMName );
    //void InsertPic( String aPicFName,int aPos,int aEndPos = -1 );

    //void InsertPicTitle( String aTitle, String aSubTitle="图" ); //李申  20:44:13
    void InsertPicNewBm( String aPicFName, String aNewBm, String aTitle,
                         String aSubTitle="图", int aPos=-1, int aEndPos = -1 );
    void InsertTableTitle( String aTitle  ,String aSubTitle="表" );

    void InsertPic( String aPicFName, String aNewBm,
                                  int aPos,int aEndPos = -1 );
    void InsertPicNewBm( String aPicFName, String aBMName );

   public:

     void InsertStrings_ByBMName( String aBmName, TStrings* aMemo );
     void UpdateStrings_ByBMName( String aBmName, TStrings* aMemo );

     void InsertText_ByBMName( String aBmName, String aText );
     void UpdateText_ByBMName( String aBmName, String aText );

     void InsertTxt( String aTxt );
     void InsertTxt( TStrings *aStr );

     void InsertTextNewBM( String aStr, String aNewBm,
                                      int aPos=-1, int aEndPos=-1  );

     void  ReplaceContentStr( String aOldStr,String aNewStr);

   //----------Title--------------
   
   public:
     void InsertTitle( String aTitle ,String aStyle );    //待集成

   public:
     void UpdateTitle(String aTitle,String aBMName);
     void InsertFiledTitle( String aTitle );
     void InsertFiledTitleNewBM( String aStr, String aNewBm,
                                      int aPos=-1, int aEndPos=-1  );
   public:
     void InsertTables( TStrings* aTables );
     int  GetTabColCount( String aTableBM );
   public:
     void InsertTable_Group( TStrings* aBMNames, String aTableStr,
                                  String aSpRecs, String aSpFields, String aBMName );
     void InsertTable( String aTableStr, String aSpRecs,
                               String aSpFields, String aBMName );
     void InsertTable( TStrings* aTabStr, String aSpField, String aBMName);
     void InsertTable( TStringGrid * aGrid,String aBMName );
     void InsertTable( TStringGrid * aGrid, int aPos,int aEndPos );

     void  DelTableItemsAndAddBM(String aTableBM,bool IsDelTitle );
     void  DelTableItems(String aTableBM,bool IsDelTitle );
     void  TableFitWindow(String  aTableBM);

     void  GotoTableItem( int aRow, int aCol);
     void  FlushTableRecord( int aRow);
     void  FlushTableItem( int aRow,int aCol);
     int   InsertTableItem( String aTableBM, TStrings* aFiledValues );
     void  InsertTableItem_1( String aTableBM, TStrings* aFiledValues );


   //-------ListItem------------

   public:
     void InsertIcoListItem(String aBMName, TStrings* aList,int aStyle=61548);
     void UpdateIcoListItem(String aBMName, TStrings* aList,int aStyle=61548);

     void InsertListItem( String aBMName, TStrings* aList,bool aIsContinue,
                          int aNumStyle,String aBrac1,String aBrac2);

     void UpdateListItem( String aBMName, TStrings* aList,bool aIsContinue,
                          int aNumStyle,String aBrac1,String aBrac2);

     void InsertListItem( String aBMName, String aItem,bool aIsContinue,
                          int aNumStyle,String aBrac1,String aBrac2);

     void UpdateListItem(String aBMName, String aItem,bool aIsContinue,int aNumStyle,String aBrac1,String aBrac2);
};




extern MWordFun* G_Word;
//extern MExcelFun* G_EF;

#endif
