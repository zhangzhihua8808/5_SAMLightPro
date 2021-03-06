//---------------------------------------------------------------------------


#pragma hdrstop

#include "UnitTool_Class.h"
#include "UnitTool_Single.h"
#include "COMMON_FUNC.hpp"
#include "UnitWordFun.h"
#include "UnitExcelFun.h"
#include "UnitMath.h"
#include "values.h"
//#include "UnitClass_InsertObject.h"
#include "UnitPviewFun.h"
#include "UnitFormInfo.h"
#include "3DP_Def.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

//-------------------全程变量---------------------------------------------------
MError* gError = new MError;
MProgress* G_Progress = new MProgress(NULL,NULL,NULL);
Variant gManual3DEngine;
TIniFile* gIniFile = new TIniFile(ApplicationPath()+"\\SysConfig.ini");

MActionList* gActionList = new MActionList(NULL);
TMemo * G_PromptLines = NULL;




//------------------------------MListToTreePosition-----------------------------

//------------------------------------------------------------------------------
//功能：
//参数：[ aType: "TAG" 或者 "NAME" ]
//------------------------------------------------------------------------------

MListToTreePosition::MListToTreePosition()
{
  fParentNodePos = -1;
  fVisited = false;
  fChildNodesPos = new TStringList;
}

//------------------------------MListToTreePositions----------------------------

void MListToTreePositions::SetVisited( bool aVisited )
{
  for ( int i=0; i<Count; i++ )
    Items[i]->Visited = aVisited;
}

//---------------------- MDoubleList -------------------------------------------
int MDoubleList::IndexMinimum( int aBgn, int aEnd )
{
  if( aBgn>aEnd )
    Swap( &aBgn, &aEnd );

  aBgn = Math::Max( 0, aBgn );
  aEnd = Math::Min( Count-1, aEnd );

  int aIndex = -1;
  double r = MAXFLOAT;

  for( int i=aBgn; i<=aEnd; i++ )
  {
    if( r > *Items[i] )
    {
      aIndex = i;
      r = *Items[i];
    }
  }

  return aIndex;
}

int MDoubleList::IndexMaximum( int aBgn, int aEnd )
{
  if( aBgn>aEnd )
    Swap( &aBgn, &aEnd );

  aBgn = Math::Max( 0, aBgn );
  aEnd = Math::Min( Count-1, aEnd );

  int aIndex = -1;
  double r = -MAXFLOAT;

  for( int i=aBgn; i<=aEnd; i++ )
  {
    if( r < *Items[i] )
    {
      aIndex = i;
      r = *Items[i];
    }
  }

  return aIndex;
}



//-------------------------------- MError --------------------------------------
MError::MError()
{
  WarnMessage = "";
  fIsLoading = false;
  fBreak = false;
  fMemo = NULL;
  OldMemo = NULL;
  fStatusBar=NULL;
  fDebug = false;
  fHeadTitle = "";
  fWarn1Message = "";
  fIsShow = true;
  fIsMaskShow = true;

  fStatusPanel = NULL;
}

//------------------------------------------------------------------------------
//功能：在执行某个费时较多的任务时，暂时关闭响应，以免误操作
//注意：(1)所在Form的KeyPreview属性设置为True
//      (2)所在Form的OnKeyDown事件加入   gError->ProcessLoading(Key,Shift);
//      (3)基本形式为：
//         gError->SetLoading( this, true, "....." );
//  for( int i=0; i<aTreeNodes->Count; i++ )
//  { .....
//       gError->Warn1( "(" + IntToStr(i) + "/" + IntToStr(Count)+"！)" );
//    }   //该循环必须做try...catch处理，以便下一句必须执行，否则界面就无法恢复
//  gError->SetLoading( this, false, "" );
//------------------------------------------------------------------------------
void MError::SetLoading( TForm* aForm, bool aIsLoading, String aHeadTitle )
{
  HeadTitle = aHeadTitle;
  SetAllSubCtrlEnable( aForm, !aIsLoading );
  fIsLoading = aIsLoading;
}

void MError::ProcessLoading(WORD &Key, TShiftState Shift)
{
  //ESC，询问是否退出
  if( fIsLoading == false )
    return;

  if( Key == 27 )
  {
    if( MessageDlg("退出当前操作，是否确定？",
          mtInformation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes  )
      Break = true;
  }
}

void MError::ProcessLoading(TWMKey &Msg)
{
  //ESC，询问是否退出
  if( fIsLoading == false )
    return;

  if( Msg.Msg == 48384 )
  {
    if( MessageDlg("退出当前操作，是否确定？",
          mtInformation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes  )
      Break = true;
  }
}

String MError::DefaultStr(String aStr)
{
    if( fHeadTitle!="" && fIsLoading == true )
       return fHeadTitle + "[ESC退出]！"  + aStr;
    else if( fHeadTitle!="" && fIsLoading == false )
      return fHeadTitle + "！"  + aStr;
    else
      return aStr;
}

void MError::writeHeadTitle( String aHeadTitle )
{
  fHeadTitle = aHeadTitle;
  fWarn1Message = "";
}

void MError::Warn1(String aStr)
{
  if( Break == true )
  {
    Break = false;
    throw Exception( "用户中断" );
  }

  if( fIsShow == false )
    return;

  if( fStatusBar==NULL )
  {
    if( Debug )
      ShowMessage( aStr );
  }
  else
  {
    fStatusBar->SimpleText = DefaultStr(aStr);
    fWarn1Message = fStatusBar->SimpleText;
    Application->ProcessMessages();
  }
}

void MError::WarnAdd1(String aStr)
{
  if( Break == true )
  {
    Break = false;
    throw Exception( "用户中断" );
  }

  if( fStatusBar==NULL )
  {
    if(fStatusPanel != NULL)
    {
        //if(fWarn1Message=="")
        //    fWarn1Message = DefaultStr("");
        //fStatusPanel->Text = fWarn1Message+aStr;
        fStatusPanel->Text = aStr;
        Application->ProcessMessages();
    }
    else
    {
      if( Debug )
      ShowMessage( aStr );
    }
  }
  else
  {
    if(fWarn1Message=="")
      fWarn1Message = DefaultStr("");
    fStatusBar->SimpleText = fWarn1Message+aStr;
    Application->ProcessMessages();
  }
}

void MError::Warn1_Percent( String aStr, int i, int aCount, int aSp )
{
  if( aSp!=0 && i % aSp != 0 )
    return;

  gError->Warn1( MergeStr( aStr, "("+IntToStr(i) + "/" +
                                IntToStr(aCount) + ")" , "!" ) );
}


void MError::WarnAdd1_Percent( String aStr, int i, int aCount, int aSp )
{
  if( aSp!=0 && i % aSp != 0 )
    return;

  gError->WarnAdd1( MergeStr( aStr, "("+IntToStr(i) + "/" +
                                IntToStr(aCount) + ")" , "!" ) );
}

void  MError::writeMemo(TMemo* aMemo )
{
  fMemo = aMemo;
  mErrMemo = aMemo;
}

void  MError::writeStatusBar( TStatusBar* aStatusBar )
{
  fStatusBar = aStatusBar;
}

void MError::SetMemo( TMemo* aMemo )
{
  OldMemo = Memo;
  Memo = aMemo;
}

void MError::RestMemo()
{
  fMemo = OldMemo;
}

void MError::Error(String aStr)
{
  //if( fMemo==NULL )
    throw Exception( aStr );
  //else
  //  fMemo->Lines->Add(aStr);
}

void MError::Prompt(String aStr)
{
  if( fMemo!=NULL ) //&& Debug==true )
    fMemo->Lines->Add(aStr);
}

void MError::PromptLine(String aStr)
{
  if( fMemo==NULL ) //|| Debug==false )
    return;

  TStrings* aLines = fMemo->Lines;

  if( aLines->Count > 0 )
    aLines->Strings[ aLines->Count-1 ] = aStr;
  else
    aLines->Add(aStr);
}

void MError::Warn(String aStr,bool IsShowError)
{
  if( IsShowError==false )
    return;
  Warn(aStr);
}

void MError::WarnAlways(String aStr)
{
  bool aIsMaskShow = fIsMaskShow;

  fIsMaskShow = true;
  Warn(aStr);
  fIsMaskShow = aIsMaskShow;
}

void MError::Warn(String aStr)
{
  if( aStr == "用户取消" )
    return;

  WarnMessage = aStr;
  
  if( fIsMaskShow==true && ( fMemo==NULL || IsControlVisible(fMemo)==false ) )
  {
    //if( Debug )
      ShowMessage( aStr );
  }
  else
  {
    if( fMemo!=NULL && fMemo->Lines!=NULL )
      fMemo->Lines->Add(aStr);
    Application->ProcessMessages();
  }
}

void MError::WarnAdd(String aStr)
{
  WarnMessage = aStr;
  if( fMemo==NULL )
  {
    if( Debug )
      ShowMessage( aStr );
  }
  else
  {
    if( fMemo->Lines->Count>0 )
      fMemo->Lines->Strings[fMemo->Lines->Count-1] =
           fMemo->Lines->Strings[fMemo->Lines->Count-1] + " " + aStr;
    else
      fMemo->Lines->Add(aStr);
    Application->ProcessMessages();
  }
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//名称：MProgress
//历史：2009.6.17, by sxd
//------------------------------------------------------------------------------

MProgress :: MProgress( TProgressBar *aPrgBar1, TProgressBar *aPrgBar2, TControl* aMsgBar )
{
   msgBar = aMsgBar;
   prgBar1 = aPrgBar1;
   prgBar2 = aPrgBar2;
   title1 = "";
   title2 = "";
   msg1 = "";
   msg2 = "";
}

void MProgress::Prompt( String aPrompt )
{
  SetControlCption( msgBar,  aPrompt );
  Application->ProcessMessages() ;
}

void MProgress::BgnShow1( const AnsiString& aTitle, const int& aMin, const int& aMax )
{
  try
  {
    title1 = aTitle + Format( "共(%d)个",ARRAYOFCONST((aMax-aMin)) );
    if( aMax > aMin )
    {
      prgBar1->Min = aMin;
      prgBar1->Max = aMax;
    }
  }
  catch(...)
  {
  }
}

void MProgress :: BgnShow2( const AnsiString& aTitle, const int& aMin, const int& aMax )
{
 try
 {
    title2 = aTitle + Format( "共(%d)个",ARRAYOFCONST((aMax-aMin)) );
    if( aMax > aMin )
    {
      prgBar2->Min = aMin;
      prgBar2->Max = aMax;
    }
  }
  catch(...)
  {
  }
}

void MProgress :: BgnShow3( const AnsiString& aTitle, const int& aMin, const int& aMax )
{
  try
  {
    title3 = aTitle + Format( "共(%d)个",ARRAYOFCONST((aMax-aMin)) );
    if( aMax > aMin )
    {
      prgBar2->Min = aMin;
      prgBar2->Max = aMax;
    }
  }
  catch(...)
  {
  }
}

void MProgress :: Show1( const AnsiString& aMsg, const int& aPos )
{
  try
  {
    msg1 = aMsg;
    //msgBar->SimpleText = title1+"!!"+msg1;
    SetControlCption( msgBar,  title1+"!!"+msg1+"第("+IntToStr(aPos)+")个" );
    //msgBar->Caption = title1+"!!"+msg1;
    prgBar1->Position = aPos;
    Application->ProcessMessages() ;
  }
  catch(...)
  {
  }
}

void MProgress :: Show2( const AnsiString& aMsg, const int& aPos )
{
  try
  {
    msg2 = aMsg;

    //msgBar->SimpleText = title1+"!!"+msg1+"!!"+title2+"!!"+msg2+"第("+IntToStr(aPos)+")个";
    //msgBar->Caption = title1+"!!"+msg1+"!!"+title2+"!!"+msg2+"第("+IntToStr(aPos)+")个";
    SetControlCption( msgBar,  title1+"!!"+msg1+"!!"+title2+"!!"+msg2+"第("+IntToStr(aPos)+")个" );

    Application->ProcessMessages() ;
    prgBar2->Position = aPos;
    Application->ProcessMessages() ;
  }
  catch(...)
  {
  }
}

void MProgress :: Show3( const AnsiString& aMsg, const int& aPos )
{
  try
  {
    msg3 = aMsg;

    //msgBar->SimpleText = title1+"!!"+msg1+"!!"+title2+"!!"+msg2+"!!"+title3+"!!"+msg3+"第("+IntToStr(aPos)+")个";
    //msgBar->Caption = title1+"!!"+msg1+"!!"+title2+"!!"+msg2+"!!"+title3+"!!"+msg3+"第("+IntToStr(aPos)+")个";
    SetControlCption( msgBar,  title1+"!!"+msg1+"!!"+title2+"!!"+msg2+"!!"+title3+"!!"+msg3+"第("+IntToStr(aPos)+")个" );

    Application->ProcessMessages() ;
    prgBar2->Position = aPos;
    Application->ProcessMessages() ;
  }
  catch(...)
  {
  }
}

void MProgress :: EndShow1()
{
  try
  {
    //  msgBar->SimpleText = title1+"结束!!";
    //msgBar->Caption = title1+"结束!!";
    SetControlCption( msgBar, title1+"结束!! )" );

    prgBar1->Position = prgBar1->Min ;
    Application->ProcessMessages() ;
  }
  catch(...)
  {
  }
}

void MProgress :: EndShow2()
{
  try
  {
    //msgBar->SimpleText = title1+"!!"+msg1+"!!"+title2+"结束!!";
    prgBar2->Position = prgBar2->Min;
    Application->ProcessMessages() ;
  }
  catch(...)
  {
  }
}

void MProgress :: EndShow3()
{
  try
  {
    //msgBar->SimpleText = title1+"!!"+msg1+"!!"+title2+"!!"+msg2+"!!"+title3+"结束!!";
    prgBar2->Position = prgBar2->Min;
    Application->ProcessMessages() ;
  }
  catch(...)
  {
  }
}


//-----------------------------------------------------------------------
//名称：MObject::ObjectControls()
//-----------------------------------------------------------------------
/*
MObjectControls* MObject::ObjectControls()
{
  return gObjectsControls->Find(this->Type);
}
*/

MObject::MObject()
{
  fName = "";
  fType = "";
  fEditStatus = "New";
  //fGroup = NULL;
}

String MObject::readClassType()
{
  return "MObject";
}

String MObject::readName()
{
  return fName;
}

void  MObject::writeName(String aName )
{
  fName = aName;
}


//--------------------------MObjectList-----------------------------------------
__fastcall MObjectList::~MObjectList()
{
}

//------------------------------------------------------------------------------
MObject* MObjectList::Find(String aName,bool IsUppercase)  //????
{
  return  MList_Temp<MObject>::Find(aName,IsUppercase);
}

MObject*  MObjectList::Find_E(String aName,bool IsUppercase)
{
  return  MList_Temp<MObject>::Find_E(aName,IsUppercase);
}
MObject* MObjectList::Find_E(MObject* aEntity)
{
  return MList_Temp<MObject>::Find_E(aEntity);
}

void MObjectList::ResetVisited( bool isOn )
{
  for( int i=0; i<Count; i++ )
    Items[i]->Visited = isOn;
}

void MObjectList::SaveVisited()
{
  for( int i=0; i<Count; i++ )
    Items[i]->OldVisited = Items[i]->Visited;
}

void MObjectList::RestoreVisited()
{
  for( int i=0; i<Count; i++ )
    Items[i]->Visited = Items[i]->OldVisited;
}

int MObjectList::TheFirstUnVisited()
{
  for( int i=0; i<Count; i++ )
    if( Items[i]->Visited == false )
      return i;
  return -1;
}




//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//MActionControl
//------------------------------------------------------------------------------
MActionControl::MActionControl( TControl* aControl )
{
   fControl = aControl;
   Name = fControl->Name;
}

void MActionControls::AddControl( TControl* aControl )
{
  Add( new MActionControl(aControl) );
}


//------------------------------------------------------------------------------
//名称：MActionList
//说明：界面的状态管理
//------------------------------------------------------------------------------
MActionList::MActionList(TActionList* aActionList)
{
  fActionStatuses=new MActionStatuses;
  fActionExcuteStatus=new MActionAttrs(this);
  fWinControls=new MActionControls;

  fActionList=aActionList;
  fStatus=NULL;
}

MActionList::~MActionList()
{
  SafeDelete(&fActionStatuses);
  SafeDelete(&fActionExcuteStatus);
  SafeDelete(&fWinControls);
}

void MActionList::SetStatus(String aStatusName)
{
  if( aStatusName == "" )       //无需更改状态的操作
    return;

  MActionStatus* aStatus = fActionStatuses->Find(aStatusName);
  if( aStatus==NULL )
     gError->Warn("没有名称为("+aStatusName+")的状态！");
  Status = aStatus;
}

void MActionList::SetEnableActions()
{
  if( fStatus == NULL || ActionList==NULL )
    return;

  for( int i=0; i<ActionList->ActionCount; i++ )
  {
    TAction* aNowAction = (TAction*)ActionList->Actions[i];
    //if( aNowAction->Tag==1 )
    //  continue;

    int aIndex = fStatus->EnableActionNames->IndexOf( aNowAction->Name );
    if( aIndex >= 0 ) //&& !(aIndex>ActionList->ActionCount) )
    {
      aNowAction->Enabled = true;
      aNowAction->Tag = 1;
    }
  }
}

void MActionList::SetReserveActions()
{
  if( fStatus == NULL || ActionList==NULL )
    return;

  for( int i=0; i<ActionList->ActionCount; i++ )
  {
    TAction* aNowAction = (TAction*)ActionList->Actions[i];

    if( aNowAction->Tag==1 )
      continue;

    int aIndex = fStatus->ReserveActionNames->IndexOf( aNowAction->Name );
    if( aIndex >= 0 ) //&& !(aIndex>ActionList->ActionCount) )
    {    
      aNowAction->Tag = 1;
    }
  }
}

void MActionList::SetDisableActions()
{
  if( ActionList==NULL )
    return;
     
  for( int i=0; i<ActionList->ActionCount; i++ )
  {
    TAction* aNowAction = (TAction*)ActionList->Actions[i];
    if( aNowAction->Tag==1 )
      continue;

    aNowAction->Enabled = false;
    aNowAction->Tag = 1;
  }
}

void MActionList::SetVisibleControls()
{
  for( int i=0; i<WinControls->Count; i++ )
  {
    MActionControl* aNowControl = WinControls->Items[i];
    if( aNowControl->Visited == true )
      continue;

    int aIndex = fStatus->VisibleControlsNames->IndexOf( aNowControl->Name );
    if( aIndex >= 0  )
    {
      aNowControl->Visited = true;
      if( aNowControl->Control->Visible == false )
        aNowControl->Control->Visible = true;
    }

  }
}

void MActionList::SetUnVisibleControls()
{
  for( int i=0; i<WinControls->Count; i++ )
  {
    MActionControl* aNowControl = WinControls->Items[i];
    if( aNowControl->Visited == true  )
      continue;
    aNowControl->Visited = true;

    if( aNowControl->Control->Visible == true )
      aNowControl->Control->Visible = false;
  }
}

void MActionList::writeStatus( MActionStatus* aStatus )
{
  fStatus = aStatus;
  if( ActionList==NULL )
    return;

  for( int i=0; i<ActionList->ActionCount; i++ )           //设置遍历标识
    ActionList->Actions[i]->Tag = 0;

  SetEnableActions();
  SetReserveActions();
  SetDisableActions();

  for( int i=0; i<WinControls->Count; i++ )           //设置遍历标识
    WinControls->Items[i]->Visited = false;
  SetVisibleControls();
  SetUnVisibleControls();
}

//---------------------------------------------
//读入*.Action文件
//---------------------------------------------
void MActionList::LoadFromFile(String aFileName)
{
  TStringList* aList = new TStringList;

  try
  {
    aList->LoadFromFile(aFileName);
  }
  catch( Exception& e )
  {
    gError->Warn( "MActionList::LoadFromFile出错！"+e.Message );
  }
  LoadFormStrings(aList);
  delete aList;
}

void MActionList::LoadFormStrings(TStrings* aStrings)
{
  TStrings* aNewStrings = Strings_ClingLines(aStrings,"\\",true);
  //Strings_Trim(aNewStrings);
  fActionStatuses->LoadFromStrings(aNewStrings);
  fActionExcuteStatus->LoadFromStrings(aNewStrings);
}

TAction* MActionList::FindActionByName(String aName)
{
  if( ActionList==NULL )
    return NULL;
  for( int i=0; i<ActionList->ActionCount; i++ )
    if( aName == ActionList->Actions[i]->Name )
      return (TAction*)ActionList->Actions[i] ;
  return NULL;
}


//------------------------------------------------------------------------------
//MActionStatuses
//------------------------------------------------------------------------------
void MActionStatuses::LoadFromStrings(TStrings* aStrings)
{
  for( int i=0; i<aStrings->Count; i++ )
  {
    String aName, aValue;
    SplitStrTo2Str( aStrings->Strings[i], ",", aName, aValue );

    if( aName.UpperCase() != "ACTIONSTATUS" )
      continue;
    MActionStatus* aActionStatus = new MActionStatus(this);
    aActionStatus->LoadFromStr(aValue);
    Add (aActionStatus);
  }
  GetLinkStatus();               //"@Init的处理"
}

//------------------------------------------------------------------------------
//处理@init的语义
//------------------------------------------------------------------------------
void MActionStatuses::GetLinkStatus()
{
  for( int i=0; i<Count; i++ )
  {
    Items[i]->GetLinkStatus();
  }
}


//------------------------------------------------------------------------------
//MActionStatus
//------------------------------------------------------------------------------
void MActionStatus::LoadFromStr(String aStr)
{
  TStringList* aListGroup = splitToStrings(aStr,",");
  Name = Get_ListItemStr_ByName( aListGroup, "NAME", "=", "" );

  String sp[4];
  sp[0]="(";
  sp[1]=")";
  sp[2]=";";
  fEnableActionNames = splitToStrings( Get_ListItemStr_ByName( aListGroup, "ENABLES", "=", "" ),sp,3,false);
  fReserveActionNames = splitToStrings( Get_ListItemStr_ByName( aListGroup, "RESERVES", "=", "" ) ,sp,3,false);
  fVisibleControlsNames = splitToStrings( Get_ListItemStr_ByName( aListGroup, "VISCONTROLS", "=", "" ) ,sp,3,false);
}

MActionStatus::MActionStatus(MActionStatuses* aGroup)
{
   fEnableActionNames=NULL;
   fReserveActionNames=NULL;
   fVisibleControlsNames=NULL;
   fGroup=aGroup;
}

MActionStatus::~MActionStatus()
{
  SafeDelete(&fEnableActionNames);
  SafeDelete(&fReserveActionNames);
  SafeDelete(&fVisibleControlsNames);
}

//---------------------------------------------------------
//名称：void MActionStatus::GetLinkStatus_Item()
//功能：处理@init的语义
//说明：aStr--被处理的语义；　IsWhat -- fEnableActionNames || fReserveActionNames
//      如果没有引用，返回false,否则返回true
//---------------------------------------------------------
void MActionStatus::MergeLinkStatus_Item(TStrings* aList1, TStrings* aList2, String aStr)
{
  if( aList1==NULL || aList2==NULL )
    return;
    
  Strings_Union( aList1, aList2, true );
  for(;;)
  {
    int aIndex = aList1->IndexOf(aStr);
    if( aIndex < 0 )
      break;
    aList1->Delete(aIndex);
  }
}

bool MActionStatus::GetLinkStatus_Item(String aStr, String IsWhat)
{
    if( !IsPreFix( aStr, "@" ) )
      return false;

    String aNewStr = aStr.SubString( 2, aStr.Length()-1 );
    MActionStatus* aStatus = fGroup->Find(aNewStr);
    if( aStatus==NULL )
      return false;

    if( IsWhat == "Enables"  )
      MergeLinkStatus_Item( fEnableActionNames, aStatus->fEnableActionNames, aStr );
    else if ( IsWhat == "Reserves" )
      MergeLinkStatus_Item( fReserveActionNames, aStatus->fReserveActionNames, aStr );
    else if( IsWhat == "VisControls" )
      MergeLinkStatus_Item( fVisibleControlsNames, aStatus->fVisibleControlsNames, aStr );
    else
      return false;

    return true;
}

//---------------------------------------------------------
 //名称：void MActionStatus::GetLinkStatus()
 //功能：处理@init的语义
//---------------------------------------------------------
void MActionStatus::GetLinkStatus(String IsWhat)
{
  if( fGroup==NULL )
    return;

  TStrings* aStrings=NULL;
  if( IsWhat == "Enables" )
    aStrings = fEnableActionNames;
  else if ( IsWhat == "Reserves" )
    aStrings = fReserveActionNames;
  else if( IsWhat == "VisControls" )
    aStrings = fVisibleControlsNames;
  else
    throw Exception("MActionStatus::GetLinkStatus出错！没有("+IsWhat+")类型！");

  for( ;; )
  {
    bool aIsLink = false;
    for( int i=0; i<aStrings->Count; i++ )
    {
      aIsLink =GetLinkStatus_Item( aStrings->Strings[i], IsWhat );
      if( aIsLink==true )           //修改了Link项，重新进行
        break;
    }
    if ( aIsLink!=true )       //没有修改Link项，结束处理
      break;
  }

  //if( aStrings!=NULL );
  //  delete aStrings;

}

void MActionStatus::GetLinkStatus()
{
   GetLinkStatus( "Enables" );
   GetLinkStatus( "Reserves" );
   GetLinkStatus( "VisControls" );
}


//------------------------------------------------------------------------------
//MActionStatus
//------------------------------------------------------------------------------
MActionAttr::MActionAttr(TAction* aAction, MActionAttrs* aGroup)
{
  fAction = aAction;
  fGroup = aGroup;
  if( fAction!= NULL )
  {
    fOldDoOnExcute = fAction->OnExecute;
    fOldDoOnHint = fAction->OnHint;
    fAction->OnExecute = DoAfterActionClick;
  }
  fStatusAfterClick="";
}

MActionAttr::~MActionAttr()
{
}

void MActionAttr::LoadFromStr(String aStr)
{
  TStringList* aListGroup = splitToStrings(aStr,",");
  Name = Get_ListItemStr_ByName( aListGroup, "NAME", "=", "" );
  StatusAfterClick = Get_ListItemStr_ByName( aListGroup, "STATUS", "=", "" );
}

void __fastcall MActionAttr::DoAfterActionClick(TObject *Sender)
{
   try
   {
     if( fOldDoOnExcute != NULL )
       fOldDoOnExcute(Sender);
   }
   catch( Exception& e )
   {
     gError->Warn( e.Message );
     return;
   }  

   if( fGroup != NULL && fGroup->ActionList != NULL )
     fGroup->ActionList->SetStatus( fStatusAfterClick );

   if( fOldDoOnHint != NULL )
     fOldDoOnHint;                         //sxd 2008.6.2
}

//------------------------------------------------------------------------------
//MActionAttrs
//------------------------------------------------------------------------------
MActionAttrs::MActionAttrs( MActionList* aActionList )
{
  fActionList = aActionList;
}

void MActionAttrs::LoadFromStrings(TStrings* aStrings)
{
  if( fActionList==NULL || aStrings==NULL)
    return;

  for( int i=0; i<aStrings->Count; i++ )
  {
    String aName, aValue;
    SplitStrTo2Str( aStrings->Strings[i], ",", aName, aValue );

    if( aName.UpperCase() != "ACTION" )
      continue;

    TStringList* aListGroup = splitToStrings(aValue,",");
    aName = Get_ListItemStr_ByName( aListGroup, "NAME", "=", "" );

    TAction* aAction = fActionList->FindActionByName( aName );
    if( aAction==NULL )
      continue;

    MActionAttr* aActionAttr = new MActionAttr(aAction,this);
    aActionAttr->StatusAfterClick = Get_ListItemStr_ByName( aListGroup, "STATUS", "=", "" );
    Add (aActionAttr);
  }
}



