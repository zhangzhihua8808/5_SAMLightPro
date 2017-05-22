//---------------------------------------------------------------------------

//#include "UnitAll.h"

#pragma hdrstop

#include "UnitMath.h"
#include <Math.hpp>
#include <Math.h>
#include "UnitTool_AddFlow.h"

#include "COMMON_FUNC.hpp"

//--------------------------- MCoordinate ------------------------------------

MCoordinate::MCoordinate()
{
    x0=0.0;
    y0=0.0;
    z0=0.0;
    xXaxis=1.0;
    yXaxis=0.0;
    zXaxis=0.0;
    xYaxis=0.0;
    yYaxia=1.0;
    zZaxis=0.0;
}

//--------------------------- Area --------------------------------------------
MArea::MArea()
{
  fLoops = new MPolygons();
}

MArea::~MArea()
{
  delete fLoops;
}

//---------------------------  MPolygons --------------------------------------

MPolygons::MPolygons()
{
}

_fastcall MPolygons::~MPolygons()
{
}

//------------------------------------------------------------------------------
//���ܣ�ȷ��aPline��������
//����: [ aPLine -- �ж϶��� ]
//      [ aInType -- "ALL"��ȫ����ԭ��"MAXLEN"--���; "FIRST" -- ��һ�����ж�ԭ�� "MOST" -- �������ж�ԭ�� ]
//------------------------------------------------------------------------------

template <class T> MPolygon* MPolygons::_FindRegion( T* aT, String aInType )
{
  if( aT == NULL )
    return NULL;

  for( int i=0; i<Count; i++ )
  {
    MPolygon* aRegion = Items[i];
    if( aT->IsIn( aRegion) )
      return aRegion;
  }

  aInType = UpperCase( aInType ) ;
  if( aInType == "ALL" )
    return NULL;
  else if ( aInType == "MAXLEN" )
    return FindRegion_MaxLen( aT );
  else
    return NULL;
    //throw Exception( "MPolygons::FindRegion!δע�������(" +aInType+ "!)" );
}

MPolygon* MPolygons::FindRegion( MPLine* aPLine, String aInType )
{
  return _FindRegion( aPLine, aInType );
}

MPolygon* MPolygons::FindRegion( MPoint* aPoi )
{
  return FindRegion( aPoi, "" );
}

MPolygon* MPolygons::FindRegion( MPoint* aPoi, String aInType )
{
  return _FindRegion( aPoi, aInType );
}

//----------------------------------------------------------------------
//˼·������aPline��ÿ��Region�еĳ��ȣ��ȽϺ�ȷ��aPline��������
//----------------------------------------------------------------------
MPolygon* MPolygons::FindRegion_MaxLen( MPLine* aPLine )
{
  if( aPLine == NULL )
    return NULL;

  MDoubleList* aLens = new MDoubleList;

  for( int i=0; i<Count; i++ )
  {
    MPolygon* aRegion = Items[i];

    MPLine* aP1 = new MPLine;
    *aP1 = *aPLine;
    aP1->ClipByRegion( 0, aRegion );

    double aLen = aP1->Len();
    aLens->Add( new double( aLen ) );
    delete aP1;
  }

  int aIndex = aLens->IndexMaximum( 0,aLens->Count-1 );
  if( aIndex<0 || aLens->Items[aIndex] == 0 )
  {
    delete aLens;
    return NULL;
  }

  delete aLens;
  return Items[aIndex];
}

MPolygon* MPolygons::FindRegion_MaxLen( MPoint* aPoi )
{
  return NULL;
}

//----------------------------- MPosition -------------------------------------
MPosition::MPosition( double aX, double aY, double aZ,
                      double aAngX, double aAngY, double aAngZ ) : MPoint( aX,aY,aZ )
{
  AngX = aAngX;
  AngY = aAngY;
  AngZ = aAngZ;
}

//--------------------------------------------------------------------------
//���ܣ��ط�����ǰ�ƶ�aLen����
//--------------------------------------------------------------------------
void MPosition::SetPosAlongDir( double aLen )
{
  x = x + aLen * cos( DegToRad( AngX ) );
  y = y + aLen * cos( DegToRad( AngY ) );
  z = z + aLen * cos( DegToRad( AngZ ) );
}

void MPosition::SetPos( MPosition* aPos )
{
  if( aPos==NULL )
    return;

  MPoint::SetPoint( (MPoint*)aPos );

  AngX = aPos->AngX;
  AngY = aPos->AngY;
  AngZ = aPos->AngZ;
}

//--------------------------------------------------------------------------
//˵������Է������� "down","up","left","right","front","back"
//      Ҫȷ��Ŀǰ�� "�н�����"��"��λ����"��"��������"
//      �����ң��ء���λ�����˶������Ƹ�����90/-90��
//      ��ǰ�����ء�ǰ�������˶������Ƹ�����0/180��
//      ���ϡ��£��ء����������˶������Ʒ�λ��90/-90��
//--------------------------------------------------------------------------
void MPosition::SetAngleByRelDir( String aDir )
{
   //??
}

//--------------------------------------------------------------------------
//˵�������Է������� "down","up","left","right","front","back"
//      ����ϵZ�����£�X�����ң�Y����ǰ
//--------------------------------------------------------------------------

void MPosition::SetAngleByDir( String aDir )
{
  aDir = UpperCase( aDir );
  if( aDir=="DOWN" )
  {
    AngX = -90;
    AngY = 90;
    AngZ = 0;
  }
  else if( aDir == "UP" )
  {
    AngX = 90;
    AngY = -90;
    AngZ = 180;
  }
  else if( aDir == "LEFT" )
  {
    AngX = 180;
    AngY = -90;
    AngZ = -90;
  }
  else if( aDir == "RIGHT" )
  {
    AngX = 0;
    AngY = 90;
    AngZ = -90;
  }
  else if( aDir == "FRONT" )
  {
    AngX = -90;
    AngY = 0;
    AngZ = -90;
  }
  else if( aDir == "BACK" )
  {
    AngX = 90;
    AngY = 180;
    AngZ = 90;
  }
  else
    throw Exception("δע��ķ���"+aDir);
}

//-------------------------MCurvePoint-----------------------------------------
MPoint::MPoint( double aX, double aY, double aZ )
{
  x = aX;
  y = aY;
  z = aZ;
}

MPoint::MPoint( MPoint* aPoint )
{
  if( aPoint==NULL )
  {
    x = 0;
    y = 0;
    z = 0;
  }
  else
  {
    Copy( aPoint );
  }
}

MPoint MPoint::operator +(MPoint aP2)
{
  MPoint aP;
  aP.x = x + aP2.x;
  aP.y = y + aP2.y;
  aP.z = z + aP2.z;
  return aP;
}

MPoint MPoint::operator -(MPoint aP2)
{
  MPoint aP;
  aP.x = x - aP2.x;
  aP.y = y - aP2.y;
  aP.z = z - aP2.z;
  return aP;
}

void MPoint::operator =(MPoint aP)
{
  x = aP.x;
  y = aP.y;
  z = aP.z;
}

bool MPoint::operator == (MPoint aP)
{
  return x == aP.x && y == aP.y && z == aP.z;
}

void  MPoint::Copy( MPoint* aSrcPoint )
{
  if( aSrcPoint==NULL )
    return;

  x = aSrcPoint->x;
  y = aSrcPoint->y;
  z = aSrcPoint->z;
}

void MPoint::SetPoint( MPoint* aPoint )
{
  Copy( aPoint );
}

void MPoint::ToVector( double v1[] )
{
  v1[0] = x;
  v1[1] = y;
  v1[2] = z;
}

void MPoint::LoadVector( double v1[] )
{
  x = v1[0];
  y = v1[1];
  z = v1[2];
}

bool MPoint::IsEqual( MPoint* aPoint )
{
  if( aPoint == NULL )
    return false;
  return ::IsEqual( x, aPoint->x ) && ::IsEqual( y, aPoint->y ) && ::IsEqual( z, aPoint->z ) ;
}

//-------------------------MCurvePoints-----------------------------------------
MPoints::MPoints( MPoints* aPoints )
{
  Init();

  if( aPoints==NULL )
    return;

  *this = *aPoints;
}

MPoints::MPoints()
{
  Init();
}

void MPoints::Init()
{
  LOn = false;
  fEdges = new MLines;
  Wdt = PixelsToTwips( C_MPOINTS_WDT );
  LineWdt = PixelsToTwips( C_MPOINTS_LINEWDT );
}

_fastcall MPoints::~MPoints()
{
  delete fEdges;
}

// "0,0;10.2,0.2,0.3;2,2,1"
void MPoints::LoadFromString( String aStr, bool IsPixel )
{
  Clear();
  TStrings* aStrings = splitToStrings( aStr, ";", false );

  for( int i=0; i<aStrings->Count; i++ )
  {
    String aStrItem = Trim( aStrings->Strings[i] );
    TStrings* aStringsItem =  splitToStrings( aStrItem, ",", false );

    MPoint* aPoint = new MPoint;

    int aCount = aStringsItem->Count;
    if( aCount>=1 )
      aPoint->x = StrToFloatDef( aStringsItem->Strings[0], 0.0 );
    if( aCount>=2 )
      aPoint->y = StrToFloatDef( aStringsItem->Strings[1], 0.0 );
    if( aCount>=3 )
      aPoint->z = StrToFloatDef( aStringsItem->Strings[2], 0.0 );

    if( IsPixel )
    {
      aPoint->x = PixelsToTwips( aPoint->x );
      aPoint->y = PixelsToTwips( aPoint->y );
      aPoint->z = PixelsToTwips( aPoint->z );
    }

    Add( aPoint );
    delete aStringsItem;
  }
  delete aStrings;
}

void MPoints::operator = (MPoints& aP)
{
  Copy( aP );
}

void MPoints::CopyPoints( MPoints& aP )
{
  if( this == &aP )
    return;

  Clear();
  for( int i=0; i<aP.Count; i++ )
     Add( new MPoint( *aP.Items[i] ) );
}

void MPoints::Copy( MPoints& aP )
{
  if( this == &aP )
    return;

  CopyPoints( aP );

  //Clear();
  //for( int i=0; i<aP.Count; i++ )
  //   Add( new MPoint( *aP.Items[i] ) );

  Wdt = aP.Wdt;
  LineWdt = aP.LineWdt;
  LOn = aP.LOn;

  #ifdef UseAddFlow

    Node = aP.Node;

  #endif
}

#ifdef UseAddFlow

void MPoints::DeleteNode(TAddFlow* aFlow)
{
  if( Node==NULL || aFlow==NULL )
    return;

  afDeletNode( aFlow, Node  );
  Node = NULL;
}

void MPoints::Show( TAddFlow* aFlow )
{
  Node = EditPLine( aFlow, Node, this, Wdt, LineWdt, 1, false );
}

#endif

//------------------------------------------------------------------------------
//����: [ aDir - ƫ�÷���1-��ࣻ-1-�ڲ� ]
//      [ IsAddOld - true/��ԭ���ĵ���ɷ�տռ䣻false/ֻȡƫ���� ]
//------------------------------------------------------------------------------

MPoints* MPoints::Offset( int aDir, bool IsAddOld, bool IsCenter )
{
  return OffsetPLine( this, -1, aDir, IsAddOld, IsCenter );
}

//------------------------------------------------------------------------------
//���ܣ���aDivLine��this�ָ�Ϊ��������( aPoints1, aPoints2 )
//˵����(1) ���ʺϽ�this����Ϊ�������ϼ��ϵ����
//      (2) thisΪ����
//������[ aDivLine : �з��� ]
//      [ IsTrimPLine: t / �޼��з��ߣ� ]
//      [ aSubPoints1 : ������1��2 ]
//------------------------------------------------------------------------------

void MPolygon::BinSplit( bool IsTrimPLine, MPoints* aDivLine, MPolygon* aSubPoly1, MPolygon* aSubPoly2 )
{
  if( Count<3 )
    throw Exception( "���������3�����޷��з֣�" );

  if( aDivLine==NULL || aSubPoly1==NULL || aSubPoly2==NULL )
    throw Exception( "NULLָ�룬�޷��з֣�" );

  if( aDivLine->Count<2 )
    throw Exception( "�ָ��߶˵�����2�����޷��з֣�" );

  //�޼�PLine
  if( IsTrimPLine )
  {
    //aDivLine->ClipByRegion( 0, this );
    aDivLine->TrimByRegion( this );
  }

  if( !aDivLine->IsIn( this ) )
    throw Exception( "�ֽ��ߵĵ��������⣬�޷��з֣�" );

  //����λ�öԶ˵�����
  SortDivPoints(aDivLine);

  //��ȡ�ָ�㼰���ڱ߽��ϵ�λ��

  MPoint* p1 = aDivLine->Items[0];
  MPoint* p2 = aDivLine->Items[aDivLine->Count-1];

  int aSeg1 = FindEdgeByPoint( *p1 );   //ȷ��PLine��ʼ����Area�߽��λ��
  int aSeg2 = FindEdgeByPoint( *p2 );
  if( aSeg1==-1 || aSeg2==-1 )
    throw Exception( "�ֽ��ߵ���ʼ����յ㲻������߽��ϣ��޷��з֣�" );

  int aDiv1 = Math::Min( aSeg1, aSeg2 );
  int aDiv2 = Math::Max( aSeg1, aSeg2 );

  //�γɵ�һ��������
  aSubPoly1->Clear();

  MLines* aEdgesRegion = this->Edges;
  MLines* aEdgesDiv = aDivLine->Edges;

  double aWdt = 0;

  for( int i=0; i<=aDiv1; i++ )                                   //0��aDiv1�Ķ˵�
  {
    aSubPoly1->Add( new MPoint( * ( Items[i] ) ) );

    if( i>=1 )
    {
      aWdt = aEdgesRegion->Items[i-1]->Wdt;
      aSubPoly1->Edges->Items[i-1]->Wdt = aWdt;
    }
  }
  aWdt = aEdgesRegion->Items[aDiv1]->Wdt;

  for( int i=0; i<aDivLine->Count; i++ )                          //�ָ��ߵĶ˵�
  {
    aSubPoly1->Add( new MPoint( * ( aDivLine->Items[i] ) ) );

    if( aSubPoly1->Count > 1 )
    {
      if( i>0 )                                    //��һ���㣬�� aSubPoly1->Count>1������aDiv1>=1
        aWdt = aEdgesDiv->Items[i-1]->Wdt;

      aSubPoly1->Edges->Items[aSubPoly1->Count-2]->Wdt = aWdt;
    }
  }
  aWdt = aEdgesDiv->Items[aDivLine->Count-2]->Wdt;

  for( int i=aDiv2+1; i<Count; i++ )                              //aDiv2�������Ķ˵�
  {
    aSubPoly1->Add( new MPoint( * ( Items[i] ) ) );

    if( aSubPoly1->Count > 1 )
    {
      if( i>0 )                                    //��һ���㣬�� aSubPoly1->Count>1������aDiv1>=1
        aWdt = aEdgesRegion->Items[i-1]->Wdt;

      aSubPoly1->Edges->Items[aSubPoly1->Count-2]->Wdt = aWdt;
    }
  }


  //�γɵڶ���������
  aSubPoly2->Clear();
  aWdt = 0.0;

  for( int i=aDivLine->Count-1; i>=0; i-- )                          //�ָ��ߵĶ˵�
  {
    aSubPoly2->Add( new MPoint( * ( aDivLine->Items[i] ) ) );

    if( aSubPoly2->Count > 1 )
    {
      aWdt = aEdgesDiv->Items[i]->Wdt;
      aSubPoly2->Edges->Items[aSubPoly2->Count-2]->Wdt = aWdt;
    }
  }

  for( int i=aDiv1+1; i<=aDiv2; i++ )
  {
    aSubPoly2->Add( new MPoint( * ( Items[i] ) ) );    //�м䲿�ֵĶ˵�

    if( aSubPoly2->Count > 1 )
    {
      aWdt = aEdgesRegion->Items[i-1]->Wdt;
      aSubPoly2->Edges->Items[aSubPoly2->Count-2]->Wdt = aWdt;
    }
  }

  aSubPoly2->Add( new MPoint( * ( aDivLine->Items[aDivLine->Count-1] ) ) );
  if( aSubPoly2->Count > 1 )
  {
    aWdt = aEdgesRegion->Items[aDiv2]->Wdt;
    aSubPoly2->Edges->Items[aSubPoly2->Count-2]->Wdt = aWdt;
  }
}

//------------------------------------------------------------------------------
//���ܣ�ͨ������aRegion��this���вü�
//������[ aType : 0 / InRegion; 1 / OutRegion  ]
//------------------------------------------------------------------------------

void MPoints::ClipByRegion( int aType, MPolygon* aRegion )
{
  //Clear();
  if( aRegion==NULL )
    return;

  MPLines* aPlines = aRegion->ClipPLine( aType, this );
  if( aPlines->Count > 0 )
    this->CopyPoints( * aPlines->Items[0] );
  else
    this->Clear();

  delete aPlines;
}


MPLines* MPolygon::ClipPLine( int aType, MPoints* aLine )
{
  MPLines* aPlines = new MPLines;
  if( aLine == NULL )
    return aPlines;

  // ��ʼ�� + ����Ľ��㼯�� + �յ�
  MPoints* aKeyPoints = aLine->KeyPoints( this );
  if( aKeyPoints->Count<1 )
    return aPlines;

  //��ȡ��ʼ��λ��
  MPoint* aPoi = aLine->Items[0];
  int aBgn;
  if( aPoi->IsIn( this ) )
  {
    if( aType == 0 )
       aBgn = 0;
     else
       aBgn = 1;
  }
  else
  {
    if( aType == 1 )
       aBgn = 0;
     else
       aBgn = 1;
  }

  for( int i=aBgn; i<aKeyPoints->Count-1; i = i + 2 )
  {
    MPoint* aPoi1 = aKeyPoints->Items[i];
    MPoint* aPoi2 = aKeyPoints->Items[i+1];
    MPLine* aPline = aLine->GetSubPline( *aPoi1, *aPoi2, false );
    if( aPline!=NULL )
      aPlines->Add( aPline );
  }

  return aPlines;
}

double MPoints::Len()
{
  return Len( Count-1 );
}

double MPoints::Len( int aVertNo )
{
  double aLen = 0.0;

  int aNum = Math::Min( aVertNo, Count-1 );
  for( int i=0; i<aNum; i++ )
    aLen = aLen + LengthOfLine( *Items[i], *Items[i+1] );

  return aLen;
}


double MPoints::LenOfPoint( MPoint p )
{
  int aSeg = FindEdgeByPoint( p );   //ȷ��PLine��ʼ����Area�߽��λ��
  if( aSeg < 0 )
    return -1;

  return Len( aSeg ) + LengthOfLine( *Items[aSeg], p );
}

void MPoints::SortPoint( MPoint& p1, MPoint& p2 )
{
  if( LenOfPoint( p1 ) >  LenOfPoint( p2 ) )
    SwapPoint( p1, p2 );
}

void SwapPoint( MPoint& p1, MPoint& p2 )
{
  MPoint aP = p1;
  p1 = p2;
  p2 = aP;
}

//template <class T> void Swap( T* aData1,T* aData2 )


//���ܣ���ȡ aPoi1��aPoi2֮���Pline���߶�

MPLine* MPoints::GetSubPline( MPoint aPoi1, MPoint aPoi2, bool IsSort )
{

  //����PLine����
  if( IsSort )
    SortPoint( aPoi1, aPoi2 );

  MPLine* aSubPLine = new MPLine;

  int aSeg1 = FindEdgeByPoint( aPoi1 );   //ȷ��PLine��ʼ����Area�߽��λ��
  int aSeg2 = FindEdgeByPoint( aPoi2 );
  if( aSeg1==-1 || aSeg2==-1 )
    return aSubPLine;

  aSubPLine->Add( new MPoint( aPoi1 ) );

  for( int i=aSeg1+1; i<=aSeg2; i++ )
     aSubPLine->Add( new MPoint( *Items[i] ) );

  aSubPLine->Add( new MPoint( aPoi2 ) );
  return aSubPLine;
}

//�ָ�������ȷ�� ��ʼ��λ�� �� ��ֹ��֮ǰ
void MPoints::SortDivPoints( MPoints* aDivPoints )
{
  if( aDivPoints->Count < 2 )
    return;

  MPoint* ps = aDivPoints->Items[0];
  MPoint* pe = aDivPoints->Items[aDivPoints->Count-1];

  double rs =  LenOfPoint( *ps ) ;
  double re =  LenOfPoint( *pe ) ;

  if( rs < 0 || re < 0  ||           //��ʼ�����ֹ�㲻�ڱ߽���
      rs <= re )
    return;

  aDivPoints->Reverse();
}

//������this�ϵ�λ�ã��Ե㼯��[aEdgePoints]����
void MPoints::SortEdgePoints( MPoints* aEdgePoints )
{
  if( aEdgePoints->Count < 2 )
    return;

  //
  MDoubleList* aLens = new MDoubleList;

  double aLen = Len();
  if( aLen==0.0 )
    return;

  //��ȡ�������λ��
  for( int i=0; i<aEdgePoints->Count; i++ )
  {
    MPoint* aPoi = aEdgePoints->Items[i];
    aLens->Add( new double ( LenOfPoint( *aPoi ) / aLen ) ) ;
  }

  //����
  for( int i=0; i<aLens->Count-1; i++ )
  {
    // [i, aLens->Count-1]�������Сλ��
    int aIndex = aLens->IndexMinimum( i, aLens->Count-1 );
    if( aIndex==-1 )
      continue;

    if( i!=aIndex )
    {
      aEdgePoints->Exchange( i, aIndex );
      aLens->Exchange( i, aIndex );
    }
  }

  delete aLens;
}

//---------------------------------------------------------------------------
//���ܣ�EndPoint1 + SortIntPoints + EndPoint2
//������[ ����: aRegion , ���� ]
//      [ this��aRegion�Ĺؼ����Ƶ� ]
//---------------------------------------------------------------------------

MPoints* MPoints::KeyPoints( MPolygon* aRegion )
{
  MPoints* aIntPoints = IntPoints( aRegion );

  if( Count<=0 )
    return aIntPoints;

  //�޽���
  if( aIntPoints->Count<=0 )
  {
    aIntPoints->Insert( 0, new MPoint( *Items[0] ) );
    aIntPoints->Add( new MPoint( *Items[Count-1] ) );
    return aIntPoints;
  }

  //��������
  SortEdgePoints( aIntPoints );

  //������ʼ��
  if(  !IsEqual( *Items[0], *aIntPoints->Items[0] ) )
    aIntPoints->Insert( 0, new MPoint( *Items[0] ) );

  //���������
  if( !IsEqual( Items[Count-1], aIntPoints->Items[ aIntPoints->Count-1 ] ) )
    aIntPoints->Add( new MPoint( *Items[Count-1]) );

   return aIntPoints;
}

bool IsEqual( MPoint p1, MPoint p2 )
{
  return IsEqual( p1.x, p2.x ) && IsEqual( p1.y, p2.y ) && IsEqual( p1.z, p2.z );
}

//���ܣ���aRegion�Ľ���
MPoints* MPoints::IntPoints( MPolygon* aRegion )
{
  MPoints* aPoints = new MPoints;
  if( aRegion == NULL )
    return aPoints;

  for( int i=0; i<Count-1; i++ )
  {
    MPoint* p1 = Items[i];
    MPoint* p2 = Items[i+1];

    MPoints* bPoints = aRegion->IntPointsWithLine( *p1, *p2 );

    aPoints->Merge( bPoints, false );
    bPoints->Clear();
    delete bPoints;
  }

  return aPoints;
}

//���ܣ�����PLine�����˵�Region�߽�
void MPoints::ExtendToRegion( MPolygon* aRegion )
{
  if( Count<2 )
    return;

  MPoint* aPoint = ExtendLineToRegion( *Items[1], *Items[0], aRegion );
  if( aPoint->x!=MAXFLOAT )
    *Items[0] = *aPoint;
  delete aPoint;

  aPoint = ExtendLineToRegion( *Items[Count-2], *Items[Count-1], aRegion );
  if( aPoint->x!=MAXFLOAT )
    *Items[Count-1] = *aPoint;
  delete aPoint;
}


void MPoints::TrimByRegion( MPolygon* aRegion )
{
   //�޼�PLine����
   ClipByRegion( 0, aRegion );

   //����PLine����
   ExtendToRegion( aRegion );
}

//���ܣ���LON��ʽ����Vert
void MPoints::AddByLon( MPoint* aPoint )
{
   if( aPoint==NULL )
     return;

   if( LOn && Count>=1 )
   {
     MPoint* P0 = Items[ Count-1 ];
     double k = kOfLine( *P0, *aPoint );

     if( fabs( k )<1 )
       k = 0;
     else
       k = MAXFLOAT;

     MPoint* aPrpPoi = PointPrp( *P0,k,*aPoint );
     *aPoint = *aPrpPoi;
     delete aPrpPoi;
   }

   Add( aPoint );
}

//-----------------------------------------------
//--����: �����pTst���߶�[p1,p2]�е�λ��(num��)
//-----------------------------------------------
int MPoints::FindNearEdgeByPoint( MPoint pTst )
{
  MPoint aPoi = FindEdgePoint( pTst );

  if( aPoi.x == MAXFLOAT )
    return -1;

  return FindEdgeByPoint( aPoi );
}

//-----------------------------------------------
//����: �����pTst���߶�[p1,p2]�е�λ��(num��)
//-----------------------------------------------

MPoint MPoints::FindEdgePoint( MPoint pTst )
{
   MPoints* aPoints = PointPrps( pTst );

   MPoint aPoint( MAXFLOAT,MAXFLOAT,MAXFLOAT );

   double aLen;
   for( int i=0; i<aPoints->Count; i++ )
   {
     if( i==0 )
     {
       aPoint = * aPoints->Items[i];
       aLen = LengthOfLine( aPoint, pTst );
     }
     else
     {
       double aLen1 = LengthOfLine( *aPoints->Items[i], pTst );
       if( aLen1<aLen )
       {
         aPoint = *aPoints->Items[i];
         aLen = aLen1;
       }
     }
   }

   delete aPoints;
   return aPoint;
}

MPoints* MPoints::PointPrps( MPoint pTst )
{
  MPoints* aPoints = new MPoints;

  for( int i=0; i<Count-1; i++ )
  {
    MPoint* p1 = Items[i];
    MPoint* p2 = Items[ i+1 ];

    //���㴹��
    MPoint* aPntPrp = PointPrp( *p1, *p2, pTst );

    if( IsPoiInLine( *aPntPrp, *p1, *p2, 0.000001 ) )
      aPoints->Add( aPntPrp );
    else
      delete aPntPrp;
  }

  return aPoints;
}

int MPoints::FindEdgeByPoint( MPoint pTst )
{
  double    kOn,kPos;
  for( int i=0; i<Count-1; i++ )
  {
    MPoint* p1 = Items[i];
    MPoint* p2 = Items[ i+1 ];

    if( !IsPoiInLineBox( pTst, *p1, *p2 ) )
      continue;

    if( ! IsPoiOnLine( pTst, *p1, *p2  ) )
      continue;

    if( IsPoiInLine( pTst, *p1, *p2, 0.000001 ) )
      return i;
  }
  return -1;
}

bool IsPoiInLineBox( MPoint pTst, MPoint p1, MPoint p2 )
{
  double aMinX = Min( p1.x, p2.x );
  double aMinY = Min( p1.y, p2.y );
  double aMinZ = Min( p1.z, p2.z );

  double aMaxX = Max( p1.x, p2.x );
  double aMaxY = Max( p1.y, p2.y );
  double aMaxZ = Max( p1.z, p2.z );

  return ! ( pTst.x < aMinX || pTst.y < aMinY || pTst.z < aMinZ ||
             pTst.x > aMaxX || pTst.y > aMaxY || pTst.z > aMaxZ );
}

double MPoints::MinX()
{
  double aMinX = MAXFLOAT;

  for( int i=0; i<Count; i++ )
  {
    MPoint* aPoint = Items[i];
    aMinX = Min( aMinX,  aPoint->x );
  }
  return aMinX;
}

double MPoints::MinY()
{
  double aMinY = MAXFLOAT;

  for( int i=0; i<Count; i++ )
  {
    MPoint* aPoint = Items[i];
    aMinY = Min( aMinY,  aPoint->y );
  }
  return aMinY;
}

double MPoints::MinZ()
{
  double aMinZ = MAXFLOAT;

  for( int i=0; i<Count; i++ )
  {
    MPoint* aPoint = Items[i];
    aMinZ = Min( aMinZ,  aPoint->z );
  }
  return aMinZ;
}

double MPoints::MaxX()
{
  double aMaxX = -MAXFLOAT;

  for( int i=0; i<Count; i++ )
  {
    MPoint* aPoint = Items[i];
    aMaxX = Max( aMaxX,  aPoint->x );
  }
  return aMaxX;
}

double MPoints::MaxY()
{
  double aMaxY = -MAXFLOAT;

  for( int i=0; i<Count; i++ )
  {
    MPoint* aPoint = Items[i];
    aMaxY = Max( aMaxY,  aPoint->y );
  }
  return aMaxY;
}

double MPoints::MaxZ()
{
  double aMaxZ = -MAXFLOAT;

  for( int i=0; i<Count; i++ )
  {
    MPoint* aPoint = Items[i];
    aMaxZ = Max( aMaxZ,  aPoint->z );
  }
  return aMaxZ;
}

void MPoints::GetExtent( double& aMinX, double& aMinY, double& aMinZ, double& aMaxX, double& aMaxY, double& aMaxZ )
{
  aMinX = MinX();
  aMinY = MinY();
  aMinZ = MinZ();

  aMaxX = MaxX();
  aMaxY = MaxY();
  aMaxZ = MaxZ();

 /* aMinX = MAXFLOAT;
  aMinY = MAXFLOAT;
  aMinZ = MAXFLOAT;

  aMaxX = -MAXFLOAT;
  aMaxY = -MAXFLOAT;
  aMaxZ = -MAXFLOAT;

  for( int i=0; i<Count; i++ )
  {
    MPoint* aPoint = Items[i];

    aMinX = Min( aMinX,  aPoint->x );
    aMinY = Min( aMinY,  aPoint->y );
    aMinZ = Min( aMinZ,  aPoint->z );

    aMaxX = Max( aMaxX,  aPoint->x );
    aMaxY = Max( aMaxY,  aPoint->y );
    aMaxZ = Max( aMaxZ,  aPoint->z );
  } */
}

int MPoints::IndexByX(double x)
{
  int i;
  for( i=0; i<Count-1; i++ )
     if( IsInDouble( x, Items[i]->x,  Items[i+1]->x ) )
       return i;
  return Count;
}

void  MPoints::Copy( MPoints* aSrcPoints )
{
  Clear();

  if( aSrcPoints==NULL )
    return;

  for( int i=0; i<aSrcPoints->Count; i++ )
  {
    MPoint* aPoint = new MPoint;
    aPoint->Copy( aSrcPoints->Items[i] );
    Add( aPoint );
  }
}

void MPoints::SaveToFile( String aFileName )
{
  TStrings* aList = new TStringList;

  for( int i=0; i<Count; i++ )
  {
    MPoint* aPoint = Items[i];
    aList->Add( FloatToStr(aPoint->x) + "," + FloatToStr( aPoint->y ) + "," + FloatToStr( aPoint->z ) );
  }
  aList->SaveToFile( aFileName );
  delete aList;
}

String MPoints::VertsString()
{
  String aStr = "";
  for( int i=0; i<Count; i++ )
  {
    MPoint* aPoint = Items[i];
    aStr = aStr + "(" + FloatToStr(aPoint->x) + "," + FloatToStr( aPoint->y ) + "," + FloatToStr( aPoint->z ) + ")";
  }

  return aStr;
}

//----------------------------MPolygon------------------------------------------
MPLine::MPLine()
{
}

_fastcall MPLine::~MPLine()
{
}

void MPoints::SetByLine( MPoint p1, MPoint p2, double aWdt )
{
  Clear();

  Add( new MPoint( p1 ) );
  Add( new MPoint( p2 ) );

  Edges->Items[0]->Wdt = aWdt;
}

//----------------------------MPolygon------------------------------------------


MPolygon::MPolygon()
{
}

MPolygon::MPolygon( MPoints* aPoints ) : MPoints( aPoints )
{
  fTrueRegion = NULL;
}

_fastcall MPolygon::~MPolygon()
{
  if( fTrueRegion != NULL )
    delete fTrueRegion;
}

MPolygon* MPolygon::readTrueRegion()
{
  if( fTrueRegion != NULL )
    delete fTrueRegion;

  MPoints* aPoints = Offset( -1 );
  fTrueRegion = new MPolygon( aPoints );
  delete aPoints;

  return fTrueRegion;
}

void MPolygon::SetByRect( double x0, double y0, double x1, double y1, double aLeftWdt, double aRightWdt, double aFrontWdt, double aBackWdt )
{
   Clear();

   Add( new MPoint( x0, y0 ) );
   Add( new MPoint( x0, y1 ) );
   Add( new MPoint( x1, y1 ) );
   Add( new MPoint( x1, y0 ) );
   Add( new MPoint( x0, y0 ) );

   MLines* aEdges = Edges;

   aEdges->Items[0]->Wdt = aLeftWdt;
   aEdges->Items[1]->Wdt = aFrontWdt;
   aEdges->Items[2]->Wdt = aRightWdt;
   aEdges->Items[3]->Wdt = aBackWdt;
}

void MPolygon::SetByRect( TRect* aRect, double aLeftWdt, double aRightWdt, double aFrontWdt, double aBackWdt )
{
   if( aRect==NULL )
     return;

  SetByRect( aRect->left, aRect->top, aRect->Right, aRect->bottom );
}

/*   Clear();

   if( aRect==NULL )
     return;

   Add( new MPoint( aRect->left, aRect->top ) );
   Add( new MPoint( aRect->left, aRect->bottom ) );
   Add( new MPoint( aRect->Right, aRect->bottom ) );
   Add( new MPoint( aRect->Right, aRect->top ) );
   Add( new MPoint( aRect->left, aRect->top ) );

   MLines* aEdges = Edges;

   aEdges->Items[0]->Wdt = aLeftWdt;
   aEdges->Items[1]->Wdt = aFrontWdt;
   aEdges->Items[2]->Wdt = aRightWdt;
   aEdges->Items[3]->Wdt = aBackWdt;
}  */


//-------------------------------MLine------------------------------------------

MLine::MLine(MPoint aP1,MPoint aP2)
{
  Init();
  P1.Copy( &aP1 );
  P2.Copy( &aP2 );
}

MLine::MLine()
{
  Init();
}

void MLine::Init()
{
  Wdt=0;
}

MLine MLine::operator +(MLine& aLine)
{
  MLine bLine;
  bLine.P1 = this->P1 + aLine.P1;
  bLine.P2 = this->P2 + aLine.P2;
  return bLine;
}

MLine MLine::operator -(MLine& aLine)
{
  MLine bLine;
  bLine.P1 = this->P1 - aLine.P1;
  bLine.P2 = this->P2 - aLine.P2;
  return bLine;
}

void MLine::operator =(MLine& aLine)
{
  P1 = aLine.P1;
  P2 = aLine.P2;
  Wdt = aLine.Wdt;
}

bool MLine::operator ==(MLine& aLine)
{
  return P1 == aLine.P1 && P2 == aLine.P2;
}

double MLine::k()
{
  return kOfLine( P1, P2 );
}

double MLine::b()
{
  return bOfLine( P1, P2 );
}

//���Ӳ��ԣ�����ٶ�
bool MPoint::IsInBox( MPoints* aPoints )
{
  if( aPoints==NULL || aPoints->Count<3 )
    return false;

  double aMinX, aMinY, aMinZ, aMaxX, aMaxY, aMaxZ;
  aPoints->GetExtent(  aMinX, aMinY, aMinZ, aMaxX, aMaxY, aMaxZ );

  return x>=aMinX && x<=aMaxX &&
         y>=aMinY && y<=aMaxY &&
         z>=aMinZ && z<=aMaxZ;
}

//------------------------------------------------------------------------------
//���ܣ��б�this�Ƿ���aPoints�ڲ�
//˵����(1) ͨ��this��һ����������L������L��aPoints�Ľ��㣨ʵ����������Ϊż������Ϊ�ⲿ�㣻��Ϊ��������Ϊ�ڲ���
//������[ aPoints : �����߽� ]
//      [ IncludeOn : �Ƿ�����߽��ϵĵ� ]
//------------------------------------------------------------------------------
bool MPoint::IsIn( MPoints* aPoints, bool IncludeBoudPoi )
{
  if( aPoints==NULL || aPoints->Count <= 2 )
    return false;

  //���Ӳ��ԣ�����ٶ�
  if( !IsInBox(aPoints) )
    return false;

  //Pointλ��Points�ı߽�  
  if( IsOn( aPoints ) )
    return IncludeBoudPoi;

  //��������Զ����
  MPoint P2;
  P2.x = aPoints->MaxX() + 10.0;
  P2.y = y;

  //���㽻�����
  int aNum = aPoints->IntPoiNumWithLine( *this, P2 );

  //ż�������ⲿ; ���������ڲ�
  return aNum % 2 != 0;
}

bool MPoint::IsOn( MPoints* aPoints )
{
  return aPoints->FindEdgeByPoint( this ) >= 0;
}


bool MPoints::IsIntWithLine( MPoint P1, MPoint P2 )
{
  return IntPoiNumWithLine( P1,P2 ) > 0;
}


//ֱ����aPoints�Ľ��㣨ʵ������
int MPoints::IntPoiNumWithLine( MPoint P1, MPoint P2 )
{
  int Num = 0;

  for( int i=0; i<Count-1; i++ )
  {
    MPoint* P3 = Items[i];
    MPoint* P4 = Items[i+1];

    //����ʵ����
    if( IsIntLL( P1, P2, *P3, *P4, 0, 1 ) )
      Num = Num + 1;
  }
  return Num;
}

MPoints* MPoints::IntPointsWithLine( MPoint p1, MPoint p2 )
{
  MPoints* aPoints = new MPoints;

   //if( !IsIntWithLine( p1, p2 ) )
   //   return new MPoint( MAXFLOAT, MAXFLOAT, 0 );;

   for( int i=0; i<Count-1; i++ )
   {
     MPoint* p3 = Items[i];
     MPoint* p4 = Items[i+1];

     if( !IsIntLL( p1, p2, *p3, *p4 ) )
       continue;

     aPoints->Add( IntLL( &p1, &p2, p3, p4  ) );
   }

   return aPoints;
}

bool MPoints::IsIn( MPoints* aPoints )
{
   return _IsIn( aPoints );
}

bool MPoints::IsIn( MPolygon* aPolgon )
{
   return _IsIn( aPolgon );
}

bool MPoints::IsIn( MArea* aArea )
{
   return _IsIn( aArea );
}

MLines* MPoints::readEdges()
{
  //�����µ�Edges
  MLines* aEdges = new MLines;
  for( int i=0; i<Count-1; i++ )
    aEdges->Add( new MLine( *Items[i], *Items[i+1] ) );

  //����ԭ��Edges������
  for( int i=0; i < Math::Min( fEdges->Count, aEdges->Count); i++ )
    aEdges->Items[i]->Wdt = fEdges->Items[i]->Wdt;

  delete fEdges;
  fEdges = aEdges;
  return fEdges;
}

template <class T> bool MPoints::_IsIn(T* aData)
{
  MLines* aSegs = Edges;
  for( int i=0; i<aSegs->Count; i++ )
  {
    MLine* aSeg = aSegs->Items[i];

    if( !aSeg->IsIn( aData ) )
      return false;
  }

  //aSegs->Clear();
  return true;
}

bool MLine::IsIn( MPoints* aPoints )
{
  return IsInDetail( aPoints ) == 2;
}

//0��NotIn
//2��In
//1��In OutLoop But Int with InLoops

int MLine::IsInDetail( MPoints* aPoints )
{
   int aNum = 0;
   if( P1.IsIn( aPoints ) )
     aNum = aNum+1;
   if( P2.IsIn( aPoints ) )
     aNum = aNum+1;
   return aNum;
}


bool MLine::IsIn( MArea* aArea )
{
  return IsInDetail( aArea ) == 2;
}

//0��NotIn
//2��In
//1��In OutLoop But Int with InLoops

int MLine::IsInDetail( MArea* aArea )
{
  MPolygon* pOut = aArea->OutLoop();
  if( pOut==NULL )
    return 0;

  //������
  if( IsIn( pOut ) == false )
    return 0;

  //������
  MPolygons* pInLoops = aArea->InLoops();
  for( int i=0; i<pInLoops->Count; i++ )
  {
    MPolygon* aP = pInLoops->Items[i];
    if( IsInDetail( aP ) == 1 )
      return 1;
  }

  pInLoops->Clear();
  delete pInLoops;

  return 2;
}

//--------------------------------MArc------------------------------------------
MArc::MArc()
{
  fCenter = new MPoint;
  fR = 0.0;
  fABegin = 0.0;
  fAEnd = 360.0;
}

MArc::~MArc()
{
  delete fCenter;
}

//--------------------------------MSection--------------------------------------
MSection::MSection()
{
  fEdges = new MGeoObjects;
}

MSection::~MSection()
{
  delete fEdges;
}

//------------------------ ���� ------------------------------------------------

double MySign( double ax )
{
  if( ax >= 0.0 )
    return 1.0;
  else
    return -1.0;
}

//------------------------------------------------------------------------
//����(x0,y0)��k������ƫ�ã�����Ϊb ( aDirΪ1 ���� -1 )
//��ʽ��k = ( y-y0 ) / (x - x0)
//      b = sqrt( (x-x0)*(x-x0) + (y-y0)*(y-y0) )
//------------------------------------------------------------------------

void OffsetPoint( double x0, double y0, double k, double b, int aDir, double& x, double& y  )
{                   
  if( k==MAXFLOAT )
  {
    x = x0;
    y = y0 + b * MySign( aDir );
    return;
  }

  double a = sqrt( b*b / ( 1+k*k ) ) * MySign( aDir );
  x = x0 + a;
  y = y0 + k * a;
}

void OffsetPoint( MPoint* aSrcPoi, double k, double b, int aDir,  MPoint* aRetPoi )
{
  if( aSrcPoi==NULL || aRetPoi==NULL )
    throw Exception("OffsetPoint����aSrcPoiΪNULL��");

  OffsetPoint( aSrcPoi->x, aSrcPoi->y, k, b, aDir, aRetPoi->x, aRetPoi->y );
}

MPoint* OffsetPoint( MPoint* aSrcPoi, double k, double b, int aDir  )
{
  MPoint* aRetPoi = new MPoint;
  OffsetPoint( aSrcPoi, k, b, aDir, aRetPoi  );
  return aRetPoi;
}

//��ֱ��ֱ��[aPoi1,aPoi2]����Offset aSrcPoi

MPoint* OffsetPointPrpLine( MPoint* aPoi1, MPoint* aPoi2, MPoint* aSrcPoi, double b, int aDir  )
{
  return OffsetPoint( aSrcPoi,  kOfCrossLine( aPoi1, aPoi2 ), b, aDir );
}


//------------------------------------------------------------------------------
//������[ p1,p2 : ��Offset��ֱ�߶˵� ]
//      [ pTo : ָʾ��Offset�ķ���;��� ]
//      [ pOut1, pOut2 ]
//------------------------------------------------------------------------------

double LengthOfPointAndLine( MPoint p1, MPoint p2, MPoint pTo )
{
  MPoint* aPoiPrp = PointPrp( p1, p2, pTo );
  double aWdt = LengthOfLine( pTo, aPoiPrp );

  delete aPoiPrp;
  return aWdt;
}

void OffsetLine( MPoint p1, MPoint p2, MPoint pTo, MPoint* pOut1, MPoint* pOut2 )
{
  double aWdt = LengthOfPointAndLine( p1, p2, pTo );
  int aDir = OffsetLineDir( p1, p2, pTo );

  *pOut1 = *OffsetPointPrpLine( &p1, &p2, &p1, aWdt, aDir );
  *pOut2 = *OffsetPointPrpLine( &p1, &p2, &p2, aWdt, aDir );
}

//ȷ��ƫ�Ʒ���
//˵����ƫ�ƺ�����ߵķ�����pToһ��

int OffsetLineDir( MPoint p1, MPoint p2, MPoint pTo )
{
  MPoint* pFrom = PointPrp( p1, p2, pTo );

  int aDir = OffsetLineDir( p1, p2, *pFrom, pTo );
  delete pFrom;  
  return aDir;
}

//ȷ��ƫ�Ʒ���
//˵����ƫ�ƺ�����ߵķ����� [pFrom, pTo]һ��

int OffsetLineDir( MPoint p1, MPoint p2, MPoint pFrom, MPoint pTo )
{
  MPoint* p1_1 = OffsetPointPrpLine( &p1, &p2, &p1, 1.0, 1 );

  MPoint* c1 = VectorCross( pTo - pFrom, p2 - p1 );
  MPoint* c2 = VectorCross( *p1_1 - p1, p2 - p1 );


  delete p1_1;

  int aDir;
  if( c1->z * c2->z > 0 )
    aDir = 1.0;
  else
    aDir = -1.0;

  delete c1;
  delete c2;
  return aDir;
}

void OffsetLine( MLine* aSrcLin, double b, int aDir, MLine* aRetLine  )
{
  double k = aSrcLin->k();
  double k1 = kOfCrossLine(k);

  OffsetPoint( &aSrcLin->P1, k1, b, aDir, &aRetLine->P1  );
  OffsetPoint( &aSrcLin->P2, k1, b, aDir, &aRetLine->P2 );
}


//ԭ�������һ��ƫ���ߣ����
int CalOffsetDir( MPoints* aPoints, int aDir )
{
  //С��3���㣬�޷�ȷ�������
  if( aPoints==NULL || aPoints->Count<3 )
    return aDir;

  //MPoints* bPoints = new MPoints;

  //bPoints->Add( new MPoint( *aPoints->Items[0] ) );
  //bPoints->Add( new MPoint( *aPoints->Items[1] ) );
  //bPoints->Add( new MPoint( *aPoints->Items[2] ) );

  MPoints* cPoints = _OffsetPLine( aPoints, 1, aDir, false );

  if( cPoints==NULL || cPoints->Count<2 )
  {
    //delete bPoints;
    delete cPoints;
    return aDir;
  }

  double aLen = cPoints->Len() - aPoints->Len();  //LengthOfLine( *cPoints->Items[0], *cPoints->Items[1] ) - LengthOfLine( *aPoints->Items[0], *aPoints->Items[1] );

  //delete bPoints;
  delete cPoints;

  if( aLen * aDir < 0  )
    return 1;
  else
    return -1;
}

//------------------------------------------------------------------------------
//���ܣ�����OffsetLine
//������[ aPoints - ��Offset��PolyLine ]
//      [ b - ƫ�þ��� >0�����е�ͳһƫ�ã� <0����Edges�����Wdtȷ��ƫ�þ��� ]
//      [ aDir - ƫ�÷���1-��ࣻ-1-�ڲ� ]
//      [ IsAddOld - true/��ԭ���ĵ���ɷ�տռ䣻false/ֻȡƫ���� ]
//------------------------------------------------------------------------------
MPoints* OffsetPLine( MPoints* aPoints, double b, int aDir, bool IsAddOld, bool IsCenter )
{
  //ͨ�����㣬ȷ��ƫ�÷���
  aDir = CalOffsetDir( aPoints, aDir );

  if( !IsCenter )
    return _OffsetPLine( aPoints, b, aDir, IsAddOld );
  else
  {
    MPoints* bPoints = _OffsetPLine( aPoints, b/2, -aDir, false );
    MPoints* cPoints = _OffsetPLine( bPoints, b, aDir, IsAddOld );
    delete bPoints;
    return cPoints;
  }
}

MPoints* OffsetPLine( MPoints* aPoints, int aDir, bool IsAddOld, bool IsCenter )
{
  return OffsetPLine( aPoints, -1, aDir, IsAddOld, IsCenter );
}

MPoints* _OffsetPLine( MPoints* aPoints, double b, int aDir, bool IsAddOld )
{

  MPoints* aRetPoints = new MPoints;
  if( aPoints==NULL || aPoints->Count<=1 )
    return aRetPoints;
    
  MPoint* aPoi1;
  MPoint* aPoi2;
  MPoint* aPoi3;
  MPoint* aPoint;

  //�����1����

  double ab = b;

  MLines* aEdges;
  if( b<0 )
  {
    aEdges = aPoints->Edges;
    ab = aEdges->Items[0]->Wdt;
  }

  aPoi1 = aPoints->Items[0];
  aPoi2 = aPoints->Items[1];

  double k1 = kOfCrossLine(aPoi1,aPoi2);
  aRetPoints->Add( OffsetPoint( aPoi1, k1, ab, aDir) );

  //�м�����
  for( int i=1; i<aPoints->Count-1; i++ )
  {
    aPoi1 = aPoints->Items[i-1];
    aPoi2 = aPoints->Items[i];
    aPoi3 = aPoints->Items[i+1];

    if( b<0 )
      ab = aEdges->Items[i-1]->Wdt;

    MPoint* aPoi1_1 = OffsetPointPrpLine( aPoi1, aPoi2, aPoi1, ab, aDir );
    MPoint* aPoi1_2 = OffsetPointPrpLine( aPoi1, aPoi2, aPoi2, ab, aDir );

    MPoint* aPoi1_Dir = OffsetPointPrpLine( aPoi1, aPoi2, aPoi1, 1.0, aDir );

    //�б�ȡ��ȷ���н�����
    //�ò���б𣨷���ʸ�����н�����ʸ���Ĳ��Ӧ��һ�� aDir*ka Ӧ�õ��� aDir' * kb ��

    if( b<0 )
      ab = aEdges->Items[i]->Wdt;

    MPoint* aPoi2_1 = OffsetPointPrpLine( aPoi2, aPoi3, aPoi2, ab, aDir );
    MPoint* aPoi2_2 = OffsetPointPrpLine( aPoi2, aPoi3, aPoi3, ab, aDir );

    MPoint* aPoi2_Dir = OffsetPointPrpLine( aPoi2, aPoi3, aPoi2, 1.0, aDir );

    MPoint* c1 = VectorCross( *aPoi1 - *aPoi1_Dir, *aPoi1 - *aPoi2 );
    MPoint* c2 = VectorCross( *aPoi2 - *aPoi2_Dir, *aPoi2 - *aPoi3 );

    if( c1->z*c2->z < 0 )
    {
      aDir = aDir*-1;
      delete aPoi2_1;
      delete aPoi2_2;
      aPoi2_1 = OffsetPointPrpLine( aPoi2, aPoi3, aPoi2, ab, aDir );
      aPoi2_2 = OffsetPointPrpLine( aPoi2, aPoi3, aPoi3, ab, aDir );
    }

    aPoint = IntLL( aPoi1_1, aPoi1_2, aPoi2_1, aPoi2_2 );

    delete aPoi2_Dir;
    delete aPoi1_Dir;
    delete aPoi1_1;
    delete aPoi1_2;
    delete aPoi2_1;
    delete aPoi2_2;

    if( aPoint->x == MAXFLOAT || aPoint->y == MAXFLOAT )
    {
      delete aPoint;
      continue;
    }
    aRetPoints->Add( aPoint );
  }

  //�������һ����
  if( b<0 )
      ab = aEdges->Items[aPoints->Count-2]->Wdt;

  aPoi1 = aPoints->Items[aPoints->Count-2];
  aPoi2 = aPoints->Items[aPoints->Count-1];

  //k1 = kOfCrossLine(aPoi1,aPoi2);
  aRetPoints->Add( OffsetPointPrpLine( aPoi1,aPoi2, aPoi2, ab, aDir) );

  //����ԭ���Ķ˵�
  if( IsAddOld )
  {
    for( int i=aPoints->Count-1; i>=0; i-- )
    {
      MPoint* aPoint = new MPoint( aPoints->Items[i] );
      aRetPoints->Add( aPoint );
    }
  }

  return aRetPoints;
}

void kbOfLine( MPoint p1, MPoint p2, double* k, double* b )
{
  *k = kOfLine( p1, p2 );

  if( *k==MAXFLOAT )
    *b = p1.x;              //��ֱ�ߣ�b = x1 = x2
  else
    *b = p1.y - *k*p1.x;     //����, b = y1 - k*x1
}


double bOfLine( MPoint p1, MPoint p2 )
{
  double k,b;
  kbOfLine( p1, p2, &k, &b );
  return b;
}

double kOfLine( MPoint p1, MPoint p2 )
{
  if ( p1.x != p2.x )
    return ( p2.y - p1.y ) / ( p2.x - p1.x );
  else
    return MAXFLOAT;
}

double kOfCrossLine( double k )
{
  if( k==MAXFLOAT )
    return 0;
  else if ( k == 0 )
    return MAXFLOAT;
  else
    return -1.0 / k;
}

double kOfCrossLine( MPoint p1, MPoint p2 )
{
  double k = kOfLine( p1, p2 );
  return kOfCrossLine( k );
}

double LengthOfLine( MPoint p1, MPoint p2 )
{
  return sqrt( (p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y) + (p1.z-p2.z)*(p1.z-p2.z) );
}

//-------------- Check Int LL --------------------------------------------------

//-----------------------------------------------------------------------
//���ܣ����ֱ��[p1,p2]��[p3,p4]�Ƿ����ʵ����
//ԭ����ʵ�����ֱ�ߣ�p1,p2��[p3,p4]���࣬p3,p4��[p1,p2]����
//����: [ aType = 0, ʵ���㣨�����˽��㣩�� =1��ʵ����+�϶˽��㣬=-1��ʵ����+�¶˽��㣬=2��ʵ����+�齻�� ]
//˵�����غ����������Ϊ���ཻ
//-----------------------------------------------------------------------

bool IsIntofByK( double k1, double k2, int aType )
{
  //ƽ����
  if( IsEqual( k1, k2 ) )
    return false;

  //��ʵ����+�齻�㡱
  if( aType == 2 )
    return true;

  //�齻��
  if ( k1*k2 > 0 )
    return false;

  //��ʵ����+�˽��㡱
  if( aType == 0 )
    return true;

  //��ʵ����+��˽��㡱
  if ( k1*k2 == 0 && ( k1*aType<0 || k2*aType < 0 ) )
    return false;

  return true;
}


bool IsIntLL( MPoint p1, MPoint p2, MPoint p3, MPoint p4, int aType1, int aType2 )
{
  //���Ӳ���
  if( aType1 != 2 && aType2 != 2 && IsIntLL_Box(p1,p2,p3,p4) == false )
    return false;

  //�������
  double k1 = poiOnLine( p1, p3, p4 );
  double k2 = poiOnLine( p2, p3, p4 );

  if( IsIntofByK( k1, k2, aType1 ) == false )
    return false;

  //if( ( IsEqual( k1, 0 ) && IsEqual( k2,0 ) ) || ( k1*k2 > 0 ) )  //���߻���ͬ��
  //  return false;

  double k3 = poiOnLine( p3, p1, p2 );
  double k4 = poiOnLine( p4, p1, p2 );

  if( IsIntofByK( k3, k4, aType2 ) == false )
    return false;

  //if( ( IsEqual( k3, 0 ) && IsEqual( k4,0 ) ) || (k3*k4 > 0) )
  //  return false;

  return true;
}

bool IsIntLL_Box( MPoint p1, MPoint p2, MPoint p3, MPoint p4 )
{
  double aMinX1 = Min( p1.x, p2.x );
  double aMinY1 = Min( p1.y, p2.y );
  double aMaxX1 = Max( p1.x, p2.x );
  double aMaxY1 = Max( p1.y, p2.y );

  double aMinX2 = Min( p3.x, p4.x );
  double aMinY2 = Min( p3.y, p4.y );
  double aMaxX2 = Max( p3.x, p4.x );
  double aMaxY2 = Max( p3.y, p4.y );

  bool IsOut = aMinX1 > aMaxX2 || aMinX2 > aMaxX1 ||
               aMinY1 > aMaxY2 || aMinY2 > aMaxY1 ;
  return !IsOut;
}

//------------------------------------------------------------------------------
//���ܣ�ֱ����
//------------------------------------------------------------------------------
MPoint* IntLL( MPoint* aP11, MPoint* aP12, MPoint* aP21, MPoint* aP22 )
{
  MLine* aL1 = new MLine( *aP11, *aP12 );
  MLine* aL2 = new MLine( *aP21, *aP22 );

  MPoint* aPoi = IntLL( aL1, aL2 );

  delete aL1;
  delete aL2;
  return aPoi;
}

MPoint* IntLL( MLine* aLine1, MLine* aLine2 )
{
  if( aLine1==NULL || aLine2==NULL )
    throw Exception( "IntLL����NULL����!");

  return IntLL( aLine1->k(), aLine1->b(), aLine2->k(), aLine2->b() );
}

void IntLL( double k1, double b1, double k2, double b2, double* x, double* y )
{
  if( k1 == k2  )
  {
    *x = MAXFLOAT;
    *y = MAXFLOAT;
  }
  else if( k1==MAXFLOAT )
  {
    *x = b1;                      //Line1Ϊ��ֱ��
    *y = k2 * ( *x ) + b2;
  }
  else if ( k2 == MAXFLOAT )
  {
    *x = b2;                      //Line2Ϊ��ֱ��
    *y = k1 * ( *x ) + b1;
  }
  else
  {
    *x = ( b2-b1 ) / ( k1 - k2 );
    *y = ( k1*b2 - k2*b1 ) / ( k1 - k2 );
  }
}

MPoint* IntLL( double k1, double b1, double k2, double b2 )
{
  MPoint* aPoint = new MPoint();
  IntLL( k1, b1, k2, b2, &aPoint->x, &aPoint->y );
  return aPoint;
}

//���ܣ��� [ p1, p2 ]���������߶Σ�ʹ����aRegion�ı߽��ཻ

MPoint* ExtendLineToRegion( MPoint p1, MPoint p2, MPoints* aRegion )
{
   if( aRegion == NULL || p1==p2 )
     return new MPoint( MAXFLOAT, MAXFLOAT, 0.0 );

   //if( p2.IsOn(aRegion) )
   //  return new MPoint( p2 );
   //if( p1.IsOn(aRegion) )
   //  return new MPoint( MAXFLOAT, MAXFLOAT, 0.0  );


   //������aRegion��Ϊʵ���㣬����[p1,p2]�������ϵĵ�
   for( int i=0; i<aRegion->Count-1; i++ )
   {
     MPoint* p3 = aRegion->Items[i];
     MPoint* p4 = aRegion->Items[i+1];

     if( !IsIntLL( p1,p2,*p3,*p4,2,0 ) )     //[p1,p2]ȡ��[ *p3,*p4 ]ȡʵ����
       continue;

     /*//�������
     double k1 = poiOnLine( p1, *p3, *p4 );
     double k2 = poiOnLine( p2, *p3, *p4 );

     //[p1,p2]ΪԶ��[p3,p4]�ķ���
     if( k1*k2>0 && fabs(k1) <= fabs(k2) )
       continue;

     double k3 = poiOnLine( p3, p1, p2 );
     double k4 = poiOnLine( p4, p1, p2 );

     //������[p3,p4]��Ϊ�齻��
     if( k3*k4 > 0 )
        continue;*/

     MPoint* aPoint = IntLL( &p1, &p2, p3, p4 );

     if( poiPosInLine( *aPoint, p1, p2 ) > 0.0 )   //�������ж�
       return aPoint;
     else
       delete aPoint;
   }

   return new MPoint( MAXFLOAT, MAXFLOAT, 0.0 );
}

bool IsEqual( double x1, double x2, double delta )
{
  return ( fabs( x1-x2 ) <= delta ) ;
}

//------------------------------------------------------------------------------
//���ܣ���ֱ֪������+X���꣬����Y����
//------------------------------------------------------------------------------
double YOnLine( MPoint* aPoint1, MPoint* aPoint2, double x )
{
  if( aPoint1==NULL || aPoint2==NULL )
    throw Exception("YOnLine����NULL�㣡");

  double x1 = aPoint1->x;
  double y1 = aPoint1->y;
  double x2 = aPoint2->x;
  double y2 = aPoint2->y;

  if( IsEqual( y1, y2 ) )
    return y1;
  if( IsEqual( x1,x2 ) )
    return 0.5*(y1+y2);

  return ( y1*(x2-x)+y2*(x-x1) )/ (x2-x1);
}

double IsInDouble( double x, double x0, double x1, double delta )
{
  return x >= Min( x0, x1 )- delta && x <=Max( x0, x1 ) + delta;
}

//------------------------------------------------------------------------------
//���ܣ�ȡ������
//����: [ aCurveData, In, �������ߵĿ��Ƶ� ]
//      [ x, In, ������X���ꡡ]
//------------------------------------------------------------------------------
double GetSamplePointY( MPoints* aCurvePoints, double x )
{
  if( aCurvePoints==NULL )
    throw Exception("����Ϊ�գ�");

  int pos = aCurvePoints->IndexByX( x );
  if( pos<0 || pos >= aCurvePoints->Count )
    throw Exception("������������ڲ��������⣡");
  return YOnLine( aCurvePoints->Items[pos], aCurvePoints->Items[pos+1],  x );
}


void GetSamplePoints( MPoints* aCurveData, MPoints* aSamplePoints )
{
  if( aCurveData==NULL || aSamplePoints==NULL )
    throw Exception("���߻��ǲ�����Ϊ�գ�");

  for( int i=0; i<aSamplePoints->Count; i++ )
    aSamplePoints->Items[i]->y = GetSamplePointY( aCurveData, aSamplePoints->Items[i]->x );
}

double Div_E( double f1, double f2, String aVarNames )
{
  if( f2==0 )
    throw Exception( "��0��!"+aVarNames );
  return f1 / f2;
}

//====================================================================
//    FUNCTION :	ProUtilVectorCross()
//    PURPOSE  :	Cross product of two vectors
//====================================================================
void VectorCross( MPoint v1, MPoint v2, MPoint* v3 )
{
    v3->x = v1.y * v2.z - v1.z * v2.y;
    v3->y = v1.z * v2.x - v1.x * v2.z;
    v3->z = v1.x * v2.y - v1.y * v2.x;
}

MPoint* VectorCross( MPoint v1, MPoint v2 )
{
   MPoint* aPoint = new MPoint;
   VectorCross( v1, v2, aPoint );
   return aPoint;
}

//-------------------------------------------------------------------------
//[ p1, p2 : ��׼�� ]
//[ p : ͶӰ�� ]
//[ ���� : ���� ]
//-------------------------------------------------------------------------

MPoint* PointPrp( MPoint p1, MPoint p2, MPoint p )
{
  return PointPrp( p1, kOfLine( p1, p2 ), p );
}

//-------------------------------------------------------------------------
//[ P0, k : ��׼�� ]
//[ P1 : ͶӰ�� ]
//[ P : ���� ]
//-------------------------------------------------------------------------
MPoint* PointPrp( MPoint P0, double k0, MPoint P1 )
{
  MPoint* P;

  //if( IsPoiOnLine( P1, P0, k0 ) )
  //{
  //  P = new MPoint;
  //  *P = P1;
  //  return P;
  //}

  if( k0 == MAXFLOAT )
  {
    P = new MPoint;
    P->x = P0.x;
    P->y = P1.y;
  }
  else if( k0 == 0 )
  {
    P = new MPoint;
    P->x = P1.x;
    P->y = P0.y;
  }
  else
  {
    MPoint* P0_1 = OffsetPoint( &P0, k0, 1.0, 1 );
    MPoint* P1_1 = OffsetPoint( &P1, -1/k0, 1.0, 1 );

    P = IntLL( &P0, P0_1, &P1, P1_1 );
    if( P->x == MAXFLOAT )
      *P = P1;
      
    delete P0_1;
    delete P1_1;
  }

  return P;
}

//  -----------------------------------------------
//  --����: �����pTst���߶�[p1,p2]�е�λ��
//  --˵��: <0 �� >1 pTst���߶��ⲿ
//  -----------------------------------------------
double poiPosInLine( MPoint pTst, MPoint p1, MPoint p2 )
{
  if ( p1 == p2 )
    return MAXFLOAT;

  if ( p1.x != p2.x )
    return ( pTst.x - p1.x ) / ( p2.x - p1.x );
  else
    return ( pTst.y - p1.y )/( p2.y - p1.y );
}

//  -----------------------------------------------
//  --����:�ж�"��"�Ƿ���"ֱ��"�ڲ�
//  -----------------------------------------------
bool IsPoiInLine( MPoint pTst, MPoint p1, MPoint p2, double  tole )
{
  double rT = poiPosInLine( pTst, p1, p2 );

  if ( rT<=1.0+tole && rT+tole>=0.0 )
    return true;
  else
    return false;
}

//  -----------------------------------------------------------
//  --����: �������ֱ�����λ��
//  --����:
//  -- (1)pTst:���Ե�;
//  -- (2)[p1,p2]:����ֱ��
//  -- (3)����: >0 pTst��[p1,p2]���Ϸ�
//  --          =0 pTst��[p1,p2]��ֱ����
//  --          <0 pTst��[p1,p2]���·�
//  -----------------------------------------------------------
double poiOnLine( MPoint pTst, MPoint p1, MPoint p2 )
{
  double k, b;
  kbOfLine( p1,p2, &k, &b );

  if( k==MAXFLOAT )
    return pTst.x - p1.x;
  else
    return pTst.y - ( k*pTst.x + b );

  //MPoint pT
  //PrpPoint( p1,p2,pTst, &pT )
  //return pTst.y-pT.y
}

bool IsPoiOnLine( MPoint pTst, MPoint p1, double k )
{
  MPoint p2;
  OffsetPoint( &p1, k, 1.0, 1, &p2 );
  return IsPoiOnLine( pTst, p1, p2 );
}

bool IsPoiOnLine( MPoint pTst, MPoint p1, MPoint p2 )
{
  return IsEqual( poiOnLine( pTst, p1, p2 ), 0.0 );
}

//  -----------------------------------------------
//  --����:�ж�ֱ���Ƿ��غ�
//  -----------------------------------------------
bool isOverLine( MPoint p1, MPoint p2, MPoint q1, MPoint q2 )
{
  return IsPoiOnLine( p1, q1, q2 ) && IsPoiOnLine( p2, q1, q2 );
}

bool IsEqual( MPoints* aPoints, MPoints* bPoints )
{
  if( aPoints==NULL || bPoints==NULL || aPoints->Count!=bPoints->Count )
    return false;

  for( int i=0; i<aPoints->Count; i++ )
  {
    if( !( *aPoints->Items[i] == *bPoints->Items[i] ) )
      return false;
  }

  return true;
}



#pragma package(smart_init)
