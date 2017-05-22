// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'COMMON_FUNC.pas' rev: 6.00

#ifndef COMMON_FUNCHPP
#define COMMON_FUNCHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Registry.hpp>	// Pascal unit
#include <ActiveX.hpp>	// Pascal unit
#include <ShlObj.hpp>	// Pascal unit
#include <WinSock.hpp>	// Pascal unit
#include <CheckLst.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <QuickRpt.hpp>	// Pascal unit
#include <ComObj.hpp>	// Pascal unit
#include <ComCtrls.hpp>	// Pascal unit
#include <DBCtrls.hpp>	// Pascal unit
#include <Grids.hpp>	// Pascal unit
#include <Menus.hpp>	// Pascal unit
#include <ShellAPI.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <StrUtils.hpp>	// Pascal unit
#include <OleCtnrs.hpp>	// Pascal unit
#include <DB.hpp>	// Pascal unit
#include <Variants.hpp>	// Pascal unit
#include <DBGrids.hpp>	// Pascal unit
#include <Math.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <jpeg.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Common_func
{
//-- type declarations -------------------------------------------------------
struct Tindex;
typedef Tindex *Pindex;

#pragma pack(push, 4)
struct Tindex
{
	AnsiString index_id;
} ;
#pragma pack(pop)

struct TDocInfo;
typedef TDocInfo *PTDocInfo;

#pragma pack(push, 4)
struct TDocInfo
{
	AnsiString DocFile;
} ;
#pragma pack(pop)

#pragma option push -b-
enum MFormStatus { fsInsert, fs_Edit, fsQuery };
#pragma option pop

#pragma option push -b-
enum EnumSetWhat { E_swVisible, E_swEnable, E_swCheck };
#pragma option pop

typedef DynamicArray<AnsiString >  arraystring;

typedef DynamicArray<Variant >  arrayVariant;

typedef DynamicArray<void * >  arrayPointer;

typedef DynamicArray<Grids::TStringGrid* >  arrayStringGrid;

#pragma pack(push, 1)
struct LinkInfo
{
	char pTarget[260];
	char pAugment[260];
	char pDirectory[260];
} ;
#pragma pack(pop)

//-- var, const, procedure ---------------------------------------------------
static const char PathSplitter = '\x5c';
#define blanksplitter "  "
#define cPrintConfigField "PRINT_CONFIG_FIELD"
#define cFMTValue "NORMAL"
#define CLookupStyle_DropDownList "T0"
#define CLookupStyle_DropDown "T1"
static const Shortint cCheckType_integer = 0x0;
static const Shortint cCheckType_Float = 0x1;
static const Shortint cCheckType_Date = 0x2;
static const Shortint cCheckType_Time = 0x3;
static const bool C_Debug = true;
static const char csplitter = '\x3b';
static const char splitter_ = '\x5f';
#define CFlg_QUERY_TableName "@@TABLENAME"
#define CSpecialFields "@SPECIAL_FIELDS"
#define CFlg_NoStr "@NoStr"
#define CFlg_NotEqu "<>"
#define CFlg_LikeField "@Like"
#define CFLG_AutoNo "@AUTONO"
#define CSQL_SELECT "SELECT"
#define CSQL_INSERT "INSERT"
#define CSQL_DELETE "DELETE"
#define CSQL_UPDATE "UPDATE"
#define CSQL_ALTER "ALTER"
extern PACKAGE bool G_IsBuffered;
extern PACKAGE AnsiString mErrFuncName;
extern PACKAGE AnsiString mErrMsg;
extern PACKAGE AnsiString mRaiseErrMsg;
extern PACKAGE Stdctrls::TMemo* mErrMemo;
extern PACKAGE void __fastcall RunScript(AnsiString VBSciptFileName, AnsiString aFunc)/* overload */;
extern PACKAGE void __fastcall RunScript(Classes::TStrings* aList, AnsiString aFunc)/* overload */;
extern PACKAGE void __fastcall _RunScript(const Variant &sc, Classes::TStrings* aList, AnsiString aFunc);
extern PACKAGE void __fastcall RunJSScript(Classes::TStrings* aList, AnsiString aFunc)/* overload */;
extern PACKAGE void __fastcall RunJSScript(AnsiString aFileName, AnsiString aFunc)/* overload */;
extern PACKAGE void __fastcall RunJSScript(AnsiString aFileName)/* overload */;
extern PACKAGE void __fastcall RunJSScript(Classes::TStrings* VBScript)/* overload */;
extern PACKAGE void __fastcall RunDMSCript(AnsiString FileName);
extern PACKAGE void __fastcall RunDSSCript(AnsiString FileName);
extern PACKAGE void __fastcall RunVBScript(AnsiString VBSciptFileName)/* overload */;
extern PACKAGE void __fastcall RunVBScript(Classes::TStrings* VBScript)/* overload */;
extern PACKAGE void __fastcall AddNamedValue_Strings(Classes::TStrings* I_Strings, AnsiString I_Name, AnsiString I_Value);
extern PACKAGE bool __fastcall SetItems(Classes::TStrings* I_String, Stdctrls::TComboBox* O_Combo, int I_DefIndex = 0x0);
extern PACKAGE void __fastcall SelectItem(int I_Item, Stdctrls::TComboBox* O_Combo)/* overload */;
extern PACKAGE void __fastcall SelectItem(AnsiString I_Item, Stdctrls::TComboBox* O_Combo)/* overload */;
extern PACKAGE AnsiString __fastcall BoolToStr(Stdctrls::TCheckBox* aCheckBox)/* overload */;
extern PACKAGE AnsiString __fastcall BoolToStr(bool I_Bool)/* overload */;
extern PACKAGE bool __fastcall mStrToBool(AnsiString I_Str);
extern PACKAGE int __fastcall ArrayCount(const AnsiString * I_array, const int I_array_Size)/* overload */;
extern PACKAGE int __fastcall ArrayCount(const int * I_array, const int I_array_Size)/* overload */;
extern PACKAGE int __fastcall ArrayCount(const double * I_array, const int I_array_Size)/* overload */;
extern PACKAGE void __fastcall CheckIntStrings(const AnsiString * P_StringName, const int P_StringName_Size, const AnsiString * P_String, const int P_String_Size)/* overload */;
extern PACKAGE void __fastcall CheckFloatStrings(const AnsiString * P_StringName, const int P_StringName_Size, const AnsiString * P_String, const int P_String_Size)/* overload */;
extern PACKAGE void __fastcall CheckFloatString(AnsiString I_StringName, AnsiString I_String, double I_Min = -1.700000E+308, double I_Max = 1.700000E+308);
extern PACKAGE void __fastcall CheckFloatStrings(const AnsiString * P_StringName, const int P_StringName_Size, const AnsiString * P_String, const int P_String_Size, const double * P_Mins, const int P_Mins_Size, const double * P_Maxs, const int P_Maxs_Size)/* overload */;
extern PACKAGE void __fastcall CheckIntString(AnsiString I_StringName, AnsiString I_String, int I_Min = 0x80000001, int I_Max = 0x7fffffff);
extern PACKAGE void __fastcall CheckIntStrings(const AnsiString * P_StringName, const int P_StringName_Size, const AnsiString * P_String, const int P_String_Size, const int * P_Mins, const int P_Mins_Size, const int * P_Maxs, const int P_Maxs_Size)/* overload */;
extern PACKAGE void __fastcall CheckNullString(const AnsiString * P_StringName, const int P_StringName_Size, const AnsiString * P_String, const int P_String_Size)/* overload */;
extern PACKAGE void __fastcall CheckNullString_SetDef(AnsiString &I_String, const AnsiString I_StringDef);
extern PACKAGE void __fastcall CheckNullString(AnsiString I_String, AnsiString I_StringName)/* overload */;
extern PACKAGE void __fastcall CheckNullString(Stdctrls::TEdit* I_Edit, Stdctrls::TLabel* I_Label)/* overload */;
extern PACKAGE void __fastcall CheckNullString(Stdctrls::TComboBox* I_Edit, Stdctrls::TLabel* I_Label)/* overload */;
extern PACKAGE AnsiString __fastcall GetValue_ByName(AnsiString I_Str, AnsiString I_Name, AnsiString I_Splitter = ";", bool IsTrim = true)/* overload */;
extern PACKAGE AnsiString __fastcall GetValue_ByName(Classes::TStrings* I_List, AnsiString I_Name, AnsiString I_Splitter = ";", bool IsTrim = true)/* overload */;
extern PACKAGE AnsiString __fastcall GetName_ByValue(Classes::TStrings* I_List, AnsiString I_Value, AnsiString I_Splitter = ";");
extern PACKAGE AnsiString __fastcall GetTrueValue(AnsiString aValue, bool IsTrim = true);
extern PACKAGE AnsiString __fastcall GetFirstItem(AnsiString aValue, AnsiString aSplitter, bool IsTrim = true);
extern PACKAGE AnsiString __fastcall StringsToAString(Classes::TStrings* strings, AnsiString splitter = ";");
extern PACKAGE void __fastcall AStringToStrings(AnsiString aString, Classes::TStrings* aStrings, AnsiString splitter = ";", bool isMerge = false);
extern PACKAGE Variant __fastcall split(AnsiString str, AnsiString delimiter = ";", bool IsUpperCase = true);
extern PACKAGE Classes::TStrings* __fastcall GetStringsNames(Classes::TStrings* I_String)/* overload */;
extern PACKAGE AnsiString __fastcall GetStringsNames(AnsiString I_String, AnsiString I_Splitter = ";")/* overload */;
extern PACKAGE AnsiString __fastcall GetStringsValues(AnsiString I_String, AnsiString I_Splitter = ";", bool IsTrim = true)/* overload */;
extern PACKAGE Classes::TStrings* __fastcall GetStringsValues(Classes::TStrings* I_String, bool IsTrim = true)/* overload */;
extern PACKAGE AnsiString __fastcall GetItem_NamedValue(Classes::TStrings* I_String, int I_ItemIndex);
extern PACKAGE Classes::TList* __fastcall MergeLists(Classes::TList* aList, Classes::TList* bList);
extern PACKAGE Classes::TStrings* __fastcall MergeStrings(Classes::TStrings* aString, Classes::TStrings* bStrings, bool isMaskMerge)/* overload */;
extern PACKAGE Classes::TStrings* __fastcall MergeString(Classes::TStrings* aString, Classes::TStrings* bString, AnsiString splitter)/* overload */;
extern PACKAGE Classes::TStringList* __fastcall splitToStrings_WithSplitter(AnsiString aInString, const AnsiString * aInSplitters, const int aInSplitters_Size, bool IsUpperCase = true);
extern PACKAGE Classes::TStringList* __fastcall splitToStrings(AnsiString aInString, const AnsiString * aInSplitters, const int aInSplitters_Size, bool isWithSplitter = false, bool IsUpperCase = true)/* overload */;
extern PACKAGE Classes::TStringList* __fastcall splitToStrings(AnsiString aInString, Classes::TStrings* aInSplitters, bool isWithSplitter = false, bool IsUpperCase = true)/* overload */;
extern PACKAGE Classes::TStringList* __fastcall splitToStrings(AnsiString aInString, AnsiString aInDelimiter = ";", bool isWithSplitter = false, bool IsUpperCase = true)/* overload */;
extern PACKAGE void __fastcall AssignSCrollBar(Extctrls::TImage* Img, Stdctrls::TScrollBar* sbH, Stdctrls::TScrollBar* sbV, Extctrls::TPanel* Panel1);
extern PACKAGE AnsiString __fastcall NotStrField(AnsiString I_SqlStr);
extern PACKAGE AnsiString __fastcall NotEqualField(AnsiString I_SqlStr);
extern PACKAGE AnsiString __fastcall LikeField(AnsiString I_SqlStr);
extern PACKAGE AnsiString __fastcall FmtWdtString(int I_N, AnsiString I_String, AnsiString I_AddChar);
extern PACKAGE AnsiString __fastcall Left(AnsiString I_String, int aLen);
extern PACKAGE bool __fastcall IsSuffix(AnsiString I_Str, AnsiString I_Suffix)/* overload */;
extern PACKAGE AnsiString __fastcall Right(AnsiString I_Str, int I_Length);
extern PACKAGE bool __fastcall IsSuffix(AnsiString I_Str, Classes::TStringList* I_Suffix)/* overload */;
extern PACKAGE bool __fastcall IsPreFix(AnsiString I_String, Classes::TStringList* I_PreFix)/* overload */;
extern PACKAGE bool __fastcall IsPreFix(AnsiString I_String, AnsiString I_PreFix)/* overload */;
extern PACKAGE AnsiString __fastcall RemoveSuffix(AnsiString I_String, AnsiString I_Suffix);
extern PACKAGE AnsiString __fastcall RemovePrefix(AnsiString I_String, AnsiString I_Prefix);
extern PACKAGE void __fastcall SetLoopErrPanel(Stdctrls::TMemo* aMemo);
extern PACKAGE void __fastcall BgnLoopErr(AnsiString aFuncName);
extern PACKAGE void __fastcall Prompt(AnsiString aStr);
extern PACKAGE void __fastcall PromptError(AnsiString aStr);
extern PACKAGE void __fastcall PromptDebugError(AnsiString aStr);
extern PACKAGE void __fastcall ShowLoopErr(void);
extern PACKAGE void __fastcall AddLoopErr(const AnsiString aNowErr, int aIndex)/* overload */;
extern PACKAGE void __fastcall AddLoopErr(const AnsiString aNowErr)/* overload */;
extern PACKAGE void __fastcall AddRaiseErr(const AnsiString aNowErr);
extern PACKAGE AnsiString __fastcall GetLoopErr();
extern PACKAGE void __fastcall EnableControls(Controls::TWinControl* pn, bool isEnable);
extern PACKAGE void __fastcall SaveControlStatus(Controls::TWinControl* pn);
extern PACKAGE void __fastcall RestoreControlStatus(Controls::TWinControl* pn);
extern PACKAGE void __fastcall ClearControls(Controls::TWinControl* pn);
extern PACKAGE int __fastcall RightPos(AnsiString aStr, AnsiString aSplitter);
extern PACKAGE void __fastcall SplitStrTo2Str_Right(AnsiString aSrcStr, AnsiString aSplitter, AnsiString &aStr1, AnsiString &aStr2, bool FromLeft, bool IsTrim = true);
extern PACKAGE void __fastcall SplitStrTo2Str(AnsiString aSrcStr, AnsiString aSplitter, AnsiString &aStr1, AnsiString &aStr2, bool IsTrim = true);
extern PACKAGE void __fastcall _SplitStrTo2Str(int aPos, AnsiString aSrcStr, AnsiString aSplitter, AnsiString &aStr1, AnsiString &aStr2, bool IsTrim = true);
extern PACKAGE void __fastcall SplictStrToVar(const AnsiString aSrcStr, const char aSplitter, Variant &aVarStrs)/* overload */;
extern PACKAGE Variant __fastcall SplictStrToVar(const AnsiString aSrcStr, const char aSplitter)/* overload */;
extern PACKAGE AnsiString __fastcall commTabSearchGetSelFields(Controls::TWinControl* pn);
extern PACKAGE AnsiString __fastcall commTabSearchGetSelCaption(Controls::TWinControl* pn);
extern PACKAGE void __fastcall commTabSearch2(Controls::TWinControl* pn, AnsiString RealEStr, AnsiString DisplayCStr, AnsiString DefaultValue = "", int DetailWidth = 0xfa, int CaptionWidth = 0x50, int StartVerPos = 0x28, int dLen = 0x1e);
extern PACKAGE AnsiString __fastcall commTabSearchGetKeyWords(Controls::TWinControl* pn);
extern PACKAGE AnsiString __fastcall commTabSearchGetLogic(Controls::TWinControl* pn);
extern PACKAGE void __fastcall FmtStrings(Classes::TStrings* aStrings, bool isTrim = true, bool isUpperCase = true);
extern PACKAGE bool __fastcall IsLike(const AnsiString aWholeStr, const AnsiString aSubStr)/* overload */;
extern PACKAGE bool __fastcall IsLike(const AnsiString aInStr, const AnsiString * aInStrArray, const int aInStrArray_Size)/* overload */;
extern PACKAGE bool __fastcall IsLike(const AnsiString aInStr, const Classes::TStrings* aInStringS)/* overload */;
extern PACKAGE bool __fastcall IsIn(const AnsiString aInStr, const AnsiString * aInStrArray, const int aInStrArray_Size)/* overload */;
extern PACKAGE bool __fastcall IsIn(const AnsiString aInStr, const Classes::TStrings* aInStringS)/* overload */;
extern PACKAGE bool __fastcall IsIn(const AnsiString aInStr, const AnsiString aStrStrings, const AnsiString aSp)/* overload */;
extern PACKAGE Classes::TStrings* __fastcall GetSubStringListBySP(AnsiString aInString, AnsiString aInLeftSP, AnsiString aInRightSP, bool isWithSP = false, bool IsTrim = true);
extern PACKAGE AnsiString __fastcall GetSubStrBySP(int I_Index, AnsiString aInString, AnsiString aInLeftSP, AnsiString aInRightSP, bool isWithSP = false);
extern PACKAGE AnsiString __fastcall NamedItem(int I_Index, AnsiString aInString, AnsiString aInDelimiter = ";");
extern PACKAGE AnsiString __fastcall FirstItem(AnsiString aInString, AnsiString aInDelimiter = ";");
extern PACKAGE AnsiString __fastcall LastItem(AnsiString aInString, AnsiString aInDelimiter = ";");
extern PACKAGE int __fastcall IndexLookupList(Classes::TStrings* I_LookupList, AnsiString I_ItemName, AnsiString I_Splitter, bool IsTrim = true);
extern PACKAGE void __fastcall Set_ListItems_ByName(Classes::TStrings* I_LookupList, AnsiString I_ItemName, AnsiString I_Splitter, AnsiString aValue);
extern PACKAGE void __fastcall Set_ListItemStr_ByName(Classes::TStrings* I_LookupList, AnsiString I_ItemName, AnsiString I_Splitter, AnsiString I_Str)/* overload */;
extern PACKAGE void __fastcall Set_ListItemStr_ByName(AnsiString &aStr, AnsiString aSp1, AnsiString aItemName, AnsiString aSp2, AnsiString I_Value)/* overload */;
extern PACKAGE Classes::TStrings* __fastcall Get_ListItems_ByName(Classes::TStrings* I_LookupList, AnsiString I_ItemName, AnsiString I_Splitter, bool IsTrim = true);
extern PACKAGE AnsiString __fastcall Get_ListItemStr_ByName(AnsiString aStr, AnsiString aSp1, AnsiString aItemName, AnsiString aSp2, AnsiString aDefValue, BOOL isTrim = true)/* overload */;
extern PACKAGE AnsiString __fastcall Get_ListItemStr_ByName(Classes::TStrings* I_LookupList, AnsiString I_ItemName, AnsiString I_Splitter, AnsiString I_Default, bool IsTrim = true)/* overload */;
extern PACKAGE BOOL __fastcall StrToBool1(AnsiString aStr);
extern PACKAGE BOOL __fastcall Get_ListItemBool_ByName(Classes::TStrings* I_LookupList, AnsiString I_ItemName, AnsiString I_Splitter, BOOL I_Default);
extern PACKAGE double __fastcall Get_ListItemFloat_ByName(Classes::TStrings* I_LookupList, AnsiString I_ItemName, AnsiString I_Splitter, double I_Default);
extern PACKAGE Classes::TStrings* __fastcall MergeItemsToStrings(const AnsiString * aInStrArray, const int aInStrArray_Size)/* overload */;
extern PACKAGE AnsiString __fastcall MergeItems(const Classes::TStrings* I_string, AnsiString I_InSp)/* overload */;
extern PACKAGE AnsiString __fastcall MergeItems(const AnsiString * aInStrArray, const int aInStrArray_Size, AnsiString aInSp = ";")/* overload */;
extern PACKAGE int __fastcall GetYearFromstr(AnsiString str);
extern PACKAGE int __fastcall GetMonthFromstr(AnsiString str);
extern PACKAGE int __fastcall GetDayFromstr(AnsiString str);
extern PACKAGE int __fastcall CheckDate(AnsiString dstr);
extern PACKAGE void __fastcall ValidCheck(Dbctrls::TDBComboBox* aComBox)/* overload */;
extern PACKAGE void __fastcall ValidCheck(int chktype, AnsiString chkstr, AnsiString minValue, AnsiString maxValue)/* overload */;
extern PACKAGE Variant __fastcall TypeCheck(int chktype, AnsiString chkstr);
extern PACKAGE AnsiString __fastcall FilterStr(AnsiString str);
extern PACKAGE void __fastcall GetFilesInDir(Classes::TStrings* O_Files, AnsiString I_PathName, AnsiString I_ExtName = "*.*", BOOL IsRecursion = true, int aType = 0x3f);
extern PACKAGE AnsiString __fastcall GetPathName(AnsiString aFileName);
extern PACKAGE AnsiString __fastcall GetFileName_NoPath(AnsiString aFileName);
extern PACKAGE bool __fastcall isAbsPath(AnsiString aFileName);
extern PACKAGE AnsiString __fastcall GetFullFileName(AnsiString aFileName);
extern PACKAGE AnsiString __fastcall GetFileExt(AnsiString aFileName);
extern PACKAGE AnsiString __fastcall GetFileName_NoExt(AnsiString aFileName);
extern PACKAGE int __fastcall IndexMenuByName(AnsiString P_Name, Menus::TMenuItem* P_MenuItem);
extern PACKAGE void __fastcall SetMenuVis(Menus::TMenuItem* IO_Menu, bool I_IsVis)/* overload */;
extern PACKAGE void __fastcall SetMenuVis(Menus::TPopupMenu* IO_Menu, bool I_IsVis, int I_EscNum = 0x0)/* overload */;
extern PACKAGE void __fastcall SetMenuVis(Menus::TMainMenu* IO_Menu, bool I_IsVis)/* overload */;
extern PACKAGE void __fastcall SetMenuVis(Menus::TMenuItem* P_Menu, const AnsiString * P_MenuNames, const int P_MenuNames_Size, const bool * P_MenuVis, const int P_MenuVis_Size, EnumSetWhat P_SetWhat)/* overload */;
extern PACKAGE void __fastcall SetCheckBox(Stdctrls::TCheckBox* P_Control, bool P_Bool, EnumSetWhat P_SetWhat);
extern PACKAGE bool __fastcall HasGrandChild(Comctrls::TTreeNode* aNode);
extern PACKAGE Comctrls::TTreeNode* __fastcall Tree_Root(Comctrls::TTreeView* I_Tree);
extern PACKAGE bool __fastcall Check_DupNode_InParNode(Comctrls::TTreeNode* I_ParNode, AnsiString I_CurNode_Text);
extern PACKAGE Comctrls::TTreeNode* __fastcall GetDupNode_InParNode(Comctrls::TTreeNode* I_ParNode, AnsiString I_CurNode_Text);
extern PACKAGE Comctrls::TTreeNode* __fastcall Get_NameNode_InTreeNodes_ALL(Comctrls::TTreeNodes* I_Tree, AnsiString I_CurNode_Text, int I_No, int I_Node_Attr);
extern PACKAGE Comctrls::TTreeNode* __fastcall Get_LikeNameNode_InTreeNodes_ALL(int &FindPos, Comctrls::TTreeNodes* I_Tree, AnsiString I_CurNode_Text);
extern PACKAGE Comctrls::TTreeNode* __fastcall Get_NameNode_InTreeNodes(Comctrls::TTreeNodes* I_Tree, AnsiString I_CurNode_Text, int I_No = 0x1);
extern PACKAGE Comctrls::TTreeNode* __fastcall Get_NameNode_HasTree_InTreeNodes(Comctrls::TTreeNodes* I_Tree, AnsiString I_CurNode_Text, int I_No = 0x1);
extern PACKAGE Comctrls::TTreeNode* __fastcall Get_NameNode_NULLTree_InTreeNodes(Comctrls::TTreeNodes* I_Tree, AnsiString I_CurNode_Text, int I_No = 0x1);
extern PACKAGE void __fastcall _StringListToTrees(int I_CurPos, Classes::TStrings* I_ListNode, Classes::TStrings* I_ListPar, const bool * I_VistFlg, const int I_VistFlg_Size, Comctrls::TTreeView* aTree, Comctrls::TTreeNode* O_TreeNode, const AnsiString * InsertNodeName, const int InsertNodeName_Size, bool I_Can_SameName_InAPar, bool I_SameName_NullTree);
extern PACKAGE void __fastcall StringListToTrees(AnsiString i_curValue, Classes::TStrings* I_ListNode, Classes::TStrings* I_ListPar, Comctrls::TTreeView* aTree, Comctrls::TTreeNode* O_TreeNode, const AnsiString * InsertNodeName, const int InsertNodeName_Size, bool I_Can_SameName_InAPar = false, bool I_SameName_SameTree = false)/* overload */;
extern PACKAGE void __fastcall StringListToTrees(int i_curPos, Classes::TStrings* I_ListNode, Classes::TStrings* I_ListPar, Comctrls::TTreeView* aTree, Comctrls::TTreeNode* O_TreeNode, const AnsiString * InsertNodeName, const int InsertNodeName_Size, bool I_Can_SameName_InAPar = false, bool I_SameName_SameTree = false)/* overload */;
extern PACKAGE void __fastcall StringListToTrees(Classes::TStrings* I_ListNode, Classes::TStrings* I_ListPar, Comctrls::TTreeView* aTree, Comctrls::TTreeNode* O_TreeNode, const AnsiString * InsertNodeName, const int InsertNodeName_Size, bool I_Can_SameName_InAPar = false, bool I_SameName_SameTree = false)/* overload */;
extern PACKAGE void __fastcall ExpandChildern(Comctrls::TTreeNode* I_Node, bool I_IsExpandAll);
extern PACKAGE AnsiString __fastcall FormatStrDate(AnsiString aDate);
extern PACKAGE AnsiString __fastcall FormatStrTime(AnsiString aTime);
extern PACKAGE AnsiString __fastcall FmtErrMessage(AnsiString aFuncName, AnsiString aErrMsg);
extern PACKAGE arraystring __fastcall StringListToArray(Classes::TStrings* aString);
extern PACKAGE Classes::TStringList* __fastcall StringArrayToStringList(const AnsiString * I_StringArray, const int I_StringArray_Size);
extern PACKAGE arrayPointer __fastcall ListToArray(Classes::TList* aString);
extern PACKAGE Classes::TList* __fastcall ArrayToList(arrayPointer I_StringArray);
extern PACKAGE arrayStringGrid __fastcall ListToStringGridArray(Classes::TList* aString);
extern PACKAGE Classes::TStrings* __fastcall ReplaceStrInStrings(Classes::TStrings* aStrings, Classes::TStrings* subStr, Classes::TStrings* newsubStr, bool IsCase = false)/* overload */;
extern PACKAGE Classes::TStrings* __fastcall ReplaceStrInStrings(Classes::TStrings* aStrings, AnsiString subStr, AnsiString newsubStr, bool IsCase = false)/* overload */;
extern PACKAGE Classes::TStrings* __fastcall ReplaceStrInStrings(Classes::TStrings* aStrings, const AnsiString * subStr, const int subStr_Size, const AnsiString * newsubStr, const int newsubStr_Size, bool IsCase = false)/* overload */;
extern PACKAGE void __fastcall ReplaceStrInFile(AnsiString aFileName, AnsiString subStr, AnsiString newsubStr, bool IsCase = false)/* overload */;
extern PACKAGE void __fastcall ReplaceStrInFile(AnsiString aFileName, const AnsiString * subStr, const int subStr_Size, const AnsiString * newsubStr, const int newsubStr_Size, bool IsCase = false)/* overload */;
extern PACKAGE void __fastcall ReplaceStrInFile(AnsiString aFileName, Classes::TStrings* subStr, Classes::TStrings* newsubStr, bool IsCase = false)/* overload */;
extern PACKAGE AnsiString __fastcall ReplaceStr(AnsiString Str, Classes::TStrings* subStr, Classes::TStrings* newsubStr, bool IsCase = false)/* overload */;
extern PACKAGE AnsiString __fastcall ReplaceStr(AnsiString Str, const AnsiString * subStr, const int subStr_Size, const AnsiString * newsubStr, const int newsubStr_Size, bool IsCase = false)/* overload */;
extern PACKAGE int __fastcall PosByCase(AnsiString subStr, AnsiString Str, bool IsCase = false);
extern PACKAGE AnsiString __fastcall ReplaceStr(AnsiString Str, AnsiString subStr, AnsiString newsubStr, bool IsCase = false)/* overload */;
extern PACKAGE AnsiString __fastcall AddStr(AnsiString op1, AnsiString op2);
extern PACKAGE AnsiString __fastcall MaxStr(AnsiString op1, AnsiString op2);
extern PACKAGE AnsiString __fastcall MinStr(AnsiString op1, AnsiString op2);
extern PACKAGE void __fastcall DelRows(Grids::TStringGrid* I_Grid, int I_RowBgn, int I_RowNum = 0x1);
extern PACKAGE AnsiString __fastcall GridCell(Grids::TStringGrid* I_Grid, int I_Col, AnsiString I_RowName)/* overload */;
extern PACKAGE void __fastcall SetGridCell(Grids::TStringGrid* I_Grid, int I_Col, int I_Row, AnsiString I_Value)/* overload */;
extern PACKAGE void __fastcall SetGridCell(Grids::TStringGrid* I_Grid, AnsiString I_ColName, int I_Row, AnsiString I_Value)/* overload */;
extern PACKAGE void __fastcall SetGridCell(Grids::TStringGrid* I_Grid, int I_Col, AnsiString I_RowName, AnsiString I_Value)/* overload */;
extern PACKAGE AnsiString __fastcall GridCell(Grids::TStringGrid* I_Grid, AnsiString I_ColName, int I_Row, bool I_IsRow = false)/* overload */;
extern PACKAGE void __fastcall FlushGridRow(Grids::TStringGrid* I_Grid, int I_Row);
extern PACKAGE void __fastcall FlushGrid(Grids::TStringGrid* I_Grid);
extern PACKAGE int __fastcall FindNamedCol(Grids::TStringGrid* I_Grid, AnsiString I_Name);
extern PACKAGE int __fastcall FindNamedRow(Grids::TStringGrid* I_Grid, AnsiString I_Name);
extern PACKAGE Classes::TStrings* __fastcall GridCol(Grids::TStringGrid* I_Grid, AnsiString I_ColName);
extern PACKAGE int __fastcall GridCellRow(Grids::TStringGrid* I_Grid, const AnsiString * I_ColNames, const int I_ColNames_Size, const AnsiString * I_RowValues, const int I_RowValues_Size)/* overload */;
extern PACKAGE int __fastcall GridCellRow(Grids::TStringGrid* I_Grid, AnsiString I_ColName, AnsiString I_RowValue)/* overload */;
extern PACKAGE double __fastcall Formula_Str(AnsiString I_Str)/* overload */;
extern PACKAGE double __fastcall Formula_Str(Classes::TStringList* I_List)/* overload */;
extern PACKAGE AnsiString __fastcall FormulaStr_Replace(AnsiString aStr, const AnsiString * StrVarName, const int StrVarName_Size, const AnsiString * StrVarValue, const int StrVarValue_Size);
extern PACKAGE double __fastcall Formula_Replace(AnsiString aStr, const AnsiString * StrVarName, const int StrVarName_Size, const AnsiString * StrVarValue, const int StrVarValue_Size)/* overload */;
extern PACKAGE double __fastcall Formula_Replace(AnsiString aStr, Classes::TStrings* StrVarName, Classes::TStrings* StrVarValue)/* overload */;
extern PACKAGE double __fastcall Formula(AnsiString aStr)/* overload */;
extern PACKAGE double __fastcall Formula(AnsiString aStr, Classes::TStrings* StrVarName, Classes::TStrings* StrVarValue)/* overload */;
extern PACKAGE double __fastcall Formula(AnsiString aStr, const AnsiString * StrVarName, const int StrVarName_Size, const AnsiString * StrVarValue, const int StrVarValue_Size)/* overload */;
extern PACKAGE AnsiString __fastcall WideStr_BZToUnicode(WideString wStr);
extern PACKAGE WideString __fastcall WideStr_UnicodeToBZ(WideString wStr);
extern PACKAGE AnsiString __fastcall GetNamedValue(Classes::TStrings* I_Names, Classes::TStrings* I_Values, AnsiString I_Name);
extern PACKAGE bool __fastcall isNamedType(AnsiString I_Name, AnsiString I_TypeDef, AnsiString I_Splitter = ";");
extern PACKAGE void __fastcall InitFeatStr(Classes::TStrings* &O_Str);
extern PACKAGE AnsiString __fastcall StringValue(Classes::TStrings* I_String, int i);
extern PACKAGE AnsiString __fastcall StringName(Classes::TStrings* I_String, int i);
extern PACKAGE void __fastcall Openform(Classes::TComponent* Aowner, TMetaClass* Formclass, void *fm);
extern PACKAGE void __fastcall OpenSubForm(Forms::TForm* Frm, AnsiString no, AnsiString name, AnsiString standard, AnsiString testno);
extern PACKAGE AnsiString __fastcall getIPs();
extern PACKAGE AnsiString __fastcall IPAddrToName(AnsiString IPAddr);
extern PACKAGE Classes::TStrings* __fastcall compar_str(Classes::TStrings* name1, Classes::TStrings* name2, bool getsame);
extern PACKAGE bool __fastcall isEqual(AnsiString str1, AnsiString str2);
extern PACKAGE int __fastcall FullIndex(AnsiString I_Str, Classes::TStrings* I_String);
extern PACKAGE void __fastcall Tree_Copy(Comctrls::TTreeNode* I_Src_Node, Comctrls::TTreeNode* O_Dest_Node);
extern PACKAGE Comctrls::TTreeNode* __fastcall Tree_NewRoot(Comctrls::TTreeView* I_Tree);
extern PACKAGE AnsiString __fastcall Tree_FullPath(Comctrls::TTreeNode* I_Node);
extern PACKAGE void __fastcall CopyStringGrid(Grids::TStringGrid* I_Src, Grids::TStringGrid* OI_Dest);
extern PACKAGE Classes::TStrings* __fastcall StrGridHints(Classes::TList* aGrids);
extern PACKAGE AnsiString __fastcall StrGridHints_Str(Classes::TList* aGrids);
extern PACKAGE void __fastcall MoveLookupListToCell(Grids::TStringGrid* I_SG, Controls::TWinControl* I_LookupList, int I_TitleCellCol, int I_TitleCellRow, AnsiString I_TitleValue, int I_CellCol, int I_CellRow);
extern PACKAGE int __fastcall LocateNamedRow(Classes::TStringList* aList, Classes::TStringList* i_find_what, const int i_find_From = 0x0, const int i_find_end = 0x7fffffff)/* overload */;
extern PACKAGE int __fastcall LocateNamedRow(Classes::TStringList* aList, const AnsiString i_find_what, const int i_find_From = 0x0, const int i_find_end = 0x7fffffff)/* overload */;
extern PACKAGE AnsiString __fastcall Find_NamedRow(Classes::TStringList* aList, const AnsiString i_find_what, const int i_find_From = 0x0, const int i_find_end = 0x7fffffff);
extern PACKAGE AnsiString __fastcall Find_NamedValue(Classes::TStringList* aList, const AnsiString i_find_what, const int i_find_From = 0x0, const int i_find_end = 0x7fffffff);
extern PACKAGE AnsiString __fastcall AddFilter(const AnsiString * FldNames, const int FldNames_Size, const AnsiString * fldValues, const int fldValues_Size)/* overload */;
extern PACKAGE AnsiString __fastcall AddFilter(const AnsiString * FldNames, const int FldNames_Size, const AnsiString * fldValues, const int fldValues_Size, const AnsiString * fOrAnd, const int fOrAnd_Size, const AnsiString * fopers, const int fopers_Size, const BOOL * IsStrtype, const int IsStrtype_Size)/* overload */;
extern PACKAGE void __fastcall AddTreeNodes(Comctrls::TTreeNodes* aTreeNodes, const AnsiString * NodeTextS, const int NodeTextS_Size, Comctrls::TTreeNode* ParNode)/* overload */;
extern PACKAGE void __fastcall SetNodeImageSeleIndex(Comctrls::TTreeNode* aNode, int Index);
extern PACKAGE AnsiString __fastcall GetMidStr(AnsiString src, AnsiString split1, AnsiString split2);
extern PACKAGE BOOL __fastcall IsAIntNum(AnsiString aStr)/* overload */;
extern PACKAGE BOOL __fastcall IsAIntNum(AnsiString aStr, AnsiString ExcludeStr)/* overload */;
extern PACKAGE AnsiString __fastcall CopyStr(AnsiString aSrc, int aPos, int aLength);
extern PACKAGE HWND __fastcall RunAppByLnk(AnsiString AppLnkFile);
extern PACKAGE AnsiString __fastcall ReadRegistry(AnsiString KeyName);
extern PACKAGE void __fastcall WriteRegistry(AnsiString KeyName, AnsiString KeyValue);
extern PACKAGE void __fastcall MergeTrees(Comctrls::TTreeView* aTree1, Comctrls::TTreeView* aTree2);
extern PACKAGE int __fastcall Control_AbsLeft(Controls::TControl* aControl);
extern PACKAGE int __fastcall Control_AbsTop(Controls::TControl* aControl);
extern PACKAGE bool __fastcall StrHasChinese(AnsiString aStr);
extern PACKAGE void __fastcall SetCLBoxSelMod(Checklst::TCheckListBox* ClBok);
extern PACKAGE void __fastcall MoveCLBToTreeNode(Checklst::TCheckListBox* ClBox, Comctrls::TTreeNode* aNode);
extern PACKAGE void __fastcall MoveTreeNodeToCLB(Checklst::TCheckListBox* ClBox, Comctrls::TTreeView* aTree);
extern PACKAGE void __fastcall DelTreeNodeByTextList(Comctrls::TTreeView* aTree, Classes::TStrings* aDelList);
extern PACKAGE BOOL __fastcall IsEqualStr(AnsiString aStr1, AnsiString aStr2, BOOL IsCase);
extern PACKAGE int __fastcall IndexOfStr(Classes::TStrings* aStrings, AnsiString aStr, BOOL IsCase = false);
extern PACKAGE void __fastcall FreeTstrings(const Classes::TStrings* const * I_Tstring, const int I_Tstring_Size);
extern PACKAGE AnsiString __fastcall SetFullStr(int I_num, AnsiString I_SetWhat, AnsiString I_Str);
extern PACKAGE Variant __fastcall EvalScript(Classes::TStrings* aList, AnsiString aFunc = "main");

}	/* namespace Common_func */
using namespace Common_func;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// COMMON_FUNC
