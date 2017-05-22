//---------------------------------------------------------------------------

#ifndef UnitProeEngineH
#define UnitProeEngineH

#include "UnitTool_Class.h"

class MProeEngine;
extern MProeEngine* gProeEngine;

extern int G_CheckedNo;
extern int G_CheckedNum;

extern MProeEngine* G_ProeEngine;              //访问PROE的引擎

class MProFrame;
class MProFrames;
class MPartFrame;
class MPartFrames;



//---------------FrameChange----20121226--from--邵老师---臧霖整理------------
class MProFrame;
class MProFrames;
class MPartFrame;
class MPartFrames;
class MParaList;
class MDoubleList;
//---------------FrameChange----end--------

//------------------ Functions ----------------------------------------------

void UpdateProeModelParas( String aFileName, MParaList* aParas );
TStrings* GetProeParaStrings( String aFileName );
String KeyItem( String aKeyStr, String aItem );

//-------------------MProFrame--------------------------------------------------

//from 邵老师20121226  臧霖整理
//*.fra文件的解析

class MProFrame : public MObject
{
  public:
    MPartFrames* PartFrames;
  public:
    TStrings* PartNameList();
    String PartNameList_Str();

  public:
    MProFrame();
    ~MProFrame();
  public:
    void ReadFrame(TStrings* aStrings);
  public:
    void RelMatrixToAbsMatrix();  

  public:
  
   //传递组件单位信息--------臧霖---20130102---
    bool FrameIsModelUnitMmns;
};


class MProFrames : public MObjectList_Temp<MProFrame>
{
  public:
    TStrings* FraStrings;

  public:
    String ModelFileName;
    String FraFileName;

  public:
    int CurFrame;
    int AnimationSpeed;

  public:
    bool AnimationPause;                       //控制动画播放的暂停变量------------------臧霖--------20120105

  public:
    String PptName;                            //为了让每个动画的fra文件名字不同，以免发布的时候相互覆盖----臧霖---20130321

//  public:
//    bool FramesIsModelUnitMmns;                //判断模型单位类型-------臧霖--------20120102

  public:
    TStrings* FrameNameList();
    String FrameNameList_Str();
  public:
    MProFrames();
    //~MProFrames();

  public:
    void ReadFraFromFile( String aFileName );
    void ReadFraFromStrings( TStrings* aStrings );


  //记录总的帧数和总的零件数用来控制循环-----臧霖----20120102

  public:
    int TotalFrames();       //int IntTotalFrames;
    int TotalParts();        //int IntTotalParts;


  //用数零件数的方法读取零件总数---------臧霖--------20130322
  //public:
    //int ReadTotalPartNum( TStrings* aStrings );




  public:
    void RelMatrixToAbsMatrix();

};

class MPartFrames : public MObjectList_Temp<MPartFrame>
{
};

class MPartFrame : public MObject
{
  public:
    double Matrix[4][4];
  public:
    void ReadFrame(TStrings* aStrings);
  public:
    TStrings* MatrixList();
    String MatrixList_Str();

  public:
    MPartFrame();
//修改矩阵成网页中可用的文件----------臧霖-----20121231
  public:
    bool PartFrameIsModelUnitMmns;
    void ChangeMmnsInToWeb(double Matrix[4][4]);
    void ChangeInksInToMmns(double Matrix[4][4]);
//    double ChangeAsmToPvs(double MatrixNum);
    void ChangeMatrixLast(double Matrix[4][4]);

  public:
    String PartName;
    String MatrixString();

    //-----------PVS里的MatrixString--------臧霖----------20130410
  public:
    //String PvsMatrixString;

};


//----------------------- CsNode --------------------------------------------

class MNodeInfo : public MObject
{
  public:
    String NodeType;                   //CsNode的类型
    String Key;
    String Info;
  public:
    MNodeInfo();
};

class MComponentNodeInfo : public MNodeInfo
{
  public:
    MComponentNodeInfo();
};

class MCsNodeInfo : public MNodeInfo
{
  public:
    String UdfKey;                     //放置在Cs上的UdfKey
  public:
    MCsNodeInfo();
};

MNodeInfo* NodeInfo( TTreeNode* aNode );
String NodeKeyStr( TTreeNode* aNode );
String NodeType( TTreeNode* aNode );

MCsNodeInfo* CsNodeInfo( TTreeNode* aNode );
String CsNodeUdfKey( TTreeNode* aNode );
void CsNodeSetUdfKey( TTreeNode* aNode, String aUdfKey );

//void SetNodeInfo( TTreeNode* aNode, String aNodeInfo );

String CompNodeModelPath( TTreeNode* aNode );
String CsNodeModelPath( TTreeNode * aNode );

TTreeNode* CompNodeOfCsNode( TTreeNode* aNode );

TList* GetTreeCSNodes( TTreeView* aTree, bool IsGetChecked );
TList* GetTreeNodeCSNodes( TTreeNode* aNode, bool IsGetChecked );
TList* GetTreeCSNodes(TList* aAllNodes, bool IsGetChecked );

void SetCsTreeImage(TTreeView* aTree);
void SetCsNodeImage(TTreeNode* aNode);

bool IsCSNode( TTreeNode* aNode );
bool IsCompNode( TTreeNode* aNode );
bool IsNamedNode( TTreeNode* aNode, String aType );

String BaseCs();
String BaseCs( String aModelType );

void SelectAndCreateCS( String aPrompt, String aCsNamePrefix, String& SelItem, String& aCsName, String& aCsKeyStr  );
void SelectAndCreateCS( String aPrompt, String aCsNamePrefix, String& SelItem  );

String UpdateCsInfo( String aCsKeyStr, String aNewItems );

//String SetCsInfo( String aFaceKeyStr, String aCsName, double aU, double aV ){};
//String SetCsInfo( String aCsName ,String tx,String ty,String tz,
//			String rx,String ry,String rz,String BaseName,String aOwnerName="" );

TStrings* GetProeParaStrings( String aFileName );

String GetCurMdlMaxCsName( String aCsLab, TStrings* aCsNames );
String GetCurMdlMaxCsName( String aCsLab );
int GetMaxCsId( TStrings * aCsNames,String aLab );

//----------

//------------------- ProeEngine_Action -------------------------------------
String Action_Func(String FuncName, const char* format, ...);

String Action_CopyCS( String aSrcCompPath, String aSrcCSName,
                      String dx, String dy, String dz, String dax, String day, String daz, String aNewCSName);

String Action_RenameFeature( String aCompFileName, String aOldName, String aNewName );

String Action_AlignPairedCS( String aSrcCompPath, String aSrcCSName, String aDestCompPath, String aDestCSName );

//------------------- ProeEngine --------------------------------------------


TStrings* ParasToStrings( MParaList* aParas );
String TrueCompPath( String aCompPath, bool IsCutFirst );

class MProeEngine
{

  public:
    void CheckConfig(String IsShowModal="false");
    void ConfigProe(String IsShowModal="false"); 
    
  public:
    String AskProeTitle();
    void EraseMemMdl( String aName );

  //----IsInitProe----
  private:
    bool   fIsInitProe;
  public:
    __property bool IsInitProe={read=fIsInitProe,write=fIsInitProe};

  //----OutStyle----     "SCRIPT" / "PROE"
  private:
    String   fOutStyle;
  public:
    __property String OutStyle={read=fOutStyle,write=fOutStyle};

  public:
    bool IsScriptModel();
    void SaveScriptFile( String aPath );

  //----ScriptStrings----         //在“Script”方式下，输出的命令流
  private:
    TStrings*   fScriptStrings;
  public:
    __property TStrings* ScriptStrings={read=fScriptStrings};

  //----Engine----
  private:
    Variant   fEngine;
  public:
    __property Variant Engine={read=fEngine};

  public:
    MProeEngine();
    ~MProeEngine();
    
  public:
    void Execute(TStrings* aStrings);
    void MProeEngine::Execute(String aStr);
    
  public:
    bool CheckInit();  

  public:
    void UpdateModelParas( String aFileName, MParaList* aParas, bool IsNewFile  );
    TStrings* GetModelParaStrings( String aFileName, bool IsNewFile  );

  public:
    void CloseModel();

  //----- 基本信息 --------
  String GetComponentInfo(String aCompPath);            //获取指定组件的 ID+NAME ( ID=xx;NAME=XXX );

  //----- 装配 ------
  public:
    String AddCompToAssem( String aCompFileName, String AddPath, bool NewWhenNULL ) ;   //2010.9.10  aCompFileName:文件名称; AddPath:装配路径, 返回ModelPath

    void ConsComp( String aModePath1, String aAF1Name, String aModelPath2, String aAF2Name )  ;  //第一个Comp移动
    void ConsCompByKey( String aModePath1, String aAF1KeyStr, String aModelPath2, String aAF2KeyStr )  ;  //2010.9.10 第一个Comp移动

  //----- 形状特征 ----
  public:
    bool IsExistShapeFeature( String aUdfKey );

  public:
    String AddShapeFeature( String aGraphFileName, String aCompPath, String aAFComp, bool IsCutFirst, String aExtrudeComps="" );  //返回Key = "UdfModelPath=;UDFHeadName=;CSModelPath=;CSName=;"
    String AddShapeFeature( String aGraphFileName, String aCompPath, String aAFComp, String ACompPathAddIn, String aExtrudeComps="" );

  public:
    void UpdateShapeFeatureParas( String aSFCompPath, String aSFName, MParaList* aParas  );
    void UpdateShapeFeatureParas( String aSFCompPath, String aSFName, bool IsCutFirst, MParaList* aParas  );
    void UpdateShapeFeatureParas_ByKey( String aUdfKey, MParaList* aParas  );

    //void ShapeFeature_AutoInterSect( String aCompPath, String aFeatPath, bool IsCutFirst );
    void ShapeFeature_ExcludeInertSect( String aCompPath, String aFeatPath, bool IsCutFirst, String aCompPaths_Exclude );

  public:
    //void ShapeFeature_AutoInterSect( String aCompPath, String aFeatPath );
    void ShapeFeature_ExcludeInertSect( String aCompPath, String aFeatPath, String aCompPaths_Exclude );

  public:
    void RenameFeature( String aCompFileName, String aOldName, String aNewName );
    void ArrayFeature( String aCompPath, String aFeatPath, int aNX, double aDX, int aNY, double aDY );

  public:
    void AlignPairedCS( String aSrcCompPath, String aSrcCSName, String aDestCompPath, String aDestCSName );
    void CopyCS( String aSrcCompPath, String aSrcCSName,
                 double dx, double dy, double dz, double dax, double day, double daz, String aNewCSName );
  public:
    void GroupComponents( String aCompPath, String aComponentNames, String aGroupName );

  public:
    String ModelInfo( String aMdlName );
    String UDFInfo( String aMdlName );
    String ProjectDataInfo( String aMdlName );

  //需添加 2010.9.10
  public:
    String ModelType( String aModelPath );             //返回 "PART" || "ASSEMBLE"
    bool HasOpenModel( String aFileName ) {return true;};
    void EraseModel( String aFileName ) ;      //删除指定文件在内存中的实例

  public:
    String GetFeatureName( String aCsKeyStr ){ return ""; };
    String GetSurfaceInfo( String aFaceKey );

  public:
    TStrings* GetSelections( String aPrompt, String aFilter, int aMaxSelNum );
    String GetSelection( String aPrompt, String aFilter );

  public:
    bool DeleteShapeFeature( String aKeyStr );

  public:
    String GetCsInfo( String aCsKeyStr ){ return "";};      //bool  GetCsInfo( String aCsName , CSInfo &aCsInfo,ProAsmcomppath * aMdl)
    void SetCsInfo( String aCsKeyStr,String aCsInfo,bool IsOffSetSelf=false ){};

    void RefreshAll( String aModelPath ){};

    //void SetCsInfo( String aCsName,CSInfo aSrcCsInfo,bool IsOffSetSelf,ProAsmcomppath *comp_path=NULL);

  public:
    String NewAssemble( String aFileName );  //返回aModelPath
    void SaveModelNoAddVer( String aModelPath ){};        //SaveCurMdlNoAddVer

  public:
    String ModelFileName( String aModelPath );
    String FileNameToModelPath( String aFileName ){return "";};

    bool OpenModel( String aFileName, bool OpenWhenExsist );
    bool OpenModelByKey( String aModelKey ) ;
  public:
    String ReadMdlParas_All(String ModelPath);
  public:
    TStrings* GetModelCSInfos( String aMdlPath );
    void GetModelCSInfos( String aMdlPath, TStrings* aCSNames );

  public:
    TStrings* GetAssemPath( String aModelPath );
    void GetAssemPath( String aModelPath, TStrings* aModelPaths );

    void GetAssemPathTree(String aMdlPath, TTreeView* aTree );        //返回的TreeNode->Data指向ModelPath
    void GetCSTree( String aMdlPath, TTreeView* aTree, bool IsMaskLoad );
    void GetCSTree_Node(  TTreeNode* aNode );
  protected:
    void __fastcall DoCsTreeClick(TObject *Sender);
    bool HasLoadCs(TTreeNode* aNode);

  //------------------------ FaceInfo ----------------------------------

  public:
    String GetFaceInfo( String SelSurfaceItem );                  //获取Surface的信息

    void GetFaceUVSize( String SelSurfaceItem, double* aUSize, double* aVSize );                                      //SelFeatFace
    void GetFaceUV( String SelSurfaceItem, double* aUMin, double* aUMax, double* aVMin, double* aVMax );          //SelFeatFace
    //String Getuv_param( String SelItem );

  //------------------------ SelectionInfo -----------------------------

  public:
    String GetSelectionInfo( String SelItem );
    bool GetSelctionUV( String SelItem, double* aU, double* aV );               //当前点（Selection）的UV值

  //------------------------- CS --------------------------------------

  public:
    void DelCsInMdl( String aModelPath, TStrings* CreateCsKeyList );                            //从当前Model删除坐标系集合
    void DelCsInMdl( String aModelPath, String aCsKeyStr ){};                            //从当前Model删除坐标系集合

  public:
    //String CreateCsInMdl( String aModelPath, String SelItem, String aCsName );                   //在SelItem处建立坐标系
    //String CreateCsInMdl( String aModelPath, String SelItem, String* SelSurfaceItem );           //在SelItem处建立坐标系

    String CreateCsInSurface( String SurfaceSelItem, String aCsName, bool aParallelAxis=false  );
    void PlaceCsToCurrMdl( String aPlaceInfo, String SelFeatSurface, TStrings* aCsNameList  ){};   //在指定面SelFeatSurface上排列坐标系

  public:
    String CreateCsByXYZ( String aModelKey, double x, double y, double z, double aX, double aY, double aZ, String aCsName );

  public:
    //aParallelAxis : 与第一方向平行；与第二方向平行

    String CreateCsByUV( String aSurfaceKey, double uPara, double vPara, double Ang, String aCsName, bool aParallelAxis=false );
    //String CreateCsByUV( String aModelKey, String aSurfaceKey, double uPara, double vPara, double Ang, String aCsName, bool aParallelAxis=false );

    //String CreateCsByUV( String SelItem, double uPara, double vPara, String aCsName, String aBaseCs, bool aParallelAxis=false );
    //CreateCsByUV( &SelItem,&SelSurfaceItem,uv_param,FrameBaseFeatInfo1->CB_ProeCSysName->Text,aBaseCs,bool( CB_FeatState->ItemIndex ) );

    TStrings* CreateCsByUVArray( String SelItem, MDoubleList* uParams, MDoubleList* vParams, String aCsName, String aBaseCs, bool aParallelAxis=false );
    //aLValue, aWValue : 布局特征的轮廓参数
    void GetUVArray( String SelItem, String aPlaceInfo, bool aParallelAxis, double aLValue, double aWValue, MDoubleList* uParams, MDoubleList* vParams ){};
  //------------------------3D工艺设计------------------------------------
  public:
    String DynSelectFeat(String filter, bool ISPrecision=true);               //特征动态点选
    void GetDimensionData(String Item,String *ID,double *baseValue,
          double *upperError,double *lowwerError,bool IsPrecision=true);      //获取尺寸特征信息
    void GetGTol(String Item,String *ID,double *baseValue);                   //获取几何公差特征值
    void GetSurfaceFinish(String Item,String *ID,double *baseValue);          //获取粗糙度特征值
    TStrings* ModelFeatIDs();                                                 //获取当前模型ID
    void ModelStateSet(int featID );                    //模型状态设置
    String RoughDataGet(String Item, String name);                            //模型项粗加工数据获取
    void HighlightMdlFeats(TStrings *OldIDList, TStrings *NewIDList);         //模型特征亮选
    bool CreateMdlSnap(String FileName);                                      //创建模型当前Snap
    void ModelSaveAs(String NewName);                                         //另存为当前模型
    bool MdlSaveByPath(String aModelPath,String aPath,String aNewName);       //另存为当前模型,By葛晓波
    void ModelEDFileSave(String path, String name);                           //模型ED文件保存
    bool MdlViewStore(String ModelName,String ViewName);                      //模型视图保存
    String ViewRefit(String ModelName,String ViewName);                         //模型视图设置
  public:
    String GetViewMatrix(String ModelName,String ViewName);

  //----NC----------

  public:
    String GetNcSegs( String aModelName );
    String PlayNCById( String aModelName,int aId )  ;
    String PlayNCByName( String aModelName,String aName);

  //---- 臧霖 ---------------
  public:
    String GetProcessPlanAllInfos(String aFileName);    //获得Process Plan里的所有信息（邱博晋）
    bool PpsSaveAsTxt(String dir_pvs);                      //将ProcessPlan的信息存储为TXT

  public:
    bool Miodfy_recipe();                               //修改PVS配置文件，把简化视图选项（SIM_）改为可存储为PVA形式
    String SaveAsPvs(String dir_pvs);                     //把当前的模型文件存储为PVS文件，文件名为PRT(或ASM)的名称，后缀为PVS，存储到 dir_pvs

  public:
    bool BoolIsMmns(String aFileName);                  //判断模型计量是否为Mmns  ( Y = Mmns;  N = in( 英寸 ) )
    String ReadMdlUnit(String MdlFullName);             //读取模型及其子模型的计量单位( 返回："/43 in /n/r /45 mm" )

  public:
    String Str_XsecMsg(String MdlFullName);             //获取截面信息（ 邱博晋 ）

  public:
    bool IsMdlAsm(String MdlFullName);                      //判断模型是否为ASM
    bool PrtToAsm(String PrtName, String aModelFullName);   //新建一个ASM，将给定的PRT加入

  public:
    bool SaveRepForXsection(String XsecNames);              //将Xsec存储为简化视图
    bool DeleteRepForXsection(String XsecNames);            //删除简化视图（XsecNames）

//从邱博瑨那里合并过来的------------臧霖--------20130337

  //qbj20130726
  public:
    String GetAllExpMatrix(String dir_pvs);                     //获得ASM所有爆炸视图各零件矩阵 ( )
    String ExpStateStrGet(String dir_pvs);                      //获得ASM爆炸视图名
    
  public:
    String RepAllNameGet(String dir_pvs);                       //获得ASM简化视图名
    String OrietationAllNameGet(String dir_pvs);                //获得方向名

  //设置新的Orietation
  public:
    bool SetOrientatonToNewFile(String aViewName ,String DirPath,String viewMatrix,String WindowMatrix);
};

String PVSMatrixToStr(double m[4][4]);
int NumOfBlank(String StrIfPartHaveAsm);
String RemoveLastStr(String StrIfPartHaveAsm);
void MulOfMatrixToLatter(double m1[4][4], double m2[4][4]);



#endif
