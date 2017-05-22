//---------------------------------------------------------------------------


#pragma hdrstop

#include "UnitTool_Single.h"
#include "UnitTool_Class.h"
#include "COMMON_FUNC.hpp"
#include "UnitWordFun.h"
#include "UnitDirectory.h"
#include "UnitTool_ClassExtend.h"


//---------------------------------------------------------------------------
#pragma package(smart_init)

int G_SecBgn = -1;
int G_SecEnd = -1;

const float kPi = 3.14159265f;
const float k2Pi = kPi * 2.0f;
const float kPiOver2 = kPi / 2.0f;
const float k1OverPi = 1.0f / kPi;
const float k1Over2Pi = 1.0f / k2Pi;
const float kPiOver180 = kPi / 180.0f;
const float k180OverPi = 180.0f / kPi;


//------------------------MBinaryFileRW-----------------------------------------
//�������ļ���д��
//�ȱ����ַ����ĳ��ȣ�long�ֽ�
//Ȼ�󱣴��ַ���
long   save_string(ofstream& aFile,String aStr)
{
   long length = aStr.Length();
   save_long(aFile,length);                   //�ַ�������
   aFile.write(aStr.c_str(),length);          //�ַ�������

   return 1;
}

String load_string(ifstream& aFile)   //long size
{
   String str;

   long length = load_long(aFile);

   if(length>0)
   {
     str.SetLength(length);
     aFile.read(str.c_str(),length);
   }

   return str;
}

long  save_long(ofstream& aFile,long l)
{
   aFile.write((char*)&l,sizeof(long));

   return 1;
}

long  load_long(ifstream& aFile)
{
   long l = 0;
   aFile.read((char*)&l,sizeof(long));

   return l;
}

//------------------------------------------------------------------------------
String  GetSaveProjectDir()
{
     String  aDir = ApplicationPath() + "\\����Ŀ¼";
     CheckAndMakeDirectory(aDir);

     return aDir;
}

//aParentTreeNode : ѡ��Ľڵ�
//aNodeName : �ڵ������
//fOwner: ָ����;
/*
MDataModuleTreeNode*  InsertTreeNode_DataModule(MManualProjectDoc* aOwner,MDataModuleTreeNode* aParentTreeNode,String aNodeName)
{

    if(aOwner == NULL && aOwner->FrameDM == NULL)  throw Exception("aOwner == NULL in InsertTreeNode_DataModule");

    MTreeNodes_DataModule*  aMainItems = aOwner->MainItems;

    //����һ��ID
    int aMaxID = StrToInt(aMainItems->MaxID);
    aMainItems->MaxID = aMaxID + 1;

    MDataModuleTreeNode*  aItem = aMainItems->NewDataModule_AT(aMaxID,aNodeName,"","","");

    //�ҵ���
    TTreeView*  aTree = aOwner->FrameDM->TreeView_Word;
    if(aParentTreeNode == NULL)  //���ڵ�
    {
        TTreeNode* aNewNode = aTree->Items->Add(NULL,aItem->NodeName);
        aNewNode->Data = (void*)aItem;
        aNewNode->ImageIndex = 0;
        aNewNode->SelectedIndex = 0;
        aItem->ImageIndex = 0;
        aItem->TreeNode = aNewNode;
    }
    else  //����ӽڵ�
    {
        TTreeNode* aNewNode = aTree->Items->AddChild(aParentTreeNode->TreeNode,aItem->NodeName);
        aNewNode->Data = (void*)aItem;
        aItem->TreeNode = aNewNode;

        if( aParentTreeNode->TreeNode->Parent!=NULL &&  aParentTreeNode->TreeNode->Parent->Data!=NULL )
        {
         MDataModuleTreeNode* aData =
               (MDataModuleTreeNode*)aParentTreeNode->TreeNode->Parent->Data;
         aItem->ParentName = aData->DataModuleID;
        }
    }

    aTree->FullExpand(); //չ��

    return aItem;

    return NULL;
}
*/
//------------------ Message ---------------------------------------------------

void ThrowMessageOnTop( String aMsg )
{
  ThrowMessage( aMsg );
}

void ShowMessageOnTop( String aMessage )
{
   ShowMessage( aMessage );
}

void ThrowMessage( String aMessage )
{
  throw Exception( aMessage );
}


void AddPromptLine( String aText )
{
  if( G_PromptLines!=NULL )
  {
    G_PromptLines->Lines->Add( aText );
    Application->ProcessMessages();
  }
}


//------------------------------------------------------------------------------


void CopyStrings ( TStrings* aDest, TStrings* aSrc, int aBgn, int aEnd )
{
  aDest->Clear();
  int aCount = Math::Min(aEnd,aSrc->Count-1);
  for( int i=aBgn; i<=aCount; i++ )
    aDest->Add(aSrc->Strings[i]);
}

//------------------------------------------------------------------------------
//���ܣ�Strings_ClingLines
//���ܣ������е��ַ����ϲ�
//------------------------------------------------------------------------------

void Strings_ClingLines1(TStrings* aOldStrings,String Suffix,bool IsTrim)  //���з�����
{
  TStrings* aStrings = Strings_ClingLines( aOldStrings, Suffix, IsTrim );
  CopyStrings( aOldStrings, aStrings, false );
  delete aStrings;
}

TStrings* Strings_ClingLines(TStrings* aOldStrings,String Suffix,bool IsTrim)
{
  TStrings* aNewList = new TStringList;

  String aStr = "" ;
  for( int i=0; i<aOldStrings->Count; i++ )
  {

     String aOldStr = aOldStrings->Strings[i];
     if( IsTrim==true )
       aOldStr = aOldStr.Trim();
     if( IsSuffix( aOldStr, Suffix ) && i<aOldStrings->Count-1 )
       aStr = aStr + aOldStr.SubString(1,aOldStr.Length()-Suffix.Length());
     else
     {
       aStr = aStr + aOldStr;
       aNewList->Add( aStr );
       aStr = "";
     }
  }
  return  aNewList;
}

/*
MMapElement_ExcelImporter* GetMapParas(String aProjectPath)
{
     //Ĭ�ϣ��ӹ���Ŀ¼����
     String  aParaFile = aProjectPath + "\\�����ļ�.xls";
     if(!FileExists(aParaFile))
     {
         throw Exception(aParaFile + " ������,�����ļ����ʽ�Ƿ���ȷ");
     }

     MMapElement_ExcelImporter*  aImporter = new MMapElement_ExcelImporter();
     aImporter->ImportToListView(aParaFile,NULL,NULL,NULL);   //����

     return aImporter;
}
*/




void Strings_Utf8ToAnsi( TStrings* aList )
{
  for( int i=0; i<aList->Count; i++ )
    aList->Strings[i] = Utf8ToAnsi( aList->Strings[i] );
}

TTreeNode* FindTreeViewNodeByData( TTreeView* aTree, void* aData )
{
  TList* aNodes = GetTreeNodes( aTree );
  for( int i=0; i<aNodes->Count; i++ )
  {
    TTreeNode* aNode = (TTreeNode*) aNodes->Items[i];
    if( aNode->Data == aData )
    {
      aNodes->Clear();
      delete aNodes;
      return aNode;
    }
  }

  aNodes->Clear();
  delete aNodes;
  return NULL;
}

//------------------------------------------------------------------------------
//��ȡ���е�����б�
/*
void GetNames_ExportRvToWord(TRVOfficeConverter* aRvc,TStrings* aStrings)
{
  aStrings->Clear();
  if(aRvc == NULL)
    return;

  aRvc->GetExportFilter();
  for(int i=0; i < aRvc->ExportConverters->Count; i++)
      aStrings->Add( ((TRVOfficeConverterInfo*)aRvc->ExportConverters->Items[i])->Name );
}
void GetNames_ImportRvFromWord(TRVOfficeConverter* aRvc,TStrings* aStrings)
{
  aStrings->Clear();
  if(aRvc == NULL)
    return;

  aRvc->GetImportFilter();
  for(int i=0; i < aRvc->ImportConverters->Count; i++)
      aStrings->Add( ((TRVOfficeConverterInfo*)aRvc->ImportConverters->Items[i])->Name );
}

//---------------------------------------------------------------------------
void  SetUnicodeType(TRichViewEdit* aRichViewEdit,TRVStyle *aRVStyle)
{
   aRichViewEdit->RTFReadProperties->UnicodeMode = rvruOnlyUnicode;

     //��ȫ��֧��UNicode
     for(int i=0; i < aRVStyle->TextStyles->Count; i++)
     {
          TFontInfo*  aFontInfo = aRVStyle->TextStyles->Items[i];
          aFontInfo->FontName = "����";
          aFontInfo->Size = 12;
          aFontInfo->Unicode = true;
     }
     aRichViewEdit->Style = aRVStyle;
}

//��word����rvc
void WordToRvc( String aBookMark, TRVOfficeConverter* aRvc1, TRichViewEdit* aRVEdit )
{
  TRVOfficeConverter* aRvc = (TRVOfficeConverter*)aRvc1;

  if( aRvc==NULL || aBookMark=="" || aRVEdit==NULL )
    return;

  String  aFileName = TempPath() + "\\" + aBookMark + ".doc";
  DeleteFile(aFileName);
  G_Word->CopyBMToNewFile( aBookMark, aFileName );
  ImportRvFromWord( aRvc, aFileName, aRVEdit );
}

//д��word
void RvcToWord( String aBookMark, void* aRvc1, TRichViewEdit* aRVEdit)
{
  TRVOfficeConverter* aRvc = (TRVOfficeConverter*)aRvc1;

  if( aRvc==NULL || aBookMark=="" || aRVEdit==NULL )
    return;

  String  aFileName = TempPath() + "\\" + aBookMark + ".doc";
  ExportRvToWord( aRvc, aFileName, aRVEdit );
  G_Word->UpdateFile_BM(  aBookMark, aFileName );
}

//����Doc�ļ�
void ExportRvToWord( void* aRvc, String aFileName,  TRichViewEdit* aRVEdit )
{
  if( aRvc == NULL )
    return;

  TRVOfficeConverter* aRvc1 = (TRVOfficeConverter*)aRvc;

  if( aRvc1->ExportRV( aFileName, aRVEdit, FilterIndex_ExportRvToWord(aRvc1) ) == false )
    throw Exception( "ExportRV����" + IntToStr(aRvc1->ErrorCode)  );
}

int FilterIndex_ExportRvToWord(TRVOfficeConverter* aRvc)
{
  TStrings* aStrings = new TStringList;

  String aFileName = ApplicationPath() + "\\RVC���ת����.txt";
  if( FileExists( aFileName ) == true )
    aStrings->LoadFromFile( aFileName );

  //�п���û�е����
  aStrings->Add( "Word97" );
  aStrings->Add( "WWord 97-2003 �ĵ�" );
  aStrings->Add( "Word 97-2002 & 6.0/95 - RTF" );

  int aIndex = FilterIndex_ExportRvToWord( aRvc, aStrings );
  delete aStrings;
  return aIndex;
}

//�жϣ��ļ������һ���Ƿ���֮ƥ��,�ļ�������Ч��ֻ��һ��;
int FilterIndex_ExportRvToWord(TRVOfficeConverter* aRvc, TStrings* aTypes)
{
  for( int i=0; i<aTypes->Count; i++ )
  {
    int aIndex = FilterIndex_ExportRvToWord( aRvc, aTypes->Strings[i] );
    if( aIndex >= 0 )
      return aIndex;
  }
  gError->Warn( "û���ҵ�ExportRvToWord����������");
  return 0;
}

//���ܣ����RV�������
int FilterIndex_ExportRvToWord(TRVOfficeConverter* aRvc,String aType)
{
    if(aRvc == NULL)
       return -1;

    aRvc->GetExportFilter();
    for(int i=0; i <aRvc->ExportConverters->Count; i++)
    {
        String  aName = ((TRVOfficeConverterInfo*)aRvc->ExportConverters->Items[i])->Name;
        if( UpperCase(aName) == UpperCase(aType) )
        {
            //gError->Warn( "ExportRvToWord!" + aName + "(" + IntToStr( i ) + ")" );
            return i;
        }
    }
    return -1;
}


//����: ���RV��������
int FilterIndex_ImportRvFromWord(TRVOfficeConverter* aRvc)
{
  TStrings* aStrings = new TStringList;

  String aFileName = ApplicationPath() + "\\RVC����ת����.txt";
  if( FileExists( aFileName ) == true )
    aStrings->LoadFromFile( aFileName );

  aStrings->Add( "Word97" );
  aStrings->Add( "Word 97-2003 �ĵ�" );
  aStrings->Add( "Word 97-2002 & 6.0/95 - RTF" );
  aStrings->Add( "Word 97-2002" );

  int aIndex = FilterIndex_ImportRvFromWord( aRvc, aStrings );
  delete aStrings;
  return aIndex;
}

//����Doc�ļ�
void ImportRvFromWord( void* aRvc, String aFileName,  TRichViewEdit* aRVEdit )
{
  if( aRvc == NULL )
    return;
  TRVOfficeConverter* aRvc1 = (TRVOfficeConverter*)aRvc;
  aRVEdit->Clear();

  if( aRvc1->ImportRV( aFileName, aRVEdit, FilterIndex_ImportRvFromWord(aRvc1) ) == false )
    throw Exception( "ImportRV����" + IntToStr(aRvc1->ErrorCode)  );
  aRVEdit->Format();
}

int FilterIndex_ImportRvFromWord(TRVOfficeConverter* aRvc, TStrings* aTypes)
{
  for( int i=0; i<aTypes->Count; i++ )
  {
    int aIndex = FilterIndex_ImportRvFromWord( aRvc, aTypes->Strings[i] );
    if( aIndex >= 0 )
      return aIndex;
  }
  gError->Warn( "û���ҵ�ImportRvFromWord����������");
  return 0;
}

int FilterIndex_ImportRvFromWord(TRVOfficeConverter* aRvc,String aType)
{
    if(aRvc == NULL)
       return -1;

    aRvc->GetImportFilter();
    for(int i=0; i < aRvc->ImportConverters->Count; i++)
    {
        String  aName = ((TRVOfficeConverterInfo*)aRvc->ImportConverters->Items[i])->Name;
        if( UpperCase(aName) == UpperCase(aType) )
        {
            //gError->Warn( "ImportRvFromWord!" + aName + "(" + IntToStr( i ) + ")" );
            return i;
        }
    }
    return -1;
}

*/

void  SaveParaMapInfoToWord(String  aStr)
{
    if(aStr == "")  return;

    TStrings*  aParaFile = new TStringList;

    aParaFile->Delimiter = '@';
    aParaFile->DelimitedText  = G_Word->GetVarVal_NoExp("ParaMapItems",false);   //��--��--д
    aParaFile->Add(aStr);
    G_Word->AddVar("ParaMapItems",aParaFile->DelimitedText);

    delete aParaFile;
}

//2014
void DelStringsItemByObject(  TStrings* aStrings, void* aObject  )
{
  if( aStrings==NULL )
    return;

  DelStringsItem( aStrings, aStrings->IndexOfObject( (TObject*) aObject ) );
}


//------------------------------------------------------------------------------
String ExtractFileName_NoDot( String aFileName )
{
  String aStr1, aStr2;
  SplitStrTo2Str( ExtractFileName( aFileName ), ".", aStr1, aStr2 );
  return aStr1;
}

String FormatDir( String aPath )
{
  if( IsSuffix( aPath, "\\" ) )
    aPath = aPath.SubString( 1, aPath.Length()-1 );
  return aPath;
}

//���治��б��
String ExtractFilePath_Format( String aFileName )
{
  return FormatDir( ExtractFilePath( aFileName ) );
}

String ProjectDirName(String  aProjectFileName)
{
    if(aProjectFileName != "")
         return ExtractFileDir( aProjectFileName );

    return "";
}

bool DelDirFiles( String dir  )       //�÷����Ϻ�
{
  if( dir == "" )
    return false;

  if( IsRootDir( dir ) == true )
    throw Exception( "Ŀ¼(" +dir+ ")Ϊ��Ŀ¼�����ܽ���Ŀ¼��ȫɾ������!" );

  if(FileExists(dir))
  {
    DeleteFile(dir);
    return true;
  }

  TSearchRec Tp;
  AnsiString a_path;

  a_path = dir + "\\*.*";
  if(FindFirst(a_path,faAnyFile,Tp) != 0)
    return false;

  while(1<2)
  {
   if( Tp.Name != ".."  && Tp.Name != ".")
   {
     AnsiString file_name = MaskMergePathAndFileName(dir,Tp.Name);
     //AnsiString file_name = dir + "\\" + Tp.Name;
     if(FileExists(file_name))
       DeleteFile(file_name);
     else
       DelADir(file_name);
   }

   if(FindNext(Tp) != 0)
     break;
  }

  FindClose(Tp);
  return ::RemoveDirectory(dir.c_str());
}

bool IsRootDir( String aDir )
{
  if( ParentDir( aDir ) == "" )
    return true;
  else
    return false;  
}

String MaskMergePathAndFileName( String aPathName, String aFileName )
{
   if( IsSuffix( aPathName, "\\" ) )
     return aPathName + aFileName;
   else
     return aPathName + "\\" + aFileName;
}

bool DelADir(AnsiString dir)        //��ʱ���ļ�����
{
   return DelDirFiles(dir);
}

//---------------------------------------------------------------------------
//Function : ɾ��һ���ļ���,�����������е��ļ��м��ļ�
//---------------------------------------------------------------------------
String ParentDir( String aPath )
{
  return FormatDir(ExtractFilePath(aPath));
}



//------------------------------------------------------------------------------
void DelStringsItem( TStrings* aStrings, int aIndex )
{
  if( aStrings==NULL || aIndex <0 || aIndex > aStrings->Count-1 )
    return ;
  aStrings->Delete(aIndex);
}

void SetOnlyPageControlVis( TPageControl* aPage, String aName, bool aVis, bool IsManual)
{
    TTabSheet* aSheet = FindPageByName(aPage,aName);
    SetOnlyPageControlVis( aPage, aSheet, aVis, IsManual  );
}

void SetOnlyPageControlVis( TTabSheet* aSheet, bool aVis, bool IsManual)
{
  SetOnlyPageControlVis( aSheet->PageControl, aSheet, aVis, IsManual );
}

void SetOnlyPageControlVis( TPageControl* aPage, TTabSheet* aSheet, bool aVis, bool IsManual)
{
  if( aSheet==NULL )
    return;

  try
  {
     aSheet->TabVisible = aVis;
  }
  catch(Exception& e)
  {
     aSheet->TabVisible = aVis;
  }
  //for( int i=0; i<aPage->PageCount; i++ )
  //{
  //  if( aPage->Pages[i] != aSheet )
  //    aPage->Pages[i]->TabVisible = !aVis;
  //}
  SetPageVisble( aPage, aVis, OPENARRAY( TTabSheet*, (aSheet) ),IsManual );
}

String   TStringsToString(TStrings*  aStrings,String  aSplitChar)
{
    String  aSum = "";

    if(aStrings == NULL || aStrings->Count == 0)
        return aSum;

    for(int i=0; i < aStrings->Count; i++)
    {
        String  aStr = aStrings->Strings[i];

        aSum += aStr;
        aSum += aSplitChar;     //��עΪ�յ����
    }

    return aSum;
}

MDMSourceItem*    GetSelectedDMSourceItem( TListBox* aList )
{
   return (MDMSourceItem*) GetListBoxSelectedNodeData( aList );
}

/*
void  UpdatePictureGroup(String aBmName,MDMSourceItems*  aDMItems)
{
   if( G_Word->HasBM(aBmName) == false  || aDMItems== NULL || aDMItems->Count <= 0)
       return;
   try
   {
      int aSP=-1,aEP=-1;
      G_Word->GetBMRange( aBmName,aSP,aEP);
      G_Word->SelRange(aSP,aSP);

      for(int i=0; i < aDMItems->Count; i++)
      {
        try
        {
          MDMSourceItem*  aItem = aDMItems->Items[i];
          UpdatePictureGroup(aItem);
        }
        catch( Exception& e )
        {
          gError->Warn( "����ģ�Ͷ�����ͼ��"+e.Message );
        }
      }
      G_Word->NewLine();
      //InsertStrings_ByBMName(aBmName,aMemo);
      int aPos = G_Word->GetCurPos();
      G_Word->SelRange(aPos,aPos+aEP-aSP);
      G_Word->DelSel();
   }
   catch(Exception &aE)
   {
     throw Exception("UpDateStrins_ByBMName!"+aE.Message);
   }
}
*/

/*
void UpdatePictureGroup(MDMSourceItem*  aItem)
{
    if(aItem == NULL)  return;

    if(IsCanLoad(aItem->FileName))
    {
        G_Word->InsertPic(aItem->FileName);
    }

    G_Word->InsertPicTitle(aItem->ImageTitle,"ͼ");

    G_Word->ClearFormat();
    G_Word->InsertText_ByBMName("",MemoVarPostProcess(aItem->ImageRemark));
}
*/

bool  IsCanLoad(String aPicFileName)
{
    TImage*  aImage = new TImage(NULL);
    bool  bRet = true;

    try
    {
       aImage->Picture->LoadFromFile(aPicFileName);
    }
    catch(Exception& e)
    {
       bRet = false;
    }

    aImage->Picture = NULL;
    delete aImage;
    return bRet;
}

//-----------���棺Pages------------------------------------------
TTabSheet * FindPageByName(TPageControl* aPage, String aTabName)
{
  if( aPage==NULL )
    return NULL;

  for( int i=0; i<aPage->PageCount; i++ )
  {
    if (aTabName== aPage->Pages[i]->Caption)
     return aPage->Pages[i];
  }
  return  NULL;
}

void SetPageVisble( TPageControl* aPage, bool aVis,
                    TTabSheet **aSheet_array, const int aSheet_array_Size,
                    bool IsManual    )
{
   if( aPage==NULL )
     return;

   for( int i=0; i<=aSheet_array_Size; i++ )
   {
      if(  aSheet_array[i]->TabVisible != aVis )
        aSheet_array[i]->TabVisible = aVis;
   }

   if( !IsManual )
     return;

   for( int i=0; i<aPage->PageCount; i++ )        //ȡ������
   {
     try
     {
       int j;
       for( j=0; j<=aSheet_array_Size; j++ )
       {
         if( aPage->Pages[i] == aSheet_array[j] )
              break;
       }
       if( j > aSheet_array_Size )
       {
         if( aPage->Pages[i] != NULL )
         if ( aPage->Pages[i]->TabVisible == aVis )
             aPage->Pages[i]->TabVisible = !aVis;
       }
     }
     catch(Exception& e)
     {
     }
  }
}


MTreeNode_ModeObject* GetSelectedModeNodeObject( TListView* aList )
{
   return (MTreeNode_ModeObject*) GetListViewSelectedNodeData( aList );
}

MLaserPen*  GetSelectedLaserPen( TListView* aList )
{
   return (MLaserPen*)GetListViewSelectedNodeData( aList );
}

MLaserPen*  GetSelectedLaserPen(TComboBox* aComBox)
{
   return (MLaserPen*)GetComboBoxSelectedLayerData( aComBox );
}


void SetPageControlVis( TPageControl* aPage, bool aVis )
{
  if( aPage==NULL )
    return;

  for( int i=0; i<aPage->PageCount; i++ )
  {
    try
    {
      aPage->Pages[i]->TabVisible = aVis;
    }
    catch( Exception& e )
    {
    }
  }
}

int StringsControl_SetItem(TControl* aControl, String aStr)
{
  if( aControl==NULL )
    return -1;
  String aType=aControl->ClassName();

  if( aType=="TComboBox" )
  {
    TComboBox* aCombo = (TComboBox*)aControl;

    int aIndex = aCombo->Items->IndexOf( aStr );
    StringsControl_SetItemIndex(aControl,aIndex);
    return aIndex;
  }
  else if ( aType=="TListBox" )
  {
    TListBox* aList = (TListBox*)aControl;

    int aIndex = aList->Items->IndexOf( aStr );
    StringsControl_SetItemIndex(aControl,aIndex);
    return aIndex;
  }
  else
  {
    ShowMessage("δע���StringsControl");
    return -1;
  }
}



//------------------����--------------------------------------------------------

//˵������Action��Ϣ����ʱ�������"�û�ȡ��"����Ҫ�����쳣���Ա��жϹ���
//      ����ֻ����ʾ��Ϣ����
void MaskProcessException( Exception& e, String aAddStr )
{
  String aErrorStr = e.Message;
  if( aErrorStr=="" )
    return;

  //String aStr = aErrorStr;

  //if( aAddStr!="" )
  //  aStr = aAddStr + "!" + aErrorStr;

  if( aErrorStr == "�û��ж�" )                                                 //�û���ESC�˳�
  {
    gError->Warn1( "�û��ж�" );
    throw Exception( aErrorStr );
  }
  else
    gError->Warn( aAddStr + "!" + aErrorStr );
}

//˵�����ڽӹ��쳣������˳�����󣬶��쳣��һ���Ĵ���

void MaskThrowException( String aErrorStr, String aAddStr, bool IsInAction )
{
  if( aErrorStr=="" ||
      ( IsInAction==false && aErrorStr == "�û�ȡ��" ) )
    return;

  String aStr = aErrorStr;
  if( aAddStr!="" )
    aStr = aAddStr + "!" + aErrorStr;
  throw Exception( aStr );
}

void CheckNULLStr( String aStr, String aWarn )
{
  if( aStr=="" )
    throw Exception( aWarn );
}

MTreeNode_ModeObject*  GetSelectedModeNode( TListBox* aList )
{
   return (MTreeNode_ModeObject*) GetListBoxSelectedNodeData( aList );
}

MPartProject*  GetSelectedPartProject( TListBox* aList )
{
   return (MPartProject*) GetListBoxSelectedNodeData( aList );
}

void DebugFile_New( String aFileName )
{
  TStrings* aStrings = new TStringList;
  aStrings->SaveToFile(aFileName);
  delete aStrings;
}

void DebugFile_Add( String aFileName, String aStr )
{
  TStrings* aStrings = new TStringList;
  try
  {
    aStrings->LoadFromFile( aFileName );
  }
  catch( Exception& e )
  {
  }
  aStrings->Add( TimeToStr(Now()) + "----" + aStr );
  aStrings->SaveToFile(aFileName);
  delete aStrings;
}


MTreeNode_ModeObject* GetSelectedModeNode(TTreeView* aTree )
{
   return (MTreeNode_ModeObject*) GetTreeViewSelectedNodeData( aTree );
}

MLayerDataTreeNode* GetSelectedLayerDataItem( TTreeView* aTree )
{
   return (MLayerDataTreeNode*) GetTreeViewSelectedNodeData( aTree );
}

void* GetTreeViewSelectedNodeData( TTreeView* aTree )
{
  if( aTree==NULL || aTree->Selected == NULL )
    return NULL;
  return aTree->Selected->Data;
}


MParaMapElementItem*  GetSelectedMapElement( TListView* aList )
{
   return (MParaMapElementItem*) GetListViewSelectedNodeData( aList );
}

String  MemoVarPostProcess(String aMemoVar,String aDiv)
{
    TStrings* aReadStrings = splitToStrings_Mask(aMemoVar,aDiv);
    String aRet = aReadStrings->Text;

    delete aReadStrings;

    return aRet;
}

void SetImagePictureNULL(TImage* aImage)
{
  if( aImage==NULL )
    return;
  aImage->Picture = NULL;
  aImage->Visible = false;
}

String AskFileName( String aTitle, String aDefDir, String aFilter, String aDefaultExt )
{
  TOpenDialog* aDialog = new TOpenDialog(NULL);

  aDialog->Title = aTitle ;
  aDialog->InitialDir = aDefDir; //ExpandFileName(C_PROJ_PATH,ApplicationPath()) ;

  aDialog->DefaultExt = aDefaultExt;
  aDialog->Filter = aFilter;

  String aFileName="";
  if( aDialog->Execute() )
     aFileName = aDialog->FileName;
  delete aDialog;
  return aFileName;
}

//------------------ StringsStr ------------------------------------------------

//���ӣ�Get_ListItem_ByName_StringsStr( "A=2\r\nB=3\r\n", "B", "=", "" ) -> ����"3"

String Get_ListItem_ByName_StringsStr( String aStringsStr, String aItemName, String aSplitter, String aDefault, bool aIsTrim )
{
  TStrings* aStrings = new TStringList;
  aStrings->Text = aStringsStr;
  String aStr = Get_ListItemStr_ByName( aStrings, aItemName, aSplitter, aDefault, aIsTrim );
  delete aStrings;
  return aStr;
}

//���ӣ�Get_ListItem_ByName_Str( "A=2;B=3", ";", "B", "=", "" ) -> ����"3"

String Get_ListItem_ByName_Str( String aStringsStr, String aDivItem, String aItemName, String aSplitter, String aDefault, bool aIsTrim )
{
  TStrings* aStrings = splitToStrings( aStringsStr, aDivItem );
  String aStr = Get_ListItemStr_ByName( aStrings, aItemName, aSplitter, aDefault, aIsTrim );
  delete aStrings;
  return aStr;
}

//------------------------------------------------------
//���ܣ��� aRootStrΪ���ڵ㣬�������ṹ
//˵������aListParName=aRootStrΪ��һ��ڵ㣬˳��ȡ�������еĺ��ӽڵ�
//------------------------------------------------------

void ListToTree( TStrings* aListName, TStrings* aListParName,
                 TTreeView* aTree, String aRootStr, bool IncludeRoot, bool aIsClear )
{
  TStrings* aListShowName = new TStringList;
  ListToTree( aListName, aListParName, aListShowName,aTree, aRootStr, IncludeRoot, aIsClear );
  delete aListShowName;
}

void ListToTree( TStrings* aListName, TStrings* aListParName, TStrings* aListShowName,
                 TTreeView* aTree, String aRootStr, bool IncludeRoot, bool aIsClear )
{
   ListToTree_Basic( NULL, aListName, aListParName, aListShowName, aTree, aRootStr,
                     0, IncludeRoot, "NAME", aIsClear );
}

TList* GetTreeNodes( TTreeView* aTree )
{
  TList* aNodes = new TList;
  if( aTree==NULL || aTree->Items==NULL )
    return aNodes;
  for( int i=0; i<aTree->Items->Count; i++ )
    aNodes->Add( aTree->Items->Item[i] );
  return aNodes;
}

TTreeNode* TreeNode_AddChild( TTreeNode* aNode, String aName )
{
  if( aNode==NULL || aNode->TreeView==NULL )
    return NULL;
  TTreeView* aTree = (TTreeView*)aNode->TreeView;
  return aTree->Items->AddChild( aNode, aName );
}

bool GetNodeChecked( TTreeNode *ANode )
{
  TVITEM tvItem;
  tvItem.mask = TVIF_HANDLE | TVIF_STATE;
  tvItem.hItem = ANode->ItemId;
  tvItem.stateMask = TVIS_STATEIMAGEMASK;
  TreeView_GetItem( ANode->TreeView->Handle, &tvItem );
  return ((BOOL)(tvItem.state >> 12) -1);
}

//���ܣ����aNode�����������ӽڵ�
//������[ IsSearchNext: true--ͬʱ�����ھӽڵ㣬��GetTreeNodes�ã� false -- һ��������� ]

TList* GetTreeNodeNodes( TTreeNode* aNode, bool IsSearchNext )
{

  TList* aNodes = new TList;
  if( aNode==NULL )
    return aNodes;

  //��ȡ�ڵ�Ϊ���ڵ�Ĵ�������  
  if( aNode->Parent == NULL && aNode->TreeView!=NULL )
  {
    TTreeView* aTreeView = (TTreeView*) aNode->TreeView;
    for( int i=0; i<aTreeView->Items->Count; i++ )
      aNodes->Add( aTreeView->Items->Item[i] );
    return aNodes;
  }

  //_GetTreeNodes( aNode, aNodes );


  //2014,�����ھӽڵ������
  int i=0;
  for( ;; )
  {
    if( aNode==NULL )
      break;

    _GetTreeNodes( aNode, aNodes, i );
    if( IsSearchNext==false )
      break;
    aNode = aNode->getNextSibling();
  }

  return aNodes;
}

void _GetTreeNodes( TTreeNode* aNode, TList* aNodes, int& aCurCount )
{
  if( aNode == NULL )
    return;             
  if( aCurCount>0 )
    List_MaskAdd( aNodes, aNode );
  aCurCount=aCurCount+1;
  for( int i=0; i<aNode->Count;i++ )
     _GetTreeNodes( aNode->Item[i], aNodes, aCurCount );
}

void List_MaskAdd( TList* aList, void* aItem )
{
  if( aList==NULL )
    return;
  if( aList->IndexOf( aItem ) >= 0 )
    return;
  aList->Add( aItem );
}

String Strings_GetMaxName( String aCsLab, TStrings* aCsNames )
{
  String aMaxId = IntToStr( Strings_GetMaxId(aCsNames,aCsLab) );
  return aCsLab+aMaxId;
}

//���ܣ���ȡaNames��ǰ׺ΪaPrefix�������
//���磺Strings_GetMaxId( "A1;A7;A10;B5;A2", "A" ), ����11
int Strings_GetMaxId( TStrings* aNames, String aPrefix )
{
  if( aNames==NULL )
    return 0;

  int aMaxId = 0;
  aPrefix = Trim( UpperCase(aPrefix) );
  for (int i=0 ; i<aNames->Count; i++ )
  {
    String aTmp;
    if ( UpperCase( aNames->Strings[i]).Pos(aPrefix) != 1 )
      continue;

    aTmp = CopyStr( aNames->Strings[i],aPrefix.Length()+1,aNames->Strings[i].Length() );
    try
    {
      if(  StrToInt( aTmp ) > aMaxId )
        aMaxId = StrToInt( aTmp );
    }
    catch(...)
    {
      continue;
    }
  }

  return aMaxId+1;
}

//------------------------------------------------------------------------------
//���ܣ��滻�ַ�����Ŀ��ֵ
//���磺Str_UpdateNamedItem( "A=1;B=2;C=3;D=4", "B=5;E=6", ";", "=" )  -> ���� "A=1;B=5;C=3;D=4;E=5"
//------------------------------------------------------------------------------
String String_UpdateNamedItem( String aOldStr, String aNewItems,
                                     String aSpItems, String aSpNameAndValue )
{
  TStrings* aStringsOld =  splitToStrings( aOldStr, aSpItems, false );
  TStrings* aStringsItems =  splitToStrings( aNewItems, aSpItems, false );

  for( int i=0; i<aStringsItems->Count; i++ )
  {
    String aStr = aStringsItems->Strings[i];
    String aName, aValue;
    SplitStrTo2Str( aStr, "=", aName, aValue );
    if( aName=="" )
      continue;

    int aIndex = String_FindNamedItem( aStringsOld, "=" , aName );

    if( aIndex<0 )
      aStringsOld->Add( aStr );
    else
      aStringsOld->Strings[ aIndex ] = aStr;
  }

  String aNewStr = StringsToStr( aStringsOld, aSpItems, false );
  delete aStringsOld;
  delete aStringsItems;
  return aNewStr;
}

void RunScript( TStrings* aStrings )
{
  TStrings* aScriptStrings = new TStringList;

  aScriptStrings->Text = aStrings->Text;
  aScriptStrings->Insert( 0, "sub main()" );
  aScriptStrings->Add( "end sub" );

  RunScript( aScriptStrings, "main" );
  delete aScriptStrings;
}

//------------------------------------------------------------------------------

void Strings_RmvSection( TStrings* aStrings, int aSecCount, String aStartStr, String aEndStr,
                          int aStartPos, int aEndPos, bool RmvHeadAndTail )
{
  int  aSecBgn, aSecEnd;

  Strings_GetSection_Pos( aStrings, aSecCount, aStartStr, aEndStr,
                              "Between", aStartPos, aEndPos, aSecBgn, aSecEnd  ) ;

  if( RmvHeadAndTail == false )
  {
    aSecBgn = aSecBgn + 1;
    aSecEnd = aSecEnd - 1;
  }

  if( aSecBgn>=0 && aSecEnd>=0 )
  {
    for ( int i=aSecEnd ; i>=aSecEnd; i-- )
      aStrings->Delete(i);
  }
}


//------------------------------------------------------------------------------
//���ܣ���ȡָ���ַ�����ַ������ϣ����硰Strings_GetSection(aStrings,"Bgn","End")��
//������[ aStrings ]
//      [ aStartStr : ����ʼ��Ƿ��� ]
//      [ aEndStr : �������Ƿ��� ]
//      [ aGetPos : ��ȡ��ʽ "Between" ��"Before"��"After" ]
//------------------------------------------------------------------------------


void Strings_GetSection_Pos( TStrings* aStrings, int aSecCount, String aStartStr, bool IsStrings, String aEndStr,  TStrings*  aEndStrings,
                              String aGetPos, int aStartPos, int aEndPos,  int& aSecBgn,int& aSecEnd  )
{

  int aBgn = LocateNamedRow( aStrings, aSecCount, aStartStr, aStartPos, aEndPos   );
  int aEnd;
  if( aBgn < 0 )
  {
    aBgn = 0;
    aEnd = -1;
  }
  else
  {
    if( IsStrings )
    {
      //--- ���EndStrԴ
      //TStrings* aEndStrs = splitToStrings( aEndStr, aEndStrSp, false );
      aEnd = LocateNamedRow( aStrings, 0, aEndStrings, aBgn+1, aEndPos   );
      //delete aEndStrs;
    }
    else
    {
      //--- ����Դ ----
      aEnd = LocateNamedRow( aStrings, 0, aEndStr, aBgn+1, aEndPos   );          //2009.7.17 by sxd
    }

    //aEnd = LocateNamedRow( aStrings, 0, aEndStr, aStartPos, aEndPos   );
    if( aEnd < 0 )
      aEnd = aStrings->Count;
  }

  if( aGetPos == "Before" )
  {
    aSecBgn = 0;
    aSecEnd = aBgn-1;
  }
  else  if( aGetPos == "Between" )
  {
    aSecBgn = aBgn;
    aSecEnd = aEnd;
  }
  else if( aGetPos == "After" )
  {
    aSecBgn = aEnd+1;
    aSecEnd = aStrings->Count;
  }
  else
    throw Exception( "δע��GetSection���ͣ�" );

  //CopyStrings( aSecStrings, aStrings, aSecBgn, aSecEnd );
  //return  aSecStrings;
}

int LocateNamedRow( TStrings* aStrings, int aFindCount , String aStrFind, int aBgn, int aEnd )
{
  return _LocateNamedRow( aStrings, aFindCount, "Str", NULL, aStrFind, aBgn,  aEnd );
}

//------------------------------------------------------------------------------
//������[ aStrings: ���������ַ������� ]
//      [ aFindCount: ���ҵ�ʵ���� 0,1,2,3.... ]
//      [ aStrFind: ��λ�ַ��� IsPreFix��ʽ ]
//------------------------------------------------------------------------------
int _LocateNamedRow( TStrings* aStrings, int aFindCount, String Style, TStrings* aStringFind, String aStrFind, int aBgn, int aEnd )
{
  if( aStrings==NULL  )
    return -1;

  int aPos = aBgn;
  int aFind = 0;
  for( ; ; )
  {
     if( UpperCase( Style ) == UpperCase( "Strings" ) )
       aPos = LocateNamedRow( (TStringList*)aStrings, (TStringList*)aStringFind, aBgn, aEnd );
     else
       aPos = LocateNamedRow( (TStringList*)aStrings, aStrFind, aBgn, aEnd );

     if( aPos<0 )
       return -1;
     aFind = aFind+1;
     if( aFind>aFindCount )
       return aPos;

     //aFind = aFind + 1;            //2010.5.31
     aBgn = aPos+1;
  }
}

int LocateNamedRow( TStrings* aStrings, int aFindCount , TStrings* aStringFind, int aBgn, int aEnd )
{
  return _LocateNamedRow( aStrings, aFindCount, "Strings", aStringFind, "", aBgn,  aEnd );
}


void Strings_GetSection_Pos( TStrings* aStrings, int aSecCount, String aStartStr, String aEndStr,
                              String aGetPos, int aStartPos, int aEndPos,  int& aSecBgn,int& aSecEnd )
{
   Strings_GetSection_Pos( aStrings, aSecCount, aStartStr, false, aEndStr,  NULL,
                           aGetPos, aStartPos, aEndPos,  aSecBgn, aSecEnd  );
}

TStrings* GetSectionFromFile( String aFileName, int aSecCount, String aStartStr, String aEndStr,
                              int aStartPos, int aEndPos, bool RmvHeadAndTail )
{
   try
   {
     if( FileExists( aFileName ) == false )
       return new TStringList;

     TStrings* aStringsAll = new TStringList;
     aStringsAll->LoadFromFile( aFileName );

     TStrings* aStrings = Strings_GetSection( aStringsAll, aSecCount, aStartStr, aEndStr,
                              aStartPos, aEndPos, RmvHeadAndTail );
     delete aStringsAll;
     return aStrings;
   }
   catch( Exception& e )
   {
     return new TStringList;
   }  
}

//------------------------------------------------------------------------------
//������[ aStrings -- ��ȡ��ԭ�ַ��� ]
//      [ aSecCount -- ʵ���� ]
//      [ aStartStr -- Sec����ʼ��� ]
//      [ aEndStr -- Sec�Ľ������ ]
//      [ IsStrings -- true/����������; flase -- ����������� ]
//      [ aEndStrSp -- ����"��" ]
//------------------------------------------------------------------------------
TStrings* Strings_GetSection( TStrings* aStrings, int aSecCount, String aStartStr, bool IsStrings, String aEndStr,  TStrings*  aEndStrings,
                              String aGetPos, int aStartPos, int aEndPos, bool RmvHeadAndTail )

{
  TStrings* aSecStrings = new TStringList;

  int  aSecBgn, aSecEnd;
  Strings_GetSection_Pos( aStrings, aSecCount, aStartStr, IsStrings, aEndStr, aEndStrings,
                              aGetPos, aStartPos, aEndPos, aSecBgn, aSecEnd );

  if( RmvHeadAndTail==true )
  {
    CopyStrings( aSecStrings, aStrings, aSecBgn+1, aSecEnd-1 );
    G_SecBgn = aSecBgn+1;
    G_SecEnd = aSecEnd-1;
  }
  else
  {
    CopyStrings( aSecStrings, aStrings, aSecBgn, aSecEnd );
    G_SecBgn = aSecBgn;
    G_SecEnd = aSecEnd;
  }

  return  aSecStrings;
}

TStrings* Strings_Union( TStrings* aList1, TStrings* aList2, bool isMaskMerge  )
{
  return MergeStrings( aList1, aList2, isMaskMerge );
}


TStrings* Strings_Union( TStrings** I_Strings, int I_Strings_Size, bool isMaskMerge  )
{
  if(  I_Strings_Size < 2 )
    return (new TStringList);

  TStrings* aList = Strings_Union( I_Strings[0], I_Strings[1], isMaskMerge );
  for( int i=2; i<I_Strings_Size; i++ )
  {
    TStrings* aListNew = Strings_Union( aList, I_Strings[i], isMaskMerge );
    CopyStrings( aList, aListNew);
    delete aListNew;
  }
  return aList;
}


TStrings* Strings_GetSection( TStrings* aStrings, int aSecCount, String aStartStr, String aEndStr,
                              String aGetPos, int aStartPos, int aEndPos, bool RmvHeadAndTail )
{
  return Strings_GetSection( aStrings, aSecCount, aStartStr, false, aEndStr,  NULL,
                              aGetPos, aStartPos, aEndPos, RmvHeadAndTail );
}

TStrings* Strings_GetSection( TStrings* aStrings, int aSecCount, String aStartStr, String aEndStr,
                              int aStartPos, int aEndPos, bool RmvHeadAndTail )
{
   return Strings_GetSection( aStrings, aSecCount, aStartStr, false, aEndStr, NULL,
                              "Between", aStartPos, aEndPos, RmvHeadAndTail ) ;
}

TStrings* Strings_GetSection( TStrings* aStrings, int aSecCount, String aStartStr, TStrings*  aEndStrings,
                              int aStartPos, int aEndPos, bool RmvHeadAndTail )
{
   return Strings_GetSection( aStrings, aSecCount, aStartStr, true, "", aEndStrings,
                              "Between", aStartPos, aEndPos, RmvHeadAndTail ) ;

}

//------------------------------------------------------------------------------
//���ӣ�Strings_GetSection_Named( aStrings, "NAME", "=", "HFSSModel1", "$begin 'HFSSModel'",  "$end 'HFSSModel'", true );
//------------------------------------------------------------------------------
TStrings* Strings_GetSection_Named( TStrings* aStrings, String aIdName, String aIdSp, String aIdValue, String aStartStr, String aEndStr,
                                    int aStartPos, int aEndPos,  bool RmvHeadAndTail )
{
  //ȡ��0��
  if( aIdValue=="" )
    return Strings_GetSection( aStrings, 0, aStartStr, aEndStr, aStartPos, aEndPos, RmvHeadAndTail );

  TStrings* aSecStrings = new TStringList;
  //int i=0;
  int aBgn = aStartPos;
  for( ;; )
  {
    delete aSecStrings;
    aSecStrings = Strings_GetSection( aStrings, 0, aStartStr, aEndStr, aBgn, aEndPos, RmvHeadAndTail );

    //if( aSecStrings->Count <= 2 )
    //  break;

    if( G_SecBgn<0 || G_SecEnd<0 )
      break;

    aBgn = G_SecEnd + 1;

    String aValue = Get_ListItemStr_ByName( aSecStrings, aIdName, aIdSp, "" );
    if( UpperCase(aValue) == UpperCase(aIdValue) )
      break;
  }

  return aSecStrings;
}

//TStrings* Strings_GetSection( TStrings* aStrings, int aSecCount, String aStartStr, String aEndStr, int aStartPos, int aEndPos, bool RmvHeadAndTail )
//{
//  return Strings_GetSection( aStrings, aSecCount, aStartStr, aEndStr, "Between",  aStartPos, aEndPos,RmvHeadAndTail );
//}

TStrings* Strings_GetSectionBefore( TStrings* aStrings, int aSecCount, String aStartStr, String aEndStr )
{
   return Strings_GetSection( aStrings, aSecCount, aStartStr, aEndStr, "Before" );
}

TStrings* Strings_GetSectionAfter( TStrings* aStrings, int aSecCount, String aStartStr, String aEndStr )
{
   return Strings_GetSection( aStrings, aSecCount, aStartStr, aEndStr, "After" );
}


//----------------------------------------------------------------------------
//���ܣ�[ "AB", "BC", "", "CD" ]  -> [ "AB;BC;;CD"]
//----------------------------------------------------------------------------

void StrToStrings( String aStr, TStrings* aString, String aSp )
{
  splitToStrings( aStr, aSp, false, aString );
}

String StringsToStr( TStrings* aStrings, String aSp, bool IsTrim, int aMaxLen )
{
  return StringsToStr( aStrings, 0, aStrings->Count-1, aSp, IsTrim, aMaxLen );
}

String StringsToStr( TStrings* aStrings, int aBgn, int aEnd, String aSp, bool IsTrim, int aMaxLen )
{
  if( aBgn<0)
    aBgn = 0;
  if( aEnd > aStrings->Count-1 )
    aEnd = aStrings->Count-1;
    
  String aStr="";
  String aStrRet="";
  for( int i=aBgn; i<=aEnd; i++ )
  {
    if( IsTrim && aStrings->Strings[i]=="" )
      continue;

    if( i==0 )  //aStr=="" )
      aStr = aStrings->Strings[i];
    else
      aStr = aStr + aSp + aStrings->Strings[i];

    if( aMaxLen>0 && aStr.Length() >= aMaxLen )      //���ڽضϳ���
      break;
      
    aStrRet=aStr;
  }
  return aStrRet;
}


//------------------------------------------------------------------------------
//���ܣ�����aStrings�е�ָ����Ŀ
//���磺Strings_FindNamedItem( "A=1\n\rB=2\n\rC=3\n\rD=4",  "=", "B" )  -> ���� 1
//------------------------------------------------------------------------------

int String_FindNamedItem
             ( TStrings* aStrings, String aSpNameAndValue, String aName )
{
  for( int i=0; i<aStrings->Count; i++ )
  {
    String aStr = aStrings->Strings[i];
    String aName1, aValue1;
    SplitStrTo2Str( aStr, aSpNameAndValue, aName1, aValue1 );

    if( IsEqualByCase(aName,aName1,false) == true ) //UpperCase( aName ) == UpperCase( aName1 ) )
      return i;
  }
  return -1;
}

//------------------------------------------------------------------------------
//���ܣ�
//������[ ]
//���ӣ�
//   ListName = [ A B C D E ]
//   ListParentName = [ B "" B C C ]
//   aRootStr �� aRootTag -- ��Ϊ���ڵ���ַ�������Tag����
//aNodeIns: ����Tree��λ��( NULL��ʾ���ڵ� ��
//aType: "TAG" ���� "NAME"

// IncludeRoot: �������Ƿ�������ڵ㣬 �ǣ����ڵ�����ڼ�����    [36666 ��] [3667 36666] [ 3668 36666]
//                                     �񣬸��ڵ㲻�ڼ�����      [3667 36666] [ 3668 36666]
//------------------------------------------------------------------------------
void ListToTree_Basic( TTreeNode* aNodeIns,
                       TStrings* aListName, TStrings* aListParName, TStrings* aListShowName,
                       TTreeView* aTree, String aRootStr, unsigned int aRootTag,
                       bool IncludeRoot, String aType, bool aIsClear )
{

  TStrings* aRootPos = _ListToTree_FindRootPos( aListParName, aRootStr, aRootTag, aType );

  bool aClear;
  for( int i=0; i<aRootPos->Count; i++ )
  {
    if( i==0 )
      aClear = aIsClear;
    else
      aClear = false;
        
    ListToTree_Basic( aNodeIns, aListName, aListParName, aListShowName,
                        aTree, StrToIntDef( aRootPos->Strings[i],-1), IncludeRoot, aType, aClear ) ;
  }
  delete aRootPos;
}

//------------------------------------------------------------------------
//����: List --> Tree
//������[ aNodeIns -- Tree�Ĳ���λ�� ]
//      [ aLiatName, aListParName, aListShowName -- List�ṹ������Ϣ ]
//      [ aRootPos--���ڵ��λ�� ]
//      [ IncludeRoot -- true,����һ�����ڵ㣻false--�޸��ڵ����� ]

void ListToTree_Basic( TTreeNode* aNodeIns,
                       TStrings* aListName, TStrings* aListParName, TStrings* aListShowName,
                       TTreeView* aTree, int aRootPos,
                       bool IncludeRoot, String aType, bool aIsClear )
{
  if( aRootPos<0 )
    return;
    
  if( aListName==NULL || aListParName==NULL || aTree == NULL )
    return;
  if( aListName->Count!=aListParName->Count )
    throw Exception( "aListName->Count!=aListParName->Count" );

 //�Ľ�������㷨�ٶ�   
  MListToTreePositions* aListParPos = _ListToTree_CreateRelation( aListName, aListParName, aType );
  aListParPos->SetVisited(false);

  if( aIsClear == true )
    //�����
    aTree->Items->Clear();

  //--- ���ñ�����־ ---

  //TStrings* aVisited = new TStringList;
  //for( int i=0; i<aListName->Count; i++ )
  //  aVisited->Add("F");
  //--- ���Ҳ�����Root�ڵ� -------
  //int aRootIndex = aListParName->IndexOf( aRootStr );
  //if( aRootIndex > 0 )
  //  aVisited->Strings[aRootIndex] = "T";

  //ȷ�����Ĳ���λ��
  TTreeNode* aNode = aNodeIns;

  //�и��ڵ�����
  if( aNode==NULL && IncludeRoot==true )
  {
    aNode = aTree->Items->AddChild( NULL, aListName->Strings[aRootPos] );
    aNode->Data = (void*)aListName->Objects[aRootPos];   
  }
  
  //--- ���������뺢�ӽڵ� ----  
  int aCurCount=1;
  _ListToTree( aListName, aListParPos, aListShowName, aRootPos, aTree, aNode, aCurCount );

  delete aListParPos;             
  //delete aVisited;
}


//��aRootPos��Ӧ�Ľڵ���뵽aParentNode�����ݹ����Root�ĺ��ӽڵ�

void _ListToTree( TStrings* aListName, MListToTreePositions* aListParPos, TStrings* aListShowName,
                  int aRootPos, TTreeView* aTree, TTreeNode* aParentNode, int& aCurCount )
{
  if( aRootPos<0 )
    return;

  //if( aListName==NULL || aListParPos==NULL  || aTree == NULL )
  //  return;    
  //gError->Warn1( "�б�ṹת��Ϊ���ṹ(" + IntToStr(aCurCount)+ "/" + IntToStr(aListName->Count) + ")");

  //���뵱ǰ�ڵ�
  TTreeNode* aNode = aTree->Items->AddChild( aParentNode, aListShowName->Strings[aRootPos] );
  aNode->Data = (void*)aListName->Objects[aRootPos];

  //�ݹ���뺢�ӽڵ�
  MListToTreePosition* aPos = aListParPos->Items[aRootPos];

  if( aPos->Visited==true )
    return;
  aPos->Visited= true;

  for( int i=0; i<aPos->ChildNodesPos->Count; i++ )
  {
    int aNewPos = StrToIntDef( aPos->ChildNodesPos->Strings[i], -1 );
    if( aNewPos<0 )
      continue;

    //TTreeNode* aNode = aTree->Items->AddChild( aParentNode, aListShowName->Strings[aNewPos] );
    //aNode->Data = (void*)aListName->Objects[aNewPos];

    _ListToTree( aListName, aListParPos, aListShowName, aNewPos, aTree, aNode, aCurCount );    
  }    
}

unsigned int StringList_Tag( TStrings* aList, int i )
{
  TObject* aObject = aList->Objects[i];
  if( aObject==NULL )
    return -1;

  return * ((unsigned int *) aObject);
}



//------------------------------------------------------------------------------
//���ܣ���aListName��aListParName����Ԥ�����γ�MListToTreePositions�ṹ(���׽ڵ�ͺ��ӽڵ�ļ���)
//------------------------------------------------------------------------------

MListToTreePositions* _ListToTree_CreateRelation( TStrings* aListName, TStrings* aListParName,
                                                  String aType )
{ 
  if( aListName==NULL || aListParName==NULL )
    throw Exception( "��ָ��!" );
  if( aListName->Count!=aListParName->Count )
    throw Exception( "aListName->Count!=aListParName->Count" );

  //��ʼ���ṹ  
  MListToTreePositions* aListParPos = new MListToTreePositions;
  for( int i=0; i<aListName->Count; i++ )
  {
      MListToTreePosition* aPosNode = new MListToTreePosition();
      aListParPos->Add( aPosNode );
  }
  
  if( aType == "TAG" )     //�ڵ�ƥ��, TAG��ʽ
  {
    for(int i=0; i<aListName->Count; i++ )
    {
      gError->Warn1( "���ڵ㴦��(" + IntToStr(i) + "/" +
                     IntToStr(aListName->Count)+"��)" );

      unsigned int aiTag = StringList_Tag( aListName, i );
      //unsigned int aiParentTag = StringList_Tag( aListParName, i );

      for( int j=0; j<aListName->Count; j++ )      //δ����
      {
        if( aListParPos->Items[j]->ParentNodePos >= 0 )  //|| i==j )
          continue;

        //unsigned int ajTag = StringList_Tag( aListName, j );
        unsigned int ajParentTag = StringList_Tag( aListParName, j );

        //if( ajTag == aiParentTag  )     //j��i�ĸ���
        //{
        //  aListParPos->Items[i]->ParentNodePos =  j;
        //  aListParPos->Items[j]->ChildNodesPos->Add( IntToStr( i ) );
        //}
        //else

        if( aiTag == ajParentTag  )    //i��j�ĸ���
        {
            aListParPos->Items[j]->ParentNodePos = i;
            aListParPos->Items[i]->ChildNodesPos->Add( IntToStr( j ) );
        }
      }
    }
  }
  else
  {
    String aiName;
    String ajParentName ;

    for(int i=0; i<aListName->Count; i++ )
    {
      gError->Warn1( "���ڵ㴦��(" + IntToStr(i) + "/" +
                     IntToStr(aListName->Count)+"��)" );

      aiName = UpperCase(aListName->Strings[i]);
      //String aiParentName = UpperCase( aListParName->Strings[i] );

      //for( int j=i+1; j<aListName->Count; j++ )
      for( int j=0; j<aListName->Count; j++ )
      {
        if( aListParPos->Items[j]->ParentNodePos >= 0 )  //|| i==j )
          continue;

        //String ajName = UpperCase( aListName->Strings[j] );
        ajParentName  = UpperCase(aListParName->Strings[j]);

        if( aiName == ajParentName   )    //i��j�ĸ���
        {
            aListParPos->Items[j]->ParentNodePos = i;
            //aListParPos->Items[j]->Flg = true;
            aListParPos->Items[i]->ChildNodesPos->Add( IntToStr( j ) );
        }

      }
    }

  }

  gError->Warn1( "OK" );
  return aListParPos;
}



//���ܣ�Ԥ����

TStrings* _ListToTree_FindRootPos( TStrings* aStrings, String aRootStr, unsigned int aRootTag, String aType )
{
  TStrings* aPos = new TStringList;
  aRootStr = UpperCase( aRootStr );

  if( aType=="NAME" )
  {
     for( int i=0; i<aStrings->Count; i++ )
     {
        if( UpperCase(aStrings->Strings[i]) == aRootStr  )
           aPos->Add( IntToStr(i) );;
     }
  }
  else
  {
     for( int i=0; i<aStrings->Count; i++ )
     {
        if( StringList_Tag( aStrings, i ) == aRootTag  )
          aPos->Add( IntToStr(i) );
     }
  }
  return aPos;
}



//----------------ListView---------------------------------

void ListView_DelItemByata( TListView* aList, void* aData )
{
  if( aList==NULL || aData==NULL )
    return;

  int aItemIndex = ListView_IndexByData( aList, aData );
  if( aItemIndex >= 0 )
    aList->Items->Delete( aItemIndex );
}

void ListView_Delete( TListView* aList, TListItem* aItem )
{
  if( aList==NULL || aItem==NULL )
    return;

  int aItemIndex = aList->Items->IndexOf( aItem );
  if( aItemIndex >= 0 )
    aList->Items->Delete( aItemIndex );
}

void* GetListViewSelectedNodeData ( TListView* aList )
{
  if( aList==NULL )
    return NULL;

  TListItem* aSelected = aList->Selected;
  if( aSelected!=NULL )
    return aSelected->Data;
  else
    return NULL;
}

TListItem* ListView_InsertItems( TListView* aListView, String aStrAll, String aSp, void* aData )
{
  return ListView_InsertItems( aListView, aListView->ItemIndex, aStrAll, aSp, aData );
}

TListItem* ListView_InsertItems( TListView* aListView, int aItemIndex, String aStrAll, String aSp, void* aData )
{
  if( aListView==NULL )
    return NULL;

  if( aItemIndex<0 )
    aItemIndex=0;
  TListItem* aListItem = aListView->Items->Insert(aItemIndex);
  ListView_SetItems( aListItem, aStrAll, aSp, aData );

  try
  {
    aListView->ItemIndex = aItemIndex;
  }
  catch( Exception& e )
  {
  }

  return aListItem;
}

//���ӣ�ListView_SetItems( aItem, FullName(), "->", (void*)this );

void ListView_SetItems( TListItem* aListItem, String aStrAll, String aSp, void* aData )
{
  TStrings* aStrings = splitToStrings( aStrAll, aSp );
  if( aStrings->Count<1 )
  {
    delete aStrings;
    return;
  }

  aListItem->SubItems->Clear();
    
  aListItem->Caption = aStrings->Strings[0];
  aListItem->Data = aData;

  for( int i=1; i<aStrings->Count; i++ )
    aListItem->SubItems->Add(aStrings->Strings[i]);

  delete aStrings;
}

TListItem* ListView_AddItems( TListView* aListView, String aStrAll, String aSp, void* aData )
{
  if( aListView==NULL )
    return NULL;
  TListItem* aListItem = aListView->Items->Add();
  ListView_SetItems( aListItem, aStrAll, aSp, aData );
  return aListItem;
}

TListItem* ListView_SelectedItem( TListView* aListView )
{
  if( aListView==NULL )
    return NULL;
  return aListView->Selected;
}

int ListView_FindColByCaption( TListView* aListView, String aCaption )
{
  if( aListView==NULL )
    return -1;

  for( int i=0; i<aListView->Columns->Count; i++ )
  {
    TListColumn* aColumn = aListView->Columns->Items[i];
    if( IsEqualByCase(aColumn->Caption, aCaption, false ) == true )
      return i;
  }
  return -1;
}

int ListView_GetRowByCaptionAndValue( TListView* aListView, String aColName, String aFindValue )
{
  int aCol = ListView_FindColByCaption(aListView, aColName);
  return ListView_GetRowByCaptionAndValue( aListView, aCol, aFindValue );
}

int ListView_GetRowByCaptionAndValue( TListView* aListView, int aCol, String aFindValue )
{
  if( aListView==NULL || aCol < 0  )
    return -1;

  for( int i=0; i<aListView->Items->Count; i++ )
  {
    TListItem* aItem = aListView->Items->Item[i] ;
    String aStr = ListView_ItemValue( aItem, aCol );
    if( IsEqualByCase( aStr, aFindValue, false ) ==  true )
      return i;
  }         
  return -1;
}

bool ListView_SelectRow( TListView* aListView, int aRow )
{
  if( aListView==NULL || aRow<0 || aRow>=aListView->Items->Count )
    return false;
  aListView->Items->Item[aRow]->Selected = true;
  return true;
}

//20151022
//  ListView_Search( LV_Records, "��Ʒ���Ϻ�", EditSearch->Text );

void ListView_Search( TListView* aListView, String aColName, String aFindValue )
{
  int aRow =  ListView_GetRowByCaptionAndValue( aListView, aColName, aFindValue );
  ListView_SelectRow(aListView, aRow);
}

//20151022 ����ֲ

void SetListViewData( TListItem* aItem, void* aData )
{
  if( aItem == NULL )
    return;
  aItem->Data = aData;
}

void SetListViewSelectedNodeData ( TListView* aList, void* aData )
{
   SetListViewData( ListView_SelectedItem(aList), aData );
}

String ListView_ItemValue( TListItem* aItem, int aCol )
{
   if( aItem==NULL || aCol < 0 || aCol > aItem->SubItems->Count )
     return "";

   if( aCol==0 )
     return aItem->Caption;

   return aItem->SubItems->Strings[ aCol-1 ];
}


String ListView_ItemValue_NamedCol( TListItem* aItem, String aName )
{
  return ListView_ItemValue( aItem, ListView_FindColByCaption( aItem, aName ) );
}

int ListView_FindColByCaption( TListItem* aItem, String aName )
{
  if( aItem==NULL )
    return -1;
  return ListView_FindColByCaption( (TListView*)aItem->ListView, aName );
}


String ListView_SelectedItemValue( TListView* aListView, int aCol )
{
   return ListView_ItemValue( ListView_SelectedItem( aListView ), aCol );
}

TList* ListView_GetSelectedItems( TListView* aListView )
{
  TList* aItems = new TList;
  if( aListView==NULL )
    return aItems;
  for( int i=0; i<aListView->Items->Count; i++ )
  {
    TListItem* aItem = aListView->Items->Item[i] ;
    if(  aItem->Selected == true )
      aItems->Add( aItem );
  }
  return aItems;
}

void ListView_SelectAllItems( TListView* aListView, bool IsSelected )
{
  if( aListView==NULL )
    return;
  for( int i=0; i<aListView->Items->Count; i++ )
  {
    TListItem* aItem = aListView->Items->Item[i] ;
    aItem->Selected = IsSelected;
  }

  //��ʾѡ��Ч��
  ControlSetFocused( aListView );
}

void ControlSetFocused( TWinControl* aControl )
{
  if( aControl==NULL )
    return;

  String aName = aControl->ClassName();

  if( aName == "TSpeedButton" )
  {
    TSpeedButton* aButton = (TSpeedButton*)aControl;
    //aButton->Click();
    aButton->Down = true;
  }
  else
    if( aControl->CanFocus() )
      aControl->SetFocus();
}


TList* ListView_GetAllItems( TListView* aListView )
{
  TList* aItems = new TList;
  if( aListView==NULL )
    return aItems;
  for( int i=0; i<aListView->Items->Count; i++ )
  {
    TListItem* aItem = aListView->Items->Item[i] ;
    aItems->Add( aItem );
  }
  return aItems;
}

TList* ListView_GetSelectedItemDatas( TListView* aListView )
{
  TList* aItems = ListView_GetSelectedItems( aListView );
  TList* aItemDatas = ListView_GetListItemsDatas(aItems);
  aItems->Clear();
  delete aItems;
  return  aItemDatas;
}

TList* ListView_GetAllItemDatas( TListView* aListView )
{
  TList* aItems = ListView_GetSelectedItemDatas( aListView );
  TList* aItemDatas = ListView_GetListItemsDatas(aItems);
  aItems->Clear();
  delete aItems;
  return  aItemDatas;
}

TList* ListView_GetListItemsDatas( TList* aItems )
{
    TList* aItemDatas = new TList;
    for( int i=0; i<aItems->Count; i++ )
    {
       TListItem* aItem = (TListItem*)aItems->Items[i];
       aItemDatas->Add( aItem->Data );
    }
    return aItemDatas;
}

void* ListView_SelectedItemData( TListView* aListView )
{
   TListItem* aItem = ListView_SelectedItem( aListView );
   if( aItem == NULL )
     return NULL;
   return aItem->Data;
}

TListItem* ListView_FindByData( TListView* aListView, void* aData )
{
  if( aListView==NULL )
    return NULL;
  int aIndex = ListView_IndexByData( aListView, aData );
  if( aIndex<0 )
    return NULL;
  return aListView->Items->Item[aIndex];

 /* for( int i=0; i<aListView->Items->Count; i++ )
  {
    TListItem* aItem = aListView->Items->Item[i];
    if( aItem->Data == aData )
      return aItem;
  }
  return NULL; */
}

int ListView_IndexByData( TListView* aListView, void* aData )
{
  if( aListView==NULL )
    return -1;
  for( int i=0; i<aListView->Items->Count; i++ )
  {
    TListItem* aItem = aListView->Items->Item[i];
    if( aItem->Data == aData )
      return i;
  }
  return -1;
}



//���ӣ�ListView_AddTitles( aList, "��������;������;����ֵ", "50;80;0", ";" );

void ListView_AddTitles( TListView* aListView, String aTitles, String aSizeStr, String aSp, bool IsMask )
{
  if( aListView==NULL )
    return;

  if( IsMask==true && aListView->Columns->Count>0 )
    return;
    
  TStrings* aStrings = splitToStrings( aTitles, aSp );
  TStrings* aSizes = splitToStrings( aSizeStr, aSp );

  for( int i=0; i<aStrings->Count; i++ )
  {
    TListColumn* aColumn = aListView->Columns->Add();
    aColumn->Caption = aStrings->Strings[i];

    int aSize;
    try
    {
      aSize = StrToInt( aSizes->Strings[i] );
    }
    catch( Exception& e )
    {
      aSize = 0;
    }
    if( aSize>0 )
    {
      aColumn->Width = aSize;
      aColumn->AutoSize = false;
    }
    else
      aColumn->AutoSize = true;
  }
}

void ListView_InitForGrid(TListView* aListView)
{
  if( aListView==NULL )
    return;
  aListView->Clear();
  aListView->Columns->Clear();
  aListView->ViewStyle = vsReport;
  aListView->RowSelect = true;
  aListView->GridLines = true;
  aListView->ShowWorkAreas = true;
}

void ListView_Refresh(TListView* aListView)
{
  if( aListView==NULL )
    return;
  aListView->Width = aListView->Width+10;
  aListView->Width = aListView->Width-10;
}



String AskDirectory( String aPath )
{
  FormDirectory->Directory->Directory = aPath;
  if( FormDirectory->ShowModal() != mrOk )
    throw Exception ("�û�ȡ��");
  return FormDirectory->Directory->Directory;
}

String  GetProjectPath()
{
    //��ȡ����·��;
    TIniFile*  aPrjPath = new TIniFile(ApplicationPath()+"\\SysConfig.ini");

    String  aDefault =  ApplicationPath()+"\\defaultPrj";
    String aProjectPath = aPrjPath->ReadString("Project","ProjectPath",aDefault);
    delete aPrjPath;

    return aProjectPath;
}

void  DelVarStringsIfIn(String  aBookMark,TStrings* aVarNames)
{
    if(aVarNames == NULL && aBookMark == "")
            return;
    for(int i=0; i < aVarNames->Count; i++)
    {
        String aVarName = aVarNames->Strings[i];
        if(HasSubString(aVarName,aBookMark))
        {
            G_Word->AddVar(aVarName,"NULL");
        }
    }
}

//------------------------------------------------------------------------
//���ܣ���ǿ���ַ���λ������
//������[ aStr, aStrToFind  ]
//      [ aBgnPos -- ������ʼλ�� ]
//      [ aEndPos -- ��������λ�� ]
//˵����1Ϊ��ʼλ��
//------------------------------------------------------------------------

int StrPos( String aStr, String aStrToFind, int aBgnPos, int aEndPos )
{
  if( aBgnPos<=0 )
    aBgnPos = 1;
    
  if( aEndPos<=0 )
    aEndPos=aStr.Length();

  if( aBgnPos > aEndPos  )
    return 0;

  //��[aBgnPos,aEndPos]���ַ�������
  String aSubStr = aStr.SubString( aBgnPos, aEndPos-aBgnPos+1 );
  int aPos = aSubStr.Pos( aStrToFind );

  //����ɾ�������
  if( aPos<=0 )
    return 0;
  else
    return aBgnPos+aPos-1;
}



int GetSubStrCount( String aStr, String aSubStr )
{
  int aCount=0;
  int aPos = StrPos( aStr, aSubStr, 1 );
  for( ;; )
  {
    if( aPos<=0 )
      break;
    aCount=aCount+1;
    aPos = StrPos( aStr, aSubStr, aPos+aSubStr.Length() );
  }
  return aCount;
}

bool HasSubString( String aStr, String aSubStr )
{
  aStr = UpperCase( aStr );
  int aPos = aStr.Pos(UpperCase(aSubStr));
  return aPos>0;
}

bool HasSubString( String aStr, TStrings* aSubStrings )
{
  if( aSubStrings==NULL )
    return false;

  for( int i=0; i<aSubStrings->Count; i++ )
    if( HasSubString( aStr, aSubStrings->Strings[i] ) == true )
      return true;
  return false;
}

bool HasSubString( String aStr, String aSubStr, String aSp )
{
  TStrings* aStrings = splitToStrings( aSubStr, aSp );
  bool aRes = HasSubString( aStr, aStrings );
  delete aStrings;
  return aRes;
}






//------------------------------------------------------------------------------
//���ܣ��Եݹ鷽ʽ���Զ������Ծ���·����ʽ������Ŀ¼
//���ӣ�CheckAndMakeDirectory( "c:\\x\\y\\z" )������c:\�½���ָ��Ŀ¼������ԭ����״̬���
//------------------------------------------------------------------------------
void CheckAndMakeDirectory(String aDir)
{
  //ֻ�Ծ���·����������д���
   if( !IsAbsoluteFileName(aDir) )
   {
     //gError->Warn("CheckAndMakeDirectory����ֻ�Ծ���·����������д���");
     return;
  }

  String aParentDir = GetParentDirectory( aDir );

  if( aParentDir=="" || aParentDir==aDir )
    return;

  if( FileExists(aParentDir) )
  {
    gError->Warn( "�ļ�("+aParentDir+")�Ѵ��ڣ����ܴ���Ŀ¼�����Ƴ��ļ����ٴ���");
    return;
  }
  else if( !DirectoryExists (aParentDir) )
  {
    CheckAndMakeDirectory( aParentDir );   //�ݹ�
  }

  _CheckAndMakeDirectory( aDir );
}


TStringList* CheckAndLoadFromFile( String aFileName )
{               
  TStringList* aList = new TStringList;
  CheckAndLoadFromFile( aFileName, aList );
  return aList;
}

void CheckAndLoadFromFile( String aFileName, TStringList* aList )
{
  try
  {
    aList->Clear();
    if( FileExists( aFileName ) == false )
    {
      gError->Warn( "�ļ�(" +aFileName+ ")�����ڣ�" );
      return;
    }  
    aList->LoadFromFile( aFileName );
  }
  catch( Exception& e )
  {
    gError->Warn( "�ļ�װ�س���" + e.Message );
  }
}

String Manual3DPath()
{
  return ApplicationPath() + "\\Manual3D";
}

String Manual3DExeFile()
{
  return Manual3DPath() + "\\Manual3D.exe h";
}


//------------------------------------------------------------------------------
//������������ȡ����ָ����Name����������
//�磺 BeginNode,NodeId
int  GetIndexFromStrings_ByName(TStrings* aStrings,String iName,String iValue,int aBgnPos)
{
    int  iRet = -1;

    if(aStrings == NULL || aStrings->Count <= 0 )
        return iRet;

    String  aName, aValue;
    for(int i = aBgnPos; i < aStrings->Count; i++)
    {
        SplitStrTo2Str( aStrings->Strings[i], ",", aName, aValue );
        if( aName.UpperCase().Trim() != iName.UpperCase().Trim())
              continue;
        if( aValue.UpperCase().Trim() == iValue.UpperCase().Trim())
        {
             iRet = i;
             break;
        }
    }
    return iRet;
}


void ObjectToListBox( TListBox* aList, TObject* aObject, String aName )
{
  if( aList==NULL )
    return;

  int aIndex = aList->Items->IndexOfObject( aObject );
  if( aIndex < 0 )
    aList->Items->AddObject( aName, aObject );
  else
    aList->Items->Strings[ aIndex ] = aName;
}

void ObjectToComboBox( TComboBox* aBox, TObject* aObject, String aName )
{
  if( aBox==NULL )
    return;

    aBox->Items->AddObject(aName, aObject);
}


void StringsControl_SetItemIndex(TControl* aControl, int aIndex)
{
  if( aControl==NULL )
    return;
  String aType=aControl->ClassName();

  if( aType=="TComboBox" )
  {
    TComboBox* aBox = ((TComboBox*)aControl);
    if( aIndex>=0 && aIndex<aBox->Items->Count )
      aBox->ItemIndex = aIndex;
    else
      aBox->ItemIndex = -1;
  }
  else if ( aType=="TListBox" )
  {
    TListBox* aListBox = ((TListBox*)aControl);
    if( aIndex>=0 && aIndex<aListBox->Items->Count )
      aListBox->ItemIndex = aIndex;
    else
      aListBox->ItemIndex = -1;      
  }
  else
    throw Exception("δע���StringsControl");
}



//���룺aMemoText: Memo->Text
String  MemoVarPreProcess(String aMemoText,String aDiv)
{
   return StringReplace(aMemoText,"\r\n",aDiv,TReplaceFlags()<<rfReplaceAll);
}

void ConfirmApplication( Variant& aEng, String aExeCmd,String aComStr )
{
   String aProcessName = ChangeFileExt( ExtractFileName( aExeCmd ),".exe");
   try
   {
      if( ProcessExists1(aProcessName ) ==false )
         WinExec( aExeCmd.c_str()  , SW_NORMAL	 );
      if(  aEng.IsEmpty()  == true )
         aEng = Variant::CreateObject(aComStr);
   }
   catch(Exception &aE)
   {
     throw Exception("ConfirmApplication����!"+aComStr+"��"+aE.Message);
   }
}

void FileToStringsControl( String aFileName, TControl* aStringControl )
{
  if( aStringControl==NULL )
    throw Exception("StringControlΪ�գ�");
    
  if( !FileExists( aFileName )  )
    throw Exception( "�ļ�" +aFileName+ "������!" );

  StringsControl_Items(aStringControl)->LoadFromFile( aFileName );


  if( StringsControl_Count( aStringControl)>0 && StringsControl_ItemIndex(aStringControl) < 0 )
    StringsControl_SetItemIndex( aStringControl, 0 );
}

int StringsControl_ItemIndex(TControl* aControl)
{
  if( aControl==NULL )
    return 0;
  String aType=aControl->ClassName();

  if( aType=="TComboBox" )
    return ((TComboBox*)aControl)->ItemIndex;
  else if ( aType=="TListBox" )
    return ((TListBox*)aControl)->ItemIndex;
  else
    throw Exception("δע���StringsControl");
}

int StringsControl_Count(TControl* aControl)
{
  if( aControl==NULL )
    return 0;
  String aType=aControl->ClassName();

  if( aType=="TComboBox" )
    return ((TComboBox*)aControl)->Items->Count;
  else if ( aType=="TListBox" )
    return ((TListBox*)aControl)->Items->Count;
  else
    throw Exception("δע���StringsControl");
}

String StringsControl_ItemCur(TControl* aControl)
{
  return StringsControl_Item( aControl, StringsControl_ItemIndex( aControl ) );
}

String StringsControl_Item(TControl* aControl, int aIndex)
{
  if( aControl==NULL )
    return 0;

  if( aIndex < 0 || aIndex >= StringsControl_Count(aControl) )
    return "";

  String aType=aControl->ClassName();

  if( aType=="TComboBox" )
    return ((TComboBox*)aControl)->Items->Strings[ aIndex ];
  else if ( aType=="TListBox" )
    return ((TListBox*)aControl)->Items->Strings[ aIndex ];
  else
    throw Exception("δע���StringsControl");
}


TStrings* StringsControl_Items(TControl* aControl)
{
  if( aControl==NULL )
    throw Exception( "NULL Control!StringsControl_Items!" );
  String aType=aControl->ClassName();

  if( aType=="TComboBox" )
    return ((TComboBox*)aControl)->Items;
  else if ( aType=="TListBox" )
    return ((TListBox*)aControl)->Items;
  else
    throw Exception("δע���StringsControl");
}


TObject* GetListBoxSelectedNodeData ( TListBox* aList )
{
  try
  {
    return (aList->Items->Objects[ aList->ItemIndex ]);
  }
  catch( Exception& e )
  {
    return NULL;
  }
}

TObject* GetComboBoxSelectedLayerData(TComboBox* aCBox)
{
    try
    {
      return ( aCBox->Items->Objects[ aCBox->ItemIndex ]);
    }
    catch( Exception& e )
    {
      return NULL;
    }
}

MLayerDataTreeNode*  GetSelectedLayerData(TComboBox* aCBox)
{
    return (MLayerDataTreeNode*)GetComboBoxSelectedLayerData( aCBox );
}



//------------------------------Ŀ¼Ϊ����·��----------------------------------
bool IsAbsoluteFileName(String aDir)
{
  return ( UpperCase(ExpandFileName(aDir)) == UpperCase(aDir) );
}

//------------------------------------------------------------------------------
String GetParentDirectory( String aDir )
{
  aDir = ExcludeTrailingPathDelimiter(aDir);
  return ExtractFileDir( aDir );
}


void _CheckAndMakeDirectory(String aDir)
{
  if( FileExists(aDir) )
    throw Exception("�ļ�("+aDir+")�Ѵ��ڣ����ܴ���Ŀ¼�����Ƴ��ļ����ٴ���");
  else if( !DirectoryExists (aDir) )
      CreateDir( aDir );
}

bool CopyFileAlways( String aSrcFileName, String aDestFileName )
{
  try
  {
    if(aSrcFileName == aDestFileName)  return true;

    if( !FileExists(aSrcFileName) )
      throw Exception( "Դ�ļ�("+aSrcFileName+")�����ڣ�" );

    String aDestPath =  ExtractFilePath(aDestFileName);
    CheckAndMakeDirectory( aDestPath );

    if( FileExists( aDestFileName )  )
      DeleteFile(aDestFileName);

    return CopyFileTo( aSrcFileName, aDestFileName );
  }
  catch( Exception& e )
  {
    gError->Warn( "CopyFileAlways����" + e.Message );
    return false;
  }
}

//------------------------------------------------------------------------------
void SetAllSubCtrlEnable( TWinControl* aControl, bool IsEnable )
{
  if( aControl==NULL )
    return  ;

  //�ӿؼ�  
  for (int i=0 ;i<aControl->ControlCount;i++)
    aControl->Controls[i]->Enabled =IsEnable;

  //MainMenu�˵�  
  for (int i=0 ;i<aControl->ComponentCount ;i++)
  {
      if (dynamic_cast<TMainMenu*>( aControl->Components[i] ) )
      {
        TMainMenu* aMenu =  (TMainMenu*) aControl->Components[i];
        for (int j=0;j<aMenu->Items->Count ; j++)
          aMenu->Items->Items[j]->Enabled = IsEnable;
        break;
     }
  }          
}

bool IsControlVisible(TControl* aControl)
{
  for(;;)
  {
    if( aControl==NULL )
      break;
    if( aControl->Visible==false )
      return false;
    aControl = aControl->Parent;
  }
  return true;
}


//------------------------------------------------------------------------------
String MergeStr( String aStr1, String aStr2, String aDiv )
{
  if( aStr1=="" && aStr2=="" )
    return "";
  else if( aStr1!="" && aStr2=="" )
    return aStr1;
  else if( aStr1=="" && aStr2!="" )
    return aStr2;
  else
    return aStr1 + aDiv + aStr2;
}

bool IsEqualByCase(String aStr1, String aStr2, bool IsUppercase)
{
  aStr1 = Trim(aStr1);
  aStr2 = Trim(aStr2);
  return ( ( IsUppercase && aStr1==aStr2 ) ||
           ( !IsUppercase && UpperCase(aStr1)==UpperCase(aStr2) ) );
}

//------------------------------------------------------------------------------
//���ܣ��Ƿ���������ַ�
//------------------------------------------------------------------------------
bool String_HasChineseCharacter(String aStr)
{
  for( int i=0; i < aStr.Length(); i++ )
    if( (unsigned int)aStr[i+1] > 128 )
      return true;
  return false;
}


//------------------------------------------------------------------------------
//���ܣ�File / Path���ƴ�����
//------------------------------------------------------------------------------
String ApplicationPath()
{
   return ( ExtractFileDir( Application->ExeName ) );
}

//ģ��Ŀ¼
String TemplatePath()
{
   return ApplicationPath() + "\\ģ�嶨��";
}

String  ManualPath()
{
   return ApplicationPath() + "\\ʵ����Ŀ¼";
}

//��ʱĿ¼
String  TempPath()
{
   return  ApplicationPath() + "\\Temp";
}

//--------------------ϵͳĿ¼--------------------------------------------------
// ���ϵͳ���еıر�����--------------------
String  SystemPath()
{
    String   aPath = ApplicationPath() + "\\ϵͳĿ¼";

    CheckAndMakeDirectory(aPath);
    return aPath;
}

//------------------------------------------------------------------------------
bool ProcessExists1( String ExeName )
{
    char cBuf[256];
    AnsiString ExeFile;
    PROCESSENTRY32 pe32 = {sizeof(pe32)};

    HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
    if(hSnapShot  == NULL)
    {
      return false;
    }

    bool bFlag = Process32First(hSnapShot,&pe32);
    while (bFlag)
    {
      ExeFile = AnsiString(pe32.szExeFile);
      if( IsEqualByCase( ExeFile, ExeName , false ) == true ) //  UpperCase( ExeFile ) ==UpperCase(  ExeName ) )     //
      {
        CloseHandle(hSnapShot);
        return true;
      }
      bFlag  = Process32Next(hSnapShot,&pe32);
    }
    CloseHandle(hSnapShot);
    return false;
}

//-------------------------------------------------------------------------
//aTitles:  ��List����ʾ�ı�����
//aColSizes: ���
void TStringsToListView( TStrings* aStrings, TListView* aList,String aTitles,String  aColSizes)
{
    if(aStrings == NULL || aList == NULL)
         return;

    TStrings* aList_Titles = splitToStrings( aTitles, ";" );
    TStrings* aList_ColSizes = splitToStrings( aColSizes, ";" );

    ListView_InitForGrid(aList);
    ListView_AddTitles( aList, aTitles, aColSizes, ";" );

    for(int i=0; i < aStrings->Count; i++)
        ListView_AddItems(aList, aStrings->Strings[i],"=");

    ListView_Refresh(aList);

    delete aList_Titles;
    delete aList_ColSizes;
}

//---------------------------------------------------------------------------
bool ProcessExists( String ExeName)
{
    char  cBuf[256];
    AnsiString  ExeFile;
    PROCESSENTRY32  pe32     =  {sizeof(pe32)};

    HANDLE hSnapShot  = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
    if(hSnapShot  == NULL)
      return false;

    bool  bFlag  =  Process32First(hSnapShot,&pe32);
    while  (bFlag)
    {
      ExeFile  = AnsiString(pe32.szExeFile);
      if( UpperCase( ExeFile ) ==UpperCase(  ExeName ) )
      {
        return true;
      }
      bFlag  = Process32Next(hSnapShot,&pe32);
    }
    CloseHandle(hSnapShot);
    return false;
}

//------------------------------------------------------------------------------
//-----------WiatForFile------------------------------------

//���ܣ��ȴ�aExeFileName�����ļ�aFileName
//������[ aFileName -- ���ɵĽ���ļ������磺aPDFFileName ]
//      [ aProcessName -- �����ļ���ִ�еĽ������ƣ����磺"Word2PDF.EXE"]
//      [ aKillExeFileName -- ɱ��������ִ�е�exe����bat�ļ����ƣ����磺ApplicationPath()+"\\killword2PDF.bat"]

String WaitForFile( String aFileName, String aProcessName, String aKillExeFileName )
{
  gError->HeadTitle = "���������ļ�(" +aFileName+ ")";

  gError->Warn1( "���Ժ�" );
  for( ;; )
  {
    if( FileExists( aFileName ) == true )     //�ɹ�
    {
      if( aKillExeFileName!="" && FileExists(aKillExeFileName)==true )
        WinExec( aKillExeFileName.c_str(),SW_HIDE);
     {
       gError->Warn1( "OK��" );
       return aFileName;
     }
    }

    if( aProcessName!="" && ProcessExists1( aProcessName ) == false )   //ʧ��
    {
      gError->Warn1( "ʧ�ܣ�" );
      return "";
    } 
  }
}


//�����˸�ʽ���ֲ���DelimitedText��stringǰ�ո���ʧ������
//��Ҫ����ͷ�
TStrings* CRLFString2TStrings(String  aCRLFText,String aDiv)
{
    String  aStr1 = StringReplace(aCRLFText,"\r\n",aDiv,TReplaceFlags()<<rfReplaceAll);

    return  splitToStrings_Mask(aStr1,aDiv);
}


//----------------------------------------------------------------------------
//���ܣ���aStrings��ǰ׺ΪaPrefix���ַ��������У�
//���ӣ�FindStrInStrings_Prev( aStrings, "xx_", 0 )
//----------------------------------------------------------------------------
TStrings* FindAllStrStrings_Prev( TStrings* aStrings, String aPrefix )
{
  int aBgnPos = 0;
  TStrings* aFindStrings = new TStringList;
  for( ;; )
  {
     int aPos = IndexStrInStrings_Prev( aStrings, aPrefix, aBgnPos );
     if( aPos<0 )
       break;

     aFindStrings->Add(  aStrings->Strings[aPos] );
     aBgnPos = aPos+1;
  }
  return aFindStrings;
}

int IndexStrInStrings_Prev( TStrings* aStrings, String aPrefix, int aBgnPos )
{
  for( int i=aBgnPos; i<aStrings->Count; i++ )
  {
    String aStr = aStrings->Strings[i];
    if( IsPreFix( aStr, aPrefix ) )
      return i;
  }
  return -1;
}


//------------------------------------------------------------------------------
//���ܣ���aDivΪ����aStr�����Զ�ȥ���ظ���aDiv
//------------------------------------------------------------------------------
TStrings* splitToStrings_Mask( String aStr, String aDiv )
{
  TStrings* aStrings = splitToStrings( aStr, aDiv, false );
  for( int i=0; i<aStrings->Count; i++ )
  {
    if( aStrings->Strings[i] == aDiv || aStrings->Strings[i] == "" )
    {
      aStrings->Delete(i);
      i=i-1;
    }
  }
  return aStrings;
}


//------------------------------------------------------------------------------
// ���ܣ�Str��д��Grid
// ˵����"ѧ���ɼ�,DEFAULT=ѧ��;����;Ӣ��;����//1;����;60;70//2;����;75;80"
//------------------------------------------------------------------------------

void StrToGrid( String aStr, String aSpRec, String aSpField, TStringGrid* aGrid )
{
   TStrings* aValues = splitToStrings( aStr, aSpRec, false );
   aValues->Insert( 0, aValues->Count );
   StringsToGrid( aValues, aGrid, 0, NULL, NULL, aSpField );
   delete aValues;
}

//------------------------------------------------------------------------------
//��ģʽ��ת��
//------------------------------------------------------------------------------

void StringsToGrid( TStrings* aStrings, TStringGrid* aGrid, String aRecSp )
{
  TStrings* aStrings1 = new TStringList;
  aStrings1->Text = aStrings->Text;

  aStrings1->Insert(0,aStrings1->Count);
  StringsToGrid( aStrings1, aGrid, 0, NULL, NULL, aRecSp );
  delete aStrings1;
}


//------------------------------------------------------------------------------
// ���ܣ�TString*��д��Grid
// ˵����
//    ����
//    ��һ��Text
//    �ڶ���Text
//    ....
//    ��N��Text
//------------------------------------------------------------------------------

void StringsToGrid( TStrings* aStrings, TStringGrid* aGrid, int GridNo, TStatusBar* aHint, TProgressBar* aBar, String aRecSp )
{
  if( aGrid==NULL || aStrings==NULL )
    return;

  TStrings* ColWidths = Grid_GetColWidths(aGrid); //����ColWidths[]
  Grid_Clear(aGrid);

  if( aStrings->Count<=0 )
    return;

  //---��ѯ��ȡ��Grid��ʼλ��---
  int aGridCount;
  int aBgn=0, aEnd;
  int aGridNo=0;

  if( aHint!=NULL )
    aHint->SimpleText = "���ڶ���Grid���ݣ���"+IntToStr(aStrings->Count)+"�����ݣ�";
  if( aBar!=NULL )
  {
    try
    {
      aBar->Min = Math::Min( 1, aBar->Max );
      aBar->Max = Math::Max( aStrings->Count,aBar->Min ) ;
      aBar->Position = aBgn;
    }
    catch(Exception& except)
    {
    }
  }

  for(;;)
  {
     try
     {
       if( aBar!=NULL)
         try
         {
           aBar->Position = aBgn;
         }
         catch(Exception& except)
         {
         }
       aGridCount = StrToInt( aStrings->Strings[aBgn] );
       aEnd = aBgn + 1 + aGridCount ;

       aGridNo = aGridNo+1;
       if( aGridNo > GridNo )
         break;
       aBgn = aBgn+aGridCount+1;
     }
     catch(Exception& except)
     {
       throw Exception("�����Grid�洢��ʽ��");
     }
  }

  //---��ȡGrid---
  for( int i=aBgn+1; i<Math::Min( aEnd,aStrings->Count ); i++ )
  {
    if( aBar!=NULL)
       aBar->Position = i;
     TStrings* aRow=new TStringList;
     AStringToStrings( aStrings->Strings[i], aRow, aRecSp );
     if( i==aBgn+1 )
       Grid_SetRow(  aGrid, 0, aRow );
     else
       Grid_InsertRow( aGrid, aRow );
     delete aRow;
  }

  Grid_SetFixRows( aGrid, 1 );

  //����ColWidths[]
  for( int i=0; i<ColWidths->Count; i++ )
  {
    try
    {
      if( i>=aGrid->ColCount )
        break;
      aGrid->ColWidths[i] = StrToFloat( ColWidths->Strings[i] );
    }
    catch(Exception& e)
    {
    }
  }

  if( aHint!=NULL )
    aHint->SimpleText = "";
  if( aBar!=NULL)
       aBar->Position = 0;
}


TStrings* Grid_GetColWidths(TStringGrid* aGrid)
{
  TStrings* aStrings = new TStringList;
  if( aGrid==NULL )
    return aStrings;
  for( int i=0; i<aGrid->ColCount; i++ )
    aStrings->Add( FloatToStr( aGrid->ColWidths[i] ) );
  return aStrings;
}

void Grid_Clear( TStringGrid* aGrid )
{
  if( aGrid==NULL )
    return;

  aGrid->RowCount = aGrid->FixedRows;
  aGrid->ColCount = aGrid->FixedCols;

  for( int i=0; i<255; i++ )
    aGrid->Cols[i]->Text = "";
}

void  Grid_SetFixRows( TStringGrid* aGrid, int aCount )
{
  if( aGrid->RowCount > aCount )
    aGrid->FixedRows = aCount;
}

void Grid_SetRow(TStringGrid* aGrid, int aRow, TStrings* aStrings)
{
  if( aGrid==NULL || aStrings==NULL )
    return;

  aGrid->ColCount = Math::Max( aGrid->ColCount, aStrings->Count );
  aGrid->Rows[aRow]->Text = aStrings->Text;
}

void Grid_InsertRow(TStringGrid* aGrid, String aStr, String aSp)
{
  TStrings* aStrings = splitToStrings( aStr, aSp, false );
  Grid_InsertRow( aGrid, aStrings );
  delete aStrings;
}


void Grid_InsertRow(TStringGrid* aGrid, TStrings* aStrings)
{
  if( aGrid==NULL || aStrings==NULL )
    return;
  aGrid->ColCount = Math::Max( aGrid->ColCount, aStrings->Count );

  if( (aGrid->RowCount==aGrid->FixedRows+1) && IsNullStrings( aGrid->Rows[aGrid->RowCount-1] ) )
    aGrid->Rows[aGrid->RowCount-1]->Text = aStrings->Text;
  else
  {
    aGrid->Rows[aGrid->RowCount]->Text = aStrings->Text;
    aGrid->RowCount = aGrid->RowCount+1;
  }
}

bool IsNullStrings( TStrings* aStrings )
{
  if( aStrings==NULL )
    return true;

  for( int i=0; i<aStrings->Count; i++ )
  {
    if ( Trim(aStrings->Strings[i]) != "" )
      return false;
  }
  return true;
}

void SetControlCption( TControl* aControl, String aCaption )
{
  if( aControl->ClassNameIs("TStatusBar") )
     ((TStatusBar*)aControl)->SimpleText = aCaption;
  else if (  aControl->ClassNameIs("TPanel") )
    ((TPanel*)aControl)->Caption = aCaption;
  else
    throw Exception( "SetControlCption����δ���������" );
}






