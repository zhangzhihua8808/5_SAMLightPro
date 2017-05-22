
//---------------------------------------------------------------------------
#pragma hdrstop

#include "UnitOfficeFun.h"
#include "UnitPPTFun.h"
#include "COMMON_FUNC.hpp"
#include "UnitTool_Single.h"
#include "UnitTool_Class.h"

MPPtFun* G_PPT   =  new MPPtFun;
Variant PptApp;

//--------------------- PowerPoint functions -----------------------------------


/* ---该函数没有被采用

HWND RunPPTByOle()
{
    bool flag = ProcessExists();
    Variant aPptApp;
    
    if( flag==false )
    {
      aPptApp  = Variant::CreateObject("Powerpoint.Application");
      aPptApp.OlePropertySet( "Visible", true );
      HWND hWndPpt = ::FindWindow(NULL, "Microsoft PowerPoint");
      while (hWndPpt == 0)
        hWndPpt = ::FindWindow(NULL, "Microsoft PowerPoint");
      return hWndPpt;
    }
    else
    {
      aPptApp  = Variant::GetActiveObject("Powerpoint.Application");
      aPptApp.OlePropertySet("Visible", true);
      int Presentation_Count = aPptApp.OlePropertyGet("Presentations").OlePropertyGet("Count");
      if( Presentation_Count>0 )
      {
        String str = aPptApp.OlePropertyGet("ActivePresentation").OlePropertyGet("Name");
        str ="Microsoft PowerPoint - [" + str + "]";
        HWND hWndPpt = ::FindWindow(NULL, str.c_str() );
        while (hWndPpt == 0)
        {
          hWndPpt = ::FindWindow(NULL, str.c_str());
        }
        return hWndPpt;
      }
      else if( Presentation_Count==0 )
      {
              HWND hWndPpt = ::FindWindow(NULL, "Microsoft PowerPoint");
              while (hWndPpt == 0)
              {
                hWndPpt = ::FindWindow(NULL, "Microsoft PowerPoint");
              }
              return hWndPpt;
      }
  }
} */


void MPPtFun::InitVBS( bool IsOnlyRun )
{
   MOfficeFun::InitVBS( IsOnlyRun );

   if( ProcessExists("POWERPNT.EXE") == false )    //ppt未启动
     AddVBS(" Set MyPPT = CreateObject(\"PowerPoint.Application\")");
   else
    AddVBS(" Set MyPPT = GetObject(,\"PowerPoint.Application\")");     //  '创建WORD文档

   PptApp = Variant::GetActiveObject( "Powerpoint.Application" );
}

Variant MPPtFun::GetSelOleObjProp( String aName )
{
  InitVBS( false );
  AddVBS( " set bShape = MyPPT.ActiveWindow.Selection.SlideRange");
  AddVBS( " main = bShape."+aName );
  EndVBS( false );
  return EvalScript(VBS );
}

void MPPtFun::SingleProeInst()
{
  TStrings* aNList = new TStringList();

  Variant aCurSlide = CurSlide();
  String aNewName = GetSlideNewPViewName( aCurSlide, aNList );
  delete aNList;
  if( UpperCase(aNewName) != UpperCase(C_PrePViewName+"1")  )
  {
      throw Exception("该页面只允许插入单个Proe对象实例！");
  }
}

void MPPtFun::SetSelOleObjUrl( String aUrl)
{
   SetSelOleObj("OLEFormat.object.URL = "+ AnsiQuotedStr(aUrl,'\"'));
}


void MPPtFun::SetSelOleObj( String aNameValue)
{
  InitVBS();
  AddVBS(" set bShape = MyPPT.ActiveWindow.Selection.SlideRange");
  AddVBS("bShape."+ aNameValue );
  EndVBS();
} 

void MPPtFun::ConfirmRun()
{
   if( ProcessExists("POWERPNT.EXE")==false )
   {
     MOfficeFun::InitVBS();
     AddVBS(" Set MyPPT = CreateObject(\"Powerpoint.Application\")");
     AddVBS(" MyPPT.Visible = true ");
     EndVBS();
   }
   else
   {
      MOfficeFun::InitVBS();
      AddVBS(" Set MyPPT = GetObject(,\"Powerpoint.Application\")");
      AddVBS(" MyPPT.Visible = true ");
      EndVBS();
   }
   PptApp = Variant::GetActiveObject("Powerpoint.Application");
}

void  MPPtFun::Open( String  aName )
{    
   InitVBS();
   AddVBS(" MyPPT.Presentations.Open " + AnsiQuotedStr(aName,'\"'));
   EndVBS();
}

void MPPtFun::Quit()
{
    if( ProcessExists("POWERPNT.EXE")==true )
    {
	  InitVBS( );
	  AddVBS(" MyPPT.Quit ");
	  EndVBS();
    }

    //int Presentation_Count = PptApp.OlePropertyGet("Presentations").OlePropertyGet("Count");
    //	for(int i=1;i<=Presentation_Count;i++)
    //	{
    //	  PptApp.OlePropertyGet("ActivePresentation").OleProcedure("Close");
    //	}
    //	PptApp.OleFunction("Quit");
    //	PptApp = Unassigned;

    //	char  cBuf[256];
    //	AnsiString  ExeFile;
    //	PROCESSENTRY32  pe32 = {sizeof(pe32)};
    //	HANDLE hSnapShot  = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
    //	if(hSnapShot == NULL)
    //	return;
    //	bool  bFlag  =  Process32First(hSnapShot,&pe32);
    //	while  (bFlag)
    //	{
    //	  ExeFile = AnsiString(pe32.szExeFile);
    //	  if(ExeFile=="POWERPNT.EXE")
    //	  {
    //    int pPid = pe32.th32ProcessID;
    //    HANDLE ps = OpenProcess(1,false,pPid);
    //    if(ps)
    //    {
    //      TerminateProcess(ps,-9);
    //    }
    //    else
    //       MessageBox(Handle, "无法终止此进程！ ",Application-> Title.c_str(),MB_OK|MB_ICONERROR);
    //  }
    //  bFlag = Process32Next(hSnapShot,&pe32);
    //}
    //	CloseHandle(hSnapShot);  
}

bool MPPtFun::IsModify()
{
  InitVBS(false);

  AddVBS(" acount = MyPPT.Presentations.Count ");
  AddVBS(" for i = 1 to acount ");
  AddVBS(" if MyPPT.Presentations.Item(i).Saved = 0 Then  ");
  AddVBS("   main =1 ");
  AddVBS("   exit function ");
  AddVBS(" End If ");
  AddVBS(" next ");
  AddVBS(" main =0 ");
  EndVBS(false);

  int  aRes = EvalScript(VBS);
  if( aRes ==0 )
        return false;
  if( aRes ==1 )
        return true ;
}

String MPPtFun::ActPreFullFileName()
{
   InitVBS(false);
   AddVBS(" main= MyPPT.ActivePresentation.FullName ");
   EndVBS(false);
   String  aName = EvalScript(VBS );
   return aName;
}

void MPPtFun::ChangePviewPvsPath()
{
    InitVBS();
    AddVBS(" For i = 1 To MyPPT.ActivePresentation.Slides.Count");
    AddVBS(" set bShapes = MyPPT.ActivePresentation.Slides.item(i).Shapes");
    AddVBS(" For Each s In bShapes");
    AddVBS(" If s.Type = 6 Then s.UnGroup  ");
    AddVBS("  Next ");
    AddVBS("  Next ");

    AddVBS(" For i = 1 To MyPPT.ActivePresentation.Slides.Count ");
    AddVBS("Set aslide = MyPPT.ActivePresentation.Slides.Item(i)");
    AddVBS("For Each s In aslide.Shapes");
    AddVBS("  If (s.name = \"TManualPView1\") Then");

    AddVBS("   aurl = s.OLEFormat.Object.SourceURL");
    AddVBS("  apath = Left(aurl, InStr(1, aurl, \"MyPpts\\Files\\\") + 12) ");
    AddVBS("  s.OLEFormat.Object.SourceURL = Replace(aurl, apath, MyPPT.ActivePresentation.Path & \"\\Files\\\") ");
    AddVBS(" End If");
    AddVBS("Next ");
    AddVBS("Next");
  EndVBS();

  int aC = ActPreSlidesCount();
  for (int i=0; i<aC ; i++)
  {
     GroupPview(i+1);
  }
}


void MPPtFun::SaveAll()
{
  //  InitVBS( );
  //  AddVBS(" acount = MyPPT.Presentations.Count ");
  //  AddVBS(" for i = 1 to acount ");
  //  AddVBS(" MyPPT.Presentations.Item(i).save ");
  //  AddVBS(" next ");
  //  EndVBS();

  InitVBS();
  AddVBS(" acount = MyPPT.Presentations.Count ");
  AddVBS(" for i = 1 to acount ");
  AddVBS(" if MyPPT.Presentations.Item(i).Saved = 0 Then  ");
  AddVBS(" MyPPT.Presentations.Item(i).save ");
  AddVBS(" End If ");
  AddVBS(" next ");
  EndVBS();

}

void  MPPtFun::Save( String aFileName )
{
   String aStr = ReplaceStr(aFileName,"\\","#");

   InitVBS();
   AddVBS(" For Each aPptDoc In MyPPT.Presentations ");

   AddVBS(" Dim  str1,aName ");
   AddVBS(" str1 = aPptDoc.FullName ");  
   AddVBS(" aName =  Replace( str1,\"\\\", \"#\") ");

   AddVBS("    if lcase(aName) = "+AnsiQuotedStr(LowerCase( aStr), '""' ) +" then ");
   AddVBS(" if aPptDoc.Saved = 0 Then  ");
   AddVBS("     aPptDoc.Save");
   AddVBS("    end if ");
   AddVBS("     exit sub ");
   AddVBS("    end if ");
   AddVBS("   next ");

   EndVBS();
}

void MPPtFun::Close( String aFileName )
{
   InitVBS();
   String aStr = ReplaceStr( aFileName,"\\","#" );
   AddVBS(" For Each aPptDoc In MyPPT.Presentations ");
   AddVBS("   Dim  str1,aName");
   AddVBS("   str1 = aPptDoc.FullName");
   AddVBS("   aName =  Replace( str1,\"\\\", \"#\")");

   AddVBS("   if lcase(aName) = "+AnsiQuotedStr(LowerCase( aStr),'""') +" then ");
   AddVBS("     aPptDoc.Close");

   //if( IsSave )
   //  AddVBS("     aPptDoc.Close -1");
   //else
   // AddVBS("     aPptDoc.Close 0");

   AddVBS("    exit sub ");
   AddVBS("   end if ");
   AddVBS(" next ");
   EndVBS();
}

//------------------------------------------------------------------------------
//功能：获得所有窗口
//------------------------------------------------------------------------------

void MPPtFun::CloseAll()
{
   InitVBS();
   AddVBS("  acount = MyPPT.Presentations.Count ");
   AddVBS(" for i = acount to 1 Step -1");
   AddVBS(" MyPPT.ActivePresentation.Close ");
   AddVBS(" next ");
   EndVBS();
}

//------------------------------------------------------------------------------
//功能：获得 Presentations.add
//------------------------------------------------------------------------------

void MPPtFun::NewFile( String aName )
{
  InitVBS();
  AddVBS("MyPPT.Presentations.Add");
  AddVBS("MyPPT.ActivePresentation.SaveAs "+AnsiQuotedStr(aName,'\"') );
  EndVBS();
}

//------------------------------------------------------------------------------
//功能：获得 Presentations.count
//------------------------------------------------------------------------------

int MPPtFun::PresentCount()
{
  InitVBS(false);
  AddVBS(" main = MyPPT.Presentations.count");
  EndVBS(false);
  int  aCount = EvalScript(VBS );
  return aCount;
}

//------------------------------------------------------------------------------
//功能：获得 ActivePresentation.Slides.count
//------------------------------------------------------------------------------

int MPPtFun::ActPreSlidesCount()
{
  //PptApp.OlePropertyGet("Presentations").OlePropertyGet("Count")
  try
  {
    InitVBS(false);
    AddVBS(" main = MyPPT.ActivePresentation.Slides.count");
    EndVBS(false);
    int  aCount = EvalScript(VBS );
    return aCount;
  }
  catch(...)
  {
    return -1;
  }
}

//-------------------SelectType-------------------------------------------------

int MPPtFun::ActWinSelType()
{
   //PptApp.OlePropertyGet("ActiveWindow").OlePropertyGet("Selection").OlePropertyGet("Type") == ppSelectionShapes)

   InitVBS(false);
   AddVBS(" main = MyPPT.ActiveWindow.Selection.Type");
   EndVBS(false);

   int  aType = EvalScript(VBS );
   return aType;
}

//---------------------------SildeRange-----------------------------------------

//------------------------------------------------------------------------------
//功能：获得 ActiveWindow.Selection.SlideRange.Count
//------------------------------------------------------------------------------

int MPPtFun::ActWinSelSRCount()
{
  try
  {
    InitVBS(false);
    AddVBS(" main = MyPPT.ActiveWindow.Selection.SlideRange.Count");
    EndVBS(false);

    int  aCount = EvalScript( VBS );         //GetObjProperty( PptApp, "ActiveWindow.Selection.SlideRange.Count" );
    return aCount;
  }
  catch(...)
  {
    return -1;
  }
}

String MPPtFun::ActWinSelSlideRangeName()
{
  //PptApp.OlePropertyGet("ActiveWindow").OlePropertyGet("Selection").OlePropertyGet("SlideRange").
      //          OlePropertyGet("Name");
   InitVBS(false);
    AddVBS(" main = MyPPT.ActiveWindow.Selection.SlideRange.Name");
    EndVBS(false);
    String  aName = EvalScript(VBS );
    return aName;
}


//--------------SelShape--------------------------------------------------------

int MPPtFun::ActWinSelShapeRangeType()
{
   // Variant bShape = PptApp.OlePropertyGet("ActiveWindow").OlePropertyGet("Selection").
   //              OlePropertyGet("ShapeRange");
   //    String bShapeName = bShape.OlePropertyGet("Name");

   InitVBS(false);
   AddVBS(" main = MyPPT.ActiveWindow.Selection.ShapeRange.Type");
   EndVBS(false);

   int  aType = EvalScript(VBS );
   return aType;
}

String MPPtFun::ActWinSelShapeRangeName()
{
    InitVBS(false);
    AddVBS(" main = MyPPT.ActiveWindow.Selection.ShapeRange.Name");
    EndVBS(false);
    String  aName = EvalScript(VBS );
    return aName;
}


void MPPtFun::InsertPic( String aName ,float aLeft, float aTop,float aWidth,float aHeight )
{
   InitVBS();
   AddVBS( " set mShapes = MyPPT.ActiveWindow.Selection.SlideRange.Shapes");
   AddVBS( " mShapes.AddPicture " + AnsiQuotedStr(aName,'\"')+",false,true," +
           FloatToStr(aLeft)+","+FloatToStr(aTop)+","+FloatToStr(aWidth)+","+FloatToStr(aHeight));
   EndVBS();
}

void  MPPtFun::SaveAsHtml(String aWebName)
{
    InitVBS();
    AddVBS(" set ActPre = MyPPT.ActivePresentation");
    AddVBS(" ActPre.SaveAs "+AnsiQuotedStr(aWebName,'\"')+",12,0");
    EndVBS();

    // ActivePresentation = PptApp.OlePropertyGet("ActivePresentation");
    //       ActivePresentation.OleFunction("SaveAs",PptWebName.c_str(),ppSaveAsHTML,False);
}

String  MPPtFun::SlidesName( int aIndex )
{
   InitVBS(false);
   AddVBS("set iSlide= MyPPT.ActivePresentation.Slides.Item( "+IntToStr( aIndex )+" )");
   AddVBS(" main = iSlide.Name");
   EndVBS(false);
   String  aName = EvalScript(VBS );
   return aName;
}

int  MPPtFun::ActPreSlideShapeCount( int aIndex )
{
   InitVBS(false);
   AddVBS("set iSlide= MyPPT.ActivePresentation.Slides.Item( "+IntToStr( aIndex )+" )");
   AddVBS(" main = iSlide.Shapes.Count");
   EndVBS(false);

   int  aCount = EvalScript(VBS );
   return aCount;
}

String MPPtFun::ActPreName_NoExt()
{
  return GetFileName_NoExt( ActPreName() );
}

String MPPtFun::ActPreName()
{
   InitVBS(false);
   AddVBS(" main= MyPPT.ActivePresentation.Name ");
   EndVBS(false);
   String  aName = EvalScript(VBS );
   return aName;
}

//--------------------获取Slide的各种属性---------------------------------------

String MPPtFun::SlideShapeName( int aSlideId,int aShapeId )
{
   InitVBS(false);
   AddVBS("set iSlide= MyPPT.ActivePresentation.Slides.Item( "+IntToStr( aSlideId )+" )");
   AddVBS(" main = iSlide.Shapes.Item( "+IntToStr( aShapeId )+" ).Name");
   EndVBS(false);

   String  aName = EvalScript(VBS );
   return aName;
}

int MPPtFun::SlideShapeType( int aSlideId,int aShapeId )
{
   InitVBS(false);
   AddVBS("set iSlide= MyPPT.ActivePresentation.Slides.Item( "+IntToStr( aSlideId )+" )");
   AddVBS(" main = iSlide.Shapes.Item( "+IntToStr( aShapeId )+" ).Type");
   EndVBS(false);
   int  aType = EvalScript( VBS );
   return aType;
}

String MPPtFun::SlideShapeUrl( int aSlideId,int aShapeId)
{
   // String urlPath = ijShape.OlePropertyGet("OLEFormat").OlePropertyGet("object").OlePropertyGet("sourceUrl");

   InitVBS(false);
   AddVBS("set iSlide= MyPPT.ActivePresentation.Slides.Item( "+IntToStr( aSlideId )+" )");
   AddVBS(" main = iSlide.Shapes.Item( "+IntToStr( aShapeId )+" ).OLEFormat.object.sourceUrl");
   EndVBS(false);

   String  aName = EvalScript( VBS );
   return aName;
}

String MPPtFun::SlideShapeAltTxt( int aSlideId,int aShapeId )
{
    // String urlPath = ijShape.OlePropertyGet("OLEFormat").OlePropertyGet("object").OlePropertyGet("sourceUrl");
    InitVBS(false);
    AddVBS("set iSlide= MyPPT.ActivePresentation.Slides.Item( "+IntToStr( aSlideId )+" )");
    AddVBS(" main = iSlide.Shapes.Item( "+IntToStr( aShapeId )+" ).AlternativeText");
    EndVBS(false);
    String  aTxt = EvalScript(VBS );
    return aTxt;
}

int  MPPtFun::SlideShapesHasTitle( int aSlideId )
{

  //  iSlide=ActivePresentation.OlePropertyGet("Slides").OleFunction("Item",i);
  //         if( iSlide.OlePropertyGet("Shapes").OlePropertyGet("HasTitle") == msoTrue )
  //         {
  //           String TitleName =iSlide.OlePropertyGet("Shapes").OlePropertyGet("Title").OlePropertyGet("AlternativeText");
  //           if(TitleName == "文本框: "+Slidename)
  //           {
  //            // PptApp.OlePropertyGet("ActiveWindow").OlePropertyGet("Selection").OlePropertyGet("SlideRange") = iSlide;
  //             iSlide.OleProcedure("Select");
  
  InitVBS( false );
  AddVBS( "set iSlide= MyPPT.ActivePresentation.Slides.Item( "+IntToStr( aSlideId )+" )");
  AddVBS( " main = iSlide.Shapes.HasTitle" );
  EndVBS( false );

  int  aType = EvalScript(VBS );
  return aType;
}

//功能：获得 Shapes.Title.AlternativeText
String MPPtFun::SlideShapesTitleAltTxt( int aSlideId )
{
   InitVBS(false);
   AddVBS("set iSlide = MyPPT.ActivePresentation.Slides.Item( "+IntToStr( aSlideId )+" )");
   AddVBS(" main = iSlide.Shapes.Title.AlternativeText");
   EndVBS(false);

   String  aTxt = EvalScript(VBS );
   return aTxt;
}

void MPPtFun::SlidesSelect( int aSlideId )
{
   InitVBS();
   AddVBS("set iSlide= MyPPT.ActivePresentation.Slides.Item( "+IntToStr( aSlideId )+" )");
   AddVBS(" iSlide.Select");
   EndVBS();
}




//------------------------CurSlide----------------------------------------------

Variant MPPtFun::GetSlide( int i )
{
  return GetObjProperty( PptApp,"ActiveWindow.Selection.SlideRange").Exec(Function("item")<<i );
}

Variant MPPtFun::CurSlide()
{
  return GetSlide(1);  //GetObjProperty( PptApp,"ActiveWindow.Selection.SlideRange" ).Exec( Function("item") <<1;
}

String MPPtFun::CurSlideName()
{
  try
  {
    return GetObjProperty( CurSlide(),"Name" );
  }
  catch(Exception& e)
  {
    //gError->Warn("获得SlideName出错！"+e.Message);
    return "";
  }
}

int MPPtFun::CurSlideId()
{
   try
  {
    return  GetObjProperty( CurSlide(),"SlideIndex");
  }
  catch(Exception& e)
  {
    //gError->Warn("获得SlideID出错！"+e.Message);
    return -1;
  }
}

//------------------------OleObject---------------------------------------------

String  MPPtFun::AddOleObj( MOleObj* aObj )
{
  InitVBS(false);
  AddVBS(" on error resume next");
  AddVBS(" set bShapes = MyPPT.ActiveWindow.Selection.SlideRange.Shapes");
  AddVBS(" set bShape = bShapes.AddOLEObject("+aObj->PosSizeStr() + AnsiQuotedStr( aObj->mClassName ,'\"')+",,,,,"+IntToStr(aObj->mLink)+")");

  if( aObj->mName != "")
    AddVBS(" bShape.Name = "+ AnsiQuotedStr( aObj->mName,'\"'));

  if( aObj->mPropertyStrs != "" )
  {
    TStrings * aPro = new TStringList();
    aPro->DelimitedText = aObj->mPropertyStrs;
    for (int i =0; i < aPro->Count  ; i++)
      AddVBS(" bShape.OLEFormat.object."+ aPro->Names[i]+" = " + aPro->Values[aPro->Names[i]]);
    delete aPro;
    //AddVBS(" bShape.OLEFormat.object.Caption = "+ AnsiQuotedStr(aObj->mCaption ,'\"'));
  }

  AddVBS(" main = bShape.Name ");
  EndVBS(false);

  String  aTxt = EvalScript(VBS );
  return aTxt;
}

void MPPtFun::UpdateOleObj( String aSlideName,String aCtrlName ,String PropertyStr)
{
   if(  aSlideName == "" ||  aCtrlName =="" ||  PropertyStr=="" )
     return;
     
   UnGroup(aSlideName);   //To李申，难道不恢复吗

   try
   {
     InitVBS();
     
     AddVBS(" aCount = MyPPT.ActivePresentation.Slides.count");
     AddVBS("set aSlide = nothing");
     AddVBS("for i = 1 to aCount");
     AddVBS("if Lcase(MyPPT.ActivePresentation.Slides.item(i).Name) = "+AnsiQuotedStr(LowerCase(aSlideName) ,'\"')+" then");
     AddVBS("set aSlide = MyPPT.ActivePresentation.Slides.item(i) ");
     AddVBS("exit for");
     AddVBS("end if ");
     AddVBS("next ");
     AddVBS("if aSlide is nothing then exit sub");
     AddVBS("for i = 1 to aSlide.Shapes.Count ");
     AddVBS("if lCase(aSlide.Shapes.item(i).name) = "+AnsiQuotedStr(LowerCase(aCtrlName) ,'\"')+" then ");
     AddVBS(" set aShape =  aSlide.Shapes.item(i) ");

     TStrings * aPro = new TStringList();
     aPro->DelimitedText = PropertyStr;
     for (int i =0; i < aPro->Count  ; i++)
       AddVBS(" aShape."+ aPro->Names[i]+" = " + aPro->Values[aPro->Names[i]]);
     delete aPro; 

     AddVBS("exit for");
     AddVBS("end if ");
     AddVBS("next");
     EndVBS();

    // GroupPview( SlideNameToId( aSlideName ) );
   }
   catch(Exception &aE)
   {
      throw Exception( aE.Message+"UpdateOleObj更新控件属性出错！");
   }
}

void  MPPtFun::AddOleTitleObj( MOleTitleObj * aObj )
{
  InitVBS();

  AddVBS(" set bShapes = MyPPT.ActiveWindow.Selection.SlideRange.Shapes");
  AddVBS(" set bShape = bShapes.AddOLEObject("+aObj->PosSizeStr() + AnsiQuotedStr( aObj->mClassName ,'\"')+",,,,,"+IntToStr(aObj->mLink)+")");
  AddVBS(" bShape.OLEFormat.object.Caption = "+ AnsiQuotedStr(aObj->mCaption ,'\"'));

  // if( FileExists( aObj->mPic  ) )
  //    AddVBS(" bShape.OLEFormat.object.Picture = LoadPicture("+ AnsiQuotedStr(aObj->mPic ,'\"')+")");

  if( aObj->mName != "" )
      AddVBS(" bShape.Name = "+ AnsiQuotedStr( aObj->mName,'\"'));
  if( aObj->mFontSize != "" )
   AddVBS(" bShape.OLEFormat.object.FontSize = "+ aObj->mFontSize);

  EndVBS();
}


void MPPtFun::AddScrollBar( MOleFrmScrollBar * aSB )
{
  // bShape = bShapes.OleFunction("AddOLEObject",48.125,468.5,629.375,11.25,"Forms.ScrollBar.1",EmptyParam,
  //            EmptyParam,EmptyParam,EmptyParam,msoFalse);
  //    bShape.OlePropertyGet("OLEFormat").OlePropertyGet("object").OlePropertySet("Value","1");
  //bShape.OlePropertyGet("OLEFormat").OlePropertyGet("object").OlePropertySet("Max",G_Frames->IntTotalFrames - 1);

  InitVBS();
  AddVBS(" set bShapes = MyPPT.ActiveWindow.Selection.SlideRange.Shapes");

  // 查找同名shape，如果存在，就更新属性 ，否则新建
  AddVBS(" set bShape = bShapes.AddOLEObject("+aSB->PosSizeStr() + AnsiQuotedStr( aSB->mClassName ,'\"')+",,,,,"+IntToStr(aSB->mLink)+")");
  if( aSB->mName != "" )
     AddVBS(" bShape.Name = "+  AnsiQuotedStr( aSB->mName,'\"'));

  if( aSB->mValue > -1 )
   AddVBS(" bShape.OLEFormat.object.Value = "+ IntToStr(aSB->mValue ));

  if( aSB->mMax > -1 )
    AddVBS(" bShape.OLEFormat.object.Max = "+ IntToStr(aSB->mMax ));

  EndVBS();
}
  
//--------------臧霖-------添加的AddText------------20130820-----
void MPPtFun::AddTextBox(MOleFrmTextBox * aTxt )
{
  //bShape = bShapes.OleFunction("AddOLEObject",475,480,40,30,"Forms.TextBox.1",EmptyParam,
  //            EmptyParam,EmptyParam,EmptyParam,msoFalse);
  //bShape.OlePropertyGet("OLEFormat").OlePropertyGet("object").OlePropertySet("Text",PpsTitle);

  InitVBS();
  AddVBS(" set bShapes = MyPPT.ActiveWindow.Selection.SlideRange.Shapes");

  // 查找同名shape，如果存在，就更新属性 ，否则新建
  AddVBS(" set bShape = bShapes.AddOLEObject("+aTxt->PosSizeStr() + AnsiQuotedStr( aTxt->mClassName ,'\"')+",,,,,"+IntToStr(aTxt->mLink)+")");

  if( aTxt->mName != "" )
     AddVBS(" bShape.Name = "+  AnsiQuotedStr( aTxt->mName,'\"'));
  if( aTxt->StrNum != "" )
    AddVBS(" bShape.OLEFormat.object.Text = "+ AnsiQuotedStr( aTxt->StrNum ,'\"') );

  EndVBS();
}

String MPPtFun::InsertMedia( String aFileName ,String MediaClassName )
{
    InitVBS(false);
    AddVBS(" set bShapes = MyPPT.ActiveWindow.Selection.SlideRange.Shapes");
    AddVBS(" set bShape = bShapes.AddOLEObject(88,88,518,414,"+ AnsiQuotedStr( MediaClassName,'\"')+",,,,,False)");
    AddVBS(" bShape.OLEFormat.object.URL = MyPPT.ActivePresentation.Path & "+ AnsiQuotedStr(aFileName,'\"'));
    AddVBS(" main= bShape.Name");
    EndVBS( false );
    String aName = EvalScript( VBS );
    return aName;
}


String MPPtFun::GetPVAltTxt()
{
  return GetSelOleObjProp("AlternativeText" );
}
  
String MPPtFun::GetPVUrl()
{
  //bShape = PptApp.OlePropertyGet("ActiveWindow").OlePropertyGet("Selection").OlePropertyGet("ShapeRange");
  //ObjectFileName = bShape.OlePropertyGet("OLEFormat").OlePropertyGet("object").OlePropertyGet("sourceUrl");

  return GetSelOleObjProp("OLEFormat.object.sourceUrl" );

}

//--------------UnGroup---------------------------------------------------------

void MPPtFun::UnGroup( Variant aCurSlide )
{
   UnGroup( int( GetObjProperty( aCurSlide,"SlideIndex" ) ) );
}

void MPPtFun::UnGroup( String aSlideName )
{
   UnGroup( SlideNameToId( aSlideName ) );
}

void MPPtFun::UnGroup( int aSlideIndex )
{
  InitVBS();
  AddVBS(" set bShapes = MyPPT.ActivePresentation.Slides.item(" + IntToStr( aSlideIndex) + ").Shapes");
  AddVBS(" For Each s In bShapes");
  AddVBS(" If s.Type = 6 Then s.UnGroup  ");
  AddVBS("  Next ");
  EndVBS();
}

int MPPtFun::SlideNameToId( String aSlideName )
{
  InitVBS(false);
  AddVBS(" aCount = MyPPT.ActivePresentation.Slides.Count");
  AddVBS(" for i =1 to aCount");
  AddVBS(" set aSlide = MyPPT.ActivePresentation.Slides.item(i)");
  AddVBS(" If Lcase(aSlide.Name) ="+ AnsiQuotedStr(LowerCase(aSlideName),'\"')+" Then main= aSlide.SlideIndex  ");
  AddVBS("  Next ");
  EndVBS(false);

  return EvalScript(VBS );
}

//当前选中的根据PViewName组合, VBS 中String类型有问题

String MPPtFun::GroupPviewNameList( String PViewName,int aSlideIndex )
{
  InitVBS( false );

  AddVBS( " set bShapes = MyPPT.ActivePresentation.Slides.item("+IntToStr( aSlideIndex)+").Shapes");
  AddVBS( " NameList =\"\" ");
  AddVBS( " For Each s In bShapes");
  AddVBS( " If s.Type <> 6 Then  ");
  AddVBS( "   If InStr(1, LCase(s.Name), " + AnsiQuotedStr(LowerCase(PViewName),'\"')+" ) > 0 Then" );
  AddVBS( "       ReDim Preserve a(aCount)" );
  AddVBS( "       a(aCount) = s.Name  " );
  AddVBS( "  if NameList =\"\" then" );
  AddVBS( "   NameList = s.Name" );
  AddVBS( " else " );
  AddVBS( "     NameList =NameList+\",\"+ s.Name" );
  AddVBS( "    End If " );
  AddVBS( "    End If " );
  AddVBS( "    End If " );
  AddVBS( "  Next " );
  AddVBS( "  main = NameList " );
  EndVBS( false );

  String aNameList = EvalScript( VBS );
  if( aNameList == "" )
    return "";

  TStrings* aList = new TStringList();
  aList->DelimitedText = aNameList;

  String aR ="a(0)";
  for ( int i =1 ; i<aList->Count ; i++ )
   aR = aR+",a("+IntToStr(i)+")";
  return aR; 
}


//------------------------------------------------------------------------------
//功能：产生PView控件组
//------------------------------------------------------------------------------

void MPPtFun::GroupPview( Variant aCurSlide )
{
  try
  {
    int aSlideIndex = GetObjProperty( aCurSlide,"SlideIndex");      //必须将aSlideIndex设置为int
    GroupPview(  aSlideIndex );
  }
  catch( Exception& e )
  {
    gError->Warn( "GroupView出错！" + e.Message );
  }
}

void MPPtFun::GroupPview( int aSlideIndex )
{

  try
  {
     //获得PViewlist
     Variant aCurSlide = GetSlide(aSlideIndex);  //GetObjProperty( PptApp,"ActivePresentation.Slides").Exec(Function("item")<<aSlideIndex );

     TStrings* aNList = new TStringList();
     GetSlideNewPViewName( aCurSlide, aNList );

     //组合PView控件
     GroupByCtrlName( aNList ,aSlideIndex );
     delete aNList;
  }
  catch( Exception& e )
  {
    gError->Warn( "GroupView出错！" + e.Message );
  }

}

void MPPtFun::GroupByCtrlName( TStrings * PViewNameList,int aSlideIndex )
{
  if( PViewNameList == NULL )
    return;

  for ( int i=0 ; i<PViewNameList->Count; i++ )
     GroupByCtrlName( PViewNameList->Strings[i], aSlideIndex );
}

void MPPtFun::GroupByCtrlName( String PViewName,int aSlideIndex )
{
  try
  {
    String aNameList = GroupPviewNameList( PViewName,aSlideIndex );

    InitVBS();
    AddVBS(" on error resume next" );  //by sxd
    AddVBS(" set bShapes = MyPPT.ActivePresentation.Slides.item("+IntToStr( aSlideIndex)+").Shapes");
    AddVBS(" Dim a( )");
    AddVBS(" For Each s In bShapes");
    AddVBS(" If s.Type <> 6 Then ");
    AddVBS("  If InStr(1, LCase(s.Name), "+AnsiQuotedStr(LowerCase(PViewName),'\"')+" ) > 0 Then");
    AddVBS("      ReDim Preserve a(aCount)");
    AddVBS("      a(aCount) =CStr( s.Name  ) ");
    AddVBS("     aCount = aCount + 1 ");
    AddVBS("   End If ");
    AddVBS("   End If ");
    AddVBS("Next ");
    AddVBS(" MyPPT.ActivePresentation.Slides.item("+IntToStr( aSlideIndex)+").Shapes.Range(array("+aNameList+")).Group ");
    EndVBS();
  }
  catch( Exception& e )
  {
    gError->Warn( "GroupByCtrlName出错！"+e.Message );
  }
}

//  void  SetSelOleObjProperty(String aPValue)
//  {
//    InitVBS();
//    AddVBS(" set bShape = MyPPT.ActiveWindow.Selection.SlideRange");
//    if(
//  } 



String MPPtFun::SetPVProperty( String aAltTxt,String aFileName)
{
    /* bShape = PptApp.OlePropertyGet("ActiveWindow").OlePropertyGet("Selection").OlePropertyGet("ShapeRange");
      bShape.OlePropertyGet("OLEFormat").OlePropertyGet("object").OlePropertySet("renderatstartup","true");
      bShape.OlePropertyGet("OLEFormat").OlePropertyGet("object").OlePropertySet("thumbnailView","true");
      str = OrientationsInfo+"&"+ComboBox1->Text + "+" + ComboBox2->Text+ "$";
      bShape.OlePropertySet("AlternativeText",str.c_str());
    */
    InitVBS(false);
    AddVBS(" set bShape = MyPPT.ActiveWindow.Selection.SlideRange");
    if( aFileName != "" )
      AddVBS(" bShape.OLEFormat.object.sourceUrl = "+ AnsiQuotedStr(aFileName,'\"'));
    AddVBS(" bShape.OLEFormat.object.renderatstartup = true ");
    AddVBS(" bShape.OLEFormat.object.thumbnailView = true ");
    if(  aAltTxt != "")
    AddVBS(" bShape.AlternativeText = "+ AnsiQuotedStr(aAltTxt,'\"'));
    AddVBS(" main = bShape.Name ");
    EndVBS(false);
    String aName  =  EvalScript(VBS );
    return aName;
}

//---------------------PView----------------------------------------------------
  
//------------------------------------------------------------------------------
//功能：获得PView的名称集合，并发挥下一个PView的序号
//参数：
//------------------------------------------------------------------------------

String MPPtFun::GetSlideNewPViewName()
{
  Variant aCurSlide = CurSlide(); 
  TStrings* aNList = new TStringList();
  String aNewName = GetSlideNewPViewName( aCurSlide, aNList );
  delete aNList;
  return aNewName;
}

String MPPtFun::GetSlideNewPViewName( Variant aSlide, TStrings* aNameList )//当前slide中遍历返回
{
   if ( aNameList== NULL )
     return "";                    //by sxd

   //组合后的shape无法得到其中的Pview的名称，必须取消组合
   UnGroup( int( GetObjProperty( aSlide,"SlideIndex" ) ) );

   //C_PrePViewName
   Variant shapes = aSlide.Exec( PropertyGet( "Shapes" ) );
   int aCount = GetObjProperty( shapes,"count" );
   int aMax = 0;

   for ( int i=1; i<=aCount ; i++ )
   {
     try
     {
       Variant aShape =  shapes.Exec( Function( "item")<<i );
       String aName =  GetObjProperty( aShape,"Name");

       String aShapeFlag = GetObjProperty( aShape,"AlternativeText");
       if (  aShapeFlag.Pos( C_PViewLab ) <= 0 )     //aName.Pos( C_PrePViewName ) <= 0 )     //TManualPView
         continue;

       aNameList->Add( aName );
       int aNo = StrToIntDef( aName.SubString(  C_PrePViewName.Length()+1, aName.Length() ), 0 );
       if( aNo > aMax )
         aMax =  aNo;
     }
     catch(Exception& e)
     {
       gError->Warn( e.Message );
     }
   }

   return C_PrePViewName+IntToStr( aMax +1 );
}

//------------------------------------------------------------------------------
//功能：获得PView的名称集合，创建一个新的PView (IsAddNew=true)
//------------------------------------------------------------------------------

TStrings* MPPtFun::GetPViewNameList( bool IsAddNew )
{
  Variant aCurSlide = CurSlide();  //GetObjProperty(PptApp,"ActiveWindow.Selection.SlideRange").Exec(Function("item")<<1);

  TStrings* aNList = new TStringList();
  String aNewName = GetSlideNewPViewName( aCurSlide, aNList );

  if( IsAddNew )
    aNList->Add(aNewName) ;
    
  return  aNList;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

void GetPvPos(TStrings* aNameList, float &aL ,float &aT)
{
  if(  aNameList == NULL || aNameList->Count == 0 )
    return;
  aL =  aNameList->Count *C_PosDelta+aL;
  aT =  aNameList->Count *C_PosDelta+aT;
}

//------------------------------------------------------------------------------
//功能：在PPT下，建立PView控件对象，为对象赋予属性AltText
//参数：
//  [ aFileName -- PVIew对象的Source = aFileName ]
//  [ AltText -- PView对象的属性 ]
//  [ 返回：返回PView对象的名称列表 ]
//------------------------------------------------------------------------------

TStrings* MPPtFun::InsertPView( String aFileName, String AltText, float aL,float aT,float aW,float aH, String PviewClassName )
{   
  TStrings* aNList = new TStringList();
  
  Variant aCurSlide = CurSlide();  //GetObjProperty( PptApp,"ActiveWindow.Selection.SlideRange").Exec(Function("item")<<1 );
  String aNewName = GetSlideNewPViewName( aCurSlide, aNList );

  InitVBS( false );
  GetPvPos( aNList,aL,aT );

  AddVBS(" set bShapes = MyPPT.ActiveWindow.Selection.SlideRange.Shapes");

  AddVBS(" set bShape = bShapes.AddOLEObject("+FloatToStr(aL)+","+FloatToStr(aT)+","+FloatToStr(aW)+","+FloatToStr(aH)+","+ AnsiQuotedStr( PviewClassName,'\"')+",,,,,False)");
  AddVBS(" bShape.Name = "+ AnsiQuotedStr(aNewName,'\"'));
  AddVBS(" bShape.OLEFormat.object.sourceUrl = "+ AnsiQuotedStr(aFileName,'\"'));
  AddVBS(" bShape.OLEFormat.object.renderatstartup = \"true\" ");
  AddVBS(" bShape.OLEFormat.object.thumbnailView = \"true\" ");

  if( AltText != "" )
    AddVBS(" bShape.AlternativeText = "+ AnsiQuotedStr(AltText,'\"'));

  AddVBS(" main = bShape.Name ");
  EndVBS(false);
  String aName = EvalScript(VBS );

  aNList->Add( aName );
  return aNList;
}

void MPPtFun::SetCodeSeg( String aPVName,String aCodeFileName )
{
  TStrings* aList = new TStringList();
  try
  {
    aList->LoadFromFile( aCodeFileName );
    aList->Insert( 0, "'"+aPVName+C_PViewCodeStart );
    aList->Insert( aList->Count,"'"+aPVName+C_PViewCodeEnd );
    aList->SaveToFile(aCodeFileName );
  }
  __finally
  {
     delete aList;
  }
}       


//------------------------------------------------------------------------------
//功能：安装了某些程序在office中可能会产生保护，例如Adobe PDFmaker 弹出“该工程被保护无法运行”
//------------------------------------------------------------------------------

void MPPtFun::SetPviewCode(String aSlideName,String aCodeFileName ,String aPVName)
{
    if( FileExists( aCodeFileName ) == false )
      return;
      //ThrowMessageOnTop( "代码文件"+aCodeFileName+"不存在！" );

    try
    {
      SetCodeSeg( aPVName, aCodeFileName );
      InitVBS();

      AddVBS("For i = 1 To MyPPT.VBE.VBProjects.Count ");//140321
      AddVBS("If MyPPT.VBE.VBProjects.Item(i).Name = "+AnsiQuotedStr("VBAProject",'\"')+" Then ");//140321
      AddVBS("Set VBComponents = MyPPT.VBE.VBProjects.Item(i).VBComponents ");//140321
      AddVBS("End If ");//140321
      AddVBS("Next  "); //140321
      AddVBS("SlideItemCount = VBComponents.Count"); 
      AddVBS("SlideItem = 0 ");
      AddVBS(" for m = 1 to  SlideItemCount ");
      AddVBS("  if VBComponents.Item(m).Name = " + AnsiQuotedStr(aSlideName,'\"') +" then " );
      AddVBS("    SlideItem = m ");
      AddVBS("    exit for");
      AddVBS("  end if ");
      AddVBS(" next ");
      AddVBS("if SlideItem > 0  then ");
      AddVBS("  set  CodeModule = VBComponents.Item(SlideItem).CodeModule ");
      //判断删除已有的Pview代码段
      AddVBS("  linesCount = CodeModule.CountofLines ");
      AddVBS("  aStartLine = 0 ");
      AddVBS("  aDelCount = 0 ");
      AddVBS("  for ii=0 to linesCount-1 ");
      AddVBS("  aLineCode = CodeModule.Lines(ii+1 ,1 )");
      AddVBS("  if Lcase( aLineCode ) = " +AnsiQuotedStr("'"+LowerCase(aPVName+C_PViewCodeStart),'\"')+" then");
      AddVBS("  aStartLine = ii+1 ");
      AddVBS("  end if  ");
      AddVBS("  if Lcase( aLineCode ) = " +AnsiQuotedStr("'"+LowerCase(aPVName+C_PViewCodeEnd),'\"')+" then");
      AddVBS("   exit for ");
      AddVBS("  end if  ");
      AddVBS(" if aStartLine > 0 then aDelCount = aDelCount +1 ");
      AddVBS("  next ");
      // AddVBS("  Msgbox aStartLine  ");
      //   AddVBS("  Msgbox aDelCount  ");
      AddVBS("  if aStartLine > 0 then  ");
      AddVBS("  CodeModule.DeleteLines aStartLine,aDelCount+1 ");
      AddVBS("  end if ");
      AddVBS("  CodeModule.AddFromFile "+  AnsiQuotedStr(aCodeFileName,'\"') );
      AddVBS("end if ");
      EndVBS();
    }
    catch( Exception& e )
    {
      gError->Warn( "SetPviewCode出错！" + e.Message );
    }

  //Variant VBComponents;
  //    VBComponents = PptApp.OlePropertyGet("VBE").OlePropertyGet("VBProjects").OleFunction("Item",1).OlePropertyGet("VBComponents");
  //    int SlideItem = 0;
  //    int SlideItemCount = VBComponents.OlePropertyGet("Count");
  //    for(int m=1;m<=SlideItemCount;m++)
  //    {
  //       if( VBComponents.OleFunction("Item",m).OlePropertyGet("Name")== SlideName )
  //       {
  //         SlideItem = m;
  //       }
  //    }
  //    if(SlideItem!=0)
  //    {
  //      Variant CodeModule = VBComponents.OleFunction("Item",SlideItem).OlePropertyGet("CodeModule");
  //      int linesCount = CodeModule.OlePropertyGet("CountofLines");
  //      for(int ii=0;ii<linesCount;ii++)
  //      {
  //        CodeModule.OleFunction("DeleteLines",1);
  //      }
  //      VBComponents.OleFunction("Item",SlideItem).OlePropertyGet("CodeModule").OleFunction("AddFromFile", templatefile.c_str());
}

void MPPtFun::InsertHTextBox()
{
   //Variant bShapes,bShape;
   //   bShapes=PptApp.OlePropertyGet("ActiveWindow").OlePropertyGet("Selection").OlePropertyGet("SlideRange").
   //                   OlePropertyGet("Shapes");
   //   bShape = bShapes.OleFunction("AddTextbox",msoTextOrientationHorizontal,100,100,200,50);
   //   bShape.OlePropertySet("Height",280);
   //   bShape.OlePropertyGet("Line").OlePropertySet("Visible",msoTrue);

   InitVBS();
   AddVBS(" set bShapes = MyPPT.ActiveWindow.Selection.SlideRange.Shapes");
   AddVBS(" set bShape = bShapes.AddTextbox( 1,100,100,200,50 )");
   AddVBS(" bShape.Line.Visible  = true" );
   EndVBS();
}

void MPPtFun::DelSelShape()
{
  //    PptApp.OlePropertyGet("ActiveWindow").OlePropertyGet("Selection").OlePropertyGet("ShapeRange").OleProcedure("Delete");
  InitVBS();
  AddVBS("  MyPPT.ActiveWindow.Selection.SlideRange.Delete");
  EndVBS();
}

String MPPtFun::AddSlide( int aId,int aLayoutType)
{
  //PptApp.OlePropertyGet("ActivePresentation").OlePropertyGet("Slides").OleFunction("Add",index,ppLayoutTitle);
  InitVBS(false);
  AddVBS(" set iSlide =   MyPPT.ActivePresentation.Slides.Add( " + IntToStr( aId)+","+IntToStr(aLayoutType) +")");
  AddVBS(" main = iSlide.Name ");
  EndVBS(false);

  return EvalScript( VBS );
}

void  MPPtFun::SlideRangeLayoutSet( int aType )
{
  // PptApp.OlePropertyGet("ActiveWindow").OlePropertyGet("Selection").OlePropertyGet("SlideRange").OlePropertySet("Layout",ppLayoutTitle);
  InitVBS();
  AddVBS("  MyPPT.ActiveWindow.Selection.SlideRange.Layout = " + IntToStr(aType) );
  EndVBS();
}

//------------------ActWinSelText-----------------------------------------------

String MPPtFun::GetActWinSelTextRangText()
{
  //String Text = PptApp.OlePropertyGet("ActiveWindow").OlePropertyGet("Selection").OlePropertyGet("TextRange").OlePropertyGet("Text");
  InitVBS(false);
  AddVBS(" main= MyPPT.ActiveWindow.Selection.TextRange.Text");
  EndVBS(false);
  return EvalScript(VBS );
}

void MPPtFun::SetActWinSelTextRangText( String aTxt )
{
  InitVBS();
  AddVBS("  MyPPT.ActiveWindow.Selection.TextRange.Text = " +AnsiQuotedStr(aTxt,'\"'));
  EndVBS();
}

void MPPtFun::SetHyperlinkInfo( String AddressStr, String TextToDisplayStr, String SubAddressStr, String ScreenTipStr )
{
  //   hyperlink = PptApp.OlePropertyGet("ActiveWindow").OlePropertyGet("Selection").OlePropertyGet("TextRange").OlePropertyGet("ActionSettings").
  //                OleFunction("Item",1).OlePropertyGet("Hyperlink");
  //          hyperlink.OlePropertySet("Address",NCFileName.c_str());
  //          hyperlink.OlePropertySet("SubAddress","");
  //          hyperlink.OlePropertySet("ScreenTip","");
  //          hyperlink.OlePropertySet("TextToDisplay",NCFile.c_str());

    InitVBS();
    AddVBS(" set hyperlink = MyPPT.ActiveWindow.Selection.TextRange.ActionSettings.Item(1).Hyerlink " );
    AddVBS(" hyperlink.Address = "+AnsiQuotedStr(AddressStr,'\"'));
    AddVBS(" hyperlink.SubAddress = "+AnsiQuotedStr(SubAddressStr,'\"'));
    AddVBS(" hyperlink.ScreenTip = "+AnsiQuotedStr(ScreenTipStr,'\"'));
    AddVBS(" hyperlink.TextToDisplay = "+AnsiQuotedStr(TextToDisplayStr,'\"'));
    EndVBS();
}

int  MPPtFun::SlideShowWinCount()
{
  //PptApp.OlePropertyGet("SlideShowWindows").OlePropertyGet("Count")
   InitVBS(false);
  AddVBS(" main= MyPPT.SlideShowWindows.Count");
  EndVBS(false);

  int  aCount = EvalScript(VBS );
  return aCount;
}
  
void MPPtFun::SetActPreSlidesAdvOnClick( String OnClickVal, String OnTimeVal, String AdvanceTimeVal  )
{
  InitVBS();
  AddVBS("sildecount = MyPPT.ActivePresentation.Slides.count");
  AddVBS("  for  i=1 to sildecount ");
  AddVBS("  MyPPT.ActivePresentation.Slides.Item(i).SlideShowTransition.AdvanceOnClick ="+ OnClickVal);
  AddVBS("  MyPPT.ActivePresentation.Slides.Item(i).SlideShowTransition.AdvanceOnTime = "+ OnTimeVal);

  if ( AdvanceTimeVal !="" )
     AddVBS("  MyPPT.ActivePresentation.Slides.Item(i).SlideShowTransition.AdvanceTime = "+ AdvanceTimeVal);
     
  AddVBS(" next ");
  EndVBS();
}

void  MPPtFun::ActPreSlideShowSetRun()
{
  //  Variant SlideShowWindow;
  //		PptApp.OlePropertyGet("ActivePresentation").OlePropertyGet("SlideShowSettings").OlePropertySet("ShowType",ppShowTypeWindow);//ppShowTypeSpeaker
  //		PptApp.OlePropertyGet("ActivePresentation").OlePropertyGet("SlideShowSettings").OlePropertySet("LoopUntilStopped",False);
  //		SlideShowWindow =PptApp.OlePropertyGet("ActivePresentation").OlePropertyGet("SlideShowSettings").OleFunction("Run");

  InitVBS();
  AddVBS(" MyPPT.ActivePresentation.SlideShowSettings.ShowType = 2");
  AddVBS(" MyPPT.ActivePresentation.SlideShowSettings.LoopUntilStopped = 0 ");

  //PptApp.OlePropertyGet("ActivePresentation").OlePropertyGet("SlideShowSettings").OlePropertySet("ShowWithNarration",msoFalse);
  //PptApp.OlePropertyGet("ActivePresentation").OlePropertyGet("SlideShowSettings").OlePropertySet("ShowWithAnimation",msoTrue);

  AddVBS(" MyPPT.ActivePresentation.SlideShowSettings.ShowWithNarration = 0 ");
  AddVBS(" MyPPT.ActivePresentation.SlideShowSettings.ShowWithAnimation = -1 ");
  AddVBS(" MyPPT.ActivePresentation.SlideShowSettings.Run  ");
  EndVBS();
}

void MPPtFun::SlideShowWinView( String aProcedureName )
{
  //PptApp.OlePropertyGet("SlideShowWindows").OleFunction("Item",1).OlePropertyGet("View").OleProcedure("Next");
  InitVBS();
  AddVBS(" MyPPT.SlideShowWindows.Item(1).View."+aProcedureName);
  EndVBS();
}
  
void MPPtFun::ReViewActPpt(int aSleepCount )
{
  int sildecount = ActPreSlidesCount();
  for( int i=1;i< sildecount;i++)
    SlideShowWinView("Next");

  Sleep( (unsigned long)aSleepCount );
  SlideShowWinView("Exit");
}
   
int MPPtFun::GetRelDelta( TStrings * aNameList )
{
  if ( aNameList == NULL || aNameList->Count<=1)
    return 0;
  return (aNameList->Count-1)*C_PosDelta;
}


//----------Add by sxd 2014-----------------------------------------------------

//String MPPtFun::GetActivePPTFileName()
//{
//  return GetObjProperty( PptApp,"ActivePresentation.Name" );
//}

//String MPPtFun::GetActivePPTFileName_NoExt()
//{
//  return ChangeFileExt( GetActivePPTName(),"" );
//}

#pragma package(smart_init)
