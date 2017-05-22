//---------------------------------------------------------------------------

#ifndef UnitTool_SingleH
#define UnitTool_SingleH
//------------------------头文件------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
#include <ToolWin.hpp>
#include <ImgList.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <IdGlobal.hpp>
#include  <tlhelp32.h>
#include <Grids.hpp>
#include <fstream>
#include "values.h"


using namespace std;

class MTreeNode_ModeObject;
class MParaMapElementItem;
class MListToTreePositions;
class MDMSourceItem;
class MDMSourceItems;
class MManualProject;
class MLayerDataTreeNode;
class MMapElement_ExcelImporter;
class MManualProjectDoc;
class MLaserPen;
class MAMProject;
class MPartProject;

extern int G_SecBgn;
extern int G_SecEnd;

extern const float kPi;
extern const float k2Pi;
extern const float kPiOver2;
extern const float k1OverPi;
extern const float k1Over2Pi;
extern const float kPiOver180;
extern const float k180OverPi;


const String C_CmpManual = "结构手册";
const String C_DocManual = "服务手册";

//二进制文件读写类
long   save_string(ofstream& aFile,String aStr);
String load_string(ifstream& aFile);   //long size
long  save_long(ofstream& aFile,long l);
long  load_long(ifstream& aFile);


inline float	degToRad(float deg) { return deg * kPiOver180; }
inline float	radToDeg(float rad) { return rad * k180OverPi; }

//------------------------------------------------------------------------------
template <class T>
void SafeDelete(T** x)
{
  if( *x==NULL )
    return;
  delete *x;
  *x=NULL;
}

String  GetSaveProjectDir();

bool DelDirFiles( String dir  );       //该方法较好
bool IsRootDir( String aDir );
String MaskMergePathAndFileName( String aPathName, String aFileName );
bool DelADir(AnsiString dir);
String ParentDir( String aPath );

void DebugFile_New( String aFileName );
void DebugFile_Add( String aFileName, String aStr );

void Strings_ClingLines1(TStrings* aOldStrings,String Suffix,bool IsTrim);
TStrings* Strings_ClingLines(TStrings* aOldStrings,String Suffix,bool IsTrim);
void CopyStrings ( TStrings* aDest, TStrings* aSrc, int aBgn=0, int aEnd=MAXINT );

TTreeNode* FindTreeViewNodeByData( TTreeView* aTree, void* aData );

/*
MDataModuleTreeNode*  InsertTreeNode_DataModule(MManualProjectDoc* aOwner,
                          MDataModuleTreeNode* aParentTreeNode,String aNodeName);
*/

void DelStringsItemByObject(  TStrings* aStrings, void* aObject  );
void DelStringsItem( TStrings* aStrings, int aIndex );

void  UpdatePictureGroup(String aBmName,MDMSourceItems*  aDMItems);
void  UpdatePictureGroup(MDMSourceItem*  aItem);
bool  IsCanLoad(String aPicFileName);

void SetOnlyPageControlVis( TPageControl* aPage, String aName, bool aVis, bool IsManual=true);
TTabSheet * FindPageByName(TPageControl* aPage, String aTabName);
void SetOnlyPageControlVis( TTabSheet* aSheet, bool aVis, bool IsManual=true);

String   TStringsToString(TStrings*  aStrings,String  aSplitChar);

MDMSourceItem*    GetSelectedDMSourceItem( TListBox* aList );

void SetPageControlVis( TPageControl* aPage, bool aVis );
void SetOnlyPageControlVis( TPageControl* aPage, TTabSheet* aSheet, bool aVis, bool IsManual=true);

void SetPageVisble( TPageControl* aPage, bool aVis,
                    TTabSheet **aSheet_array, const int aSheet_array_Size,
                    bool IsManual    );


//------------------------------------------------------------
String ExtractFileName_NoDot( String aFileName );
String ExtractFilePath_Format( String aFileName );
String FormatDir( String aPath );
String ProjectDirName(String  aProjectFileName);




void  SaveParaMapInfoToWord(String  aStr);

//void  SetUnicodeType(TRichViewEdit* aRichViewEdit,TRVStyle *aRVStyle);

void MaskProcessException( Exception& e, String aAddStr );
void MaskThrowException( String aErrorStr, String aAddStr, bool IsInAction );

void CheckNULLStr( String aStr, String aWarn );
MTreeNode_ModeObject*  GetSelectedModeNode( TListBox* aList );
MTreeNode_ModeObject* GetSelectedModeNode(TTreeView* aTree );
void* GetTreeViewSelectedNodeData( TTreeView* aTree );

String  MemoVarPostProcess(String aMemoVar,String aDiv="@@");
void SetImagePictureNULL(TImage* aImage);
String AskFileName( String aTitle, String aDefDir, String aFilter, String aDefaultExt );
String Get_ListItem_ByName_StringsStr( String aStringsStr, String aItemName, String aSplitter, String aDefault, bool aIsTrim=true );
String Get_ListItem_ByName_Str( String aStringsStr, String aDivItem, String aItemName, String aSplitter, String aDefault, bool aIsTrim=true );

void ListToTree( TStrings* aListName, TStrings* aListParName, TStrings* aListShowName,
                 TTreeView* aTree, String aRootStr, bool IncludeRoot, bool aIsClear=true );
void ListToTree( TStrings* aListName, TStrings* aListParName,
                 TTreeView* aTree, String aRootStr="", bool IncludeRoot=true, bool aIsClear=true  );

void ListToTree_Basic( TTreeNode* aNodeIns,
                       TStrings* aListName, TStrings* aListParName, TStrings* aListShowName,
                       TTreeView* aTree, String aRootStr, unsigned int aRootTag,
                       bool IncludeRoot, String aType, bool aIsClear );

TStrings* _ListToTree_FindRootPos( TStrings* aStrings, String aRootStr, unsigned int aRootTag, String aType );

void ListToTree_Basic( TTreeNode* aNodeIns,
                       TStrings* aListName, TStrings* aListParName, TStrings* aListShowName,
                       TTreeView* aTree, int aRootPos,
                       bool IncludeRoot, String aType, bool aIsClear );

MListToTreePositions* _ListToTree_CreateRelation( TStrings* aListName, TStrings* aListParName,
                                                  String aType );

void _ListToTree( TStrings* aListName, MListToTreePositions* aListParPos, TStrings* aListShowName,
                  int aRootPos, TTreeView* aTree, TTreeNode* aParentNode, int& aCurCount );

unsigned int StringList_Tag( TStrings* aList, int i );

TList* GetTreeNodes( TTreeView* aTree );

void Strings_Utf8ToAnsi( TStrings* aList );


TTreeNode* TreeNode_AddChild( TTreeNode* aNode, String aName );
bool GetNodeChecked( TTreeNode *ANode );
TList* GetTreeNodeNodes( TTreeNode* aNode, bool IsSearchNext=false );

void _GetTreeNodes( TTreeNode* aNode, TList* aNodes, int& aCurCount );

void List_MaskAdd( TList* aList, void* aItem );

String Strings_GetMaxName( String aCsLab, TStrings* aCsNames );

int Strings_GetMaxId( TStrings* aNames, String aPrefix );

String String_UpdateNamedItem( String aOldStr, String aNewItems,
                                     String aSpItems, String aSpNameAndValue );

int String_FindNamedItem
             ( TStrings* aStrings, String aSpNameAndValue, String aName );

void StrToStrings( String aStr, TStrings* aString, String aSp );
String StringsToStr( TStrings* aStrings, String aSp, bool IsTrim, int aMaxLen =-1);
String StringsToStr( TStrings* aStrings, int aBgn, int aEnd, String aSp, bool IsTrim, int aMaxLen=-1 );

//-----------------------目录有关-----------------------------------------------
void CheckAndMakeDirectory(String aDir);
bool IsAbsoluteFileName(String aDir);
String GetParentDirectory( String aDir );
void _CheckAndMakeDirectory(String aDir);
bool CopyFileAlways( String aSrcFileName, String aDestFileName );
String AskDirectory( String aPath );

String  GetProjectPath();
void  DelVarStringsIfIn(String  aBookMark,TStrings* aVarNames);

int GetSubStrCount( String aStr, String aSubStr );
bool HasSubString( String aStr, String aSubStr );
bool HasSubString( String aStr, TStrings* aSubStrings );
bool HasSubString( String aStr, String aSubStr, String aSp );

int StrPos( String aStr, String aStrToFind, int aBgnPos, int aEndPos=-1 );


//----------------------TControl------------------------------------------------
void SetAllSubCtrlEnable( TWinControl* aControl, bool IsEnable );
bool IsControlVisible(TControl* aControl);
void SetControlCption( TControl* aControl, String aCaption );


void StrToGrid( String aStr, String aSpRec, String aSpField, TStringGrid* aGrid );
void StringsToGrid( TStrings* aStrings, TStringGrid* aGrid, String aRecSp );
void StringsToGrid( TStrings* aStrings, TStringGrid* aGrid, int GridNo, TStatusBar* aHint, TProgressBar* aBar, String aRecSp );
TStrings* Grid_GetColWidths(TStringGrid* aGrid);
void Grid_Clear( TStringGrid* aGrid );
void Grid_SetRow(TStringGrid* aGrid, int aRow, TStrings* aStrings);
void Grid_InsertRow(TStringGrid* aGrid, String aStr, String aSp);
void Grid_InsertRow(TStringGrid* aGrid, TStrings* aStrings);
void  Grid_SetFixRows( TStringGrid* aGrid, int aCount );
bool IsNullStrings( TStrings* aStrings );


void ObjectToListBox( TListBox* aList, TObject* aObject, String aName );
void ObjectToComboBox( TComboBox* aBox, TObject* aObject, String aName );
TObject* GetComboBoxSelectedLayerData(TComboBox* aCBox);

TObject* GetListBoxSelectedNodeData ( TListBox* aList );
MLayerDataTreeNode*  GetSelectedLayerData(TComboBox* aCBox);

MParaMapElementItem*  GetSelectedMapElement( TListView* aList );


//----Merge----------
String MergeStr( String aStr1, String aStr2, String aDiv );
bool IsEqualByCase(String aStr1, String aStr2, bool IsUppercase);
bool String_HasChineseCharacter(String aStr);


//功能：File / Path名称处理工具
String ApplicationPath();
String TemplatePath();
String  TempPath();
String Manual3DPath();
String Manual3DExeFile();
String  ManualPath();
String  SystemPath();


void RunScript( TStrings* aStrings );

void Strings_RmvSection( TStrings* aStrings, int aSecCount,
                         String aStartStr, String aEndStr,
                         int aStartPos=0, int aEndPos=MAXINT,
                         bool RmvHeadAndTail=true );


//------------------------------------------------------------------------------
bool ProcessExists1( String ExeName );
String WaitForFile( String aFileName, String aProcessName, String aKillExeFileName );
bool ProcessExists( String ExeName);


MLayerDataTreeNode* GetSelectedLayerDataItem( TTreeView* aTree );
MTreeNode_ModeObject* GetSelectedModeNodeObject( TListView* aList );
//MAMProject*  GetSelectedAMProject( TListBox* aList );

MLaserPen*  GetSelectedLaserPen( TListView* aList );
MLaserPen*  GetSelectedLaserPen(TComboBox* aComBox);
MPartProject*  GetSelectedPartProject( TListBox* aList );

//------------------------------------------------------------------------------
TStrings* CRLFString2TStrings(String  aCRLFText,String aDiv);
TStrings* FindAllStrStrings_Prev( TStrings* aStrings, String aPrefix );
int IndexStrInStrings_Prev( TStrings* aStrings, String aPrefix, int aBgnPos );
TStrings* splitToStrings_Mask( String aStr, String aDiv );


void Strings_GetSection_Pos( TStrings* aStrings, int aSecCount,
                             String aStartStr, String aEndStr,
                             String aGetPos, int aStartPos, int aEndPos,
                             int& aSecBgn,int& aSecEnd );

int LocateNamedRow( TStrings* aStrings, int aFindCount ,
                        String aStrFind, int aBgn=0, int aEnd=MAXINT );
int LocateNamedRow( TStrings* aStrings, int aFindCount,
                        TStrings* aStringFind, int aBgn=0, int aEnd=MAXINT );
int _LocateNamedRow( TStrings* aStrings, int aFindCount, String Style, TStrings* aStringFind, String aStrFind, int aBgn, int aEnd );

TStrings* Strings_GetSection( TStrings* aStrings, int aSecCount,
                              String aStartStr, String aEndStr,
                              String aGetPos, int aStartPos=0,
                              int aEndPos=MAXINT, bool RmvHeadAndTail=false );

TStrings* GetSectionFromFile( String aFileName, int aSecCount,
                              String aStartStr, String aEndStr,
                              int aStartPos=0, int aEndPos=MAXINT,
                              bool RmvHeadAndTail=false );

TStrings* Strings_GetSection( TStrings* aStrings, int aSecCount,
                              String aStartStr, String aEndStr,
                              int aStartPos=0, int aEndPos=MAXINT,
                              bool RmvHeadAndTail=false );
TStrings* Strings_GetSection( TStrings* aStrings, int aSecCount,
                              String aStartStr, TStrings*  aEndStrings,
                              int aStartPos=0, int aEndPos=MAXINT,
                              bool RmvHeadAndTail=false );

//--------------------------File -----------------------------------------------
TStringList* CheckAndLoadFromFile( String aFileName );
void CheckAndLoadFromFile( String aFileName, TStringList* aList );

TStrings* Strings_Union( TStrings* aList1, TStrings* aList2, bool isMaskMerge );
TStrings* Strings_Union( TStrings** I_Strings, int I_Strings_Size, bool isMaskMerge );


int  GetIndexFromStrings_ByName(TStrings* aStrings,String iName,String iValue,int aBgnPos);


void StringsControl_SetItemIndex(TControl* aControl, int aIndex);

void ThrowMessageOnTop( String aMsg );
void ShowMessageOnTop( String aMessage );
void ThrowMessage( String aMessage );



//void WordToRvc( String aBookMark, TRVOfficeConverter* aRvc1, TRichViewEdit* aRVEdit );
//void RvcToWord( String aBookMark, void* aRvc1, TRichViewEdit* aRVEdit);
//void ImportRvFromWord( void* aRvc, String aFileName,  TRichViewEdit* aRVEdit );
//void ExportRvToWord( void* aRvc, String aFileName,  TRichViewEdit* aRVEdit );
//int FilterIndex_ImportRvFromWord(TRVOfficeConverter* aRvc,String aType);
//int FilterIndex_ExportRvToWord(TRVOfficeConverter* aRvc,String aType);
//int FilterIndex_ImportRvFromWord(TRVOfficeConverter* aRvc, TStrings* aTypes);
//int FilterIndex_ExportRvToWord(TRVOfficeConverter* aRvc, TStrings* aTypes);

//int FilterIndex_ImportRvFromWord(TRVOfficeConverter* aRvc);
//int FilterIndex_ExportRvToWord(TRVOfficeConverter* aRvc);
//void GetNames_ExportRvToWord(TRVOfficeConverter* aRvc,TStrings* aStrings);
//void GetNames_ImportRvFromWord(TRVOfficeConverter* aRvc,TStrings* aStrings);


String  MemoVarPreProcess(String aMemoText,String aDiv="@@");
void ConfirmApplication( Variant& aEng, String aExeCmd,String aComStr );
void ListView_DelItemByata( TListView* aList, void* aData );
void ListView_Delete( TListView* aList, TListItem* aItem );

int ListView_FindColByCaption( TListView* aListView, String aCaption );
int ListView_FindColByCaption( TListItem* aItem, String aCaption );

int ListView_GetRowByCaptionAndValue( TListView* aListView, String aColName, String aFindValue );
int ListView_GetRowByCaptionAndValue( TListView* aListView, int aCol, String aFindValue );
bool ListView_SelectRow( TListView* aListView, int aRow );
void ListView_Search( TListView* aListView, String aColName, String aFindValue );


TListItem* ListView_FindByData( TListView* aListView, void* aData );
int ListView_IndexByData( TListView* aListView, void* aData );
void* GetListViewSelectedNodeData ( TListView* aList );

TListItem* ListView_SelectedItem( TListView* aListView );
void* ListView_SelectedItemData( TListView* aListView );
TListItem* ListView_SelectedItem( TListView* aListView );

TList* ListView_GetSelectedItems( TListView* aListView );
TList* ListView_GetSelectedItemDatas( TListView* aListView );

//20151022 待移植

void SetListViewData( TListItem* aItem, void* aData );
void SetListViewSelectedNodeData ( TListView* aList, void* aData );

void ListView_SelectAllItems( TListView* aListView, bool IsSelected );
TList* ListView_GetAllItems( TListView* aListView );
TList* ListView_GetAllItemDatas( TListView* aListView );

TList* ListView_GetListItemsDatas( TList* aItems );

String ListView_ItemValue_NamedCol( TListItem* aItem, String aName );
String ListView_ItemValue( TListItem* aItem, int aCol );
String ListView_SelectedItemValue( TListView* aListView, int aCol );
//String ListView_SelectedItem( TListView* aListView, int aCol );

TListItem* ListView_AddItems( TListView* aListView, String aStrAll, String aSp, void* aData=NULL );
TListItem* ListView_InsertItems( TListView* aListView, String aStrAll, String aSp, void* aData=NULL );
TListItem* ListView_InsertItems( TListView* aListView, int aItemIndex, String aStrAll, String aSp, void* aData=NULL );
void ListView_SetItems( TListItem* aListView, String aStrAll, String aSp, void* aData );
void ListView_AddTitles( TListView* aListView, String aTitles, String aSizeStr, String aSp, bool IsMask=false );
void ListView_InitForGrid(TListView* aListView);
void ListView_Refresh(TListView* aListView);

void TStringsToListView(TStrings* aStrings, TListView* aList,String aTitles,String  aColSizes);

void ControlSetFocused( TWinControl* aControl );


void FileToStringsControl( String aFileName, TControl* aStringControl );
TStrings* StringsControl_Items(TControl* aControl);
int StringsControl_Count(TControl* aControl);
int StringsControl_ItemIndex(TControl* aControl);
void StringsControl_SetItemIndex(TControl* aControl, int aIndex);
String StringsControl_ItemCur(TControl* aControl);
String StringsControl_Item(TControl* aControl, int aIndex);

int StringsControl_SetItem(TControl* aControl, String aStr);

MMapElement_ExcelImporter* GetMapParas(String aProjectPath);
void AddPromptLine( String aText );


#endif
