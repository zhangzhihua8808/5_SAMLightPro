//---------------------------------------------------------------------------

#ifndef UnitExcelFunH
#define UnitExcelFunH


#include <vcl.h>


//---------------------------------------------------------------------------
/*
class MExcelFun  : public MOfficeFun
{
   private:
	 void InitVBS(bool IsOnlyRun = true);
   public:
	 String GetSheetCellValue( String aSheetName,int aRowId,int aColId );
         void  QuitExcel();
         void  ConfirmRun();


	 TStrings * GetPortData(String aFileName );
};
*/
//------------------------------------------------------------------------------
class MExcelFun
{
protected:
   Variant   readExcel_App();
   Variant   readWorkBooks();
   Variant   readWorkSheets();
   long  readCount_WorkSheets();
   Variant   ReadWorkSheets(int aIndex);

public:
   __property  Variant  Excel_App = {read = readExcel_App};                     //---------Excel_App------
   __property  Variant  WorkBooks = {read = readWorkBooks};                     //--------workbooks  工作薄
   __property  Variant  WorkSheets = {read = readWorkSheets };                  //worksheets
   __property  long  Count_WorkSheets = {read = readCount_WorkSheets};          //-------------Count of worksheet
   __property  Variant  WorkSheets_Item[int aIndex] = {read=ReadWorkSheets};         //base 0


      //------IsVisible------ 是否显示
private:
   bool  fIsVisible;
public:
   __property bool  IsVisible = {read = fIsVisible,write = fIsVisible};

public:
  MExcelFun();
public:
   String GetSheetCellValue(int aRowId,int aColId );
   TStrings*  GetSheetCellsValue(int aColId,int aRowBgs,int  aRowEnd);            
   void GetSheetCellsValue(int aColId,int aRowBgs,int  aRowEnd, TStrings* aValues);
   bool IsValidWorkSheetsIndex(int aIndex);
public:
   void   ConfirmOpenFile(AnsiString  aFileName);
   void   QuitExcel();
   TStrings*  NameList_Worksheets();
   long   Rows_Record(Variant aSheet);
};


extern MExcelFun* G_Excel;

#endif
