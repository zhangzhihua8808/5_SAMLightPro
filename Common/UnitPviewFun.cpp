//---------------------------------------------------------------------------

#include "UnitAll.h"
#pragma hdrstop

#include "UnitProeEngine.h"

#define Pi 3.1415926535

float C_PView_Left = 30;                         //PView控件插入的位置坐标
float C_PView_Top = 30;
float C_PView_Width = 629.375;
float C_PView_Height = 436.625;

//float Bt_Width = 39.625;
//float Bt_Height  = 22.625;

float C_PView_Left_XS = 200 ;
float C_PView_Top_XS = 80;
float C_PView_Width_XS = 420;
float C_PView_Height_XS = 340;


//---------------------------------------------------------------------------
void SetMdlName( String aFName  )
{
   TStrings * OriInfo = new TStringList;
   const String C_ModelName = "C:/WINDOWS/system32/ModleFileName.txt"  ;
   OriInfo->Add(aFName);
   OriInfo->SaveToFile(C_ModelName);
   OriInfo->Free();

}

TStrings *GetOrientInfo(  String aFName, TCppWebBrowser *WebBrowser1 )
{
    const String C_WebName = "GetOrientInfoByFile.html";
    const String C_OrientInfo ="C:/WINDOWS/system32/OrientInfo.txt";

    SetMdlName( aFName );
    DeleteFile( C_OrientInfo );

    wchar_t tmp[200];
    String aWebName = ExtractFilePath(Application->ExeName)+C_WebName;
    WebBrowser1->Navigate( aWebName.WideChar(tmp,200) );

    //int  aMax = 0;
    TStrings * OriInfo = new TStringList;
    while( FileExists(  C_OrientInfo ) == false )
    {
      Sleep((unsigned long)500);
      //aMax++;
      //if( aMax > 5) return OriInfo;
      Application->ProcessMessages();
    }
    OriInfo->LoadFromFile(C_OrientInfo);
    return   OriInfo;
}

void CreatePViewOrientCode(String PviewName,String ViewState,String OrientState,
                     String Oname1, String Otype1,String CodeFile )
{
      TStringList* MyList1 = new TStringList();
      try
      {
        MyList1->Add("Private Sub "+PviewName+"_OnLoadComplete()");
        MyList1->Add( PviewName+".ListViewStates");
        MyList1->Add( PviewName+".SetViewState \""+ViewState+"\", \""+OrientState+"\"");
        MyList1->Add( "Set orientations = "+PviewName+".GetOrientations");
        MyList1->Add( "orientations.SetOrientation \""+Oname1+"\", \""+Otype1+"\"");
        MyList1->Add( "End Sub");
        MyList1->SaveToFile( CodeFile );
      }
      __finally
      {
        delete MyList1;
      }

}



//---------------------------------------------------------------------------
//void  ChangeInToMm(double m1[4][4])
//{
//  int i, j;
//  for(i=0;i<3;i++)
//  {
//    for(j=0;j<3;j++)
//    {
//      m1[i][j] = m1[i][j] * 25.4;
//    }
//  }
//}

//---------------------------------------------------------------------------
//void  ChangeMmToIn(double m1[4][4])
//{
//  int i, j;
//  for(i=0;i<3;i++)
//  {
//    for(j=0;j<3;j++)
//    {
//      m1[i][j] = m1[i][j] / 25.4;
//    }
//  }
//}


//------------------------------------------------------------------------------
//功能：清除重复的PView代码
//------------------------------------------------------------------------------

void RmvSameWebCode( String aPViewName,String aWebCodeFileName )
{
  if( FileExists( aWebCodeFileName ) == false )
    return;

  TStringList* aList_WebCode = new TStringList();
  aList_WebCode->LoadFromFile(aWebCodeFileName);

  Strings_RmvSection( aList_WebCode, 0, C_PViewWebCodeStart + aPViewName , C_PViewWebCodeEnd );

  /*int aS=-1, aE=-1;

  for ( int i =0 ; i<aList_WebCode->Count ; i++ )
  {
    String aCodeLine =  aList_WebCode->Strings[i];

    if( aCodeLine.Pos( C_PViewWebCodeStart + aPViewName ) > 0 )
       aS=i;

    if( aS>=0  && aCodeLine.Pos( C_PViewWebCodeEnd ) > 0 )
    {
      aE=i;
      break;
    }
  }

  if( aS>=0 && aE>=0 )
  {
    for ( int i =aE ; i>=aS; i-- )
      aList_WebCode->Delete(i);
  }  */

  aList_WebCode->SaveToFile(aWebCodeFileName);
  delete aList_WebCode;
}


//-----------------By SXD-------------------------------------------------------

//功能：获得aDirFileName模型中的Unit和Part信息
TStrings* GetAllPartAndUnit( String aModelFullName )
{
  //提取aDirFileName中的”单位“信息到aList_AllPartUnit
  //{ "/-1\r\nmm\r\n/38\r\nmm\r\n/47\r\nmm\r\n/50\r\nmm\r\n" }

  String aStr_AllPartUnit = G_ProeEngine->ReadMdlUnit( aModelFullName );
  return StringToStringList( aStr_AllPartUnit, "\r\n" );
}

TStrings* GetPartIDList( TStrings* aList_AllPartUnit )
{
  //提取aStr_AllPartUnit中的零件ID信息
  TStrings* aPartIdList = new TStringList;

  for( int i=2; i<aList_AllPartUnit->Count; i=i+2 )
    aPartIdList->Add( aList_AllPartUnit->Strings[i] );

  return  aPartIdList;
}

TStrings* GetPartIDList(  String aModelFullName  )
{
  TStrings* aList_AllPartUnit = GetAllPartAndUnit(aModelFullName);
  TStrings* aPartIdList = GetPartIDList(aList_AllPartUnit);
  delete aList_AllPartUnit;
  return aPartIdList;
}


//------------------------------------------------------------------------------
//功能：去除Proe文件名称的后缀
//例子： “xx.prt.1” --> "xx.prt"  "xx.asm.1" -->"xx.asm"
//参数：[ aModelName -- 例如：“c:\\tt\\xx\\8_18.asm.1” ]
//返回：[ "c:\\tt\\xx\\8_18.asm" ]
//------------------------------------------------------------------------------

String GetAsmFileNameNoVer( String aModelFullName )
{
    if( aModelFullName.Pos(".asm.") )
      return aModelFullName.SubString( 0, aModelFullName.Pos(".asm") + 3 );
    else if(aModelFullName.Pos(".prt."))
      return  aModelFullName.SubString( 0, aModelFullName.Pos(".prt") + 3 );
    else
      return aModelFullName;
}

//------------------------------------------------------------------------------
//参数：[ aModelName -- 例如：“c:\\tt\\xx\\8_18.asm.1” ]
//返回：[ "8_18" ]
//------------------------------------------------------------------------------

String EtractAsmFileNameNoExt( String aModelFullFileName )
{
    return ChangeFileExt( ExtractFileName( GetAsmFileNameNoVer(aModelFullFileName) ),"" );          //8_18
}

bool IsAssemFile( String aFileName )
{ 
  return LowerCase( aFileName ).Pos(".asm") > 0;
}

bool IsPrtFile( String aFileName )
{
   return LowerCase( aFileName ).Pos(".prt") > 0;
}


//------------------------------------------------------------------------------
//功能：搜索Part的Uint
//参数：
//  aPartAndUnit -- 存放零件号和Unit的字符串
//  aPartAndUnit格式
//  /-1
//   mm
//  /38
//  nmm
//  ......
//  aPartId -- 查找关键字，例如 "/37"
//------------------------------------------------------------------------------
String FindUnitByPartId( TStrings* aPartAndUnit, String aPartId )
{
  for( int j=0; j<aPartAndUnit->Count; j=j+2 )
  {
    if( aPartId == aPartAndUnit->Strings[j] )
      return aPartAndUnit->Strings[j+1];
  }
  return "mm";
}

//功能：获得装配的Unit
String GetAsmUnit( TStrings* aPartAndUnit )
{
  if( aPartAndUnit->Count < 2 )
    return "mm";
  return aPartAndUnit->Strings[1];
}


//------------------------PRS---------------------------------------------------

//---------------------------------------------------------------------------
//功能：将矩阵的比例系数Scale设置回1
//---------------------------------------------------------------------------

/*void PRSMatrix_ScaleToOne( double PRSMatrix[9] )
{
  double aScale = fabs(PRSMatrix[8]);

  if( aScale == 0 )
    return;

  //位置除以Scale
  for( int i=0; i<3; i++)
    PRSMatrix[i] = PRSMatrix[i] / aScale;

  //角度不变

  //Scale设置为1
  for(int j=6; j<9; j++)
    PRSMatrix[j] = 1;
}*/

//功能：矩阵归一化处理1
void PRSMatrix_Normalize( double PRSMatrix[9] )
{
  double aScl = fabs(PRSMatrix[8]);
  if( aScl==0.0 )
    aScl=1.0;
    
  for( int i = 0; i < 3; i++ )
    PRSMatrix[i] = PRSMatrix[i] / aScl;
  for( int j = 6; j < 9; j++ )
    PRSMatrix[j] = 1;
}

//---------------------------------------------------------------------------
//void SetPRSMatrixToZero(double PRSMatrix[9])
//{
//  for(int i = 0; i < 9; i++)
//    PRSMatrix[i] = 0;
//}

//---------------------------------------------------------------------------
//void SetPRSMatrixToZero(double PvsMatrix[4][4])
//{
//  for(int i = 0; i < 4; i++)
//  {
//    for(int j = 0; j < 4; j++)
//      PvsMatrix[i][j] = 0;
//  }
//}

//---------------------------------------------------------------------------
//功能： 字符串分割 "1.0 0.8 0.5 0.0 1.0 1.2 0.7 0.6" --> PRSMatrix[9]
//---------------------------------------------------------------------------

void PRSMatrix_LoadStr( String aString, double PRSMatrix[9] )
{

  for( int i=0; i<8; i++ )
     PRSMatrix[i] = 0.0;

  TStrings* aItems = splitToStrings( aString, " ", false );

  if( aItems->Count<9 )
    return;

  for( int i=0; i<=8; i++ )
    PRSMatrix[i] = StrToFloatDef(  aItems->Strings[i], 0 );

  //for( int i = 0; i < 8; i++ )
  //{
  //  String StrMatrix = aString.SubString(1, aString.Pos(" "));
  //  aString.Delete(1, aString.Pos(" "));
  //  PRSMatrix[i] = StrToFloatDef( StrMatrix,0 ); //ls 0911
  //}
  //PRSMatrix[8] = StrToFloat(aString);
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

String PRSMatrix_ToStr(double PRSMatrix[9])
{
  String StrPvsMatrix = FloatToStr( PRSMatrix[0] );

  for( int i = 1; i < 9; i++ )
    StrPvsMatrix =  StrPvsMatrix + " " + FloatToStr( PRSMatrix[i] );
  return StrPvsMatrix;
}


//-----------------PRSMatrix----------------------------------------------------

void PRSMatrix_SetScale( double PRSMatrix[9], double aScale )
{
  for(int i = 0; i < 3; i++)
    PRSMatrix[i] = PRSMatrix[i] * aScale;
}

//void PRSMatrix_ScalePosition( double PRSMatrix[9], double aScl )
//{
//  for(int i=0; i<3; i++)
//    PRSMatrix[i] = PRSMatrix[i] * aScl;
//}

void PRSMatrix_MMToM( double PRSMatrix[9] )
{
  PRSMatrix_SetScale( PRSMatrix, 0.001 );
}

//void PRSMatrix_MM_To_M( double PRSMatrix[9] )
//{
//    PRSMatrix_ScalePosition( PRSMatrix, 0.001 );
//}

void PRSMatrix_INToM( double PRSMatrix[9] )
{
  PRSMatrix_SetScale( PRSMatrix, 0.0254 );
}

//void PRSMatrix_IN_To_M( double PRSMatrix[9] )
//{
//  PRSMatrix_ScalePosition( PRSMatrix, 0.0254 );
//}

void PRSMatrix_UnitToM( double aPRSMatrix[9], String aUnit )
{
  if( aUnit == "mm")
    PRSMatrix_MMToM(aPRSMatrix);
  else
    PRSMatrix_INToM(aPRSMatrix);
}

//void PRSMatrix_Unit_To_M( double PRSMatrix[9], String aValue_Unit )
//{
//  if( LowerCase(aValue_Unit) == "mm" )
//    PRSMatrix_MM_To_M(PRSMatrix);
//  else
//    PRSMatrix_IN_To_M(PRSMatrix);
//}



//---------------------------------------------------------------------------
void PRSMatrix_StrToArray( String aString, double aPRSMatrix[9] )
{
  PRSMatrix_SetToZero( aPRSMatrix );

  TStrings* aItems = splitToStrings( aString, " " );

  for( int i=0; i<Math::Min( aItems->Count, 9 ); i++ )
    aPRSMatrix[i] = StrToFloatDef( aItems->Strings[i], 0.0 );

  delete aItems;
}

//---------------------------------------------------------------------------
String PRSMatrix_ArrayToStr( double PRSMatrix[9] )
{
  String aStrMat;
  for( int i = 0; i < 9; i++ )
  {
    if( i == 0 )
      aStrMat = FloatToStr( PRSMatrix[i] );
    else
      aStrMat =  aStrMat + " " + FloatToStr(PRSMatrix[i]);
  }
  return aStrMat;
}

//---------------------------------------------------------------------------
void PRSMatrix_SetToZero( double PRSMatrix[9] )
{
  for(int i = 0; i < 9; i++)
    PRSMatrix[i] = 0;
}


//---------------------------------------------------------------------------
void PvsMatrix_SetToZero(double PvsMatrix[4][4])
{
  for(int i = 0; i < 4; i++)
    for(int j = 0; j < 4; j++)
      PvsMatrix[i][j] = 0;
}

//-------------------------View-------------------------------------------------

//----------------------------------------------------------------------------
//功能：获得aViewName的Martrix信息
//参数：[ aViewName -- 窗口的名称 ]
//返回：
//   VIEW0001
//   1.5625 0 0 0 0 1.5625 0 0 0 0 1.5625 0 -336.343544407895 -256.941303453947 0 1
//   VIEW0001viewMatrix
//   -1.1415 1.2885 3.0394739009509 0 2.2139 -2.0868 1.7162 0 2.448 2.4873 -0.1347 0 606.239 522.15192 -1642.78898392254 1
//----------------------------------------------------------------------------

TStrings* GetViewMatrix( String aViewName )
{
   TStrings* aViewMatrixList = new TStringList;

   //返回矩阵信息
   String aNameMatrix = G_ProeEngine->ViewRefit( "",aViewName );

   //  aNameMatrix格式
   //   WindowMatrix=1,0,0,0,;0,1,0,0,;0,0,1,0,;0,0,0,1,;
   //   viewMatrix=-0.97231064,0,0,0,;0,0.9723,0,0,;0,0,-0.9723,0,;819.058,275.637772302056,-1987.44808898637,1,;

   //输出
   aViewMatrixList->Add( aViewName );
   aViewMatrixList->Add( GetMatrixStr( aNameMatrix,"WindowMatrix" ) );
   aViewMatrixList->Add( aViewName+"viewMatrix" );
   aViewMatrixList->Add( GetMatrixStr( aNameMatrix,"viewMatrix" ) );

   return aViewMatrixList;
}


//--------------------------------------------------------------------
//功能：aViewMatrix的格式转换
//  aOldViewMat格式：
//   WindowMatrix=1,0,0,0,;0,1,0,0,;0,0,1,0,;0,0,0,1,;
//   viewMatrix=-0.97231064,0,0,0,;0,0.9723,0,0,;0,0,-0.9723,0,;819.058,275.637772302056,-1987.44808898637,1,;
//  返回：（zhuan.exe的格式）
//   VIEW0001
//   1.5625 0 0 0 0 1.5625 0 0 0 0 1.5625 0 -336.343544407895 -256.941303453947 0 1
//   VIEW0001viewMatrix
//   -1.1415 1.2885 3.0394739009509 0 2.2139 -2.0868 1.7162 0 2.448 2.4873 -0.1347 0 606.239 522.15192 -1642.7889 1
// [ aFlag -- WindowMatrix 或 viewMatrix ]
//--------------------------------------------------------------------

String GetMatrixStr( String aOldViewMat,String aFlag )
{
  //获得aFlag行
  String aStr = Get_ListItem_ByName_StringsStr( aOldViewMat, aFlag, "=", "" );

  aStr = ReplaceStr( aStr, ";", "" );                        //去除;       
  aStr = ReplaceStr( aStr, ",", " " );                       //用" "代替","
  return aStr;

  //while(aStr.Pos(";"))     //邱博晋
  //  aStr=aStr.Delete(aStr.Pos(";"),1);

 // String aStrNew="";
 // TStrings* aItems = splitToStrings( aStr, ",", false );

  //for( int i=0;i<aItems->Count;i++)
  //  aStrNew = aStrNew+ aItems->Strings[i]+" ";

  //delete aItems;
  //return aStrNew;
}

float GetViewScale( String aViewName )
{
  TStrings* aMatrixNew = GetViewMatrix( aViewName );

  if( aMatrixNew->Count<2 )
    return 1.0;

  //Sleep( (unsigned long)1000 );
  int len = aMatrixNew->Strings[1].Pos(" ");

  double aScale = StrToFloatDef( aMatrixNew->Strings[1].SubString(1,len), 1.0 );
  delete aMatrixNew;

  return aScale;
}


//----------------------------------------------------------------------------
//功能：获取aOrietationNameList的非基本视图的矩阵信息
//输出：
//  VIEW0001
//  1.5625 0 0 0 0 1.5625 0 0 0 0 1.5625 0 -336.343544407895 -256.941303453947 0 1
//  VIEW0001viewMatrix
//  -1.1415 1.28858 3.0394739009509 0 2.21399094449 -2.08 1.7162 0 2.448 2.487 -0.13 0 606.23 522.151 -1642.788 1
//  VIEW0002
//  1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1
//  VIEW0002viewMatrix
//  -2.3020 -1.684 -1.658 0 -1.4798 -0.7780 2.8444 0 -1.843 2.7283 -0.21264 0 434.7334 545.080457126513 -1535.08722642955 1
// .....
//----------------------------------------------------------------------------

TStrings* OrientList_GetNoneBasicViews( TStrings* aOrietationNameList )
{
    //去除"前"、"后"、"左"、"右"、"上"、"下"视图
    TStrings* aWindowMatrixList = new TStringList;
    for( int i=0; i<aOrietationNameList->Count; i++ )
    {
      String aOrientName = aOrietationNameList->Strings[i];
      if( isBasicOrietationName( aOrientName ) == true )
        continue;

      TStrings* aStrings = GetViewMatrix( aOrientName );
      aWindowMatrixList->AddStrings( aStrings );
      delete aStrings;
    }
    return aWindowMatrixList;
}


//qbj20130815
//判断OrietationName是否为基本OrietationName

bool isBasicOrietationName( String aViewName )
{
  TStrings* aBasicOrietationNameList = BasicOrietationName();
  for( int i=0; i<aBasicOrietationNameList->Count; i++ )
  {
    if( aViewName == aBasicOrietationNameList->Strings[i])
      return true;
  }
  return false;
}

TStrings* BasicOrietationName()
{
  TStrings* aBasicOrietationNameList = new TStringList;
  aBasicOrietationNameList->Add("BACK");
  aBasicOrietationNameList->Add("BOTTOM");
  aBasicOrietationNameList->Add("DEFAULT");
  aBasicOrietationNameList->Add("FRONT");
  aBasicOrietationNameList->Add("LEFT");
  aBasicOrietationNameList->Add("RIGHT");
  aBasicOrietationNameList->Add("TOP");
  return aBasicOrietationNameList;
}




//--------------------PVSAndModelFile-------------------------------------------

String FullModelNameToFullPvsPath( String aModelFullName )
{
  if( IsPrtFile( aModelFullName ) )
    return FullPartNameToFullPVSPath( aModelFullName );
  else
    return  FullAssemNameToFullPVSPath( aModelFullName );
}

//-------------------------------------------------------
//输入："c:\t\x\8_18.asm.1"
//返回："c:\t\x\8_18_pvs"
//-------------------------------------------------------

String FullAssemNameToFullPVSPath( String aModelFullName )
{
    return aModelFullName.SubString( 1,aModelFullName.Pos(".asm")-1 ) + "_pvs";
}

String FullPartNameToFullPVSPath( String aModelFullName )
{
    return aModelFullName.SubString( 1, aModelFullName.Pos(".prt")-1 ) + "_pvs";
}

String SYS_PVSTempFile()
{
  return ApplicationPath()+"\\sys\\prt0008.ed";
}


//---------------------------------------------------------------------------
//功能：将Fra文件中的矩阵变换式（4*4)转换为关于目标位置、角度和比例(P,R,S)(3*3)矩阵的exe文件（朱路程用VC做）
//      利用了VEGA提供的接口函数
//---------------------------------------------------------------------------

String APPName_FROEMatToPRS( String aFraFileName )     //邱博晋
{
  return ApplicationPath() + "\\zhuan.exe " + aFraFileName;
}

String APPName_FROEFraToPRS( String aFraFileName )
{
  return ApplicationPath() + "\\zhuan16To9.exe " + aFraFileName;
}

String APPName_PRSToPVS( String aPRSFileName )
{
  return ApplicationPath() + "\\zhuan9_4.exe " + aPRSFileName;
}

String APPName_PRSToPVS_ExplodeViewAndOrientView( String aPRSFileName )
{
   return ApplicationPath() + "\\zhuan3344.exe " + aPRSFileName;
}

String PPTCodeFile()
{
  return ApplicationPath() + "\\template.txt";
}


//--------------------其它 -----------------------------------------------------

void ScalePosByUnit( bool aIsMdlMm, String XsecOr[3], double XsecO[3] )
{
  if( aIsMdlMm )
  {
    for( int j=0; j < 3; j++)
      XsecO[j] = StrToFloatDef( XsecOr[j], 0  ) / 1000;
  }
  else
  {
    for(int aa = 0; aa < 3; aa++)
      XsecO[aa] = StrToFloatDef( XsecOr[aa], 0  ) * 0.0254;
  }
}


//------------------------------------------------------------------------
//string转成Liststring分隔符为sign
//{ "/-1\r\nmm\r\n/38\r\nmm\r\n/47\r\nmm\r\n/50\r\nmm\r\n" }
//------------------------------------------------------------------------

TStrings* StringToStringList( String aOldstr, String aSplitter, bool IsUtf8 )
{
   //";"去除
   //aOldstr = ReplaceStr( aOldstr, ";", "" );

   //代码分割
   TStrings* aStrings = splitToStrings( aOldstr,aSplitter,false );

   //码制转换
   if( IsUtf8==true )
     Strings_Utf8ToAnsi( aStrings );

   return aStrings;
}

//---------------------------------------------------------------------------
//判断是否为矩阵
//---------------------------------------------------------------------------
bool IsMatrix( String aLine )
{
  if( aLine == "" )
    return true;
  return IsIn( aLine.SubString(0,1), "-;1;2;3;4;5;6;7;8;9;0", ";" );
}

String ModelFileNameToPVSFileName( String aModelFullName )
{
    String dir_pvs = GetAsmFileNameNoVer( aModelFullName ); //asm文件名

    String dir_pvs1 = ChangeFileExt( dir_pvs,"_pvs" );       //8_18_pvs,存储PVS文件
    String dir_pvs2 = ExtractFileName( dir_pvs );            //8_18.asm
    String dir_pvs3 = ChangeFileExt( dir_pvs2,"" );          //8_18

    return  dir_pvs1+"\\"+dir_pvs3+ ".pvs";
}

#pragma package(smart_init)
