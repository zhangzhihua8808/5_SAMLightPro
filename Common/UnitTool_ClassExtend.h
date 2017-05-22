//---------------------------------------------------------------------------

#ifndef UnitTool_ClassExtendH
#define UnitTool_ClassExtendH

//------------------------头文件------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
#include <ToolWin.hpp>
#include <ImgList.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include <IniFiles.hpp>
#include "UnitTool_Class.h"
#include "UnitTool_Single.h"
#include "COMMON_FUNC.hpp"

#include <gl\gl.h>
#include <gl\glu.h>

#include "clipper.hpp"
#include <stdio.h>


using namespace Clipper;


class MTreeNodes_LayerData;
class MLayerDataTreeNode;
class MObjectList_Temp;
class MPolyLines;
class MHatchLines;
class M2DPoints;
class MAMProjects;
class MPartDatas_LayerDataTreeNode;
class MPartData_LayerDataTreeNode;
class MPartProject;
class MPartProjects;
class MLaserPens;
class MLaserPen;

//------------------------------------------------------------------------------
//增量制造工程
//CLI二进制文件读取工程
class MAMProject : public MObject
{
  private:
     String  fProjectName;                    //工程名称，与RootNode的NodeName相同； "在新建的时候"
     String  fProjectFileName;                //like ; XXX.3dmanual
     MTreeNodes_LayerData*    fMainItems;                                       //分层数据
     TTreeView*   fLayersDataHolder;
     TComboBox*   fLayerDataSelect;
     MLayerDataTreeNode*  fCurLayerDataItem;

     double  fMinZ;
     String   fProjectType;

     //与二进制文件读取有关的信息
     float  fUnit;
     int    fLayers;
     short  int   fPartID;
     bool  IsBinaryCliFile(String  aFileName);
     void  DoFileFormatConvert(String aSrcFile,String aDestFile);
     void  BinaryCLIFileHeadProcess(FILE* stream);
  protected:
     String   readConfigFileName();
     String   readPrjLocation();

     double   readMiddleX();
     double   readMiddleY();
     double   readPartDimX();
     double   readPartDimY();
     double   readMinX();
     double   readMaxX();
     double   readMinY();
     double   readMaxY();
     double   readMaxZ();
     void     writeCurLayerDataItem(MLayerDataTreeNode* aItem);
  public:
     __property  double   PartMinX = {read=readMinX};
     __property  double   PartMaxX = {read=readMaxX};
     __property  double   PartMinY = {read=readMinY};
     __property  double   PartMaxY = {read=readMaxY};
     __property  double   PartMinZ = {read=fMinZ};
     __property  double   PartMaxZ = {read=readMaxZ};
     __property  double   PartMiddleX = {read=readMiddleX};
     __property  double   PartMiddleY = {read=readMiddleY};
     __property  double   PartDimX = {read=readPartDimX};
     __property  double   PartDimY = {read=readPartDimY};

     __property  String   ProjectName = {read=fProjectName,write=fProjectName};
     __property  String   ProjectFileName = {read=fProjectFileName,write=fProjectFileName};
     __property  String   CfgFileName= {read=readConfigFileName};               //保存工程树信息
     __property  MTreeNodes_LayerData*  MainItems = {read=fMainItems};
     __property  TTreeView*   LayersDataHolder = {read=fLayersDataHolder,write=fLayersDataHolder};
     __property  TComboBox*   LayerDataSelect = {read=fLayerDataSelect,write=fLayerDataSelect};
     __property  MLayerDataTreeNode*  CurLayerDataItem = {read=fCurLayerDataItem,write=writeCurLayerDataItem};
     __property  String   ProjectLocation ={read=readPrjLocation};
     __property  String   ProjectType = {read=fProjectType,write=fProjectType}; //用于区分是多层文件还是单层文件
     __property  short int      PartID = {read=fPartID,write=fPartID};

  public:
     MAMProject();
     virtual ~MAMProject();

  public:
     void  SetPrjInformation(String aPrjFileName,String aPrjName);   //新建
     void  CheckMainStruct( TStrings* aStrings, int& iTreeBegin, int& iTreeEnd );
     void  ModelFile_PreProcess(MLayerDataTreeNode* aDMNode,String aModelFileName);

     String  SaveCatalogStruct(String  aOutFileName="");

     //从模型文件中加载数据
     void  LoadLayerDataItemsFromFile( String aModelFileName, TTreeView* aTree );
     void  LoadLayerDataItemsFromFile(TStrings* aStrings);
     void  LoadLayerDataItemsFromFile();

     void  LoadLayerDatasFromCLiFile(String aCliFile,bool bSaveCtStruct=true,bool bConvertDXF=true);
     void  LoadCLiHeaderInfoFromStrings(TStrings* aStrings);
     void  LoadCLiLayerInfoFromStrings(TStrings* aStrings,bool  bConvertDxf=true);

     void  ConvertCli2Dxf(TStringList* aSubFileStrings,String aSaveFileName);
     void  ConvertEdgeCli2Dxf(TStrings* aSubFileStrings,String aSaveFileName);

     void  DoMovePart(double  aPartMoveX,double aPartMoveY);
     void  DoScalePart(double aPartScaleX,double aPartScaleY);

     void  LoadLayerDatasFromFile(String aCfgFile);

     //与二进制文件读取有关的
     String ConvertBinaryToAscIICLiFile(String  aCLiFileName);
};

//-------------------------代表一个要打印的Part，这个Part直接不能用于打印-------
class  MPartProject : public  MObject
{
   public:
      MPartProject(MPartProjects* aItems=NULL);

   private:
       MPartProjects*  fItems;
       MLaserPens*     fLaserPens;   //一个零件有多个pen,打印的速度，功率等
       MLaserPen*      fLaserPen;    //暂时先用一个笔
       String  fProjectName;
       float  fUnit;
       int    fLayers;
       short  int   fPartID;
       MTreeNodes_LayerData*    fMainItems;
       TTreeView*   fLayersDataHolder;
       double   readMinX();
       double   readMaxX();
       double   readMinY();
       double   readMaxY();
   public:
       __property  MPartProjects*  Items =  {read=fItems,write=fItems};
       __property  MLaserPens*   LaserPens = {read=fLaserPens,write=fLaserPens};
       __property  MLaserPen*    LaserPen = {read=fLaserPen,write=fLaserPen};
       __property  String   ProjectName = {read=fProjectName,write=fProjectName};
       __property  short int      PartID = {read=fPartID,write=fPartID};
       __property  MTreeNodes_LayerData*  MainItems = {read=fMainItems};
       __property  TTreeView*   LayersDataHolder = {read=fLayersDataHolder,write=fLayersDataHolder};
       __property  double   PartMinX = {read=readMinX};
       __property  double   PartMaxX = {read=readMaxX};
       __property  double   PartMinY = {read=readMinY};
       __property  double   PartMaxY = {read=readMaxY};
   public:
       void  LoadCLiLayerInfoFromStrings(TStrings* aStrings);
       void  LoadGYInfoFromFile(String aFileName);
       void  LoadCLiHeaderInfoFromStrings(TStrings* aStrings);
       void  ToListBox(TListBox* aList);
       void  LoadLayerDatasFromCLiFile(String aCliFile);
       void  DoMovePart(double  aPartMoveX,double aPartMoveY);
       MLayerDataTreeNode* FindLayerDataTreeNodeByHeight(double aAbsoluteHeight);
};

class MPartProjects : public  MObjectList_Temp<MPartProject>
{
   public:
      MPartProjects();

   public:
      MPartProject*  NewPartProject();
      void LoadPartProjectsFromFileStrings(TStrings* aFiles);
      void AddToListBox(TListBox*  aListBox,bool bClear=false);
};


//------------------------------------------------------------------------------
class MTreeNodes_LayerData : public  MObjectList_Temp<MLayerDataTreeNode>
{
  private:
        MAMProject*  fProject;
  protected:
        virtual String  readMaxID();
        virtual void    writeMaxID(String aID);
        virtual bool    IsEqualByName(String aName,MObject* aEntity,bool IsUppercase);
        double readMinX();
        double readMaxX();
        double readMinY();
        double readMaxY();
        double readMaxZ();
  public:
     __property  double MinX = {read=readMinX};
     __property  double MaxX = {read=readMaxX};
     __property  double MinY = {read=readMinY};
     __property  double MaxY = {read=readMaxY};
     __property  double MaxZ = {read=readMaxZ};
     __property  String  MaxID = {read=readMaxID,write=writeMaxID};
     __property  MAMProject* Project = {read=fProject,write=fProject};
  public:
        MTreeNodes_LayerData();

        void  ToComboBox(TComboBox* aCBox);
        void  NewLayerDataItem(String aText);
        MLayerDataTreeNode*  NewLayerData_AT(String aID,String aName, String aType,
                              String aParentName,String aImageIndex,String aCLiFile,String aDXFFileName);   //在末尾添加,自动加入集合中
        MLayerDataTreeNode*  NewLayerData_MT(String aID,String aName, String aType,
                              String aParentName,String aImageIndex,String aCLiFile,String aDXFFileName);   //手动方式，手动加入集合中

        void ToTreeView(TTreeView* aTree,bool  bContructTree= true);
        TStrings* SaveCatalogStruct();
        TStrings* SaveCatalogDatas();

        void DoMovePart(double  aPartMoveX,double aPartMoveY);
        void DoScalePart(double aPartScaleX,double aPartScaleY);

        //与二进制文件读取有关
        MLayerDataTreeNode*  NewLayerData();
};


//------------------------------------------------------------------------------
//代表一层的数据
class MLayerDataTreeNode : public MObject
{
 private:
     MTreeNodes_LayerData*  fItems;                                             //集合

     String  fLayerDataID;                                                      //唯一标示
     String  fNodeName;
     String  fParentName;
     int     fImageIndex;

     //每个节点存储两个文件名：DXF文件：用于打印; CLI文件：用于显示
     String  fCLIFileName;                                                      //对于根节点，保存CLI文件名; 对于非根节点，保存 层文件(填充线文件)
     String  fCLIEdgeFileName;                                                  //边界文件，用于功率控制
     String  fDXFFileName;

     //每个节点有两个ID号：fLayerDataID： 用于构成树的父子关系；fLayerNO： 用于指示层信息
     TTreeNode*  fTreeNode;
     String  fLayerNO;
     MPolyLines*  fPolyLines;             //有很多polyline
     MHatchLines*  fHatchLines;           //有很多hatchLine
     TStrings*  fCliDataStr;

     //多个零件的轮廓，填充
     MPartDatas_LayerDataTreeNode*  fPartDatas_InOut;


     //用于二进制文件读取的
     String  fAbsoluteHeight;
     float   fUnit;



   protected:
      MLayerDataTreeNode* readParent();
      double readMinX();
      double readMaxX();
      double readMinY();
      double readMaxY();
      double readSizeX();
      double readSizeY();
      double readRotateX();
      double readRotateY();
  public:
     __property  double MinX = {read=readMinX};
     __property  double MaxX = {read=readMaxX};
     __property  double MinY = {read=readMinY};
     __property  double MaxY = {read=readMaxY};
     __property  double SizeX = {read=readSizeX};
     __property  double SizeY = {read=readSizeY};
     __property  double RotateX = {read=readRotateX};
     __property  double RotateY = {read=readRotateY};
     __property  MTreeNodes_LayerData*  Items = {read=fItems};
     __property  String  LayerDataID = {read=fLayerDataID,write=fLayerDataID};
     __property  String  NodeName = {read=fNodeName,write=fNodeName};
     __property  String  ParentName = {read=fParentName,write=fParentName};
     __property  int     ImageIndex = {read=fImageIndex,write=fImageIndex};
     __property  String  CLIFileName = {read=fCLIFileName,write=fCLIFileName};
     __property  String  DXFFileName= {read=fDXFFileName,write=fDXFFileName};
     __property  String  CLIEdgeFileName = {read = fCLIEdgeFileName,write=CLIEdgeFileName};
     __property  MPartDatas_LayerDataTreeNode*  PartDatas_All = {read=fPartDatas_InOut};

     __property  TTreeNode*  TreeNode = {read=fTreeNode,write=fTreeNode};
     __property  MLayerDataTreeNode* Parent = {read=readParent};
     __property  String  AbsoluteHeight = {read=fAbsoluteHeight,write=fAbsoluteHeight};
     __property  String  LayerNo = {read=fLayerNO,write=fLayerNO};

     __property  MPolyLines*  PolyLines = {read=fPolyLines};
     __property  MHatchLines* HatchLines = {read=fHatchLines};
     __property  TStrings*    CliDataStrings = {read=fCliDataStr};

     __property  float  Unit = {read=fUnit,write=fUnit};
   public:
     MLayerDataTreeNode(MTreeNodes_LayerData* aItems);
     ~MLayerDataTreeNode();

     void  Dispose();

     //保存在文件中的位置
     int   iBeginLine;
     int   iEndLine;
   public:
     //对于根节点
     void  LoadLayerDataItemsFromFile( String aModelFileName, TTreeView* aTree );
     void  SaveToCliDataStrings(TStrings* aStrings);

     //对于其他结点,找到数据位置    (打开时使用)
     void  LoadSingleCliData(TStrings* aStrings,int aItemBeginSearch,int& iItemEnd);
     void  CheckSubStruct( TStrings* aStrings, int& iTreeBegin, int& iTreeEnd );
     void  ProcessCliData(TStrings* aStrings);

     //void LoadDataElementsFromFile( String aCfgFName, TListBox* aListBox );
     //void LoadDataElementsFromFile( String aCfgFName);
     //void LoadDataElementsFromStrings(TStrings* aStrings);
     //void LoadDataElementsFromStrings(TStrings* aStrings,TListBox* aListBox);
     //void CheckMainStruct( TStrings* aStrings, int& iTreeBegin, int& iTreeEnd );
     String SaveCatalogStruct();
     String SaveCatalogData();

     void  LoadHatchLine(String aLine);

     void DrawInOpenGL();
     void DoMovePart(double  aPartMoveX,double aPartMoveY);
     void DoScalePart(double aPartScaleX,double aPartScaleY);

     //String SaveDMStruct();
     //void SaveDMDocFile(bool  IsCloseFile);
     //void  Save(bool IsCloseFile);

     void  GetCliDataStrings(TStrings*  aStrings,int aItemBeginSearch,int& iItemEnd);
     String  ConvertCli2Dxf(TStringList* aSubFileStrings,String  aLayerPath);
     void  DxfOutFromStrings(TStringList* aRetStrings,TStrings*  aStrList);
     void  DxfOutFromString(TStringList* aRetStrings,String  aStr);


     void  DxfOutFromPOLYLINE(TStringList* aRetStrings,String aStr);
     void  DxfOutFromHATCHES(TStringList* aRetStrings,String aStr);

     //二进制文件读取
     void LoadSingleCliData(FILE* stream);
};


//------------------------------------------------------------------------------
//打标一个打印文件
class  MPartData_LayerDataTreeNode : public MObject
{
   private:
      MPolyLines*  fPolyLines;             //有很多polyline
      MHatchLines*  fHatchLines;           //有很多hatchLine

      double  fLaserPower;     //代表该打印文件的激光功率，激光速度，从而可以得到Pen
      double  fLaserSpeed;

      bool    bFinishPrint;

      MPartDatas_LayerDataTreeNode*  fItems;
   public:
      __property  MPolyLines*   PolyLines = {read=fPolyLines};
      __property  MHatchLines*  HatchLines = {read=fHatchLines};
      __property  double   LaserPower = {read=fLaserPower,write=fLaserPower};
      __property  double   LaserSpeed = {read=fLaserSpeed,write=fLaserSpeed};
      __property  bool     FinishPrint ={read=bFinishPrint,write=bFinishPrint};
      __property  MPartDatas_LayerDataTreeNode*  Items={read=fItems,write=fItems};

   public:
      MPartData_LayerDataTreeNode(MPartDatas_LayerDataTreeNode*  aItems);

      void    ToListView( TListView* aList );
      String  FullName();
      void Dispose();
};

class MPartDatas_LayerDataTreeNode : public  MObjectList_Temp<MPartData_LayerDataTreeNode>
{
   public:
      MPartDatas_LayerDataTreeNode();

      MPartData_LayerDataTreeNode*  NewPartData_LayerDataTreeNode();

      void   ToListView(TListView* aLV);

      void  Dispose();
};

//------------------------------------------------------------------------------
//代表一个点
class M2DPoint : public MObject
{
   private:
      float  fX;
      float  fY;
      M2DPoints*  fItems;
   public:
      __property  float X = {read=fX,write=fX};
      __property  float Y = {read=fY,write=fY};
      __property  M2DPoints* Items = {read=fItems,write=fItems};
   public:
      M2DPoint(M2DPoints* aItems);

      String  OutPoint();

      void DoScalePart(double aPartScaleX,double aPartScaleY,
                                           double aRotateX,double aRotateY);
};

//代表点的集合
class M2DPoints : public  MObjectList_Temp<M2DPoint>
{
  protected:
     double readMinX();
     double readMaxX();
     double readMinY();
     double readMaxY();
  public:
     __property  double MinX = {read=readMinX};
     __property  double MaxX = {read=readMaxX};
     __property  double MinY = {read=readMinY};
     __property  double MaxY = {read=readMaxY};
  public:
      M2DPoints();
      M2DPoint*  New2DPoint(double aX,double aY);
      String     OutPoints();
};

//------------------------------------------------------------------------------
//代表一条Polyline线
class  MPolyLine : public MObject
{
  private:
     M2DPoints*   fPoints;
     MPolyLines*  fItems;
     int          fPathType;   //0:边界实轮廓，1：内部实轮廓，2：内部虚轮廓

     //用于二进制文件读取的
     unsigned  short    fDir;        //0:顺时针；1：逆时针，2：非闭合
     unsigned  short    fPartID;     //零件ID
  public:
     __property  M2DPoints*  Points = {read=fPoints};
     __property  int PathType = {read=fPathType,write=fPathType};
     __property  MPolyLines* Items = {read=fItems};
     __property  unsigned short Dir = {read=fDir,write=fDir};
     __property  unsigned short PartID = {read=fPartID,write=fPartID};
  public:
     MPolyLine(MPolyLines* aItems);

     void Dispose();

     String  OutPolyLine();
     String  OutPutContour2CLI();

     void LoadPolyLineData(String aLine);                                       //old style;
     void LoadPolyLineDataFromStr(String aLine);                                //采用Clipper处理

     void DrawInOpenGL();
     void DoMovePart(double  aPartMoveX,double aPartMoveY);
     void DoScalePart(double aPartScaleX,double aPartScaleY,double aRotateX,double aRotateY);

     void  PolyLineToPath(TPath& aPath,int scale);
};

//Polyline的集合
class MPolyLines : public  MObjectList_Temp<MPolyLine>
{
  public:
     MPolyLines();
  protected:
     double readMinX();
     double readMaxX();
     double readMinY();
     double readMaxY();

  public:
     MPolyLine*  NewPolyLine();
     TStrings*   OutPolyLine();

     TClipper*  fClipper;

     void  AddPaths(const TPaths& aPaths,int aScale,int aType);
     void  PathToPoints(const TPath& aPath,M2DPoints* aPoints,int aScale);

     void  DrawInOpenGL();
     void  DoMovePart(double  aPartMoveX,double aPartMoveY);
     void  DoScalePart(double aPartScaleX,double aPartScaleY,double aRotateX,double aRotateY);

     void OutPutContours2CLI(TStrings*  aCLIFile);

     void Dispose();
  public:
     __property  double MinX = {read=readMinX};
     __property  double MaxX = {read=readMaxX};
     __property  double MinY = {read=readMinY};
     __property  double MaxY = {read=readMaxY};
};

//------------------------------------------------------------------------------
//代表一条填充线
class  MHatchLine : public  MObject
{
   private:
      M2DPoints*  fPoints;
      MHatchLines*  fItems;
   public:
      __property  MHatchLines* Items = {read=fItems};
      __property  M2DPoints*   Points = {read=fPoints};
   public:
      MHatchLine(MHatchLines*  aItems);
      ~MHatchLine();

      void Dispose();

      String  OutHatchLine();

      void DrawInOpenGL();
      void DoMovePart(double  aPartMoveX,double aPartMoveY);
      void DoScalePart(double aPartScaleX,double aPartScaleY,double aRotateX,double aRotateY);
};

//填充线的集合
class MHatchLines : public  MObjectList_Temp<MHatchLine>
{
   public:
      MHatchLines();
   public:
      MHatchLine*  NewHatchLine(double aStartPointX,double aStartPointY,
                                double aEndPointX,double aEndPointY);
      TStrings*  OutHatchLine();
      void Dispose();

      void DrawInOpenGL();
      void DoMovePart(double  aPartMoveX,double aPartMoveY);
      void DoScalePart(double aPartScaleX,double aPartScaleY,double aRotateX,double aRotateY);

      void OutPutContours2CLI(TStrings*  aCLIFile);
};


//---------------------------------------------------------------------------
class CGLView
{
private:
    HWND m_hWnd;
    HDC  m_hDC;
    HGLRC m_hGLRC;
    float  fWindowRange;
    float  fWorkArea;
    MLayerDataTreeNode* fCurDrawLayer;
public:
    __property  HWND  hWnd = {write=m_hWnd};
    __property  float WindowRange = {read=fWindowRange,write=fWindowRange};
    __property  float WorkArea = {read=fWorkArea,write=fWorkArea};
    __property  MLayerDataTreeNode* CurDrawLayer = {read=fCurDrawLayer,write=fCurDrawLayer};
public:
    CGLView();
    ~CGLView();

    bool SetupGLContext();
    int  SetPixelFormat(HDC hdc);
    void Resize(unsigned short iWidth, unsigned short iHeight);

    void SetupLighting();
    void RenderGLScene();
    void DrawObjects();

    void DisableOpenGL();           //关闭
    
};

//------------------------------------------------------------------------------

class MLaserPen : public MObject
{
   private:
      int   fPenID;
      String   fPenName;
      String   fPenPower;
      String   fPenSpeed;
      String   fPenFreq;   //频率
      MLaserPens*  fItems;
   public:
      __property  int   PenID = {read=fPenID,write=fPenID};
      __property  String   PenName = {read=fPenName,write=fPenName};
      __property  String   PenPower = {read=fPenPower,write=fPenPower};
      __property  String   PenSpeed = {read=fPenSpeed,write=fPenSpeed};
      __property  String   PenFreq = {read=fPenFreq,write=fPenFreq};
      __property  MLaserPens* Items = {read=fItems,write=fItems};

   public:
     MLaserPen(MLaserPens*  aItems);

     void    ToListView( TListView* aList );
     String  FullName();
     String  SaveToString();
     bool    IsEqual(MLaserPen* aPen);

};

class MLaserPens :  public MObjectList_Temp<MLaserPen>
{
  public:
     MLaserPens();

  public:
     MLaserPen*  NewItem(int aID);

     void   LoadFromFile(String  aFileName);
     void   LoadFromStrings(TStrings* aStrings);
     void   LoadItemFromString(String  aText);

     void   SaveToFile(String  aFileName);

     void   ToListView(TListView* aLV);
     void   ToComboBox(TComboBox* aCBox);
};


//------------------------------------------------------------------------------
//Node,NodeType=子程序,NodeName=激光器开机上电,NodeCode=110,NodeKey=,NodeValue=
class MConfigVars;
class MConfigVar : public MObject
{
   private:
      String  fConfigVarType;
      String  fConfigVarName;
      String  fConfigVarCode;
      String  fConfigVarKey;
      String  fConfigVarValue;
      MConfigVars*  fItems;
   public:
      __property  String  ConfigVarType ={read=fConfigVarType,write=fConfigVarType};
      __property  String  ConfigVarName ={read=fConfigVarName,write=fConfigVarName};
      __property  String  ConfigVarCode = {read=fConfigVarCode,write=fConfigVarCode};
      __property  String  ConfigVarKey = {read=fConfigVarKey,write=fConfigVarKey};
      __property  String  ConfigVarValue = {read=fConfigVarValue,write=fConfigVarValue};
      __property  MConfigVars*  Items = {read=fItems,write=fItems};

   public:
      MConfigVar(MConfigVars* aItems);
};

class MConfigVars :  public MObjectList_Temp<MConfigVar>
{
   public:
      MConfigVars();

   public:
      MConfigVar*  NewItem(String aVarType,String aVarName,String aVarCode,
                                    String aVarKey,String aVarValue);

      void LoadFromFile(String  aFileName);
      void   LoadFromStrings(TStrings* aStrings);
      void   LoadItemFromString(String  aText);
      MConfigVar*  FindItemByName(String  aType,String aName);
};

//------------------------------------------------------------------------------
class MGroupPrint9Blocks;
class  MPrint9BlocksTest
{
   public:
       MGroupPrint9Blocks*  Blocks;

   public:
       MPrint9BlocksTest();
       ~MPrint9BlocksTest();
   public:
       void  FreshBlocks(String  aFileName);
       void  LoadGroupPrint9BlockFromText(String aText);
       void  LoadGroupPrint9BlockFromText(String aID,String aItemList);
};

class  MGroupPrint9Block : public MObject
{
   public:
       int   GroupID;
       TStringList*  ItemList;
       MGroupPrint9Blocks*  Items;
   public:
       MGroupPrint9Block(MGroupPrint9Blocks* aItems);
};

class MGroupPrint9Blocks : public MObjectList_Temp<MGroupPrint9Block>
{
   public:
      MGroupPrint9Blocks();

   public:
      MGroupPrint9Block*   NewGroupPrint9Block(int aGroupID);
      void  ClearGroups();
};

//------------------------------------------------------------------------------
//说明：数据模块的数据源
class MDMSourceItems;

//代表一个CLI Part
class MDMSourceItem : public MObject
{
    //----Items----
  private:
    MDMSourceItems*   fItems;
    String   fFileName;                                                         //文件的全路径

  public:
    __property MDMSourceItems* Items={read=fItems,write=fItems};
    __property String  FileName={read=fFileName,write=fFileName};

    MAMProject*  fCLIPart;
  public:
    MDMSourceItem( MDMSourceItems* aItems);
    void ToListBox(TListBox* aList);
};

//代表 CLI Parts
class MDMSourceItems : public MObjectList_Temp<MDMSourceItem>
{
  public:
     MDMSourceItems();

  public:
     MDMSourceItem*   NewNameItem(String aFileName);
     void  ToListBox(TListBox* aList,bool  bClear=true);
     int  IndexByName(String  aName);
};


//------------------------------------------------------------------------------
//代表管理者
class MDMSource
{
    //----Items---- [集合]---------------
  private:
    MDMSourceItems*   fItems;
  public:
    __property MDMSourceItems* Items={read=fItems};

  public:
      MDMSource();

      void  LoadStepNamesFromParaValueStrings(TStrings* aParaValueStrings);     //操作步骤
      void  LoadFileNamesFromListBox(TListBox* aList);    //加载ListBox
      void  DeleteFileNames(TListBox* aList);
      void  DeleteSelectedFileNameItem(TListBox* aList);         //删除选择项
      void  MergeStepNamesAndShow(TListBox* aList,String aStepName,String aTitle,
                               String aFileName,String aRemark,bool isMaskMerge);

}; 

#endif
