//---------------------------------------------------------------------------
//说明：(1)BookMark -- 指带位置信息的字符串，例如： A =1,30
//      (2)BMName -- 标签名称
//---------------------------------------------------------------------------


#pragma hdrstop

#include "UnitTool_Single.h"
#include "UnitTool_Class.h"
#include "UnitWordFun.h"
#include "COMMON_FUNC.hpp"

Variant WordApp;

//const String DataInfo = "DataInfo";
//const String DataValue = "DataValue";
//const int PortNumRow = 1;
//const int PortNumCol = 2;


//------------------ MOffice ---------------------------------------------------

void ConfirmDeleteWordFile( String aFileName )
{
  if( FileExists( aFileName ) == true && ProcessExists1("WINWORD.EXE") == true )     //文档正在被编辑
     G_Word->Close_NoExp( aFileName, true );
     
  if( FileExists(aFileName) )
  {
     if(DeleteFile(aFileName)== false)  //删不掉
     {
       String aStr = ApplicationPath()+"\\killword.bat";
       WinExec( aStr.c_str(),SW_HIDE );
       DeleteFile(aFileName);
     }
  }
}

MWordFun::MWordFun()
{
  Init();
}

//------------------------------------------------------------------------------
Variant MWordFun::readWord_App()
{
    Variant  aWord_App;

    try
    {
        aWord_App = Variant::GetActiveObject("Word.Application");
    }
    catch(...)
    {
        try
        {
            aWord_App = Variant::CreateObject("Word.Application");
        }
        catch(...)
        {
            return NULL;
        }
    }

//  aWord_App.OlePropertySet("DisplayAlerts",false);
    return aWord_App;
}

Variant MWordFun::readDocuments()
{
    if(VarIsNull(Word_App))  return NULL;

    return Word_App.Exec(PropertyGet("Documents"));
}

int  MWordFun::readDocCount()
{
    return GetObjProperty(Documents,"Count");
}

void  MWordFun::SetActiveDocument()
{
    if(VarIsNull(Documents))  return;

    int  iCount = readDocCount();
    for(int i=0; i < iCount; i++)
    {
        Variant aDocment = Documents.OleFunction("Item",i+1);
        String  aFullName = aDocment.Exec(PropertyGet("FullName"));

        if( aFullName !="" && FFileName == aFullName)
        {
            aDocment.OleProcedure("Activate");
            break;
        }
    }
}
//------------------------------------------------------------------------------

void MWordFun::Init()
{
  HasWord="";
}

MWordFun::~MWordFun()
{
  try
  {
    MaskQuit();
    //if( HasWord == "New" )
    //  Quit();
  }
  catch( Exception& e )
  {
  }
}

//要更新XXX
void MWordFun::DelTableItems_Merge(String aTableBM,bool IsDelTitle )
{
  if( aTableBM == ""  ) return;
  InitVBS();
  AddVBS("on error resume next ");
  AddVBS(" if MyWord.ActiveDocument.Bookmarks.Exists(\""+aTableBM+"\") = True Then ");
  AddVBS(" MyWord.Selection.GoTo -1,,,\""+aTableBM+"\"");
  AddVBS(" if MyWord.Selection.Tables.Count >0 Then");   
  if( IsDelTitle==false )
  {
     AddVBS("  MyWord.Selection.Tables(1).Rows.Add ");
     AddVBS("For i = MyWord.Selection.Tables(1).Rows.Count-1 To 2 step -1");
     AddVBS("If ( MyWord.Selection.Tables(1).Rows.Count > 2) Then  ");
     AddVBS("  MyWord.Selection.Tables(1).Cell(i, 1).Select ");
     AddVBS("  MyWord.Selection.Tables(1).Cell(i, 1).Delete 2 ");
     AddVBS("End If");
     AddVBS(" Next ");
   }
   else
   AddVBS("MyWord.Selection.Tables.Item(1).Rows.Delete");

   AddVBS(" end if ");
   AddVBS(" end if ");

   EndVBS();
   AddBMByPos(aTableBM,GetCurPos(),GetCurPos());
}


void  MWordFun::AddVarsNameAndValue(TStrings*  aNameValueList,String aWordFileName)
{
   if(aNameValueList == NULL && aNameValueList->Count == 0)  return;

   for(int i=0; i < aNameValueList->Count; i++)
   {
        String  aName = aNameValueList->Names[i];
        String  aValue = aNameValueList->Values[aName];

        AddVar(aWordFileName,aName,aValue);
   }

   TStrings* aVV = GetVarsNameAndValue(aWordFileName);
   String aaa = aVV->Text;

}

//新增的
//aFileName : Word文件名，为空，则取激活的文档

TStrings* MWordFun::GetVarsNameAndValue( String aFileName )
{
  /*TStrings* aVarsName = GetVarNames(aFileName);
  TStrings* aVarsNameAndValue = new TStringList;

  try
  {
    String  aVarName,aVarValue,aVarNameAndValue;
    for(int i=0; i < aVarsName->Count; i++)
    {
      aVarName = aVarsName->Strings[i];
      aVarValue = GetVarVal_NoExp(aVarName,true);
      aVarNameAndValue = aVarName + "=" + aVarValue;
      aVarsNameAndValue->Add(aVarNameAndValue);

      gError->Warn("正在获取("+IntToStr(i)+"//"+IntToStr(aVarsName->Count)+")变量");
    }
  }
  catch( Exception& e )
  {
    gError->Warn( "GetVarsNameAndValue!" + e.Message );
  }
  delete aVarsName;
  return aVarsNameAndValue;  */
    InitVBS(false);
    AddVBS(" Set NewDoc = Nothing ");
    if ( aFileName == "" )
    {
      AddVBS(" Set NewDoc = MyWord.ActiveDocument");    //
    }
    else
    {
      if( FileExists( aFileName ) == false )
             throw Exception( aFileName+" 文件不存在！");
      AddVBS(" Set NewDoc =  MyWord.Documents.Open(\""+aFileName+"\")");
    }
    AddVBS( " Set Vs = NewDoc.Variables  ");       //所有的变量
    AddVBS( " For i = 1 To Vs.Count ");
    AddVBS( " Set aV = Vs.Item(i) ");
    AddVBS( " aStr = aV.Name &\"=\" & aV.Value");
    AddVBS(" names = CStr(aStr) &\"$$$\" & CStr(names) ");
    AddVBS(" Next  ");
    AddVBS(" main = names  ");
    EndVBS(false);
    String aNames = EvalScript(VBS );
    return splitToStrings(aNames,"$$$");
}

TStrings* MWordFun::GetVarNames(String aFileName)
{
    InitVBS(false);
    AddVBS(" Set NewDoc = Nothing ");
    if ( aFileName == "" )
    {
      AddVBS(" Set NewDoc = MyWord.ActiveDocument");    //
    }
    else
    {
      if( FileExists( aFileName ) == false )
             throw Exception( aFileName+" 文件不存在！");
      AddVBS(" Set NewDoc =  MyWord.Documents.Open(\""+aFileName+"\")");
    }
    AddVBS( " Set Vs = NewDoc.Variables  ");       //所有的变量
    AddVBS( " For i = 1 To Vs.Count ");
    AddVBS( " Set aV = Vs.Item(i) ");
    AddVBS( " aStr = aV.Name ");
    AddVBS(" names = CStr(aStr) &\",\" & CStr(names) ");
    AddVBS(" Next  ");
    AddVBS(" main = names  ");
    EndVBS(false);
    String aNames = EvalScript(VBS );
    return splitToStrings(aNames,",");
}

/*void MWordFun::DelTableItems_Merge(String aTableBM,bool IsDelTitle )
{
  if( aTableBM == ""  ) return;
  InitVBS();
  //AddVBS("  on error resume next ");
  AddVBS(" if MyWord.ActiveDocument.Bookmarks.Exists(\""+aTableBM+"\") = True Then ");
  AddVBS(" MyWord.Selection.GoTo -1,,,\""+aTableBM+"\"");
  AddVBS(" if MyWord.Selection.Tables.Count >0 Then");
  if( IsDelTitle==false )
  {
     AddVBS("  MyWord.Selection.Tables(1).Rows.Add ");
     AddVBS("For i = 2 To MyWord.Selection.Tables(1).Rows.Count");
     AddVBS("If (MyWord.Selection.Tables(1).Rows.Count > 2) Then  ");
     AddVBS("  MyWord.Selection.Tables(1).Cell(i, 1).Select ");
     AddVBS("  MyWord.Selection.Cells.Delete 2 ");
     AddVBS("End If");
     AddVBS(" Next ");
  }else
    AddVBS("MyWord.Selection.Tables.Item(1).Rows.Delete");
    AddVBS(" end if ");
    AddVBS(" end if ");

  EndVBS();
  AddBMByPos(aTableBM,GetCurPos(),GetCurPos());
} */


//待改进
String WordToPDF( String aWordFileName, String aPDFFileDir, bool AskOverwrite )
{
  if( FileExists( aWordFileName ) == false )
    throw Exception( "文件(" +aWordFileName+ ")不存在！" );

  String aPDFFileName = aPDFFileDir + "\\" +
                       ChangeFileExt( ExtractFileName( aWordFileName ), ".pdf" )  ;

  if( FileExists( aPDFFileName ) == true  )
  {
    if( AskOverwrite == true )
    {
      if( MessageDlg("PDF文件(" +aPDFFileName+ ")已经存在！是否覆盖?",
          mtInformation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrNo  )
         return "";
    }
    if( DeleteFile( aPDFFileName ) == false )
      throw Exception( "文件(" + aPDFFileName + ")无法删除！" );
  }

  CheckAndMakeDirectory( aPDFFileDir );
  String aStr = ApplicationPath() + "\\wordToPDF /source \"" +
                aWordFileName + "\" /target \"" + aPDFFileDir + "\"";

  WinExec( aStr.c_str(),SW_HIDE );

  try
  {
    return WaitForFile( aPDFFileName, "Word2PDF.EXE",
                        ApplicationPath()+"\\killword2PDF.bat" );

    /*gError->HeadTitle = "正在生成PDF文件(" +aPDFFileName+ ")";
    for( ;; )
    {
      gError->Warn1( "请稍候！" );

      //成功
      if( FileExists( aPDFFileName ) == true )
      {
        String aStr =  ApplicationPath()+"\\killword2PDF.bat";
        WinExec( aStr.c_str(),SW_HIDE);
        return aPDFFileName;
      }

      //失败
      if( ProcessExists( "Word2PDF.EXE") == false )
        return "";
    } */

  }
  catch( Exception& e )
  {
     gError->Warn( e.Message );
  }

  //用户中断
  aStr =  ApplicationPath()+"\\killword2PDF.bat";
  WinExec( aStr.c_str(),SW_HIDE);
  return "";
}

void MWordFun::CloseGrammaCheck_NoExp(bool IsShowError)
{
  try
  {
    CloseGrammaCheck();
  }
  catch( Exception& e )
  {
    if( IsShowError )
      gError->Warn(e.Message);
  }
}

void MWordFun::CloseGrammaCheck()
{
  InitVBS( );
  AddVBS ("With MyWord.Options");
  AddVBS ("      .CheckSpellingAsYouType = False");
  AddVBS ("      .CheckGrammarAsYouType = False");
  AddVBS ("      .SuggestSpellingCorrections = False");
  AddVBS ("      .SuggestFromMainDictionaryOnly = False");
  AddVBS ("      .CheckGrammarWithSpelling = False");
  AddVBS ("      .ShowReadabilityStatistics = False");
  AddVBS ("  End With");
  EndVBS();
}

bool MWordFun::IsModify_NoExp(bool IsShowError)
{
  try
  {
    return IsModify();
  }
  catch( Exception& e )
  {
    if( IsShowError == true )
      gError->Warn( "MWordFun::IsModify_NoExp!" + e.Message );
    return false;  
  }
}

bool MWordFun::IsModify()
{
  InitVBS(false);

  AddVBS(" if MyWord.ActiveDocument.Saved = 0 Then  ");
  AddVBS("   main =1 ");
  AddVBS("   exit function ");
  AddVBS(" End If ");

  AddVBS(" main =0 ");
  EndVBS(false);
  int aRes = EvalScript(VBS );

  if( aRes ==0 )                     //未更改
    return false;
  else
    return true;                     //aRes ==1
}

void MWordFun::ConverToPdf()
{
  InitVBS( );
  AddVBS ("MyWord.Application.ActivePrinter = \"PDFCreator\"");
  AddVBS ("MyWord.ActiveDocument.PrintOut True, False, 0, , , , , , , , False ");
  EndVBS();
}

int MWordFun::InsertTableItem_Merge( String aTableBM, TStrings* aFiledValues )
{
  if( aTableBM == "" ||aFiledValues==NULL ||aFiledValues->Count==0 ) return -1;

  try
  {   int aColCount  = GetTabColCount(aTableBM);

      InitVBS(false);
      AddVBS("main = -1");
      AddVBS("  on error resume next ");
      AddVBS(" if MyWord.ActiveDocument.Bookmarks.Exists(\""+aTableBM+"\") = True Then ");
      AddVBS(" MyWord.Selection.GoTo -1,,,\""+aTableBM+"\"");
      AddVBS(" if MyWord.Selection.Tables.Count >0 Then");
      AddVBS("if MyWord.Selection.Tables(1).Rows.Count = 1 then");
      AddVBS(" MyWord.Selection.Tables(1).Rows.Add");
      AddVBS(" else");
      AddVBS(" IsEmptRow = true");
      AddVBS(" For i=1 to MyWord.Selection.Tables(1).Columns.Count");
      AddVBS(" MyWord.Selection.Tables(1).Cell(MyWord.Selection.Tables(1).Rows.Count, i).Select");
      AddVBS(" if ( Trim( MyWord.Selection.Range.Text) <>\"\" )  and  (Asc(Trim( MyWord.Selection.Range.Text)) <> 13) Then");
      AddVBS(" IsEmptRow = false");
      AddVBS("   exit for");
      AddVBS(" end if ");
      AddVBS(" next ");
      AddVBS(" if( IsEmptRow = false ) then  ");
      AddVBS("  MyWord.Selection.Tables(1).Rows.Add");
      AddVBS(" end if ");
      AddVBS(" end if ");

      //AddVBS(" for i=1 to  MyWord.Selection.Tables(1).Columns.Count ");
      for (int i=0; i<aColCount ; i++)
      {
        if( i+1>aFiledValues->Count) break;
        if( aFiledValues->Strings[i] ==  "@@" )
        {
          AddVBS("if  MyWord.Selection.Tables(1).Rows.Count >2 then  ");
          AddVBS(" MyWord.Selection.Tables(1).Cell(MyWord.Selection.Tables(1).Rows.Count, "+IntToStr(i+1)+").Select");
          AddVBS(" MyWord.Selection.MoveUp 5, 1, 1");
          AddVBS(" MyWord.Selection.Cells.Merge");
          AddVBS("end if ");
        }
        else
        {
          AddVBS(" MyWord.Selection.Tables(1).Cell(MyWord.Selection.Tables(1).Rows.Count, "+IntToStr(i+1)+").Select");
          AddVBS_StringsStrToWordStr(aFiledValues->Strings[i]);
          //AddVBS(" MyWord.Selection.Range.Text = \"" + aFiledValues->Strings[i]  + "\"");
        }
      }
      AddVBS("main = MyWord.Selection.Tables(1).Rows.Count");
      AddVBS(" end if ");
      AddVBS(" end if ");

      EndVBS(false);
      int aRow =  EvalScript(VBS );
      return aRow;
  }
  catch(Exception &aE)
  {
     throw Exception( "InsertTableItem出错！"+aE.Message);
  }
}

void MWordFun::AddVBS_StringsStrToWordStr( String aStringsStr )
{
  TStrings* aStrings = new TStringList;
  aStrings->Text = aStringsStr;

  for( int i=0; i<aStrings->Count; i++ )
  {
    String aStr = aStrings->Strings[i];
    AddVBS(" MyWord.Selection.TypeText  "+AnsiQuotedStr(  aStr ,'""') );
//    AddVBS(" MyWord.Selection.Range.Text = \"" +  aStr + "\"");
    if( i!=aStrings->Count-1 )
      AddVBS ("MyWord.Selection.TypeParagraph ");
  }
  delete aStrings;
}

void MWordFun::MaskQuit()
{
  if( HasWord == "New" )
      Quit();
}

//待集成

void MWordFun::InsertTitle( String aTitle ,String aStyle )
{
  if( aTitle == "" ) return;

  InitVBS( );
  AddVBS(" MyWord.Selection.TypeText  "+AnsiQuotedStr( aTitle ,'""') );
  AddVBS ("MyWord.Selection.Style  = MyWord.ActiveDocument.Styles(\""+aStyle+"\") ");
  AddVBS ("MyWord.Selection.TypeParagraph ");
  AddVBS ("MyWord.Selection.ClearFormatting ");
  EndVBS();
}

void  MWordFun::UpdatePictureTitle(String aBMName,String  aTitle)
{
   if( HasBM( aBMName )==false )
      return;

   int aSP=-1,aEP=-1;
   GetBMRange( aBMName,aSP,aEP);
   SelRange(aSP,aSP);

   InsertPicTitle( aTitle,"图");

   //InsertFiledTitle(aTitle );

   int aPos = GetCurPos();
   SelRange(aPos,aPos+aEP-aSP);
   DelSel();
}

void  MWordFun::UpdateTableTitle(String aBMName,String  aTitle)
{
   if( HasBM( aBMName )==false )
      return;

   int aSP=-1,aEP=-1;
   GetBMRange( aBMName,aSP,aEP);
   SelRange(aSP,aSP);

   InsertTableTitle(aTitle,"表");
   //InsertFiledTitle(aTitle );
   int aPos = GetCurPos();
   SelRange(aPos,aPos+aEP-aSP);
   DelSel();
}


void  MWordFun::UpdatePictureTitle(String aBMName,String  aTitle,bool bOnly,String aSubTitle)
{
   if( HasBM( aBMName )==false )
      return;

   int aSP=-1,aEP=-1;
   GetBMRange( aBMName,aSP,aEP);
   SelRange(aSP,aSP);

   InsertPicTitle( aTitle,aSubTitle,bOnly);

   int aPos = GetCurPos();
   SelRange(aPos,aPos+aEP-aSP);
   DelSel();
}

//-------------------函数-------------------------------------------------------

void MWordFun::CheckCursorPosition()
{
  //检查光标位置
  MaskShrinkBM();
  //UnSelRange();

  String aBMNameOfCursor = GetBMNameOfCursor();
  if( aBMNameOfCursor!="" )
    throw Exception( "当前光标在'" +
                           aBMNameOfCursor + "'的区域内，请移动光标！" );
  //SetActiveDocument();
}

//--------------------------------参数------------------------------------------
void MWordFun::AddVar( String aVarName,String aVarVal)
{
  if( aVarName == "" || aVarVal =="" ) return;
  InitVBS();
  AddVBS("for i =1 to MyWord.ActiveDocument.Variables.Count");
  AddVBS(" if MyWord.ActiveDocument.Variables.Item(i).Name = "+AnsiQuotedStr(aVarName,'\"') +" then");
  AddVBS("  MyWord.ActiveDocument.Variables.Item(i).Value = "+AnsiQuotedStr(aVarVal,'\"') );
  AddVBS(" exit sub");
  AddVBS(" end if");
  AddVBS("Next");
  AddVBS("  MyWord.ActiveDocument.Variables.Add "+AnsiQuotedStr(aVarName,'\"') +","+AnsiQuotedStr(aVarVal,'\"') );
  EndVBS( );
}

void MWordFun::AddVar( String aWordFileName, String aVarName,String aVarVal)
{
    InitVBS();
    AddVBS(" Set NewDoc = Nothing ");
    if ( aWordFileName == "" )
    {
      AddVBS(" Set NewDoc = MyWord.ActiveDocument");    //
    }
    else
    {
      if( FileExists( aWordFileName ) == false )
             throw Exception( aWordFileName+" 文件不存在！");
      AddVBS(" Set NewDoc =  MyWord.Documents.Open(\""+aWordFileName+"\")");
    }
    AddVBS("for i =1 to NewDoc.Variables.Count");
    AddVBS(" if NewDoc.Variables.Item(i).Name = "+AnsiQuotedStr(aVarName,'\"') +" then");
    AddVBS("  NewDoc.Variables.Item(i).Value = "+AnsiQuotedStr(aVarVal,'\"') );
    AddVBS(" exit sub");
    AddVBS(" end if");
    AddVBS("Next");
    AddVBS("  NewDoc.Variables.Add "+AnsiQuotedStr(aVarName,'\"') +","+AnsiQuotedStr(aVarVal,'\"') );
    EndVBS( );
}

void MWordFun::DelVarVals(String aWordFileName, TStrings* aVarNames )
{
    for(int i=0; i < aVarNames->Count; i++)
    {
       try
       {
           DelVarVal( aWordFileName,aVarNames->Strings[i] );
       }
       catch( Exception& e )
       {
       }
    }
}

//功能：删除BM对应的Range
void MWordFun::DelVarVal(String aWordFileName,String aVarName)
{
    InitVBS();
    AddVBS(" Set NewDoc = Nothing ");
    if ( aWordFileName == "" )
    {
      AddVBS(" Set NewDoc = MyWord.ActiveDocument");    //
    }
    else
    {
      if( FileExists( aWordFileName ) == false )
             throw Exception( aWordFileName+" 文件不存在！");
      AddVBS(" Set NewDoc =  MyWord.Documents.Open(\""+aWordFileName+"\")");
    }
    AddVBS("for i =1 to NewDoc.Variables.Count");
    AddVBS(" if NewDoc.Variables.Item(i).Name = "+AnsiQuotedStr(aVarName,'\"') +" then");
    AddVBS("  NewDoc.Variables.Item(i).Delete" );
    AddVBS("  exit sub");
    AddVBS(" end if");
    AddVBS("Next");
    EndVBS( );
}


String MWordFun::GetVarVal_NoExp( String aVarName, bool IsShowError )
{
  try
  {
    return GetVarVal( aVarName );
  }
  catch( Exception& e )
  {
    if( IsShowError==true )
      gError->Warn( "GetVarVal_NoExp!" + e.Message );
    return "";
  }
}

String MWordFun::GetVarVal( String aVarName )
{
  if( aVarName == "") return "";

  InitVBS(false);
  AddVBS("for i =1 to MyWord.ActiveDocument.Variables.Count");
  AddVBS(" if MyWord.ActiveDocument.Variables.Item(i).Name = "+AnsiQuotedStr(aVarName,'\"') +" then");
  AddVBS(" main= MyWord.ActiveDocument.Variables.Item(i).Value" );
  AddVBS(" exit function");
  AddVBS(" end if");
  AddVBS("Next");
  AddVBS(" mani=\"\" ");
  EndVBS( false );
  return EvalScript(VBS );
}

void  MWordFun::GotoTableItem( int aRow, int aCol)
{
  if( aRow<=0 || aCol <=0 )
    throw Exception("非法的行列号，行:"+IntToStr( aRow )+",列："+IntToStr(aCol)+"行列号必须大于0!");
  InitVBS( );
  AddVBS(" if MyWord.Selection.Tables.Count >0 Then");
  AddVBS("if ( MyWord.Selection.Tables(1).Rows.Count >="+IntToStr( aRow )+")  and (MyWord.Selection.Tables(1).Columns.Count >="+IntToStr( aCol )+") then ");
  AddVBS(" MyWord.Selection.Tables(1).Cell("+IntToStr( aRow )+","+IntToStr(aCol)+").Select");
  AddVBS(" end if ");
   AddVBS(" end if ");
  EndVBS( );
}
void  MWordFun::FlushTableRecord( int aRow)
{
  if( aRow<=0   )
    throw Exception("非法的行号，"+IntToStr( aRow )+",行号必须大于0!");
  InitVBS( );
  AddVBS(" if MyWord.Selection.Tables.Count >0 Then");
  AddVBS("if ( MyWord.Selection.Tables(1).Rows.Count >="+IntToStr( aRow )+") then ");
  AddVBS(" For i=1 to MyWord.Selection.Tables(1).Columns.Count");
  AddVBS(" MyWord.Selection.Tables(1).Cell("+IntToStr( aRow )+",i).Select");
  AddVBS(" MyWord.Selection.Range.Text = \"\"");
  AddVBS(" next");
  AddVBS(" end if ");
  AddVBS(" end if ");
  EndVBS( );
}
void MWordFun::FlushTableItem( int aRow,int aCol)
{
  if( aRow<=0 || aCol <=0 )
    throw Exception("非法的行列号，行:"+IntToStr( aRow )+",列："+IntToStr(aCol)+"行列号必须大于0!");
   InitVBS( );
  AddVBS(" if MyWord.Selection.Tables.Count >0 Then");
   AddVBS("if ( MyWord.Selection.Tables(1).Rows.Count >="+IntToStr( aRow )+")  and (MyWord.Selection.Tables(1).Columns.Count >="+IntToStr( aCol )+") then ");
  AddVBS(" MyWord.Selection.Tables(1).Cell("+IntToStr( aRow )+","+IntToStr(aCol)+").Select");
  AddVBS(" MyWord.Selection.Range.Text = \"\"");
  AddVBS(" end if ");
  AddVBS(" end if ");
  EndVBS( );
}
int MWordFun::InsertTableItem( String aTableBM, TStrings* aFiledValues )
{
  if( aTableBM == "" ||aFiledValues==NULL ||aFiledValues->Count==0 ) return -1;
  try
  {   int aColCount  = GetTabColCount(aTableBM);
      
      InitVBS(false);
       AddVBS("main = -1");
      AddVBS(" if MyWord.ActiveDocument.Bookmarks.Exists(\""+aTableBM+"\") = True Then ");
      AddVBS(" MyWord.Selection.GoTo -1,,,\""+aTableBM+"\"");
      AddVBS(" if MyWord.Selection.Tables.Count >0 Then");
      AddVBS("if MyWord.Selection.Tables(1).Rows.Count = 1 then");
      AddVBS(" MyWord.Selection.Tables(1).Rows.Add");
      AddVBS(" else");
      AddVBS(" IsEmptRow = true");
      AddVBS(" For i=1 to MyWord.Selection.Tables(1).Columns.Count");
      AddVBS(" MyWord.Selection.Tables(1).Cell(MyWord.Selection.Tables(1).Rows.Count, i).Select");
      AddVBS(" if ( Trim( MyWord.Selection.Range.Text) <>\"\" )  and  (Asc(Trim( MyWord.Selection.Range.Text)) <> 13) Then");
      AddVBS(" IsEmptRow = false");
      AddVBS("   exit for");
      AddVBS(" end if ");
      AddVBS(" next ");
      AddVBS(" if( IsEmptRow = false ) then  ");
      AddVBS("  MyWord.Selection.Tables(1).Rows.Add");
      AddVBS(" end if ");
      AddVBS(" end if ");
      
      //AddVBS(" for i=1 to  MyWord.Selection.Tables(1).Columns.Count ");
      for (int i=0; i<aColCount ; i++)
      {
        if( i+1>aFiledValues->Count) break;
        AddVBS(" MyWord.Selection.Tables(1).Cell(MyWord.Selection.Tables(1).Rows.Count, "+IntToStr(i+1)+").Select");
        AddVBS(" MyWord.Selection.Range.Text = \""+aFiledValues->Strings[i]+"\"");
      }
      AddVBS("main = MyWord.Selection.Tables(1).Rows.Count");
      AddVBS(" end if ");
      AddVBS(" end if ");

      EndVBS(false);
      int aRow =  EvalScript(VBS );
      return aRow;
  }
  catch(Exception &aE)
  {
     throw Exception( "InsertTableItem出错！"+aE.Message);
  }
}




//最后添加标签
void MWordFun::DelTableItemsAndAddBM(String aTableBM,bool IsDelTitle )
{
  if( aTableBM == ""  ) return;
  InitVBS();
  AddVBS(" if MyWord.ActiveDocument.Bookmarks.Exists(\""+aTableBM+"\") = True Then ");
  AddVBS(" MyWord.Selection.GoTo -1,,,\""+aTableBM+"\"");
  AddVBS(" if MyWord.Selection.Tables.Count >0 Then");
  if( IsDelTitle==false )
  {
    AddVBS("For i = MyWord.Selection.Tables(1).Rows.Count To 2 Step -1");
    AddVBS("MyWord.Selection.Tables.Item(1).Rows.Item(i).Delete");
    AddVBS("Next");
    //AddVBS(" MyWord.Selection.Tables(1).Rows.Add");
  }else
    AddVBS("MyWord.Selection.Tables.Item(1).Rows.Delete");
  AddVBS(" end if ");
  AddVBS(" end if ");

  EndVBS();

  AddBMByPos(aTableBM,GetCurPos(),GetCurPos());
}

void MWordFun::DelTableItems(String aTableBM,bool IsDelTitle )
{
  if( aTableBM == ""  ) return;
  InitVBS();
  AddVBS(" if MyWord.ActiveDocument.Bookmarks.Exists(\""+aTableBM+"\") = True Then ");
  AddVBS(" MyWord.Selection.GoTo -1,,,\""+aTableBM+"\"");
  AddVBS(" if MyWord.Selection.Tables.Count >0 Then");
  if( IsDelTitle==false )
  {
    AddVBS("For i = MyWord.Selection.Tables(1).Rows.Count To 3 Step -1");
    AddVBS("MyWord.Selection.Tables(1).Rows(i).Delete");
    AddVBS("Next");
     AddVBS("if MyWord.Selection.Tables(1).Rows.Count >1 then");
      AddVBS("For m = 1 To MyWord.Selection.Tables(1).Columns.Count");
    AddVBS(" MyWord.Selection.Tables(1).Cell(2,m).Select");
        AddVBS(" MyWord.Selection.Range.Text = \"\"");
    AddVBS("Next");
    AddVBS(" end if ");

  }else
    AddVBS("MyWord.Selection.Tables.Item(1).Rows.Delete");
  AddVBS(" end if ");
  AddVBS(" end if ");

  EndVBS();
  AddBMByPos(aTableBM,GetCurPos(),GetCurPos());
}

/*
void MWordFun::DelTableItems(String aTableBM,bool IsDelTitle )
{
  if( aTableBM == ""  ) return;
  InitVBS();
  AddVBS(" if MyWord.ActiveDocument.Bookmarks.Exists(\""+aTableBM+"\") = True Then ");
  AddVBS(" MyWord.Selection.GoTo -1,,,\""+aTableBM+"\"");
  AddVBS(" if MyWord.Selection.Tables.Count >0 Then");
  if( IsDelTitle==false )
  {
    AddVBS("For i = MyWord.Selection.Tables(1).Rows.Count To 2 Step -1");
    AddVBS("MyWord.Selection.Tables.Item(1).Rows.Item(i).Delete");
    AddVBS("Next");
    AddVBS(" MyWord.Selection.Tables(1).Rows.Add");
  }else
    AddVBS("MyWord.Selection.Tables.Item(1).Rows.Delete");
  AddVBS(" end if ");
  AddVBS(" end if ");

  EndVBS();
}
*/
//根据窗口设置宽度
void  MWordFun::TableFitWindow(String  aTableBM)
{
   if(aTableBM == "") return;

   InitVBS();
   AddVBS(" if MyWord.ActiveDocument.Bookmarks.Exists(\""+aTableBM+"\") = True Then ");
   AddVBS(" MyWord.Selection.GoTo -1,,,\""+aTableBM+"\"");
   AddVBS(" if MyWord.Selection.Tables.Count >0 Then");
     AddVBS(" MyWord.Selection.Tables(1).AutoFitBehavior 2");
   AddVBS(" end if ");
   AddVBS(" end if ");

   EndVBS();
}

void MWordFun::SelBMS( TStrings* aBMNames )
{
   if( aBMNames == NULL || aBMNames->Count <=0 )
      return;

   int aS, aE;
   int aStart;
   for( aStart=0; aStart<aBMNames->Count; aStart++ )
   {
     GetBMRange( aBMNames->Strings[aStart],aS,aE );
     if( aS >=0 )
       break;
   }

   for (int i=aStart+1; i<aBMNames->Count;i++ )
   {
      int atmpSP,atmpEP;
      GetBMRange( aBMNames->Strings[i],atmpSP,atmpEP);
      if( atmpSP<0 )
        continue;

      aS =  aS<atmpSP?aS:atmpSP;
      aE =  aE>atmpEP?aE:atmpEP;
   }
   SelRange(aS,aE);
}


//  61548 黑圆点  61550 黑矩形   61558 黑菱形

void MWordFun::InsertIcoListItem(String aBMName, TStrings* aList,int aStyle)
{
     int aStPos =GetCurPos() ;
     String aTmpStyle =IntToStr( aStyle);
     if( aTmpStyle =="")
       aTmpStyle= "61548";

     InitVBS();
     AddVBS(" With MyWord.ListGalleries(1).ListTemplates(1).ListLevels(1)");
     AddVBS("   .NumberFormat = ChrW("+aTmpStyle+")");
     AddVBS("   .StartAt = 1");

     AddVBS("End With");

     AddVBS(" MyWord.Selection.Range.ListFormat.ApplyListTemplate MyWord.ListGalleries(1).ListTemplates(1), True, 0,2");
     EndVBS();

     //插入文本
     InsertTxt(aList );
     if( aBMName == "") return;

     int aEndPos = GetCurPos() ;
     //创建BM
     AddBMByPos( aBMName,aStPos,aEndPos );
     SelRange( aEndPos,aEndPos);
}

void MWordFun::UpdateIcoListItem(String aBMName, TStrings* aList,int aStyle)
{
    if( aBMName =="" ||HasBM( aBMName )==false ) return;

   int aSP=-1,aEP=-1;
   GetBMRange( aBMName,aSP,aEP);
   SelRange(aSP,aSP);
   InsertIcoListItem( "",aList ,aStyle);
        //插入文本

   int aPos = GetCurPos();
   SelRange(aPos,aPos+aEP-aSP);
   DelSel();
}

/*void MWordFun::InsertListItem( String aBMName, TStrings* aList,
                               bool aIsContinue,int aNumStyle,
                               String aBrac1,String aBrac2)
{
    int aStPos =GetCurPos() ;
    String aTmpStyle =IntToStr( aNumStyle);
    if( aTmpStyle =="")
       aTmpStyle= "0";
    InitVBS();
    AddVBS(" With MyWord.ListGalleries(2).ListTemplates(1).ListLevels(1)");
    AddVBS("   .NumberFormat = \""+aBrac1+"%1"+aBrac2+"\"");
    AddVBS("   .StartAt = 1");
    AddVBS("   .NumberStyle = "+aTmpStyle);//0 数字 4字母
    AddVBS("End With");
    String aTmpContinue = "True";
    if( !aIsContinue )
       aTmpContinue = "False";
    AddVBS(" MyWord.Selection.Range.ListFormat.ApplyListTemplate MyWord.ListGalleries(2).ListTemplates(1), "+aTmpContinue+", 0,2");
    EndVBS();

    //插入文本
    InsertTxt(aList );
    if( aBMName == "") return;

    int aEndPos = GetCurPos() ;
    
      //创建BM
    AddBMByPos( aBMName,aStPos,aEndPos );
    SelRange( aEndPos,aEndPos);
}

void MWordFun::UpdateListItem( String aBMName, String aItem,
                               bool aIsContinue,
                               int aNumStyle,String aBrac1,String aBrac2)
{
  if( aBMName =="" ||HasBM( aBMName )==false ) return;

  int aSP=-1,aEP=-1;
  GetBMRange( aBMName,aSP,aEP);

  SelRange(aSP,aSP);
  InsertListItem( "",aItem ,aIsContinue,aNumStyle ,aBrac1,aBrac2);
        //插入文本

   int aPos = GetCurPos();
   SelRange(aPos,aPos+aEP-aSP);
   DelSel();
}

void MWordFun::UpdateListItem( String aBMName, TStrings* aList,bool aIsContinue,int aNumStyle,String aBrac1,String aBrac2)
{
    if( aBMName =="" ||HasBM( aBMName )==false ) return;

   int aSP=-1,aEP=-1;
   GetBMRange( aBMName,aSP,aEP);
   SelRange(aSP,aSP);
   InsertListItem( "",aList ,aIsContinue,aNumStyle ,aBrac1,aBrac2);
        //插入文本

   int aPos = GetCurPos();
   SelRange(aPos,aPos+aEP-aSP);
   DelSel();
}

//功能：在word当前位置插入编号项  ,并建立aBMName书签，书签名为空则不创建书签
//参数：[ String aBrac1 编号前符号，括号形式 ]
//      [ String aBrac2 编号后符号，括号形式 ]
//      [ int aNumStyle 数字格式   0 阿拉伯数字，4 小写字母  ,39 大写 一、二、三，18 带圈 阿拉伯数字 ]
//      [ aIsContinue 同样的编号形式是否继续之前编号数字 ]

void MWordFun::InsertListItem( String aBMName, String aItem,bool aIsContinue,int aNumStyle,String aBrac1,String aBrac2)
{
  int aStPos =GetCurPos() ;
  String aTmpStyle =IntToStr( aNumStyle);
  if( aTmpStyle =="")
    aTmpStyle= "0";

  InitVBS();
  AddVBS(" With MyWord.ListGalleries(2).ListTemplates(1).ListLevels(1)");
  AddVBS("   .NumberFormat = \""+aBrac1+"%1"+aBrac2+"\"");
  AddVBS("   .StartAt = 1");
  AddVBS("   .NumberStyle = "+aTmpStyle);//0 数字 4字母
  AddVBS("End With");

  String aTmpContinue = "True";
  if( !aIsContinue )
    aTmpContinue = "False";

  AddVBS(" MyWord.Selection.Range.ListFormat.ApplyListTemplate MyWord.ListGalleries(2).ListTemplates(1), "+aTmpContinue+", 0,2");
  EndVBS();

  //插入文本
  InsertTxt(aItem );

  if( aBMName == "") return;

  int aEndPos = GetCurPos() ;

  //创建BM
  AddBMByPos( aBMName,aStPos,aEndPos );
  SelRange( aEndPos,aEndPos);

  NewLine();
  ClearFormat();
} */

void MWordFun::InsertListItem(String aBMName, String aItem,bool aIsContinue,int aNumStyle,String aBrac1,String aBrac2)
{
   int aStPos =GetCurPos() ;
   String aTmpStyle =IntToStr( aNumStyle);
   if( aTmpStyle =="")
       aTmpStyle= "0";
   InitVBS();
   AddVBS(" With MyWord.ListGalleries(2).ListTemplates(1).ListLevels(1)");
   AddVBS("   .NumberFormat = \""+aBrac1+"%1"+aBrac2+" \"");
   AddVBS("   .StartAt = 1");
   AddVBS("   .NumberStyle = "+aTmpStyle);//0 数字 4字母
   AddVBS("End With");
   String aTmpContinue = "True";
   if( !aIsContinue )
       aTmpContinue = "False";
   AddVBS(" MyWord.Selection.Range.ListFormat.ApplyListTemplate MyWord.ListGalleries(2).ListTemplates(1), "+aTmpContinue+", 0,2");
   EndVBS();

   //插入文本
   InsertTxt(aItem );
   if( aBMName == "") return;
   int aEndPos = GetCurPos() ;

      //创建BM
   AddBMByPos( aBMName,aStPos,aEndPos );
   SelRange( aEndPos,aEndPos);
   NewLine();
   ClearFormat();
}

void MWordFun::UpdateListItem(String aBMName, String aItem,bool aIsContinue,int aNumStyle,String aBrac1,String aBrac2)
{
  if( aBMName =="" ||HasBM( aBMName )==false ) return;

  int aSP=-1,aEP=-1;
  GetBMRange( aBMName,aSP,aEP);
  SelRange(aSP,aSP);
  InsertListItem( "",aItem ,aIsContinue,aNumStyle ,aBrac1,aBrac2);
        //插入文本

  int aPos = GetCurPos();
  SelRange(aPos,aPos+aEP-aSP);
  DelSel();
}

void MWordFun::InsertListItem( String aBMName, TStrings* aList,bool aIsContinue,int aNumStyle,String aBrac1,String aBrac2)
{
     int aStPos =GetCurPos() ;
     String aTmpStyle =IntToStr( aNumStyle);
     if( aTmpStyle =="")
       aTmpStyle= "0";
     InitVBS();
     AddVBS(" With MyWord.ListGalleries(2).ListTemplates(1).ListLevels(1)");
     AddVBS("   .NumberFormat = \""+aBrac1+"%1"+aBrac2+" \"");
     AddVBS("   .StartAt = 1");
    AddVBS("   .NumberStyle = "+aTmpStyle);//0 数字 4字母
    AddVBS("End With");
    String aTmpContinue = "True";
    if( !aIsContinue )
       aTmpContinue = "False";
    AddVBS(" MyWord.Selection.Range.ListFormat.ApplyListTemplate MyWord.ListGalleries(2).ListTemplates(1), "+aTmpContinue+", 0,2");
    EndVBS();
    //插入文本
    InsertTxt(aList );
    if( aBMName == "") return;

    int aEndPos = GetCurPos() ;
      //创建BM
    AddBMByPos( aBMName,aStPos,aEndPos );
    SelRange( aEndPos,aEndPos);
}

void MWordFun::UpdateListItem( String aBMName, TStrings* aList,bool aIsContinue,int aNumStyle,String aBrac1,String aBrac2)
{
    if( aBMName =="" ||HasBM( aBMName )==false ) return;

   int aSP=-1,aEP=-1;
   GetBMRange( aBMName,aSP,aEP);
   SelRange(aSP,aSP);
   InsertListItem( "",aList ,aIsContinue,aNumStyle ,aBrac1,aBrac2);
        //插入文本

   int aPos = GetCurPos();
   SelRange(aPos,aPos+aEP-aSP);
   DelSel();
}

String MWordFun::GetPreBMNameofCursor()
{
   InitVBS(false);
   AddVBS(" Set BMs = MyWord.ActiveDocument.Bookmarks ");
   AddVBS("  aName  = \"\" ");
    AddVBS("  aPos  = 0");
   AddVBS(" For i = 1 To BMs.Count ");
   AddVBS("    Set aBM = BMs.Item(i) ");
   AddVBS("    If ( aBM.Range.End < MyWord.Selection.Range.Start ) Then ");
   AddVBS("     	If ( aName  = \"\") then  ");
   AddVBS("         aName  = aBM.Name ");
   AddVBS("         aPos =  aBM.Range.End ");
   AddVBS("    else  ");
   AddVBS("       if( aPos < aBM.Range.End ) then ");
   AddVBS("         aName  = aBM.Name ");
   AddVBS("         aPos =  aBM.Range.End ");
   AddVBS("     End If ");
   AddVBS("     End If ");
   AddVBS("     End If ");
   AddVBS("  Next ");
   AddVBS(" main = aName ");
   EndVBS(false );
   String aName = EvalScript(VBS );
   return aName;
}

void MWordFun::MaskShrinkBM()
{
   InitVBS( );

   AddVBS(" Set BMs = MyWord.ActiveDocument.Bookmarks ");
    AddVBS(" aSelSt=MyWord.Selection.Range.Start");
    AddVBS(" aSelEnd=MyWord.Selection.Range.End");
   AddVBS(" For i = 1 To BMs.Count ");
   AddVBS("    Set aBM = BMs.Item(i) ");

   AddVBS("    If (MyWord.Selection.Range.Start >= aBM.Range.Start  ) And (MyWord.Selection.Range.End <= aBM.Range.End) Then ");
    AddVBS(" aBmSt=aBM.Range.Start");
    AddVBS(" aBmEnd=aBM.Range.End");
  
   AddVBS("aE=aBmEnd");
   AddVBS("aSt=aBmSt");

   AddVBS(" MyWord.Selection.GoTo -1,,,aBM.Name");
   AddVBS("aTabEnd=aBmSt");
   AddVBS(" if MyWord.Selection.Tables.Count >0 Then");
    AddVBS(" MyWord.Selection.Tables(1).Cell(MyWord.Selection.Tables(1).Rows.Count, MyWord.Selection.Tables(1).Columns.Count).Select");
    AddVBS("aTabEnd=MyWord.Selection.End");
   AddVBS("End If ");
   AddVBS(" For j = aE - 1 To aSt Step -1");
   AddVBS("MyWord.ActiveDocument.Range(j, aE).Select ");
   AddVBS("astr = Trim(MyWord.Selection.Text)");
   AddVBS("If (astr <> \"\") Then");
   AddVBS(" If (Asc(astr) <> 13) Then");
   AddVBS(" aBmEnd =j+1");
   AddVBS("Exit for");
   AddVBS("End If ");

   AddVBS("End If ");

   AddVBS("Next ");

   AddVBS(" For m = aSt+1 To aE ");
   AddVBS("MyWord.ActiveDocument.Range(aSt,m ).Select ");
   AddVBS("astr = Trim(MyWord.Selection.Text)");
   AddVBS("If (astr <> \"\") Then");
   AddVBS(" If (Asc(Right(astr, 1)) <> 13) Then");
   AddVBS(" aBmSt = m-1");
   AddVBS("Exit for");
   AddVBS("End If ");
   AddVBS("End If ");
   AddVBS("Next ");
  //  AddVBS(" Msgbox aBmSt & \";;\" & aBmEnd ");
   AddVBS(" if( aTabEnd > aBmEnd ) then ");
   AddVBS(" aBM.End = aTabEnd ");
   AddVBS("else ");
   AddVBS(" aBM.End = aBmEnd ");
   AddVBS("     End If ");
   AddVBS(" aBM.Start = aBmSt ");
   AddVBS("MyWord.ActiveDocument.Range(aSelSt,aSelEnd ).Select ");
   AddVBS("	    Exit sub  ");
   AddVBS("     End If ");
   AddVBS("  Next ");

   EndVBS(  );
}

//---------------BMSToFile-------------------------------------------------

void MWordFun::CopyBMSToNewFile( TStrings* aBMList,String aNewWordFile )
{
  CombinBMIntoFile( aBMList,aNewWordFile );
}

void MWordFun::CopyBMToNewFile( String aBMName,String aNewFile )
{
   if( aBMName=="" || aNewFile=="" ) return;
   InitVBS();
   AddVBS(" if MyWord.ActiveDocument.Bookmarks.Exists(\""+aBMName+"\") = True Then ");
   AddVBS(" MyWord.Selection.GoTo -1,,,\""+aBMName+"\"");

  AddVBS(" MyWord.Selection.copy");
  AddVBS(" Set NewDoc = Nothing ");
  AddVBS(" Set NewDoc = MyWord.Documents.Add( \"Normal\", False, 0,true )");
  AddVBS(" MyWord.Selection.Paste");
  AddVBS(" NewDoc.SaveAs  \""+aNewFile+"\"" );
  AddVBS(" NewDoc.Close" );
   AddVBS(" end if ");
  EndVBS( );
}

void MWordFun::SaveBMS_SelectionToNewFile( TStrings* aBMList,String aNewWordFile)
{
    //先选择
    SelBMS(aBMList);
    InitVBS();
    AddVBS(" MyWord.Selection.copy");
    AddVBS(" Set NewDoc = Nothing ");
    AddVBS(" Set NewDoc = MyWord.Documents.Add( \"Normal\", False, 0,true )");
    AddVBS(" MyWord.Selection.Paste");
    AddVBS(" NewDoc.SaveAs  \""+aNewWordFile+"\"" );
    AddVBS(" NewDoc.Close");
    EndVBS( );
}


void MWordFun::CombinBMIntoFile( TStrings* aBMList,String aNewWordFile)
{
  if( aBMList==NULL || aBMList->Count == 0 )
    throw Exception("CombinBMContIntoFile书签为空！");
  String aPath = ExtractFilePath( aNewWordFile );
  TStrings* aTmpList = new TStringList;

  for (int i=0; i< aBMList->Count; i++)
  {
    String aTmpFileName = aPath+aBMList->Strings[i]+"_TmpBMF.doc";
    CopyBMToNewFile( aBMList->Strings[i],aTmpFileName );
    aTmpList->Add(aTmpFileName);
  }
  NewFile(aNewWordFile);
  for (int i=0;i<aTmpList->Count ;i++)
  {
    InsertFile_BM( aBMList->Strings[i],aTmpList->Strings[i]);
    DeleteFile(aTmpList->Strings[i]);
  }
  Save("",true);
}

/*
void MWordFun::InsertSubWordFile( String aNodeId ,String aWordFileName )
{
  if( FileExists( aWordFileName ) == false )
    throw Exception("InsertWordFile出错，要插入的文件："+aWordFileName+"不存在！");
  //ConfirmRunEnv( aNodeId,"InsertSubWordFile");
  try
  {
    if( HasBM( aNodeId ) )//更新数据
      {
         UpdateSubWordFile( aNodeId,aWordFileName );
      }
      else
      {
        //创建标签
        int aStPos = GetCurPos() ;
        //插入文本
        InsertFile(aWordFileName );
        int aEndPos = GetCurPos() ;
        //创建BM
        AddBMByPos( aNodeId,aStPos,aEndPos );
       SelRange( aEndPos,aEndPos);
      }
   }
  catch(Exception &aE)
  {
    throw Exception("InsertSubWordFile出错，"+aE.Message);
  }
} */

void MWordFun::InsertFile_BM( String aBMName ,String aWordFileName )
{
  if( FileExists( aWordFileName ) == false )
    throw Exception("InsertWordFile出错，要插入的文件："+aWordFileName+"不存在！");

  try
  {
    //创建标签
    int aStPos = GetCurPos() ;

    //插入文本
    InsertFile( aWordFileName );  
    int aEndPos = GetCurPos() ;

    //创建BM
    AddBMByPos( aBMName,aStPos,aEndPos );
    SelRange( aEndPos,aEndPos );
  }
  catch(Exception &aE)
  {
    throw Exception("InsertSubWordFile出错，"+aE.Message);
  } 
}

void MWordFun::UpdateTableFile_BM( String aBMName ,String aWordFileName )
{
   try
   {
     if( FileExists(aWordFileName)==false )   //Word不存在
     {
       UpdateText_ByBMName( aBMName, " " );
       return;
     }

     if( HasBM(aBMName) == false )
     {
       InsertFile_BM(aBMName,aWordFileName);
       return;
     }

     int aSP=-1,aEP=-1;
     GetBMRange( aBMName,aSP,aEP);                   //获取起始和结尾

     SelRange(aSP,aSP);
     InsertFile_BM(aBMName,aWordFileName);           //选中，插入

     int aPos = GetCurPos();
     //SelRange(aSP,aPos);
     //DelSel();
     AddBMByPos( aBMName,aSP,aPos);
   }
  catch(Exception &aE)
  {
    throw Exception("UpdateSubWordFile出错，"+aE.Message);
  }
}

void MWordFun::UpdateFile_BM( String aBMName ,String aWordFileName )
{
  try
  {
     if( FileExists(aWordFileName)==false )   //Word不存在
     {
       UpdateText_ByBMName( aBMName, " " );
       return;
     }

     if( HasBM(aBMName) == false )
     {
       InsertFile_BM(aBMName,aWordFileName);
       return;
     }

     int aSP=-1,aEP=-1;
     GetBMRange( aBMName,aSP,aEP);                   //获取起始和结尾

     SelRange(aSP,aSP);
     InsertFile_BM(aBMName,aWordFileName);           //选中，插入

     int aPos = GetCurPos();
     SelRange(aPos-1,aPos+aEP-aSP);
     DelSel();
   }
  catch(Exception &aE)
  {
    throw Exception("UpdateSubWordFile出错，"+aE.Message);
  }
}

/*void MWordFun::UpdateFile_BM( String aBMName ,String aWordFileName )
{
  try
  {
     if( FileExists(aWordFileName)==false )
     {
       UpdateText_ByBMName( aBMName, " " );
       return;
     }

     if( HasBM(aBMName) == false )
     {
       InsertFile_BM(aBMName,aWordFileName);
       return;
     }

     int aSP=-1,aEP=-1;
     GetBMRange( aBMName,aSP,aEP);                   //获取起始和结尾

     SelRange(aSP,aSP);
     InsertFile_BM(aBMName,aWordFileName);           //选中，插入

     int aPos = GetCurPos();
     SelRange(aPos,aPos+aEP-aSP);
     DelSel();
   }
  catch(Exception &aE)
  {
    throw Exception("UpdateSubWordFile出错，"+aE.Message);
  }
} */

/*void MWordFun::UpdateSubWordFile( String aNodeId ,String aWordFileName )
{
  try
  {
     DelBMVal( aNodeId );
     InsertSubWordFile(aNodeId,aWordFileName);
   }
  catch(Exception &aE)
  {
    throw Exception("UpdateSubWordFile出错，"+aE.Message);
  }
} */

int MWordFun::GetCurPos()
{
  InitVBS(false);
  AddVBS(" main = MyWord.Selection.Range.Start ");
  EndVBS(false);
  int aPos = EvalScript(VBS );
  return aPos;
}

void MWordFun::AddBMByPos(String aBMName, int aStPos,int aEndPos )
{
  if( HasBM( aBMName ) ) return;
  if( aBMName == "" || aStPos <0|| aEndPos<0 ) return;
  
  InitVBS();
  AddVBS("MyWord.Selection.SetRange "+IntToStr( aStPos)+","+IntToStr( aEndPos));
  AddVBS(" MyWord.ActiveDocument.Bookmarks.Add \""+aBMName +"\",MyWord.Selection.Range ");
  EndVBS();
}

//功能：BM改名

void MWordFun::RenameBM( String aOldBM, String aNewBM )
{
  if( HasBM(aOldBM) == false )
    return;
    
  int aStartPos=-1, aEndPos=-1;
  GetBMRange( aOldBM, aStartPos, aEndPos );

  if( aStartPos<0 ||  aEndPos<0 )
    return;

  DelBM( aOldBM );
  AddBMByPos( aNewBM,  aStartPos, aEndPos );
}

//功能：删除BM
void MWordFun::DelBM( String aBMName )
{
   if ( aBMName == "" )
     return;

   InitVBS();
   AddVBS(" Set NewDoc = Nothing ");
   AddVBS(" if MyWord.ActiveDocument.Bookmarks.Exists(\""+aBMName+"\") = True Then ");
   AddVBS("  MyWord.ActiveDocument.Bookmarks(\""+aBMName+"\").Delete " );
   AddVBS(" end if ");
   InitBM( );
   EndVBS();
}

void MWordFun::DelBMVals( TStrings* aBMNames )
{
  for( int i=0; i<aBMNames->Count; i++ )
  {
    try
    {
      DelBMVal( aBMNames->Strings[i] );
    }
    catch( Exception& e )
    {
    }
  }
}

//功能：删除BM对应的Range
void MWordFun::DelBMVal( String aBMName )
{
  InitVBS();
  AddVBS(" if MyWord.ActiveDocument.Bookmarks.Exists(\""+aBMName+"\") = True Then ");
  AddVBS(" MyWord.Selection.GoTo -1,,,\""+aBMName+"\"");

  //AddVBS(" MyWord.Selection.Delete");
  AddVBS(" MyWord.Selection.Cut");

  //AddVBS(" MyWord.ActiveDocument.Bookmarks(\""+aBMName+"\").Delete " );
  AddVBS(" end if ");
  EndVBS();
}

void MWordFun::InsertFile( String aFileName )
{
  InitVBS();
  AddVBS(" MyWord.Selection.InsertFile "+AnsiQuotedStr(aFileName,'\"')+",\"\",False,False,False");
  EndVBS( );
}

bool MWordFun::HasBM( String aBMName )
{
  if( aBMName == "" ) return false;
  InitVBS(false);
  AddVBS(" main =  MyWord.ActiveDocument.Bookmarks.Exists(\""+aBMName+"\")  ");
  EndVBS(false );
  bool aHas = EvalScript(VBS );
  return aHas;
}

//20151114
void MWordFun::SetDocReadOnly_NoExp( bool IsReadOnly, bool IsShow )
{
  try
  {
     SetDocReadOnly( IsReadOnly );
  }
  catch( Exception& e )
  {
     if( IsShow==true )
       gError->Warn( "SetDocReadOnly_NoExp!" + e.Message );
  }
}

void MWordFun::SetDocReadOnly( bool IsReadOnly )
{
    InitVBS();
    if( IsReadOnly ) //只读
    {
       AddVBS ("MyWord.ActiveDocument.Protect 3, False, \"lsxd\", False, False");
    }
    else
    {
      AddVBS ("MyWord.ActiveDocument.Unprotect \"lsxd\"");
    }
    AddVBS ("MyWord.CommandBars(\"Task Pane\").Visible = False");
    EndVBS();
}

int  MWordFun::GetTabColCount( String aTableBM )
{
      if( aTableBM == "" ) return 0;
      InitVBS(false);
      AddVBS(" if MyWord.ActiveDocument.Bookmarks.Exists(\""+aTableBM+"\") = True Then ");
      AddVBS(" MyWord.Selection.GoTo -1,,,\""+aTableBM+"\"");
      AddVBS(" if MyWord.Selection.Tables.Count >0 Then");
      AddVBS(" main = MyWord.Selection.Tables(1).Columns.Count");
      AddVBS("exit function ");
      AddVBS(" end if ");
      AddVBS(" end if ");
      AddVBS(" main =0 ");
      EndVBS(false);
      int aCount = EvalScript(VBS );
      return aCount;
}

void MWordFun::InsertTableItem_1( String aTableBM, TStrings* aFiledValues )
{
  if( aTableBM == "" ||aFiledValues==NULL ||aFiledValues->Count==0 ) return;
  try
  {
      int aColCount  = GetTabColCount(aTableBM);

      InitVBS();
      AddVBS(" if MyWord.ActiveDocument.Bookmarks.Exists(\""+aTableBM+"\") = True Then ");
      AddVBS(" MyWord.Selection.GoTo -1,,,\""+aTableBM+"\"");
      AddVBS(" if MyWord.Selection.Tables.Count >0 Then");
      AddVBS(" MyWord.Selection.Tables(1).Rows.Add");
      //AddVBS(" for i=1 to  MyWord.Selection.Tables(1).Columns.Count ");
      for (int i=0; i<aColCount ; i++)
      {
        if( i+1 > aFiledValues->Count) break;
        AddVBS(" MyWord.Selection.Tables(1).Cell(MyWord.Selection.Tables(1).Rows.Count, "+IntToStr(i+1)+").Select");
        AddVBS(" MyWord.Selection.Range.Text = \""+aFiledValues->Strings[i]+"\"");
      }
      AddVBS(" end if ");
      AddVBS(" end if ");
      EndVBS();
  }
  catch(Exception &aE)
  {
     throw Exception( "InsertTableItem出错！"+aE.Message);
  }
} 

bool MWordFun::IsRun()
{
  return ProcessExists1("WINWORD.EXE");
}

void MWordFun::ConfirmRun()
{
   if( ProcessExists1("WINWORD.EXE")==false )
   {

     MOfficeFun::InitVBS();
     AddVBS(" Set MyWord = CreateObject(\"Word.Application\")");
     AddVBS(" MyWord.Visible = true ");
     EndVBS();

     HasWord = "New";
   }
   else
   {
     MOfficeFun::InitVBS();
     AddVBS(" Set MyWord = GetObject(,\"Word.Application\")");
     AddVBS(" MyWord.Visible = true ");
     EndVBS();

     HasWord = "Old";
   } 
   WordApp = Variant::GetActiveObject("Word.Application");
   ::Sleep(200);
}

void MWordFun::InitVBS( bool IsOnlyRun )
{
    MOfficeFun::InitVBS( IsOnlyRun );

   // if( FindWindow("OpusApp",NULL )<= 0 )//word未启动
    if( ProcessExists1("WINWORD.EXE")==false )
       AddVBS(" Set MyWord = CreateObject(\"Word.Application\")");
    else
       //AddVBS(" On Error Resume Next " );
       AddVBS(" Set MyWord = GetObject(,\"Word.Application\")");     //  '创建WORD文档

    if( IsVisible == true )
      AddVBS(" MyWord.Visible = True " );
}

//-------------------- InsertString --------------------------------------------

void MWordFun::InsertTxt( String aTxt )
{
   if( aTxt =="") return;
   InitVBS();
   AddVBS(" MyWord.Selection.TypeText  "+AnsiQuotedStr( aTxt ,'""') );
   EndVBS( );
}

void  MWordFun::InsertTxt( TStrings *aStr )
{
  if( aStr == NULL || aStr->Count==0) return;

  InitVBS();
  for (int i=0; i<aStr->Count ; i++)
  {
    AddVBS(" MyWord.Selection.TypeText  "+AnsiQuotedStr(  aStr->Strings[i]  ,'""') );
    if( i<aStr->Count-1)
      AddVBS ("MyWord.Selection.TypeParagraph ");
  }
  EndVBS();
}

void MWordFun::ClearFormat()
{
   InitVBS();
   AddVBS ("MyWord.Selection.ClearFormatting ");
   EndVBS();
}


void MWordFun::InsertText_ByBMName( String aBmName, String aInText )
{
    try
    {
      if(Trim(aInText) == "" )   //"   \r\n"
        aInText="  ";
      TStrings* aStrings = new TStringList;
      aStrings->Text = aInText;
      //aStrings->Add( aInText );
      InsertStrings_ByBMName( aBmName, aStrings );
      delete aStrings;
    }
    catch( Exception& e )
    {
      gError->Warn( "InsertText_ByBMName!" + e.Message );
    }

}

//只适于一个Text情况
/*void MWordFun::UpdateText_ByBMName( String aBmName, String aText )
{
  TStrings* aStrings = new TStringList;
  //aStrings->Add( aText );                                                     //modify by zzh0905
  aStrings->DelimitedText = aText;
  UpdateStrings_ByBMName( aBmName, aStrings );
  delete aStrings;
} */

void MWordFun::UpdateText_ByBMName( String aBmName, String aText )
{
  TStrings* aStrings = CRLFString2TStrings(aText,"@@");
  UpdateStrings_ByBMName( aBmName, aStrings );
  delete aStrings;
}

//文本段落型
/*void MWordFun::InsertStrings_ByBMName( String aBmName, TStrings* aMemo )
{
    if( aMemo == NULL || aMemo->Count ==0)
       throw Exception("插入内容为空！");

    //创建标签
    int aStPos = GetCurPos() ;

    //插入文本
    InsertTxt( aMemo );
    int aEndPos = GetCurPos();

    //创建BM
    AddBMByPos( aBmName,aStPos,aEndPos );
    SelRange( aEndPos,aEndPos );
} */

//文本段落型
void MWordFun::InsertStrings_ByBMName( String aBmName, TStrings* aMemo )
{
     if( aMemo == NULL)
       throw Exception("插入内容为空！");

    if(aMemo->Count == 0)
       aMemo->Add("  ");

    //创建标签
    int aStPos = GetCurPos() ;

    //插入文本
    InsertTxt( aMemo );
    int aEndPos = GetCurPos();

    //创建BM
    AddBMByPos( aBmName,aStPos,aEndPos );
    SelRange( aEndPos,aEndPos );
}

void MWordFun::UpdateStrings_ByBMName( String aBmName, TStrings* aMemo )
{
   if( HasBM(aBmName) == false ||aMemo==NULL )
       return;

   try
   {
      int aSP=-1,aEP=-1;
      GetBMRange( aBmName,aSP,aEP);

      SelRange(aSP,aSP);
      InsertStrings_ByBMName(aBmName,aMemo);
      int aPos = GetCurPos();
      SelRange(aPos,aPos+aEP-aSP);
      DelSel();
   }
   catch(Exception &aE)
   {
     throw Exception("UpDateStrins_ByBMName!"+aE.Message);
   }
}

void  MWordFun::FlushTableItemAndAddPictures(String aTableBM,int aRow,int aCol,TStrings* aFileList)
{
    if( aTableBM == "" || HasBM(aTableBM) == false || aFileList == NULL) return;

    if( aRow<=0 || aCol <=0 )
        throw Exception("非法的行列号，行:"+IntToStr( aRow )+",列："+IntToStr(aCol)+"行列号必须大于0!");

    InitVBS( );
    AddVBS(" if MyWord.ActiveDocument.Bookmarks.Exists(\""+aTableBM+"\") = True Then ");    //选中
    AddVBS(" MyWord.Selection.GoTo -1,,,\""+aTableBM+"\"");
    AddVBS(" end if ");

    AddVBS(" if MyWord.Selection.Tables.Count >0 Then");
    AddVBS("if ( MyWord.Selection.Tables(1).Rows.Count >="+IntToStr( aRow )+")  and (MyWord.Selection.Tables(1).Columns.Count >="+IntToStr( aCol )+") then ");
    AddVBS(" MyWord.Selection.Tables(1).Cell("+IntToStr( aRow )+","+IntToStr(aCol)+").Select");
    AddVBS(" MyWord.Selection.Range.Text = \"\"");                                          //清空

    //填写
    for(int i=0; i < aFileList->Count; i++)
    {
      String aFileName = aFileList->Strings[i];
      if( FileExists( aFileName ) == false )           //sxd
        continue;

      AddVBS(" MyWord.Selection.InlineShapes.AddPicture \""+aFileName+"\",False,True");
      if(i < aFileList->Count-1)
         AddVBS(" MyWord.Selection.TypeParagraph");
    }
    AddVBS(" end if ");
    AddVBS(" end if ");

    EndVBS();
}

void MWordFun::FlushTableItemAndAddText(String aTableBM, int aRow,int aCol,String aText)
{
    if( aTableBM == "" || HasBM(aTableBM) == false) return;

    if( aRow<=0 || aCol <=0 )
        throw Exception("非法的行列号，行:"+IntToStr( aRow )+",列："+IntToStr(aCol)+"行列号必须大于0!");

    InitVBS( );
    AddVBS(" if MyWord.ActiveDocument.Bookmarks.Exists(\""+aTableBM+"\") = True Then ");    //选中
    AddVBS(" MyWord.Selection.GoTo -1,,,\""+aTableBM+"\"");
    AddVBS(" end if ");

    AddVBS(" if MyWord.Selection.Tables.Count >0 Then");
    AddVBS("if ( MyWord.Selection.Tables(1).Rows.Count >="+IntToStr( aRow )+")  and (MyWord.Selection.Tables(1).Columns.Count >="+IntToStr( aCol )+") then ");
    AddVBS(" MyWord.Selection.Tables(1).Cell("+IntToStr( aRow )+","+IntToStr(aCol)+").Select");
    AddVBS(" MyWord.Selection.Range.Text = \"\"");
    AddVBS(" end if ");
    AddVBS(" end if ");
    EndVBS();   

    TStrings* aStrings = CRLFString2TStrings(aText,"@@");
    InsertTxt(aStrings);
    delete  aStrings;
}

void  MWordFun::Add_a_RowInTable(String aTableBM)
{
    if( aTableBM == "" || HasBM(aTableBM) == false )  return;

    InitVBS( );
    AddVBS(" if MyWord.ActiveDocument.Bookmarks.Exists(\""+aTableBM+"\") = True Then ");    //选中
    AddVBS(" MyWord.Selection.GoTo -1,,,\""+aTableBM+"\"");
    AddVBS(" end if ");
    AddVBS("  MyWord.Selection.Tables(1).Rows.Add");
    EndVBS();
}

void  MWordFun::NewLine()
{
    InitVBS( );
    AddVBS ("MyWord.Selection.TypeParagraph ");
    EndVBS();
}

void MWordFun::DelSel()
{
   InitVBS();
   AddVBS(" MyWord.Selection.Delete");
   EndVBS();
}

//-------------------- InsertPic -----------------------------------------------

void MWordFun::UpdatePic( String aPicFName,String aBMName )
{
  if( FileExists( aPicFName )==false || aBMName =="" )
              return;
  if( HasBM( aBMName )==false )
      return;

  int aSP=-1,aEP=-1;
  GetBMRange( aBMName,aSP,aEP);
  SelRange(aSP,aSP);

  InsertPic( aPicFName );

  int aPos = GetCurPos();
  SelRange(aPos,aPos+aEP-aSP);
  DelSel();
}

void  MWordFun::UpdateTitle(String  aTitle,String aBMName)
{
   if( HasBM( aBMName )==false )
      return;

   int aSP=-1,aEP=-1;
   GetBMRange( aBMName,aSP,aEP);
   SelRange(aSP,aSP);

   InsertFiledTitle(aTitle );

   int aPos = GetCurPos();
   SelRange(aPos,aPos+aEP-aSP);
   DelSel();
}

void MWordFun::ReplaceContentStr( String aOldStr,String aNewStr)
{
    InitVBS();
    AddVBS(" MyWord.Selection.Find.ClearFormatting ");
    AddVBS(" MyWord.Selection.Find.Replacement.ClearFormatting  ");
    AddVBS("  With MyWord.Selection.Find ");
    AddVBS("     .Text = \""+aOldStr+"\"");
    AddVBS("     .Replacement.Text = \""+aNewStr+"\"");
    AddVBS("     .Forward = True ");
    AddVBS("     .Wrap = 1");
    AddVBS("     .Format = False");
    AddVBS("     .MatchCase = False");
    AddVBS("     .MatchWholeWord = False ");
    AddVBS("     .MatchByte = True ");
    AddVBS("     .MatchWildcards = False  ");
    AddVBS("     .MatchSoundsLike = False");
    AddVBS("     .MatchAllWordForms = False ");
    AddVBS(" End With ");
    AddVBS(" MyWord.Selection.Find.Execute  , , , , , , , , , , 2");
    EndVBS();
}

//给定aBMName，把aPicFName文件的图片贴到aBMName所在位置
/*void MWordFun::InsertPic( String aPicFName, String aBMName )
{
  if( aBMName=="" )
    return;

  int aSP=-1,aEP=-1;
  GetBMRange( aBMName,aSP,aEP );
  InsertPic( aPicFName,aSP,aEP );
} */

void MWordFun::InsertPic( String aPicFName )
{
  InsertPic(  aPicFName,-1 );
}


//图4.示意图 ( 图为aSubTitle，.示意图为aTitle，若 aSubTitle为空则不插入标题）
void MWordFun::InsertPicNewBm( String aPicFName, String aBMName,
                                   String aSubTitle ,String aTitle )
{
     InsertPic( aPicFName,-1,-1,aBMName,aSubTitle,aTitle );
}

void  MWordFun::InsertPicTitle( String aTitle  ,String aSubTitle )
{
   InitVBS( );
   AddVBS ("MyWord.Selection.TypeParagraph ");
   AddVBS ("MyWord.CaptionLabels.Add  "+AnsiQuotedStr(aSubTitle,'\"') );
   AddVBS (" MyWord.Selection.InsertCaption  "+AnsiQuotedStr(aSubTitle,'\"')+","+AnsiQuotedStr(aTitle,'\"')+"  ,\"\" , 1");
   AddVBS (" MyWord.Selection.ParagraphFormat.Alignment = 1");
   AddVBS ("MyWord.Selection.TypeParagraph ");
   EndVBS();
}

void  MWordFun::InsertTableTitle( String aTitle  ,String aSubTitle )
{
   InitVBS( );
   //AddVBS ("MyWord.Selection.TypeParagraph ");
   AddVBS ("MyWord.CaptionLabels.Add  "+AnsiQuotedStr(aSubTitle,'\"') );
   AddVBS (" MyWord.Selection.InsertCaption  "+AnsiQuotedStr(aSubTitle,'\"')+","+AnsiQuotedStr(aTitle,'\"')+"  ,\"\" , 1");
   AddVBS (" MyWord.Selection.ParagraphFormat.Alignment = 1");
   //AddVBS ("MyWord.Selection.TypeParagraph ");
   EndVBS();
}


// bOnly = true: 只处理 Title， 不考虑具体的位置
void  MWordFun::InsertPicTitle( String aTitle  ,String aSubTitle , bool bOnly )
{
   if(bOnly)
   {
       InitVBS( );
       AddVBS ("MyWord.CaptionLabels.Add  "+AnsiQuotedStr(aSubTitle,'\"') );
       AddVBS (" MyWord.Selection.InsertCaption  "+AnsiQuotedStr(aSubTitle,'\"')+","+AnsiQuotedStr(aTitle,'\"')+"  ,\"\" , 1");
       AddVBS (" MyWord.Selection.ParagraphFormat.Alignment = 1");
       EndVBS();
   }
   else
       InsertPicTitle(aTitle,aSubTitle);
}

/*void  MWordFun::InsertPicTitle( String aTitle  ,String aSubTitle)
{
   InitVBS( );
   AddVBS ("MyWord.Selection.TypeParagraph ");
   AddVBS ("MyWord.CaptionLabels.Add  "+AnsiQuotedStr(aSubTitle,'\"') );

   //2003
   //AddVBS (" MyWord.Selection.InsertCaption  "+AnsiQuotedStr(aSubTitle,'\"')+","+AnsiQuotedStr(aTitle,'\"')+"  ,\"\" , 1, 0");
   //2000
   AddVBS (" MyWord.Selection.InsertCaption  " + AnsiQuotedStr(aSubTitle,'\"') + "," + AnsiQuotedStr(aTitle,'\"') + "  ,\"\" , 1");

   AddVBS (" MyWord.Selection.ParagraphFormat.Alignment = 1");
   AddVBS ("MyWord.Selection.TypeParagraph ");
   EndVBS();


   //    Selection.InsertCaption Label:="图", TitleAutoText:="InsertCaption1", Title _
   //     :="", Position:=wdCaptionPositionBelow
}*/

void MWordFun::InsertPic( String aPicFName,int aPos,int aEndPos,String aNewBm,
                           String aTitle, String aSubTitle )
{
   if(! FileExists(aPicFName) )
      throw Exception( "要插入的图片文件"+aPicFName+"不存在！");
      
   int aStPos =  GetCurPos() ;
   InitVBS();
   int aE  = aEndPos;
   if (aEndPos  < 0) aE = aPos;
   if ( aPos > 0 )
    AddVBS(" MyWord.Selection.SetRange "+IntToStr( aPos )+","+IntToStr( aE ));

   AddVBS(" MyWord.Selection.InlineShapes.AddPicture \""+aPicFName+"\",False,True");
  // if( aNewBm !="" )
   //AddVBS ("MyWord.Selection.MoveRight 1,1, 1 ");
   AddVBS (" MyWord.Selection.ParagraphFormat.Alignment = 1");
   EndVBS();
 
   if( aSubTitle !="")
   {
     InsertPicTitle( aTitle,aSubTitle  );
   }
    int bPos = GetCurPos() ;
      //创建BM
   if( aNewBm !="" )
   {
      AddBMByPos( aNewBm,aStPos,bPos );
      SelMoveRight();
   }
}

//例子：

void MWordFun::InsertPics( TStrings* aPicNames  )
{
  if( aPicNames ==NULL )
    return;

  TStrings * aBMNames;
  aBMNames = GetBookmarkTrueNames("");

  for( int i=0; i<aPicNames->Count; i++ )
  {
    try
    {
      String aStr = aPicNames->Strings[i];

      String aName;
      String aFileName;

      SplitStrTo2Str( aStr, "=", aName, aFileName );

      InsertPic_Group( aBMNames, aFileName, aName );
    }
    catch( Exception& e )
    {
      gError->Warn( "InsertPics出错！"+e.Message );
    }
  }

  delete aBMNames;
}

//功能：找到aBMNames中为 XX, XX_1, XX_2 ...的图片，全部用aPicFName替换
void MWordFun::InsertPic_Group( TStrings* aBMNames, String aPicFName,String aName )
{
  // XX_1, XX_2...的匹配
  TStrings* aMatchBMs = FindAllStrStrings_Prev( aBMNames, aName + "_" );

  // 全名称匹配
  if( IsIn( aName, aBMNames ) )
    aMatchBMs->Add( aName );

  for( int i=0; i<aMatchBMs->Count; i++ )
    InsertPic( aPicFName, aMatchBMs->Strings[i] );

  delete aMatchBMs;
}

/*void MWordFun::InsertPic( String aPicFName,int aPos,int aEndPos )
{
   if(! FileExists(aPicFName) )
   {
     gError->Warn( "文件(" +aPicFName + " )不存在!" );
     return;
   }

   InitVBS();

   int aE = aEndPos;
   if ( aEndPos  < 0 )
     aE = aPos;

   if ( aPos > 0 )
    AddVBS(" MyWord.Selection.SetRange "+IntToStr( aPos )+","+IntToStr( aE ));

   AddVBS(" MyWord.Selection.InlineShapes.AddPicture \""+aPicFName+"\",False,True");
   EndVBS();
} */


void MWordFun::SelMoveRight()
{
   SelMoveRight(1) ;
}

void MWordFun::SelMoveRight(int aCount)
{
    InitVBS( );
    AddVBS ("MyWord.Selection.MoveRight 1, " + IntToStr(aCount) + ", 1 ");
    EndVBS();
}

/*
Sub Macro1()
'
' Macro1 Macro
' 宏在 2015-7-28 由 微软用户 录制
'
    Selection.WholeStory
    Selection.Delete Unit:=wdCharacter, Count:=1
End Sub
*/

void  MWordFun::ClearDoc()
{
    InitVBS( );
    AddVBS("MyWord.Selection.WholeStory");
    AddVBS("MyWord.Selection.Delete");
    EndVBS();
}


//插入 图片(aPicName) + BookMark(aBMName)
void MWordFun::InsertPicNewBm( String aPicFName,String aBMName )
{
     InsertPic(  aPicFName,aBMName,-1,-1 );
}

void MWordFun::InsertPic( String aPicFName, String aNewBm, int aPos, int aEndPos )
{
   if( FileExists(aPicFName)==false )
   {
     gError->Warn( "文件(" +aPicFName + " )不存在!" );
     return;
   }

   InitVBS();
   int aE  = aEndPos;

   if ( aEndPos  < 0)
     aE = aPos;

   if ( aPos > 0 )
    AddVBS(" MyWord.Selection.SetRange "+IntToStr( aPos )+","+IntToStr( aE ));
   AddVBS(" MyWord.Selection.InlineShapes.AddPicture \""+aPicFName+"\",False,True");

   if( aNewBm !="" )
     AddVBS ("MyWord.Selection.MoveLeft 1,1, 1 ");

   EndVBS();

   if( aNewBm !="" )
   {
      AddBMBySel(aNewBm);
      SelMoveRight();
   }
}
//---------------------------------------------------------------------------
//参数：aPicFName -- 图片文件名称   aNewBm--创建的BookMark名称，""则不添加
//      aTitle -- 题注名称  aSubTitle -- "图"、"图表" ...
//      [ aPos, aEndPos ] -- 图片的放置位置
//---------------------------------------------------------------------------

void MWordFun::InsertPicNewBm( String aPicFName, String aNewBm, String aTitle,
                                 String aSubTitle, int aPos, int aEndPos  )

{
   if(! FileExists(aPicFName) )
   {
     gError->Warn( "文件(" +aPicFName + " )不存在!" );
     return;
   }

   //-----插入图片,并选择----
   InitVBS();

   int aE = aEndPos;
   if (aEndPos  < 0)
     aE = aPos;
   if ( aPos > 0 )
    AddVBS(" MyWord.Selection.SetRange "+IntToStr( aPos )+","+IntToStr( aE ));

   AddVBS(" MyWord.Selection.InlineShapes.AddPicture \""+aPicFName+"\",False,True");
   if( aNewBm !="" )
     AddVBS ("MyWord.Selection.MoveLeft 1,1, 1 ");

   EndVBS();

   //-----插入BookMark----
   if( aNewBm !="" )
   {
      AddBMBySel(aNewBm);
      SelMoveRight();
   }

   //-----插入题注---------
   
   if( aSubTitle !="")
     InsertPicTitle( aTitle,aSubTitle  );
}


//---------------------------------------------------------------------------
//参数：aPicFName -- 图片文件名称   aNewBm--创建的BookMark名称，""则不添加
//      aTitle -- 题注名称  aSubTitle -- "图"、"图表" ...
//      [ aPos, aEndPos ] -- 图片的放置位置
//---------------------------------------------------------------------------
void MWordFun::InsertTextNewBM( String aStr, String aNewBm, int aPos, int aEndPos  )
{

   //-----插入图片,并选择----
   InitVBS();

   int aE = aEndPos;
   if (aEndPos<0)
     aE = aPos;
     
   if ( aPos > 0 )
    AddVBS(" MyWord.Selection.SetRange "+IntToStr( aPos )+","+IntToStr( aE ));

   AddVBS(" MyWord.Selection.TypeText \""+aStr+"\"");
   if( aNewBm !="" )
     AddVBS ("MyWord.Selection.MoveLeft 1, " + IntToStr(aStr.Length()) + ", 1 " );

   EndVBS();

   //-----插入BookMark----
   if( aNewBm !="" )
   {
      AddBMBySel(aNewBm);
      SelMoveRight( aStr.Length() );
  }
}


void MWordFun::InsertFiledTitleNewBM( String aStr, String aNewBm, int aPos, int aEndPos )
{
   InitVBS();
   
   int aE = aEndPos;
   if (aEndPos<0)
     aE = aPos;
     
   if ( aPos > 0 )
    AddVBS(" MyWord.Selection.SetRange "+IntToStr( aPos )+","+IntToStr( aE ));

   AddVBS(" MyWord.Selection.Fields.Add MyWord.Selection.Range, -1,"+
                            AnsiQuotedStr(  "TITLE  "+aStr ,'""')+", True");
   if( aNewBm !="" )
     AddVBS ("MyWord.Selection.MoveLeft 1, " + IntToStr(aStr.Length()) + ", 1 " );

   EndVBS();

   //-----插入BookMark----
   if( aNewBm !="" )
   {
      AddBMBySel(aNewBm);
      SelMoveRight( aStr.Length() );
  }
}

void MWordFun::InsertFiledTitle( String aTitle )
{
   InitVBS();
   AddVBS(" MyWord.Selection.Fields.Add MyWord.Selection.Range, -1,"+
                             AnsiQuotedStr(  "TITLE  "+aTitle ,'""')+", True");
   EndVBS( );
}


//------------------------------------------------------------------------------
//  aTabStr表格内容  以默认的逗号作为分隔符，aBMName 插入位置的书签名
//  aTabStr.Strings[0] 为为表头数据,其它字符时表格内容，数据以"，"分割
//  eg: aTabStr.Strings[0] = "a,b,c"
//  aTabStr.Strings[1] = "11,12,13"
//  aTabStr.Strings[2] = "21,22,23"
//  得到表格 | a  | b  | c  |
//           | 11 | 12 | 13 |
//           | 21 | 22 | 23 |
//------------------------------------------------------------------------------

void MWordFun::InsertTables( TStrings* aTables )
{
  if( aTables ==NULL )
    return;

  TStrings * aBMNames = GetBookmarkTrueNames("");

  for( int i=0; i<aTables->Count; i++ )
  {
    try
    {
      String aStr = aTables->Strings[i];

      String aName;
      String aTableValue;

      SplitStrTo2Str( aStr, "=", aName, aTableValue );
      InsertTable_Group( aBMNames, aTableValue, "//", ";", aName );
    }
    catch( Exception& e )
    {
      gError->Warn( "InsertPics出错！"+e.Message );
    }
  }

  delete aBMNames;
}

void MWordFun::InsertTable_Group( TStrings* aBMNames, String aTableStr, String aSpRecs, String aSpFields, String aName )
{
  // XX_1, XX_2...的匹配
  TStrings* aMatchBMs = FindAllStrStrings_Prev( aBMNames, aName + "_" );

  // 全名称匹配
  if( IsIn( aName, aBMNames ) )
    aMatchBMs->Add( aName );

  for( int i=0; i<aMatchBMs->Count; i++ )
    InsertTable( aTableStr, aSpRecs, aSpFields, aMatchBMs->Strings[i] );

  delete aMatchBMs;
}

void MWordFun::InsertTable( String aTableStr, String aSpRecs, String aSpFields, String aBMName )
{
  TStringGrid* aGrid = new TStringGrid((void*)NULL);
  StrToGrid( aTableStr, aSpRecs, aSpFields, aGrid );
  InsertTable( aGrid,aBMName );
  delete aGrid;
}

void MWordFun::InsertTable( TStringGrid * aGrid,String aBMName )
{
  if( aBMName=="" || aGrid->RowCount<=0 || aGrid->ColCount<=0 )
    return;

  int aSP=-1,aEP=-1;
  GetBMRange( aBMName,aSP,aEP );

  if( aSP<0 )
  {
    gError->Warn( "标签(" + aBMName + ")不存在!" );
    return;
  }

  InsertTable( aGrid,aSP,aEP );
}


void MWordFun::InsertTable( TStrings * aTableStr, String aSpField, String aBMName)
{
  TStringGrid* aGrid = new TStringGrid((void*)NULL);
  StringsToGrid( aTableStr, aGrid, aSpField );
  InsertTable( aGrid,aBMName );
  delete aGrid;
}

//  if( aTabStr == NULL || aTabStr->Count<=0 )
//    return ;

//  //解析表的行和列数据
//  int  aRow = aTabStr->Count ;

//  TStrings * aColumStrs = new TStringList();

//  aColumStrs->DelimitedText = aTabStr->Strings[0];  //表头


void MWordFun::InsertTable( TStringGrid * aGrid, int aPos,int aEndPos )
{

  if( aGrid==NULL )
    return;

  int aRow = aGrid->RowCount;
  int aCol = aGrid->ColCount;
  int aE  = aEndPos;
  if ( aEndPos<0 )
    aE = aPos;

  InitVBS();
  if ( aPos > 0 )
    AddVBS(" MyWord.Selection.SetRange "+IntToStr( aPos )+","+IntToStr( aE ));

  AddVBS(" MyWord.Selection.Tables.Add MyWord.Selection.Range,"+IntToStr(aRow)+","+IntToStr(aCol));
  for (int i=1; i<=aRow;i++)
  {
    //aColumStrs->DelimitedText = aTabStr->Strings[i-1];
    for (int j=1; j<=aCol; j++ )    //单元格赋值
    {
      String aStr = aGrid->Cells[j-1][i-1];   //aColumStrs->Strings[j-1];
      AddVBS(" MyWord.Selection.Tables(1).Cell("+IntToStr(i)+","+IntToStr(j)+").Select");
      AddVBS(" MyWord.Selection.Range.Text = \""+aStr+"\"");
    }
  }

  //设置表格属性
  AddVBS(" With MyWord.Selection.Tables(1)" );
  AddVBS(" .Style = \"网格型\" " );
  AddVBS(" .ApplyStyleHeadingRows = True " );
  AddVBS(" .ApplyStyleLastRow = True   " );
  AddVBS(" .ApplyStyleFirstColumn = True " );
  AddVBS(" .ApplyStyleLastColumn = True " );
  AddVBS("  End With  " );

  //delete aColumStrs;
  EndVBS();
}

/*void MWordFun::InsertTab( TStrings * aTabStr,int aPos,int aEndPos)
{

  if( aTabStr == NULL || aTabStr->Count<=0 )
    return ;

  //解析表的行和列数据
  int  aRow = aTabStr->Count ;

  TStrings * aColumStrs = new TStringList();

  aColumStrs->DelimitedText = aTabStr->Strings[0];  //表头

  int aCol = aColumStrs->Count;
  int aE  = aEndPos;
  if (aEndPos  < 0)
    aE = aPos;

  InitVBS();
  if ( aPos > 0 )
    AddVBS(" MyWord.Selection.SetRange "+IntToStr( aPos )+","+IntToStr( aE ));

  AddVBS(" MyWord.Selection.Tables.Add MyWord.Selection.Range,"+IntToStr(aRow)+","+IntToStr(aCol));
  for (int i =1; i<=aRow;i++)
  {
    aColumStrs->DelimitedText = aTabStr->Strings[i-1];
    for (int j=1; j<=aColumStrs->Count ;j++)    //单元格赋值
    {
      String aStr =  aColumStrs->Strings[j-1];
      AddVBS(" MyWord.Selection.Tables(1).Cell("+IntToStr(i)+","+IntToStr(j)+").Select");
      AddVBS(" MyWord.Selection.Range.Text = \""+aStr+"\"");
    }
  }

  //设置表格属性

  AddVBS(" With MyWord.Selection.Tables(1)" );
  AddVBS(" .Style = \"网格型\" " );
  AddVBS(" .ApplyStyleHeadingRows = True " );
  AddVBS(" .ApplyStyleLastRow = True   " );
  AddVBS(" .ApplyStyleFirstColumn = True " );
  AddVBS(" .ApplyStyleLastColumn = True " );
  AddVBS("  End With  " );

  delete aColumStrs;
  EndVBS();
}*/




//---------------------------------------------------------------------------
/*void MWordFun::CreateWordFile(  String aDotFileName ,String aFileName,TStrings* aKeyValue,bool IsQuit)
{

   if( FileExists( aDotFileName ) == false )
	 throw Exception("模板文件"+aDotFileName+"不存在！");

   InitVBS();

   AddVBS(" Set NewDoc = Nothing ");
   AddVBS(" Set NewDoc = MyWord.Documents.Add(\""+aDotFileName+"\")");

   if( aKeyValue  && aKeyValue->Count > 0 )
   {
             for (int i = 0; i < aKeyValue->Count; i++)
                   ReplaceBookMark(VBS,"NewDoc", aKeyValue->Names[i],aKeyValue->Values[ aKeyValue->Names[i]]);
             //ReplaceBookMark(TStrings * aPortValList )//当前文档书签赋值（多对一的关系）
   }

   if( aFileName != "" )// 不保存
     AddVBS(" NewDoc.SaveAs  \""+aFileName+"\"" );

   if( IsQuit )
     AddVBS(" MyWord.Quit" );

   EndVBS();
} */

//------------------------------------------------------------------------------
//功能：查找aDocName中的aBMName标签，并修改其内容
//------------------------------------------------------------------------------

void MWordFun::ReplaceBookMark( TStrings * aVBS,String aDocName,String aBMName,String aValue)
{
   if( aVBS == NULL )
     return;

   aVBS->Add(" if " +aDocName+ ".Bookmarks.Exists(\""+aBMName+"\") = True Then ");
   aVBS->Add(" Set aBM = "+aDocName+ ".Bookmarks(\""+aBMName+"\") " );
   aVBS->Add(" Set aRange = aBM.Range" );
   aVBS->Add(" aRange.Text = \""+ aValue+"\"" );   //书签内容修改后，书签丢失
   aVBS->Add(" aRange.Bookmarks.Add \""+aBMName+"\"");//保留原有书签位置
   aVBS->Add(" end if ");
}

//------------------------------------------------------------------------------
//当前文档书签赋值（多对一的关系）
//参数：[ aParaValueNameAndValues -- "AA=1\nBB=2" ]
//------------------------------------------------------------------------------

void MWordFun::ReplaceBookMark( TStrings * aParaValueNameAndValues, String aFileName )
{
  if( aParaValueNameAndValues == NULL )
     return;

  TStrings* aNames = new TStringList;
  TStrings* aValues = new TStringList;

  for( int i=0; i<aParaValueNameAndValues->Count; i++ )
  {
    try
    {
      String aName,aValue;
      SplitStrTo2Str( aParaValueNameAndValues->Strings[i], "=", aName,aValue ) ;
      aNames->Add( aName );
      aValues->Add( aValue );
    }
    catch( Exception& e )
    {
      gError->Warn( "MWordFun::ReplaceBookMark出错!" + e.Message );
    }
  }

  ReplaceBookMark(  aNames, aValues, aFileName );
  delete aNames;
  delete aValues;
}

//------------------------------------------------------------------------------
//参数：[ aNames -- 标签名称 ]
//      [ aValues -- 值名称 ]
//      [ aFileName -- 文档名称, ""为当前打开文档 ]
//------------------------------------------------------------------------------

void MWordFun::ReplaceBookMark( TStrings * aNames, TStrings* aValues, String aFileName  )
{

   //获得标签集合
   TStrings * aBMNames = GetBookmarkTrueNames(aFileName);

   InitVBS();

   //打开文件
   AddVBS(" Set NewDoc = Nothing ");
   if ( aFileName == "" )
   {
    AddVBS(" Set NewDoc = MyWord.ActiveDocument");    //
   }
   else
   {
     if( FileExists( aFileName ) == false )
       throw Exception( aFileName+" 文件不存在！");
     AddVBS(" Set NewDoc =  MyWord.Documents.Open(\""+aFileName+"\")");
   }

   int aCount = Math::Min(aNames->Count,aValues->Count);
   G_Progress->BgnShow1("Word标签替换",0,aCount-1);
   
   for (int i=0; i<aCount; i++)
   {
     try
     {
         G_Progress->Show1( "查找匹配字符!", i );

         //搜索参数aName
	 String aName = aNames->Strings[i];
         //if(  aName == "组_3511高温" )
         //  aName = "组_3511高温";

         // XX_1, XX_2...的匹配
         TStrings* aMatchBMs = FindAllStrStrings_Prev( aBMNames, aName + "_" );

         // 全名称匹配
         if( IsIn( aName, aBMNames ) )
           aMatchBMs->Add( aName );

         for( int j=0; j<aMatchBMs->Count; j++ )
           ReplaceBookMark( VBS, "NewDoc", aMatchBMs->Strings[ j ], aValues->Strings [i] );

         delete aMatchBMs;
     }
     catch( Exception& e )
     {
     }

   }

   G_Progress->EndShow1();

   /*for (int i=0; i<aBMNames->Count; i++)
   {

     try
     {
	 String aBM = aBMNames->Names[i];

	 String aPortName = GetPortNameByBmName( aBM );

	 if( aPortName.Pos(C_BMLab)>0 )
   	   aPortName = aPortName.SubString( C_BMLab.Length()+1,aPortName.Length() );

	 if( aParaValueNameAndValues->IndexOfName(aPortName) < 0 )
           continue;

	 ReplaceBookMark( VBS, "NewDoc",aBM,aParaValueNameAndValues->Values[aPortName] );
     }
     catch( Exception& e )
     {
     }

   }*/

   //AddVBS(" NewDoc.Save");
   EndVBS();

   delete aBMNames;
}

//---------------------------------------------------------------------------
//功能：打开模板文件（aDotFileName），并生成新的文件 （aFileName ）
//---------------------------------------------------------------------------
void MWordFun::CreateWordFileByTemplate(  String aDotFileName ,String aFileName, bool IsQuit )
{
  CopyFileAlways( aDotFileName, aFileName );

  // if( FileExists( aDotFileName ) == false )
  //	 throw Exception("模板文件"+aDotFileName+"不存在！");

  Open(aFileName);

   if( IsQuit )
      this->CloseActiveDoc();
}

void MWordFun::Open_NoExp(  String aFileName, bool IsShowError )
{
  try
  {
     Open(  aFileName );
  }
  catch( Exception& e )
  {
    if( IsShowError==true )
      gError->Warn( "WordFun::Open_NoExp!" + e.Message );
  }
}

void MWordFun::Open(  String aFileName )
{
    FFileName = aFileName;

    InitVBS();
    AddVBS(" MyWord.Documents.Open(\""+aFileName+"\")");
    EndVBS();
}



//---------------------------------------------------------------------------
//功能：打开模板文件（aDotFileName），用aPortValue规定的字符串替换标签，并生成新的文件 （aFileName ）
//参数：[ aPortValue的格式
//        "天线俯仰工作范围=111112222"
//        "AA=你好"
//        "BB=西安电子科技大学 ]
//---------------------------------------------------------------------------

void MWordFun::CreateWordFileByTemplateAndReplaceBookMarks(  String aDotFileName ,String aFileName,TStrings* aPortValue,bool IsQuit )
{
    CreateWordFileByTemplate(aDotFileName,aFileName,IsQuit);
    ReplaceBookMark( aPortValue,aFileName );
}

//生成临时文件名称
//String MWordFun::GetTmpFileName()
//{

//}

void MWordFun::GetBMRange(String aBMName,int &aStartPos,int &aEndPos ,String aFileName )
{
  InitVBS(false);
  AddVBS(" Set NewDoc = Nothing ");

  if ( aFileName == "" )
  {
   AddVBS(" Set NewDoc = MyWord.ActiveDocument");    //
  }
  else
  {
    if( FileExists( aFileName ) == false ) throw Exception( aFileName+" 文件不存在！");
       AddVBS(" Set NewDoc =  MyWord.Documents.Open(\""+aFileName+"\")");
  }

  AddVBS(" if NewDoc.Bookmarks.Exists(\""+aBMName+"\") = True Then ");
  AddVBS(" Set aBM = NewDoc.Bookmarks(\""+aBMName+"\") " );
  AddVBS(" main = CStr( aBm.Range.Start)&\";\"&CStr(aBm.Range.End)  ");
  AddVBS(" end if ");
  EndVBS(false);

  String aRange = EvalScript(VBS );

  String aX,aY;
  SplitStrTo2Str( aRange,";",aX,aY );
  aStartPos = StrToIntDef( aX,-1);
  aEndPos = StrToIntDef( aY,-1);
}

TStrings * MWordFun::GetBookmarkTrueNames(String aFileName  )
{
  TStrings* aTrueNames=new TStringList;
  
  TStrings* aStrings = GetBookmarkNames(aFileName);
  for( int i=0; i<aStrings->Count; i++ )
    aTrueNames->Add( aStrings->Names[i] );

  delete aStrings;
  return aTrueNames;  
}

TStrings * MWordFun::GetBookmarkNames(String aFileName  )
{
	InitVBS(false);

	AddVBS(" Set NewDoc = Nothing ");
	if ( aFileName == "" )
        {
	 AddVBS(" Set NewDoc = MyWord.ActiveDocument");    //
	}
        else
	{
          if( FileExists( aFileName ) == false ) throw Exception( aFileName+" 文件不存在！");
	     AddVBS(" Set NewDoc =  MyWord.Documents.Open(\""+aFileName+"\")");
	}

	AddVBS(" Set BMs = NewDoc.Bookmarks  ");
	AddVBS(" For i = 1 To BMs.Count  ");
	AddVBS(" Set aBm = BMs.Item(i)  ");
	AddVBS(" aStr = aBm.Name  ");

	AddVBS(" names = CStr(aStr) & \"=\"&CStr( aBm.Range.Start)&\";\"&CStr(aBm.Range.End)&\",\" & CStr(names)  ");
	AddVBS(" Next  ");
	AddVBS(" main = names  ");
	EndVBS(false);
	String aNames = EvalScript(VBS );
	return splitToStrings(aNames,",");
}

void MWordFun::AddBM( String aBMName )
{
  if ( aBMName == "" )
     return;

  InitVBS();
  AddVBS(" Set NewDoc = MyWord.ActiveDocument");
  AddVBS(" NewDoc.Bookmarks.Add \""+aBMName +"\",MyWord.Selection.Range ");
  EndVBS();
}

String MWordFun::GetBookMark( String aName )
{
   //IsDebug=true;
   
    InitVBS(false);

    AddVBS(" Set NewDoc = MyWord.ActiveDocument");

    AddVBS(" aName = \"" + aName + "\"" );
    AddVBS(" if NewDoc.Bookmarks.Exists(\"aName\") = True Then ");

    AddVBS(" aBgn = NewDoc.Bookmarks(\"aName\").Range.Start");
    AddVBS(" aEnd = NewDoc.Bookmarks(\"aName\").Range.end");

    AddVBS(" main = aName + \"=\" + aBgn + \";\" + aEnd " );
    AddVBS(" exit function");
    AddVBS(" end if");


    AddVBS(" main = aName ");
    EndVBS(false);

    //fVBS->SaveToFile( "c:\\xx.vbs" );
    String aR = EvalScript(VBS );
    return aR;
}

String MWordFun::MaskAddBM( String aBMName,   String aSp )
{
  if( aBMName=="" )
    return "";

  String aName = MaskGetBMName( aBMName, aSp );
  AddBM( aName );
  return aName;
}

String MWordFun::MaskGetBMName( String aBMName,   String aSp )
{
  if( aBMName=="" )
    return "";

  String aName = aBMName;
  int i=0;
  for( ;; )
  {
    if(  HasBM( aName ) == false )
      break;
    i=i+1;
    aName = aBMName + aSp + IntToStr(i);
  }
  return aName;
}

void MWordFun::SetBMRangeBySel( String aName )
{
   if( HasBM (aName) == false )
     throw Exception( "标签(" +aName+ ")不存在!");

   //IsDebug=true;
   InitVBS();
   AddVBS(" Set NewDoc = MyWord.ActiveDocument");
   AddVBS(" NewDoc.Bookmarks(\"" + aName +"\").Range.Start=MyWord.Selection.Range.Start ");
   AddVBS(" NewDoc.Bookmarks(\"" + aName +"\").Range.end=MyWord.Selection.Range.end ");
   EndVBS();
}


//功能：在当前文档所选位置添加aBMName的书签
//参数：[返回：BookMark]

String MWordFun::AddBMBySel( String aBMName )
{
  String  aStr = GetBMNameBySel();
  if( aStr !="" )
    DelBM( aStr );

  InitVBS(false);
  AddVBS( " Set NewDoc = Nothing " );
  if ( aBMName == "" )
    return "-1,-1";

  AddVBS(" Set NewDoc = MyWord.ActiveDocument");
  AddVBS(" if MyWord.Selection.Range.Start = MyWord.Selection.Range.End then");
  AddVBS(" MsgBox \"没有选择范围，无法完成映射!\"");
  AddVBS(" main = \"-1,-1\"");
  AddVBS(" exit function");
  AddVBS(" end if");
  AddVBS(" NewDoc.Bookmarks.Add \""+aBMName +"\",MyWord.Selection.Range ");
  InitBM( );
  AddVBS(" main = Cstr(MyWord.Selection.Range.Start)&\",\"&Cstr(MyWord.Selection.Range.End)");
  EndVBS(false);
  String aR = EvalScript(VBS );
  return aR;
}

//功能：返回Range所在位置的BMName

String MWordFun::GetBMNameOfCursor()
{
    InitVBS(false);
    AddVBS(" Set BMs = MyWord.ActiveDocument.Bookmarks ");
    AddVBS(" For i = 1 To BMs.Count ");
    AddVBS("    Set aBM = BMs.Item(i) ");
    AddVBS("    If (aBM.Range.Start = MyWord.Selection.Range.Start) And (MyWord.Selection.Range.End = aBM.Range.End) Then ");
    AddVBS("     	main = aBM.Name ");
    AddVBS("	    Exit Function  ");
    AddVBS("     End If ");
    //AddVBS("    If (MyWord.Selection.Range.Start >= aBM.Range.Start  ) And (MyWord.Selection.Range.End <= aBM.Range.End) Then ");
    AddVBS("    If (MyWord.Selection.Range.Start >= aBM.Range.Start  ) And (MyWord.Selection.Range.End < aBM.Range.End) Then ");
    AddVBS("     	main = aBM.Name ");
    AddVBS("	    Exit Function  ");
    AddVBS("     End If ");
    AddVBS("  Next ");
    AddVBS(" main = \"\" ");
    EndVBS(false );
    String aName = EvalScript(VBS );
    return aName;
}


//功能：返回光标所在位置的BMName

String MWordFun::GetBMNameBySel()
{
    InitVBS(false);

    AddVBS(" Set BMs = MyWord.ActiveDocument.Bookmarks ");
    AddVBS(" For i = 1 To BMs.Count ");
    AddVBS("    Set aBM = BMs.Item(i) ");
    AddVBS("    If (aBM.Range.Start = MyWord.Selection.Range.Start) And (MyWord.Selection.Range.End = aBM.Range.End) Then ");
    AddVBS("     	main = aBM.Name ");
    AddVBS("	    Exit Function  ");
    AddVBS("     End If ");
    AddVBS("  Next ");
    AddVBS(" main = \"\" ");
    EndVBS(false );
    String aName = EvalScript(VBS );

    return aName;
}

void MWordFun::InitBM()
{
	AddVBS( " With MyWord.ActiveDocument.Bookmarks " );
	AddVBS( "    .DefaultSorting = wdSortByName" );
	AddVBS( " .ShowHidden = False" );
	AddVBS( " End With" );
}


void MWordFun::SelRange( int aStartPos,int aEndPos )
{
  if( aStartPos<0 && aEndPos<0 )
     UnSelRange();
     
  InitVBS();
  AddVBS(" MyWord.ActiveDocument.Range("+IntToStr( aStartPos )+","+
                                          IntToStr( aEndPos )+").Select ");
  EndVBS( );
}

void MWordFun::UnSelRange()
{
  MoveDown();
}

void MWordFun::MoveDown()
{
    InitVBS();
    AddVBS ("MyWord.Selection.MoveDown 5, 1 ");
    EndVBS();
}

void MWordFun::GotoBM( String aBMName )
{
   InitVBS();
   AddVBS(" if MyWord.ActiveDocument.Bookmarks.Exists(\""+aBMName+"\") = True Then ");
   AddVBS(" MyWord.Selection.GoTo -1,,,\""+aBMName+"\"");
   AddVBS(" end if ");
   EndVBS( );
}

//---------------GotoBMAndSelRange----------------------------------------------


//功能：定位aName，并选择集合
void MWordFun::GotoBMAndSelRange1( String aName )
{
   GotoBM( aName );
  
  int aBgn, aEnd;
  GetBMRange( aName, aBgn, aEnd );
  if( aBgn<0 || aEnd<0 )
  {
    UnSelRange();
    return;
  }

  SelRange( aBgn, aEnd );
}

//---------------GotoBMAndSelRange----------------------------------------------

void BookMarkToNameAndRange( String aBookMark, String& aName,
                                        int& aBgn, int& aEnd )
{
  String aValue,aBgnStr,aEndStr;
  SplitStrTo2Str( aBookMark,"=",aName,aValue );
  SplitStrTo2Str( aValue,";",aBgnStr,aEndStr );

  aBgn = StrToIntDef(aBgnStr,-1);
  aEnd = StrToIntDef(aEndStr,-1);
}

String BookMarkToName( String aBookMark )
{
  String aName;
  int aBgn, aEnd;
  BookMarkToNameAndRange( aBookMark, aName, aBgn, aEnd );
  return aName;
}

//参数：  [ AA=10;15 ]
void MWordFun::GotoBMAndSelRange( String aBookMark )
{
  String aName;
  int aBgn, aEnd;
  BookMarkToNameAndRange( aBookMark , aName, aBgn, aEnd );

  GotoBM( aName );

  if( aBgn<0 || aEnd<0 )
    return;
    
  SelRange( aBgn, aEnd );
}

//--------------------Save------------------------------------------------------

void  MWordFun::Save()
{
  InitVBS();
  AddVBS(" if MyWord.ActiveDocument.Saved = 0 Then  ");
  AddVBS(" MyWord.ActiveDocument.Save ");
  AddVBS(" End If ");
  EndVBS();
}

void  MWordFun::Quit()
{
  try
  {
    InitVBS();
    AddVBS(" MyWord.Quit ");
    EndVBS( );
  }
  catch( Exception& e )
  {
  }
  
  HasWord="";
}

void  MWordFun::Save( String aFileName,bool IsClose )
{
	 InitVBS();
	if( aFileName == "" )
	  AddVBS(" MyWord.ActiveDocument.Save ");
	else
	  AddVBS(" MyWord.ActiveDocument.SaveAs  \""+aFileName+"\"");
	if( IsClose )
	{
	  AddVBS(" if MyWord.Documents.Count = 1 then  ");
	  AddVBS(" MyWord.ActiveDocument.Close ");
	  AddVBS(" MyWord.Quit ");
	  AddVBS(" else");
	  AddVBS(" MyWord.ActiveDocument.Close ");
	  AddVBS(" end if ");
	}
	EndVBS( );
}

void MWordFun::CloseActiveDoc( )
{
   InitVBS();
   //AddVBS(" if MyWord.Documents.Count = 1 then  ");
   //AddVBS(" MyWord.ActiveDocument.Close( nosave )");
   //AddVBS(" MyWord.Quit ");
   //AddVBS(" else");
   AddVBS(" MyWord.ActiveDocument.Close( nosave ) ");
   //AddVBS(" end if ");
   EndVBS( );
}

void MWordFun::CloseAll()
{
   InitVBS();
   AddVBS("  acount = MyWord.Documents.Count ");
   AddVBS(" for i = acount to 1 Step -1");
   AddVBS(" MyWord.Documents.Close ");
   AddVBS(" next ");
   EndVBS();
}

/*void MWordFun::Close(  String aFileName )
{
    InitVBS();
    AddVBS(" MyWord.Documents.Close(\""+aFileName+"\")");
    EndVBS();
}*/

void  MWordFun::Save( String aFileName )
{
   InitVBS();
   String aStr = ReplaceStr(aFileName,"\\","#");

   AddVBS("   For Each aWordDoc In MyWord.Documents ");
   AddVBS(" Dim  str1,aName");
   AddVBS("str1 = aWordDoc.FullName");
   AddVBS("  aName =  Replace( str1,\"\\\", \"#\")");
   AddVBS("    if lcase(aName) = "+
                AnsiQuotedStr(LowerCase( aStr), '""' ) +" then ");
   AddVBS("     aWordDoc.Save");
   AddVBS("     exit sub ");
   AddVBS("    end if ");
   AddVBS("   next ");

   EndVBS( );
 }

void MWordFun::Close_NoExp( String aFileName, bool IsShow )
{
  try
  {
    Close( aFileName );
  }
  catch( Exception& e )
  {
    if( IsShow==true )
      gError->Warn( "MWordFun::Close！" + e.Message );
  }
}

void MWordFun::Close( String aFileName )
{
     InitVBS();
     String aStr = ReplaceStr(aFileName,"\\","#");
     AddVBS("   For Each aWordDoc In MyWord.Documents ");
     AddVBS(" Dim  str1,aName");
     AddVBS("str1 = aWordDoc.FullName");
     AddVBS("  aName =  Replace( str1,\"\\\", \"#\")");

     AddVBS("    if lcase(aName) = "+
                     AnsiQuotedStr(LowerCase( aStr),'""') +" then ");
     AddVBS("     aWordDoc.Close");

     AddVBS("     exit sub ");
     AddVBS("    end if ");
     AddVBS("   next ");
     EndVBS( );
}



String MWordFun::GetActiveDocFileName()
{
   InitVBS(false);
   AddVBS(" main = MyWord.ActiveDocument.FullName  ");
   EndVBS(false );
   String aNames = EvalScript(VBS );
   return aNames;
}

void  MWordFun::NewFile( String aFileName )
{
  if( aFileName == "" ) return;
  InitVBS();
  AddVBS(" Set NewDoc = Nothing ");
  AddVBS(" Set NewDoc = MyWord.Documents.Add( \"Normal\", False, 0,true )");

  AddVBS(" NewDoc.SaveAs  \""+aFileName+"\"" );
  EndVBS( );
  //AddVBS(" NewDoc.SaveAs  \""+aFileName+"\"" );
}

String MWordFun::RotStr( String aSrc )
{
	if( aSrc =="") return "";
	String aStr ="";
	for (int i = aSrc.Length(); i >=1 ; i--) {
	  aStr = aStr+String(aSrc[i]) ;
	}
	return aStr;
}

int MWordFun::LeftPos( String aSrc,String aSub)
{
	int aId = 0;
	if(  aSrc.Pos(aSub) <= 0) return aId;
	int aLPos =  RotStr( aSrc).Pos( RotStr( aSub));
	return aSrc.Length()-(aLPos+aSub.Length()-2);
}

/*String  MWordFun::GetBmVal( String aBMName )
{
   if( aBMName == "" ) return "";
   InitVBS(false);
   AddVBS(" if MyWord.ActiveDocument.Bookmarks.Exists(\""+aBMName+"\") = True Then ");
   AddVBS(" Set aBM = MyWord.ActiveDocument.Bookmarks(\""+aBMName+"\") " );
   AddVBS(" Set aRange = aBM.Range" );
   AddVBS(" main =aRange.Text " );   //书签内容修改后，书签丢失
   AddVBS(" end if " );
   EndVBS( false );
   return EvalScript(VBS );
}*/

String MWordFun::GetPortNameByBmName( String aBMName )
{
  if( aBMName =="")
    return "";

  int aPos = LeftPos( aBMName,"_" );
  if( aPos == 0 )
    aPos = aBMName.Length()+2;
  return  aBMName.SubString( 1,aPos-1 );
}

/*void MWordFun::GetPortValue( String aFileName,TStrings * aPortValues )
{
   if( aFileName == "" || FileExists(aFileName)== false )
     return;
   if( aPortValues != NULL )
     aPortValues->Clear();

   ConfirmOpenFile( aFileName );
   TStrings * aBMNames = GetBookmarkNames();
   if( aBMNames ==NULL ||aBMNames->Count <= 0 )
     return;

   for (int i = 0; i < aBMNames->Count; i++ )
   {
      String aName = aBMNames->Names[i];
      String aPortName = GetPortNameByBmName( aName );
      if (aPortName == "" )
        continue;

      if( aPortValues->IndexOfName(aPortName) < 0 )
            aPortValues->Add(aPortName+"="+GetBmVal(aName));
   }
}*/

/*void MExcelFun::InitVBS( bool IsOnlyRun )
{
   MOfficeFun::InitVBS( IsOnlyRun );
   if( FindWindow("XlMain",NULL )<= 0 )//word未启动
     AddVBS(" Set MyExcel = CreateObject(\"Excel.Application\")");
   else
     AddVBS(" Set MyExcel = GetObject(,\"Excel.Application\")");     //  '创建WORD文档
}

String MExcelFun::GetSheetCellValue( String aSheetName,int aRowId,int aColId )
{
    InitVBS( false );
    AddVBS(" MyExcel.sheets(\""+aSheetName+"\").Activate ");
    AddVBS(" set MySheet = MyExcel.ActiveSheet ");
    AddVBS("  main = MySheet.cells("+IntToStr( aRowId )+","+IntToStr( aColId )+ ").Value");
    EndVBS(false);
    String aVal = EvalScript(VBS );
    return aVal;
}

TStrings * MExcelFun::GetPortData( String aFileName )
{
   if( 	!ConfirmOpenFile( aFileName )  )
     return NULL;
     
   //int aPortNum = StrToInt( GetSheetCellValue(DataInfo,PortNumRow,PortNumCol );
   InitVBS( false );
   AddVBS(" MyExcel.Visible = false ");
   AddVBS(" MyExcel.sheets(\""+DataValue+"\").Activate ");
   AddVBS(" set MySheet = MyExcel.ActiveSheet ");
   AddVBS(" cellval = mysheet.Cells(1, 1).Value ");
   AddVBS(" aColId = 1 ");
   AddVBS(" ResVal = \"\" ");
   AddVBS(" Do Until cellval = \"\" ");
   AddVBS(" ResVal = CStr(cellval) & \"=\" & CStr(mysheet.Cells(2, aColId).Value) & \",\" & ResVal");
   AddVBS(" aColId = aColId + 1");
   AddVBS(" cellval = mysheet.Cells(1, aColId).Value ");
   AddVBS(" Loop ");
   AddVBS(" main = ResVal  ");

   EndVBS(false);
   String aVal = EvalScript(VBS );
   return splitToStrings(aVal,",");
} */

String TrimAll(String astr) 
{
	String ar = Trim(astr);

	int apos = ar.Pos(" ");
	while( apos > 0 )
	{
		String ab = Trim(ar.SubString(apos,ar.Length()));
		ar = ar.SubString(1,apos-1)+ab;    //左侧
		apos = ar.Pos(" ");

	}
	return ar;
}

String ReplaceSymbByDL( String aPName )
{
   if (aPName == "" ) return NULL;
  //替换所有的 空格
   TReplaceFlags aFlag;
   aFlag<< rfReplaceAll<<rfIgnoreCase;
   String LabStr = " ";
   aPName =  StringReplace(aPName ," ","_",aFlag);
  //  '~' 126   @ 64  # 35 $ 36 % 37  ^ 94  & 38 * 42  (40 )41 -   45 +43 / 47 , 44
//. 46  ? 63  空格 32   '39  "34 _95 =61  ;59 :58
   aPName =  StringReplace(aPName ,"-","_",aFlag);
   aPName =  StringReplace(aPName ,"\\","_",aFlag);
   aPName =  StringReplace(aPName ,"/","_",aFlag);
   aPName =  StringReplace(aPName ,"@","_",aFlag);
   aPName =  StringReplace(aPName ,"#","_",aFlag);
   aPName =  StringReplace(aPName ,"+","_",aFlag);
   aPName =  StringReplace(aPName ,"*","_",aFlag);
   aPName =  StringReplace(aPName ,"%","_",aFlag);
   aPName =  StringReplace(aPName ,"&","_",aFlag);

   aPName =  StringReplace(aPName ,"~","_",aFlag);
   aPName =  StringReplace(aPName ,"!","_",aFlag);
   aPName =  StringReplace(aPName ,":","_",aFlag);
   aPName =  StringReplace(aPName ,";","_",aFlag);
   aPName =  StringReplace(aPName ,".","_",aFlag);
   aPName =  StringReplace(aPName ,",","_",aFlag);
   aPName =  StringReplace(aPName ,"'","_",aFlag);
   aPName =  StringReplace(aPName ,"""","_",aFlag);
   aPName =  StringReplace(aPName ,"(","_",aFlag);
   aPName =  StringReplace(aPName ,")","_",aFlag);
   aPName =  StringReplace(aPName ,"[","_",aFlag);
   aPName =  StringReplace(aPName ,"[","_",aFlag);
   aPName =  StringReplace(aPName ,"{","_",aFlag);
   aPName =  StringReplace(aPName ,"}","_",aFlag);
   aPName =  StringReplace(aPName ,"^","_",aFlag);
   aPName =  StringReplace(aPName ,"$","_",aFlag);
   
   return aPName;
}

TTreeNode * GetTN( TTreeNodes * I_Tree,String aName )
{
	String ap = aName;
	if( aName.Pos(C_BMLab) >0 )
	 ap = aName.SubString( C_BMLab.Length()+1,aName.Length() );
	for (int i = 0 ; i < I_Tree->Count; i++) {
	  String aT = ReplaceSymbByDL( UpperCase( I_Tree->Item[ i ]->Text) );
	  if( UpperCase( ap )==  UpperCase( aT )  )
	  {
	     return I_Tree->Item[i];
	  }

	}
	return NULL;
}

//---------------------------------------------------------------------------
void MapBMToTV( TStrings * aBMInfo,TTreeView * aTV )
{
   if( aBMInfo == NULL || aTV == NULL )
     return;
     
   for (int i = aBMInfo->Count-1; i >=0 ; i--) {
	 //TTreeNode * aNode = aTV->Items[i];
	 String aName = aBMInfo->Names[i];
	 String aPortName = G_Word->GetPortNameByBmName(aName);
	// TTreeNode * aNode = Get_NameNode_InTreeNodes( aTV->Items,aPortName);
	//int ap = 0;
	TTreeNode * aNode = GetTN( aTV->Items,aPortName);
	 if( aNode == NULL ) continue;
	 MBookMark * aBM = new MBookMark;
	 aBM->Name = aName;
	 String Str1,Str2;
	 SplitStrTo2Str( aBMInfo->Values[ aBMInfo->Names[i]] ,";",Str1,Str2);
	 aBM->StartPos = StrToInt( Str1);
	 aBM->EndPos = StrToInt( Str2);
	 if( GetNodeChild(aNode, aName ) == NULL )
  	  aTV->Items->AddChildObject( aNode,aName,aBM );
   }
   aTV->Items->Item[0]->Expand(true);
}

TTreeNode *  GetNodeChild( TTreeNode *aPNode ,String aChildName )
{
	if( aPNode == NULL || aChildName=="") return NULL;
	for (int i = 0; i < aPNode->Count; i++) {
       if( aPNode->Item[i]->Text == aChildName ) return aPNode->Item[i];  
	}
	return NULL;
}

MBookMark::MBookMark()
{
	fStartPos = -1;
	fEndPos = -1;
	fPortName ="";
}

MWordFun * G_Word =  new MWordFun;
//MExcelFun * G_EF =  new MExcelFun;

#pragma package(smart_init)
