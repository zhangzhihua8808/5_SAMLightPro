//---------------------------------------------------------------------------


#pragma hdrstop

#include "UnitExcelFun.h"
#include "UnitOfficeFun.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

MExcelFun * G_Excel =  new MExcelFun;

//------------------------------------------------------------------------------
// ���캯����Ĭ�ϣ�Ϊ����ʾ
//------------------------------------------------------------------------------
MExcelFun::MExcelFun()
{
    IsVisible = false;

    //VariantClear(Value);
}

//------------------------------------------------------------------------------
//��ȡExcel_App
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
//��ȡ������
//------------------------------------------------------------------------------
Variant  MExcelFun::readWorkBooks()
{
    return  Excel_App.Exec(PropertyGet("Workbooks"));
}

//------------------------------------------------------------------------------
//���ļ�
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
//�ر��ļ�
//------------------------------------------------------------------------------
void  MExcelFun::QuitExcel()
{
     Excel_App.Exec(Procedure("Quit"));
}

//------------------------------------------------------------------------------
//��ȡ��Ԫ���ֵ
//------------------------------------------------------------------------------
String MExcelFun::GetSheetCellValue(int aRowId,int aColId)
{
       Variant aSheet = GetObjProperty(Excel_App,"ActiveWorkbook.ActiveSheet");

       //ת����Ϊ�˲��ı���ǰ�ĳ���
       char  chColId = 'A' + aColId - 1;
       String  strColId = String(chColId);

       Variant aRange = aSheet.Exec(PropertyGet("Range")<<strColId+IntToStr(aRowId));

       return GetObjProperty(aRange,"Value");
}

//------------------------------------------------------------------------------
//����������aColId��aRowBgs��aRowEnd ������ 1
//���磺    G_Excel->GetSheetCellsValue(1,1,4)  �� ȡ��1�еĵ�1������4��Ԫ��
//------------------------------------------------------------------------------

void MExcelFun::GetSheetCellsValue(int aColId,int aRowBgs,int  aRowEnd, TStrings* aValues)
{
  TStrings* aStrings = GetSheetCellsValue(aColId,aRowBgs,aRowEnd);
  aValues->Text = aStrings->Text;
  delete aStrings;
}

TStrings*  MExcelFun::GetSheetCellsValue(int aColId,int aRowBgs,int  aRowEnd)
{

  //����ռ�
  TStringList*  aValues = new TStringList;
  if( aColId<0 )
    return aValues;

   Variant aSheet = GetObjProperty(Excel_App,"ActiveWorkbook.ActiveSheet");

   //ת����Ϊ�˲��ı���ǰ�ĳ���
   char  chColId = 'A' + aColId - 1;
   String  strFrom = String(chColId)+ IntToStr(aRowBgs);
   String  strTo  =  String(chColId)+ IntToStr(aRowEnd);

   if(strFrom == strTo)  //ֻ��1��
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
      return GetObjProperty(WorkSheets,"Count");   //ָExcel �ļ�
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
        return  WorkSheets.Exec(PropertyGet("Item")<<aIndex+1);                 //���Sheet
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




