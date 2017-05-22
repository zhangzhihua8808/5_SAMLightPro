unit COMMON_FUNC;

interface
Uses
  Classes, Dialogs,
  sysUtils ,Jpeg,
  Forms,controls,extctrls,stdctrls, math,
  dbgrids,Variants,DB,OleCtnrs,StrUtils,
  //ZLib,
  windows, shellapi, Menus,Grids,dbCtrls,
  ComCtrls,ComObj,
  //Excel2000,
  QuickRpt,Graphics,CheckLst,Winsock,shlobj,ActiveX,Registry;
  //, IdGlobal,            DBTables,

const
  PathSplitter = '\';
  //csplitter = ';';
  blanksplitter = '  ';
   //  cPrintConfigTable = 'PRINT_CONFIG_TBL';
  cPrintConfigField = 'PRINT_CONFIG_FIELD';
  cFMTValue = 'NORMAL';

  CLookupStyle_DropDownList = 'T0' ;
  CLookupStyle_DropDown = 'T1' ;

  cCheckType_integer = 0;
  cCheckType_Float = 1;
  cCheckType_Date = 2;
  cCheckType_Time = 3;

  C_Debug = True;
  csplitter = ';';
  splitter_ = '_';

  //G_DBName = 'PAR_DB' ;                       //????
  //G_DBName2 = 'FM_DB2' ;

  CFlg_QUERY_TableName = '@@TABLENAME';      //为TQUERY设置的TableName标志， PARAS['@@TABLENAME']为TableName

  CSpecialFields = '@SPECIAL_FIELDS' ;       //特殊字段，例如@AutoNo, @PageNo, @User等

  CFlg_NoStr = '@NoStr' ;                    //标志传入的SQL值为非STR字符串
  CFlg_NotEqu = '<>';
  CFlg_LikeField = '@Like';                  //定义Like字段

  CFLG_AutoNo = '@AUTONO';


  //-----SQL字符-------------------
  CSQL_SELECT = 'SELECT';
  CSQL_INSERT = 'INSERT';
  CSQL_DELETE = 'DELETE';
  CSQL_UPDATE = 'UPDATE';
  CSQL_ALTER = 'ALTER';

type
  Pindex =^Tindex;
  Tindex= record
  //parent_id:string;
  //index_name:string;
  index_id:string;

end;

  PTDocInfo =^TDocInfo ;
  TDocInfo = record
    //DocId:string;
    //DocName:string;
    DocFile:string;
  end;

type
  MFormStatus = ( fsInsert, fs_Edit, fsQuery );

type                                              //控制Control的设置属性
  EnumSetWhat = ( E_swVisible, E_swEnable, E_swCheck );

 type arraystring =  array of string;
 type arrayVariant =  array of variant;
 type arrayPointer =  array of Pointer;
 type arrayStringGrid = array of TStringGrid;

type
   LinkInfo = record
    pTarget:Array [0..MAX_PATH-1] Of Char;
    pAugment:Array [0..MAX_PATH-1] Of Char;
    pDirectory:Array [0..MAX_PATH-1] Of Char;
  end;

//--------Sql操作时的Tool函数---------
  function NotStrField( I_SqlStr:string ) : string;
  function NotEqualField( I_SqlStr:string ) : string;
  function LikeField( I_SqlStr:string ) :string;

  function StrToBool1 ( aStr:string ):bool;

  procedure _RunScript( sc:Variant; aList:TStrings; aFunc:AnsiString );

  procedure RunScript(VBSciptFileName:String;aFunc:String);overload; //by sxd 2008.3.22
  procedure RunScript(aList:TStrings;aFunc:String);overload;

  procedure RunJSScript( aList:TStrings;aFunc:AnsiString );overload;
  procedure RunJSScript( VBScript :TStrings  ) ;overload;
  procedure RunJSScript(aFileName:String;aFunc:AnsiString); overload;
  procedure RunJSScript(aFileName:String); overload;           //error

  procedure RunDSSCript(FileName:String);
  procedure RunDMSCript(FileName:String);

//-----------------字符串处理函数-------------------

  procedure InitFeatStr( var O_Str :TStrings );

  function IsEqualStr( aStr1:String; aStr2:String; IsCase:bool ):bool;
  function IndexOfStr( aStrings:TStrings; aStr:String ; IsCase:bool=false ) : integer;

  procedure FmtStrings( aStrings:TStrings; isTrim:boolean=True; isUpperCase:boolean=True );


  //-----数学计算------
  function FormulaStr_Replace(aStr:String; StrVarName,StrVarValue: array of string ):String;   //by sxd 2008.3.22    FormulaStr_Replace( '%A%*%B%', ['%A%','%B%'], ['10.2','11.0'] ) --> "10.2*11.0"
  function Formula_Replace(aStr:String; StrVarName,StrVarValue: array of string):double; overload;      //by sxd 2008.3.22
  function Formula_Replace(aStr:String; StrVarName,StrVarValue: TStrings):double;overload;              //by sxd 2008.3.22

  function Formula(aStr:String):double; overload;
  function Formula(aStr:String; StrVarName,StrVarValue: array of string):double; overload;    //by sxd 2008.3.22
  function Formula(aStr:String; StrVarName,StrVarValue: TStrings):double;overload;            //by sxd 2008.3.22

  function Formula_Str( I_Str : string ) : double;  overload;
  function Formula_Str( I_List:TstringList ) : double;  overload;
  //-----码制转换------
  function WideStr_BZToUnicode(wStr:wideString) : string;
  function WideStr_UnicodeToBZ(wStr:wideString) : Widestring;

  function GetNamedValue( I_Names, I_Values : TStrings;  I_Name : string ) : string;
  
  function StringArrayToStringList( I_StringArray : array of string ) : tStringList;
  function StringListToArray( aString : TStrings ):arraystring;

  function ListToStringGridArray( aString : TList ): arrayStringGrid;

  function ListToArray( aString : TList ): arrayPointer;
  function ArrayToList( I_StringArray : arrayPointer ) : TList;

  function PosByCase( subStr,Str: AnsiString; IsCase : boolean = false ) : integer;

  //-----字符串提取-----
  function ReplaceStr(Str,subStr,newsubStr: AnsiString; IsCase : boolean = false): string;  overload;
  function ReplaceStr(Str:string; subStr,newsubStr: TStrings; IsCase : boolean = false): string;  overload;
  function ReplaceStr(Str:string; subStr,newsubStr: array of string; IsCase : boolean = false): string; overload;

  function ReplaceStrInStrings( aStrings:TStrings; subStr,newsubStr: string; IsCase: boolean = false ): TStrings; overload;   //new 2008.1.30
  function ReplaceStrInStrings( aStrings:TStrings; subStr,newsubStr: array of string; IsCase: boolean = false ): TStrings; overload;   //new 2008.1.30
  function ReplaceStrInStrings( aStrings:TStrings; subStr,newsubStr: Tstrings; IsCase : boolean = false ): TStrings; overload;   //new 2008.1.30

  procedure ReplaceStrInFile( aFileName:string; subStr,newsubStr: string; IsCase : boolean = false ); overload;   //new 2008.1.30
  procedure ReplaceStrInFile( aFileName:string; subStr,newsubStr: array of string; IsCase : boolean = false ); overload;   //new 2008.1.30
  procedure ReplaceStrInFile( aFileName:string; subStr,newsubStr: Tstrings; IsCase : boolean = false ); overload;   //new 2008.1.30

  function Left( I_String :string; aLen : integer ) :string;
  function Right( I_Str :string; I_Length : integer ) : string;

  //------前后缀--------

  function RemoveSuffix( I_String :string; I_Suffix:string ) :string;
  function RemovePrefix( I_String :string; I_Prefix:string ) :string;

  function IsSuffix( I_Str, I_Suffix :string ) : boolean; overload;
  function IsSuffix( I_Str:string ; I_Suffix :TStringList ) : boolean;overload;
  function IsPreFix( I_String:string; I_PreFix:string ) : boolean;overload;
  function IsPreFix( I_String:string; I_PreFix:TStringList ) : boolean;overload;

  //-----检测空字符串，并以汉字方式提示-----------
  procedure CheckFloatStrings( P_StringName:array of string; P_String : array of string ); overload;
  procedure CheckFloatStrings( P_StringName:array of string; P_String : array of string;
                            P_Mins:array of double;P_Maxs:array of double );overload;
  procedure CheckFloatString( I_StringName:string;I_String :string; I_Min:double=-MaxDouble; I_Max:double=MaxDouble  );

  procedure CheckIntStrings( P_StringName:array of string; P_String : array of string); overload;
  procedure CheckIntStrings( P_StringName:array of string; P_String : array of string;
                            P_Mins:array of integer;P_Maxs:array of integer );overload;
  procedure CheckIntString( I_StringName:string;I_String :string; I_Min:integer=-MAXINT; I_Max:integer=MAXINT  );

  procedure CheckNullString_SetDef( var I_String :string; const I_StringDef:string );
  procedure CheckNullString( P_StringName:array of string; P_String : array of string ); overload;
  procedure CheckNullString( I_String :string; I_StringName:string );overload;
  procedure CheckNullString( I_Edit :TEdit; I_Label:TLabel );overload;
  procedure CheckNullString( I_Edit :TComboBox; I_Label:TLabel );overload;

  function isEqual(str1,str2: string):boolean;

  //------字符串分割-------
  function splitToStrings( aInString:string; aInDelimiter:string=CSplitter;isWithSplitter:boolean=False; IsUpperCase:boolean=true  ) : TStringList;overload;

  function RightPos( aStr:string; aSplitter:string ) : integer;
  procedure _SplitStrTo2Str( aPos : integer; aSrcStr:string; aSplitter:string; var aStr1:string; var aStr2:string;IsTrim:boolean=true);
  procedure SplitStrTo2Str( aSrcStr:string; aSplitter:string; var aStr1:string; var aStr2:string;IsTrim:boolean=true);
  procedure SplitStrTo2Str_Right( aSrcStr:string; aSplitter:string; var aStr1:string; var aStr2:string;FromLeft:boolean; IsTrim:boolean=true);

  procedure SplictStrToVar(const aSrcStr:string; const aSplitter:char; var aVarStrs:Variant);overload;
  function SplictStrToVar(const aSrcStr:string; const aSplitter:char):Variant;overload;
  function split( str:string; delimiter:string=CSplitter; IsUpperCase:boolean=true ) :variant;
  function splitToStrings_WithSplitter( aInString : string; aInSplitters : array of string; IsUpperCase:boolean=true ) : TStringList;
  function splitToStrings( aInString : string; aInSplitters : array of string; isWithSplitter:boolean=False; IsUpperCase:boolean=true  ) : TStringList;overload;
  function splitToStrings( aInString : string; aInSplitters : TStrings; isWithSplitter:boolean=False; IsUpperCase:boolean=true  ) : TStringList;overload;

  //GetSubStrBySP( 1, "2.0*%A%+cos(%B%)", "%", "%" ), 返回"%B%"   by sxd 2008.3.22
  function GetSubStrBySP( I_Index:integer; aInString:string; aInLeftSP:string; aInRightSP:string;isWithSP:boolean =False ):string;
  function GetSubStringListBySP( aInString:string; aInLeftSP:string; aInRightSP:string;isWithSP:boolean =False;IsTrim:boolean=true ):TStrings;

  function NamedItem( I_Index:integer; aInString:string; aInDelimiter:string=CSplitter ) :string;
  function FirstItem( aInString:string; aInDelimiter:string=CSplitter ) :string;
  function LastItem( aInString:string; aInDelimiter:string=CSplitter ) :string;

  function GetValue_ByName( I_Str:String; I_Name:String; I_Splitter:string=';'; IsTrim:boolean=true ) : string;overload;
  function GetValue_ByName( I_List:Tstrings; I_Name:String; I_Splitter:string=';'; IsTrim:boolean=true ) : string;overload;
  function GetName_ByValue( I_List:Tstrings; I_Value:String; I_Splitter:string=';'  ) : string;

  function GetTrueValue(aValue:string;IsTrim:boolean=true) : string;
  function GetFirstItem(aValue:string;aSplitter:string;IsTrim:boolean=true) : string;

  function StringsToAString( strings : TStrings;splitter:string=CSplitter ) :string ;
  procedure AStringToStrings( aString:string; aStrings:TStrings; splitter:string = CSplitter;isMerge:boolean = False );

  //2005
  function IsLike( const aWholeStr:string; const aSubStr: string ):boolean;overload;
  function IsLike( const aInStr:string; const aInStrArray: Array of string ):boolean;overload;
  Function IsLike(Const aInStr:string; Const aInStringS :Tstrings):boolean;overload;         //by ls 5.20

  function IsIn( const aInStr:string; const aInStrArray: Array of string ):boolean;overload;
  Function IsIn(Const aInStr:string; Const aInStringS :Tstrings):boolean;overload;         //by ls 5.20
  Function IsIn(Const aInStr:string; Const aStrStrings : String; const aSp : String):boolean;overload;

  //by sxd 2008.3.22 IndexLookupList( {(NAME=A),(DATATYPE=int)}, "NAME", '=' )
  function IndexLookupList ( I_LookupList:TStrings; I_ItemName:string; I_Splitter:string;IsTrim:boolean=true ):integer;

  procedure Set_ListItems_ByName( I_LookupList:TStrings; I_ItemName:string; I_Splitter:string; aValue:String );
  procedure Set_ListItemStr_ByName ( I_LookupList:TStrings; I_ItemName:string; I_Splitter:string; I_Str:string );overload;
  procedure Set_ListItemStr_ByName( var aStr:String; aSp1:String; aItemName:String; aSp2:String; I_Value:String );overload;

  //by sxd: 2009.9.17 , 获取所有以I_ItemName为名称，以I_Splitter为分割的项目
  function Get_ListItems_ByName( I_LookupList:TStrings; I_ItemName:string; I_Splitter:string; IsTrim:boolean=true ):TStrings;
  //function Get_ListItemStr_ByName ( I_LookupList:TStrings; I_ItemName:string; I_Splitter:string; IsTrim:boolean=true ):string;overload;
  function Get_ListItemStr_ByName ( I_LookupList:TStrings; I_ItemName:string; I_Splitter:string; I_Default:string; IsTrim:boolean=true ):string;overload;
  function Get_ListItemStr_ByName( aStr:String; aSp1:String; aItemName:String; aSp2:String; aDefValue:String; isTrim : bool=true ):String;overload;
  function Get_ListItemBool_ByName ( I_LookupList:TStrings; I_ItemName:string; I_Splitter:string; I_Default:bool ):bool;
  function Get_ListItemFloat_ByName ( I_LookupList:TStrings; I_ItemName:string; I_Splitter:string; I_Default:double ):double;

  //------字符串合并-------
  procedure FreeTstrings(I_Tstring:array of Tstrings);

  function MergeItems(const I_string:Tstrings;I_InSp:string) :String;overload ;//by ls 2003.4.21
  function MergeItems( const aInStrArray: Array of string; aInSp:string=CSplitter ) : string;overload;
  function MergeStrings( aString:TStrings; bStrings:TStrings; isMaskMerge:boolean ):Tstrings;overload;
  function MergeString( aString:TStrings; bString:TStrings; splitter : string ):TStrings;overload;
  function MergeItemsToStrings( const aInStrArray: Array of string) : Tstrings;overload ;

  function MergeLists( aList:TList; bList:TList ):TList;

  //TStrings的Names,Values处理
  function GetStringsNames( I_String : TStrings ) : TStrings;overload;
  function GetStringsValues( I_String : TStrings;IsTrim:boolean=true ) : TStrings;overload;

  //GetStringsNames( "No=001;classNo=005" ) = "No;ClassNo"    by sxd 2008.6.7
  //GetStringsValues( "No=001;classNo=005" ) = "001;005"
  function GetStringsNames( I_String : String; I_Splitter:string=';' ) : String;overload;
  function GetStringsValues( I_String : String; I_Splitter:string=';';IsTrim:boolean=true=true ) : String;overload;

  function GetItem_NamedValue( I_String :TStrings; I_ItemIndex:integer ) : string;

  //-----------------------
  function AddFilter(FldNames:array of string; fldValues:array of string):string;overload;
  function AddFilter(FldNames:array of string; fldValues:array of string;
              fOrAnd:array of string;fopers:array of string;IsStrtype:array of bool):string;overload;

  procedure AddTreeNodes(aTreeNodes:TTreeNodes;NodeTextS:array of string;ParNode:TTreeNode); overload;

  function  AddStr(op1,op2: string): string;
  function  MaxStr(op1,op2: string): string;
  function  MinStr(op1,op2: string): string;

  function StringValue( I_String:TStrings; i:integer ) : string;
  function StringName( I_String:TStrings; i:integer ) : string;

  //-------字符串应用----------------
  
  function isNamedType( I_Name : string; I_TypeDef : string; I_Splitter:string=';' ) : boolean;

  //-------2005.9.10----------------
  function LocateNamedRow( aList:TStringList; const i_find_what :String;
                           const i_find_From : integer =0 ; const i_find_end : integer = maxint ) : integer;overload;
  function LocateNamedRow( aList:TStringList; i_find_what :TStringList;
                              const i_find_From:integer = 0 ;  const i_find_end:integer=maxint) : integer;overload;
  //function LocateNamedRow_Like( aList:TStringList; const i_find_what :string;
  //                              const i_find_From:integer=0;  const i_find_end:integer = maxint) : integer;
  function Find_NamedRow( aList:TstringList; const i_find_what :string;
                          const i_find_From : integer = 0;  const i_find_end : integer = maxint ) : string;
  function Find_NamedValue( aList:TstringList ; const i_find_what :string ;
                            const i_find_From :  integer = 0; const i_find_end : integer = maxint ) : string ;

  //-------FileName Process---------
  procedure GetFilesInDir( O_Files : TStrings; I_PathName : string; I_ExtName : string = '*.*' ; IsRecursion:bool=true; aType:integer=faAnyFile );
  function GetPathName( aFileName:string ) : string;
  function GetFileName_NoPath( aFileName :string ):string;
  function isAbsPath( aFileName :String ) :boolean;
  function GetFullFileName( aFileName:string  ):string;
  function GetFileExt( aFileName :string ):string;
  function GetFileName_NoExt( aFileName :string ):string;

  //by SXD
  Function FmtErrMessage(aFuncName:string;aErrMsg:string) : string;
  Function FormatStrDate( aDate:string ) :string ;
  Function FormatStrTime( aTime:string ) :string ;

  function FmtWdtString( I_N:integer; I_String:string; I_AddChar:string ):string;

  //-------------出错处理----------
  procedure Prompt( aStr:string );
  procedure PromptError( aStr:string );
  procedure PromptDebugError( aStr:string );

  procedure SetLoopErrPanel(aMemo:TMemo);
  procedure BgnLoopErr(aFuncName:string);
  procedure ShowLoopErr();
  procedure AddRaiseErr(const aNowErr:string );
 // procedure RaiseLoopErr();
  procedure AddLoopErr( const aNowErr:string ); overload;
  procedure AddLoopErr( const aNowErr:string; aIndex:integer ); overload;
  function GetLoopErr():string;


//-----------------StringGrid操作----------------------  //for xk


  procedure CopyStringGrid( I_Src, OI_Dest : TStringGrid );

  function StrGridHints( aGrids : TList ):TStrings;
  function StrGridHints_Str( aGrids : TList ) : String;


  procedure FlushGridRow( I_Grid:TStringGrid; I_Row : integer );
  procedure FlushGrid( I_Grid : TStringGrid );

  function FindNamedCol(I_Grid:TStringGrid; I_Name:string) : integer;
  function FindNamedRow(I_Grid:TStringGrid; I_Name:string) : integer;
  function GridCol( I_Grid : TstringGrid; I_ColName : string ) : TStrings;
  function GridCellRow( I_Grid : TStringGrid; I_ColName : string; I_RowValue : string ):integer;overload;
  function GridCellRow( I_Grid : TStringGrid; I_ColNames : array of string; I_RowValues : array of string ):integer;overload;
  function GridCell( I_Grid : TStringGrid; I_ColName : string; I_Row : integer;  I_IsRow:boolean=false ):string;overload;
  function GridCell( I_Grid : TStringGrid; I_Col : integer; I_RowName : string ):string;overload;

  procedure SetGridCell( I_Grid : TStringGrid; I_Col : integer; I_Row : integer;  I_Value:string );overload;
  procedure SetGridCell( I_Grid : TStringGrid; I_ColName : string; I_Row : integer;  I_Value:string  );overload;
  procedure SetGridCell( I_Grid : TStringGrid; I_Col : integer; I_RowName:string; I_Value:string  );overload;

  procedure DelRows( I_Grid :TStringGrid; I_RowBgn : integer; I_RowNum : integer=1 );

  procedure MoveLookupListToCell( I_SG:TStringGrid;
                                I_LookupList:TWinControl;
                                I_TitleCellCol, I_TitleCellRow : integer;
                                I_TitleValue : string;
                                I_CellCol, I_CellRow : integer );

//-----------------控件操作--------------------------

  function Control_AbsLeft( aControl:TControl ) : integer;
  function Control_AbsTop( aControl:TControl ) : integer;

  procedure SaveControlStatus(pn:TWinControl);
  procedure RestoreControlStatus(pn:TWinControl);
  procedure EnableControls(pn:TWinControl; isEnable:boolean);
  procedure ClearControls(pn:TWinControl);

  //-------mod by SXD-------------------------------
  //----合法性Check----
  function TypeCheck( chktype: integer; chkstr: string ) : variant;
  procedure ValidCheck( chktype: integer; chkstr: string; minValue:string ; maxValue :string  ); overload;
  procedure ValidCheck(aComBox:TDBComboBox); overload;

  procedure AssignSCrollBar( Img:TImage;sbH,sbV:TScrollBar;Panel1:TPanel);




//Get the searched items from the checkBox
  function  commTabSearchGetSelFields(pn:TWinControl): String;
//Get the searched items of the display name from the checkBox
  function  commTabSearchGetSelCaption(pn:TWinControl): String;
//create the comboBoxes to input the search keyword according to the searched items
  procedure commTabSearch2(pn:TWinControl; RealEStr,DisplayCStr:String; DefaultValue:String='';
            DetailWidth:integer = 250; CaptionWidth:integer = 80;StartVerPos:integer =40; dLen:integer=30);
//Get the searched keywords
  function  commTabSearchGetKeyWords(pn:TWinControl): String;
//Get the searched logic
  function  commTabSearchGetLogic(pn:TWinControl): String;




  //TStrings
  procedure AddNamedValue_Strings( I_Strings:TStrings; I_Name : string; I_Value : string );

  function GetYearFromstr(str: string): integer;//str format:xxxx-xx-xx
  function GetMonthFromstr(str: string): integer;
  function GetDayFromstr(str: string): integer;
  function CheckDate(dstr: string): integer;
  //function ValidateCheck(chktype: integer;chkstr: string):integer;
  function FilterStr(str: string): string;


  //Menu Tool

  function IndexMenuByName( P_Name:string; P_MenuItem:TMenuItem ) :integer;
  procedure SetMenuVis( P_Menu :TMenuItem; P_MenuNames: array of string;  P_MenuVis : array of boolean;
                        P_SetWhat:EnumSetWhat );overload;
  procedure SetMenuVis( IO_Menu : TMenuItem; I_IsVis :boolean ); overload;
  procedure SetMenuVis( IO_Menu : TMainMenu; I_IsVis :boolean );  overload;
  //procedure SetMenuVis( IO_Menu : TPopupMenu; I_IsVis :boolean );  overload;
  procedure SetMenuVis( IO_Menu : TPopupMenu; I_IsVis :boolean;I_EscNum:integer=0 ); overload; //by ls 2003.4.21


  procedure SetCheckBox( P_Control:TCheckBox; P_Bool:boolean; P_SetWhat : EnumSetWhat );

  //Array Tool
  function ArrayCount( I_array : array of string ) : integer;overload;
  function ArrayCount( I_array : array of integer ) : integer;overload;
  function ArrayCount( I_array : array of double ) : integer;overload;

  //Bool Tool
  function BoolToStr(I_Bool:boolean):string; overload;
  function mStrToBool(I_Str:string):boolean;
  function BoolToStr(aCheckBox : TCheckBox):string; overload;
  function GetMidStr(src:string;split1:string;split2:string):string;
  function IsAIntNum(aStr:String):bool;overload;
  function IsAIntNum(aStr:String;ExcludeStr:String):bool;overload;
  function CopyStr(aSrc :String;aPos :Integer; aLength:Integer):String;
  //ComboBox Tool
  procedure SelectItem( I_Item:string; O_Combo :TComboBox ); overload;
  procedure SelectItem( I_Item:integer; O_Combo :TComboBox );overload;
  function SetItems( I_String:TStrings; O_Combo :TComboBox; I_DefIndex :integer = 0 ):boolean;

  //TreeView Tool
  function HasGrandChild(aNode:TTreeNode ):boolean;
  function Tree_Root( I_Tree : TTreeView ) : TTreeNode ;
  procedure StringListToTrees( i_curValue:string;I_ListNode, I_ListPar : TStrings;
                               aTree:TTreeView; O_TreeNode : TTreeNode; InsertNodeName:array of string;
                             I_Can_SameName_InAPar : boolean = false;
                             I_SameName_SameTree : boolean = false  );overload;
  procedure StringListToTrees( i_curPos:Integer;I_ListNode, I_ListPar : TStrings;
                               aTree:TTreeView; O_TreeNode : TTreeNode;  InsertNodeName:array of string;
                             I_Can_SameName_InAPar : boolean = false;
                             I_SameName_SameTree : boolean = false  );overload;
                             
  procedure StringListToTrees( I_ListNode, I_ListPar : TStrings;  aTree:TTreeView;
                   O_TreeNode : TTreeNode; InsertNodeName:array of string;
                  I_Can_SameName_InAPar : boolean = false;
                  I_SameName_SameTree : boolean = false );overload;

  procedure _StringListToTrees( I_CurPos : integer; I_ListNode, I_ListPar : TStrings;
                                I_VistFlg : array of boolean;
                                 aTree:TTreeView; O_TreeNode : TTreeNode;
                                InsertNodeName:array of string;
                                I_Can_SameName_InAPar : boolean; I_SameName_NullTree : boolean   );

  procedure ExpandChildern( I_Node :TTreeNode; I_IsExpandAll : boolean );

  procedure Tree_Copy ( I_Src_Node, O_Dest_Node : TTreeNode );   //for xk 20041103
  function Tree_NewRoot( I_Tree : TTreeView ) : TTreeNode;
  function Tree_FullPath( I_Node : TTreeNode ) : string;
  function Check_DupNode_InParNode( I_ParNode:TTreeNode; I_CurNode_Text:string ):boolean;
  function GetDupNode_InParNode( I_ParNode:TTreeNode; I_CurNode_Text:string ):TTreeNode;
  
  function Get_NameNode_InTreeNodes( I_Tree:TTreeNodes; I_CurNode_Text:string; I_No : integer=1 ):ttreenode;
  function Get_NameNode_HasTree_InTreeNodes( I_Tree:TTreeNodes; I_CurNode_Text:string; I_No : integer=1 ):ttreenode;
  function Get_NameNode_NULLTree_InTreeNodes( I_Tree:TTreeNodes; I_CurNode_Text:string; I_No : integer=1 ):ttreenode;



  Procedure Openform(Aowner:Tcomponent;Formclass:Tformclass;Var fm);
  Procedure OpenSubForm(Frm: TForm;no,name,standard,testno:string);

  function SetFullStr(I_num:integer;I_SetWhat:string;I_Str:string):string;


  function getIPs(): String;
  function IPAddrToName(IPAddr : String): String;



  function  compar_str(name1,name2:Tstrings; getsame:boolean):Tstrings;          //by ls



  function FullIndex(  I_Str:string; I_String:TStrings ) : integer;  // for xk 20041103

  function Get_NameNode_InTreeNodes_ALL( I_Tree:TTreeNodes; I_CurNode_Text:string; I_No : integer; I_Node_Attr : integer ):ttreenode;
  function Get_LikeNameNode_InTreeNodes_ALL(var FindPos:integer; I_Tree:TTreeNodes; I_CurNode_Text:string):ttreenode;





  {VBSCript 运行函数}
  procedure RunVBScript( VBScript :TStrings); overload;
  procedure RunVBScript(VBSciptFileName:String);overload;


  function RunAppByLnk(AppLnkFile:string):Hwnd;
  function  ReadRegistry(KeyName:String):String;
  procedure WriteRegistry(KeyName:String;KeyValue:String);

  procedure MergeTrees( aTree1,aTree2:TTreeView);

  //---------- Move From LS 2010.7.1 ----------------
   
  function StrHasChinese(aStr:String):boolean;//判断字符中是否存在中文
  procedure SetCLBoxSelMod(ClBok:TCheckListBox);
  procedure MoveCLBToTreeNode( ClBox:TCheckListBox;aNode:TTreeNode);
  procedure MoveTreeNodeToCLB( ClBox:TCheckListBox;aTree:TTreeview);
  procedure DelTreeNodeByTextList( aTree:TtreeView;aDelList:TStrings);

    //产品树
  procedure SetNodeImageSeleIndex(aNode:TTreeNode;Index:Integer);

  function EvalScript(aList:TStrings;aFunc:String='main'): Variant;

var
  G_IsBuffered : boolean;



  mErrFuncName:string;         //错误发生的程序位置
  mErrMsg :string;             //非结构性的出错，例如循环中的赋值等，用BgnLoopErr,EndLoopErr,.等处理
  mRaiseErrMsg :string;
  mErrMemo:TMemo;              //显示非结构性错误的Memo指针



  //FormDBMethod: TFormDBMethod;


implementation

//------------VBScript----------------------  by sxd 2008.3.22
procedure RunScript(VBSciptFileName:String;aFunc:AnsiString);
var
  aStrLst : TStringList;
begin
  aStrLst :=  TStringList.Create;
  aStrLst.LoadFromFile(VBSciptFileName);
  RunScript(aStrLst,aFunc);
end;

procedure RunScript(aList:TStrings;aFunc:AnsiString);
var
  sc : Variant;
begin
  sc := CreateOleObject('ScriptControl');
  sc.Language := 'VBScript';
  _RunScript( sc, aList, aFunc );
end;

procedure _RunScript( sc:Variant; aList:TStrings; aFunc:AnsiString );
var
  aStr : String;
  i : integer;
begin
  aStr := '';
  i := 0;
  while(i<aList.Count) do
  begin
   aStr := aStr + aList.Strings[i]+ #13;
   i := i+1;
  end;
  sc.AddCode(aStr);
  if(  aFunc<>'' ) then
    sc.Run(aFunc);
end;

procedure RunJSScript( aList:TStrings;aFunc:AnsiString );
var
  sc : Variant;
begin
  sc := CreateOleObject('ScriptControl');
  sc.Language := 'JScript';
  _RunScript( sc, aList, aFunc );
end;

procedure RunJSScript(aFileName:String;aFunc:AnsiString); overload;
var
  aStrLst : TStringList;
begin
  aStrLst := TStringList.Create();
  aStrLst.LoadFromFile(aFileName);
  try
    RunJSScript(aStrLst,aFunc);
  finally
    aStrLst.Free;
  end;
end;

procedure RunJSScript( aFileName:String );
begin
  RunJSScript( aFileName, '' );
end;

procedure RunJSScript( VBScript :TStrings ) ;
begin
  RunJSScript( VBScript, '' );
end;

{  if VBScript.Count = 0 then exit;

  sc := CreateOleObject('ScriptControl');
  sc.Language := 'JScript';
  try
      aStr1:='';

      for  i:=0 to VBScript.Count-1 do
        aStr1 := aStr1+#13+VBScript.Strings[i];

      sc.AddCode(aStr1);
     // sc.run('main');
  except
      ShowMessage('脚本运行错误：'+#13+
                   '  Description: '+sc.Error.Description+#13+
                   '  Text: '+sc.Error.Text +#13+
                   '  Source: '+sc.Error.Source +#13+
                    '  Line: '+IntToStr(sc.Error.Line-1)+'  Column: '+IntToStr(sc.Error.Column) );
  end;
end;}

procedure RunDMSCript(FileName:String);
var
  sc : Variant;
  aStr1 : string;
begin
  if (not fileexists(FileName)) then raise exception.Create(FileName+'脚本不存在！');
  sc := CreateOleObject('ScriptControl');
  sc.Language := 'VBScript';
  aStr1 := 'Sub RunDMSCript(FileName)'+#13
           + 'Set wb = GetObject(, "AnsysWB.WB.110")'+#13
           + 'Set ag = wb.AppletList.Applet("AGApplet").App'+#13
           + 'ag.Script.agRunScript FileName'+#13+'End Sub' ;

  sc.AddCode(aStr1);
  sc.run('RunDMSCript', FileName );
end;

procedure RunDSSCript(FileName:String);
var
  sc : Variant;
  aStr1 : string;
begin
  if (not fileexists(FileName)) then raise exception.Create(FileName+'脚本不存在！');
  sc := CreateOleObject('ScriptControl');
  sc.Language := 'VBScript';
  aStr1 := 'Sub RunDSSCript(FileName)'+#13
           + 'Set wb = GetObject(, "AnsysWB.WB.110")'+#13
           + 'Set ds = wb.AppletList.Applet("DSApplet").App'+#13
           + 'ds.Script.doToolsRunMacro FileName'+#13+'End Sub' ;

  sc.AddCode(aStr1);
  sc.run('RunDSSCript', FileName );
end;

procedure RunVBScript(VBSciptFileName:String);
var
  aStrLst : TStringList;
begin
  aStrLst := TStringList.Create;
  aStrLst.LoadFromFile(VBSciptFileName);
  try
    RunVBScript(aStrLst);
  finally
    aStrLst.Free;
  end;
end;

procedure RunVBScript( VBScript :TStrings ) ;
var
  sc : Variant;
  i : integer;
  aStr1 : string;
begin
  if VBScript.Count = 0 then exit;
  sc := CreateOleObject('ScriptControl');
  sc.Language := 'VBScript';
  try
      aStr1:='';

      for  i:=0 to VBScript.Count-1 do
        aStr1 := aStr1+#13+VBScript.Strings[i];

      sc.AddCode(aStr1);
      sc.run('main');
  except
      raise Exception.Create('脚本运行错误：'+#13+
                   '  Description: '+sc.Error.Description+#13+
                   '  Text: '+sc.Error.Text +#13+
                   '  Source: '+sc.Error.Source +#13+
                    '  Line: '+IntToStr(sc.Error.Line-1)+'  Column: '+IntToStr(sc.Error.Column) );
  end;
end;


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
procedure AddNamedValue_Strings( I_Strings:TStrings; I_Name : string;  I_Value: string );
begin
    if I_Strings.IndexOfName(I_Name) >= 0 then
      Exit;
    I_Strings.Values[I_Name] := I_Value;
end;



//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
function SetItems( I_String:TStrings; O_Combo :TComboBox; I_DefIndex :integer = 0 ) : boolean ;
begin
  result := True;
  try
    O_Combo.Items := I_String;
    SelectItem( I_DefIndex, O_Combo );
  except
    on E:exception do PromptError( '设置ComboBox.Items出错！'+e.Message );
  end;
end;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
procedure SelectItem( I_Item:integer; O_Combo :TComboBox );
begin
  if ( I_Item < O_Combo.Items.Count ) and ( I_Item>=0 ) then
    O_Combo.ItemIndex := I_Item;
  //O_Combo.OnClick( Nil );
end;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
procedure SelectItem( I_Item:string; O_Combo :TComboBox );
begin
  try
    O_Combo.ItemIndex := O_Combo.Items.IndexOf(I_Item)
  except
    on E:exception do PromptDebugError( format( '选择TComboBox项目(%s)出错！%s', [ I_Item,e.Message] ) );
  end;
end;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
function BoolToStr(aCheckBox : TCheckBox):string;
begin
  result := BoolToStr(aCheckBox.Checked);
end;

function BoolToStr(I_Bool:boolean):string;
begin
  if I_Bool then
    Result := '1'
  else
    Result := '0';
end;

function mStrToBool(I_Str:string):boolean;
begin
  if I_Str='1' then
    result := True
  else
    result := False;
end;

//------------------------------------------------------------------------------
//功能：获取数组元素数量
//------------------------------------------------------------------------------
function ArrayCount( I_array : array of string ) : integer;
begin
  result := high(I_array) - low(I_array) + 1;
end;

function ArrayCount( I_array : array of integer ) : integer;
begin
  result := high(I_array) - low(I_array) + 1;
end;

function ArrayCount( I_array : array of double ) : integer;
begin
  result := high(I_array) - low(I_array) + 1;
end;

{
procedure CheckIntString( P_StringName:array of string; P_String : array of string ); overload;
var
  i:integer;
  aStr:string;
begin
  try
    aStr := '';
    for i:=low( P_StringName ) To high(P_StringName) do
    begin
      try
        CheckIntString( P_StringName[i], P_String[i] );
      except
        on E:exception do aStr := aStr+e.Message+'!'+chr(13);
      end;
    end;
  except
    on E:Exception do raise exception.Create( 'CheckNullString:'+e.Message );
  end;
  if aStr <>'' then  raise exception.Create(aStr);
end;

procedure CheckIntString( I_StringName:string;I_String :string  );overload;
begin
  try
    StrToInt(I_String);
  except
    on E:exception do raise exception.Create( format('整型数(%s)输入不正确！%s',[I_StringName,e.message] ) );
  end;
end;}

procedure CheckIntStrings( P_StringName:array of string; P_String : array of string); overload;
var
  i:integer;
  aStr:string;
begin
  try
    aStr := '';
    for i:=low( P_StringName ) To high(P_StringName) do
    begin
      try
          CheckIntString( P_StringName[i], P_String[i] )
      except
        on E:exception do aStr := aStr+e.Message+'!'+chr(13);
      end;
    end;
  except
    on E:Exception do raise exception.Create( 'CheckNullString:'+e.Message );
  end;
  if aStr <>'' then  raise exception.Create(aStr);
end;

procedure CheckFloatStrings( P_StringName:array of string; P_String : array of string ); overload;
var
  i:integer;
  aStr:string;
begin
  try
    aStr := '';
    for i:=low( P_StringName ) To high(P_StringName) do
    begin
      try
          CheckFloatString( P_StringName[i], P_String[i] )
      except
        on E:exception do aStr := aStr+e.Message+'!'+chr(13);
      end;
    end;
  except
    on E:Exception do raise exception.Create( 'CheckNullString:'+e.Message );
  end;
  if aStr <>'' then  raise exception.Create(aStr);
end;

procedure CheckFloatString( I_StringName:string;I_String :string; I_Min:double=-MaxDouble; I_Max:double=MaxDouble  );
var
  aValue:double;
begin
  try
    aValue := StrToFloat(I_String);
    //if( I_Min>I_Max ) then  exit;
    if( I_Min>I_Max ) then
    begin
      ShowMessage('浮点数('+I_StringName+')的边界定义有问题!不能<'+FloatToStr(I_Min)+'!不能大于'+FloatToStr(I_Max));
      exit;
    end;
    if( aValue < I_Min )then
      raise exception.create(format('浮点数(%s)不能小于%f！',[I_StringName,I_Min] ));
    if( aValue > I_Max )then
      raise exception.create(format('浮点数(%s)不能大于%f！',[I_StringName,I_Max] ));
  except
    on E:exception do raise exception.Create( format('浮点数(%s)输入不正确！%s',[I_StringName,e.message] ) );
  end;
end;

procedure CheckFloatStrings( P_StringName:array of string; P_String : array of string;
                            P_Mins:array of double;P_Maxs:array of double );overload;
var
  i:integer;
  aStr:string;
  aMin,aMax:double;
begin
  try
    aStr := '';
    for i:=low( P_StringName ) To high(P_StringName) do
    begin
      try
        try
          aMin := P_Mins[i];
        except
          aMin := -MaxDouble
        end;
        try
          aMax := P_Maxs[i];
        except
          aMax := MaxDouble
        end;
        CheckFloatString( P_StringName[i], P_String[i], aMin, aMax );
      except
        on E:exception do aStr := aStr+e.Message+'!'+chr(13);
      end;
    end;
  except
    on E:Exception do raise exception.Create( 'CheckNullString:'+e.Message );
  end;
  if aStr <>'' then  raise exception.Create(aStr);
end;

procedure CheckIntString( I_StringName:string;I_String :string; I_Min:Integer=-MAXINT; I_Max:Integer=MAXINT  );
var
  aValue:Integer;
begin
  try
    aValue := StrToInt(I_String);
    //if( I_Min>I_Max ) then  exit;
    if( aValue < I_Min )then
      raise exception.create(format('整型数(%s)不能小于%d！',[I_StringName,I_Min] ));
    if( aValue > I_Max )then
      raise exception.create(format('整型数(%s)不能大于%d！',[I_StringName,I_Max] ));
  except
    on E:exception do raise exception.Create( format('整型数(%s)输入不正确！%s',[I_StringName,e.message] ) );
  end;
end;

procedure CheckIntStrings( P_StringName:array of string; P_String : array of string;
                            P_Mins:array of Integer;P_Maxs:array of Integer );
var
  i:integer;
  aStr:string;
  aMin,aMax:integer;
begin
  try
    aStr := '';
    for i:=low( P_StringName ) To high(P_StringName) do
    begin
      try
        try
          aMin := P_Mins[i];
        except
          aMin := -MaxInt
        end;
        try
          aMax := P_Maxs[i];
        except
          aMax := MaxInt
        end;
        CheckFloatString( P_StringName[i], P_String[i], aMin, aMax );
      except
        on E:exception do aStr := aStr+e.Message+'!'+chr(13);
      end;
    end;
  except
    on E:Exception do raise exception.Create( 'CheckNullString:'+e.Message );
  end;
  if aStr <>'' then  raise exception.Create(aStr);
end;




//------------------------------------------------------------------------------
//功能：检测空字符串
//------------------------------------------------------------------------------
procedure CheckNullString( P_StringName:array of string; P_String : array of string );
var
  i:integer;
  aStr:string;
begin
  try
    aStr := '';
    for i:=low( P_StringName ) To high(P_StringName) do
    begin
      if P_String[i] = '' then
        aStr := aStr + format( '(%s)不能为空!',[P_StringName[i]] );
    end;
  except
    on E:Exception do PromptDebugError( 'CheckNullString:'+e.Message );
  end;
  if aStr <>'' then  raise exception.Create(aStr);
end;


procedure CheckNullString_SetDef( var I_String :string; const I_StringDef:string );
begin
  if I_String = '' then
    I_String := I_StringDef;
end;


procedure CheckNullString( I_String :string; I_StringName:string );
begin
  if I_string = '' then
    raise exception.Create( format('栏位(%s)不能为空！',[I_StringName] ) );
end;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
procedure CheckNullString( I_Edit :TEdit; I_Label:TLabel );
begin
  try
    if I_Edit.Visible and I_Edit.Enabled  then
      CheckNullString( I_Edit.text, I_Label.caption );
  except
    on E:exception do
    begin
      if I_Edit.CanFocus then
        I_Edit.SetFocus;
      raise exception.Create( 'CheckNullString出错！' + e.Message );
    end;
  end;
end;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
procedure CheckNullString( I_Edit :TComboBox; I_Label:TLabel );
begin
  try
    if I_Edit.Visible and I_Edit.Enabled then
      CheckNullString( I_Edit.text, I_Label.caption );
  except
    on E:exception do
    begin
      if I_Edit.CanFocus then
        I_Edit.SetFocus;
      raise exception.Create( 'CheckNullString出错！' + e.Message );
    end;
  end;
end;

{procedure CheckNullString( I_Edits : array of TEdit; I_Labels:TEdits ) ;
var
  i:integer;
begin
  for i:=low(I_Edits) to high(I_Edits) do
  begin
    CheckNullString( I_Edits[i], I_Labels[i] );
  end;
end;}

function GetValue_ByName( I_Str:String; I_Name:String; I_Splitter:string=';'; IsTrim:boolean=true ) : string;
var
  aName, aValue : string;
begin
  SplitStrTo2Str(I_Str,I_Splitter,aName,aValue,IsTrim );
  if aName = I_Name then
    result := aValue
  else
    result := '';
end;

//------------------------------------------------------------------------------
//功能：返回集合中指定名称的值
//例如：[ '01--信息工程系','02--电子工程系','03--计算机系' ], '01'
//------------------------------------------------------------------------------
function GetValue_ByName( I_List:Tstrings; I_Name:String; I_Splitter:string=';'; IsTrim:boolean=true ) : string;
var
  i : integer;
  aName, aValue : string;
begin
  result := '';
  for i:=0 to I_List.Count-1 do
  begin
    SplitStrTo2Str(I_List[i],I_Splitter,aName,aValue,IsTrim );
    if aName = I_Name then
    begin
      result := aValue;
      exit;
    end;
  end;
end;

function GetName_ByValue( I_List:Tstrings; I_Value:String; I_Splitter:string=';'  ) : string;
var
  i : integer;
  aName, aValue : string;
begin
  result := '';
  for i:=0 to I_List.Count-1 do
  begin
     SplitStrTo2Str(I_List[i],I_Splitter,aName,aValue,true );
    if aValue = I_Value then
    begin
      result := aName ;
      exit;
    end;
  end;
end;

//------------------------------------------------------------------------------
//功能：获取Combox项目的实际值 （'English;1' --> '1'）
//输入：
//------------------------------------------------------------------------------
function GetTrueValue(aValue:string;IsTrim:boolean=true) : string;
begin
  result := GetFirstItem( aValue,CSplitter,IsTrim );
end;

function GetFirstItem(aValue:string;aSplitter:string;IsTrim:boolean=true) : string;
var
    aStr:string;
begin
  SplitStrTo2Str(aValue,aSplitter,result,aStr,IsTrim );
end;



//------------------------------------------------------------------------------
//功能： 将Strings格式的str集合转化成单行格式（例如‘MXL;BTL;BOM’）
//------------------------------------------------------------------------------
function StringsToAString(strings : TStrings ; splitter:string=CSplitter) :string ;
var
  i:integer;
begin
  result := '';
  for i:=0 to strings.Count -1 do
  begin
    if i=0 then
      result := Strings[i]
    else
      result := result + splitter + Strings[i];
  end;
end;

//------------------------------------------------------------------------------
//功能： 将单行格式的Str集合（例如‘MXL;BTL;BOM’）转化为Strings格式
//------------------------------------------------------------------------------
procedure AStringToStrings( aString:string; aStrings:TStrings; splitter:string = CSplitter; isMerge:boolean = False );
var
  aStrArray : variant;
  aStr : string;
  i : integer;
begin
  if aString='' then
    exit;

  aStrArray := Split(aString, splitter);
  //if aStrArray = Null then
  if varType(aStrArray) = varNull then
    exit;
  for i:=1 to VarArrayHighBound(aStrArray,1) do
  begin
    aStr := aStrArray[ i ];
    if isMerge then
      if astrings.indexof( aStr ) >= 0  then
          continue;
    astrings.add( aStr );
  end;
end;



Function  pos_Case( delimiter:string;  aStr:string; IsUpperCase:boolean=true ) :  integer;
var
  aStr1:string;
  adelimiter1:string;
begin
    if( IsUpperCase ) then
      result := pos(delimiter,aStr)
    else
    begin
      aStr1 := UpperCase(aStr);
      adelimiter1 :=  UpperCase(delimiter);
      result := pos( adelimiter1,aStr1 );
    end;
end;      

//------------------------------------------------------------------------------
//功能：拆分字符串
//输入: { str / 被拆分的字符串 }   { delimiter / 分割符号 }
//------------------------------------------------------------------------------
function split( str:string; delimiter:string=CSplitter; IsUpperCase:boolean=true ) :variant;
var
  v:variant;
  sT:string;
  nVar:integer;
  curPos :integer;
  Lendeli : integer;
begin
  try
    if str = '' then
      exit;

    Lendeli := length(delimiter);
    nVar := 0;
    sT := str;
    if sT='' then
      sT:=delimiter;

    //---获取item的数量---------

    curPos := pos_Case(delimiter,sT,IsUpperCase);


    while  curPos > 0 do
    begin
      nVar := nVar+1;
      sT := copy( sT, curPos+Lendeli, length(sT)-curPos );
      curPos := pos_Case(delimiter,sT,IsUpperCase);
    end;
    if St <> '' then
      nVar := nVar+1;

    v := varArrayCreate([1,nVar],varVariant);

    nVar := 0;
    sT := str;
    curPos := pos_Case(delimiter,sT,IsUpperCase);
    while  curPos > 0 do
    begin
      nVar := nVar+1;
      v[ nVar ] := copy(sT,1,curPos-1);
      sT := copy( sT, curPos+Lendeli, length(sT)-curPos );
      curPos := pos_Case(delimiter,sT,IsUpperCase);
    end;
    if St <> '' then
      v[ nVar+1 ] := sT;

    result := v;

  except
    on E:exception do raise exception.Create(FmtErrMessage('SPLITER',E.Message));
  end;
end;

//------------------------------------------------------------------------------
//功能：获取Strings的Names集合
//------------------------------------------------------------------------------
function GetStringsNames( I_String : TStrings ) : TStrings;
var
  i : integer;
begin
  result := TStringList.create;
  for i:=0 to I_String.Count-1 do
    result.Add(I_String.Names[i]);
end;

//------------------------------------------------------------------------------
//功能：获取I_String的Names集合      by sxd 2008.6.7
//例子：GetStringsNames( "No=001;classNo=005" ) --> "No;ClassNo"
//------------------------------------------------------------------------------
function GetStringsNames( I_String : String; I_Splitter:string=';' ) : String;
var
  aStrings : TStrings;
begin
  aStrings := GetStringsNames( splitToStrings( I_String, I_Splitter ) );
  result := StringsToAString( aStrings, I_Splitter );
  aStrings.Destroy;
end;

//------------------------------------------------------------------------------
//功能：获取I_String的Values集合      by sxd 2008.6.7
//例子：GetStringsValues( "No=001;classNo=005" ) --> "001;005"
//------------------------------------------------------------------------------
function GetStringsValues( I_String : String; I_Splitter:string=';';IsTrim:boolean=true=true ) : String;
var
  aStrings : TStrings;
//  aStr : String;
begin
  aStrings := GetStringsValues( splitToStrings( I_String, I_Splitter ), IsTrim );

  result := StringsToAString( aStrings, I_Splitter );
  aStrings.Destroy;
end;

//------------------------------------------------------------------------------
//功能：获取Strings的Values集合
//------------------------------------------------------------------------------
function GetStringsValues( I_String : TStrings; IsTrim:boolean=true ) : TStrings;
var
  i : integer;
  aStrName,aStrValue : String;
begin
  result := TStringList.create;
  for i:=0 to I_String.Count-1 do
  begin
    SplitStrTo2Str( I_String.Strings[i],'=',aStrName,aStrValue, IsTrim );
    result.Add( aStrValue );
    //result.Add(I_String.Values[I_String.Names[i]]);
  end;
end;

//------------------------------------------------------------------------------
//功能：获取命名集合的命名值（例如，001=西安电子科技大学）
//------------------------------------------------------------------------------
function GetItem_NamedValue( I_String :TStrings; I_ItemIndex:integer ) : string;
begin
  try
    result:='';
    if I_ItemIndex<0 then exit;
    result := I_String[I_ItemIndex];
    if pos( '=', result )>0 then
      result := I_String.names[I_ItemIndex];       //by sxd
  except
    on E:exception do PromptDebugError( 'GetItem_NamedValue'+e.Message );
  end;
end;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
function MergeLists( aList:TList; bList:TList ):TList;
var
  i :integer;
begin
  result := aList;
  for i:=0 to bList.Count-1 do
  begin
    result.Add( bList[i] );
  end;
end;

//------------------------------------------------------------------------------
//功能：将两个Strings合并
//例子：AString = [ 'A', 'B' ], BString=[ 'C','D','E' ], result = [ 'A','B','C','D','E']
//  [ isMaskMerge ]  / True,合并时去除同类项； False: 不去除
//------------------------------------------------------------------------------
function MergeStrings( aString:TStrings; bStrings:TStrings; isMaskMerge:boolean ):Tstrings;
var
  i :integer;
begin
  //result := MergeLists( aString,  bStrings, isMaskMerge );

  result := aString;
  for i:=0 to bStrings.Count-1 do
  begin
    if isMaskMerge then
      if result.IndexOf( bStrings[i] ) >= 0 then
        continue;
    result.Add( bStrings[i] );
  end;
end;

//------------------------------------------------------------------------------
//功能：将两个Strings相加
//例子：AString = [ 'A', 'B' ], BString=[ 'C','D','E' ], result = [ 'A;C','B;D' ]
//------------------------------------------------------------------------------
function MergeString( aString:TStrings; bString:TStrings; splitter : string ):TStrings;overload;
var
  i:integer;
begin
  result := aString;
  try
    for i:=0 to bString.Count-1 do
    begin
      result[i] := result[i] +splitter+ bString[i];
    end;
  except
  end;
end;


//------------------------------------------------------------------------------
//功能：
//------------------------------------------------------------------------------
{function splitToArray( aInString:string; O_Array : array of string; aInDelimiter:string=CSplitter ):boolean;
var
  aStrings : TStrings;
begin
  result := true;
  try
    aStrings := splitToStrings(aInString,aInDelimiter );
    result := StringsToArray( aStrings, O_Array );
  except
    on E:exception do
    begin
      result := False;
      promptDebugError('splitToArray:'+e.Message);
    end;
  end;
end;

//------------------------------------------------------------------------------
//功能：
//------------------------------------------------------------------------------
function StringsToArray( aString : TStrings; O_Array : array of string ):boolean;
var
  i :integer;
begin
  result := True;
  try
    setlength( O_Array, aString.Count );          //SetLength
    for i:=0 to aString.Count-1 do
      O_Array[i] := aString[i];
  except
    on E:exception do
    begin
      result := False;
      promptDebugError('splitToArray:'+e.Message);
    end;
  end;
end; }

//------------------------------------------------------------------------------
//功能：'ax*bas-aa'  -->  List (ax)(*)(bas)(-)(aa)
//参数：splitToStrings_WithSplitter( 'ax*bas-aa', ['+','*','-','\']
//------------------------------------------------------------------------------
function splitToStrings_WithSplitter( aInString : string; aInSplitters : array of string; IsUpperCase:boolean=true ) : TStringList;
var
  aList, aListTmp, aListTmp1 : TStringList;
  i,j,k : integer;
begin
  aList := TStringList.Create;
  aListTmp := TStringList.Create;
  aListTmp.Add( aInString );
  for i:= low(aInSplitters) to high(aInSplitters) do
  begin
    aList.Clear;

    for j:=0 to aListTmp.Count-1 do
    begin
      if IsIn( aListTmp[j], aInSplitters ) then        //2012.12.20 by sxd
      begin
        aList.Add( aListTmp[j] ) ;
        continue;
      end;

        aListTmp1 :=  splitToStrings( aListTmp[j], aInSplitters[i], true, IsUpperCase );
        for k:=0 to aListTmp1.Count-1 do
          aList.Add( aListTmp1[k] );

    end;
    aListTmp.Clear;
    for k:=0 to aList.Count-1 do
      aListTmp.Add( aList[k] );
  end;
  result:=aList;
end;
//------------------------------------------------------------------------------
//功能：'ax*bas-aa'  -->  List (ax)(*)(bas)(-)(aa)
//     by sxd 2008.3.22
//------------------------------------------------------------------------------
function splitToStrings( aInString : string; aInSplitters : array of string; isWithSplitter:boolean=False; IsUpperCase:boolean=true  ) : TStringList;
var
  aList : TStringList;
  i : integer;
begin
  aList := splitToStrings_WithSplitter( aInString, aInSplitters, IsUpperCase );

  if( not isWithSplitter ) then       //去除分割符
  begin
    i:=0;
    while i<aList.Count-1 do
    begin
      if IsIn( aList[i], aInSplitters ) then
        aList.Delete(i)
      else
        i:=i+1;
    end;
  end;
  result := aList;
end;

function splitToStrings( aInString : string; aInSplitters : TStrings; isWithSplitter:boolean=False; IsUpperCase:boolean=true  ) : TStringList;overload;
var
  arrayStr : arraystring;
begin
  arrayStr := StringListToArray(  aInSplitters );
  result := splitToStrings( aInString, arrayStr, isWithSplitter, IsUpperCase  )

end;

//------------------------------------------------------------------------------
//功能：'ax;b;as;aa'  -->  List (ax)(b)(as)(aa)
//------------------------------------------------------------------------------
function splitToStrings( aInString:string; aInDelimiter:string=CSplitter; isWithSplitter:boolean=False; IsUpperCase:boolean=true  ) : TStringList;
var
  i:integer;
  aSubStringArray : variant;
begin
  result := TStringList.Create();

  aSubStringArray := split( aInString, aInDelimiter, IsUpperCase );
  if VarIsEmpty(aSubStringArray) then
    exit;

  //形成返回字符串
  for i:=1 to VarArrayHighBound(aSubStringArray,1) do
  begin
    try
      result.Add( aSubStringArray[i] );
      if ( isWithSplitter=true ) and (i<VarArrayHighBound(aSubStringArray,1)) then
        result.Add( aInDelimiter );
    except
    end;
  end;

  //“(5)”, ")" 的情况
  if (isWithSplitter=true) and (IsSuffix(aInString,aInDelimiter)) then
    result.Add( aInDelimiter );

end;

{function GetSubString( aInString:string; aInPos:integer; aInDelimiter:string=';' ):string;
var
  i:integer;
  aSubStringArray : variant;
begin
  result := '';
  aSubStringArray := split( aInString, aInDelimiter );
  try
    result := aSubStringArray[ aInPos ];
  except
  end;
end

function IndexOfString( aInString:string; aFindString )
begin
  aSqlWords := split( aSqlText, ' ' );
  for i:=1 to VarArrayHighBound(aSqlWords,1) do
  begin
    astr := uppercase( trim( aSqlWords[ i ] ) );

  end;  //for
end; }

//---------------------------------------------------------------------------
procedure AssignSCrollBar(Img:TImage;sbH,sbV:TScrollBar;Panel1:TPanel);
begin
   if (img.Width>Panel1.Width)or(img.height>Panel1.height)then
   begin
     img.Align:=alNone;
     if img.Width-panel1.Width>0 then
       sbH.Max:=img.Width-panel1.Width;
     if img.Height-panel1.Height>0 then
       sbV.Max:=img.Height-panel1.Height;
   end
   else
     img.Align:=alClient;
end;  

//---------------------------------------------------------------------------
procedure GetStrPoint(strPoint:string;var x:integer;var y:integer);
var
  s: string;
  iPos: integer;
begin
  iPos := pos(',',strPoint);
  s := copy( strPoint, 1,iPos -1 ); //( pos(strPoint,' ') - 1 ) );
  x := strtoint( s );
  s := copy( strPoint, iPos+1, length(strPoint)-iPos );
  y := strtoint( s );
end;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
function NotStrField( I_SqlStr:string ) : string;
begin
  result := CFlg_NoStr + I_SqlStr;
end;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
function NotEqualField( I_SqlStr:string ) : string;
begin
  result := CFlg_NotEqu + I_SqlStr;
end;

function LikeField( I_SqlStr:string ) :string;
begin
  result := CFlg_LikeField + I_SqlStr;
end;


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
function FmtWdtString( I_N:integer; I_String:string; I_AddChar:string ):string;
var
  i:integer;
begin
  result := I_String;
  if length(I_String)>=I_N then  exit;

  result := '';
  for i:=0 to ( I_N - length(I_String) - 1 ) do
    result := result + I_AddChar;
  result := result +  I_String;
end;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
function Left( I_String :string; aLen : integer ):string;
begin
  result := copy( I_String, 1, min( aLen,length(I_String)) );
end;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
function IsSuffix( I_Str, I_Suffix :string ) : boolean; overload;
begin
  result := ( UpperCase(I_Suffix) = UpperCase( Right( I_Str, length(I_Suffix) ) ) );         //UnCase处理
  //result := ( I_Suffix = Right( I_Str, length(I_Suffix) ) );
end;

function Right( I_Str :string; I_Length : integer ) : string;
begin
  result := copy( I_Str, max( 1, length(I_Str)-I_Length+1 ), I_Length );
end;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

function IsSuffix( I_Str:String ; I_Suffix :TStringList ) : boolean;overload;
var
  i : integer;
begin

  if (I_Suffix=Nil) then
  begin
    result := false;
    exit;
  end;

  for i:= 1 to I_Suffix.Count do
  begin
    if( IsSuffix( I_Str, I_Suffix.Strings[i] ) = true ) then
    begin
      result := true;
      exit;
    end;
  end;
  result := false;
end;

function IsPreFix( I_String:String; I_PreFix:TStringList ) : boolean;overload;
var
  i : integer;
begin

  if (I_PreFix=Nil) then
  begin
    result := false;
    exit;
  end;

  for i:= 1 to I_PreFix.Count do
  begin
    if( IsPreFix( I_String, I_PreFix.Strings[i-1] ) = true ) then
    begin
      result := true;
      exit;
    end;
  end;
  result := false;
end;

function IsPreFix( I_String:string; I_PreFix:string ) : boolean;overload;
begin
  //result := ( I_PreFix = Left( I_String, length(I_PreFix) ) );
  result := ( UpperCase( I_PreFix ) = UpperCase( Left( I_String, length(I_PreFix) ))  );        //UnCase处理
end;

function RemoveSuffix( I_String :string; I_Suffix:string ) :string;
begin
  if IsSuffix( I_String, I_Suffix ) then
    result := left( I_String, length(I_String)-length(I_Suffix) )
  else
    result := I_String;
end;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
function RemovePrefix( I_String :string; I_Prefix:string ) :string;
begin
  if IsPrefix( I_String, I_Prefix ) then
    result := Right( I_String, length(I_String)-length(I_PreFix) )
  else
    result := I_String;  
  //result := copy( I_String, length(I_Prefix)+1, length(I_String)-length(I_Prefix) )
end;



//------------------------------------------------------------------------------
//功能： 设置显示‘非结构性错误’的Memo
//------------------------------------------------------------------------------
procedure SetLoopErrPanel(aMemo:TMemo);
begin
  mErrMemo := aMemo;
end;

//------------------------------------------------------------------------------
//功能：收集处理过程中的错误
//------------------------------------------------------------------------------
procedure BgnLoopErr(aFuncName:string);
begin
  //----显示已经发生的Exception-----
  ShowLoopErr;

  //----初始化----------------------
  mErrMsg := '';
  mRaiseErrMsg:='';
  mErrFuncName := aFuncName;
end;

//procedure RaiseLoopErr();
//begin
//  if mErrMsg <> ''  then  raise exception.Create(FmtErrMessage(mErrFuncName,mErrMsg));
//end;

procedure SetMyMsg( I_ErrStr:string; I_ErrMemo:TMemo );
begin
  if I_ErrMemo = Nil then
    ShowMessage(I_ErrStr)
  else
    I_ErrMemo.Lines.Add ( I_ErrStr );
end;

procedure Prompt( aStr:string );                     //输入提示
begin
  //SetMyMsg( aStr,mErrMemo,msgPrompt );
  SetMyMsg( aStr,mErrMemo );
end;

procedure PromptError( aStr:string );                //出错提示
begin
  //SetMyMsg( aStr,mErrMemo,msgError);
  SetMyMsg( aStr,mErrMemo );
end;

procedure PromptDebugError( aStr:string );           //Debug Error
begin
  if C_Debug then
    //SetMyMsg( aStr,mErrMemo,msgLoopError);
   SetMyMsg( aStr,mErrMemo );
end;

procedure ShowLoopErr();
var
  aStr:string;
begin
  if mErrMsg <> ''  then
  begin
    //SetMyMsg( FmtErrMessage(mErrFuncName,mErrMsg),mErrMemo,msgLoopError);
    SetMyMsg( FmtErrMessage(mErrFuncName,mErrMsg),mErrMemo);
    mErrMsg:='';
  end;
  if mRaiseErrMsg<>'' then
  begin
    aStr:=mRaiseErrMsg;
    mRaiseErrMsg:='';
    raise exception.Create(FmtErrMessage(mErrFuncName,aStr));
  end;
end;

//------------------------------------------------------------------------------
// [ aIndex : 循环序号，如果＝－1，则不在循环 ]
//------------------------------------------------------------------------------
procedure AddLoopErr( const aNowErr:string; aIndex:integer ); overload;
begin
  mErrMsg := mErrMsg + format( '[%d: %s]',[aIndex,aNowErr] );
end;

procedure AddLoopErr(const aNowErr:string ); overload;
begin
  mErrMsg := mErrMsg + format( '[%s]',[aNowErr] )+#13;
end;

procedure AddRaiseErr(const aNowErr:string );
begin
  mRaiseErrMsg := mRaiseErrMsg + format( '[%s]',[aNowErr] );
end;

function GetLoopErr():string;
begin
  result := mErrMsg;
end;



//------------------------------------------------------------------------------
//功能：设置指定Control及其子Control的状态
//------------------------------------------------------------------------------
procedure EnableControls(pn:TWinControl; isEnable:boolean);
var
  i:integer;
  aName :string;
begin
  for i:=0 to (pn.ControlCount-1) do
  begin
    try
      if pn.Controls[i] = Nil then
        continue;

      pn.Controls[i].Enabled := isEnable;
      aName := upperCase( pn.Controls[i].className );
      if ( aName = 'TGROUPBOX' ) or
         ( aName = 'TPANEL' ) then
        EnableControls(TWinControl(pn.Controls[i]),isEnable);
    except
    end;
  end;
end;

//------------------------------------------------------------------------------
//功能：保存指定Control及其子Control的Enable状态
//说明：将状态保存在Control的Hint中
//------------------------------------------------------------------------------
procedure SaveControlStatus(pn:TWinControl);
var
  i:integer;
  aName :string;
begin
  for i:=0 to (pn.ControlCount-1) do
  begin
    try
      if pn.Controls[i] = Nil then
        continue;

      if pn.Controls[i].Enabled  then
       pn.Controls[i].Hint := 'Y'+ pn.Controls[i].Hint
      else
       pn.Controls[i].Hint := 'N'+ pn.Controls[i].Hint;

      aName := upperCase( pn.Controls[i].className );
      if ( aName = 'TGROUPBOX' ) or
         ( aName = 'TPANEL' ) then
        SaveControlStatus(TWinControl(pn.Controls[i]));
    except
    end;
  end;
end;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
procedure RestoreControlStatus(pn:TWinControl);
var
  i:integer;
  aName :string;

  procedure RestoreAControl( aControl:TControl) ;
  var
    aFlg:string;
  begin
    with aControl do
    begin
      if length(Hint) <=0 then
        exit;
      aFlg := copy( Hint,1,1);
      if ( aFlg <> 'Y' ) and ( aFlg <> 'N' ) then
        exit;
      if aFlg='Y' then
        aControl.Enabled := True;
      if aFlg='N' then
        aControl.Enabled := False;
      Hint := copy( Hint,2,length(Hint)-1);
    end;
  end;

begin
  for i:=0 to (pn.ControlCount-1) do
  begin
    try
      if pn.Controls[i] = Nil then
        continue;
      RestoreAControl( pn.Controls[i] );

      aName := upperCase( pn.Controls[i].className );
      if ( aName = 'TGROUPBOX' ) or
         ( aName = 'TPANEL' ) then
        RestoreControlStatus(TWinControl(pn.Controls[i]));
    except
    end;
  end;
end;

//------------------------------------------------------------------------------
///////////////*2001.12.4 By LiJunFeng     The function clears the subcontrols of a parent control///
//------------------------------------------------------------------------------
procedure ClearControls(pn:TWinControl);
begin
  with pn do
  begin
    while ControlCount>0 do
      Controls[ControlCount-1].parent:=nil;
      Controls[ControlCount-1].Free;
  end;
end;

function RightPos( aStr:string; aSplitter:string ) : integer;
var
  aOldPos, aPos : integer;
begin
  aOldPos := 0;

  while 0<1 do
  begin
    aPos := pos( aSplitter,aStr );
    if( aPos <= 0 ) then
      break;

    aOldPos := aOldPos + aPos ;
    aStr := Copy( aStr, aPos+1, length(aStr) );
  end;
  result := aOldPos;
end;

// [ FromLeft -- 当无aSplitter时， True / aStr2不为"" ； False / aStr1不为空 ]
procedure SplitStrTo2Str_Right( aSrcStr:string; aSplitter:string; var aStr1:string; var aStr2:string; FromLeft:boolean; IsTrim:boolean=true);
var
  aPos : integer;
begin
  aPos := RightPos( aSrcStr, aSplitter );
  _SplitStrTo2Str( aPos, aSrcStr, aSplitter, aStr1, aStr2, IsTrim );

  if( (FromLeft=true) and (aStr2='') ) then
  begin
    aStr2 := aStr1;
    aStr1 := '';
  end
end;

//------------------------------------------------------------------------------
//功能：将aSrcStr分割成aStr1和aStr2，分割符号为aSplitter
//      例如： aSrcStr = 'DAIHAO;FUMIAN'  ; aSplitter = ';' aStr1='DAIHAO'  aStr2='FUMIAN'
//------------------------------------------------------------------------------
procedure SplitStrTo2Str( aSrcStr:string; aSplitter:string; var aStr1:string; var aStr2:string;IsTrim:boolean=true);
var
  aPos : integer;
begin

  aPos := pos( UpperCase(aSplitter), UpperCase(aSrcStr) );    //2011.12修改，加入UpperCase， 防止大小写敏感
  _SplitStrTo2Str( aPos, aSrcStr, aSplitter, aStr1, aStr2, IsTrim );

end;

procedure _SplitStrTo2Str( aPos : integer; aSrcStr:string; aSplitter:string; var aStr1:string; var aStr2:string;IsTrim:boolean=true);
begin
  if aPos > 0 then
  begin
    //aStr1 := Trim(Copy(aSrcStr,1,aPos-1));
    //aStr2 :=Trim( Copy(aSrcStr,aPos+length(aSplitter),Length(aSrcStr)-(aPos+length(aSplitter)-1)));
    aStr1 := Copy(aSrcStr,1,aPos-1);                                                                 //mod by sxd 2009.11.2
    aStr2 := Copy(aSrcStr,aPos+length(aSplitter),Length(aSrcStr)-(aPos+length(aSplitter)-1));        //mod by sxd 2009.11.2

    if( IsTrim = true ) then
    begin
      aStr1 := Trim( aStr1 );
      aStr2 := Trim( aStr2 );
    end;
  end
  else
  begin
    aStr1 := aSrcStr;
    aStr2 := '';
  end;
end;

procedure SplictStrToVar( const aSrcStr:string; const aSplitter:char; var aVarStrs:Variant);
var
  i :integer;
  aTmp :TStrings;
begin
  aTmp := TStringlist.Create;
  try
    aTmp.Delimiter :=  aSplitter;
    aTmp.DelimitedText := aSrcStr;
    for i:=VarArrayLowBound(aVarStrs,1) to  VarArrayHighBound(aVarStrs,1) do
      aVarStrs[i] := Trim(aTmp.Strings[i]);
  finally
    aTmp.free;
  end;
end;
function SplictStrToVar(const aSrcStr:string; const aSplitter:char):Variant;
var
  i :integer;
  aTmp :TStrings;
  A: Variant;
begin
  aTmp := TStringlist.Create;
  try
    
    aTmp.Delimiter :=  aSplitter;
    aTmp.DelimitedText := aSrcStr;
    A := VarArrayCreate([0, aTmp.Count-1], varVariant);
    for i:=0 to  aTmp.Count-1 do
      A[i] := Trim(aTmp.Strings[i]);
    result := A;
  finally
    aTmp.free;
  end;
end;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
function CreateDbCombox(aPanel:TWinControl;aLeft,aTop:integer) : TDBCombobox;
begin
  result:=TDBComboBox.create(aPanel);             //Combox的处理
  with result do
  begin
    Parent:=aPanel;
    Left:=aLeft;
    Top:=aTop;
   // width := 30;
    Style :=csSimple;
    font.Color :=clBlue;
    font.Size :=10;
  end;
end;

function CreateLabel(aPanel:TWinControl;aLeft,aTop:integer;aWidth:integer) : TLabel;
begin
  result:=TLabel.Create(aPanel);               //Label处理
  with result do
  begin
    Parent:=aPanel;
    Left:=aLeft;
    AutoSize:=false;
    width:=aWidth;
    Top:=aTop;
    font.Size :=10;
  end;   //with LblName
end;





//Get the searched items from the checkBox
function  commTabSearchGetSelFields(pn:TWinControl): String;
var
  selstr:string;
  i:integer;
begin
  selstr:='';
  with pn do
  begin
    for i:=0 to ControlCount -1 do
    begin
      if Controls[i] is TCheckBox then
      begin
        if (Controls[i] as TCheckBox).Checked then
        begin
          selstr:=selstr+(Controls[i] as TCheckBox).Hint+csplitter;
        end;
      end;
    end;
  end;
  result:=selstr;
end;

//Get the searched items of the display name from the checkBox
function  commTabSearchGetSelCaption(pn:TWinControl): String;
var
  selstr:string;
  i:integer;
begin
  selstr:='';
  with pn do
  begin
    for i:=0 to ControlCount -1 do
    begin
      if Controls[i] is TCheckBox then
      begin
        if (Controls[i] as TCheckBox).Checked then
        begin
          selstr:=selstr+(Controls[i] as TCheckBox).Caption+csplitter;
        end;
      end;
    end;
  end;
  result:=selstr;
end;


//create the comboBoxes to input the search keyword according to the searched items
procedure commTabSearch2(pn:TWinControl; RealEStr,DisplayCStr:String; DefaultValue:String='';
            DetailWidth:integer = 250; CaptionWidth:integer = 80;StartVerPos:integer =40; dLen:integer=30);
var
  i,toppos,leftpos,Count:integer;
  selEstr,selCStr,dv:variant;

  Cap:TLabel;
  rgs:Array of TRadioGroup;
  caps:Array of TLabel;
  cmbs:Array of TComboBox;
begin
  ClearControls(pn);
  if RealEStr='' then
    exit;
  selEstr:= Split(RealEStr, csplitter);
  selCstr:= Split(DisplayCStr, csplitter);
  if VarIsEmpty(selEstr) then
    exit;
    
  if DefaultValue<>'' then
    dv:= Split(DefaultValue, csplitter);
  Cap:=TLabel.Create(pn);
  with Cap do
  begin
    Parent:=pn;
    Caption:='请输入查询字段的关键字及组合逻辑';
    Align:=alTop;
    Font.Color :=clRed;
    Font.Size :=10;
  end;
  Count:=VarArrayHighBound(selEstr,1);
  SetLength(caps,Count);
  SetLength(cmbs,Count);
  SetLength(rgs,Count-1);
  toppos:=StartVerPos;
  leftpos:=(pn.Width -DetailWidth) div 2;
  for i:=0 to Count-1 do
  begin
    caps[i]:=TLabel.Create(pn);
    with caps[i] do
    begin
      Parent:=pn;
      Left:=leftpos;
      Top:=toppos;
      Width:=CaptionWidth;
      Caption :=selCstr[i+1];
      Hint:=selEstr[i+1];
      Alignment:=taRightJustify;
      Font.Color :=clBlue;
      Font.Size :=10;
    end;
    cmbs[i]:=TComboBox.Create(pn);
    with cmbs[i] do
    begin
      Parent:=pn;
      Left:=leftpos+CaptionWidth;
      Top:=toppos;
      toppos:=toppos+dLen;
      Width:=DetailWidth-CaptionWidth-leftpos;
      Hint:=selEstr [i+1];
      Font.Color :=clBlue;
      Font.Size :=10;
      Tag:=i;
      if DefaultValue<>'' then
        Text:=dv[ i+1 ];
    end;
    if i=Count-1 then
      Break;
    rgs[i]:=TRadioGroup.Create(pn);
    with rgs[i] do
    begin
      Parent:=pn;
      Left:=leftpos;
      Top:=toppos;
      toppos:=toppos+dLen+5;
      Width:=DetailWidth-2;
      Height:=dLen;
      items.Add('与');
      items.Add('或');
      Columns:=2;
      Caption:='';
      Font.Color :=clBlue;
      Font.Size :=10;
      Tag:=i;
    end;
  end;
end;

//Get the searched keywords
function  commTabSearchGetKeyWords(pn:TWinControl): String;
var
  str:String;
  tl:Array of String;
  i,cn:integer;
begin
  with pn do
  begin
    cn:=0;
    for i:=0 to ControlCount -1 do
    begin
      if Controls[i] is TComboBox then
        inc(cn);
    end;
    setLength(tl,cn);
    for i:=0 to ControlCount -1 do
    begin
      if Controls[i] is TComboBox then
      begin
        tl[(Controls[i] as TComboBox).Tag]:=(Controls[i] as TComboBox).Text;
      end;
    end;
  end;
  for i:=0 to cn-1 do
    str:=str+tl[i]+csplitter;
  result:=str;
end;

//Get the searched logic
function  commTabSearchGetLogic(pn:TWinControl): String;
var
  str:String;
  tl:Array of String;
  i,cn:integer;
begin
  with pn do
  begin
    cn:=0;
    for i:=0 to ControlCount -1 do
    begin
      if Controls[i] is TRadioGroup then
        inc(cn);
    end;
    setLength(tl,cn);
    for i:=0 to ControlCount -1 do
    begin
      if Controls[i] is TRadioGroup then
      begin
        if (Controls[i] as TRadioGroup).ItemIndex =0 then
          tl[(Controls[i] as TRadioGroup).Tag]:='and'
        else
          tl[(Controls[i] as TRadioGroup).Tag]:='or'
      end;
    end;
  end;
  for i:=0 to cn-1 do
    str:=str+tl[i]+csplitter;
  result:=str;
end;

//------------------------------------------------------------------------------
//功能： 检查DataSet的NewTable关联 （根据SYS_RELATION）
//说明： 某些TABLE，例如SYS_BOMS，在ADD/DELETE一个记录时，要同时向数据库ADD/DELETE一个USER TABLE
//       USERTABLE = SYS_RELATION.FIELDNAME( 例如MBNAME )。 本函数检测 aInDataSet的NEWTABLE关联
//参数： { aOutTblName / 如果aInDataSet有NEWTABLE关联，返回其TABLENAME , 例如BOM;BOM1 }
//       { aOutTblDefNames / 创建NEWTABLE时的DEFAULT字段的索引，参见SYS_FIELDSDEF / TABLENAME=SYSNEWTABLE1 }
//------------------------------------------------------------------------------
{procedure CheckRelation_NewTable( aInDataSet: TADOTable;
                                  var aOutTblName:string; var aOutTblDefName: string );
var
  aQry_SysRelation: TADOQuery;
begin

  aOutTblName := '';
  CreateTmpSet( G_DBName, aQry_SysRelation );


  try
    //-------查找aInDataSet的NEWTABLE关联---------------------
    if not OpenQuery(aQry_SysRelation,sysRelation,
                   CFLD_TblName_Relation+CSplitter+CFLD_RelType_Relation,
                   aInDataSet.TableName+csplitter+CRELATION_NEWTABLE ) then
      raise exception.Create( FmtErrMessage('CheckRelation_NewField',
                     '无法打开Sys_Relation+('+aInDataSet.TableName+csplitter+CRELATION_NEWTABLE+')') );

    with aInDataSet do
    begin
      aOutTblName := fieldbyName(aQry_SysRelation.fieldbyName(CFLD_FldName_Relation).AsString).AsString;
      aOutTblDefName := aQry_SysRelation.fieldbyName(CFLD_RelTblName_Relation).AsString
    end;
  finally
    aQry_SysRelation.Close;
    aQry_SysRelation.Free;
  end;

end; }

//------------------------------------------------------------------------------
//功能： 检查DataSet的NewField关联 （根据SYS_RELATION）
//说明： 某些TABLE，例如SYS_FIELDSDEF，在ADD/DELETE/EDIT一个记录时，要同时向数据库的某个
//       TABLE ADD/DELETE一个USER FIELD
//       USERTABLE = SYS_RELATION.TABLENAME; USERFIELD=SYS_RELATION.FIELDNAME。
//       本函数检测 aInDataSet的NEWFIELD关联
//参数： { aOutTblName / 如果aInDataSet有NEWTABLE关联，返回其TABLENAME , 例如BOM;BOM1 }
//       { aOutTblDefNames / 创建NEWTABLE时的DEFAULT字段的索引，参见SYS_FIELDSDEF / TABLENAME=SYSNEWTABLE1 }
//------------------------------------------------------------------------------
{procedure CheckRelation_NewField( aInDataSet: TADOTable;
                                  var aOutTblName:string; var aOutFieldName: string );
var
  aQry_SysRelation: TADOQuery;
begin

  aOutTblName := '';
  CreateTmpSet( G_DBName, aQry_SysRelation );

  try
    //-------查找aInDataSet的NEWFIELD关联---------------------
    if not OpenQuery(aQry_SysRelation,sysRelation,
                     CFLD_TblName_Relation+CSplitter+CFLD_RelType_Relation,
                     aInDataSet.TableName+csplitter+CRELATION_NEWFIELD ) then
      raise exception.Create( FmtErrMessage('CheckRelation_NewField',
                     '无法打开Sys_Relation+('+aInDataSet.TableName+csplitter+CRELATION_NEWFIELD+')') );

    with aInDataSet do
    begin
      aOutTblName := fieldbyName(aQry_SysRelation.fieldbyName(CFLD_RelTblName_Relation).AsString).AsString;
      aOutFieldName := fieldbyName(aQry_SysRelation.fieldbyName(CFLD_FldName_Relation).AsString).AsString;
     end;
  finally
    aQry_SysRelation.Close;
    aQry_SysRelation.Free;
  end;

end; }

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
procedure FmtStrings( aStrings:TStrings; IsTrim:boolean=true=True; isUpperCase:boolean=True );
var
  i :integer;
begin
  for i:=0 to aStrings.Count-1 do
  begin
    if isTrim then
      aStrings[i] :=  trim( aStrings[i]);
    if isUpperCase then
      aStrings[i] :=  upperCase( aStrings[i]);
  end;
end;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
function IsLike( const aWholeStr:string; const aSubStr: string ):boolean;overload;
begin
  result := uppercase( Left( aWholeStr, Length(aSubStr) ) ) = uppercase(aSubStr) ;
end;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
function IsLike( const aInStr:string; const aInStrArray: Array of string ):boolean;overload;
var
  i:integer;
begin
  result:= False;
  if aInStr = '' then
    exit;
  for i:=low(aInStrArray) to high(aInStrArray) do
  begin
    if  IsLike(aInStr, aInStrArray[i]) then
      result:=True;
  end;
end;

Function IsLike(Const aInStr:string; Const aInStringS :Tstrings):boolean;overload;         //by ls 5.20
var
  i:integer;
  aStrArray:array of string;
begin
  result:=False;
  if aInStr = '' then
    exit;
  setlength( aStrArray,aInstrings.Count);
  for i:=0 to  aInstrings.Count-1 do
    aStrArray[i]:=aInsTrings.Strings[i];
  result:=IsIn(aInStr,aStrArray);
end;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
function IsIn( const aInStr:string; const aInStrArray: Array of string ):boolean;overload;
var
  i:integer;
begin
  result:= False;
  for i:=low(aInStrArray) to high(aInStrArray) do
  begin
    if UpperCase(aInStrArray[i])=UpperCase(aInStr) then
      result:=True;
  end;
end;

Function IsIn(Const aInStr:string; Const aInStringS :Tstrings):boolean;overload;         //by ls 5.20
var
  i:integer;
  aStrArray:array of string;
begin
  result:=False;
  if( aInStringS=nil )then
    exit;
  setlength( aStrArray,aInstrings.Count);
  for i:=0 to  aInstrings.Count-1 do
    aStrArray[i]:=aInsTrings.Strings[i];
  result:=IsIn(aInStr,aStrArray);
end;

Function IsIn(Const aInStr:string; Const aStrStrings : String; const aSp : String):boolean;overload;
var
  aInStrings : TStrings;
begin
  aInStrings := SplitToStrings( aStrStrings, aSp );
  result:=IsIn( aInStr, aInStrings );
  aInStrings.destroy;
end;

//------------------------------------------------------------------------------
//功能：获取 aInString中　所有aInLeftSP和aInRightSP作为分界符的 子字符串　
//例子：GetSubStrBySP( "2.0*%A%+cos(%B%)","%","%" ), 返回｛"%A%","%B%"}
//------------------------------------------------------------------------------
function GetSubStringListBySP( aInString:string; aInLeftSP:string; aInRightSP:string;isWithSP:boolean =False; IsTrim:boolean=true ):TStrings;
var
  aStr, aStr1, aStr2 : string;
begin
  aStr:=aInString;
  result:=TStringList.create();
  while aStr<>'' do
  begin

    if( aInLeftSP='' ) then
      aStr2:=aStr
    else
      SplitStrTo2Str( aStr, aInLeftSP, aStr1, aStr2, IsTrim );
    if( aStr2='' ) then
      exit;
    SplitStrTo2Str( aStr2, aInRightSP, aStr1 , aStr2, IsTrim );
    if isWithSP then
      aStr1 := aInLeftSP + aStr1 + aInRightSP;
    result.Add( aStr1 );

    if( aStr=aStr2 ) then   //防止死锁
      break;

    aStr := aStr2;
  end;
end;

//------------------------------------------------------------------------------
//功能：获取 aInLeftSP和aInRightSP作为分界符的 子字符串　
//例子：GetSubStrBySP( 1, "2.0*%A%+cos(%B%)", "%", "%" ), 返回"%B%"
//------------------------------------------------------------------------------
function GetSubStrBySP( I_Index:integer; aInString:string; aInLeftSP:string; aInRightSP:string; isWithSP:boolean=False ):string;
var
  aStrings : TStrings;
begin
  aStrings := GetSubStringListBySP( aInString, aInLeftSP, aInRightSP, isWithSP );
  if( I_Index < aStrings.Count ) then
    result := aStrings[ I_Index ]
  else
    result := '';

  aStrings.free;

  //aStr:=aInString;
  //aIndex:=-1;
  //result:='';
  //while aIndex<I_Index do
  //begin
  //  SplitStrTo2Str( aStr, aInLeftSP, aStr1, aStr2 );
  //  if( aStr2='' ) then
  //    exit;
  //  aStr := aStr2;
  //  aIndex:=aIndex+1;
  //end;
  //SplitStrTo2Str( aStr1, aInRightSP, result, aStr2 );
  //if isWithSP then
  //  result := aInLeftSP + result + aInRightSP;
end;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
function NamedItem( I_Index:integer; aInString:string; aInDelimiter:string=CSplitter ) :string;
var
  aStringList : TStringList;
  aIndex : integer;
  aErrMsg :string;
begin
  try
    result := '';
    aErrMsg := '';
    aStringList := splitToStrings( aInString, aInDelimiter );
    if I_Index < 0 then
      aIndex := aStringList.Count-1
    else
      aIndex := I_Index;

    if aStringList.Count > 0 then
      result := aStringList[ aIndex ];
  except
    on e:exception do aErrMsg := e.Message;
  end;
  aStringList.Free;

  if aErrMsg<>'' then
    raise exception.Create( 'LastItem出错！'+aErrMsg );
end;

function FirstItem( aInString:string; aInDelimiter:string=CSplitter ) :string;
begin
   result := NamedItem( 0, aInString, aInDelimiter );
end;

function LastItem( aInString:string; aInDelimiter:string=CSplitter ) :string;
begin
   result := NamedItem( -1, aInString, aInDelimiter );
end;
//------------------------------------------------------------------------------
//例子： IndexLookupList( aStrings, "NAME", '=' )
//      在{(NAME=A), (CAPTION=骨架) }　查找
//修改：2009.9.17 加入aBgn = 0参数, 以便控制查询的起始位置
//------------------------------------------------------------------------------

procedure _IndexLookupList ( I_LookupList:TStrings; I_Text:string; I_Splitter:string; var pos:integer;
                             var value:string;  aBgn : integer = 0; IsTrim:boolean=true );
var
  i : integer;
  s1,s2 :string;
begin
  pos:=-1;
  value:='';
  for i:=aBgn to I_LookupList.Count-1 do
  begin
    SplitStrTo2Str( I_LookupList.Strings[i], I_Splitter, s1, s2, IsTrim );
    if UpperCase( I_Text ) = UpperCase( s1 ) then
    begin
      pos := i;
      value := s2;
      exit;
    end;
  end;
end;

function IndexLookupList ( I_LookupList:TStrings; I_ItemName:string; I_Splitter:string; IsTrim:boolean=true ):integer;
var
  sValue : string;
begin
  _IndexLookupList( I_LookupList, I_ItemName, I_Splitter, result, sValue, 0 , IsTrim );
end;

{function IndexLookupList ( I_LookupList:TStrings; I_Text:string; I_Splitter:string ):integer;
var
  i : integer;
begin
  result := -1;
  for i:=0 to I_LookupList.Count-1 do
  begin
    if I_Text = GetFirstItem( I_LookupList.Strings[i], I_Splitter ) then
    begin
      result := i;
      exit;
    end;
  end;
end; }

//-----------------Set_ListItem-------------------------------------------------
procedure Set_ListItems_ByName( I_LookupList:TStrings; I_ItemName:string; I_Splitter:string; aValue:String );
var
  aIndex : integer;
  aStr : string;
  aBgn : integer;
begin

  aBgn := 0;
  while 1 <> 0 do
  begin
    try
      _IndexLookupList( I_LookupList, I_ItemName, I_Splitter, aIndex, aStr, aBgn, True );
      if( aIndex < 0 ) then
        exit;
      aBgn := aIndex + 1;
      I_LookupList.Strings[aIndex] := I_ItemName + I_Splitter + aValue;
    except
    end;
  end
end;


procedure Set_ListItemStr_ByName ( I_LookupList:TStrings; I_ItemName:string; I_Splitter:string; I_Str:string );overload;
var
  aPos : integer;
  aStr : string;
begin
  _IndexLookupList( I_LookupList, I_ItemName, I_Splitter, aPos, aStr, 0, True );
  if( aPos < 0 ) then
    exit;
  I_LookupList.Strings[aPos] := I_ItemName + I_Splitter + I_Str;
end;

procedure Set_ListItemStr_ByName( var aStr: String; aSp1:String; aItemName:String; aSp2:String; I_Value:String );overload;
var
  aStrings : TStrings;
begin
  aStrings := splitToStrings( aStr, aSp1 );
  Set_ListItemStr_ByName( aStrings, aItemName, aSp2, I_Value );
  aStr := StringsToAString( aStrings, aSp1 );
  aStrings.Destroy;
end;


//------------------------------------------------------------------------------
//修改：2009.9.17 , 获取所有以I_ItemName为名称，以I_Splitter为分割的项目
//------------------------------------------------------------------------------
function Get_ListItems_ByName( I_LookupList:TStrings; I_ItemName:string; I_Splitter:string; IsTrim:boolean=true ):TStrings;
var
  aIndex : integer;
  aStr : string;
  aBgn : integer;
begin
  result := TStringList.Create();
  aBgn := 0;

  while 1 <> 0 do
  begin
    try
      _IndexLookupList( I_LookupList, I_ItemName, I_Splitter, aIndex, aStr, aBgn, IsTrim );
      if( aIndex < 0 ) then
        exit;
      aBgn := aIndex + 1;
      result.Add( aStr );
    except
    end;
  end
end;


//function Get_ListItemStr_ByName ( I_LookupList:TStrings; I_ItemName:string; I_Splitter:string; IsTrim:boolean=true ):string;
//var
//  aIndex : integer;
//begin
//  _IndexLookupList( I_LookupList, I_ItemName, I_Splitter, aIndex, result, 0,  IsTrim );
//end;

function Get_ListItemStr_ByName( aStr:String; aSp1:String; aItemName:String; aSp2:String; aDefValue:String; isTrim : bool=true ):String;overload;
var
  aStrings : TStrings;
begin
  aStrings := splitToStrings( aStr, aSp1 );
  result := Get_ListItemStr_ByName( aStrings, aItemName, aSp2, aDefValue, isTrim );
  aStrings.Destroy;
end;


function Get_ListItemStr_ByName ( I_LookupList:TStrings; I_ItemName:string; I_Splitter:string; I_Default:string; IsTrim:boolean=true ):string;
var
  aPos : integer;
  aStr : string;
begin
  result := I_Default;
  _IndexLookupList( I_LookupList, I_ItemName, I_Splitter, aPos, aStr, 0, IsTrim );
  if( aPos < 0 ) then
    exit;
  result := aStr;
end;

function StrToBool1 ( aStr:string ):bool;
begin
    aStr := UpperCase( aStr );
    if( ( aStr = 'FALSE' ) or ( aStr = 'F' ) or (aStr='0') ) then
      result := false
    else
      result := true;
end;


function Get_ListItemBool_ByName ( I_LookupList:TStrings; I_ItemName:string; I_Splitter:string; I_Default:bool ):bool;
var
  aPos : integer;
  aStr : string;
begin
  result := I_Default;
  _IndexLookupList( I_LookupList, I_ItemName, I_Splitter, aPos, aStr );
  if( aPos < 0 ) then
    exit;
  try
    result := StrToBool1( aStr );
  except
    result := I_Default;
  end;
end;

function Get_ListItemFloat_ByName ( I_LookupList:TStrings; I_ItemName:string; I_Splitter:string; I_Default:double ):double;
var
  aPos : integer;
  aStr : string;
begin
  result := I_Default;
  _IndexLookupList( I_LookupList, I_ItemName, I_Splitter, aPos, aStr );
  if( aPos < 0 ) then
    exit;
  try
    result := StrToFloat( aStr );
  except
  end;
end;

//------------------------------------------------------------------------------
function MergeItemsToStrings( const aInStrArray: Array of string) : Tstrings;overload ;
begin
  result := splitToStrings( MergeItems( aInStrArray ) ) ;
end;

//------------------------------------------------------------------------------
//  功能：合并Tstrings中的字符中间以I_InSp分开
//------------------------------------------------------------------------------
function MergeItems(const I_string:Tstrings;I_InSp:string) :String;  //by ls 2003.4.21
var
  i:integer;
  aStr:string;
begin
  result:='';
  if I_String.Count=0 then exit;
  aStr:=I_string.Strings[0];
  for I:=1 to I_string.Count-1  do
  begin
    aStr :=aStr+I_InSp+I_string.Strings[i];
  end;
  result:=aStr;
end;

{//------------------------------------------------------------------------------
//功能： 合并字符串
//------------------------------------------------------------------------------
function MergeItems( const aInStrArray: Array of string; aInSp:string=CSplitter ) : string;
var
  i:integer;
  aStr :string;
begin
  result:='' ;
  try
    for i:=low(aInStrArray) to high(aInStrArray) do
    begin
      aStr := removeSuffix( aInStrArray[i], aInSp );    //去除最后的分割符号
      if i=low(aInStrArray) then
        result:=aStr
      else
        result := result+aInSp+aStr
    end;
    if result <> '' then
      result := result+aInSp;
  except
    on E:exception do PromptError(  '合并字符串出错！'+ e.Message );
  end;
end;}


//------------------------------------------------------------------------------
//功能： 合并字符串
//------------------------------------------------------------------------------
function MergeItems( const aInStrArray: Array of string; aInSp:string=CSplitter ) : string;overload;
var
  i:integer;
  aStr :string;
begin
  result:='' ;
  try
    for i:=low(aInStrArray) to high(aInStrArray) do
    begin
      aStr := removeSuffix( aInStrArray[i], aInSp );    //去除最后的分割符号
      if i=low(aInStrArray) then
        result:=aStr
      else
        result := result+aInSp+aStr
    end;
    if result <> '' then
      result := result+aInSp;
  except
    on E:exception do PromptError(  '合并字符串出错！'+ e.Message );
  end;
end;


function GetYearFromstr(str: string): integer;//str format:xxxx-xx-xx
begin
  try
    result := strtoint(Copy(str,1,4));
  except
    result := -1;
  end;
end;

function GetMonthFromstr(str: string): integer;
begin
  try
    if str[6] = '0' then
      result := strtoint(Copy(str,7,1))
    else
      result := strtoint(Copy(str,6,2));
  except
    result := -1;
  end;
end;

function GetDayFromstr(str: string): integer;
begin
  try
    if str[9] = '0' then
      result := strtoint(Copy(str,10,1))
    else
      result := strtoint(Copy(str,9,2));
  except
    result := -1;
  end;
end;

function CheckDate(dstr: string): integer;
var
  i: integer;
begin
  if Length(dstr) <> 10 then begin
    result := 2;
    MessageBox(0,'日期自段格式有误，请检查日期的长度！','出错',MB_ICONERROR+MB_OK);
    exit;
  end;
  if (GetYearFromstr(dstr)<1000) then begin
    result := 3;
    MessageBox(0,'日期自段格式有误，请检查日期的年份！','出错',MB_ICONERROR+MB_OK);
    exit;
  end;
  i := GetMonthFromstr(dstr);
  if (i<1)or(i>12) then begin
    result := 4;
    MessageBox(0,'日期自段格式有误，请检查日期的月份！','出错',MB_ICONERROR+MB_OK);
    exit;
  end;
  i := GetDayFromstr(dstr);
  if (i<1)or(i>31) then begin
    result := 5;
    MessageBox(0,'日期自段格式有误，请检查日期的天数！','出错',MB_ICONERROR+MB_OK);
    exit;
  end;
  result := -1;
end;


//------------------------------------------------------------------------------
//功能： 字段输入值合法性check
//------------------------------------------------------------------------------
procedure ValidCheck(aComBox:TDBComboBox); overload;
var
  aMinValue,aMaxValue :string ;
  procedure GetMinAndMax(aStr:string);
  var
    pp: integer;
  begin
    if aStr <> '' then
    begin
      pp := pos('-',aStr);
      aMaxValue := Copy(aStr,pp+1,Length(aStr)-pp);
      aMinValue := Copy(aStr,1,pp-1);
    end;
  end;

begin
  with aCombox do
  begin
    GetMinAndMax(Hint);
    try
      ValidCheck(Tag,Text,aMinValue,aMaxValue);               //类型检测
    except
      on E:exception do
      begin
        Prompt( 'ValidCheck出错！'+ e.Message );
        aComBox.SetFocus;
      end;
    end;

  end;
end;

//------------------------------------------------------------------------------
//功能： 检测输入的合法性
//输入:  ChkType : 检测类型，整型、实型、年月日等
//       ChkStr : 输入的值
//       minValue,maxValue ： 要求检测的Min和Max值
//------------------------------------------------------------------------------
procedure ValidCheck( chktype: integer; chkstr: string;
                         minValue:string ; maxValue :string  ); overload;
var
  aValue : variant;
  aMinValue, aMaxValue :variant;
begin 
  aValue := TypeCheck(chktype,chkstr);
  if varType(aValue) = varString then
    exit;
    
  try
    aMinValue := TypeCheck(chktype,minValue);
    aMaxValue := TypeCheck(chktype,maxValue);
  except
    exit;
  end;
  if ( aValue < min( aMinValue,aMaxValue ) ) or ( aValue > max( aMinValue,aMaxValue) ) then
    raise exception.Create( '输入的数值必须在('+vartostr(aMinValue)+','+vartostr(aMaxValue)+')之间');
end;

//------------------------------------------------------------------------------
//Return value = -1  success
//                0  integer error
//                1  numeric error
//                2  Date error  (Length of date)
//                3  Date error  (Length of Year)
//                4  Date error  (Length of Month)
//                5  Date error  (Length of Day)
//------------------------------------------------------------------------------
function TypeCheck( chktype: integer; chkstr: string ) : variant;
var
  aType : integer;
begin
  result := '';

  aType := chktype;
  if aType = cCheckType_Integer then          //整型检测
  begin //整数
    try
      result := strtoint(chkstr);
    except
      raise exception.Create('字段格式错误，请检查输入值是否为整数！');
    end;
    exit;
  end ;

  if aType = cCheckType_Float then         //数字
  begin
    try
      result := strtofloat(chkstr);
    except
      raise exception.Create('字段格式错误，请检查输入值是否为数值！');
    end;
  end;

  if aType = cCheckType_Date then begin    //xxxx-xx-xx
    // CheckDate(chkstr);
    try
      result := StrToDate( chkStr );
    except
      raise exception.Create('字段格式错误，请检查输入值是否为日期格式！');
    end;
    exit;
  end;

  if aType = cCheckType_Time then begin    //xxxx-xx-xx
    // CheckDate(chkstr);
    try
      result := StrToTime( chkStr );
    except
      raise exception.Create('字段格式错误，请检查输入值是否为时间格式！');
    end;
    exit;
  end;
end;

function FilterStr(str: string): string;
var
  pp: integer;
begin
  pp := pos(CSplitter,str);
  if pp>0 then
    result := copy(str,1,pp-1)
  else
    result := str;
end;


//------------------------------------------------------------------------------
//Start FileNme 处理
//------------------------------------------------------------------------------
procedure GetFilesInDir( O_Files : TStrings; I_PathName : string; I_ExtName : string = '*.*' ; IsRecursion:bool=true; aType:integer=faAnyFile );
var
  aPath : string;
  aFileName : string;
  Tp:TSearchRec;
begin

  //---输入的是文件-----
  if FileExists( I_PathName ) or ( not DirectoryExists( I_PathName )) then
    exit;

  aPath:= I_PathName ;
  if findfirst( aPath+'\*.*', aType, Tp )<> 0 then
    exit;

  while 1<2 do
  begin
    if not isIn( Tp.Name, [ '.', '..' ]) then
    begin
      if IsSuffix( aPath, PathSplitter ) then
        aFileName :=  aPath+Tp.Name
      else
        aFileName :=  aPath+PathSplitter+Tp.Name;

      //---存储------
      if ( I_ExtName = '*.*' ) or ( I_ExtName = '*' ) or
         (  uppercase( GetFileExt( aFileName ) ) = uppercase( I_ExtName ) ) then
        if O_Files.IndexOf( aFileName ) < 0 then
            O_Files.Add( aFileName );

      //---递归------
      if FileExists( aFileName ) then
      begin
      end
      else if( IsRecursion = true ) then
        GetFilesInDir(  O_Files, aFileName, I_ExtName )

    end;

    if findNext(Tp) <> 0 then
      break;
  end;

  Sysutils.FindClose(Tp);
end;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
function GetPathName( aFileName:string ) : string;
var
  aStrings:TStrings;
  i:integer;
begin
  result := '';
  try
    aStrings := splitToStrings( aFileName,PathSplitter );
    for i:=0 to AStrings.Count-2 do
      if i=0 then
        result := AStrings[i]
      else
        result := result + PathSplitter+AStrings[i];
  except
  end;
end;

function GetFileName_NoPath( aFileName :string ):string;
var
  aStrings:TStrings;
begin
  result := '';
  try
    aStrings := splitToStrings( aFileName,PathSplitter );
    if AStrings.Count > 0 then
      result := AStrings[AStrings.Count-1];
  except
  end;
end;

function isAbsPath( aFileName :String ) :boolean;
begin
  result:=True;
  //showmessage( format( ' %s %d %d ',[aFileName,Pos( aFileName,'\\' ),Pos( aFileName,':\' ) ]));
  if Pos( '\\',aFileName )>0 then
    exit;
  if Pos(':\', aFileName )>0 then
    exit;
  result := False;
end;

function GetFullFileName( aFileName:string  ):string;
var
  aPathName:string;
begin

   if isAbsPath( aFileName ) then
   begin
      result := aFileName;
      exit;
   end;
  //showmessage(GetCurrentDir);
  aPathName := GetCurrentDir;
  try
    //chDir( mPathName );
    chDir( GetPathName(aFileName) );
//    showmessage(GetPathName(aFileName));
//    showmessage(GetCurrentDir);
    result := GetCurrentDir()+PathSplitter+GetFileName_NoPath(aFileName);
  except
  end;
  chDir(aPathName);
  //showmessage(GetCurrentDir);
end;

function GetFileExt( aFileName :string ):string;
var
  aStrings:TStrings;
begin
  result := '';
  try
    aStrings := splitToStrings( aFileName,'.' );
    if AStrings.Count > 0 then
      result := AStrings[AStrings.Count-1];
    aStrings.free;  //???? *** need test
  except
    on e:exception do PromptError( 'GetFileExt出错！' + e.Message );
  end;
end;

function GetFileName_NoExt( aFileName :string ):string;
var
  aStrings:TStringList;
  i:integer;
begin
  result := '';
  try
    aStrings := splitToStrings( aFileName,'.' );
    try
      for i:=0 to AStrings.Count-2 do
        if result ='' then
          result := AStrings[i]
        else
          result := result + '.'+AStrings[i];
    finally
      aStrings.Free;
    end;
  except
  end;
end;
//------------------------------------------------------------------------------
//End FileNme 处理
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//功能：给定Menu的Name，返回其在MenuItems中的位置   by sxd
//------------------------------------------------------------------------------
function IndexMenuByName( P_Name:string; P_MenuItem:TMenuItem ) :integer;
var
  i:integer;
begin
  result := -1;
  for i:=0 to P_MenuItem.Count do
  begin
    if uppercase( P_Name ) = uppercase( P_MenuItem[i].Name ) then
    begin
      result := i;
      exit;
    end;
  end;
end;

procedure SetMenuVis( IO_Menu : TMenuItem; I_IsVis :boolean );
var
  i:integer;
begin
  for i:=0 to IO_Menu.Count-1 do
  begin
    try
      IO_Menu.Items[i].Enabled:=I_IsVis;
    except
    end;
  end;
end;

procedure SetMenuVis( IO_Menu : TPopupMenu; I_IsVis :boolean ;I_EscNum:integer=0 );  //by ls 2003.4.21
var
  i:integer;
begin
  if IO_Menu=Nil then  exit;
  if  (IO_Menu.Items.Count-1-I_EscNum)<0 then exit;  //by ls 2003.4.21
  for i:=0 to (IO_Menu.Items.Count-1-I_EscNum) do    //by ls 2003.4.21
    IO_Menu.Items[i].enabled :=  I_IsVis ;
end;

procedure SetMenuVis( IO_Menu : TMainMenu; I_IsVis :boolean );
var
  i:integer;
begin
  if IO_Menu=Nil then  exit;
  for i:=0 to IO_Menu.Items.Count-1 do
    SetMenuVis( IO_Menu.Items[i], I_IsVis );
end;

{procedure SetMenuVis( IO_Menu : TPopupMenu; I_IsVis :boolean );
var
  i:integer;
begin
  if IO_Menu=Nil then  exit;
  for i:=0 to IO_Menu.Items.Count-1 do
    IO_Menu.Items[i].enabled :=  I_IsVis ;
end;}

//------------------------------------------------------------------------------
//功能：设置MenuItem(一个菜单条)的可见性 by sxd
//例子： SetMenu(  TrvMenu, [ 'NewDoc', 'DelDoc' ], [ True, False ] );
//------------------------------------------------------------------------------
procedure SetMenuVis( P_Menu :TMenuItem; P_MenuNames: array of string;  P_MenuVis : array of boolean;
                      P_SetWhat:EnumSetWhat );
var
  i:integer;
  aPos:integer;

begin
  for i:=low(P_MenuNames) to high(P_MenuNames) do
  begin
     aPos := IndexMenuByName( P_MenuNames[i], P_Menu );
     if aPos >= 0 then
       case P_SetWhat of
         E_swVisible : P_Menu[aPos].Visible := P_MenuVis[i];
         E_swEnable : P_Menu[aPos].Enabled := P_MenuVis[i];
       end;
  end;
end;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
procedure SetCheckBox( P_Control:TCheckBox; P_Bool:boolean; P_SetWhat : EnumSetWhat );
begin
  try
    case P_SetWhat of
      E_swVisible :  P_Control.visible := P_Bool;
      E_swEnable :  P_Control.enabled := P_Bool;
      E_swCheck :  P_Control.checked := P_Bool;
    end;
  except
    on E:exception do PromptDebugError( '设置CheckBox出错！'+e.Message );
  end;
end;

//判断该节点有无子孙
function HasGrandChild(aNode:TTreeNode ):boolean;
var
  i:integer;
begin
  for i:=0 to aNode.Count-1 do
  begin
    if ( aNode.Item[i].HasChildren ) then
    begin
      result := true;
      exit;
    end;
  end;
  result:=false;
end;
//------------------------------------------------------------------------------
//说明:TopItem属性为可见的最左上节点，而非根节点
//------------------------------------------------------------------------------
function Tree_Root( I_Tree : TTreeView ) : TTreeNode ;
begin
  if ( I_Tree = Nil ) then
  begin
    result := Nil;
  end  
  else
    result := I_Tree.Items.GetFirstNode;
end;

//------------------------------------------------------------------------------
//功能：判别要加入的节点(I_CurNode_Text)是否已经在父节点（I_ParNode）下存在
//------------------------------------------------------------------------------
function Check_DupNode_InParNode( I_ParNode:TTreeNode; I_CurNode_Text:string ):boolean;
var
  aNode : TTreeNode;
begin
  result := false;
  aNode := I_ParNode.getFirstChild();
  while aNode<>Nil do
  begin
    if uppercase( aNode.Text ) =  uppercase( I_CurNode_Text ) then
    begin
      result := true;
      exit;
    end;
    aNode := I_ParNode.GetNextChild( aNode );
  end;
end;

function GetDupNode_InParNode( I_ParNode:TTreeNode; I_CurNode_Text:string ):TTreeNode;
var
  aNode : TTreeNode;
begin
  result := nil;
  aNode := I_ParNode.getFirstChild();
  while aNode<>Nil do
  begin
    if uppercase( aNode.Text ) =  uppercase( I_CurNode_Text ) then
    begin
      result := aNode;
      exit;
    end;
    aNode := I_ParNode.GetNextChild( aNode );
  end;
end;

//------------------------------------------------------------------------------
//功能：在TTreeNodes中获取名称为 I_CurNode_Text 的节点
//参数：[ I_Tree / 节点集合 ]
//      [ I_CurNode_Text / 指定节点名称 ]
//      [ I_No / 要获取的实例号 ]
//      [ I_Node_Attr : 0/所有指定名称节点； 1/指定名称非空节点；2/指定名称空节点 ]
//------------------------------------------------------------------------------

function Get_NameNode_InTreeNodes_ALL( I_Tree:TTreeNodes; I_CurNode_Text:string; I_No : integer; I_Node_Attr : integer ):ttreenode;
var
  i : integer;
  No : integer;
begin
  result := nil;
  No := 1;
  for i:=0 to  I_Tree.Count-1 do
  begin
    if uppercase( I_Tree.Item[ i ].Text ) =  uppercase( I_CurNode_Text ) then
    begin

      //非空节点判别
      if ( I_Node_Attr =1 ) and ( I_Tree.Item[ i ].getFirstChild = Nil ) then
        continue;
      //空节点判别
      if ( I_Node_Attr =2 ) and ( I_Tree.Item[ i ].getFirstChild <> Nil ) then
        continue;

      if No>=I_No then
      begin
        result := I_Tree.Item[ i ];
        exit;
      end
      else
        No := No+1;
    end;
  end;
end;

function Get_LikeNameNode_InTreeNodes_ALL(var FindPos:integer; I_Tree:TTreeNodes; I_CurNode_Text:string):ttreenode;
var
  i : integer;
  FrmPos :integer;
begin
  result := nil;
  FrmPos := FindPos;
  for i:=FrmPos to  I_Tree.Count-1 do
  begin
    if (pos(uppercase( I_CurNode_Text ) ,uppercase( I_Tree.Item[ i ].Text ))>0) then
    begin
      result := I_Tree.Item[ i ];
      FindPos:=i+1;
      break;
    end;
   end;
end;

//------------------------------------------------------------------------------
//功能：判别要加入的节点(I_CurNode_Text)是否已经在当前树（I_Tree）下存在
//------------------------------------------------------------------------------
function Get_NameNode_InTreeNodes( I_Tree:TTreeNodes; I_CurNode_Text:string; I_No : integer=1 ):ttreenode;
begin
  result := Get_NameNode_InTreeNodes_ALL( I_Tree, I_CurNode_Text, I_No, 0 );
end;

function Get_NameNode_HasTree_InTreeNodes( I_Tree:TTreeNodes; I_CurNode_Text:string; I_No : integer=1 ):ttreenode;
begin
  result := Get_NameNode_InTreeNodes_ALL( I_Tree, I_CurNode_Text, I_No, 1 );
end;

function Get_NameNode_NULLTree_InTreeNodes( I_Tree:TTreeNodes; I_CurNode_Text:string; I_No : integer=1 ):ttreenode;
begin
  result := Get_NameNode_InTreeNodes_ALL( I_Tree, I_CurNode_Text, I_No, 2 );
end;

//------------------------------------------------------------------------------
//参数： [ I_Can_SameName_InAPar ]  True/允许同名子节点；False/不允许
//       [ I_SameName_NullTree ] True/第二个以后的同名节点不含子树; False/含
//------------------------------------------------------------------------------
procedure _StringListToTrees( I_CurPos : integer;
                              I_ListNode, I_ListPar : TStrings;
                              I_VistFlg : array of boolean;
                               aTree:TTreeView; O_TreeNode : TTreeNode;
                              InsertNodeName:array of string;
                              I_Can_SameName_InAPar : boolean;
                              I_SameName_NullTree : boolean );
var
  i ,j : integer;
  aNode : TTreeNode;

  aPar, aGrandPar : string;
  aExsitNode : TTreeNode;
  NodeId: Pindex ;
begin

  if O_TreeNode = Nil then
    exit;

  for i:=0 to I_ListNode.Count-1 do
  begin

    SplitStrTo2Str( I_ListPar[i], '--', aPar, aGrandPar, true );

    //if ( I_ListPar[i] = I_ListNode[I_CurPos] ) and ( I_VistFlg[i]=false )then
    if ( I_VistFlg[i]=false )then
    begin
      if aGrandPar<>'' then
        aGrandPar := aGrandPar;
      if  ( ( aPar = I_ListNode.Names[I_CurPos] ) and ( aGrandPar='' ) ) or
          ( ( aPar = I_ListNode.Names[I_CurPos] ) and ( aGrandPar=I_ListPar[I_CurPos] ) ) then
      begin
        if ( I_Can_SameName_InAPar ) or
           ( not Check_DupNode_InParNode( O_TreeNode, I_ListNode.Values[I_ListNode.Names[i]] ) ) then
        begin

          if I_SameName_NullTree then
            aExsitNode := Get_NameNode_InTreeNodes( aTree.Items,  I_ListNode.Values[I_ListNode.Names[i]] );

          for  j:= low(InsertNodeName) to high(InsertNodeName)  do
            if not Check_DupNode_InParNode( O_TreeNode, InsertNodeName[j] ) then
              aNode :=  aTree.Items.AddChild( O_TreeNode, InsertNodeName[j]  )
            else
              if j= high(InsertNodeName) then 
                aNode := GetDupNode_InParNode( O_TreeNode, InsertNodeName[j] );

          new(NodeId);
          NodeId^.index_id :=  I_ListNode.Names[i];

          //aNode := O_TreeNodes.AddChild( O_TreeNode,  I_ListNode.Values[I_ListNode.Names[i]] );
          aNode :=  aTree.Items.AddChildObject( aNode,  I_ListNode.Values[I_ListNode.Names[i]]+'_1' ,NodeId);
          //aNode.Data := Ptr( I_CurPos );
          I_VistFlg[i] := true;

          if ( not I_SameName_NullTree ) or
             ( ( I_SameName_NullTree ) and ( aExsitNode = nil ) ) then
            _StringListToTrees( i, I_ListNode, I_ListPar, I_VistFlg,  aTree, aNode, InsertNodeName,I_Can_SameName_InAPar, I_SameName_NullTree )
        end;

      end;
    end;
  end;

end;

//------------------------------------------------------------------------------
//参数： [ I_TreeNodes / 产品树节点集合 ]
//------------------------------------------------------------------------------
//procedure Copy_SameNode_SubTrees( I_TreeNodes:TTreeNodes; I_NodeText :string );
//var
//  aNode_HasSubTree : TTreeNode;
//  aNode_NullSubTree : TTreeNode;
//begin
//  aNode_HasSubTree :=
//end;

//------------------------------------------------------------------------------
//功能：将从数据库读入的表结构转换成‘树形’结构
//例如：( I_ListNode： [ 'x','x.2','x.1','x.2.1' ], I_ListPar：[ '', 'x', 'x', 'x.2' ]
//修改：
//  (1)2004/11/2 增加祖父节点的识别处理 某些情况，由于父节点会出现重号现象，需要
//     用其祖父节点判别。为兼容原版本，出入口参数不变，格式变为(如有祖父节点识别)：
//  I_ListNode： [ 'x','x.2','x.1','x.2.1' ], I_ListPar：[ '', 'x--', 'x--', 'x.2--x' ]
//     其中 '--'分割父节点和祖父节点
//  I_Can_SameName_InAPar : True/允许同一节点下的同名子节点， Flase/不允许
//  I_SameName_SameTree : True/保持同名节点相同子树， False / 不保持
//------------------------------------------------------------------------------
procedure StringListToTrees( i_curValue:string;I_ListNode, I_ListPar : TStrings;
                              aTree:TTreeView; O_TreeNode : TTreeNode;
                             InsertNodeName:array of string;
                             I_Can_SameName_InAPar : boolean = false;
                             I_SameName_SameTree : boolean = false  );
var
  aCurPos:integer;
begin
  aCurPos:= I_ListNode.IndexOfName(i_curValue);
  StringListToTrees( aCurPos,I_ListNode, I_ListPar,
                             aTree,O_TreeNode , InsertNodeName,
                             I_Can_SameName_InAPar,
                             I_SameName_SameTree );
end;

procedure StringListToTrees( i_curPos:Integer;I_ListNode, I_ListPar : TStrings;
                              aTree:TTreeView; O_TreeNode : TTreeNode;
                             InsertNodeName:array of string;
                             I_Can_SameName_InAPar : boolean = false;
                             I_SameName_SameTree : boolean = false  );
var
  i : integer;
  aRootPos : integer;          //树的根节点
  aNode : TTreeNode;
  aVisFlgs :array of boolean;  //遍历标志，防止死循环
  aSameName_NullTree : boolean;
  NodeId:Pindex;
begin
  try
    if ( I_ListNode.Count <= 0 ) then
      exit;

    if ( I_ListNode.Count <> I_ListPar.Count ) then
      raise exception.Create( 'StringListToTrees出错!输入的树结构格式不对！' );


   //-----------------------确定起始节点位置---------------------

    //-----设置未遍历标志-------
    setlength( aVisFlgs, I_ListNode.Count );
    for i:= low(aVisFlgs) to high(aVisFlgs) do
      aVisFlgs[i] := False;

    aRootPos := i_curPos;


    if aRootPos = -1 then
      raise exception.Create( 'StringListToTrees出错！没有根节点！' );
     new(NodeId);
     NodeId^.index_id :=I_ListNode.Names[aRootPos];
    if O_TreeNode=Nil then
      //aNode := O_TreeNodes.Add( O_TreeNode, I_ListNode.Values[I_ListNode.Names[aRootPos]] )
        aNode := aTree.Items.AddChildObject( O_TreeNode, I_ListNode.Values[I_ListNode.Names[aRootPos]] ,NodeId)
    else
     // aNode := O_TreeNodes.AddChild( O_TreeNode,I_ListNode.Values[I_ListNode.Names[aRootPos]]);
      aNode := aTree.Items.AddChildObject( O_TreeNode,I_ListNode.Values[I_ListNode.Names[aRootPos]],NodeId);
    //aNode.Data := Ptr( aRootPos );

    aSameName_NullTree :=  I_SameName_SameTree;
    _StringListToTrees( aRootPos, I_ListNode, I_ListPar, aVisFlgs, aTree, aNode, InsertNodeName,I_Can_SameName_InAPar, aSameName_NullTree );

    //if I_SameName_SameTree then
    //  Copy_SameNode_SubTrees( );  //相同指向节点的更新
  except
    on E:exception do raise exception.Create( 'StringListToTrees出错！'+e.Message  );
  end;
end;
//------------------------------------------------------------------------------
procedure StringListToTrees( I_ListNode, I_ListPar : TStrings;
                             aTree:TTreeView; O_TreeNode : TTreeNode;
                            InsertNodeName:array of string;
                             I_Can_SameName_InAPar : boolean = false;
                             I_SameName_SameTree : boolean = false  );
var
  i : integer;
  aRootPos : integer;          //树的根节点
  aNode : TTreeNode;
  aVisFlgs :array of boolean;  //遍历标志，防止死循环
  aSameName_NullTree : boolean;
begin
  try
    if ( I_ListNode.Count <= 0 ) then
      exit;

    if ( I_ListNode.Count <> I_ListPar.Count ) then
      raise exception.Create( 'StringListToTrees出错!输入的树结构格式不对！' );


   //-----------------------确定起始节点位置---------------------

    //-----设置未遍历标志-------
    setlength( aVisFlgs, I_ListNode.Count );
    for i:= low(aVisFlgs) to high(aVisFlgs) do
      aVisFlgs[i] := False;

    aRootPos := -1;
    for i:=0 to I_ListNode.Count-1 do
    begin
      if (I_ListNode[i]='0') and ( I_ListPar[i]='0' ) then
        continue;
      if I_ListPar[i]='0' then
      begin
        aRootPos := i;
        break;
      end;
    end;

    if aRootPos = -1 then
      raise exception.Create( 'StringListToTrees出错！没有根节点！' );

    if O_TreeNode=Nil then
      aNode := aTree.Items.Add( O_TreeNode, I_ListNode[aRootPos] )
    else
      aNode := aTree.Items.AddChild( O_TreeNode, I_ListNode[aRootPos] );
    //aNode.Data := Ptr( aRootPos );

    aSameName_NullTree :=  I_SameName_SameTree;
    _StringListToTrees( aRootPos, I_ListNode, I_ListPar, aVisFlgs, aTree, aNode, InsertNodeName,I_Can_SameName_InAPar, aSameName_NullTree );

    //if I_SameName_SameTree then
    //  Copy_SameNode_SubTrees( );  //相同指向节点的更新
  except
    on E:exception do raise exception.Create( 'StringListToTrees出错！'+e.Message  );
  end;
end;


//------------------------------------------------------------------------------
//功能： 自动展开指定节点（I_Node）下的子节点   TreeView Tool
//------------------------------------------------------------------------------
procedure ExpandChildern( I_Node :TTreeNode; I_IsExpandAll : boolean );
var
  aNode : TTreeNode;
begin
  aNode := I_Node.getFirstChild;
  while aNode <> Nil do
  begin
    aNode.Expanded := True;
    if I_IsExpandAll then
      ExpandChildern( aNode, I_IsExpandAll );
    aNode := I_Node.GetNextChild( aNode );
  end;
end;

Function FormatStrDate( aDate:string ) :string;
begin
  if length( aDate ) <> 8 then
  begin
    result := aDate;
    exit;
  end;
  result := copy( aDate, 1, 4 ) + DateSeparator + copy( aDate, 5, 2 )  +DateSeparator + copy( aDate, 7, 2 )
end;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
Function FormatStrTime( aTime:string ) :string ;
begin
  if length( aTime ) <> 6 then
  begin
    result := aTime;
    exit;
  end;
  result := copy( aTime, 1, 2 ) + DateSeparator + copy( aTime, 3, 2 )  +DateSeparator + copy( aTime, 5, 2 )
end;


//-----------------------------------------------------------------------------
//功能 : 规格化的错误信息处理
//??????????????
//-----------------------------------------------------------------------------
Function FmtErrMessage(aFuncName:string;aErrMsg:string) : string;
begin
  //if cDebug = 'Y' then
    result := aFuncName + '(' + aErrMsg + ')'
  //else
  //  result := aErrMsg;
end;
//------------------------------------------------------------------------------
//功能：
//------------------------------------------------------------------------------

function StringListToArray( aString : TStrings ):arraystring;
var
  i :integer;
begin
  setlength( result, aString.Count );          //SetLength
  for i:=0 to aString.Count-1 do
    result[i] := aString[i];
end;

function StringArrayToStringList( I_StringArray : array of string ) : tStringList;
var
  i : integer;
begin
  result := tstringlist.create;
  for i:=low(I_StringArray) to high(I_StringArray) do
    result.add ( I_StringArray[i] );
end;

function ListToArray( aString : TList ): arrayPointer;
var
  i :integer;
begin
  setlength( result, aString.Count );          //SetLength
  for i:=0 to aString.Count-1 do
    result[i] := aString[i];
end;

function ArrayToList( I_StringArray : arrayPointer ) : TList;
var
  i : integer;
begin
  result := TList.create;
  for i:=low(I_StringArray) to high(I_StringArray) do
    result.add ( I_StringArray[i] );
end;

function ListToStringGridArray( aString : TList ): arrayStringGrid;
var
  i :integer;
begin
  setlength( result, aString.Count );          //SetLength
  for i:=0 to aString.Count-1 do
    result[i] := aString[i];
end;

//------------------------------------------------------------------------------
// ReplaceStrInStrings
//------------------------------------------------------------------------------
function ReplaceStrInStrings( aStrings:TStrings; subStr,newsubStr: Tstrings; IsCase : boolean = false ): TStrings; overload;   //new 2008.1.30
var
  arrayOld, arrayNew : arraystring;
begin
  arrayOld := StringListToArray(  subStr );
  arrayNew := StringListToArray( newsubStr );
  result := ReplaceStrInStrings(aStrings, arrayOld,  arrayNew, IsCase );
end;

function ReplaceStrInStrings( aStrings:TStrings; subStr,newsubStr: string; IsCase : boolean = false ): TStrings; overload;   //new 2008.1.30
var
  i:integer;
  aStr:string;
begin
  result := TStringList.Create;
  for i:=0 to aStrings.Count-1 do
  begin
    aStr := ReplaceStr( aStrings[i], subStr, newSubStr, IsCase  );
    result.Add(aStr);
  end;
end;

//------------------------------------------------------------------------------
// ReplaceStrInStrings
//------------------------------------------------------------------------------
function ReplaceStrInStrings( aStrings:TStrings; subStr,newsubStr: array of string; IsCase : boolean = false ): TStrings; overload;   //new 2008.1.30
var
  i:integer;
  aStr:string;
begin
  result := TStringList.Create;
  for i:=0 to aStrings.Count-1 do
  begin
    aStr := ReplaceStr( aStrings[i], subStr, newSubStr, IsCase );
    result.Add(aStr);
  end;
end;

procedure ReplaceStrInFile( aFileName:string; subStr,newsubStr: string; IsCase : boolean = false ); overload;   //new 2008.1.30
var
  aStrings : TStrings;
begin
  aStrings := TStringList.Create;
  aStrings.LoadFromFile( aFileName );
  aStrings := ReplaceStrInStrings( aStrings, subStr,newsubStr );
  aStrings.SaveToFile( aFileName );
  aStrings.Destroy;
end;

procedure ReplaceStrInFile( aFileName:string; subStr,newsubStr: array of string; IsCase : boolean = false ); overload;   //new 2008.1.30
var
  aStrings : TStrings;
begin
  aStrings := TStringList.Create;
  aStrings.LoadFromFile( aFileName );
  aStrings := ReplaceStrInStrings( aStrings, subStr,newsubStr, IsCase );
  aStrings.SaveToFile( aFileName );
  aStrings.Destroy;
end;

procedure ReplaceStrInFile( aFileName:string; subStr,newsubStr: Tstrings; IsCase : boolean = false ); overload;   //new 2008.1.30
var
  aStrings : TStrings;
begin
  aStrings := TStringList.Create;
  aStrings.LoadFromFile( aFileName );
  aStrings := ReplaceStrInStrings( aStrings, subStr,newsubStr );
  aStrings.SaveToFile( aFileName );
  aStrings.Destroy;
end;

function ReplaceStr(Str:string; subStr,newsubStr: TStrings; IsCase : boolean = false ): string;  overload;
var
  i : integer;
begin
  result := str;
  if subStr.Count<>NewSubStr.Count then
    raise exception.Create( 'ReplaceStr错误！Strings长度不同！' );
  for i:=0 to subStr.count-1 do
  begin
    result := ReplaceStr( result, subStr.Strings[i], newSubStr.Strings[i], IsCase );
  end;
end;

//------------------------------------------------------------------------------
// ReplaceStr( 'abc12abcsdf', 'abc', 'xx' ) --> 'xx12xxsdf'
//------------------------------------------------------------------------------
function ReplaceStr(Str:string; subStr,newsubStr: array of string; IsCase : boolean = false ): string; overload;
var
  i : integer;
begin
  result := str;
  if ArrayCount(subStr)<>ArrayCount(NewSubStr) then
    raise exception.Create( 'ReplaceStr错误！Array长度不同！' );
  for i:=low(subStr) to high(subStr) do
  begin
    result := ReplaceStr( result, subStr[i], newSubStr[i], IsCase );
  end;
end;

function PosByCase( subStr,Str: AnsiString; IsCase : boolean = false ) : integer;
begin
  if( IsCase=true ) then
    result:=pos(subStr,Str)
  else
    result:=pos( UpperCase(substr), UpperCase(Str) );     //by sxd 2009.10.23
end;

function ReplaceStr(Str,subStr,newsubStr: AnsiString; IsCase : boolean = false ): string;
var
  pp: integer;
begin
  result :='';

  pp:=PosByCase( subStr,Str, IsCase );

  //if( IsCase=true ) then
  //  pp:=pos(subStr,Str)
  //else
  //  pp:=pos( UpperCase(substr), UpperCase(Str) );     //by sxd 2009.10.23

  while pp>0 do
  begin
    result := result + LeftStr(Str,pp-1)+newsubStr;
    //Str := RightStr(Str,Length(Str)-pp-Length(subStr)+1);
    str := Copy(str,pp+Length(subStr),Length(Str)-pp-Length(subStr)+1);

    pp:=PosByCase( subStr,Str, IsCase );
    //pp:=pos(subStr,Str);
  end;
  result := result+Str;
end;

function  AddStr(op1,op2: string): string;
var
  tt: real;
begin
  try strtofloat(op1) except
    if op1 <> '' then
      result := op1
    else
      result := op2;
    exit;
  end;
  try strtofloat(op2) except
    if op1 <> '' then
      result := op1
    else
      result := op2;
    exit;
  end;
  tt := strtofloat(op1)+strtofloat(op2);
  try strtoint(op1); except
    result := Format('%f',[tt]);
    exit;
  end;
  try strtoint(op2); except
    result := Format('%f',[tt]);
    exit;
  end;
  result := inttostr(Round(tt));
end;
function  MaxStr(op1,op2: string): string;
begin
  try strtofloat(op1); except
    if strcomp(pchar(op1),pchar(op2)) > 0 then
      result := op1
    else
      result := op2;
    exit;
  end;
  try strtofloat(op2); except
    if strcomp(pchar(op1),pchar(op2)) > 0 then
      result := op1
    else
      result := op2;
    exit;
  end;
  if strtofloat(op1) > strtofloat(op2) then
    result := op1
  else
    result := op2;
end;
function  MinStr(op1,op2: string): string;
begin
  try strtofloat(op1); except
    if strcomp(pchar(op1),pchar(op2)) < 0 then
      result := op1
    else
      result := op2;
    exit;
  end;
  try strtofloat(op2); except
    if strcomp(pchar(op1),pchar(op2)) < 0 then
      result := op1
    else
      result := op2;
    exit;
  end;
  if strtofloat(op1)<strtofloat(op2) then
    result := op1
  else
    result := op2;
end;


//------------------------------------------------------------------------------
//功能：删除指定行
//------------------------------------------------------------------------------
procedure DelRows( I_Grid :TStringGrid; I_RowBgn : integer; I_RowNum : integer=1 );
var
  i:integer;
begin
  try
    with  I_Grid do
    begin
      if (I_RowBgn<0) or   (I_RowNum<1) then
        raise exception.Create( format('输入参数不对!I_RowBgn=(%d);I_RowNum=(%d)',[I_RowBgn,I_RowNum]) );

      for i:=I_RowBgn to RowCount-1-I_RowNum do
        rows[ i ] := rows[ i + I_RowNum ];

      rowCount := rowCount - I_RowNum;
    end;  //with I_Grid
  except
    on E:exception do exception.Create( 'DelRows出错！'+e.message );
  end;
end;

//------------------------------------------------------------------------------
//功能：给定字段名称、行号，返回单元值
//------------------------------------------------------------------------------
function _GridCell( I_Grid : TStringGrid; I_ColName : string; I_Row : integer ):string;overload;
var
  aCol : integer;
begin
  result := '';

  aCol := I_Grid.Rows[0].IndexOf( I_ColName );
  if aCol < 0 then
    exit;
  result := I_Grid.Cells[ aCol, I_Row ];
end;

function _GridCell( I_Grid : TStringGrid; I_Col : integer; I_RowName : string ):string;overload;
var
  aRow : integer;
begin
  result := '';
  aRow := I_Grid.Cols[0].IndexOf( I_RowName );
  if aRow < 0 then
    exit;
  result := I_Grid.Cells[ I_Col, aRow ];
end;

function GridCell( I_Grid : TStringGrid; I_Col : integer; I_RowName : string ):string;overload;
begin
  result := GridCell( I_Grid, I_RowName, I_Col, True );
end;

procedure SetGridCell( I_Grid : TStringGrid; I_Col : integer; I_Row : integer;  I_Value:string );overload;
begin
  I_Grid.cells[ I_Col, I_Row ] := I_Value;
end;

procedure SetGridCell( I_Grid : TStringGrid; I_ColName : string; I_Row : integer;  I_Value:string );overload;
var
  aCol : integer;
begin
  aCol := FindNamedCol( I_Grid, I_ColName );
  SetGridCell( I_Grid, aCol, I_Row, I_Value );
end;

procedure SetGridCell( I_Grid : TStringGrid; I_Col : integer; I_RowName : string; I_Value:string );overload;
var
  aRow:integer;
begin
  aRow := FindNamedRow( I_Grid, I_RowName );
  SetGridCell( I_Grid, I_Col, aRow, I_Value );
end;

//------------------------------------------------------------------------------
//功能：给定字段名称、行号，返回单元值
//      可以给定字段运算符，例如 ‘总重’＝‘单重*数量’
//参数：[I_IsRow] =False,列查找方式； =True，行查找方式，= GridCell( I_Grid, I_Col, I_RowName )
//------------------------------------------------------------------------------
function GridCell( I_Grid : TStringGrid; I_ColName : string; I_Row : integer; I_IsRow:boolean=false ):string;
var
  aColList : TStringList ;
  i : integer;
begin
  try
    //----分割运算符号--------
    aColList := splitToStrings_WithSplitter( I_ColName, ['*','/','+','-'] );

    //----非计算单元----------
    if aColList.Count <= 1 then
    begin
      if not I_IsRow then
        result := _GridCell( I_Grid, I_ColName, I_Row )
      else
        result := _GridCell( I_Grid, I_Row, I_ColName );
      exit;
    end;

    //----代入单元内容-----
    i:=0;
    while i<aColList.Count do
    begin
      if not I_IsRow then
        aColList[i] := _GridCell( I_Grid, aColList[i], I_Row )
      else
        aColList[i] := _GridCell( I_Grid, I_Row, aColList[i] );
      i:=i+2
    end;

    //-------完成计算------
    result := FloatToStr( Formula_Str( aColList ) );
  except
    on E:exception do
    begin
      result := '';
      raise exception.create( format('获取单元内容出错！"%s"',[e.message] ));
    end;
  end;
end;

//------------------------------------------------------------------------------
//功能： 清空指定行
//------------------------------------------------------------------------------
procedure FlushGridRow( I_Grid:TStringGrid; I_Row : integer );
var
  i : integer;
begin
  for i:=0 to I_Grid.ColCount-1 do
    I_Grid.cells[ i, I_Row ] := '';
end;

procedure FlushGrid( I_Grid : TStringGrid );
var
  i : integer;
begin
  for i:=0 to I_Grid.RowCount-1 do
    FlushGridRow( I_Grid, i );
end;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
function FindNamedCol(I_Grid:TStringGrid; I_Name:string) : integer;
begin
  result := I_Grid.Rows[0].Indexof( I_Name );
  if result < 0 then
    raise Exception.Create( format( '字段"%s"不存在！',[I_Name] ) );
end;

function FindNamedRow(I_Grid:TStringGrid; I_Name:string) : integer;
begin
  result := I_Grid.Cols[0].Indexof( I_Name );
  if result < 0 then
    raise Exception.Create( format( '字段"%s"不存在！',[I_Name] ) );
end;

//------------------------------------------------------------------------------
//功能：给定字段名称，返回List
//------------------------------------------------------------------------------
function GridCol( I_Grid : TstringGrid; I_ColName : string ) : TStrings;
var
  aCol : integer;
begin
  aCol := FindNamedCol( I_Grid, I_ColName );
  result := I_Grid.Cols[aCol];
end;

//------------------------------------------------------------------------------
//功能：给定字段名称、记录内容，返回单元记录号
//------------------------------------------------------------------------------
function GridCellRow( I_Grid : TStringGrid; I_ColNames : array of string; I_RowValues : array of string ):integer;
var
  aCol, aRow : integer;
  aStr : string;
begin
 // result := -1 ;

  for aRow := 0 to I_Grid.RowCount-1 do
  begin
    for aCol:= low( I_ColNames ) to high( I_ColNames ) do
    begin
      if uppercase( GridCell( I_Grid, I_ColNames[aCol], aRow ) ) <> uppercase( I_RowValues[aCol] ) then
        break;
    end;
    //-----全部相等，满足条件----------
    if aCol > high( I_ColNames )  then
    begin
      result := aRow;
      exit;
    end;
  end;

  aStr := '记录';
  for aCol:= low( I_ColNames ) to high( I_ColNames ) do
  begin
    aStr := aStr + '"' + I_ColNames[aCol] + '" = "' + I_RowValues[ aCol ] + '"  '
  end;
  aStr := aStr + '不存在';
  raise exception.Create( aStr );

end;

function GridCellRow( I_Grid : TStringGrid; I_ColName : string; I_RowValue : string ):integer;
var
  aCol : integer;
begin
//  result := -1;

  aCol := I_Grid.Rows[0].IndexOf( I_ColName );
  if aCol < 0 then
    raise exception.Create( format( '记录"%s"="%s"不存在！', [ I_ColName,I_RowValue ] ) ) ;
  result := I_Grid.Cols[aCol].IndexOf( I_RowValue );
end;



//------------------------------------------------------------------------------
//功能：由
//例子：32+5*2-1/2的计算（ [ 32,+,5,*,2,-,1,/,2 ] ）
//------------------------------------------------------------------------------
function Formula_Str( I_Str : string ) : double; overload;
begin
  result := Formula_Str( splitToStrings_WithSplitter( I_Str, ['*','/','+','-'] ) );
end;

//------------------------------------------------------------------------------
//功能：由
//例子：32+5*2-1/2的计算（ [ 32,+,5,*,2,-,1,/,2 ] ）
//------------------------------------------------------------------------------
function Formula_Str( I_List:TstringList ) : double; overload;
var
  i  : integer;
begin

  try
    if I_List.Count < 1 then
      raise exception.Create( '表达式为空！' );

    //---符号检查------
    i:=1;
    while i<I_List.Count do
    begin
      if not isIn( I_List[i], [ '*', '/', '+', '-' ] ) then
        raise exception.Create( format( '未定义的符号"%s"',[ I_List[i] ] ) );
      i := i+2;
    end;


    //---'()'处理以后再作-----

    //----'*'和'/'的处理------
    i:=1;
    while i<I_List.Count do
    begin
      if isIn( I_List[i], [ '*', '/' ] ) then
      begin
        if I_List[i] = '*' then
          I_List[i-1] := FloatToStr( strToFloat( I_List[i-1] ) * strToFloat( I_List[i+1] ) );
        if I_List[i] = '/' then
          I_List[i-1] := FloatToStr( strToFloat( I_List[i-1] ) / strToFloat( I_List[i+1] ) );
        I_List.Delete(i+1);
        I_List.Delete(i);
     end
     else
      i := i+2;
    end;

    //----'*'和'/'的处理------
    i:=1;
    while i<I_List.Count do
    begin
      if isIn( I_List[i], [ '+', '-' ] ) then
      begin
        if I_List[i] = '+' then
          I_List[i-1] := FloatToStr( strToFloat( I_List[i-1] ) + strToFloat( I_List[i+1] ) );
        if I_List[i] = '-' then
          I_List[i-1] := FloatToStr( strToFloat( I_List[i-1] ) - strToFloat( I_List[i+1] ) );
        I_List.Delete(i+1);
        I_List.Delete(i);
     end
     else
      i := i+2;
    end;
    result := strToFloat( I_List[0] );
  except
    on E:exception do    raise exception.Create( '表达式出错！'+e.Message );
  end;
end;

//------------------------------------------------------------------------------
//名称：FormulaStr_Replace    by sxd 2008.3.22
//例子：FormulaStr_Replace( '%A%*%B%', ['%A%','%B%'], ['10.2','11.0'] ) --> "10.2*11.0"
//------------------------------------------------------------------------------
function FormulaStr_Replace(aStr:String; StrVarName,StrVarValue: array of string ):String;
begin
  result := ReplaceStr( aStr, StrVarName, StrVarValue );
  //ShowMessage( aStr + ' ' +  result );

end;

//------------------------------------------------------------------------------
//名称：Formula_Replace    by sxd 2008.3.22
//例子：re = Formula_Replace( '%A%*%B%', ['%A%','%B%'], ['10.2','11.0'] )
//说明：用Formula时，参数必须是符合VB规范的命名，否则会出现错误。用本函数则不会
//------------------------------------------------------------------------------
function Formula_Replace(aStr:String; StrVarName,StrVarValue: array of string):double;
begin
  result := Formula(  FormulaStr_Replace(aStr, StrVarName,StrVarValue ), [], [] );
end;

function Formula_Replace(aStr:String; StrVarName,StrVarValue: TStrings):double;
var
  StrVarNameArray, StrVarValueArray : arraystring;
begin
  StrVarNameArray := StringListToArray( StrVarName );
  StrVarValueArray := StringListToArray( StrVarValue );
  result := Formula_Replace( aStr, StrVarNameArray, StrVarValueArray );
end;

function Formula(aStr:String):double;
begin
  result := Formula( aStr, [], [] );
end;

//------------------------------------------------------------------------------
//名称：Formula    by sxd 2008.3.22
//例子：re = Formula( 'A*B', ['A','B'], ['10.2','11.0'] );
//------------------------------------------------------------------------------
function Formula(aStr:String; StrVarName,StrVarValue: TStrings):double;
var
  StrVarNameArray, StrVarValueArray : arraystring;
begin
  StrVarNameArray := StringListToArray( StrVarName );
  StrVarValueArray := StringListToArray( StrVarValue );
  result := Formula( aStr, StrVarNameArray, StrVarValueArray );
end;


//------------------------------------------------------------------------------
//名称：Formula    by sxd 2008.3.22
//例子：re = Formula( 'A*B', ['A','B'], ['10.2','11.0'] );
//------------------------------------------------------------------------------
function Formula(aStr:String; StrVarName,StrVarValue: array of string):double;
var
  sc : Variant;
  i : integer;
  aStr0, aStr1 : string;
begin
  try
    sc := CreateOleObject('ScriptControl');
    sc.Language := 'VBScript';

    aStr0 := 'Function Main ' + #13 + 'dim z' + #13;
    aStr1 := '';
    for i:=low(StrVarName) to high(StrVarName)  do
    begin
      aStr1 := aStr1 + 'dim ' + StrVarName[i] + #13
    end;

    for i:=low(StrVarValue) to high(StrVarValue) do
    begin
      aStr1 := aStr1 + StrVarName[i] + '=' + StrVarValue[i] + #13
    end;
    aStr1 := aStr0 +
             aStr1 + ' Main = ' + aStr + #13 + 'End Function';
             //
    //ShowMessage(aStr1);
    sc.AddCode(aStr1);
    result := sc.Eval('Main');
  except
    on E:Exception do  raise exception.Create( format( '公式(%s)出错！%s!',[aStr1,e.message] ) );
  end;
end;

//------------------------------------------------------------------------------
// 将标准编码的字符串转换为Unicode编码
//     wStr是一个unicode格式的字符串，但是其内容是标准格式
//     返回结果： 按标准语法将内容转换成unicode格式
//------------------------------------------------------------------------------
function WideStr_BZToUnicode(wStr:wideString) : string;
var
  i:integer;
begin
  result := '';
  for i:=1 to length(wStr) do
    result :=  result + Char( wStr[i] );
   // result :=  result + pChar( @wStr[i] );
end;

//----------------------------------------------------------
//将Unicode编码的字符串转换为标准编码
//    wStr是一个Unicode格式的字符串，其内容也是UniCode
//    返回结果：  按Unicode语法将内容转换成标准格式
//----------------------------------------------------------
function WideStr_UnicodeToBZ(wStr:wideString) : Widestring;
var
  i:integer;
  sStr : ansiString; //shortstring;
begin

  sStr := wStr; 
  result := '';
  for i:=1 to length(sStr) do
     result  :=  result + wideChar(sStr[i]);
end;

function GetNamedValue( I_Names, I_Values : TStrings;  I_Name : string ) : string;
var
  idx : integer;
begin
  result := '';
  idx :=  I_Names.IndexOf( I_Name );
  if idx >=0 then
    result := I_Values[ idx ];
end;

//------------------------------------------------------------------------------
//功能：判断是否为指定的类型
//例子：IsNamedType( 'GB-7585', 'GB*' )
//------------------------------------------------------------------------------
function _isNamedType( I_Name : string; I_TypeDef : string  ) : boolean;
var
  aPre, aSuf : string;
begin

  //--------情况'GB*'---------
  if Right( I_TypeDef, 1 ) = '*' then
  begin
    result := IsPreFix( I_Name, Left( I_TypeDef, length(I_TypeDef)-1 ) );
    exit;
  end;

  //--------情况'*W'---------
  if Left( I_TypeDef, 1 ) = '*' then
  begin
    result := IsSuffix( I_Name, Right( I_TypeDef, length(I_TypeDef)-1 ) );
    exit;
  end;

  //--------情况'GB*W'---------
  if pos( '*', I_TypeDef ) > 0 then
  begin
    SplitStrTo2Str( I_TypeDef, '*',  aPre, aSuf, true );
    result := IsPreFix( I_Name, aPre );
    if result = true then
      exit;
    result := IsSuffix( I_Name, aSuf );
    exit;
  end;

  //--------完全匹配情况--------
  result := ( I_Name =  I_TypeDef );
end;

//------------------------------------------------------------------------------
//功能：判断是否为指定的类型
//例子：IsNamedType( 'GB-7585', 'GB*;*W' )
//------------------------------------------------------------------------------
function isNamedType( I_Name : string; I_TypeDef : string; I_Splitter:string=';' ) : boolean;
var
  I_TypeList : TStringList;
  i : integer;
begin
  result:=false;
  I_TypeList := splitToStrings(   I_TypeDef, I_Splitter );
  for i:=0 to I_TypeList.Count-1 do
  begin
    result := _isNamedType( I_Name,  I_TypeList[i] );
    if result=True then
      exit;
  end;
end;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
procedure InitFeatStr( var O_Str :TStrings );
begin
  try
   if  O_Str=nil then
      O_Str:=Tstringlist.Create
   else
     O_Str.Clear;
  except
    on e:exception do raise exception.Create('InitFeatStr'+e.Message );
  end;
end;


//------------------------------------------------------------------------------
//功能：获取命名TStrings的值
//例子：【 'X=12', 'Y=31' 】  StringValue(1) = '31'; StringName(1) = 'Y'
//------------------------------------------------------------------------------
function StringValue( I_String:TStrings; i:integer ) : string;
begin
  result := I_string.Values [ I_string.Names[i]  ];
end;

function StringName( I_String:TStrings; i:integer ) : string;
begin
  result := I_string.Names[i];
end;  

//------------------------------------------------------------------------------
//功能:以showmodal的方式打开一个窗体,如果该窗体尚未创建则首先创建该窗体;
//参数:aowner:窗体的父亲,formclass :窗体的类型; fm :窗体的实例;
//------------------------------------------------------------------------------

procedure openForm(Aowner:Tcomponent;Formclass:Tformclass;Var fm);
var
  Tmp:Tform;
begin
  if Tform(fm)=nil then
  begin
    Tmp:=TForm(FormClass.NewInstance);
    Tmp.Create(AOwner);
    TForm(fm):=Tmp;
  end;
  Tform(fm).ShowModal;
end;

Procedure OpenSubForm(Frm: TForm;no,name,standard,testno:string);
//var
// equ_no,equ_name,equ_standard:string;
// bill_no:string;
begin
// Frm.equ_no:=no;
// Frm.equ_name:name;
// Frm.equ_standard:=standard;
// Frm.bill_no:=testno;
 Frm.ShowModal;
end; 

//------------------------------------------------------------------------------
//功能：获得计算机的ip地址
//------------------------------------------------------------------------------
function getIPs(): String;
type
  TaPInAddr = Array[0..10] of PInAddr;
  PaPInAddr = ^TaPInAddr;
var
  phe: PHostEnt;
  pptr: PaPInAddr;
  Buffer: Array[0..63] of Char;
  I: Integer;
  GInitData: TWSAData;
  //s:string;
begin
  try
    WSAStartup($101,GInitData);
    result:='';
    GetHostName(Buffer,SizeOf(Buffer));
    phe := GetHostByName(buffer);
    if phe = nil then Exit;
    pPtr := PaPInAddr(phe^.h_addr_list);
    I := 0;
    while pPtr^[I] <> nil do
    begin
      Result:=inet_ntoa(pptr^[I]^);
      Inc(I);
    end;
    WSACleanup;
  except
    on E:exception do  raise exception.Create( 'getIPs出错！'+e.Message  );
  end;
end;

//------------------------------------------------------------------------------
//功能：由ip地址获得计算机名
//------------------------------------------------------------------------------
function IPAddrToName(IPAddr : String): String;
var
  SockAddrIn: TSockAddrIn;
  HostEnt: PHostEnt;
  WSAData: TWSAData;
begin
  try
    WSAStartup($101,WSAData);
    SockAddrIn.sin_addr.s_addr:= inet_addr(PChar(IPAddr));
    HostEnt:= gethostbyaddr(@SockAddrIn.sin_addr.S_addr,4,AF_INET);

    if HostEnt<>nil then
      result:=StrPas(Hostent^.h_name)
    else
    result:='';
  except
    on E:exception do  raise exception.Create( 'IPAddr出错！'+e.Message  );
  end;
end;  

//------------------------------------------------------------------------------
// 功能：比较name1和name2 并获得比较结果                                  by ls
//参数：getsame＝true获得name1和name2中相同的string
//      getsame＝false获得name1中有但name2中没有的string
//      例如: str1=[a,b,c] str2=[b,c,d];
//       compar_str(str1,str2,true)=[b,c];  compar_str(str1,str2,false)=[a];
//       compar_str(str2,str1,false)=[d]
//------------------------------------------------------------------------------
function  compar_str(name1,name2:Tstrings; getsame:boolean):Tstrings;
var
  i,j:integer;
  flag:boolean;
begin
  try
    result := TStringList.Create;
    for i:=0 to name1.Count-1 do
    begin
      flag:=True;
      for j:=0 to name2.Count-1 do
      begin
        if not getsame then
        begin
          if name1.Strings[i]=name2.Strings[j] then
          begin
            flag:=False;
            break;
          end;
        end
        else
          if name1.Strings[i]<>name2.Strings[j] then  begin    flag:=False; continue;end
          else  begin flag:=true;break; end;
      end;

      if flag then
        result.Add(name1.Strings[i]);
    end;
  except
    on e:exception do raise exception.Create('cmp_str出错'+e.Message );
  end;
end;

{function SaveCompressedBmptoDB(tmpSet: TADOQuery;BlobFName: string;bmp: TBitmap):boolean;
var
  Stream: TBlobStream;
  CompressedStream: TMemoryStream;
begin
  with tmpset do begin
    Stream := TBlobStream.Create(FieldByName(BlobFName) as TBlobField, bmWrite);
    CompressedStream := TMemoryStream.Create;
    try
      bmp.SaveToStream(CompressedStream);
      CompressStream(CompressedStream, clMax);
      Stream.CopyFrom(CompressedStream,0);
      result := true;
    except
      result := false;
    end;
    CompressedStream.Free;
    Stream.Free;
  end;
end;
function SaveCompressedTreeViewtoDB(tmpSet: TDataSet;BlobFName: string;tv: TTreeView):boolean;
var
  Stream: TBlobStream;
  CompressedStream: TMemoryStream;
begin
  with tmpset do begin
    Stream := TBlobStream.Create(FieldByName(BlobFName) as TBlobField, bmWrite);
    CompressedStream := TMemoryStream.Create;
    try
      tv.SaveToStream(CompressedStream);
      CompressStream(CompressedStream, clMax);
      Stream.CopyFrom(CompressedStream,0);
      result := true;
    except
      result := false;
    end;
    CompressedStream.Free;
    Stream.Free;
  end;
end;
function LoadCompressedFieldtoImg(tmpSet: TDataSet;BlobFName: string;Img: TImage):boolean;
var
  Stream: TBlobStream;
  CompressedStream: TMemoryStream;
  size: integer;
  pic: TPicture;
begin
  with tmpset do begin
    pic := TPicture.Create;
    Stream := TBlobStream.Create(FieldByName(BlobFName) as TBlobField, bmRead);
    CompressedStream := TMemoryStream.Create;
    try
      Size := Stream.Size;
      if Size > 0 then begin
        CompressedStream.CopyFrom(Stream,0);
        UnCompressStream(CompressedStream);
//        CompressedStream.SaveToFile('c:\test.bmp');
        CompressedStream.Position := 0;
        pic.Bitmap.LoadFromStream(CompressedStream);
        img.Picture.Assign(pic.Bitmap);
        result := true;
      end else begin
        result := false;
//        img.Canvas.FillRect(Rect(0,0,img.Width,img.Height));
      end;
    except
      result := false;
    end;
    Stream.Free;
    CompressedStream.Free;
    pic.Free;
  end;
end;

function LoadCompressedFieldtoImg(tmpSet: TDataSet;BlobFName: string;pc: TPicture):boolean;
var
  Stream: TBlobStream;
  CompressedStream: TMemoryStream;
  size: integer;
  pic: TPicture;
begin
  with tmpset do begin
    pic := TPicture.Create;
    Stream := TBlobStream.Create(FieldByName(BlobFName) as TBlobField, bmRead);
    CompressedStream := TMemoryStream.Create;
    try
      Size := Stream.Size;
      if Size > 0 then begin
        CompressedStream.CopyFrom(Stream,0);
        UnCompressStream(CompressedStream);
//        CompressedStream.SaveToFile('c:\test.bmp');
        CompressedStream.Position := 0;
        pic.Bitmap.LoadFromStream(CompressedStream);
        pc.Assign(pic.Bitmap);
        result := true;
      end else begin
        result := false;
//        pc.Bitmap.Canvas.FillRect(Rect(0,0,pc.Width,pc.Height));
      end;
    except
      result := false;
    end;
    Stream.Free;
    CompressedStream.Free;
    pic.Free;
  end;
end;

function LoadCompressedFieldtoImg( tmpSet: TDataSet;BlobFName: string; bp: TBitmap):boolean;
var
  Stream: TBlobStream;
  CompressedStream: TMemoryStream;
  size: integer;
  pic: TPicture;
begin
  with tmpset do begin
    pic := TPicture.Create;
    Stream := TBlobStream.Create(FieldByName(BlobFName) as TBlobField, bmRead);
    CompressedStream := TMemoryStream.Create;
    try
      Size := Stream.Size;
      if Size > 0 then begin
        CompressedStream.CopyFrom(Stream,0);
        UnCompressStream(CompressedStream);
//        CompressedStream.SaveToFile('c:\test.bmp');
        CompressedStream.Position := 0;
        pic.Bitmap.LoadFromStream(CompressedStream);
        bp.Assign(pic.Bitmap);
        result := true;
      end else begin
        result := false;
//        bp.Canvas.FillRect(Rect(0,0,bp.Width,bp.Height));
      end;
    except
      result := false;
    end;
    Stream.Free;
    CompressedStream.Free;
    pic.Free;
  end;
end;

function LoadCompressedFieldtoTreeView(tmpSet: TDataSet;BlobFName: string;tv: TTreeView):boolean;
var
  Stream: TBlobStream;
  CompressedStream: TMemoryStream;
  size: integer;
begin
  with tmpset do begin
    Stream := TBlobStream.Create(FieldByName(BlobFName) as TBlobField, bmRead);
    CompressedStream := TMemoryStream.Create;
    try
      Size := Stream.Size;
      if Size > 0 then begin
        CompressedStream.CopyFrom(Stream,0);
        UnCompressStream(CompressedStream);
        CompressedStream.Position := 0;
        tv.LoadFromStream(CompressedStream);
        result := true;
      end else begin
        result := false;
      end;
    except
      result := false;
    end;
    Stream.Free;
    CompressedStream.Free;
  end;
end;

procedure LoadFiletoImg(fn: string;Img: TImage);overload;
var
  AJpeg:TJpegImage;
  tt: TBitmap;
begin
  AJpeg:=TJpegImage.Create;   //产生一个新的AJpeg;
  if (pos('.JPG',UPPERCASE(fn) )>0)OR(pos('.JPGE',UPPERCASE(fn))>0) then
  begin
    AJpeg.LoadFromFile(fn); //载
  end
  else
  begin
    Img.AutoSize := true;
    Img.Picture.LoadFromFile(fn);
    AJpeg.Assign(Img.Picture.Bitmap);
  end;
  tt := TBitmap.Create;
  tt.Width := AJpeg.Width;
  tt.Height := AJpeg.Height;
  tt.Canvas.FillRect(Rect(0,0,Ajpeg.Width,Ajpeg.Height));
  tt.Canvas.Draw(0,0,AJpeg);
  Img.Picture.Assign(tt);
  tt.Free;
  Ajpeg.Free ;
end;}



function isEqual(str1,str2: string):boolean;
var
  vv: variant;
  i: integer;
begin
  if (str1='')or(str2='') then
    exit;
  vv := split(str1,';');
  for i:= 1 to varArrayHighBound(vv,1) do
  begin
    if pos(vv[i]+';',str2) <= 0 then
    begin
      result := false;
      exit;
    end;
  end;
  vv := split(str2,';');
  for i:= 1 to varArrayHighBound(vv,1) do
  begin
    if pos(vv[i]+';',str1) <= 0 then
    begin
      result := false;
      exit;
    end;
  end;
  result := true;
end;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
function FullIndex( I_Str:string; I_String:TStrings ) : integer;  // for xk 20041103
var
  aIndex : integer;
  i : integer;
begin
  try
    result:=-1;
    for i:=0 to length(I_Str)-1 do
    begin
      aIndex := I_String.IndexOf( left(I_Str,length(I_Str)-i ) );
      if aIndex >= 0 then
      begin
        result := aIndex;
        exit;
      end;
    end;
  except
    on e:exception do raise exception.create('FullIndex出错！'+e.message);
  end;
end;

//------------------------------------------------------------------------------
//功能：拷贝树结构(将I_Src_Node下所有的节点拷贝到O_Dest_Node下)
//
//------------------------------------------------------------------------------
procedure _CopyTreeView ( I_Src_Node, O_Dest_Node : TTreeNode );   //for xk 20041103
var
  aNode_Src : TTreeNode;
  aNode_Dest : TTreeNode;
begin

    if (I_Src_Node=Nil) or (O_Dest_Node=Nil) then
      exit;

    aNode_Src := I_Src_Node.getFirstChild;
    aNode_Dest := O_Dest_Node;
    while aNode_Src <> Nil do
    begin
      aNode_Dest.Owner.AddChild( aNode_Dest, aNode_Src.Text );
      aNode_Src := I_Src_Node.GetNextChild( aNode_Src );
    end;

    //-----递归----
    aNode_Dest := O_Dest_Node.getFirstChild();
    aNode_Src := I_Src_Node.getFirstChild;
    while aNode_Src <> Nil do
    begin
      _CopyTreeView( aNode_Src, aNode_Dest );
      aNode_Src := I_Src_Node.GetNextChild( aNode_Src );
      aNode_Dest := I_Src_Node.GetNextChild( aNode_Dest );
    end;

end;

procedure Tree_Copy ( I_Src_Node, O_Dest_Node : TTreeNode );   //for xk 20041103
begin
  try
    if (I_Src_Node=Nil) or (O_Dest_Node=Nil) then
      raise exception.Create('树节点为空！') ;

    O_Dest_Node.Text := I_Src_Node.Text;
    _CopyTreeView( I_Src_Node, O_Dest_Node );

  except
    on e:exception do raise exception.Create( '拷贝树出错！'+e.message );
  end;
end;

function Tree_NewRoot( I_Tree : TTreeView ) : TTreeNode;
var
  aNode : TTreeNode;
begin
  result := Nil;
  if Tree_Root(  I_Tree ) <> Nil then
    exit;
  aNode := TTreeNode.Create( I_Tree.Items );
  result := I_Tree.Items.Add ( aNode, 'Root' );
end;

//------------------------------------------------------------------------------
//功能：获取某个节点在产品树中的完整路径 ( 飞机\机翼\ )
//------------------------------------------------------------------------------
function Tree_FullPath( I_Node : TTreeNode ) : string;
var
  aNode : TTreeNode;
begin
  result :='';
  aNode := I_NOde.Parent;
  while aNode <> Nil do
  begin
    if result='' then
      result := aNode.text + PathSplitter
    else
      result := result + aNode.text + PathSplitter;
    aNode := aNode.Parent;
  end;
end;

//------------------------------------------------------------------------------
//功能: StringGrid拷贝
//------------------------------------------------------------------------------
procedure CopyStringGrid( I_Src, OI_Dest : TStringGrid );
var
  i : integer;
begin
    //----设置BomGrid的Rows和Cols------
    OI_Dest.RowCount := I_Src.RowCount;
    OI_Dest.FixedRows := I_Src.FixedRows;
    OI_Dest.ColCount := I_Src.ColCount;
    OI_Dest.FixedCols := I_Src.FixedCols;

    //-----读入原始BOM信息-------------
    //for i:=0 to I_Src.RowCount-1 do
    //  OI_Dest.Rows[ i ].Text := I_Src.Rows[ i ].Text;

    for i:=0 to I_Src.ColCount-1 do
      OI_Dest.Cols[ i ].Text := I_Src.Cols[ i ].Text;

end;


function StrGridHints( aGrids : TList ):TStrings;
var
  i : integer;
  aGrid : TStringGrid;
begin
  result := TStringList.Create;
  for i:=1 to aGrids.Count do
  begin
    aGrid := aGrids.Items[i-1];
    result.Add( aGrid.Hint );
  end;
end;

function StrGridHints_Str( aGrids : TList ) : String;
var
  aStrings : TStrings;
begin
  aStrings := StrGridHints(aGrids);
  result := aStrings.Text;
  aStrings.Destroy;
end;

procedure MoveLookupListToCell( I_SG:TStringGrid;
                                I_LookupList:TWinControl;
                                I_TitleCellCol, I_TitleCellRow : integer;
                                I_TitleValue : string;
                                I_CellCol, I_CellRow : integer );
begin

  if I_SG.Cells[ I_TitleCellCol, I_TitleCellRow ] = I_TitleValue then
  begin
    I_LookupList.Visible := True;
    I_LookupList.Left :=  I_SG.Left + I_SG.cellrect(I_CellCol,I_CellRow).Left;
    I_LookupList.Width := I_SG.cellrect(I_CellCol,I_CellRow).Right - I_SG.cellrect(I_CellCol,I_CellRow).Left;
    I_LookupList.Top  :=  I_SG.Top + I_SG.cellrect(I_CellCol,I_CellRow).top;
    I_LookupList.Height  :=  I_SG.cellrect(I_CellCol,I_CellRow).Bottom - I_SG.cellrect(I_CellCol,I_CellRow).Top;

    if I_LookupList.className = 'TComboBox' then
      (I_LookupList as TComboBox).Text :=  I_SG.Cells[ I_CellCol,I_CellRow ]
    else
      if I_LookupList.className = 'TEdit' then
        (I_LookupList as TEdit).Text :=  I_SG.Cells[ I_CellCol,I_CellRow ] ;
  end
  else
    I_LookupList.Visible := false;
end;

{function LocateNamedRow( aList:TStringList; const i_find_what :String;
                          const i_find_From : integer =0; const  i_find_end :integer=maxint ) : integer;
var
  i:integer;
begin

  for i:=i_find_From to Min( i_find_end, aList.Count-1 ) do
  begin
     if ( i_find_what = aList.Strings[i] ) then
     begin
       result := i;
       exit;
     end;
  end;
  result := -1;
end;}

function LocateNamedRow( aList:TStringList; i_find_what :TStringList;
                              const i_find_From:integer = 0 ;  const i_find_end:integer=maxint) : integer;
var
  i : integer;
  aStr : String;
begin
   for i:=i_find_From to Min( i_find_end, aList.Count-1 ) do
   begin
     aStr := aList.Strings[i];
     aStr := Trim(aStr);

     if ( IsPreFix( aStr , i_find_what )  ) then
     begin
       result := i;
       exit;
     end;

   end;
   result := -1;
   exit;
end;

function LocateNamedRow( aList:TStringList; const i_find_what :string;
                              const i_find_From:integer = 0 ;  const i_find_end:integer=maxint) : integer;
var
  i : integer;
  aStr : String;
begin
   for i:=i_find_From to Min( i_find_end, aList.Count-1 ) do
   begin
     aStr := aList.Strings[i];
     aStr := Trim(aStr);
     if ( IsPreFix( aStr , i_find_what )  ) then
     begin
       result := i;
       exit;
     end;
   end;
   result := -1;
   exit;
end;

function Find_NamedRow( aList:TstringList; const i_find_what :string;
                        const i_find_From : integer = 0;  const i_find_end :integer = maxint ) : string;
var
  aRow : integer;
begin
   aRow := LocateNamedRow( aList, i_find_what,i_find_From, i_find_end );
   if ( aRow < 0 ) then
     raise exception.create( Format( '找不到(%s)行！', [i_find_what] ) )
   else
     result :=  aList.Strings[aRow];
end;

function Find_NamedValue( aList:TstringList ; const i_find_what :string ;
                          const i_find_From : integer = 0;  const i_find_end :integer = maxint  ) : string ;
begin
  result := ( RemovePrefix( Find_NamedRow (aList, i_find_what,i_find_From, i_find_end), i_find_what ) ) ;
end;


function AddFilter(FldNames:array of string; fldValues:array of string):string;overload;
var
     i:integer;
     isFirst:bool;
begin
     result:='';
     isFirst:=true;
     for i:=0 to high(FldNames) do
     begin
       if fldValues[i]='' then continue;
       if isFirst then
          result:=FldNames[i]+'='''+fldValues[i]+''''
       else
         result:=result+' and '+FldNames[i]+'='''+fldValues[i]+'''';
       isFirst:=false;
     end;
end;
function AddFilter(FldNames:array of string; fldValues:array of string;
                      fOrAnd:array of string;fopers:array of string;IsStrtype:array of bool):string;overload;
    function GetTypeStr(FValue:string;IsStr:bool):string;
    begin
      if IsStr then
        result:=QuotedStr(FValue)
      else
        result:=FValue;
    end;
var
  i:integer;
  isFirst:bool;
begin
     result:='';
     isFirst:=true;
     for i:=0 to high(FldNames) do
     begin
       if fldValues[i]='' then continue;
       if isFirst then
          result:='('+FldNames[i]+fopers[i]+GetTypeStr(fldValues[i],IsStrtype[i])+')'
       else
         result:=result+' '+fOrAnd[i]+' '+'('+FldNames[i]+fopers[i]+GetTypeStr(fldValues[i],IsStrtype[i])+')';
       isFirst:=false;
     end;
end;

procedure AddTreeNodes(aTreeNodes:TTreeNodes;NodeTextS:array of string;ParNode:TTreeNode); overload;
  var j:integer;
  begin
    for j:=low(NodeTextS) to high(NodeTextS) do
      aTreeNodes.AddChild(ParNode,NodeTextS[j]).ImageIndex:=2;
  end;


procedure SetNodeImageSeleIndex(aNode:TTreeNode;Index:Integer);
begin
  aNode.ImageIndex := Index;
  aNode.SelectedIndex := Index;
end;



function GetMidStr(src:string;split1:string;split2:string):string;
var
  pos1,pos2:integer;
  tmps:string;
begin
  result:='';
  tmps:= uppercase(src);
  pos1:=pos(uppercase(split1),tmps);
  if ( pos1=0 ) then exit;
  pos2:=pos(uppercase(split2),copy(tmps,pos1++length(split1),length(tmps)));
  result:=copy(tmps,pos1+length(split1),pos2-1);

end;

function IsAIntNum(aStr:String):bool;
begin
  result := true;
  try
    StrToInt(aStr);
  except
    result := false;
  end;
end;
function IsAIntNum(aStr:String;ExcludeStr:String):bool;
begin
 if (Pos(astr,ExcludeStr)=0) then
   result := IsAIntNum(aStr)
 else
   result :=IsAIntNum(copy(aStr,1,Pos(astr,ExcludeStr)-1));
end;
function CopyStr(aSrc :String;aPos :Integer; aLength:Integer):String;
begin
  result := Trim(copy(aSrc,aPos,aLength));
end;


function GetShortcutInfo(ShortcutFilename:string):LinkInfo;
var
   psl : IShellLink;
   ppf : IPersistFile;
   WideName:Array [0..MAX_PATH] of WideChar;
   Data:TWin32FindData;
begin
  psl := CreateComObject(CLSID_ShellLink) as IShellLink;
  ppf := psl as IPersistFile;
  MultiByteToWideChar(CP_ACP, 0, pChar(ShortcutFilename), -1, WideName, Max_Path);


  ppf.Load(WideName,STGM_READ);

  psl.GetArguments(@Result.pAugment,MAX_PATH );
  psl.GetWorkingDirectory(@Result.pDirectory,MAX_PATH );
  psl.Resolve(0,SLR_ANY_MATCH);

  psl.GetPath( @Result.pTarget,MAX_PATH,Data,SLGP_UNCPRIORITY);
end;

function RunAppByLnk(AppLnkFile:string):Hwnd;
var
  aLInfo : LinkInfo;
begin
  if not fileExists( AppLnkFile ) then
  begin
   result := 0;
   exit;
  end;
  if uppercase(ExtractFileExt(AppLnkFile))<>'.LNK' then
  begin
    result := 0;
    exit;
  end;
  aLInfo:=GetShortcutInfo(AppLnkFile);
  result := ShellExecute( 0,'Open',aLInfo.pTarget ,aLInfo.pAugment,aLInfo.pDirectory, SW_SHOWNORMAL);
end;

function  ReadRegistry(KeyName:String):String;
var
  Regf:Tregistry;
begin
    Regf:=Tregistry.Create;
    Regf.RootKey:=HKEY_LOCAL_MACHINE;
    try
          RegF.OpenKey('SOFTWARE\EmbedWindowApp\', false);
          result:=regf.ReadString(KeyName);
     finally
      RegF.CloseKey;
      RegF.Free;
    end;
end;

procedure WriteRegistry(KeyName:String;KeyValue:String);
var
  Regf:Tregistry;
begin
    Regf:=Tregistry.Create;
    Regf.RootKey:=HKEY_LOCAL_MACHINE;
    try
          RegF.OpenKey('SOFTWARE\EmbedWindowApp\', True);
          //path:=regf.ReadString(AppName);
          Regf.WriteString(KeyName,KeyValue);
     finally
      RegF.CloseKey;
      RegF.Free;
    end;
end;

procedure MergeTrees( aTree1,aTree2:TTreeView);
var
  tNodes,tmpNodes:TStrings;
  p1:String;
  i,SrcCount:integer;
  tmpData :Tlist;
begin
  tNodes := TStringlist.Create;
  tmpNodes := TStringlist.Create;
  tmpData := TList.create;
  try
    p1 := ExtractFilePath(Application.ExeName);
    aTree1.SaveToFile(p1+'t1.txt');
    aTree2.SaveToFile(p1+'t2.txt');

    SrcCount := aTree1.items.Count;

    tNodes.LoadFromFile(p1+'t1.txt');
    tmpNodes.LoadFromFile(p1+'t2.txt');
    tNodes.AddStrings(tmpNodes);
    tNodes.SaveToFile(p1+'t3.txt');
     //记录对应tree1的data
    for i := 0 to aTree1.items.count-1 do
    begin
      tmpdata.add(aTree1.items.item[i].data);
    end;
    aTree1.LoadFromFile(p1+'t3.txt');

    //对应tree1的data
    for i := 0 to SrcCount-1 do
    begin
      aTree1.items.item[i].data := tmpdata.items[i];
    end;

    //对应tree2的data
    for i := SrcCount to aTree1.items.count-1 do
    begin
      aTree1.items.item[i].data := aTree2.items.item[i-SrcCount].data;
    end;

  finally
    tNodes.Free;
    tmpNodes.Free;
    tmpData.free;
  end;
end;

//-------------------- Control ------------------------------------------------

function Control_AbsLeft( aControl:TControl ) : integer;
var
  aLeft : integer;
  aForm : TForm;
begin
  aLeft := 0;
  while( aControl <> Nil ) do
  begin
    if( aControl.Parent = Nil ) then
    begin
      try
        aForm := TForm(aControl);
        aLeft := aLeft + aForm.Width - aForm.ClientWidth;
      except
      end;
    end;

    aLeft := aLeft + aControl.Left;
    aControl := aControl.Parent;
 end;
 Control_AbsLeft := aLeft;
end;

function Control_AbsTop( aControl:TControl ) : integer;
var
  aTop : integer;
  aForm : TForm;
begin
  aTop := 0;
  while( aControl <> Nil ) do
  begin

    //aName := aControl.ClassName;

    if( aControl.Parent = Nil ) then
    begin
      try
        aForm := TForm(aControl);
        aTop := aTop + aForm.Height - aForm.ClientHeight;
      except
      end;
    end;

    aTop := aTop + aControl.Top;
    aControl := aControl.Parent;
  end;
  
  Control_AbsTop := aTop;
end;

//---------- Move From LS 2010.7.1 --------------------------
function StrHasChinese(aStr:String):boolean;
var
  i:integer;
begin
  for i := 0 to length(aStr)-1 do
  begin
    if (IsDBCSLeadByte(Byte(aStr[i]) )) then
    begin
      result := true;
      exit;
    end;
  end;
 result := false;
end;


//CheckList处理
procedure SetCLBoxSelMod(ClBok:TCheckListBox);
var
  i:integer;
  flag:Boolean;
begin
try
  flag:=False;
  ClBok.MultiSelect:=true;
  if  ClBok.SelCount=1 then     exit;

  for  i:=0 to ClBok.Count-1 do
    if  ClBok.Selected[i] then
    begin
        if  not ClBok.Checked[i] then
        begin
          Flag:=True;
          break;
        end;
    end;
  for i:=0 to ClBok.Count-1 do
   if  (ClBok.Selected[i]) then
   begin
    if Flag then
     ClBok.Checked[i]:=True
    else
      ClBok.Checked[i]:=False;
   end;

  except
    on e:exception do
     begin
     // showmessage('7');
      showmessage( 'SetCLBoxSelMod出错！' + e.Message );
    end;
  end;
end;

//CheckListToTreeNode
procedure MoveCLBToTreeNode( ClBox:TCheckListBox;aNode:TTreeNode);
var
  i:integer;
begin
  if (Clbox.SelCount = 0) then exit;
  if (aNode = nil )  then raise Exception.create('请选择需要移入的树节点！');
  for i := ClBox.Count-1  downto 0 do
  begin
    if ( ClBox.Checked[i] ) then
    begin
      aNode.Owner.AddChild(aNode,Clbox.Items.Strings[i]);
      ClBox.Items.Delete(i);
    end;
  end;
end;

procedure MoveTreeNodeToCLB( ClBox:TCheckListBox;aTree:TTreeview);
var
  i:integer;
begin
    if (  aTree.SelectionCount = 0 ) then
     raise Exception.Create('请选择需要移出的树节点！');
  for i := aTree.SelectionCount-1  downto 0 do
  begin
    if (aTree.Selections[i].HasChildren ) then raise Exception.Create('该节点不能移出！');
     if ( ClBox.Items.IndexOf(aTree.Selections[i].Text)>=0 )then continue;
   ClBox.Items.Add( aTree.Selections[i].Text );
   aTree.Items.Delete(aTree.Selections[i]);

  end;
end;

procedure DelTreeNodeByTextList( aTree:TtreeView;aDelList:TStrings);
var
  i:integer;
begin
  if ( aDelList.Count = 0 ) then exit;
  for i :=aTree.Items.Count-1  downto 0 do
  begin
    if (  aTree.Items.Item[i].HasChildren ) then continue;
    if ( aDelList.IndexOf( aTree.Items.Item[i].Text ) < 0 ) then continue;
    aTree.Items.Delete(aTree.Items.Item[i]);
  end;
end;

function IsEqualStr( aStr1:String; aStr2:String; IsCase:bool ):bool;
begin
  result := ( (IsCase=true) and ( aStr1 = aStr2 ) )
            or ( (IsCase=false) and ( UpperCase( aStr1 ) = UpperCase( aStr2 ) )  );
end;

function IndexOfStr( aStrings:TStrings; aStr:String ; IsCase:bool=false ) : integer;
var
  i : integer;
begin

  for i := aStrings.Count - 1 downto 0 do
  begin
    if( IsEqualStr( aStrings.Strings[i], aStr, IsCase ) ) then
    begin
      result := i;
      exit;
    end;
  end;

  result := -1;
end;

procedure FreeTstrings(I_Tstring: array of Tstrings);
var
  i:integer;
begin
  for i:=0 to high(I_Tstring)do
  begin
    I_Tstring[i].Free;
    I_Tstring[i]:=Nil;
  end;
end;

function SetFullStr(I_num:integer;I_SetWhat:string;I_Str:string):string;
var
  i:integer;
  aStr:string;
begin
  try
  aStr:='';
  for i:=1 to I_num-length(I_Str) do
    aStr:=aStr+I_SetWhat;
  result:=aStr+I_str;
  except
    result:='';
  end;
end;

function EvalScript(aList:TStrings;aFunc:String='main'): Variant;
var
  sc : Variant;
  aStr : String;
  i : integer;
begin
  sc := CreateOleObject('ScriptControl');
  sc.Language := 'VBScript';

  aStr := '';
  i := 0;
  while(i<aList.Count) do
  begin
   aStr := aStr + aList.Strings[i]+ #13;
   i := i+1;
  end;

  sc.AddCode(aStr);
  result := sc.Eval(aFunc);
end;

initialization
  G_IsBuffered := True;    

end.

