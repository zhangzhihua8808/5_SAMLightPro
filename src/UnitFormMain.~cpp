//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "UnitFormMain.h"
#include "UnitFormPMac.h"
#include "UnitTool_ClassExtend.h"
#include "UnitFormSamLight.h"
#include "UnitNewProject.h"
#include "UnitOpenProject.h"
#include "UnitModelLoad.h"
#include "UnitFormLaserSetting.h"
#include "UnitFormMechConfig.h"
#include "UnitTestInstance.h"
#include "UnitFormGY.h"
#include <stdio.h>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMain *FormMain;

int   CurrentIndex = 0;
int   aStep=0;   //当前的阶段
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
        : TForm(Owner)
{
    //Com软件的连接
    fProject = new MAMProject;
    fProject->LayersDataHolder = TreeView1;
    fProject->LayerDataSelect =  CBox_LayerDatas;
    fProject->CurLayerDataItem = NULL;

    m_pGLView = new CGLView();

    GasStatus->Visible = false;

    fConfigVars = new MConfigVars;
    fConfigVars->LoadFromFile(ApplicationPath() + "\\MechConfig.txt");

    CheckAndMakeDirectory(ApplicationPath() + "\\Temp");
}
//---------------------------------------------------------------------------
TStatusPanel* TFormMain::readSamStatusPanel()
{
    return  StatusBar1->Panels->Items[0];
}

TStatusPanel* TFormMain::readPmacStatusPanel()
{
    return  StatusBar1->Panels->Items[1];
}

//------------------------------------------------------------------------------
void __fastcall TFormMain::A_OpenProjectExecute(TObject *Sender)
{
    //提示，关闭当前工程
    if( IsCanCloseProject()== false )  return;

    FormOpenProject->Init(fProject);
    if(FormOpenProject->ShowModal() == false)  return;

    Project->LoadLayerDataItemsFromFile();
}

//---------------------------------------------------------------------------
void __fastcall TFormMain::A_CloseProjectExecute(TObject *Sender)
{
    CloseProject();
}

//---------------------------------------------------------------------------
void __fastcall TFormMain::A_ExitSystemExecute(TObject *Sender)
{
    //断开连接
    if(FormSamLight->IsConnected)
    {
       FormSamLight->SamLightDisConnect();   //断开
       FormSamLight->SamLightClose();        //关软件
    }
    if(FormPmac->IsOpened)
    {
       FormPmac->PMacClose();
    }

    CloseProject();
    Close();
}

//---------------------------------------------------------------------------
//新建工程
void __fastcall TFormMain::A_NewProjectExecute(TObject *Sender)
{
    //1、新建
    FormNewProject->Init();
    if(FormNewProject->ShowModal() != mrOk)  return;

    //2、先关闭已经打开的工程
    if(IsCanCloseProject() == false)   return;

    //全路径,"工程目录"
    Project->SetPrjInformation(FormNewProject->ProjectFileName,FormNewProject->ProjectName);
    InsertCatalogNode(NULL, Project->ProjectName,"0");  //根节点

    Project->SaveCatalogStruct();   //to XXX.tree;
}

//插入目录节点
MLayerDataTreeNode*  TFormMain::InsertCatalogNode(MLayerDataTreeNode*  aParentDM,
                                          String aNodeName,String aType)
{
    if(Project->ProjectFileName == "")
            throw Exception("请先打开工程或新建工程");

    MTreeNodes_LayerData*  aMainItems = Project->MainItems;
    //申请一个ID
    int aMaxID = StrToInt(aMainItems->MaxID);
    aMainItems->MaxID = IntToStr(aMaxID + 1);

    MLayerDataTreeNode* aItem = aMainItems->NewLayerData_AT(IntToStr(aMaxID),
                      aNodeName,aType,"",0,"","");
    //树
    TTreeView*  aTree = TreeView1;
    if(aParentDM == NULL) //根节点
    {
         TTreeNode* aNewNode = aTree->Items->Add(NULL,aItem->NodeName);
         aNewNode->Data = (void*)aItem;
         aNewNode->ImageIndex = 0;
         aNewNode->SelectedIndex = 0;
         aItem->TreeNode = aNewNode;
         aItem->ParentName = "";
    }
    else //子节点
    {
        if(aParentDM->TreeNode == NULL)
              throw Exception("aParentDM->TreeNode == NULL");
        TTreeNode*  aNewNode = aTree->Items->AddChild(aParentDM->TreeNode,aItem->NodeName);
        aNewNode->Data = (void*)aItem;
        aItem->TreeNode = aNewNode;
        aNewNode->ImageIndex = 1;
        aNewNode->SelectedIndex = 1;

        if(aParentDM->TreeNode->Data != NULL)
        {
            MLayerDataTreeNode* aData = (MLayerDataTreeNode*)(aParentDM->TreeNode->Data);
            aItem->ParentName = aData->LayerDataID;
        }
    }
    aTree->FullExpand();
    return aItem;
}

//-------
bool TFormMain::IsCanCloseProject()
{
    CloseProject();
    return true;
}

//---------------------------------------------------------------------------
void __fastcall TFormMain::FormResize(TObject *Sender)
{
    ModelShow->Width = ModelShow->Height;                                       //让模型显示窗口为正方形

    m_pGLView->Resize(ModelShow->Width,ModelShow->Height);
}
//---------------------------------------------------------------------------
//双击Title的相应问题;
void TFormMain::WMNCLButtonDblClk(TMessage& Msg)
{
    if(WindowState == wsMaximized)
          return;
}

void __fastcall TFormMain::FormShow(TObject *Sender)
{
     Caption = "SLM科技软件有限公司 V1.0";

     //1、OpenGL有关的函数
     OpenGLWindowInit();

     //2、状态显示
     FormSamLight->StatusPanel = SamStatusPanel;
     FormSamLight->OperatePanel = StatusBar1->Panels->Items[2];
     FormPmac->StatusPanel = PMacStatusPanel;

     //自动打印控制
     BitBtn1->Enabled = true;
     BitBtn2->Enabled = false;
     BitBtn3->Enabled = false;
     state = stop;
     ScanState = stop;

     //3、信息调试
     String  aDebug = gIniFile->ReadString("SamLight","MemoShow","false");
     if(aDebug.UpperCase() == "TRUE")
     {
         Memo2->Visible = true;
     }
     else
         Memo2->Visible = false;

     gError->Memo = Memo2;
     gError->Memo->Clear();
     gError->StatusPanel = StatusBar1->Panels->Items[2];
     gError->StatusBar = this->StatusBar1;
     this->ComboBox2->ItemIndex = 0;



    //6、显示激光笔的信息
    /*   在排版布局中，设置功率信息，尝试动态设置Pen
    FormLaserSetting->LaserPens->ToComboBox(ComBox_Power);
    if(ComBox_Power->Items->Count > 0)
    {
        ComBox_Power->ItemIndex = 0;
        DoComboBoxChange(GetSelectedLaserPen(ComBox_Power));
    }
    FormLaserSetting->LaserPens->ToComboBox(this->ComboBox3);
    if(ComboBox3->Items->Count > 0)
    {
        ComboBox3->ItemIndex = 1;
        DoComboBoxEdgeChange(GetSelectedLaserPen(ComboBox3));
    }
    */

    //隐藏
    if(this->TreeView1->Items->Count <=0)
    {
        SetOnlyPageControlVis(TabSheet5,true,true);
    }

    //4、先执行一个默认连接，如果失败，再手动连接，如果再失败，退出
    if (FormSamLight->IsConnected == false)
     {
        FormSamLight->SamLightConnect();
        if(FormSamLight->IsConnected == false)
        {
            throw Exception("振镜控制卡连接失败(IP:" + FormSamLight->IP + ",Port:" + FormSamLight->Port +")");
        }
    }

    //5、PMAC连接
    String  aFirstGearPos = gIniFile->ReadString("MechConfig","FirstGearPos","454");
    FormPmac->FirstGearPos = StrToFloat(aFirstGearPos);
    if(FormPmac->IsOpened == false)
    {
        FormPmac->PMacOpen();
        if(FormPmac->IsOpened == false)
        {
            throw Exception("PMAC运动控制卡打开失败!");
        }
    }

    //开关量Button文本初始化
    SwitchButtonTextInit();

}

void  TFormMain::OpenGLWindowInit()
{
     m_pGLView->hWnd = this->ModelShow->Handle;
     String aWindowRangel = gIniFile->ReadString("Project","WindowRange","150");
     String aWorkArea = gIniFile->ReadString("Project","WorkArea","125");
     m_pGLView->SetupGLContext();
     m_pGLView->WindowRange = StrToFloat(aWindowRangel);
     m_pGLView->WorkArea = StrToFloat(aWorkArea);
     m_pGLView->Resize(ModelShow->Width,ModelShow->Height);
}

void  TFormMain::SetButtonImage(TBitBtn* aButton,String  aImageFileName,String aText)
{
    if(FileExists(aImageFileName) == true)
    {
       aButton->Glyph = NULL;   //清Old
       aButton->Glyph->LoadFromFile(aImageFileName);
       aButton->Text = aText;
    }
}

void  TFormMain::SetCurrentStatus(TBitBtn* aButton,TShape* aShape,bool  bRun, String aText)
{
    if(bRun)
    {
        aShape->Brush->Color = clGreen;
        aButton->Text = aText;
    }
    else
    {
        aShape->Brush->Color = clRed;
        aButton->Text = aText;
    }
}


void  TFormMain::SwitchButtonTextInit()
{
    //根据变量值设置文本
    MConfigVar* aItem = ConfigVars->FindItemByName("变量","照明开");
    String  aValue = FormPmac->GetVarValueTrimCRLF(aItem->ConfigVarKey);
    String  aFilePath =  ApplicationPath() + "\\resource";
    if(aValue == "1")
    {
        SetButtonImage(BitBtn13,aFilePath+"\\BULBON.BMP","照明关");
        //BitBtn13->Text = "照明关";
    }
    else
    {
        SetButtonImage(BitBtn13,aFilePath+"\\BULBOFF.BMP","照明开");
        //BitBtn13->Text = "照明开";
    }

    aItem = ConfigVars->FindItemByName("变量","门锁开");
    aValue = FormPmac->GetVarValueTrimCRLF(aItem->ConfigVarKey);
    if(aValue == "1")
    {
        SetButtonImage(BitBtn17,aFilePath+"\\DOOROPEN.BMP","门锁关");
        //BitBtn17->Text = "门锁关";
    }
    else
    {
        SetButtonImage(BitBtn17,aFilePath+"\\DOORSHUT.BMP","门锁开");
        //BitBtn17->Text = "门锁开";
    }

    /*
    aItem = ConfigVars->FindItemByName("变量","出激光");
    aValue = FormPmac->GetVarValueTrimCRLF(aItem->ConfigVarKey);
    if(aValue == "1")
           BitBtn18->Text = "关激光";
    else
           BitBtn18->Text = "出激光";
    */

    //激光器上电
    aValue = FormPmac->GetVarValueTrimCRLF("m4001");
    if(aValue == "0")
    {
        SetCurrentStatus(BitBtn6,Shape3,false,"激光器上电");
        //BitBtn6->Text = "激光器上电";
    }
    else
    {
        SetCurrentStatus(BitBtn6,Shape3,true,"激光器断电");
        //BitBtn6->Text = "激光器断电";
    }

    //伺服上电
    aItem = ConfigVars->FindItemByName("变量","伺服上电");
    aValue = FormPmac->GetVarValueTrimCRLF(aItem->ConfigVarKey);
    if(aValue == "0")
    {
        SetCurrentStatus(BitBtn16,Shape2,false,"伺服上电");
        //BitBtn16->Text = "伺服上电";
        ButtonEnableBySifu(false);
    }
    else
    {
        SetCurrentStatus(BitBtn16,Shape2,true,"伺服断电");
        //BitBtn16->Text = "伺服断电";
        ButtonEnableBySifu(true);
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::A_LoadCLIFileExecute(TObject *Sender)
{
     LoadModelFileToTreeNode(GetSelectedLayerDataItem(TreeView1));
}

void TFormMain::LoadModelFileToTreeNode(MLayerDataTreeNode* aDMNode)
{
     if(aDMNode == NULL)  return;
     if(aDMNode->Type != "0")   //不是跟节点
     {
        gError->Warn("系统感知错误,不是根节点!");
        return;
     }

     String  aInitFile;

     if(aDMNode->CLIFileName == "")
           aInitFile = "";
     else
           aInitFile = Project->ProjectLocation + "\\" + aDMNode->CLIFileName;

     FormLoadModel->Init(aInitFile);
     if(FormLoadModel->ShowModal() != mrOk)  return;

     String  aFileName = ExtractFileName(FormLoadModel->ModelFileName);
     CopyFileAlways(FormLoadModel->ModelFileName,Project->ProjectLocation + "\\" + aFileName);
     aDMNode->CLIFileName = aFileName;                                       //只有文件名

     Project->ModelFile_PreProcess(aDMNode,FormLoadModel->ModelFileName);    //加载并显示

}
//---------------------------------------------------------------------------
void __fastcall TFormMain::TreeView1CustomDrawItem(TCustomTreeView *Sender,
      TTreeNode *Node, TCustomDrawState State, bool &DefaultDraw)
{
     if( Node == Sender->Selected)
         Sender->Canvas->Brush->Color = clBlue;
     DefaultDraw = true;
}

//---------------------------------------------------------------------------
void  TFormMain::CloseProject()
{
    fProject->ProjectFileName = "";

    fProject->MainItems->Clear();
    this->TreeView1->Items->Clear();
    fProject->CurLayerDataItem = NULL;

    //隐藏
    if(this->TreeView1->Items->Count <=0)
    {
        SetOnlyPageControlVis(TabSheet5,true,true);
    }

    m_pGLView->CurDrawLayer = NULL;
}

//弹出式菜单
void __fastcall TFormMain::TreeView1ContextPopup(TObject *Sender,
      TPoint &MousePos, bool &Handled)
{
    TTreeNode*  aNode = TreeView1->GetNodeAt(MousePos.x,MousePos.y);
    if(aNode != NULL)
    {
        TreeView1->Selected = aNode;   //选中
        ProcessPopMenu(GetSelectedLayerDataItem(TreeView1));
    }
    else
    {
        Handled = true;  //不弹出菜单
    }
}

//---------------------------------------------------------------------------
void  TFormMain::ProcessPopMenu(MLayerDataTreeNode* aDMNode)
{
    if(aDMNode == NULL || aDMNode->TreeNode == NULL)
         return;

    TTreeView*  aTV = (TTreeView*)aDMNode->TreeNode->TreeView;
    if(aTV == NULL)  return;

    if(aDMNode->Type == "0")  //根节点
    {
        aTV->PopupMenu->Items->Items[0]->Enabled = true;
    }
    else
    {
        aTV->PopupMenu->Items->Items[0]->Enabled = false;
    }
}
void __fastcall TFormMain::TreeView1Click(TObject *Sender)
{
    DoClickTreeNode(GetSelectedLayerDataItem(TreeView1));
}
//---------------------------------------------------------------------------
void  TFormMain::DoClickTreeNode(MLayerDataTreeNode* aDMNode)
{
    if(aDMNode == NULL)  return;

    try
    {
       TabSheet3->TabVisible = true;
       TabSheet4->TabVisible = true;
    }
    catch(Exception& e)
    {
       TabSheet3->TabVisible = true;
       TabSheet4->TabVisible = true;
    }

    if(aDMNode->Type == "0")     //根节点
    {
        if(aDMNode->Items->Count <= 1)  return;     //只有一个跟节点

        try
        {
            PageControl2->ActivePage = this->TabSheet3;  //自动模式

            //显示
            //PartMinX = FloatToStr(Project->PartMinX);
            //PartMaxX = FloatToStr(Project->PartMaxX);
            //PartMinY = FloatToStr(Project->PartMinY);
            //PartMaxY = FloatToStr(Project->PartMaxY);
            //PartMinZ = FloatToStr(Project->PartMinZ);
            //PartMaxZ = FloatToStr(Project->PartMaxZ);

            //PartRotateX = FloatToStr(Project->PartMiddleX);
            //PartRotateY = FloatToStr(Project->PartMiddleY);

            Edit7->Text = IntToStr(aDMNode->Items->Count -1);             //总层数
            //绘制
            Project->CurLayerDataItem = aDMNode;
            m_pGLView->CurDrawLayer = aDMNode;
        }
        catch(Exception& e)
        {
        }
    }
    else   //不是跟节点
    {
        PageControl2->ActivePage = this->TabSheet4;  //手动模式

        if(aDMNode->NodeName == "第 "+ IntToStr(1) + " 层轮廓")
             BitBtn5->Enabled = true;
        else
             BitBtn5->Enabled = false;

        StringsControl_SetItem(CBox_LayerDatas,aDMNode->NodeName);
        ComBoxChange(GetSelectedLayerData(CBox_LayerDatas));
    }
}

//------------------------------------------------------------------------------
void __fastcall TFormMain::CBox_LayerDatasChange(TObject *Sender)
{
    ComBoxChange(GetSelectedLayerData(CBox_LayerDatas));
}
//---------------------------------------------------------------------------
void  TFormMain::ComBoxChange(MLayerDataTreeNode* aDMNode)
{
    if(aDMNode == NULL) return;

    //加载数据
    String aCliFileName = Project->ProjectLocation + "\\_Cli\\" + aDMNode->CLIFileName;
    TStringList* aFile = new TStringList;
    aFile->LoadFromFile(aCliFileName);
    aDMNode->ProcessCliData(aFile);
    //显示
    Project->CurLayerDataItem = aDMNode;
    m_pGLView->CurDrawLayer = aDMNode;

    if(aDMNode->NodeName == "第 "+ IntToStr(1) + " 层轮廓")
             BitBtn5->Enabled = true;
        else
             BitBtn5->Enabled = false;

    //层厚=高度/层号
    double  aThick = StrToFloat(aDMNode->AbsoluteHeight) / StrToInt(aDMNode->LayerDataID);
    LayerThick = FloatToStr(aThick);
    Edit_Z_DownDz->Text = FloatToStr(aThick);  //默认值

    //层尺寸
    LayerSize = FloatToStr(aDMNode->SizeX) + " X " + FloatToStr(aDMNode->SizeY);
    LayerMinX = aDMNode->MinX;
    LayerMaxX = aDMNode->MaxX;
    LayerMinY = aDMNode->MinY;
    LayerMaxY = aDMNode->MaxY;

    aDMNode->PartDatas_All->ToListView(this->ListView1);
}

void TFormMain::DoComboBoxChange(MLaserPen* aItem)
{
/*
    if(aItem == NULL) return;

    this->Edit2->Text = aItem->PenPower;
    this->Edit11->Text = aItem->PenSpeed;
*/
}

void TFormMain::DoComboBoxEdgeChange(MLaserPen* aItem)
{
/*
    if(aItem == NULL) return;

    this->Edit3->Text = aItem->PenPower;
    this->Edit4->Text = aItem->PenSpeed;
*/
}

//----------------------------------单层----------------------------------------
//厚度
void  TFormMain::writeThick(String aThick)
{
    Edit_LayerThick->Text = aThick;
}

void  TFormMain::writeSize(String aSize)
{
    Edit_LayerSize->Text = aSize;
}

void  TFormMain::writeMinX(String aMinX)
{
    Edit_XMin->Text = aMinX;
}
void  TFormMain::writeMaxX(String aMaxX)
{
    Edit_XMax->Text = aMaxX;
}
void  TFormMain::writeMaxY(String aMaxY)
{
     Edit_YMax->Text = aMaxY;
}
void  TFormMain::writeMinY(String aMinY)
{
     Edit_YMin->Text = aMinY;
}

//-----------------------------总体尺寸-----------------------------------------
void TFormMain::writePartMinX(String aMinX)
{
    //Edit_PartMinX->Text = aMinX;
}
void TFormMain::writePartMaxX(String aMaxX)
{
    //Edit_PartMaxX->Text = aMaxX;
}
void TFormMain::writePartMinY(String aMinY)
{
    //Edit_PartMinY->Text = aMinY;
}
void TFormMain::writePartMaxY(String aMaxY)
{
    //Edit_PartMaxY->Text = aMaxY;
}
void TFormMain::writePartMinZ(String aMinZ)
{
    //Edit_PartMinZ->Text = aMinZ;
}
void TFormMain::writePartMaxZ(String aMaxZ)
{
    //Edit_PartMaxZ->Text = aMaxZ;
}
void TFormMain::writePartMoveX(String aMoveX)
{
    //Edit_MoveX->Text = aMoveX;
}
void TFormMain::writePartMoveY(String aMoveY)
{
    //Edit_MoveY->Text = aMoveY;
}
void TFormMain::writePartScaleX(String aScaleX)
{
    //Edit_ScaleX->Text = aScaleX;
}
void TFormMain::writePartScaleY(String aScaleY)
{
    //Edit_ScaleY->Text = aScaleY;
}

void TFormMain::writePartRotateX(String aRotateX)
{
    //Edit_RotateX->Text = aRotateX;
}

void TFormMain::writePartRotateY(String aRotateY)
{
    //Edit_RotateY->Text = aRotateY;
}

String TFormMain::readPartMoveX()
{
    return "";//Edit_MoveX->Text;
}
String TFormMain::readPartMoveY()
{
    return "";//Edit_MoveY->Text;
}
String TFormMain::readPartScaleX()
{
    return "";//Edit_ScaleX->Text;
}
String TFormMain::readPartScaleY()
{
    return "";//Edit_ScaleY->Text;
}
//------------------------------------------------------------------------------
void __fastcall TFormMain::FormPaint(TObject *Sender)
{
    m_pGLView->RenderGLScene();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::FormDestroy(TObject *Sender)
{
    delete m_pGLView;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Timer1Timer(TObject *Sender)
{
    Timer1->Enabled = false;  //停止
    m_pGLView->RenderGLScene();

    Timer1->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Btn_MoveClick(TObject *Sender)
{
    //DoPartMove(StrToFloat(PartMoveX),StrToFloat(PartMoveY));
}

void TFormMain::DoPartMove(double  aPartMoveX,double aPartMoveY)
{
    //Project->DoMovePart(aPartMoveX,aPartMoveY);  //改变了数据
    //Project->SaveCatalogStruct();                //保存了Tree文件
    //Project->LoadLayerDatasFromFile(Project->CfgFileName);
    //DoClickTreeNode(GetSelectedLayerDataItem(TreeView1));

    //PartMoveX = "0";
    //PartMoveY = "0";
}

//---------------------------------------------------------------------------
void __fastcall TFormMain::Btn_ScaleClick(TObject *Sender)
{
   //整体缩放
   //DoPartScale(StrToFloat(PartScaleX),StrToFloat(PartScaleY));
}

void  TFormMain::DoPartScale(double aPartScaleX,double aPartScaleY)
{
    //Project->DoScalePart(aPartScaleX,aPartScaleY);  //改变了数据

    //Project->SaveCatalogStruct();                //保存了Tree文件
    //Project->LoadLayerDatasFromFile(Project->CfgFileName);
    //DoClickTreeNode(GetSelectedLayerDataItem(TreeView1));

    //PartScaleX = "1";
    //PartScaleY = "1";
}

//-------------------------伺服使能---------------------------------------------
//因伺服没有上电，禁止某些功能
void  TFormMain::ButtonEnableBySifu(bool   bRun)
{
    //轿厢
    this->BitBtn19->Enabled = bRun;
    this->BitBtn20->Enabled = bRun;
    this->BitBtn21->Enabled = bRun;
    //刮刀
    this->BitBtn22->Enabled = bRun;
    this->BitBtn23->Enabled = bRun;
    this->BitBtn24->Enabled = bRun;

    //刮粉
    this->BitBtn25->Enabled = bRun;

    //手动
    this->BitBtn5->Enabled = bRun;
    this->BitBtn4->Enabled = bRun;
    this->BitBtn28->Enabled = bRun;
}

//因伺服电机在运动，禁止某些功能
void  TFormMain::ButtonEnableBySifuMove(bool bRunBefore)
{
    if(bRunBefore)  //运行前
    {
        this->BitBtn6->Enabled = false;
    }
    else
    {
        this->BitBtn6->Enabled = true;
    }
}


//---------------------------------------------------------------------------
//Z轴找平
//激光器上电启动-----------OK
void __fastcall TFormMain::BitBtn6Click(TObject *Sender)
{
    if(BitBtn6->Text == "激光器上电")
    {
        MConfigVar* aItem = ConfigVars->FindItemByName("子程序","激光器上电");
        FormPmac->SendCommand(aItem);

        //BitBtn6->Text = "激光器断电";
        SetCurrentStatus(BitBtn6,Shape3,true,"激光器断电");
    }
    else if(BitBtn6->Text == "激光器断电")
    {
        MConfigVar* aItem = ConfigVars->FindItemByName("子程序","激光器断电");
        FormPmac->SendCommand(aItem);

        //BitBtn6->Text = "激光器上电" ;
        SetCurrentStatus(BitBtn6,Shape3,false,"激光器上电");
    }
}
//---------------------------------------------------------------------------
//伺服上电-----------------OK
void __fastcall TFormMain::BitBtn16Click(TObject *Sender)
{
     if(BitBtn16->Text == "伺服上电")
     {
        MConfigVar* aItem = ConfigVars->FindItemByName("变量","伺服上电");
        FormPmac->SendCommand(aItem);

        aItem = ConfigVars->FindItemByName("变量","黄指示灯关");
        FormPmac->SendCommand(aItem);

        //BitBtn16->Text = "伺服断电";
        SetCurrentStatus(BitBtn16,Shape2,true,"伺服断电");
        ButtonEnableBySifu(true);

     }
     else if(BitBtn16->Text == "伺服断电")
     {
        MConfigVar* aItem = ConfigVars->FindItemByName("变量","伺服断电");
        FormPmac->SendCommand(aItem);

        //BitBtn16->Text = "伺服上电";
        SetCurrentStatus(BitBtn16,Shape2,false,"伺服上电");
        ButtonEnableBySifu(false);
     }
}
//---------------------------------------------------------------------------
//照明
void __fastcall TFormMain::BitBtn13Click(TObject *Sender)
{
     String  aFilePath =  ApplicationPath() + "\\resource";
     if(BitBtn13->Text == "照明开")
     {
        MConfigVar* aItem = ConfigVars->FindItemByName("变量","照明开");
        FormPmac->SendCommand(aItem);

        //BitBtn13->Text = "照明关";
        SetButtonImage(BitBtn13,aFilePath+"\\BULBON.BMP","照明关");
     }
     else if(BitBtn13->Text == "照明关")
     {
        MConfigVar* aItem = ConfigVars->FindItemByName("变量","照明关");
        FormPmac->SendCommand(aItem);

        //BitBtn13->Text = "照明开";
        SetButtonImage(BitBtn13,aFilePath+"\\BULBOFF.BMP","照明开");
     }
}

//---------------------------------------------------------------------------
//门锁
void __fastcall TFormMain::BitBtn17Click(TObject *Sender)
{
     String  aFilePath =  ApplicationPath() + "\\resource";
     if(BitBtn17->Text == "门锁开")
     {
        MConfigVar* aItem = ConfigVars->FindItemByName("变量","门锁开");
        FormPmac->SendCommand(aItem);

        //BitBtn17->Text = "门锁关";
        SetButtonImage(BitBtn17,aFilePath+"\\DOOROPEN.BMP","门锁关");
     }
     else if(BitBtn17->Text == "门锁关")
     {
        MConfigVar* aItem = ConfigVars->FindItemByName("变量","门锁关");
        FormPmac->SendCommand(aItem);

        //BitBtn17->Text = "门锁开";
        SetButtonImage(BitBtn17,aFilePath+"\\DOORSHUT.BMP","门锁开");
     }
}

//---------------------------------------------------------------------------
void __fastcall TFormMain::BitBtn18Click(TObject *Sender)
{
     if(BitBtn18->Text == "出激光")
     {
        MConfigVar* aItem = ConfigVars->FindItemByName("变量","出激光");
        FormPmac->SendCommand(aItem);

        BitBtn18->Text = "关激光";
     }
     else if(BitBtn18->Text == "关激光")
     {
        MConfigVar* aItem = ConfigVars->FindItemByName("变量","关激光");
        FormPmac->SendCommand(aItem);

        BitBtn18->Text = "出激光";
     }
}

//机器配置(workarea,轿厢参数)
void __fastcall TFormMain::A_MechConfigExecute(TObject *Sender)
{
     FormMechConfig->Init();
     FormMechConfig->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::A_Mach_LaserExecute(TObject *Sender)
{
     FormLaserSetting->Init();
     FormLaserSetting->ShowModal();
     /*
     if(FormLaserSetting->ShowModal() == mrOk)
     {
         //显示激光笔的信息
        FormLaserSetting->LaserPens->ToComboBox(ComBox_Power);
        if(ComBox_Power->Items->Count > 0)
        {
            ComBox_Power->ItemIndex = 0;
            DoComboBoxChange(GetSelectedLaserPen(ComBox_Power));
        }
        FormLaserSetting->LaserPens->ToComboBox(this->ComboBox3);
        if(ComboBox3->Items->Count > 0)
        {
            ComboBox3->ItemIndex = 1;
            DoComboBoxEdgeChange(GetSelectedLaserPen(ComboBox3));
        }
     }
     */
}

//---------------------------------------------------------------------------
//轿厢（正向）
void __fastcall TFormMain::BitBtn19MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if(CheckBox1->Checked)  return; //增量模式

    //Z轴电机正向
    FormPmac->MotorJogInc(4);
}
//---------------------------------------------------------------------------
//轿厢(停止)
void __fastcall TFormMain::BitBtn19MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if(CheckBox1->Checked)  return; //增量模式

    FormPmac->MotorStop(4);
}

//---------------------------------------------------------------------------
void __fastcall TFormMain::BitBtn19Click(TObject *Sender)
{
    if(CheckBox1->Checked) //增量模式
    {
        int  iPos;
        try
        {
            iPos = StrToInt(this->Edit12->Text);
        }
        catch(Exception& e)
        {
            throw Exception(e.Message);
        }

        ButtonEnableBySifuMove(true);

        FormPmac->MotorRalateModeUntilFinish(4,iPos,"M440");

        ButtonEnableBySifuMove(false);
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::BitBtn20MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if(CheckBox1->Checked)  return; //增量模式

    FormPmac->MotorJobDec(4); //Z轴电机反向
}

//---------------------------------------------------------------------------

void __fastcall TFormMain::BitBtn20Click(TObject *Sender)
{
    if(CheckBox1->Checked) //增量模式
    {
        int  iPos;
        try
        {
            iPos = StrToInt(this->Edit12->Text);
        }
        catch(Exception& e)
        {
            throw new Exception(e.Message);
        }

        ButtonEnableBySifuMove(true);
        FormPmac->MotorRalateModeUntilFinish(4,iPos*(-1),"M440");
        ButtonEnableBySifuMove(false);
    }
}

//---------------------------------------------------------------------------
void __fastcall TFormMain::BitBtn21Click(TObject *Sender)
{
    ButtonEnableBySifuMove(true);
    FormPmac->MotorHomeUntilFinish(4);  //回0点
    ButtonEnableBySifuMove(false);
}

//---------------------------------------------------------------------------
void __fastcall TFormMain::BitBtn22Click(TObject *Sender)
{
    if(CheckBox2->Checked) //增量模式
    {
        int  iPos;
        try
        {
            iPos = StrToInt(this->Edit1->Text);
        }
        catch(Exception& e)
        {
            throw Exception(e.Message);
        }

        ButtonEnableBySifuMove(true);
        FormPmac->MotorRalateModeUntilFinish(3,iPos,"M340");
        ButtonEnableBySifuMove(false);
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::BitBtn22MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     if(CheckBox2->Checked)  return; //增量模式

    //Z轴电机正向
    FormPmac->MotorJogInc(3);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::BitBtn22MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     if(CheckBox2->Checked)  return; //增量模式

     FormPmac->MotorStop(3);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::BitBtn24Click(TObject *Sender)
{
    ButtonEnableBySifuMove(true);
    FormPmac->MotorHomeUntilFinish(3);  //回0点
    ButtonEnableBySifuMove(false);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::BitBtn23Click(TObject *Sender)
{
    if(CheckBox2->Checked) //增量模式
    {
        int  iPos;
        try
        {
            iPos = StrToInt(this->Edit1->Text);
        }
        catch(Exception& e)
        {
            throw Exception(e.Message);
        }

        ButtonEnableBySifuMove(true);
        FormPmac->MotorRalateModeUntilFinish(3,iPos*(-1),"M340");
        ButtonEnableBySifuMove(false);
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::BitBtn23MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if(CheckBox2->Checked)  return; //增量模式

    FormPmac->MotorJobDec(3); //Z轴电机反向
}
//---------------------------------------------------------------------------
//档位扑粉
void __fastcall TFormMain::BitBtn25Click(TObject *Sender)
{
    CBox_CycleTime->Enabled = false;
    ButtonEnableBySifuMove(true);

    for(int i=0; i < StrToInt(CBox_CycleTime->Text); i++)
    {
       FormPmac->SpreadPowder(TrackBar1->Position);
    }

    CBox_CycleTime->Enabled = true;
    ButtonEnableBySifuMove(false);
}


//Z轴电机下移
void __fastcall TFormMain::BitBtn4Click(TObject *Sender)
{
    float  iPos;
    try
    {
        iPos = StrToFloat(Edit_Z_DownDz->Text);
    }
    catch(Exception& e)
    {
        throw Exception(e.Message);
    }

    ButtonEnableBySifuMove(true);
    FormPmac->MotorRalateModeUntilFinish(4,iPos*(-1000),"M440");  //下降dz  //增量模式
    ButtonEnableBySifuMove(false);
}

//------------------------------------------------------------------------------
//手动落粉量
void __fastcall TFormMain::BitBtn28Click(TObject *Sender)
{
    ComboBox1->Enabled = false;

    ButtonEnableBySifuMove(true);
    for(int i=0; i < StrToInt(ComboBox1->Text); i++)
    {
        FormPmac->SpreadPowder(TrackBar2->Position);
    }
    ButtonEnableBySifuMove(false);

    ComboBox1->Enabled = true;
}
//---------------------------------------------------------------------------
//找平
void __fastcall TFormMain::BitBtn5Click(TObject *Sender)
{
    ButtonEnableBySifuMove(true);
    FormPmac->MotorHomeUntilFinish(4);
    ButtonEnableBySifuMove(false);

    String  ZInitHeight = gIniFile->ReadString("MechConfig","ZInitHeight","236");
    String  BasePanelThick = gIniFile->ReadString("MechConfig","BasePanelThick","18");


    ButtonEnableBySifuMove(true);
    FormPmac->MotorAbsoluteModeUntilFinish(4,
               (StrToFloat(ZInitHeight)-StrToFloat(BasePanelThick))*1000,"M440");
    ButtonEnableBySifuMove(false);

    CurrentIndex = 0;
}
//---------------------------------------------------------------------------

//下载并打印
void __fastcall TFormMain::BitBtn27Click(TObject *Sender)
{
    //全手动单层(新建任务，导入dxf,开激光，打印，关激光)
    if(ComboBox2->ItemIndex == 0)
    {
        DoPrintJob(GetSelectedLayerData(CBox_LayerDatas),true);
    }
    else if(ComboBox2->ItemIndex == 1)    //全自动单层(打印小方块,从找平开始执行(即找完平以后)：Z轴下降，铺粉，打印;
    {
       CurrentIndex = CBox_LayerDatas->ItemIndex;

       BitBtn4->Click();   //Z轴下降
       BitBtn28->Click();  //扑粉

       DoPrintJob(GetSelectedLayerData(CBox_LayerDatas),true);

       CurrentIndex++;
       if(CurrentIndex >= CBox_LayerDatas->Items->Count)
                return;

       StringsControl_SetItemIndex(CBox_LayerDatas,CurrentIndex);     //选择，更新
       ComBoxChange(GetSelectedLayerData(CBox_LayerDatas));
    }
    else  if(ComboBox2->ItemIndex == 2)  //焦平面实验
    {
       CurrentIndex = CBox_LayerDatas->ItemIndex;

       BitBtn4->Click();   //Z轴下降
       //BitBtn28->Click();  //不用扑粉

       DoPrintJob(GetSelectedLayerData(CBox_LayerDatas),true);

       CurrentIndex++;
       if(CurrentIndex >= CBox_LayerDatas->Items->Count)
                return;

       StringsControl_SetItemIndex(CBox_LayerDatas,CurrentIndex);     //选择，更新
       ComBoxChange(GetSelectedLayerData(CBox_LayerDatas));
    }
    else
       throw Exception("请先选择打印类型");
}

void  TFormMain::PrintJobByNo(int iNoJob)
{
/*
    double aMX,aMY;
    double aUnit = 10;

    if(iNoJob == -4)
    {
        aMX = 3 * aUnit;
        aMY = -3 * aUnit;
    }
    else if(iNoJob == -3)
    {
        aMX = 0;
        aMY = -3 * aUnit;
    }
    else if(iNoJob == -2)
    {
        aMX = -3 * aUnit;
        aMY = -3 * aUnit;
    }
    else if(iNoJob == -1)
    {
        aMX = 3 * aUnit;
        aMY = 0;
    }
    else if(iNoJob == 0)
    {
        aMX = 0;
        aMY = 0;
    }
    else if(iNoJob == 1)
    {
        aMX = -3 * aUnit;
        aMY = 0;
    }
    else if(iNoJob == 2)
    {
        aMX = 3* aUnit;
        aMY = 3 * aUnit;
    }
    else if(iNoJob == 3)
    {
        aMX = 0;
        aMY = 3 * aUnit;
    }
    else if(iNoJob == 4)
    {
        aMX = -3 * aUnit;
        aMY = 3 * aUnit;
    }

    DoPrintJob(GetSelectedLayerData(CBox_LayerDatas),true,aMX,aMY);
*/
}

void  TFormMain::DoPrintJob(MLayerDataTreeNode* aDMNode,bool  bOpenAndClose,double aMX,double aMY)
{
    throw Exception("功能敬请期待!");
/*
    if(aDMNode == NULL)
          throw Exception("所选择的层节点数据为空!");

    FormSamLight->OnNewJob();
    FormSamLight->ImportFile(aDMNode->DXFFileName,
                Project->ProjectLocation + "\\_Layer\\" + aDMNode->DXFFileName);

    FormSamLight->TranslateEntity(aDMNode->DXFFileName,aMX,aMY);

    if(bOpenAndClose)   //打开
    {
        MConfigVar* aItem = ConfigVars->FindItemByName("变量","出激光");
        FormPmac->SendCommand(aItem);
    }

    //选笔
    FormSamLight->SetPen(ComBox_Power->ItemIndex+1);

    //打印
    //FormSamLight->mark_entity(aDMNode->DXFFileName);

    if(bOpenAndClose)   //关闭
    {
        MConfigVar* aItem = ConfigVars->FindItemByName("变量","关激光");
        FormPmac->SendCommand(aItem);
    }
*/
}

//---------------------------------------------------------------------------
void  TFormMain::DoPrintJob(MLayerDataTreeNode* aDMNode,bool  bOpenAndClose)
{
    if(aDMNode == NULL)
          throw Exception("所选择的层节点数据为空!");

    //检查轿厢门是否上锁了
    MConfigVar* aItem = ConfigVars->FindItemByName("变量","门锁关");
    if(FormPmac->GetConfigVarValue(aItem) == 0)  //门锁开
          throw Exception("危险：请先给轿厢上锁!!!");


    TStrings* aTempStrList = splitToStrings_Mask( aDMNode->DXFFileName ,";");
    for(int i=0; i < aTempStrList->Count; i++)
    {
        String  aDXF = aTempStrList->Strings[i];

        double aLaserPower = aDMNode->PartDatas_All->Items[i]->LaserPower;
        double aLaserSpeed = aDMNode->PartDatas_All->Items[i]->LaserSpeed;

        if(aDMNode->PartDatas_All->Items[i]->FinishPrint == true)
            continue;

        FormSamLight->SetLaserPen(1,aLaserPower,aLaserSpeed,5000);

        FormSamLight->OnNewJob();
        FormSamLight->ImportFile(aDXF,
                    Project->ProjectLocation + "\\_Layer\\" + aDXF);

        if(bOpenAndClose)   //打开
        {
            MConfigVar* aItem = ConfigVars->FindItemByName("变量","出激光");
            FormPmac->SendCommand(aItem);
        }

        //选笔 delete
        //FormSamLight->SetPen(ComBox_Power->ItemIndex+1);

        //打印
        FormSamLight->mark_entity(aDXF);

        if(bOpenAndClose)   //关闭
        {
            MConfigVar* aItem = ConfigVars->FindItemByName("变量","关激光");
            FormPmac->SendCommand(aItem);
        }

        //设置完成标志
        aDMNode->PartDatas_All->Items[i]->FinishPrint = true;
    }
}

void __fastcall TFormMain::ComBox_PowerChange(TObject *Sender)
{
    //DoComboBoxChange(GetSelectedLaserPen(ComBox_Power));
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::Timer2Timer(TObject *Sender)
{
    Timer2->Enabled = false;

    //氧气量
    MConfigVar* aItem;

    //0阶段： 开始洗气
    EditO2->Text = FloatToStr(FormPmac->ReadO2Percent());
    //压力值
    Edit_Presure->Text =  FloatToStr(FormPmac->ReadPresureValue());

    //0阶段：洗气完成
    if(aStep==0 && FormPmac->ReadO2Percent() < 0.1)
    {
        aItem = ConfigVars->FindItemByName("变量","洗气结束");
        FormPmac->SendCommand(aItem);

        //开风机
        aItem = ConfigVars->FindItemByName("变量","开风机");
        FormPmac->SendCommand(aItem);

        aStep = 1;  //进入第1步

        ScanState = stop;
    }
    else if(aStep == 2 && FormPmac->ReadO2Percent() < 0.1)      //ready 信号
    {
        GasStatus->Brush->Color = clGreen;

        ScanState = ready;
    }
    else if(aStep == 2 && FormPmac->ReadO2Percent() > 0.1)    //出故障
    {
        GasStatus->Brush->Color = clRed;

        ScanState = stop;
    }


    //1阶段：舱室洗气阶段
    if(aStep == 1)
    {
        aItem = ConfigVars->FindItemByName("变量","洗气完成");
        String aValue = FormPmac->GetVarValueTrimCRLF(aItem->ConfigVarKey);
        if(aValue == "0")   //没有完成
        {
            gError->Warn("正在等待【洗气完成M4055】标志,还没有准备好!");
            GasStatus->Brush->Color = clRed;

            ScanState = stop;
        }
        else  //完成
        {
            gError->Warn("系统准备好!");
            aStep = 2;

            ScanState = stop;
        }
    }

    Timer2->Enabled = true;
}
//---------------------------------------------------------------------------
//开始洗气
void __fastcall TFormMain::N15Click(TObject *Sender)
{
    FormTestInstance->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::EditCycleTimeExit(TObject *Sender)
{
    try
    {
        StrToInt(EditCycleTime->Text);
    }
    catch(Exception& e)
    {
        EditCycleTime->Text = "1";
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ComboBox3Change(TObject *Sender)
{
    //DoComboBoxEdgeChange(GetSelectedLaserPen(ComboBox3));
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::BitBtn12Click(TObject *Sender)
{
    //二进制读写
    if(OpenDialog1->Execute() == mrOk)
    {
        String  aFileName = OpenDialog1->FileName;

        MAMProject* aProject = new MAMProject();

        String  aAscIIFileName = aProject->ConvertBinaryToAscIICLiFile(aFileName);

        //
        TestReadBinaryCLiFile(aFileName);
    }
}

void TFormMain::TestReadBinaryCLiFile(String aFileName)
{
    //1.打开二进制格式STL文件
    FILE *stream;

    //打开STL文件
    stream = fopen(aFileName.c_str(),"rb");
    if(stream == NULL)
    {
       throw Exception("打开文件错误");
    }

    //Header: 14*16+2
    //HeaderStart  14字节
    //Binary        9字节
    //

    //读取文件头
    char  Header[14*16+2];

    fread(Header,sizeof(char),sizeof(Header),stream);		//获取三角面片总数

    ProcessCLIHeader(Header);

    int iLayerNum = 7;
    MPolyLines*  aPolyLines = new MPolyLines();
    for(int i=0; i < iLayerNum; i++)
    {
        CliFileLayerRead(stream,aPolyLines);
    }
    //关闭文件
    fclose(stream);
}

void  TFormMain::CliFileLayerRead(FILE* stream,MPolyLines*  aPolyLines)
{
    unsigned short  aDataType;
    unsigned short  aZThick;
    unsigned short  aIsPolyLine;
    unsigned short  aPartID;
    unsigned short  aDir;
    unsigned short  aPathPointNum;
    unsigned short  aPointX;
    unsigned short  aPointY;

    int  aStep = 1;  //第一个阶段

    for(;;)
    {
       fread(&aDataType,sizeof(unsigned short),1,stream);

       if(aDataType == 128 && aStep == 2)              //退2个字节
       {
          fseek(stream,-2,SEEK_CUR);
          break;
       }
       else if(aDataType == 127 && aStep == 2)
       {
          fseek(stream,-2,SEEK_CUR);
          break;
       }
       else if(aDataType == 128)  //16位       Z
       {
          aStep = 2;    //下一个阶段

          fread(&aZThick,sizeof(unsigned short),1,stream);    //层高
       }
       else if(aDataType == 127)  //Real Z
       {
          aStep = 2;
       }
       else if(aDataType == 129)  //16位轮廓
       {
          MPolyLine* aPolyLine = aPolyLines->NewPolyLine();

          fread(&aPartID,sizeof(unsigned short),1,stream);    //层高
          fread(&aDir,sizeof(unsigned short),1,stream);       //方向
          fread(&aPathPointNum,sizeof(unsigned short),1,stream); //轮廓点个数

          for(int i=0; i < aPathPointNum; i++)
          {
              fread(&aPointX,sizeof(unsigned short),1,stream);       //点坐标
              fread(&aPointY,sizeof(unsigned short),1,stream);       //

              aPolyLine->Points->New2DPoint(aPointX,aPointY);
          }
       }
       else if(aDataType == 130)  //Real 轮廓
       {
           //MPolyLine* aPolyLine = aPolyLines->NewPolyLine();

       }
       else if(aDataType == 131)  //16位填充线
       {

       }
       else if(aDataType == 132)  //Real型填充线
       {
       }
    }

    //读层高

    if(aDataType == 128)  //16位的
    {
        fread(&aZThick,sizeof(unsigned short),1,stream);   //层高
    }
    else if(aDataType == 127) //Real型的Z 高
    {
    }

    //读轮廓
    fread(&aIsPolyLine,sizeof(unsigned short),1,stream);
    if(aIsPolyLine == 129)   //16位类型的轮廓
    {
    }
    else if(aIsPolyLine == 130)   //Real型轮廓
    {
    }


    //ProcessDataType(DataType,stream);
}

void TFormMain::ProcessCLIHeader(char Header[])
{
    //String  aStr = String(Header);
    //TStrings* aCliHeadeList = splitToStrings_Mask( aStr,"\n");

    //0 $$HEADERSTART
    //1 $$BINARY
    //2 $$UNITS/00000000.005000
    //3 $$VERSION/200
    //4 $$LABEL/1,part1
    //5 $$DATE/090317
    //6 $$DIMENSION/00000000.000000,00000000.000000,00000000.000000,00000010.000000,00000012.000000,00000009.742200
    //7 $$LAYERS/000007
    //8 $$HEADEREND
    //String  aFileFormat = aCliHeadeList->Strings[1];   //格式
}

//---------------------------------------------------------------------------
//读取二进制格式STL文件
/*
int TFormMain::OpenSTLByBinary(String STLFileName)
{
    //1.打开二进制格式STL文件
     FILE *stream;
     int TriTotalNum;		//三角面片总数

     //先清空
     this->m_Triangles->Clear();

     //打开STL文件
     stream = fopen(STLFileName.c_str(),"rb");
     if(stream == NULL)
     {
         return OpenFile_Error;
     }

     //3.读取该STL文件的三角面片信息
     float dValue[3],dNor[3];
     fseek(stream,80,SEEK_SET);
     fread(&TriTotalNum,sizeof(int),1,stream);		//获取三角面片总数

     MTriangle* tempTri;		//临时保存一个三角面片数据，将添加到m_Triangles中
     for(int i=0; i < TriTotalNum; i++)
     {
         tempTri = new MTriangle;

         //3.1 读取第i个三角面片的信息(法向量,三个顶点坐标)
	 fread(tempTri->Nor ,sizeof(float),3,stream);	                        //读取法向量
         fread(tempTri->vertex,sizeof(float),9,stream);                         //坐标
         fseek(stream,2,SEEK_CUR);					        //跳过两个字节

         m_Triangles->Add(tempTri);
     }

     //关闭文件
     fclose(stream);
     return OpenFile_Success;

/*
     MTriangle* tempTri = new MTriangle;		//临时保存一个三角面片数据，将添加到m_Triangles中
     MPnt* tempMaxPnt = new MPnt;		//临时记录该三角面片的最大、
     MPnt* tempMinPnt = new MPnt;		//最小坐标

     //打开STL文件
     stream = fopen(STLFileName.c_str(),"rb");
     if(stream == NULL)
     {
         return OpenFile_Error;
     }

     //3.读取该STL文件的三角面片信息
     float dValue[3],dNor[3];
     fseek(stream,80,SEEK_SET);
     fread(&TriTotalNum,sizeof(int),1,stream);		//获取三角面片总数

     for(int i=0; i < TriTotalNum; i++)
     {
         //3.1 读取第i个三角面片的信息(法向量,三个顶点坐标)
	 fread(dNor,sizeof(float),3,stream);	//读取法向量
         for (int j=0;j<3;j++)
         {
	     tempTri->Nor[j] = (double)dNor[j];
         }

         for (int j=0;j<3;j++)
         {						//读取三个坐标点
             fread(dValue,sizeof(float),3,stream);
	     tempTri->Pnt3P[j].x = dValue[0];
	     tempTri->Pnt3P[j].y = dValue[1];
	     tempTri->Pnt3P[j].z = dValue[2];
         }
	 fseek(stream,2,SEEK_CUR);					//跳过两个字节

         //3.2.搜索该三角面片的最值(即该三角面片占据的空间)
 	 if (tempTri->Pnt3P[0].x > tempTri->Pnt3P[1].x)   //Xmax,Xmin
         {
	      tempMaxPnt->x = tempTri->Pnt3P[0].x;
	      tempMinPnt->x = tempTri->Pnt3P[1].x;
         }
	 else
         {
	      tempMaxPnt->x = tempTri->Pnt3P[1].x;
	      tempMinPnt->x = tempTri->Pnt3P[0].x;
         }
	 if(tempTri->Pnt3P[2].x > tempMaxPnt->x) tempMaxPnt->x = tempTri->Pnt3P[2].x;
         if(tempTri->Pnt3P[2].x < tempMinPnt->x) tempMinPnt->x = tempTri->Pnt3P[2].x;

         if (tempTri->Pnt3P[0].y > tempTri->Pnt3P[1].y)    //Ymax,Ymin
         {
	      tempMaxPnt->y = tempTri->Pnt3P[0].y;
	      tempMinPnt->y = tempTri->Pnt3P[1].y;
         }
	 else
         {
	      tempMaxPnt->y = tempTri->Pnt3P[1].y;
	      tempMinPnt->y = tempTri->Pnt3P[0].y;
         }
	 if(tempTri->Pnt3P[2].y > tempMaxPnt->y) tempMaxPnt->y = tempTri->Pnt3P[2].y;
	 if(tempTri->Pnt3P[2].y < tempMinPnt->y) tempMinPnt->y = tempTri->Pnt3P[2].y;

	 if (tempTri->Pnt3P[0].z > tempTri->Pnt3P[1].z)    //Zmax,Zmin
         {
	      tempMaxPnt->z = tempTri->Pnt3P[0].z;
	      tempMinPnt->z = tempTri->Pnt3P[1].z;
         }
	 else
         {
	      tempMaxPnt->z = tempTri->Pnt3P[1].z;
	      tempMinPnt->z = tempTri->Pnt3P[0].z;
         }
	 if(tempTri->Pnt3P[2].z > tempMaxPnt->z) tempMaxPnt->z = tempTri->Pnt3P[2].z;
         if(tempTri->Pnt3P[2].z < tempMinPnt->z) tempMinPnt->z = tempTri->Pnt3P[2].z;

         //3.3填充当前三角面片的字段Vmax，Vmin(切片方向默认沿Z轴方向)
	 tempTri->Vmax = tempMaxPnt->z;
	 tempTri->Vmin = tempMinPnt->z;
	 //1:一个点最大；2：两个点相等最大；3：三点相同；
	 tempTri->TriPosType = 0;
	 for(int j=0;j<3;j++)
         {
             if(fabs(tempTri->Pnt3P[j].z - tempTri->Vmax)< Delta)
             {
	     	tempTri->TriPosType += 1;
	     }
         }

         m_Triangles->Add(tempTri);
         //5.搜索三角面片占据的空间
         if (i<1)  //第1个三角面片
         {
	     m_TriMax->Duplicate(tempMaxPnt);
             m_TriMin->Duplicate(tempMinPnt);
         }
	 else
         {				//第i个三角面片
	     if (tempMaxPnt->x > m_TriMax->x)	//X
		    m_TriMax->x = tempMaxPnt->x;
	     if (tempMinPnt->x < m_TriMin->x)
		    m_TriMin->x = tempMinPnt->x;
	     if (tempMaxPnt->y > m_TriMax->y)	//Y
		    m_TriMax->y = tempMaxPnt->y;
	     if (tempMinPnt->y < m_TriMin->y)
		    m_TriMin->y = tempMinPnt->y;
	     if (tempMaxPnt->z > m_TriMax->z)	//Z
	            m_TriMax->z = tempMaxPnt->z;
	     if (tempMinPnt->z < m_TriMin->z)
		    m_TriMin->z = tempMinPnt->z;
         }
     }
     //关闭文件
     fclose(stream);
     return OpenFile_Success;
*/
//}

//样件工艺设计
void __fastcall TFormMain::N5Click(TObject *Sender)
{
    FormGYDesign->Init();
    FormGYDesign->ShowModal();

    gError->StatusBar = this->StatusBar1;
}

//---------------------------------------------------------------------------
//自动打印功能
//这个可以从所选的层开始
//这个要先下降Z轴
void __fastcall TFormMain::BitBtn1Click(TObject *Sender)
{
     //有可以打印的层
     if(CBox_LayerDatas->Items->Count == 0)  return;
     if(ScanState != ready)
          throw Exception("系统还没有达到可打印的状态!");

     //获取打印的层
     CurrentIndex = CBox_LayerDatas->ItemIndex;
     if(CurrentIndex == -1)
          throw Exception("请先选择打印的起始层");

     this->BitBtn1->Enabled = false;  //禁止点击开始了
     this->BitBtn2->Enabled = true;
     this->BitBtn3->Enabled = true;

     state = running;
     this->Timer3->Enabled = true;  //启动
}
//---------------------------------------------------------------------------
//用于自动打印
void __fastcall TFormMain::Timer3Timer(TObject *Sender)
{
     Timer3->Enabled = false;    //先暂停

     if(ScanState != ready)  //出故障了
           state = stop;

     if(state == running)
     {
          //就要打印了
          StringsControl_SetItemIndex(CBox_LayerDatas,CurrentIndex);     //选择，更新
          ComBoxChange(GetSelectedLayerData(CBox_LayerDatas));

          //1次扑粉操作
          BitBtn4->Click();   //Z轴下降
          BitBtn28->Click();  //扑粉

          DoPrintJob(GetSelectedLayerData(CBox_LayerDatas),true);

          CurrentIndex++;
          if(CurrentIndex == CBox_LayerDatas->Items->Count)  //打印完了
          {
              state = stop;
              Timer3->Enabled = false;
          }
          else
              Timer3->Enabled = true;
     }
}
//---------------------------------------------------------------------------
/*
    MConfigVar* aItem = ConfigVars->FindItemByName("变量","出激光");
    FormPmac->SendCommand(aItem);

    for(int i=1; i < Project->MainItems->Count; i++)
    {
        MLayerDataTreeNode* aItem = Project->MainItems->Items[i];

        aItem->TreeNode->Selected = true;
        DoPrintJob(aItem,false);
    }

    //关闭
    aItem = ConfigVars->FindItemByName("变量","关激光");
    FormPmac->SendCommand(aItem);
*/

//暂停，继续
void __fastcall TFormMain::BitBtn2Click(TObject *Sender)
{
    if (BitBtn2->Text == "暂停")
    {
         Timer3->Enabled = false;
         state = pause;

         BitBtn2->Text = "继续";
    }
    else  //继续
    {
         if(ScanState != ready)
               throw Exception("系统还没有达到可打印的状态!");

         Timer3->Enabled = true;
         state = running;

         BitBtn2->Text = "暂停";
         BitBtn2->Enabled = true;
    }
}
//---------------------------------------------------------------------------
//停止
void __fastcall TFormMain::BitBtn3Click(TObject *Sender)
{
     Timer3->Enabled = false;

     state = stop;

     BitBtn1->Text = "开始";
     BitBtn1->Enabled = true;
     BitBtn2->Text = "暂停";
     BitBtn2->Enabled = false;
     BitBtn3->Enabled=false;     //停止
}
//---------------------------------------------------------------------------
//开始洗气
void __fastcall TFormMain::BitBtn7Click(TObject *Sender)
{
    //1、开关电磁阀
    //关氮气
    MConfigVar* aItem = ConfigVars->FindItemByName("变量","氮气1号电磁阀关");
    FormPmac->SendCommand(aItem);
    aItem = ConfigVars->FindItemByName("变量","氮气3号电磁阀关");
    FormPmac->SendCommand(aItem);

    //开氩气
    aItem = ConfigVars->FindItemByName("变量","氩气2号电磁阀开");
    FormPmac->SendCommand(aItem);
    aItem = ConfigVars->FindItemByName("变量","氩气4号电磁阀开");
    FormPmac->SendCommand(aItem);

    //开混合气体
    aItem = ConfigVars->FindItemByName("变量","汇合气体5号电磁阀开");
    FormPmac->SendCommand(aItem);

    //2、开始洗气
    aItem = ConfigVars->FindItemByName("变量","洗气开始");
    FormPmac->SendCommand(aItem);

    GasStatus->Visible = true;
    GasStatus->Brush->Color = clRed;

    //Button4->Enabled = false;

    aStep = 0;

    //启动定时器监控
    Timer2->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::BitBtn8Click(TObject *Sender)
{
      //关氩气
    MConfigVar* aItem = ConfigVars->FindItemByName("变量","氩气2号电磁阀关");
    FormPmac->SendCommand(aItem);
    aItem = ConfigVars->FindItemByName("变量","氩气4号电磁阀关");
    FormPmac->SendCommand(aItem);


    //开氮气
    aItem = ConfigVars->FindItemByName("变量","氮气1号电磁阀开");
    FormPmac->SendCommand(aItem);
    aItem = ConfigVars->FindItemByName("变量","氮气3号电磁阀开");
    FormPmac->SendCommand(aItem);

    //开混合气体
    aItem = ConfigVars->FindItemByName("变量","汇合气体5号电磁阀开");
    FormPmac->SendCommand(aItem);

    aItem = ConfigVars->FindItemByName("变量","风机关闭");
    FormPmac->SendCommand(aItem);

    aStep = 0;

    Timer2->Enabled = false;
}
//---------------------------------------------------------------------------

