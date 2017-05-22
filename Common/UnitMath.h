//---------------------------------------------------------------------------

#ifndef UnitMathH
#define UnitMathH

#include "unittool_Single.h"
#include "UnitTool_Class.h"

//#define UseAddFlow

#ifdef UseAddFlow

#include "UnitTool_AddFlow.h"

#endif

class MObject;
class MLine;
class MPolygon;
class MArea;
class MPLine;
class MPLines;
class MLines;
class MPoints;

//----------- MCoordinate ---------------------------------------------------

//坐标系
class MCoordinate : public MObject
{
  public:
    double x0, y0 ,z0;
    double xXaxis, yXaxis, zXaxis;
    double xYaxis, yYaxia, zZaxis;
  public:
    double Matrix[ 12 ];            //变换矩阵
  public:
    MCoordinate();
};

class MCoordinates : public MObjectList_Temp<MCoordinate>
{
};

//----------- MGeoObject ---------------------------------------------------
class MGeoObject : public MObject
{
};

class MGeoObjects : public MObjectList_Temp<MGeoObject>
{
};

class MPoint : public MGeoObject
{
  public:
    double x;
    double y;
    double z;
  public:
    MPoint operator +(MPoint);
    MPoint operator -(MPoint);
    void operator =(MPoint aP);
    bool operator ==(MPoint aP);

  public:
    MPoint( double aX=0.0, double aY=0.0, double aZ = 0.0 );
    MPoint( MPoint* aPoint );
  public:
    void Copy( MPoint* aPoint );
    void SetPoint( MPoint* aPoint );

    bool IsEqual( MPoint* aPoint );
  public:
    void LoadVector( double aVector[] );
    void ToVector( double aVector[] );

  public:
    bool IsOnLine( MLine* aLine );
    bool IsInLine( MLine* aLine );
  public:
    bool IsInBox( MPoints*  aPoints );
  public:
    bool IsIn( MPoints* aPoints, bool IncludeBoudPoi = true  );
    bool IsIn( MArea* aArea );
  public:
    bool IsOn( MPoints* aPoints );
};

class MPosition : public MPoint
{
  public:
    double AngX;
    double AngY;
    double AngZ;
  public:
    MPosition(double aX=0.0, double aY=0.0, double aZ = 0.0,double aAngX=0,double aAngY=0.0, double aAngZ=0.0);

  public:
    void SetAngleByDir( String aDir );    //"down","top","left","right","front","back"
    void SetAngleByRelDir( String aDir );

  public:
    void SetPosAlongDir( double aLen );   //沿方向向前移动aLen距离
    void SetPos( MPosition* aPos );

};

#define C_MPOINTS_WDT 4
#define C_MPOINTS_LINEWDT 1


class MPoints : public MObjectList_Temp<MPoint>
{
  public:
    void LoadFromString(String aStr,bool IsPixel);

  public:
    MPLine* GetSubPline( MPoint aPoi1, MPoint aPoi2, bool IsSort );  //给定aPoi1,aPOi2，获取两点之间的PLine

  public:
    void SetByLine( MPoint p1, MPoint p2, double aWdt );

  public:
    MPoints* KeyPoints( MPolygon* aRegion );
    MPoints* IntPoints( MPolygon* aRegion );      //与aRegion的交点

  public:
    void TrimByRegion( MPolygon* aRegion );
    void ClipByRegion( int aType, MPolygon* aRegion );
    void ExtendToRegion( MPolygon* aRegion );

  public:
    template <class T> bool _IsIn(T* aData);

    bool IsIn( MPoints* aPoints );
    bool IsIn( MPolygon* aPolgon );
    bool IsIn( MArea* aArea );

  #ifdef UseAddFlow

  public:
    afNode* Node;
    void DeleteNode(TAddFlow* aFlow);
  public:
    void Show( TAddFlow* aFlow );

  #endif
    
  //----Edges----
  private:
    MLines*  fEdges;
  protected:
    MLines* readEdges();
  public:
    __property MLines* Edges={read=readEdges};


  //----Wdt----
  public:
    double Wdt;          //缺省的Edge的宽度
    double LineWdt;      //缺省的Edge的单边宽度

  //线段自动"横平竖直"
  public:
    bool LOn;

  public:
    void operator = (MPoints& aP);
    void Copy( MPoints& aP );
    void CopyPoints( MPoints& aP );
  public:
    void GetExtent(  double& aMinX, double& aMinY, double& aMinZ, double& aMaxX, double& aMaxY, double& aMaxZ );

    double MinX();
    double MinY();
    double MinZ();
    double MaxX();
    double MaxY();
    double MaxZ();

    bool BoxContain( MPoint aPoint );

  public:
    MPoints* PointPrps( MPoint pTst );

  public:
    int IndexByX(double x);
    int FindEdgeByPoint( MPoint pTst );
    int FindNearEdgeByPoint( MPoint pTst );
    MPoint FindEdgePoint( MPoint pTst );

  public:
    void Copy( MPoints* aSrcPoints );
    void SaveToFile( String aFileName );
  public:
    void AddByLon( MPoint* aPoint );

  public:
    String VertsString();

  public:
    int IntPoiNumWithLine( MPoint P1, MPoint P2 );
    bool IsIntWithLine( MPoint P1, MPoint P2 );
    MPoints* IntPointsWithLine( MPoint p1, MPoint p2 );

  public:
    void Split( MPLine aPLine, MPoints* aPoints1, MPoints* aPoints2 );

  public:
    MPoints();
    MPoints( MPoints* aPoints );
    virtual _fastcall ~MPoints();
    void Init();

  public:
    double Len();
    double Len( int aVertNo );
    double LenOfPoint( MPoint p );

  public:
    void SortPoint( MPoint& p1, MPoint& p2 );
    void SortEdgePoints( MPoints* aPoints );
    void SortDivPoints( MPoints* aDivPoints );

  public:
    MPoints* Offset( int aDir, bool IsAddOld=false, bool IsCenter=false );              //偏置线处理
};

class MLine : public MGeoObject
{
  public:
    MPoint P1;
    MPoint P2;
  public:
    double Wdt;
  public:
    double k();
    double b();
  public:
    MLine();
    MLine(MPoint aP1,MPoint aP2);
  public:
    void Init();

  public:
    MLine operator +(MLine&);
    MLine operator -(MLine&);
    void operator =(MLine& aP);
    bool operator ==(MLine& aP);

  public:
    bool IsIn( MPoints* aPoints );
    bool IsIn( MArea* aArea );

    int IsInDetail( MPoints* aPoints );
    int IsInDetail( MArea* aArea );
};

class MLines : public MObjectList_Temp<MLine>
{
};

class MPLine : public MPoints
{
  //----SelectedGroup----
  //private:
  //  MPoints* fPoints;
  //public:
  //  __property MPoints* Points={read=fPoints};


  public:
    MPLine();
    virtual _fastcall ~MPLine();
};

class MPLines : public MObjectList_Temp<MPLine>
{
};

class MPolygon :  public MPoints
{
  public:
    int Type;          //0:外轮廓; 1:内轮廓

  private:
    MPolygon* fTrueRegion;                    //去除边后的轮廓边界
  protected:
    MPolygon* readTrueRegion();    
  public:
      __property MPolygon* TrueRegion={read=readTrueRegion};
      
  public:
    void ShowInfo( TStrings* aList );

  public:
    MPolygon();
    MPolygon( MPoints* aPoints );
    virtual _fastcall ~MPolygon();

  public:
    void BinSplit( bool IsTrimPLine, MPoints* aDivLine, MPolygon* aSubPoly1, MPolygon* aSubPoly2 );

    MPLines* ClipPLine( int aType, MPoints* aLine );    

  public:
    void SetByRect( TRect* aRect , double aLeftWdt=0.0, double aRightWdt=0.0, double aFrontWdt=0.0, double aBackWdt=0.0 );
    void SetByRect( double x0, double y0, double x1, double y1, double aLeftWdt=0.0, double aRightWdt=0.0, double aFrontWdt=0.0, double aBackWdt=0.0 );
};      

class MPolygons : public MObjectList_Temp<MPolygon>
{
  public:
    MPolygons();
    virtual _fastcall ~MPolygons();
  public:
    MPolygon* FindRegion( MPLine* aPLine, String aInType );
    MPolygon* FindRegion( MPoint* aPoi, String aInType );
    MPolygon* FindRegion( MPoint* aPoi );

    MPolygon* FindRegion_MaxLen( MPLine* aPLine );
    MPolygon* FindRegion_MaxLen( MPoint* aPoi );
  private:
    template <class T> MPolygon* _FindRegion( T* aT, String aInType );
};

class MArea : public MGeoObject
{
  //----Loops----
  private:
    MPolygons*   fLoops;
  public:
    __property MPolygons* Loops={read=fLoops};

  public:
    MPolygon* OutLoop();    //外轮廓
    MPolygons* InLoops();

  public:
    MArea();
    ~MArea();
};


class MArc : public MGeoObject
{
  //----Center----      //圆心
  private:
    MPoint*   fCenter;
  public:
    __property MPoint* Center={read=fCenter};

  //----R----          //半径
  private:
    double   fR;
  public:
    __property double R={read=fR,write=fR};

  //----ABegin----
  private:
    double   fABegin;
  public:
    __property double ABegin={read=fABegin,write=fABegin};

  //----AEnd----
  private:
    double   fAEnd;
  public:
    __property double AEnd={read=fAEnd,write=fAEnd};

  public:
    MArc();
    ~MArc();
};

//------------------------------------------------------------------------------

class MSection
{
  //----Edges----
  private:
    MGeoObjects*   fEdges;
  public:
    __property MGeoObjects* Edges={read=fEdges};

  public:
    MSection();
    ~MSection();
};

class MFeatureSection        // 由Section扫略、旋转、拉伸等生成的物体
{
  //----Section----
  private:
    MSection*   fSection;
  public:
    __property MSection* Section={read=fSection};
};

class MFeatureExtrude : public MFeatureSection
{
  //----PS----
  private:
    MPoint*   fPS;
  public:
    __property MPoint* PS={read=fPS};

  //----PE----
  private:
    MPoint*   fPE;
  public:
    __property MPoint* PE={read=fPE};
};

class MFeatureRevolve : public MFeatureSection
{
  //----Axis----
  private:
    MLine*   fAxis;
  public:
    __property MLine* Axis={read=fAxis};

  //----ABegin----
  private:
    Double   fABegin;
  public:
    __property Double ABegin={read=fABegin,write=fABegin};

  //----AEnd----
  private:
    Double   fAEnd;
  public:
    __property Double AEnd={read=fAEnd,write=fAEnd};
};

class MFeatureSweep : public MFeatureSection
{
  //----Path----
  private:
    MPolygon*   fPath;
  public:
    __property MPolygon* Path={read=fPath};
};

//------------------------------------------------------------------------------
void OffsetPoint( double x0, double y0, double k, double b, int aDir, double& x, double& y  );

MPoint* OffsetPointPrpLine( MPoint* aPoi1, MPoint* aPoi2, MPoint* aSrcPoi, double b, int aDir  );

MPoint* OffsetPoint( MPoint* aSrcPoi, double k, double b, int aDir );
void OffsetPoint( MPoint* aSrcPoi, double k, double b, int aDir, MPoint* aPoint );

int OffsetLineDir( MPoint p1, MPoint p2, MPoint pTo );
int OffsetLineDir( MPoint p1, MPoint p2, MPoint pFrom, MPoint pTo );
void OffsetLine( MLine* aSrcLin, double b, int aDir, MLine* aRetLine  );
void OffsetLine( MPoint p1, MPoint p2, MPoint pTo, MPoint* pOut1, MPoint* aPOut2 );

MPoints* OffsetPLine( MPoints* aPoints, double b, int aDir, bool IsAddOld, bool IsCenter  );
MPoints* _OffsetPLine( MPoints* aPoints, double b, int aDir, bool IsAddOld );

//------- IntLL ----------------------------------------------------------------

MPoint* ExtendLineToRegion( MPoint p1, MPoint p2, MPoints* aRegion );

bool IsIntLL( MPoint p1, MPoint p2, MPoint p3, MPoint p4, int aType1=0, int aType2=0  );
bool IsIntLL_Box( MPoint p1, MPoint p2, MPoint p3, MPoint p4 );

MPoint* IntLL( MPoint* aP11, MPoint* aP12, MPoint* aP21, MPoint* aP22 );
MPoint* IntLL( MLine* aLine1, MLine* aLine2 );
void IntLL( double k1, double b1, double k2, double b2, double* x, double* y );
MPoint* IntLL( double k1, double b1, double k2, double b2 );

void GetSamplePoints( MPoints* aCurveData, MPoints* aSamplePoints );
double GetSamplePointY( MPoints* aCurvePoints, double x );

bool IsEqual( double x1, double x2, double delta=0.0000001 );
bool IsEqual( MPoints* aPoints, MPoints* bPoints );

double YOnLine( MPoint* aPoint1, MPoint* aPoint2, double x );
double IsInDouble( double x, double x0, double x1, double delta=0.0000001  );

double Div_E( double f1, double f2, String aVarNames = "" );

//Line, K And B
void kbOfLine( MPoint p1, MPoint p2, double* k, double* b );
double kOfLine( MPoint p1, MPoint p2 );
double bOfLine( MPoint p1, MPoint p2 );

double kOfCrossLine( double k );
double kOfCrossLine( MPoint p1, MPoint p2 );
double LengthOfLine( MPoint p1, MPoint p2 );
double LengthOfPointAndLine( MPoint p1, MPoint p2, MPoint pTo );

double poiOnLine( MPoint pTst, MPoint p1, MPoint p2 );
bool IsPoiOnLine( MPoint pTst, MPoint p1, MPoint p2 );
bool IsPoiOnLine( MPoint pTst, MPoint p1, double k );

double poiPosInLine( MPoint pTst, MPoint p1, MPoint p2 );
bool IsPoiInLine( MPoint pTst, MPoint p1, MPoint p2, double  tole );
bool IsPoiInLineBox( MPoint pTst, MPoint p1, MPoint p2 );

void SwapPoint( MPoint& p1, MPoint& p2 );

template <class T> void Swap( T* aData1,T* aData2 )
{
  T x = *aData1;
  *aData1 = *aData2;
  *aData2 = x;
};

bool IsEqual( MPoint p1, MPoint p2 );

MPoint* PointPrp( MPoint P0, double k0, MPoint P1 );
MPoint* PointPrp( MPoint p1, MPoint p2, MPoint p );

void VectorCross( MPoint v1, MPoint v2, MPoint* v3 );
MPoint* VectorCross( MPoint v1, MPoint v2 );

//---------------------------------------------------------------------------
#endif
