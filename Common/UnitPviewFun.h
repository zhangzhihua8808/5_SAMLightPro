//---------------------------------------------------------------------------

#ifndef UnitPviewFunH
#define UnitPviewFunH

//---------------------------------------------------------------------------
#include "SHDocVw_OCX.h"

const String C_RscPath = ExtractFilePath(Application->ExeName)+"rsc\\";

extern float C_PView_Left;
extern float C_PView_Top;
extern float C_PView_Width;
extern float C_PView_Height;

//extern float Bt_Width;
//extern float Bt_Height;

extern float C_PView_Left_XS;
extern float C_PView_Top_XS;
extern float C_PView_Width_XS;
extern float C_PView_Height_XS;

String EtractAsmFileNameNoExt( String aModelFullFileName );

TStrings * StringToStringList( String aOldstr, String aSplitter, bool IsUtf8=true );

void SetMdlName( String aFName  );
TStrings *GetOrientInfo(  String aFName ,TCppWebBrowser *WebBrowser1);

void CreatePViewOrientCode(String PviewName,String ViewState,String OrientState,
                     String Oname1, String Otype1,String CodeFile );



//void ChangeInToMm(double m1[4][4]);
//void ChangeMmToIn(double m1[4][4]);

bool IsAssemFile( String aFileName );
bool IsPrtFile( String aFileName );


//处理Web中插入的代码, 改自WebCodeFile( String PViewName,String WedAddMsg)
//去除 aWebCodeFileName文件的WebCode中PViewName段落
void RmvSameWebCode( String PViewName,String aWebCodeFileName );

//功能：获得aDirFileName模型中的Unit和Part信息
TStrings* GetAllPartAndUnit( String aModelFullName );   
TStrings* GetPartIDList( TStrings* aList_AllPartUnit );
TStrings* GetPartIDList(  String aModelFullName  );

String GetAsmFileNameNoVer( String aModelFullFileName );

//-------Unit----------------------

void ScalePosByUnit( bool aIsMdlMm, String XsecOr[3], double XsecO[3] );

String FindUnitByPartId( TStrings* aPartAndUnit, String aPartId );
String GetAsmUnit( TStrings* aPartAndUnit );

//------------------PRS---------------------------------------------------------
//void SetPRSMatrixToZero(double PRSMatrix[9]);
//void SetPRSMatrixToZero(double PvsMatrix[4][4]);

void PRSMatrix_LoadStr(String aString, double PRSMatrix[9]);
String PRSMatrix_ToStr(double PRSMatrix[9]);

//void PRSMatrix_ScaleToOne(double PRSMatrix[9]);
//void PRSMatrix_Unit_To_M( double PRSMatrix[9], String aValue_Unit );
//void PRSMatrix_ScalePosition( double PRSMatrix[9], double aScl );

//void PRSMatrix_MM_To_M(double PRSMatrix[9]);
//void PRSMatrix_IN_To_M(double PRSMatrix[9]);

//PRSMatrix
void PRSMatrix_UnitToM( double PRSMatrix[9], String aUnit );
void PRSMatrix_MMToM( double PRSMatrix[9] );
void PRSMatrix_INToM( double PRSMatrix[9] );
void PRSMatrix_SetScale( double PRSMatrix[9], double aScale );

void PRSMatrix_Normalize( double PRSMatrix[9] );
void PRSMatrix_StrToArray( String aString, double aPRSMatrix[9] );
String PRSMatrix_ArrayToStr( double PRSMatrix[9] );
void PRSMatrix_SetToZero( double PRSMatrix[9] );

//-------------PvsMatrix--------------------------------------------------------
void PvsMatrix_SetToZero(double PvsMatrix[4][4]);

//------View--------------------------------------------------------------------

TStrings* GetViewMatrix(String aViewName);
float GetViewScale( String aViewName );

TStrings* OrientList_GetNoneBasicViews( TStrings* aOrietationNameList );
bool isBasicOrietationName( String aViewName );
TStrings* BasicOrietationName();

String GetMatrixStr(String aList,String sign);
bool IsMatrix( String aLine );

//----------------PvsAndModel FileName------------------------------------------

String FullModelNameToFullPvsPath( String aModelFullName );
String FullAssemNameToFullPVSPath( String aModelFullName );
String FullPartNameToFullPVSPath( String aModelFullName );

String SYS_PVSTempFile();

String APPName_FROEMatToPRS( String aFraFileName );
String APPName_FROEFraToPRS( String aFraFileName );
String APPName_PRSToPVS( String aFraFileName );
String APPName_PRSToPVS_ExplodeViewAndOrientView( String aPRSFileName );

String ModelFileNameToPVSFileName( String aModelFullName );

String PPTCodeFile();

#endif
