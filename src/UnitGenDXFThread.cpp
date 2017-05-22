//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitGenDXFThread.h"
#include "UnitTool_ClassExtend.h"


#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall TGenDXFThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

//bSaveCat保存目录
__fastcall TGenDXFThread::TGenDXFThread(bool CreateSuspended,MAMProject* aProject,bool bSaveCat,String aCliFile)
        : TThread(CreateSuspended)
{
     fProject = aProject;

     fSaveCatalog = bSaveCat;

     fCliFile = aCliFile;
}
//---------------------------------------------------------------------------
void __fastcall TGenDXFThread::Execute()
{
    Synchronize(UpdateTreeNode);

}

//------------------------------------------------------------------------------
void __fastcall TGenDXFThread::UpdateTreeNode()
{
     //---- Place thread code here ----
     TStringList*  aFileStrings = new TStringList;
     aFileStrings->LoadFromFile(fCliFile);

     TStringList*  aSubFile = new TStringList;

     String  aLayerPath =  ProjectDirName(fProject->ProjectFileName) + "\\_Layer";
     DelDirFiles(aLayerPath);
     CheckAndMakeDirectory(aLayerPath);

     String aSingleCLiPath= ProjectDirName(fProject->ProjectFileName) + "\\_Cli";
     DelDirFiles(aSingleCLiPath);
     CheckAndMakeDirectory(aSingleCLiPath);

     for(int i=1; i < fProject->MainItems->Count; i++)
     {
           MLayerDataTreeNode* aItem = fProject->MainItems->Items[i];

           CopyStrings(aSubFile,aFileStrings,aItem->iBeginLine,aItem->iEndLine);

           //String aLayerEdgeFileName = aLayerPath+"\\Edge_Layer_"+ aItem->LayerNo +".dxf";

           String  aLayerFileName = aItem->ConvertCli2Dxf(aSubFile,aLayerPath); //填充线的文件
           aItem->DXFFileName = aLayerFileName;   //Layer_i_1.dxf;Layer_i_2.dxf;Layer_i_3.dxf

           String aSingleCLiFileName = aSingleCLiPath + "\\Cli_"+aItem->LayerNo +".dat";
           aSubFile->SaveToFile(aSingleCLiFileName);

           aSubFile->Clear();

           gError->WarnAdd1_Percent("正在生成节点打印文件,请稍后!",i,fProject->MainItems->Count);
    }
    delete aSubFile;
    delete aFileStrings;

    if(fSaveCatalog)
         fProject->SaveCatalogStruct();
}
//---------------------------------------------------------------------------
