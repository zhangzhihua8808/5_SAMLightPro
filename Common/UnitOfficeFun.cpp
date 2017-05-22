//---------------------------------------------------------------------------
#pragma hdrstop

#include "UnitOfficeFun.h"
#include "COMMON_FUNC.hpp"


//------------------------------------------------------------------------------
MOleObj::MOleObj(float aL,float aT,float aW,float aH,String aC,String aName ,int aRelDelta,String aPropertys,int aLink)
{
    mLeft = aL;
    mTop = aT;
    mWidth = aW;
    mHeight = aH;
    mClassName= aC;
    mName = aName;
    mLink = aLink;
    mPropertyStrs = aPropertys;
    mRelDelta = aRelDelta;

}
String MOleObj::PosSizeStr(String aSplit)
{
  return FloatToStr(mLeft+mRelDelta)+aSplit+ FloatToStr(mTop+mRelDelta)+aSplit+ FloatToStr(mWidth)+aSplit+ FloatToStr(mHeight)+aSplit;
}

MOfficeFun::MOfficeFun()
{
  fVBS = new TStringList;
  IsVisible = false;
  //IsDebug = false;
  IsDebug = true;
}

MOfficeFun::~MOfficeFun()
{
   if( fVBS )
	delete fVBS;
}

void MOfficeFun::InitVBS( bool IsOnlyRun )
{
   if( fVBS == NULL )
     return;

   fVBS->Clear();

   if( IsOnlyRun )
     AddVBS(" sub main ");
   else
     AddVBS(" function main ");

   if( IsDebug==false )    
     AddVBS(" on error resume next ");
}

void MOfficeFun::EndVBS( bool IsOnlyRun )
{
   if( fVBS == NULL )
     return;

   if( IsOnlyRun )
   {
     AddVBS(" end sub  " );
     RunVBScript( fVBS );
   }
   else
     AddVBS(" end function  " );
}

void MOfficeFun::AddVBS( String aVbs )
{
   if( aVbs!="")
     fVBS->Add(aVbs);
}

bool MOfficeFun::ConfirmOpenFile( String aFullFileName )
{
  if( aFullFileName == "")
    return false;

  //InitVBS();
  //AddVBS(" if TypeName( MyWord ) =\"Application\" then ");
  //AddVBS("   For Each aWordDoc In MyWord.Documents ");
  //AddVBS("    if aWordDoc.FullName = \""+aFullFileName +"\" then ");
  //AddVBS("     aWordDoc.Activate ");
  //AddVBS("     exit sub ");
  //AddVBS("    end if ");
  //AddVBS("   next ");
  //AddVBS("end if ");
  //AddVBS("MyWord.Documents.Open(\""+aFullFileName+"\")");
  //AddVBS(" MyWord.Visible = true ");
  //EndVBS( );

  //SW_HIDE
  //SW_SHOWNORMAL

  if (FileExists(aFullFileName))
  {
      ShellExecute( NULL,"open",aFullFileName.c_str(),"","",SW_SHOWNORMAL);
      return true;
  }
  return false;
}


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
/*void MapBMToTV( TStrings * aBMInfo,TTreeView * aTV )
{
   if( aBMInfo == NULL || aTV == NULL ) return;
   for (int i = aBMInfo->Count-1; i >=0 ; i--) {
	 //TTreeNode * aNode = aTV->Items[i];
	 String aName = aBMInfo->Names[i];
	 String aPortName = G_WORD->GetPortNameByBmName(aName);
	// TTreeNode * aNode = Get_NameNode_InTreeNodes( aTV->Items,aPortName);
	int ap = 0;
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
} */

TTreeNode *  GetNodeChild( TTreeNode *aPNode ,String aChildName )
{
    if( aPNode == NULL || aChildName=="")
        return NULL;

    for (int i = 0; i < aPNode->Count; i++)
    {
      if( aPNode->Item[i]->Text == aChildName )
         return aPNode->Item[i];
    }

    return NULL;
}
MBookMark::MBookMark()
{
    fStartPos = -1;
    fEndPos = -1;
    fPortName ="";
}



Variant GetObjProperty( Variant aObj ,String PropStr)
{
  if( VarIsNull(aObj) || PropStr =="")
          return Null;

  TStrings * aTmp = new TStringList();
  Variant tmpObj = aObj;
  try
  {
   aTmp->Delimiter = '.';
   aTmp->DelimitedText = PropStr;
   for (int i = 0; i<aTmp->Count ;i++)
   {
     tmpObj = tmpObj.Exec( PropertyGet(aTmp->Strings[i]));
   }
   delete aTmp;
   return tmpObj;
  }
  catch(Exception & aE)
  {
    delete aTmp;
    throw Exception(aE.Message+ "无法获取对象正确"+PropStr+"属性！");
  }
}


#pragma package(smart_init)
