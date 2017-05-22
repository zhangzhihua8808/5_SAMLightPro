//---------------------------------------------------------------------------


#pragma hdrstop

#include "UnitExcelFun.h"
#include "UnitOfficeFun.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

MExcelFun * G_Excel =  new MExcelFun;

//------------------------------------------------------------------------------
// 构造函数：默认，为不显示
//------------------------------------------------------------------------------
MExcelFun::MExcelFun()
{
    IsVisible = false;

    //VariantClear(Value);
}

//------------------------------------------------------------------------------
//获取Excel_App
//------------------------------------------------------------------------------
Variant   MExcelFun::readExcel_App()
{
    Variant   aExcel_App;

    try
    {
        aExcel_App = Variant::GetActiveObject("Excel.Application");
    }
    catch(...)
    {
        try
        {
            aExcel_App = Variant::CreateObject("Excel.Application");
        }
        catch(...)
        {
            Application->MessageBoxA("Unable to obtain Excel automation Object",
            "Error:",MB_OK|MB_ICONERROR);
            return NULL;
        }
    }

    Variant aVar = GetObjProperty(aExcel_App,"Visible");
    aExcel_App.Exec(PropertySet("Visible")<<IsVisible);

    return aExcel_App;
}

//------------------------------------------------------------------------------
//获取工作薄
//------------------------------------------------------------------------------
Variant  MExcelFun::readWorkBooks()
{
    return  Excel_App.Exec(PropertyGet("Workbooks"));
}

//------------------------------------------------------------------------------
//打开文件
//------------------------------------------------------------------------------
void   MExcelFun::ConfirmOpenFile(AnsiString  aFileName)
{
    try
    {
       WorkBooks.Exec(Procedure("Open")<<aFileName);
    }
    catch(...)
    {
    }
}

//------------------------------------------------------------------------------
//关闭文件
//------------------------------------------------------------------------------
void  MExcelFun::QuitExcel()
{
     Excel_App.Exec(Procedure("Quit"));
}

//------------------------------------------------------------------------------
//获取单元格的值
//------------------------------------------------------------------------------
String MExcelFun::GetSheetCellValue(int aRowId,int aColId)
{
       Variant aSheet = GetObjProperty(Excel_App,"ActiveWorkbook.ActiveSheet");

       //转换，为了不改变以前的程序
       char  chColId = 'A' + aColId - 1;
       String  strColId = String(chColId);

       Variant aRange = aSheet.Exec(PropertyGet("Range")<<strColId+IntToStr(aRowId));

       return GetObjProperty(aRange,"Value");
}

//------------------------------------------------------------------------------
//功能描述：aColId，aRowBgs，aRowEnd ：基于 1
//例如：    G_Excel->GetSheetCellsValue(1,1,4)  ： 取第1列的第1个至第4个元素
//------------------------------------------------------------------------------

void MExcelFun::GetSheetCellsValue(int aColId,int aRowBgs,int  aRowEnd, TStrings* aValues)
{
  TStrings* aStrings = GetSheetCellsValue(aColId,aRowBgs,aRowEnd);
  aValues->Text = aStrings->Text;
  delete aStrings;
}

TStrings*  MExcelFun::GetSheetCellsValue(int aColId,int aRowBgs,int  aRowEnd)
{

  //申请空间
  TStringList*  aValues = new TStringList;
  if( aColId<0 )
    return aValues;

   Variant aSheet = GetObjProperty(Excel_App,"ActiveWorkbook.ActiveSheet");

   //转换，为了不改变以前的程序
   char  chColId = 'A' + aColId - 1;
   String  strFrom = String(chColId)+ IntToStr(aRowBgs);
   String  strTo  =  String(chColId)+ IntToStr(aRowEnd);

   if(strFrom == strTo)  //只有1行
   {
       String  aValue = GetSheetCellValue(aRowBgs,aColId);
       aValues->Add(aValue);
   }
   else
   {
       Variant aRange = aSheet.Exec(PropertyGet("Range")<<strFrom<<strTo);
       Variant aVal = GetObjProperty(aRange,"Value");

       if(aVal.IsArray())
       {
           int alow = aVal.ArrayLowBound();
           int aHigh = aVal.ArrayHighBound();

           for(int i= alow; i <= aHigh; i++)
           {
               aValues->Add(aVal.GetElement(i,1));
           }
       }
   }

   return aValues;
}

long  MExcelFun::readCount_WorkSheets()
{
      return GetObjProperty(WorkSheets,"Count");   //指Excel 文件
}

TStrings*  MExcelFun::NameList_Worksheets()
{
     TStrings*  aNames = new TStringList;

     for(int i=0; i < Count_WorkSheets; i++)
     {
          String   aName = GetObjProperty(WorkSheets_Item[i],"Name");
          aNames->Add(aName);
     }
     return aNames;
}

Variant MExcelFun::readWorkSheets()
{
     return  Excel_App.Exec(PropertyGet("Worksheets"));
}

Variant   MExcelFun::ReadWorkSheets(int aIndex)
{
  if ( !IsValidWorkSheetsIndex(aIndex) ) return NULL;
        return  WorkSheets.Exec(PropertyGet("Item")<<aIndex+1);                 //获得Sheet
}

bool  MExcelFun::IsValidWorkSheetsIndex(int aIndex)
{
      return ( aIndex>=0 && aIndex<Count_WorkSheets );
}

long  MExcelFun::Rows_Record(Variant aSheet)
{
     if(aSheet.IsNull())
          return -1;

     Variant  aRange = GetObjProperty(aSheet,"UsedRange");
     aRange =  GetObjProperty(aRange,"Rows");
     return GetObjProperty(aRange,"Count");
}




