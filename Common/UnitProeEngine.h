//---------------------------------------------------------------------------

#ifndef UnitProeEngineH
#define UnitProeEngineH

#include "UnitTool_Class.h"

class MProeEngine;
extern MProeEngine* gProeEngine;

extern int G_CheckedNo;
extern int G_CheckedNum;

extern MProeEngine* G_ProeEngine;              //����PROE������

class MProFrame;
class MProFrames;
class MPartFrame;
class MPartFrames;



//---------------FrameChange----20121226--from--����ʦ---�������------------
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

//from ����ʦ20121226  �������
//*.fra�ļ��Ľ���

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
  
   //���������λ��Ϣ--------���---20130102---
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
    bool AnimationPause;                       //���ƶ������ŵ���ͣ����------------------���--------20120105

  public:
    String PptName;                            //Ϊ����ÿ��������fra�ļ����ֲ�ͬ�����ⷢ����ʱ���໥����----���---20130321

//  public:
//    bool FramesIsModelUnitMmns;                //�ж�ģ�͵�λ����-------���--------20120102

  public:
    TStrings* FrameNameList();
    String FrameNameList_Str();
  public:
    MProFrames();
    //~MProFrames();

  public:
    void ReadFraFromFile( String aFileName );
    void ReadFraFromStrings( TStrings* aStrings );


  //��¼�ܵ�֡�����ܵ��������������ѭ��-----���----20120102

  public:
    int TotalFrames();       //int IntTotalFrames;
    int TotalParts();        //int IntTotalParts;


  //����������ķ�����ȡ�������---------���--------20130322
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
//�޸ľ������ҳ�п��õ��ļ�----------���-----20121231
  public:
    bool PartFrameIsModelUnitMmns;
    void ChangeMmnsInToWeb(double Matrix[4][4]);
    void ChangeInksInToMmns(double Matrix[4][4]);
//    double ChangeAsmToPvs(double MatrixNum);
    void ChangeMatrixLast(double Matrix[4][4]);

  public:
    String PartName;
    String MatrixString();

    //-----------PVS���MatrixString--------���----------20130410
  public:
    //String PvsMatrixString;

};


//----------------------- CsNode --------------------------------------------

class MNodeInfo : public MObject
{
  public:
    String NodeType;                   //CsNode������
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
    String UdfKey;                     //������Cs�ϵ�UdfKey
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

  //----ScriptStrings----         //�ڡ�Script����ʽ�£������������
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

  //----- ������Ϣ --------
  String GetComponentInfo(String aCompPath);            //��ȡָ������� ID+NAME ( ID=xx;NAME=XXX );

  //----- װ�� ------
  public:
    String AddCompToAssem( String aCompFileName, String AddPath, bool NewWhenNULL ) ;   //2010.9.10  aCompFileName:�ļ�����; AddPath:װ��·��, ����ModelPath

    void ConsComp( String aModePath1, String aAF1Name, String aModelPath2, String aAF2Name )  ;  //��һ��Comp�ƶ�
    void ConsCompByKey( String aModePath1, String aAF1KeyStr, String aModelPath2, String aAF2KeyStr )  ;  //2010.9.10 ��һ��Comp�ƶ�

  //----- ��״���� ----
  public:
    bool IsExistShapeFeature( String aUdfKey );

  public:
    String AddShapeFeature( String aGraphFileName, String aCompPath, String aAFComp, bool IsCutFirst, String aExtrudeComps="" );  //����Key = "UdfModelPath=;UDFHeadName=;CSModelPath=;CSName=;"
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

  //����� 2010.9.10
  public:
    String ModelType( String aModelPath );             //���� "PART" || "ASSEMBLE"
    bool HasOpenModel( String aFileName ) {return true;};
    void EraseModel( String aFileName ) ;      //ɾ��ָ���ļ����ڴ��е�ʵ��

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
    String NewAssemble( String aFileName );  //����aModelPath
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

    void GetAssemPathTree(String aMdlPath, TTreeView* aTree );        //���ص�TreeNode->Dataָ��ModelPath
    void GetCSTree( String aMdlPath, TTreeView* aTree, bool IsMaskLoad );
    void GetCSTree_Node(  TTreeNode* aNode );
  protected:
    void __fastcall DoCsTreeClick(TObject *Sender);
    bool HasLoadCs(TTreeNode* aNode);

  //------------------------ FaceInfo ----------------------------------

  public:
    String GetFaceInfo( String SelSurfaceItem );                  //��ȡSurface����Ϣ

    void GetFaceUVSize( String SelSurfaceItem, double* aUSize, double* aVSize );                                      //SelFeatFace
    void GetFaceUV( String SelSurfaceItem, double* aUMin, double* aUMax, double* aVMin, double* aVMax );          //SelFeatFace
    //String Getuv_param( String SelItem );

  //------------------------ SelectionInfo -----------------------------

  public:
    String GetSelectionInfo( String SelItem );
    bool GetSelctionUV( String SelItem, double* aU, double* aV );               //��ǰ�㣨Selection����UVֵ

  //------------------------- CS --------------------------------------

  public:
    void DelCsInMdl( String aModelPath, TStrings* CreateCsKeyList );                            //�ӵ�ǰModelɾ������ϵ����
    void DelCsInMdl( String aModelPath, String aCsKeyStr ){};                            //�ӵ�ǰModelɾ������ϵ����

  public:
    //String CreateCsInMdl( String aModelPath, String SelItem, String aCsName );                   //��SelItem����������ϵ
    //String CreateCsInMdl( String aModelPath, String SelItem, String* SelSurfaceItem );           //��SelItem����������ϵ

    String CreateCsInSurface( String SurfaceSelItem, String aCsName, bool aParallelAxis=false  );
    void PlaceCsToCurrMdl( String aPlaceInfo, String SelFeatSurface, TStrings* aCsNameList  ){};   //��ָ����SelFeatSurface����������ϵ

  public:
    String CreateCsByXYZ( String aModelKey, double x, double y, double z, double aX, double aY, double aZ, String aCsName );

  public:
    //aParallelAxis : ���һ����ƽ�У���ڶ�����ƽ��

    String CreateCsByUV( String aSurfaceKey, double uPara, double vPara, double Ang, String aCsName, bool aParallelAxis=false );
    //String CreateCsByUV( String aModelKey, String aSurfaceKey, double uPara, double vPara, double Ang, String aCsName, bool aParallelAxis=false );

    //String CreateCsByUV( String SelItem, double uPara, double vPara, String aCsName, String aBaseCs, bool aParallelAxis=false );
    //CreateCsByUV( &SelItem,&SelSurfaceItem,uv_param,FrameBaseFeatInfo1->CB_ProeCSysName->Text,aBaseCs,bool( CB_FeatState->ItemIndex ) );

    TStrings* CreateCsByUVArray( String SelItem, MDoubleList* uParams, MDoubleList* vParams, String aCsName, String aBaseCs, bool aParallelAxis=false );
    //aLValue, aWValue : ������������������
    void GetUVArray( String SelItem, String aPlaceInfo, bool aParallelAxis, double aLValue, double aWValue, MDoubleList* uParams, MDoubleList* vParams ){};
  //------------------------3D�������------------------------------------
  public:
    String DynSelectFeat(String filter, bool ISPrecision=true);               //������̬��ѡ
    void GetDimensionData(String Item,String *ID,double *baseValue,
          double *upperError,double *lowwerError,bool IsPrecision=true);      //��ȡ�ߴ�������Ϣ
    void GetGTol(String Item,String *ID,double *baseValue);                   //��ȡ���ι�������ֵ
    void GetSurfaceFinish(String Item,String *ID,double *baseValue);          //��ȡ�ֲڶ�����ֵ
    TStrings* ModelFeatIDs();                                                 //��ȡ��ǰģ��ID
    void ModelStateSet(int featID );                    //ģ��״̬����
    String RoughDataGet(String Item, String name);                            //ģ����ּӹ����ݻ�ȡ
    void HighlightMdlFeats(TStrings *OldIDList, TStrings *NewIDList);         //ģ��������ѡ
    bool CreateMdlSnap(String FileName);                                      //����ģ�͵�ǰSnap
    void ModelSaveAs(String NewName);                                         //���Ϊ��ǰģ��
    bool MdlSaveByPath(String aModelPath,String aPath,String aNewName);       //���Ϊ��ǰģ��,By������
    void ModelEDFileSave(String path, String name);                           //ģ��ED�ļ�����
    bool MdlViewStore(String ModelName,String ViewName);                      //ģ����ͼ����
    String ViewRefit(String ModelName,String ViewName);                         //ģ����ͼ����
  public:
    String GetViewMatrix(String ModelName,String ViewName);

  //----NC----------

  public:
    String GetNcSegs( String aModelName );
    String PlayNCById( String aModelName,int aId )  ;
    String PlayNCByName( String aModelName,String aName);

  //---- ��� ---------------
  public:
    String GetProcessPlanAllInfos(String aFileName);    //���Process Plan���������Ϣ���񲩽���
    bool PpsSaveAsTxt(String dir_pvs);                      //��ProcessPlan����Ϣ�洢ΪTXT

  public:
    bool Miodfy_recipe();                               //�޸�PVS�����ļ����Ѽ���ͼѡ�SIM_����Ϊ�ɴ洢ΪPVA��ʽ
    String SaveAsPvs(String dir_pvs);                     //�ѵ�ǰ��ģ���ļ��洢ΪPVS�ļ����ļ���ΪPRT(��ASM)�����ƣ���׺ΪPVS���洢�� dir_pvs

  public:
    bool BoolIsMmns(String aFileName);                  //�ж�ģ�ͼ����Ƿ�ΪMmns  ( Y = Mmns;  N = in( Ӣ�� ) )
    String ReadMdlUnit(String MdlFullName);             //��ȡģ�ͼ�����ģ�͵ļ�����λ( ���أ�"/43 in /n/r /45 mm" )

  public:
    String Str_XsecMsg(String MdlFullName);             //��ȡ������Ϣ�� �񲩽� ��

  public:
    bool IsMdlAsm(String MdlFullName);                      //�ж�ģ���Ƿ�ΪASM
    bool PrtToAsm(String PrtName, String aModelFullName);   //�½�һ��ASM����������PRT����

  public:
    bool SaveRepForXsection(String XsecNames);              //��Xsec�洢Ϊ����ͼ
    bool DeleteRepForXsection(String XsecNames);            //ɾ������ͼ��XsecNames��

//���񲩬�����ϲ�������------------���--------20130337

  //qbj20130726
  public:
    String GetAllExpMatrix(String dir_pvs);                     //���ASM���б�ը��ͼ��������� ( )
    String ExpStateStrGet(String dir_pvs);                      //���ASM��ը��ͼ��
    
  public:
    String RepAllNameGet(String dir_pvs);                       //���ASM����ͼ��
    String OrietationAllNameGet(String dir_pvs);                //��÷�����

  //�����µ�Orietation
  public:
    bool SetOrientatonToNewFile(String aViewName ,String DirPath,String viewMatrix,String WindowMatrix);
};

String PVSMatrixToStr(double m[4][4]);
int NumOfBlank(String StrIfPartHaveAsm);
String RemoveLastStr(String StrIfPartHaveAsm);
void MulOfMatrixToLatter(double m1[4][4], double m2[4][4]);



#endif
