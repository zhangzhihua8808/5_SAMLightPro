//---------------------------------------------------------------------------

#include "UnitAll.h"
#pragma hdrstop

#include "UnitProeEngine.h"
#include "UnitTool_Single.h"
#include "UnitTool_Class.h"
#include "COMMON_FUNC.hpp"

int G_CheckedNo = 0;
int G_CheckedNum = 0;

MProeEngine* G_ProeEngine = new MProeEngine();              //访问PROE的引擎


//----------------------- Functions ------------------------------------------

TStrings* GetProeParaStrings( String aFileName )
{
  if( !FileExists(aFileName) )
    throw Exception( "文件("  + aFileName +")不存在！");

  //return new TStringList;
  gError->Warn( "正在读取Proe模型的参数..." );

  G_ProeEngine->OpenModel( aFileName, false );
  TStrings* aStrings = G_ProeEngine->GetModelParaStrings ( aFileName, true );
  gError->Warn( "OK!" );
  return aStrings;
}

void UpdateProeModelParas( String aFileName, MParaList* aParas )
{
  if( G_ProeEngine->CheckInit() == false )
    throw Exception( "请先启动PRO/E" );
    
  if( !FileExists(aFileName) )
    throw Exception( "文件("  + aFileName +")不存在！");

  gError->Warn( "正在更新模型参数！" ) ;
  G_ProeEngine->OpenModel( aFileName, false );
  G_ProeEngine->UpdateModelParas( aFileName, aParas, false );
  gError->Warn( "参数更新OK！" ) ;
}

String KeyItem( String aKeyStr, String aItem )
{
  return Get_ListItem_ByName_Str( aKeyStr, ";", aItem, "=", "" );
}

//---------------------------------------------------------------------------

String Action_Func(String FuncName, const char* format, ...)
{
  va_list params;
  va_start(params, format);

  String aString;
  aString.vprintf( format, params );
  va_end(params);

  aString = ReplaceStr( aString, "(null)", "" );
  return "s." + FuncName + " " + aString +" ";
}

String Action_CopyCS( String aSrcCompPath, String aSrcCSName,
                      String dx, String dy, String dz, String dax, String day, String daz, String aNewCSName )
{
  return Action_Func( "COPYCS", "\"%s\",\"%s\",%s,%s,%s,%s,%s,%s,\"%s\"", aSrcCompPath, aSrcCSName,
                      dx, dy, dz, dax, day, daz, aNewCSName );

  //return "COPYCS(" + aSrcCompPath + "," + aSrcCSName + "," +
  //       dx + "," + dy + "," + dz + "," +
  //       dax + "," + day  + "," + daz  + "," + aNewCSName + ")";
}

String Action_RenameFeature( String aCompFileName, String aOldName, String aNewName )
{
  return  Action_Func( "RenameFeature", "\"%s\",\"%s\",\"%s\"", aCompFileName, aOldName, aNewName );
}

String Action_AlignPairedCS( String aSrcCompPath, String aSrcCSName, String aDestCompPath, String aDestCSName )
{
  return  Action_Func( "AlignPairedCS", "\"%s\",\"%s\",\"%s\",\"%s\"", aSrcCompPath, aSrcCSName, aDestCompPath, aDestCSName  );
}

//---------------------------------------------------------------------------

MProeEngine::MProeEngine()
{
  try
  {
    fIsInitProe = false;

    //fOutStyle = "PROE";              //直接向PROE输出
    fOutStyle = "SCRIPT";

    fScriptStrings = new TStringList;

    //by sxd 2012.11.21 (优先启动同名目录下的Server，便于管理)
    String ApplicationExeName = ApplicationPath() + "\\proeserver.exe";
    WinExec( ApplicationExeName.c_str() , 0 );

    fEngine = Variant::CreateObject( "ProeServer.ProeEngine" );         //如果程序已经启动，取当前程序；否则启动一个
  }
  catch( Exception& e )
  {
    ShowMessage( "启动Proe引擎失败！"+e.Message );
  }
}

MProeEngine::~MProeEngine()
{
  delete fScriptStrings;
//  fEngine.Unassigned();
}

//by sxd 2012.12.20

void MProeEngine::CheckConfig( String IsShowModal )
{
  //String aProeDir = GetRegStringValue(aKey, "InstallLocation", (unsigned int)HKEY_LOCAL_MACHINE);

  String aFileMsgExe = GetRegStringValue( "SYSTEM\\ControlSet001\\Control\\Session Manager\\Environment",
                "PRO_COMM_MSG_EXE", (unsigned int)HKEY_LOCAL_MACHINE );

  if( FileExists( aFileMsgExe )==false )
    ConfigProe(IsShowModal);
}

void MProeEngine::ConfigProe(String IsShowModal)
{
  try
  {
     fEngine.Exec(  PropertyGet("ConfigProe") << IsShowModal );
  }
  catch( Exception& e)
  {
     gError->Warn( "MProeEngine::ConfigProe出错！" + e.Message  );
     return;
  }
}

//by sxd 2012.11.21

String MProeEngine::AskProeTitle()
{
  try
  {
    return fEngine.Exec(  PropertyGet("AskProeTitle") );
  }
  catch( Exception& e)
  {
     gError->Warn( "MProeEngine::AskProeTitle出错！" + e.Message  );
     return "";
  }
}

//by sxd 2012.11.21

void MProeEngine::EraseMemMdl( String aName )
{
  try
  {
    fEngine.Exec(  PropertyGet("EraseMemMdl") << aName );
  }
  catch( Exception& e)
  {
     gError->Warn( "MProeEngine::GetComponentInfo出错！" + e.Message  );
     return;
  }
}


//获取指定组件的 ID+NAME ( ID=xx;NAME=XXX );
String MProeEngine::GetComponentInfo(String aCompPath)
{

  try
  {
    return fEngine.Exec(  PropertyGet("GetModelPathInfo") << aCompPath );
  }
  catch( Exception& e)
  {
     gError->Warn( "MProeEngine::GetComponentInfo出错！" + e.Message  );
     return "";
  }
}

//------------------------- AssemPath处理 --------------------------------------

TStrings* MProeEngine::GetAssemPath( String aModelPath )
{
  TStrings* aStrings = new TStringList;
  GetAssemPath( aModelPath, aStrings );
  return aStrings;
}

void MProeEngine::GetAssemPath( String aModelPath, TStrings* aModelPaths )
{
  if( !CheckInit() )
      return;

  //String aStr = "GetAssemPath::::MdlPath=" +aMdlPath ;
  //ScriptStrings->Add( aStr );

  try
  {
    aModelPaths->Text = fEngine.Exec(  PropertyGet("GetAssemPath") << aModelPath );
  }
  catch( Exception& e)
  {
     gError->Warn( "MProeEngine::aModelPaths出错！" + e.Message  );
     return;
  }
}

//返回的TreeNode->Data指向ModelPath
void MProeEngine::GetAssemPathTree(String aMdlPath, TTreeView* aTree )
{
  if( aTree==NULL )
    return;

  aTree->Items->Clear();
  TStrings* aStrings = GetAssemPath( aMdlPath );  //获取aMdlPath下属的Comp的AssemPath(包括aMdlPath)

  TStrings* aStrings_Parent = new TStringList;
  String aParentStr, aTrueName;
  try
  {
    for( int i=0; i<aStrings->Count; i++ )
    {
      SplitStrTo2Str_Right( aStrings->Strings[i], "\\", aParentStr, aTrueName, true );
        //无前缀，当前Feature或当前Component的情况

      aStrings_Parent->Add(aParentStr);
    }

    ListToTree( aStrings, aStrings_Parent, aTree, "", false );

    TList* aNodes = GetTreeNodes( aTree );
    for( int i=0; i<aNodes->Count; i++)
    {
      TTreeNode* aNode = (TTreeNode*)aNodes->Items[i];

      MComponentNodeInfo* aNodeInfo = new MComponentNodeInfo();
      aNodeInfo->Key = "ModelPath=" + aNode->Text;
      aNode->Data = (void*) aNodeInfo;

      //SetNodeInfo( aNode,"ModelPath=" + aNode->Text + ";NodeType=零部件" );
      //String* aStrData = new String;
      //*aStrData = "ModelPath=" + aNode->Text + ";NodeType=零部件" ;
      //aNode->Data = (void*) aStrData;

      SplitStrTo2Str_Right( aStrings->Strings[i], "\\", aParentStr, aTrueName, true );
      aNode->Text = aTrueName;
    }

    aNodes->Clear();
    delete aNodes;
  }
  __finally
  {
    delete aStrings;
    delete aStrings_Parent;
  }
}

//--------------------- CS处理(对模型中的CS的处理函数) -------------------------

//功能：获取aMdlPath中所有的CS信息
void MProeEngine::GetModelCSInfos( String aMdlPath, TStrings* aCSNames )
{
  //String aStr = "GetModelCSInfos::::MdlPath=" +aMdlPath ;
  //ScriptStrings->Add( aStr );

  if( !CheckInit() )
      return;

  try
  {
    aCSNames->Text = fEngine.Exec(  PropertyGet("GetModelCSInfos") << aMdlPath );
  }
  catch( Exception& e)
  {
     gError->Warn( "MProeEngine::GetModelCSInfos出错！" + e.Message  );
     return;
  }
}

//功能：获取aMdlPath中所有的CS信息
TStrings* MProeEngine::GetModelCSInfos( String aMdlPath )
{
  TStrings* aStrings = new TStringList;
  GetModelCSInfos( aMdlPath, aStrings );
  return aStrings;
}

//从当前Model删除坐标系集合
void MProeEngine::DelCsInMdl( String aModelPath, TStrings* aCreateCsKeyList )
{
  for( int i=0; i<aCreateCsKeyList->Count; i++ )
    DelCsInMdl( aModelPath, aCreateCsKeyList->Strings[i] );
}

TStrings* MProeEngine::CreateCsByUVArray( String SelItem, MDoubleList* uParams, MDoubleList* vParams,
                                           String aCsName, String aBaseCs, bool aParallelAxis )
{
  //生成的CS的关键字
  TStrings* aCsStrs = new TStringList;

  if( uParams==NULL || vParams==NULL || uParams->Count!=vParams->Count )
    return aCsStrs;

  //String aModelPath = KeyItem( SelItem, "ModelPath" );

  for( int i=0; i<uParams->Count; i++ )
  {
    String aMaxId = GetCurMdlMaxCsName(aCsName);

    String aCsStr  = CreateCsByUV( SelItem, *uParams->Items[i], *vParams->Items[i],  0.0, aMaxId, aParallelAxis );
    aCsStrs->Add( aCsStr );
  }

  return aCsStrs;
}

//------------------------------------------------------------------------------
//功能：在SelItem处建立坐标系
//
//------------------------------------------------------------------------------

//String MProeEngine::CreateCsInMdl( String SelItem, String aCsName )
//{
//  String aModelPath =  KeyItem( SelItem, "ModelPath" );
//  return CreateCsByUV( aModelPath, SelItem,
//};


//参数：[ aParallelAxis : False/X与U方向相同; True/X与V方向相同 ]

String MProeEngine::CreateCsInSurface( String SurfaceSelItem, String aCsName, bool aParallelAxis )
{
  double u,v;
  if( !GetSelctionUV( SurfaceSelItem, &u, &v ) )
    return "";

  return CreateCsByUV( SurfaceSelItem, u, v, 0.0,  aCsName, aParallelAxis );
};


//------------------------------------------------------------------------------
//功能：Creat CS In Surface
//参数：[ aModelKey -- 面所在的模型信息 ]
//      [ aSurfaceKey -- 面信息 ]
//------------------------------------------------------------------------------

String MProeEngine::CreateCsByUV( String aSurfaceKey, double uPara, double vPara, double ang,
                                  String aCsName, bool aParallelAxis  )
{
  if( !CheckInit() )
    return "";

  String aOldFileName = "";
  String aCsKey;
  bool HasOpen=false;

  try
  {
    //切换打开的模型（ 由aSurfaceKey的FileName项，获取FileName，打开 )

    String aFileName = KeyItem( aSurfaceKey, "FileName" );
    if( FileExists( aFileName ) )
    {
      aOldFileName = ModelFileName( "" );

      if( UpperCase(aFileName) != UpperCase( aOldFileName ) )
        HasOpen = OpenModel( aFileName, false );
    }

    //生成CS
    //String aModelPath = "";   //KeyItem( aSurfaceKey, "ModelPath" );
    if( aParallelAxis )
       ang = ang + 90.0;
    aCsKey = fEngine.Exec(  PropertyGet("CreateCSByUV") <<  aSurfaceKey << uPara << vPara << ang << aCsName );
  }
  catch( Exception& e)
  {
     gError->Warn( "MProeEngine::CreateCSByUV出错！" + e.Message  );
     aCsKey = "";
  }

  if( HasOpen && aOldFileName!="" )
    OpenModel( aOldFileName, false );

  return aCsKey;
}

//String CreateCsByUV( String SelItem, double uPara, double vPara, String aCsName, String aBaseCs, bool aParallelAxis=false )



//--------------------------- CsNode的操作小工具 -------------------------------

//---------------------- NodeInfo ---------------------------------
MNodeInfo* NodeInfo( TTreeNode* aNode )
{
  if( aNode==NULL || aNode->Data == NULL )
    return NULL;

  return (MNodeInfo*) aNode->Data;
}

//void SetNodeInfo( TTreeNode* aNode, String aNodeInfo )
//{
//  if( aNode == NULL )
//    return;

//  String* aStr = ( String* ) aNode->Data;
//  if( aStr!=NULL )
//    delete aStr;

//  String* aStrData = new String;
//  *aStrData = aNodeInfo ;
//  aNode->Data = (void*) aStrData;
//}

String NodeType( TTreeNode* aNode )
{
  MNodeInfo* aNodeInfo = NodeInfo( aNode );
  if( aNodeInfo == NULL )
    return "";
  else
    return aNodeInfo->NodeType;

  //String aStr = NodeInfo( aNode );
  //return Get_ListItem_ByName_Str( aStr, ";", "NodeType", "=", "" );
}

String NodeKeyStr( TTreeNode* aNode )
{
  MNodeInfo* aNodeInfo = NodeInfo( aNode );
  if( aNodeInfo == NULL )
    return "";
  else
    return aNodeInfo->Key;
}

MCsNodeInfo* CsNodeInfo( TTreeNode* aNode )
{
  if( !IsCSNode( aNode ) )
    return NULL;

  return (MCsNodeInfo*) aNode->Data;
}

String CsNodeUdfKey( TTreeNode* aNode )
{
  MCsNodeInfo* aCsNodeInfo = CsNodeInfo( aNode );
  if( aCsNodeInfo==NULL )
    return "";
  return aCsNodeInfo->UdfKey;
}

void CsNodeSetUdfKey( TTreeNode* aNode, String aUdfKey )
{
  MCsNodeInfo* aCsNodeInfo = CsNodeInfo( aNode );
  if( aCsNodeInfo==NULL )
    return;
  aCsNodeInfo->UdfKey = aUdfKey ;
}

String CompNodeModelPath( TTreeNode* aNode )
{
  String aStr = NodeKeyStr( aNode );
  return KeyItem( aStr,"ModelPath" );   //Get_ListItem_ByName_Str( aStr, ";", "ModelPath", "=", "" );
}

//--------------------------------------------------------------------------
//功能：获取CsTree中的Comp节点
//参数：[ aNode -- CsNode ]
//      [ return -- ComponentNode ]
//--------------------------------------------------------------------------
TTreeNode* CompNodeOfCsNode( TTreeNode* aNode )
{
  if( aNode != NULL && aNode->Parent != NULL )
    return aNode->Parent->Parent;
  else
    return NULL;
}

//功能：给定CS所在的树节点，返回其所在的模型字符串

String CsNodeModelPath( TTreeNode * aNode )
{
  TTreeNode* aParNode = CompNodeOfCsNode( aNode );    //aNode->Parent->Parent;
  return CompNodeModelPath( aParNode );
}

//------------------------------------------------------------------------------
//功能：判别aNode是否为坐标系节点
//参数：[ aNode -- 节点 ]
//      [ JudgeChecked -- 是否依据勾选提取 ]
//------------------------------------------------------------------------------
bool IsCSNode( TTreeNode* aNode )
{
  return IsNamedNode( aNode, "坐标系" );
}

bool IsCompNode( TTreeNode* aNode )
{
  return IsNamedNode( aNode, "零部件" );
}

bool IsNamedNode( TTreeNode* aNode , String aType )
{
  return NodeType(aNode ) == aType;
}

bool MProeEngine::HasLoadCs( TTreeNode* aNode )
{
  TList* aNodes = GetTreeNodeCSNodes( aNode, false );

  //try
  //{
    int aCount = aNodes->Count;
  //}
  //__finally
  //{
    aNodes->Clear();
    delete aNodes;
  //}

  return aCount>0;

}

//----------------------- GetCsTree(创建CSTree) --------------------------------

void MProeEngine::GetCSTree( String aMdlPath, TTreeView* aTree, bool IsMaskLoad )
{
  try
  {
    if( aTree==NULL )
      return;

    GetAssemPathTree( aMdlPath, aTree );

    //智能装载，点取Comp节点时才装载坐标系
    if( IsMaskLoad )
    {
      aTree->OnClick = DoCsTreeClick;
      return;
    }

    //非Mask装载，一次全部读入

    gError->Warn( "正在读取坐标系树，请稍候...!" );
    gError->Prompt( "---" );

    TList* aNodes = GetTreeNodes(aTree );
    int aCount = aNodes->Count;
    for( int i=0; i<aCount; i++ )
    {
      try
      {
         gError->PromptLine( "正在读取模型的坐标系信息！"+ IntToStr(aCount-i-1) + "/" + IntToStr(aCount)   );
         GetCSTree_Node( (TTreeNode*)aNodes->Items[i] );
      }
      catch( Exception& e )
      {
        gError->Warn( "出错！"+e.Message );
      }
    }
    gError->Warn( "OK!" );
  }
  __finally
  {
  }
}

//功能：读取指定组件节点(aNode)的CS
void MProeEngine::GetCSTree_Node(  TTreeNode* aNode )
{
    //TTreeNode* aNode = (TTreeNode*)aNodes->Items[i];
    if ( !IsCompNode(aNode) )   //aNode == NULL || aNode->Data == NULL )
      return;

    gError->Warn( "正在读取节点(" +aNode->Text+")的坐标系信息，请稍候...!" );

    String aStr = NodeKeyStr( aNode ) ; //*(String*) aNode->Data;
    String aModelPath = KeyItem(aStr,"ModelPath");      //Get_ListItem_ByName_Str( aStr, ";", "ModelPath", "=", "" );

    //读取当前Model的CS信息到CB_AsmFeatList
    TStrings* aCsNames = gProeEngine->GetModelCSInfos( aModelPath );

    for( int j=0; j<aCsNames->Count; j++ )
    {
      String aStr = aCsNames->Strings[j];
      String aName = KeyItem( aStr, "Name" );

      MCsNodeInfo* aCsNodeInfo = new MCsNodeInfo;
      aCsNodeInfo->Key = aStr;

      //String* aStrCs = new String;
      //*aStrCs = aCsNames->Strings[j] + ";NodeType=坐标系" ;
      //String aName = Get_ListItem_ByName_Str( *aStrCs, ";", "Name", "=", "" );

      TTreeNode* aCsNode =TreeNode_AddChild( aNode, aName );

      //aCsNode->Data = (void*)aStrCs;
      aCsNode->Data = (void*)aCsNodeInfo;
    }

    delete aCsNames;
    gError->Prompt( "OK!" );
}

//功能：智能读取时，点击TreeNode的操作
void __fastcall MProeEngine::DoCsTreeClick(TObject *Sender)
{
  if( Sender==NULL || !Sender->ClassNameIs( "TTreeView" ) )
    return;

  TTreeView* aTree = (TTreeView*)Sender;

  TTreeNode* aNode = aTree->Selected;
  if( aNode == NULL || !IsCompNode(aNode ) || HasLoadCs( aNode ) )   //判别是否已经装载
    return;

  GetCSTree_Node( aNode );
  SetCsTreeImage( aTree );
}

void SetCsTreeImage(TTreeView* aTree)
{
  TList* aNodes = GetTreeNodes( aTree );
  for( int i=0; i<aNodes->Count; i++ )
  {
    try
    {
      SetCsNodeImage( (TTreeNode*) aNodes->Items[i] );
    }
    catch(Exception& e)
    {
      gError->Warn( "SetTreeImage出错！"+e.Message );
    }
  }
  aNodes->Clear();
  delete aNodes;
}

void SetCsNodeImage(TTreeNode* aNode)
{
  if( aNode==NULL )
    return;

  if( IsCompNode(aNode) )
  {
    aNode->ImageIndex = 0;
    aNode->SelectedIndex = 0;
  }
  else if( IsCSNode(aNode) )
  {
    aNode->ImageIndex = 1;
    aNode->SelectedIndex = 1;
  }
  else
  {
    aNode->ImageIndex = -1;
    aNode->SelectedIndex = -1;
  }
}

//---------------- GetTreeCSNodes（从CSTree上读取信息） -------------------

//功能：获取aTree中的CSNode集合
TList* GetTreeCSNodes( TList* aAllNodes, bool IsGetChecked )
{
  TList* aNodes = new TList();
  for (int i=0; i<aAllNodes->Count; i++)
  {
     TTreeNode * aNode = (TTreeNode*) aAllNodes->Items[i];
     if ( !IsCSNode( aNode  ) )
       continue;

     if ( IsGetChecked && !GetNodeChecked( aNode ) )
       continue;

     aNodes->Add( (void*)aNode );
  }
  return aNodes;
}

TList* GetTreeCSNodes( TTreeView* aTree, bool IsGetChecked )
{
  TList* aAllNodes = GetTreeNodes( aTree );
  TList* aNodes = GetTreeCSNodes( aAllNodes, IsGetChecked );
  aAllNodes->Clear();
  delete aAllNodes;
  return aNodes;
}


TList* GetTreeNodeCSNodes( TTreeNode* aNode, bool IsGetChecked )
{
  TList* aAllNodes = GetTreeNodeNodes( aNode );
  TList* aNodes = GetTreeCSNodes( aAllNodes, IsGetChecked );
  aAllNodes->Clear();
  delete aAllNodes;
  return aNodes;
}



//----------------------- CS相关类 ---------------------------------------------

MNodeInfo::MNodeInfo()
{
  NodeType = "";
  Key = "";
  Info = "";
}

MComponentNodeInfo::MComponentNodeInfo() : MNodeInfo()
{
  NodeType = "零部件";
}

MCsNodeInfo::MCsNodeInfo() : MNodeInfo()
{
  NodeType = "坐标系";
  UdfKey = "";
}

//---------------------------------------------------------------------------
//参数：[ aPrompt : 提示信息 ]
//      [ aCsNamePrefix :  CS前缀 ]
//      [ SelItem : 新生成的CS关键字 ]
//---------------------------------------------------------------------------

void SelectAndCreateCS( String aPrompt, String aCsNamePrefix, String& SelItem  )
{
  String aCsName, aCsKey;
  SelectAndCreateCS( aPrompt, aCsNamePrefix, SelItem, aCsName, aCsKey  );
}

void SelectAndCreateCS( String aPrompt, String aCsNamePrefix, String& SelItem, String& aCsName, String& aCsKeyStr  )
{
  SelItem = gProeEngine->GetSelection( "请选择特征定位点", "surface" );
  if ( SelItem == ""  )
    throw Exception("未选取正确位置！");

  aCsName = GetCurMdlMaxCsName(aCsNamePrefix);
  gProeEngine->CreateCsInSurface( SelItem, aCsName );
}

String GetCurMdlMaxCsName( String aCsLab )
{
  TStrings* aCsNames = gProeEngine->GetModelCSInfos( "" );
  String aMaxCsName = Strings_GetMaxName( aCsLab, aCsNames );
  delete aCsNames;
  return aMaxCsName;
}

String UpdateCsInfo( String aCsKeyStr, String aNewItems )
{
  return String_UpdateNamedItem( aCsKeyStr, aNewItems, ";", "=" );
}

String BaseCs( String aModelType )
{
   if ( UpperCase( aModelType ) == "PART" )
     return "ASM_DEF_CSYS";
   else
     return "PRT_CSYS_DEF";
}

String BaseCs()
{
  return BaseCs( gProeEngine->ModelType( "" ) );
}


//----------------------- Face -------------------------------------------------
String MProeEngine::GetFaceInfo( String SelSurfaceItem )
{
  if( !CheckInit() )
      return "";

  try
  {
    return fEngine.Exec(  PropertyGet("GetFaceUV") << SelSurfaceItem );
  }
  catch( Exception& e)
  {
     gError->Warn( "MProeEngine::GetFaceUV出错！" + e.Message  );
     return "";
  }
}

void MProeEngine::GetFaceUVSize( String SelSurfaceItem, double* aUSize, double* aVSize )
{
  double u0,u1,v0,v1;
  GetFaceUV( SelSurfaceItem, &u0, &u1, &v0, &v1 );
  *aUSize = fabs( u1 - u0 );
  *aVSize = fabs( v1 - v0 );
}

void MProeEngine::GetFaceUV( String SelSurfaceItem, double* aUMin, double* aUMax, double* aVMin, double* aVMax )
{
  TStrings* aStrings = new TStringList;

  aStrings->Text = fEngine.Exec(  PropertyGet("GetFaceUV") << SelSurfaceItem );
  *aUMin = Get_ListItemFloat_ByName( aStrings, "UMin", "=", 0 );
  *aUMax = Get_ListItemFloat_ByName( aStrings, "UMax", "=", 0 );
  *aVMin = Get_ListItemFloat_ByName( aStrings, "VMin", "=", 0 );
  *aVMax = Get_ListItemFloat_ByName( aStrings, "VMax", "=", 0 );

  delete aStrings;
}

bool MProeEngine::GetSelctionUV( String SelItem, double* aU, double* aV )
{

  String aStr = GetSelectionInfo( SelItem );

  if( aStr == "" )
    return false;

  TStrings* aStrings = splitToStrings( aStr, ";", false );

  *aU = Get_ListItemFloat_ByName( aStrings, "U", "=", 0 );
  *aV = Get_ListItemFloat_ByName( aStrings, "V", "=", 0 );

  delete aStrings;
  return true;
}

String MProeEngine::GetSelectionInfo( String SelItem )
{
  if( !CheckInit() )
    return "";

  try
  {
    return fEngine.Exec(  PropertyGet("GetSelctionUV") << SelItem );
  }
  catch( Exception& e)
  {
     gError->Warn( "MProeEngine::GetSelctionUV出错！" + e.Message  );
     return "";
  }
}

//----------------------- MOdel ------------------------------------------------
String MProeEngine::ModelFileName( String aModelPath )
{
  if( !CheckInit() )
      return "";

  try
  {
    String aModelFileName = fEngine.Exec(  PropertyGet("ModelFileName") << aModelPath );
    return aModelFileName;
  }
  catch( Exception& e)
  {
     gError->Warn( "MProeEngine::ModelFileName出错！" + e.Message  );
     return "";
  }
}

//-------------------------- Model ---------------------------------------------

//返回 "PART" || "ASSEMBLE"
String MProeEngine::ModelType( String aModelPath )
{
  if( !CheckInit() )
      return "";

  try
  {
    String aModelType = fEngine.Exec(  PropertyGet("ModelType") << aModelPath );
    return aModelType;
  }
  catch( Exception& e)
  {
     gError->Warn( "MProeEngine::ModelType出错！" + e.Message  );
     return "";
  }
}

//-------------------------------------------------------------------------
//功能: 获取aModelPath中所有的模型参数
//-------------------------------------------------------------------------
String MProeEngine::ReadMdlParas_All(String aModelPath)
{
  if( !CheckInit() )
    return "";
  try
  {
    return fEngine.Exec(  PropertyGet("ReadMdlParas_All") << aModelPath );
  }
  catch( Exception& e)
  {
     gError->Warn( "MProeEngine::ReadMdlParas_All出错！" + e.Message  );
     return "";
  }
}

void MProeEngine::EraseModel( String aFileName )
{
  if( !CheckInit() )
    return;

  try
  {
    String aStr = "FileName=" + aFileName;
    gError->Warn( "EraseModel！(" + aStr + ")" );

    fEngine.Exec(  PropertyGet("EraseMdlByName") << aFileName  );
    return;
  }
  catch( Exception& e)
  {
     gError->Warn( "MProeEngine::EraseModel出错！" + e.Message  );
     return;
  }
}

//------------------------------------------------------------------------------
//功能：打开模型
//参数：
//  [ aFileName -- 模型的文件名 ]
//  [ OpenWhenExsist -- T / 如果模型已经打开，擦除当前内存中的模型，重新打开  F / 如果模型已经打开，将其激活，退出 ]
//------------------------------------------------------------------------------
bool MProeEngine::OpenModel( String aFileName, bool OpenWhenExsist )
{
  if( !CheckInit() )
    return false;

  try
  {
    String aStr = "FileName=" + aFileName + "OpenWhenExsist=" + Sysutils::BoolToStr(OpenWhenExsist);
    gError->Warn( "OpenModel！(" + aStr + ")" );

    if( aFileName == "" )
      throw Exception( "文件名为空！" );

    bool IsOk = fEngine.Exec(  PropertyGet("OpenProModel") << aFileName << OpenWhenExsist );
    return IsOk;
  }
  catch( Exception& e)
  {
     gError->Warn( "MProeEngine::OpenModel出错！" + e.Message  );
     return false;
  }
}


bool MProeEngine::OpenModelByKey( String aModelKey )
{
  if( !CheckInit() )
    return false;

  try
  { 
    fEngine.Exec(  Function("DisplayMdl") << aModelKey );
    return true;
  }
  catch( Exception& e)
  {
     gError->Warn( "MProeEngine::OpenModel出错！" + e.Message  );
     return false;
  }
}

void MProeEngine::Execute(TStrings* aStrings)
{
  for( int i=0; i<aStrings->Count; i++ )
    Execute( aStrings->Strings[i] );
}

void MProeEngine::Execute(String aStr)
{
  if( aStr == "" )
    return;

  ScriptStrings->Add( aStr );
  if( gProeEngine->IsScriptModel() )
    return;

  TStrings* aNewStrings = new TStringList;

  aNewStrings->Add( " set s = GetObject(\"\", \"ProeServer.ProeEngine\")" );
  aNewStrings->Add( aStr );

  try
  {
    RunScript( aNewStrings );
    gError->Warn( "OK!(" + aStr + ")" );
  }
  catch( Exception& e )
  {
    gError->Warn( "MProeEngine::Execute出错！" + e.Message + "(" + aStr+ ")" );
  }

  delete aNewStrings;

/*  if( aStrings->Text == "" )
    return;

  ScriptStrings->Add( aStrings->Text );
  if( gProeEngine->IsScriptModel() )
    return;

  TStrings* aNewStrings = new TStringList;

  aNewStrings->Add( " set s = GetObject(\"\", \"ProeServer.ProeEngine\")" );
  aNewStrings->Text = aNewStrings->Text + "\n" + aStrings->Text;

  try
  {
    RunScript( aNewStrings );
  }
  catch( Exception& e )
  {
    gError->Warn( "MProeEngine::Execute出错！" + e.Message + "(" + aStrings->Text + ")" );
  }

  delete aNewStrings;*/
}



//------------------- CheckInit ------------------------------------------

bool MProeEngine::CheckInit()
{
  //认为设置中断点，以便调试

  if( G_CheckedNum>0 )
  {
    if( G_CheckedNo > G_CheckedNum )
      throw Exception( "调试终止！" );
    else
      G_CheckedNo = G_CheckedNo + 1;
  }

  if( fIsInitProe == true )
    return true;

  if( fEngine.IsEmpty() || fEngine.IsNull() )
    throw Exception( "未驱动Proe引擎!" );

  try
  {
     gError->Warn( "启动Proe引擎！" );

     fIsInitProe = fEngine.Exec(  PropertyGet("InitProe") );

     //if( fIsInitProe==false )
     //  throw Exception( "请先启动PRO/E" );

     //fIsInitProe = fEngine.Exec(  Function( "InitProe" ));
     //fIsInitProe = true;
     return fIsInitProe;
  }
  catch( Exception& e )
  {
    gError->Warn( "启动Proe引擎失败！"+e.Message );
    return false;
  }
}

bool MProeEngine::IsScriptModel()
{
  return UpperCase(OutStyle) == "SCRIPT";
}

TStrings* ParasToStrings( MParaList* aParas )
{
  TStrings* aStrings = new TStringList;
  if( aParas==NULL )
    return aStrings;

  for( int i=0; i<aParas->Count; i++ )
  {
    MPara* aPara = aParas->Items[i];
    aStrings->Add( aPara->Name +","+aPara->Value );
  }
  return aStrings;
}

//----------------------- GetSurfaceInfo ---------------------------------------
String MProeEngine::GetSurfaceInfo( String aFaceKey )
{
  if( !CheckInit() )
      return "";

  String aStr = "GetSurfaceInfo::::FaceKey=" +aFaceKey ;
  ScriptStrings->Add( aStr );

  try
  {
    String aStr = fEngine.Exec(  PropertyGet("GetSurfaceInfo") << aFaceKey );
    return NamedItemOfStringsStr( aStr, 0 );
  }
  catch( Exception& e)
  {
     gError->Warn( "MProeEngine::GetSurfaceInfo出错！" + e.Message  );
     return "";
  }
}


//------------------- UpdateModelParas ------------------------------------

void MProeEngine::UpdateModelParas( String aFileName, MParaList* aParas, bool IsNewFile )
{
  String aStr = "UpdateModelParas::::FileName=" + aFileName + ",IsNewFile=" + Sysutils::BoolToStr(IsNewFile) + ",";
  for( int i=0; i<aParas->Count; i++ )
  {
    MPara* aPara = aParas->Items[i];
    aStr = aStr + ",ParaName=" + aPara->Name +",ParaValue="+aPara->Value;
  }
  ScriptStrings->Add( aStr );

  if( IsScriptModel() )
    return;

  if( !CheckInit() )
    return;

  if( aParas->Count<=0 )
    return;
      
  TStrings* aStrings = ParasToStrings(aParas);
  try
  {
    gError->Warn( "UpdateModelParas！(" + aStr + ")" );
    fEngine.Exec(  Function("UpdateModelParas") << aFileName << aStrings->Text << IsNewFile   );
    //fEngine.Exec(  Function("SetParas") << aFileName << aStrings->Text << IsNewFile   );
  }
  catch( Exception& e)
  {
     gError->Warn( "UpdateModelParas出错！" + e.Message + "(" + aFileName + ")" );
  }

  delete aStrings;
}


//------------------- GetModelParaStrings ---------------------------------

TStrings* MProeEngine::GetModelParaStrings( String aFileName, bool IsNewFile  )
{
  String aGroup = "PROE";                                                     //指定ParaGroup
  
  TStrings* aStrings = new TStringList;
  if( !CheckInit() )
    return aStrings;

  aStrings->Text = fEngine.Exec(  PropertyGet("ReadMdlPara") << aFileName << aGroup << IsNewFile );                  //读取指定模型参数
  return aStrings;
}

//---------------------------- CloseModel ---------------------------------

void MProeEngine::CloseModel()
{
  if( !CheckInit() )
    return;

  fEngine.Exec(  Function("CloseModel")  );                  //读取指定模型参数
}

void MProeEngine::SaveScriptFile( String aPath )
{
  ScriptStrings->SaveToFile( aPath + "\\script.cmd" );
}

String MProeEngine::NewAssemble( String aFileName )
{
   return AddCompToAssem( aFileName, "", true );
}

//---------------------------- AddCompToAssem ------------------------------

//参数：[ aCompFileName -- 模型对应的文件名 ]
//      [ AddPath -- 模型在装配中的路径，例如：LRM模块.左侧插拔器.螺杆 ]
//      [ NewWhenNULL -- True / 当aCompFileName不存在时，自动新建一个 False / 当aCompFileName不存在时，显示错误 ]
//      [ 返回 -- 新建的ModelPath ]

//?? NewWhenNULL ---  aCompFileName不存在，自动新建一个
//?? OpenWhenNULLPath -- AddPath为""，直接打开aCompFileName

String MProeEngine::AddCompToAssem( String aCompFileName, String AddPath, bool NewWhenNULL )
{
  String aStr = "FileName=" +aCompFileName+",AssemPath=" + AddPath;
  ScriptStrings->Add( "AddCompToAssem::::" +aStr  );

  if( IsScriptModel() )
    return "";

  if( !CheckInit() )
    return "";

  try
  {

    if( !NewWhenNULL && !FileExists( aCompFileName ) )
      throw Exception( "装配文件(" + aCompFileName + ")不存在！" );

    String aStrName = ExtractFileName_NoDot ( aCompFileName );
    String aStrPath = ExtractFileName_NoDot ( AddPath );

    if( UpperCase( aStrName ) == UpperCase( aStrPath ) )     //避免 A -> X1\X2\A 的情况
      throw Exception( "实例名与加入的装配名称相同，无法处理！" );

    gError->Warn( "AddCompToAssem！(" + aStr + ")" );


    String aModelPath = fEngine.Exec(  PropertyGet("AddCompToAssem") << aCompFileName << AddPath );
    return aModelPath;
  }
  catch( Exception& e)
  {
     gError->Warn( "AddCompToAssem出错！" + e.Message  + "(" + aStr + ")" );
     return "";
  }

}

//------------------------------------------------------------------------------
//功能：零部件的坐标系约束
//参数：[ aModePath1, aAF1Name -- 被约束的零件（移动体）]
//      [ aModePath2, aAF2Name -- 约束母体 ]
//------------------------------------------------------------------------------
void MProeEngine::ConsComp( String aModePath1, String aAF1Name, String aModePath2, String aAF2Name )
{
  String aStr = "FromModelPath=" +aModePath1+",FromFeatureName="+aAF1Name+
                ",ToModelPath=" + aModePath2 + ",ToFeatureName=" + aAF2Name;
  ScriptStrings->Add( "ConsComp::::" + aStr );

  if( IsScriptModel() )
    return;
  if( !CheckInit() )
    return;

  try
  {
    gError->Warn( "ConsComp！(" + aStr + ")" );
    fEngine.Exec(  Function("ConsComp") << aModePath1 << aAF1Name << aModePath2 << aAF2Name   );
  }
  catch( Exception& e)
  {
     gError->Warn( "ConsComp出错！" + e.Message + "(" + aStr +")" );
  }
}


//改进：自动识别Key与Name
void MProeEngine::ConsCompByKey( String aModelPath1, String aAF1KeyStr, String aModelPath2, String aAF2KeyStr )
{
  String aStr = "FromModelPath=" +aModelPath1+",FromFeatureName="+aAF1KeyStr+
                ",ToModelPath=" + aModelPath2 + ",ToFeatureName=" + aAF2KeyStr;
  ScriptStrings->Add( "ConsCompByKey::::" + aStr );

  if( IsScriptModel() )
    return;
  if( !CheckInit() )
    return;

  try
  {
    gError->Warn( "ConsCompByKey！(" + aStr + ")" );
    fEngine.Exec(  Function("ConsCompByKey") << aModelPath1 << aAF1KeyStr << aModelPath2 << aAF2KeyStr   );
  }
  catch( Exception& e)
  {
     gError->Warn( "ConsComp出错！" + e.Message + "(" + aStr +")" );
  }
}

//-------------------  ShapeFeature --------------------------------------------

String TrueCompPath( String aCompPath, bool IsCutFirst )
{
  if( IsCutFirst == true )
    return aCompPath;
  else
    return Str_RemoveLastItem(aCompPath, "\\");
}

bool MProeEngine::IsExistShapeFeature( String aUdfKey )
{
  String aStr = "IsExistShapeFeature::::UDFKeyStr=" +aUdfKey;
  if( !CheckInit() )
    return false;
  try
  {
    return fEngine.Exec(  PropertyGet("IsUDFExist") << aUdfKey );
  }
  catch( Exception& e)
  {
     gError->Warn( "IsExistShapeFeature出错！" + e.Message + "(" + aStr + ")" );
     return false;
  }
}

//------------------------------------------------------------------------
//参数：[ aGraphFileName : UDF文件 ]
//      [ aCompFileName,aAFComp: 确定UDF定位的参考坐标系 ]
//      [ IsCutFirst: true,UDF建立在aCompFileName， flase,UDF建立在aCompFileName的父装配 ]
//------------------------------------------------------------------------

String MProeEngine::AddShapeFeature( String aGraphFileName, String aCompPath, String aAFComp, bool IsCutFirst, String aExtrudeComps  )
{
  return AddShapeFeature( aGraphFileName, aCompPath, aAFComp,  TrueCompPath (aCompPath,IsCutFirst), aExtrudeComps );
}

//参数：[ aGraphFileName / Graph文件,例如：ProeModel\Lib\chacao_h_cut.gph.1 ]
//      [ aCompFileName / 加入Graph的CompPath, 例如: jianhuajixiang\TOP ]
//      [ aAFComp / 特征名称, 例如: 上板插槽_1 ]
//      [ ACompPathAddIn / 新建ShapeFeature所在的CompPath,例如jianhuajixiang ]
//      [ aExtrudeComps / 需要避免Cut的零部件集合, 例如: ]

String MProeEngine::AddShapeFeature( String aGraphFileName, String aCompPath, String aAFComp, String ACompPathAddIn, String aExtrudeComps )
{
  String aStr = "FromFileName=" +aGraphFileName+
                        ",CompPath=" + aCompPath + ",FeatPath=" + aAFComp + ",CompAddIn="+ACompPathAddIn + ",ExtrudeComps="+aExtrudeComps;
  ScriptStrings->Add( "AddShapeFeature::::" + aStr );

  if( IsScriptModel() )
    return "";
  if( !CheckInit() )
    return "";

  try
  {
    gError->Warn( "AddShapeFeature！(" + aStr + ")" );

    if( !FileExists( aGraphFileName ) )
      throw Exception( "文件(" + aGraphFileName + ")不存在！" );

    //return fEngine.Exec(  Function("AddShapeFeature") << aGraphFileName << aCompPath << aAFComp << ACompPathAddIn << aExtrudeComps );
    return fEngine.Exec(  PropertyGet("AddSFeature") << aGraphFileName << aCompPath << aAFComp << ACompPathAddIn << aExtrudeComps );
  }
  catch( Exception& e)
  {
     gError->Warn( "AddShapeFeature出错！" + e.Message + "(" + aStr + ")" );
  }

}

void MProeEngine::UpdateShapeFeatureParas( String aCompFileName, String aSFName, bool IsCutFirst, MParaList* aParas  )
{
  UpdateShapeFeatureParas( TrueCompPath (aCompFileName,IsCutFirst), aSFName, aParas );
}

void MProeEngine::UpdateShapeFeatureParas( String aSFCompPath, String aSFName, MParaList* aParas  )
{
  String aStr = "UpdateShapeFeatureParas::::SFCompPath=" +aSFCompPath +",SFName="+aSFName + ",";

  for( int i=0; i<aParas->Count; i++ )
  {
    MPara* aPara = aParas->Items[i];
    aStr = aStr + ",ParaName=" + aPara->Name +",ParaValue="+aPara->Value;
  }
  ScriptStrings->Add( aStr );

  if( IsScriptModel() )
    return;
  if( !CheckInit() )
    return;

  TStrings* aStrings = ParasToStrings(aParas);
  try
  {
    gError->Warn( "UpdateShapeFeatureParas！(" + aStr + ")" );

    fEngine.Exec(  Function("UpdateSFParas") << aSFCompPath << aSFName << aStrings->Text   );
  }
  catch( Exception& e)
  {
     gError->Warn( "UpdateSFParas出错！" + e.Message + "(" + aStr + ")" );
  }
  delete aStrings;
}

void MProeEngine::UpdateShapeFeatureParas_ByKey( String aUdfKey, MParaList* aParas  )
{
  String aModelPath = KeyItem( aUdfKey, "UdfModelPath" );
  String aSFName = KeyItem( aUdfKey, "UDFHeadName" );

  UpdateShapeFeatureParas( aModelPath, aSFName, aParas );
}

bool MProeEngine::DeleteShapeFeature( String aKeyStr )
{
  String aStr = "DeleteShapeFeature::::UDFKeyStr=" +aKeyStr;
  if( !CheckInit() )
    return false;
  try
  {
    gError->Warn( "DeleteShapeFeature！(" + aStr + ")" );

    return fEngine.Exec(  PropertyGet("DelUDFByKey") << aKeyStr );
  }
  catch( Exception& e)
  {
     gError->Warn( "DeleteShapeFeature出错！" + e.Message + "(" + aStr + ")" );
     return false;
  }
}

//---------------------- UDF ---------------------------------------------------

//void MProeEngine::ShapeFeature_AutoInterSect( String aCompPath, String aFeatPath, bool IsCutFirst )
//{
//   ShapeFeature_AutoInterSect( TrueCompPath (aCompPath,IsCutFirst), aFeatPath );
//}

//功能: 实现“UDF->选取特征->相交->自动添加相交组件”的操作
//void MProeEngine::ShapeFeature_AutoInterSect( String aCompPath, String aFeatPath )
//{
//  String aStr = "CompPath=" +aCompPath+
//                        ",FeatPath=" + aFeatPath ;
//  ScriptStrings->Add( "UDF_AutoInterSect::::" + aStr );

//  if( IsScriptModel() )
//    return;

//}

void MProeEngine::ShapeFeature_ExcludeInertSect( String aCompPath, String aFeatPath, bool IsCutFirst, String aCompPaths_Exclude )
{
  ShapeFeature_ExcludeInertSect( TrueCompPath (aCompPath,IsCutFirst), aFeatPath, aCompPaths_Exclude );
}

//功能: 实现“UDF->选取特征->相交->去除”的操作
void MProeEngine::ShapeFeature_ExcludeInertSect( String aCompPath, String aFeatPath, String aCompPaths_Exclude )
{
  String aStr = "CompPath=" +aCompPath+
                        ",FeatPath=" + aFeatPath + ",Exclude:" + aCompPaths_Exclude ;
  ScriptStrings->Add( "UDF_ExcludeInertSect::::" + aStr );

  if( IsScriptModel() )
    return;
  if( !CheckInit() )
    return;

  try
  {
    gError->Warn( "ShapeFeature_ExcludeInertSect！(" + aStr + ")" );

    fEngine.Exec(  Function("UDF_ExcludeInertSect") << aCompPath << aFeatPath << aCompPaths_Exclude  );
  }
  catch( Exception& e)
  {
     gError->Warn( "UDF_ExcludeInertSect出错！" + e.Message + "(" + aStr + ")" );
  }

}

//------------------------------------------------------------------------------
void MProeEngine::RenameFeature( String aCompFileName, String aOldName, String aNewName )
{
  if( IsEqualByCase(aOldName,aNewName,false) )
    return;

  String aStr = "RenameAssemFeature::::FromFileName=" +aCompFileName+ ",OldName="+aOldName + ",NewName="+aNewName;
  ScriptStrings->Add( aStr );

  if( IsScriptModel() )
    return;
  if( !CheckInit() )
    return;

  try
  {
    gError->Warn( "RenameAssemFeature！(" + aStr + ")" );

    fEngine.Exec(  Function("RenameFeature") << aCompFileName << aOldName << aNewName  );
  }
  catch( Exception& e)
  {
     gError->Warn( "RenameFeature出错！" + e.Message  );
  }
}

void MProeEngine::ArrayFeature( String aCompPath, String aFeatPath, int aNX, double aDX, int aNY, double aDY )
{
  String aStr = "ArrayFeature::::FromFileName=" +aCompPath+ ",aFeatName="+aFeatPath +
                      ",NX=" + IntToStr( aNX ) + ",DX=" + FloatToStr( aDX ) +
                      ",NY=" + IntToStr( aNY ) + ",DY=" + FloatToStr( aDY );
  ScriptStrings->Add( aStr );

  if( IsScriptModel() )
    return;
  if( !CheckInit() )
    return;

  try
  {
    gError->Warn( "ArrayFeature！(" + aStr + ")" );

    fEngine.Exec(  Function("ArrayFeature") << aCompPath << aFeatPath << aNX << aDX << aNY << aDY  );
  }
  catch( Exception& e)
  {
     gError->Warn( "ArrayFeature出错！" + e.Message  );
  }
}

//移动坐标系[ aDestCompPath, aDestCSName ]，使其与坐标系[ aSrcCompPath, aSrcCSName ]对齐（Z坐标投影）

void MProeEngine::AlignPairedCS( String aSrcCompPath, String aSrcCSName, String aDestCompPath, String aDestCSName )
{
  String aStr = "SrcFileName=" +aSrcCompPath+ ",SrcCSName="+aSrcCSName +
                        ",DestFileName=" + aDestCompPath + ",DestCSName=" + aDestCSName;

  ScriptStrings->Add( "AlignPairedCS::::" + aStr );

  if( IsScriptModel() )
    return;
  if( !CheckInit() )
    return;

  try
  {
    gError->Warn( "AlignPairedCS！(" + aStr + ")" );

    fEngine.Exec(  Function("AlignPairedCS") << aSrcCompPath << aSrcCSName << aDestCompPath << aDestCSName   );
  }
  catch( Exception& e)
  {
     gError->Warn( "AlignPairedCS出错！" + e.Message + "(" + aStr + ")" );
  }
}

void MProeEngine::CopyCS( String aSrcCompPath, String aSrcCSName,
                          double dx, double dy, double dz, double dax, double day, double daz, String aNewCSName )
{
  String aStr =  "CopyCS::::SrcFileName=" +aSrcCompPath+ ",SrcCSName="+aSrcCSName +
                      ",DX=" + FloatToStr(dx) + ",DY=" + FloatToStr(dy) + ",DZ=" + FloatToStr(dz) +
                      ",AX=" + FloatToStr(dax) + ",AY=" + FloatToStr(day) + ",AZ=" + FloatToStr(daz) +
                      ",NewCSName="+aNewCSName ;
  ScriptStrings->Add( aStr );

  if( IsScriptModel() )
    return;
  if( !CheckInit() )
    return;

  try
  {
    gError->Warn( "CopyCS！(" + aStr + ")" );

    fEngine.Exec(  Function("CopyCS") << aSrcCompPath << aSrcCSName << dx << dy << dz << dax << day << daz << aNewCSName  );
  }
  catch( Exception& e)
  {
     gError->Warn( "CopyCS出错！" + e.Message  );
  }
}

//------------------------------------------------------------------
//参数：
// [ aCompPath: ASM的路径名称 ]
// [ aComponentNames：成组零件名称，以";"分割，例如“AA;BB”]
// [ aGroup：组名称 ]
//------------------------------------------------------------------
void MProeEngine::GroupComponents( String aCompPath, String aComponentNames, String aGroupName )
{
  String aStr = "GroupComponents::::ComPath=" +aCompPath+ ",ComponentNames="+aComponentNames + ",GroupName="+aGroupName ;
  ScriptStrings->Add( aStr );

  if( IsScriptModel() )
    return;
  if( !CheckInit() )
    return;

  try
  {
    gError->Warn( "GroupComponents(" + aStr + ")" );

    fEngine.Exec(  Function("GroupComponents") << aCompPath << aComponentNames << aGroupName );
  }
  catch( Exception& e)
  {
     gError->Warn( "GroupComponents出错！" + e.Message  );
  }
}

String MProeEngine::ModelInfo( String aMdlName )
{
  String aStr = "ModelInfo::::MdlName=" +aMdlName ;
  ScriptStrings->Add( aStr );
  //if( IsScriptModel() )
  //  return "";
  if( !CheckInit() )
    return "";

  try
  {
    gError->Warn( "ModelInfo(" + aStr + ")" );

    String aStr = fEngine.Exec(  PropertyGet("ModelInfo") << aMdlName );
    return aStr;
  }
  catch( Exception& e)
  {
     gError->Warn( "MProeEngine::ModelInfo出错！" + e.Message  );
     return "";
  }
}

String MProeEngine::UDFInfo( String aMdlName )
{
  String aStr = "UDFInfo::::MdlName=" +aMdlName ;
  ScriptStrings->Add( aStr );
  //if( IsScriptModel() )
  //  return "";

  if( !CheckInit() )
    return "";

  try
  {
    gError->Warn( "UDFInfo(" + aStr + ")" );

    String aStr = fEngine.Exec(  PropertyGet("UDFInfo") << aMdlName );
    return aStr;
  }
  catch( Exception& e)
  {
     gError->Warn( "MProeEngine::UDFInfo出错！" + e.Message  );
     return "";
  }
}

String MProeEngine::ProjectDataInfo( String aMdlName )
{
  if( !CheckInit() )
      return "";

  try
  {
    String aStr = fEngine.Exec(  PropertyGet("ProjectDataInfo") << aMdlName );
    return aStr;
  }
  catch( Exception& e)
  {
     gError->Warn( "MProeEngine::ModelInfo出错！" + e.Message  );
     return "";
  }
}



TStrings* MProeEngine::GetSelections( String aPrompt, String aFilter, int aMaxSelNum )
{
  TStrings* aStrings = new TStringList;
  if( !CheckInit() )
    return aStrings;

  try
  {
    //aStrings->Text = fEngine.Exec(  PropertyGet("ProeSelect") << aPrompt << aFilter << IntToStr(aMaxSelNum) );
    gError->Warn( aPrompt );
    aStrings->Text = fEngine.Exec(  PropertyGet("ProeSelect") << aFilter << IntToStr(aMaxSelNum) );
    return aStrings;
  }
  catch( Exception& e)
  {
     gError->Warn( "MProeEngine::GetSelections出错！" + e.Message  );
     return aStrings;
  }
}
//------------------------3D工艺设计(By何小波)-------------------------------
String MProeEngine::GetSelection( String aPrompt, String aFilter )
{
  String aStr;
  TStrings* aStrings = GetSelections( aPrompt, aFilter, 1 );

  if( aStrings->Count<=0 )
    aStr = "";
  else
    aStr = aStrings->Strings[0];

  delete aStrings;
  return aStr;
}

String MProeEngine::DynSelectFeat(String filter, bool ISPrecision)
{
   try
  {
    String aStr = fEngine.Exec(  PropertyGet("DynamicSelectFeat") << filter << ISPrecision );
    return aStr;
  }
  catch( Exception& e)
  {
     gError->Warn( "MProeEngine::DynSelectFeat出错！" + e.Message  );
     return "";
  }
}

void MProeEngine::GetDimensionData(String Item,String *ID,double *baseValue,
                  double *upperError,double *lowwerError,bool IsPrecision)
{
   try
  {
    String aStr = fEngine.Exec(  PropertyGet("GetDimData") << Item << IsPrecision );
    TStrings* aStrings = splitToStrings(aStr,";");
    *ID      = GetValue_ByName(aStrings,"ID","=");
    *baseValue   = StrToFloat(GetValue_ByName(aStrings,"BASEVALUE","="));
    *upperError  = StrToFloat(GetValue_ByName(aStrings,"UPPERERROR","="));
    *lowwerError = StrToFloat(GetValue_ByName(aStrings,"LOWWERERROR","="));
  }
  catch( Exception& e)
  {
     gError->Warn( "MProeEngine::GetDimensionData出错！" + e.Message  );
  }
}

void MProeEngine::GetGTol(String Item,String *ID,double *baseValue)
{
   try
  {
    String aStr = fEngine.Exec(  PropertyGet("GetGemTolerence") << Item );
    TStrings* aStrings = splitToStrings(aStr,";");
    *ID      = GetValue_ByName(aStrings,"ID","=");
    *baseValue   = StrToFloat(GetValue_ByName(aStrings,"BASEVALUE","="));
  }
  catch( Exception& e)
  {
     gError->Warn( "MProeEngine::GetGTol出错！" + e.Message  );
  }
}

void MProeEngine::GetSurfaceFinish(String Item,String *ID,double *baseValue)
{
   try
  {
    String aStr = fEngine.Exec(  PropertyGet("GetSurfFinish") << Item  );
    TStrings* aStrings = splitToStrings(aStr,";");
    *ID      = GetValue_ByName(aStrings,"ID","=");
    *baseValue   = StrToFloat(GetValue_ByName(aStrings,"BASEVALUE","="));
  }
  catch( Exception& e)
  {
     gError->Warn( "MProeEngine::GetSurfaceFinish出错！" + e.Message  );
  }
}

TStrings* MProeEngine::ModelFeatIDs()
{
   TStrings* aStrings;
   try
  {
    String aStr = fEngine.Exec(  PropertyGet("GetModelFeatIDs") );
    aStrings = splitToStrings(aStr,";");
    return  aStrings;
  }
  catch( Exception& e)
  {
     gError->Warn( "MProeEngine::ModelFeatIDs出错！" + e.Message  );
     return aStrings;
  }
}

void MProeEngine::ModelStateSet(int featID )
{
   try
  {
    if( featID < 0 )
      return;
      
    fEngine.Exec(  Function("MdlStateSet") << featID  );
  }
  catch( Exception& e)
  {
     gError->Warn( "MProeEngine::ModelStateSet出错！" + e.Message  );
  }
}

String MProeEngine::RoughDataGet(String Item, String name)
{
   try
  {
    String aStr = fEngine.Exec(  PropertyGet("RoughDataGet") << Item << name );
    return aStr;
  }
  catch( Exception& e)
  {
     gError->Warn( "MProeEngine::RoughDataGet出错！" + e.Message  );
     return "";
  }
}

void MProeEngine::HighlightMdlFeats(TStrings *OldIDList, TStrings *NewIDList)
{
   try
  {
    String OldStr,NewStr;
    if(OldIDList==NULL)
      OldStr="";
    else
    {
       OldIDList->Delimiter = ';';
       OldStr = OldIDList->DelimitedText;
    }

    NewIDList->Delimiter = ';';
    NewStr = NewIDList->DelimitedText;
    OldStr = fEngine.Exec(  PropertyGet("HighlightFeatures") << OldStr << NewStr );
    OldIDList = splitToStrings( OldStr, ";");
  }
  catch( Exception& e)
  {
     gError->Warn( "MProeEngine::HighlightMdlFeats出错！" + e.Message  );
  }
}

bool MProeEngine::CreateMdlSnap(String FileName)
{
   try
  {
     bool result;
     result = fEngine.Exec(  PropertyGet("CreateSnap") << FileName );
     return result;
  }
  catch( Exception& e)
  {
     gError->Warn( "MProeEngine::CreateMdlSnap出错！" + e.Message  );
     return false;
  }
}

void MProeEngine::ModelSaveAs(String NewName)
{
   try
  {
     fEngine.Exec(  Function("ModelSaveAs") << NewName );
  }
  catch( Exception& e)
  {
     gError->Warn( "MProeEngine::ModelSaveAs出错！" + e.Message  );
  }
}

bool MProeEngine::MdlSaveByPath(String aModelPath,String aPath,String aNewName)
{
   try
  {
     bool result;
     result = fEngine.Exec(  PropertyGet("MdlSaveByPath") << aModelPath << aPath << aNewName );
     return result;
  }
  catch( Exception& e)
  {
     gError->Warn( "MProeEngine::MdlSaveByPath出错！" + e.Message  );
     return false;
  }
}

void MProeEngine::ModelEDFileSave(String path, String name)
{
   try
  {
     fEngine.Exec(  Function("MdlEdFileSave") << path << name );
  }
  catch( Exception& e)
  {
     gError->Warn( "MProeEngine::ModelEDFileSave出错！" + e.Message  );
  }
}

bool MProeEngine::MdlViewStore(String ModelName,String ViewName)
{
   try
  {
     bool result;
     result = fEngine.Exec(  PropertyGet("ViewStore") << ModelName << ViewName );
     return result;
  }
  catch( Exception& e)
  {
     gError->Warn( "MProeEngine::MdlViewStore出错！" + e.Message  );
     return false;
  }
}

String MProeEngine::GetViewMatrix( String aModelName,String aViewName )
{
  return  ViewRefit( aModelName,aViewName );
}

String MProeEngine::ViewRefit(String ModelName,String ViewName)
{
   try
  {
     String result;

     if( Trim(ViewName)=="" )
       return "";
       
     result = fEngine.Exec(  PropertyGet("ViewRefit") << ModelName << ViewName );
     return result;
  }
  catch( Exception& e)
  {
     gError->Warn( "MProeEngine::ViewRefit出错！" + e.Message  );
     return "";
  }
}

String MProeEngine::GetNcSegs( String aModelName )
{
   try
  {
     String result;
     result = fEngine.Exec(  PropertyGet("GetNCSteps") << aModelName );
     return result;
  }
  catch( Exception& e)
  {
     gError->Warn( "MProeEngine::GetNcSegs出错！" + e.Message  );
     return "";
  }
}

String MProeEngine::PlayNCById( String aModelName,int aId )
{
   try
  {
     String result;
     result = fEngine.Exec(  PropertyGet("PlayNCsegById") << aModelName<<aId );
     return result;
  }
  catch( Exception& e)
  {
     gError->Warn( "MProeEngine::PlayNCById出错！" + e.Message  );
     return "";
  }
}

String MProeEngine::PlayNCByName( String aModelName,String aName)
{
   try
  {
     String result;
     result = fEngine.Exec(  PropertyGet("PlayNCStepByName") << aModelName<<aName );
     return result;
  }
  catch( Exception& e)
  {
       gError->Warn( "MProeEngine::PlayNCByName出错！" + e.Message  );
     return "";
  }
}



//---------------臧霖--------------------------------------------------------
String MProeEngine::GetProcessPlanAllInfos(String aFileName)
{
   try
  {
     return fEngine.Exec(  PropertyGet("GetProcessPlanAllInfos") << aFileName );
  }
  catch( Exception& e)
  {
     gError->Warn( "MProeEngine::PlayNCStepById出错！" + e.Message  );
     return "";
  }
}

//修改PVS的输出控制选项，确保SimpRep能够被输出

bool MProeEngine::Miodfy_recipe()
{
   try
  {
     return fEngine.Exec(  PropertyGet("Miodfy_recipe"));
  }
  catch( Exception& e)
  {
     gError->Warn( "MProeEngine::PlayNCStepById出错！" + e.Message  );
     return "";
  }
}


String MProeEngine::SaveAsPvs( String dir_pvs )
{
   try
  {
     return fEngine.Exec(  PropertyGet("SaveAsPvs") << dir_pvs );
  }
  catch( Exception& e)
  {
     gError->Warn( "MProeEngine::PlayNCStepById出错！" + e.Message  );
     return "";
  }
}

//判断组件的单位----------臧霖---------------20130102
bool MProeEngine::BoolIsMmns(String aFileName)
{
   try
  {
     return fEngine.Exec(  PropertyGet("BoolIsMmns") << aFileName );
  }
  catch( Exception& e)
  {
     gError->Warn( "MProeEngine::PlayNCStepById出错！" + e.Message  );
     return "";
  }
}
//返回所有零件的单位的函数----------臧霖-----------20130513
String MProeEngine::ReadMdlUnit(String MdlFullName)
{
   try
  {
     return fEngine.Exec(  PropertyGet("ReadMdlUnit") << MdlFullName );
  }
  catch( Exception& e)
  {
     gError->Warn( "MProeEngine::PlayNCStepById出错！" + e.Message  );
     return "";
  }
}
//返回Plane类型的截面信息----------臧霖-----------20130628
String MProeEngine::Str_XsecMsg(String MdlFullName)
{
   try
  {
     return fEngine.Exec(  PropertyGet("Str_XsecMsg") << MdlFullName );
  }
  catch( Exception& e)
  {
     gError->Warn( "MProeEngine::PlayNCStepById出错！" + e.Message  );
     return "";
  }
}
//返回Plane类型的截面信息----------臧霖-----------20130628
bool MProeEngine::IsMdlAsm(String MdlFullName)
{
   try
  {
     return fEngine.Exec(  PropertyGet("IsMdlAsm") << MdlFullName );
  }
  catch( Exception& e)
  {
     gError->Warn( "MProeEngine::PlayNCStepById出错！" + e.Message  );
     return "";
  }
}
//将零件导入到组件里----------臧霖-----------20130702
bool MProeEngine::PrtToAsm(String PrtName, String aModelFullName)
{
   try
  {
     return fEngine.Exec(  PropertyGet("PrtToAsm") << PrtName << aModelFullName );
  }
  catch( Exception& e)
  {
     gError->Warn( "MProeEngine::PlayNCStepById出错！" + e.Message  );
     return "";
  }
}
//利用截面视图的名字存储简化视图----------臧霖-----------20130703
bool MProeEngine::SaveRepForXsection(String XsecNames)
{
   try
  {
     return fEngine.Exec(  PropertyGet("SaveRepForXsection") << XsecNames);
  }
  catch( Exception& e)
  {
     gError->Warn( "MProeEngine::PlayNCStepById出错！" + e.Message  );
     return "";
  }
}
//利用截面视图的名字删除简化视图----------臧霖-----------20130703
bool MProeEngine::DeleteRepForXsection(String XsecNames)
{
   try
  {
     return fEngine.Exec(  PropertyGet("DeleteRepForXsection") << XsecNames);
  }
  catch( Exception& e)
  {
     gError->Warn( "MProeEngine::PlayNCStepById出错！" + e.Message  );
     return "";
  }
}
//---------------------------------------------------------------------------
//------------------ Functions ----------------------------------------------

//-----------------------------MProeFrame---------------------------------------
//from邵老师20121226  臧霖整理
MPartFrame::MPartFrame()
{
  Matrix[0][0] = 1;
  Matrix[0][1] = 0;
  Matrix[0][2] = 0;
  Matrix[0][3] = 0;

  Matrix[1][0] = 0;
  Matrix[1][1] = 1;
  Matrix[1][2] = 0;
  Matrix[1][3] = 0;

  Matrix[2][0] = 0;
  Matrix[2][0] = 0;
  Matrix[2][2] = 1;
  Matrix[2][3] = 0;

  Matrix[3][0] = 0;
  Matrix[3][1] = 0;
  Matrix[3][2] = 0;
  Matrix[3][3] = 1;

}

MProFrame::MProFrame()
{
  PartFrames = new MPartFrames();
}

MProFrame::~MProFrame()
{
  delete PartFrames;
}

String MPartFrame::MatrixString()
{
  return PVSMatrixToStr( Matrix );
}

MProFrames::MProFrames()
{
  ModelFileName = "";
  FraFileName = "";
  PptName="";
  FraStrings = new TStringList;
}

//MProFrames::~MProFrames()
//{
//  delete  FraStrings;
//}

TStrings* MProFrames::FrameNameList()
{
  TStrings* aNames = new TStringList;

  for( int i=0; i<Count; i++ )                   
    aNames->Add( Items[i]->Name );
  return aNames;
}

String MProFrames::FrameNameList_Str()
{
  TStrings* aNames = FrameNameList();
  String aStr = aNames->Text;
  delete aNames;
  return aStr;
}

TStrings* MProFrame::PartNameList()
{
  TStrings* aNames = new TStringList;

  for( int i=0; i<PartFrames->Count; i++ )
    aNames->Add( PartFrames->Items[i]->Name );
  return aNames;
}

String MProFrame::PartNameList_Str()
{
  TStrings* aNames = PartNameList();
  String aStr = aNames->Text;
  delete aNames;
  return aStr;
}

TStrings* MPartFrame::MatrixList()
{
  TStrings* aStrings = new TStringList;
  for( int i=0; i<4; i++ )
  {
    String aStr = Matrix[0][i];
    for( int j=1; j<4; j++ )
    {
      aStr = aStr + " " + FloatToStr(Matrix[j][i]);
    }
    aStrings->Add( aStr );
  }
  return aStrings;
}

String MPartFrame::MatrixList_Str()
{
  TStrings* aStrings = MatrixList();
  String aStr = aStrings->Text;
  delete aStrings;
  return aStr;
}

//---------------------------------------------------------------------------
//功能：解析Proe输出的Fra文件
//输入: Fra文件，见例子文件
//输出：[ 文件名: ]

//?Model: F:\ZL\Pro_E\shuangchengzhuangpei\asm0004
//Number of parts: 5
//Number of frames: 91
//MaFrame 0
//Part: 1 (39)
//  1.000000000000e+000  0.000000000000e+000  0.000000000000e+000
//  0.000000000000e+000  1.000000000000e+000  0.000000000000e+000
//  0.000000000000e+000  0.000000000000e+000  1.000000000000e+000
//  1.500000000000e+002  1.500000000000e+002 -2.000000000000e+002
//Part: 1 (40)
//   ......

//MaFrame 1
//Part: 1 (39)
//  1.000000000000e+000  0.000000000000e+000  0.000000000000e+000
//  0.000000000000e+000  1.000000000000e+000  0.000000000000e+000
//  0.000000000000e+000  0.000000000000e+000  1.000000000000e+000
//  1.500000000000e+002  1.500000000000e+002 -2.000000000000e+002
//Part: 1 (40)
//  ......

//MaFrame 2

//---------------------------------------------------------------------------

void MProFrames::ReadFraFromFile( String aFileName )
{
  //by sxd 2014
  Clear();
  FraFileName = ExtractFileName_NoExt( aFileName );
  
  if( !FileExists( aFileName ) )
    throw Exception( "Fra文件(" + aFileName + ")不存在！" );

  FraStrings->LoadFromFile( aFileName );
  ReadFraFromStrings( FraStrings );
}

void MProFrames::ReadFraFromStrings( TStrings* aStrings )
{
  FraStrings->Text = aStrings->Text;
  //ModelFileName = Get_ListItemStr_ByName( aStrings, "Model", ":", "" );            //此处为什么之后后为NULL。。。Get_ListItemStr_ByName该函数什么意思，是不是因为打开文件的时候，第一个字母M没翻译出来，而且出现了乱码？？？？

  //IntTotalParts = (int)Get_ListItemFloat_ByName( aStrings, "Number of parts", ":", 0 );
  //IntTotalParts = ReadTotalPartNum( aStrings );
  //IntTotalFrames = Get_ListItemInt_ByName( aStrings, "Number of frames", ":", 0 );

  int aBgnPos = 0;

  for( ;; )
  {

    TStrings* aFrameString = Strings_GetSection( aStrings, 0,
                                                 "MaFrame",  "MaFrame",  aBgnPos, MAXINT, false );

    aBgnPos=G_SecEnd;
    if( aBgnPos<=0 )
      break;

    MProFrame* aFrame = new MProFrame;

    if( aFrameString->Count > 0 )
    {
      aFrame->Name = aFrameString->Strings[0];
      aFrameString->Delete( 0 );
    }
    else
      aFrame->Name = "default";

//    aFrame->FrameIsModelUnitMmns = FramesIsModelUnitMmns;      //传递组件单位信息   臧霖20120102
    aFrame->ReadFrame( aFrameString );
    Add( aFrame );
    delete aFrameString;
  }    
}

//功能：获取Fra文件中Part的数量

int MProFrames::TotalParts()
{
  if( Count<=0 )
    return 0;

  return Items[0]->PartFrames->Count;
}

int MProFrames::TotalFrames()
{
  return Count;
}

/*int MProFrames::ReadTotalPartNum( TStrings* aStrings )
{
  int aTotalPartNum = 0;

  for( int i = 0; i < aStrings->Count; i++)
  {

    String aStrFrame = aStrings->Strings[i];
    if( aStrFrame.Pos("MaFrame") <= 0  )
      continue;

    for( int j = i + 1; j < aStrings->Count; j++)
    {
      String aStrPart = aStrings->Strings[j];

      if( aStrPart.Pos("Part") )
        aTotalPartNum++;

      if( aStrPart.Pos("MaFrame") )
      {
        return aTotalPartNum;
        break;
      }
    }

  }

  if( aStrings->Count == 0 )
    ShowMessage("请选择要播放的动画");

  return aTotalPartNum;
} */


//------------------------------------------------------------------------------

void MProFrame::ReadFrame(TStrings* aStrings)
{

  //---

  int aBgnPos = 0;

  for(;;)
  {
    TStrings* aPartFrameString = Strings_GetSection( aStrings, 0,
                                                 "Part:",  "Part:",  aBgnPos, MAXINT, false );
    aBgnPos=G_SecEnd;
    
    if( aBgnPos<=0 )
      break;

    MPartFrame* aPartFrame = new MPartFrame;

//    aPartFrame->PartFrameIsModelUnitMmns = FrameIsModelUnitMmns;      //传递组件单位信息   臧霖20120102
    aPartFrame->ReadFrame( aPartFrameString );
    PartFrames->Add( aPartFrame );
    delete aPartFrameString;

  }
}

//------------------------------------------------------------------------------
//功能：将Part的 RelMatrix -> AbsMatrix
//说明：读取的PROE矩阵是按照Part相对与其父亲节点的位置给定的，但是在PVS中没有父子关系
//      所有必需将原来的相对Matrix变为绝对Matrix
//------------------------------------------------------------------------------


void MProFrames::RelMatrixToAbsMatrix()
{
    for( int i=0; i<Count; i++ )
    {
      MProFrame* aFrame =  Items[i];
      aFrame->RelMatrixToAbsMatrix();
    }
}

void MProFrame::RelMatrixToAbsMatrix()
{

  for( int i=0; i<PartFrames->Count; i++ )
  {

    MPartFrame* aPart = PartFrames->Items[i];

    String aPartName = aPart->Name;                   //aPartName
    int aNumOfB = NumOfBlank( aPartName );

    if( aNumOfB <= 1)    //少于一个零件
      continue;

    //--------多于一个零件---------------

    String aParentPartName = RemoveLastStr(aPartName);   //aParentPartName

    for( int j=0; j<PartFrames->Count; j++ )
    {
      MPartFrame* aParentPart = PartFrames->Items[j];

      //搜索Parent
      if( aParentPart->Name != aParentPartName )
        continue;

      //aParentPart和aPart矩阵相乘
      MulOfMatrixToLatter( aParentPart->Matrix, aPart->Matrix);
      //aPart->MatrixString = PVSMatrixToStr( aPart->Matrix );

      break;
    }
  }
}

int NumOfBlank( String StrIfPartHaveAsm )
{
  int aNumOfBlank = 0;
  String StrPartHaveAsm;
    StrPartHaveAsm = StrIfPartHaveAsm;
    
  while(StrPartHaveAsm.Pos("/"))
  {
    aNumOfBlank++;
    int PlaceOfBlank = StrPartHaveAsm.Pos("/");
    StrPartHaveAsm.Delete(PlaceOfBlank, 1);
  }
  
  return aNumOfBlank;
}

//---------------------------------------------------------------------------
String  RemoveLastStr(String StrIfPartHaveAsm)
{
  String StrNewName = "/";
  String StrPartHaveAsm;                        
    StrPartHaveAsm = StrIfPartHaveAsm;
    StrPartHaveAsm.Delete(1, 1);
  if(StrPartHaveAsm.Pos("/"))
  {
    while(StrPartHaveAsm.Pos("/"))
    {
      int PlaceOfBlank = StrPartHaveAsm.Pos("/");
        StrNewName = StrNewName + StrPartHaveAsm.SubString(0, PlaceOfBlank);
      StrPartHaveAsm.Delete(1, PlaceOfBlank);
    }
    
    StrNewName = StrNewName.SubString(1, StrNewName.Length() - 1);
    return StrNewName;
  }
  else
    return StrIfPartHaveAsm;
}

//---------------------------------------------------------------------------
void  MulOfMatrixToLatter(double m1[4][4], double m2[4][4])
{
  int i, j, k;
  double MidChange[4][4];
  for(i=0;i<4;i++)
  {
    for(j=0;j<4;j++)
    {
      MidChange[i][j] = 0.0;
      for(k=0;k<4;k++)
        MidChange[i][j] += m1[i][k] * m2[k][j];
    }
  }
  for(i=0;i<4;i++)
  {
    for(j=0;j<4;j++)
    {
      m2[i][j] = MidChange[i][j];
    }
  }
}

//------------------------------------------------------------------------------
//参数：
//Part: 1 (39)
//  1.000000000000e+000  0.000000000000e+000  0.000000000000e+000
//  0.000000000000e+000  1.000000000000e+000  0.000000000000e+000
//  0.000000000000e+000  0.000000000000e+000  1.000000000000e+000
//  1.500000000000e+002  1.500000000000e+002 -2.000000000000e+002
//Part: 1 (40)
//------------------------------------------------------------------------------

void MPartFrame::ReadFrame( TStrings* aStrings )
{
  if( aStrings->Count<1 )
    return;

  //  Name = aStrings->Strings[0];
  //将Name的形式改成网页可读的-------臧霖--------20130105
  PartName = aStrings->Strings[0];
  PartName = PartName.SubString(PartName.Pos("(")+1,PartName.Length() - PartName.Pos("(") -1);
  PartName = "/" + PartName;

  //将空格部分用"/"来代替-----------臧霖----------20120107
  while(PartName.Pos(" "))
  {
    int PlaceBlank = PartName.Pos(" ");
    PartName.Delete(PlaceBlank, 1);
    PartName.Insert("/", PlaceBlank);
  }
  Name = PartName;

  aStrings->Delete(0);

  int aCount = Math::Min( aStrings->Count, 4 );                       //Math::Min不知道什么意思啊，以下函数都不知道？？？？
  for( int i=0; i<aCount; i++ )
  {
    String aStr = Trim( aStrings->Strings[i] );                       //去掉前后空格
    TStrings* aItems = splitToStrings( aStr, " ", false );            //aItems一共5项，三个数加两个空格

    Strings_RomveNullStr( aItems );                                   //去掉aItems的空格，变成3项了
    for( int j=0; j<Math::Min( aItems->Count, 3 ); j++ )
      Matrix[j][i] = StrToFloatDef( aItems->Strings[j], Matrix[j][i] );

    delete aItems;
  }

  //修改矩阵成网页的矩阵---------臧霖---------20121231

  //  if(PartFrameIsModelUnitMmns == false)
  //     ChangeInksInToMmns(Matrix);
  //  ChangeAsmToPvs(Matrix);            //用这句则导出的是PVS的，如果不用则导出的是ASM的
  //  ChangeMmnsInToWeb(Matrix);
  //  ChangeMatrixLast(Matrix);

  //ChangeMatrixToString (Matrix);      //  先注销掉，因为要修改，用在后边再变成Str
}

//------------臧霖-------以ASM来播放模型----------20130409
/*
void MPartFrame::ChangeInksInToMmns(double Matrix[4][4])
{
  int ai, aj;
  for(ai = 0; ai < 3; ai++)
  {
    for(aj = 0; aj < 3; aj++)
    {
      Matrix[ai][aj] = Matrix[ai][aj] / 0.0254;
    }
  }
}
void MPartFrame::ChangeMmnsInToWeb(double Matrix[4][4])
{
  int ai, aj;
  for(ai = 0; ai < 3; ai++)
  {
    for(aj = 0; aj < 3; aj++)
    {
      Matrix[ai][aj] = Matrix[ai][aj] / 0.0254;
    }
  }
}
double MPartFrame::ChangeAsmToPvs(double MatrixNum)
{
//  int ai, aj;
//  for(ai = 0; ai < 3; ai++)
//  {
//    for(aj = 0; aj < 3; aj++)
//    {
//      Matrix[ai][aj] = Matrix[ai][aj] / 0.0254;
//    }
//  }
  MatrixNum = MatrixNum / 0.0254;
  return MatrixNum;
}

void MPartFrame::ChangeMatrixLast(double Matrix[4][4])
{
  Matrix[3][0] = 0;
  Matrix[3][1] = 0;
  Matrix[3][2] = 0;
  Matrix[3][3] = 1;
}
*/
/*
//------------臧霖------以前的矩阵转换
void MPartFrame::ChangeInksInToMmns(double Matrix[4][4])
{
  Matrix[3][0] = Matrix[3][0] ;
  Matrix[3][1] = Matrix[3][1] ;
  Matrix[3][2] = Matrix[3][2] ;
}

void MPartFrame::ChangeMmnsInToWeb(double Matrix[4][4])
{
  Matrix[3][0] = Matrix[3][0] ;
  Matrix[3][1] = Matrix[3][1] ;
  Matrix[3][2] = Matrix[3][2] ;
}
*/



//------------------------------------------------------------------------------
//邱博瑨----------20130109--------PpsSaveAsTxt------
//功能：将当前打开的PPS模型存储为PVS结构（存储到dir_pvs目录下），并生成存储其信息的TXT文件
//------------------------------------------------------------------------------

bool MProeEngine::PpsSaveAsTxt( String dir_pvs )
{
   try
  {
     return fEngine.Exec(  PropertyGet("PpsSaveAsTxt") << dir_pvs );
  }
  catch( Exception& e)
  {
     gError->Warn( "MProeEngine::PlayNCStepById出错！" + e.Message  );
     return "";
  }
}

//qbj20130726
String MProeEngine::GetAllExpMatrix(String dir_pvs)
{
   try
  {
     return fEngine.Exec(  PropertyGet("GetAllExpMatrix") << dir_pvs );
  }
  catch( Exception& e)
  {
     gError->Warn( "MProeEngine::GetAllExpMatrix出错！" + e.Message  );
     return "";
  }
}
//---------------------qbj201300711-------------------ExpStateStrGet------
String MProeEngine::ExpStateStrGet(String dir_pvs)
{
   try
  {
     return fEngine.Exec(  PropertyGet("ExpStateStrGet") << dir_pvs );
  }
  catch( Exception& e)
  {
     gError->Warn( "MProeEngine::ExpStateStrGet出错！" + e.Message  );
     return "";
  }
}
//---------------------------------------------------------------------------
//---------------------qbj201300801-------------------RepNameStrGet------
String MProeEngine::RepAllNameGet(String dir_pvs)
{
   try
  {
     return fEngine.Exec(  PropertyGet("RepAllNameGet") << dir_pvs );
  }
  catch( Exception& e)
  {
     gError->Warn( "MProeEngine::RepAllNameGet出错！" + e.Message  );
     return "";
  }
}
//---------------------------------------------------------------------------
//---------------------qbj201300802-------------------RepNameStrGet------
String MProeEngine::OrietationAllNameGet(String dir_pvs)
{
   try
  {
     return fEngine.Exec(  PropertyGet("OrietationAllNameGet") << dir_pvs );
  }
  catch( Exception& e)
  {
     gError->Warn( "MProeEngine::OrietationAllNameGet出错！" + e.Message  );
     return "";
  }
}

//---------------------------------------------------------------------------
bool MProeEngine::SetOrientatonToNewFile(String aViewName ,String DirPath,String viewMatrix,String WindowMatrix)
{
   try
  {
     return fEngine.Exec(  PropertyGet("SetOrientatonToNewFile")<< aViewName << DirPath<< viewMatrix<< WindowMatrix );
  }
  catch( Exception& e)
  {
     gError->Warn( "MProeEngine::SetOrientatonToNewFile出错！" + e.Message  );
     return "";
  }
}

//---------------------------------------------------------------------------
String  PVSMatrixToStr(double m[4][4])
{
  String Str;
  for(int tostringi = 0; tostringi < 4; tostringi++)
    for(int tostringj = 0; tostringj < 4; tostringj++)
      Str =  Str + " " + FloatToStr(m[tostringj][tostringi]);
  return Str;
}

//---------------------------------------------------------------------------
//------------------ Functions ----------------------------------------------



#pragma package(smart_init)
