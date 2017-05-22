//---------------------------------------------------------------------------

//#include "UnitAll.h"

#pragma hdrstop

#define UseAddFlow
#include "UnitTool_AddFlow.h"

//------------------- afLink ---------------------------------------------------

MPoints* GetAfNodePoints( afNode* aNode )
{
  if( aNode==NULL || aNode->CustomShapeIndex<0 )
    return NULL;

  MPoints* aPoints = (MPoints*) aNode->UserData;

  if( aPoints!=NULL )
    aPoints->Node = aNode;

  return aPoints;
}

MPoints* GetAfLinkPoints( afLink* aLink )
{
  MPoints* aPointsOut = new MPoints;
  if( aLink==NULL )
    return aPointsOut;

  afLinkPoints* aPoints = aLink->ExtraPoints;
  for( int i=0; i<aPoints->Count; i++ )
  {
    afLinkPoint* aPoint = aPoints->get_Item(i);
    MPoint* aPoint1 = new MPoint();
    aPoint1->x = aPoint->x;
    aPoint1->y = aPoint->y;
    aPointsOut->Add( aPoint1 );
  }
  return  aPointsOut;
}

void MousePointToPixelPoint( TAddFlow* aFlow, double X, double Y, double* aX, double* aY )
{
  *aX = (X * 100.0 / aFlow->xZoom) + TwipsToPixels(aFlow->xScroll) ;
  *aY = (Y * 100.0 / aFlow->yZoom) + TwipsToPixels(aFlow->yScroll) ;
}

void MousePointToTwipsPoint( TAddFlow* aFlow, double X, double Y, double* aX, double* aY )
{
  MousePointToPixelPoint( aFlow, X, Y, aX, aY );
  *aX = PixelsToTwips( *aX );
  *aY = PixelsToTwips( *aY );
}

//------------------ Polygon ---------------------------------------------------

bool IsValidPLine(MPoints* aPoints)
{
  if( aPoints==NULL ||  aPoints->Count <= 1  )
    return false;

  //double aMinX,aMinY,aMinZ,aMaxX,aMaxY,aMaxZ;
  //aPoints->GetExtent( aMinX, aMinY, aMinZ, aMaxX, aMaxY, aMaxZ );

  //int aWdt = aMaxX-aMinX;         //计算Node的区域
  //int aHgt = aMaxY-aMinY;

  //if( aWdt==0 || aHgt==0 )
  //  return false;

  return true;
}

//绘制Polygon
afNode* EditPolygon( TAddFlow * aFlow, afNode* aOldNode, MPoints* aPoints, double aLineWdt, double aScaleFactor, bool IsCoordTrans )
{
   return _EditPLine( aFlow, aOldNode, aPoints, true, 10.0, aLineWdt, aScaleFactor, IsCoordTrans );
}

afNode* EditPLine( TAddFlow * aFlow,  afNode* aOldNode, MPoints* aPoints, double aAreaWdt, double aLineWdt, double aScaleFactor, bool IsCoordTrans )
{
   return _EditPLine( aFlow, aOldNode, aPoints, false, aAreaWdt, aLineWdt, aScaleFactor, IsCoordTrans );
}

afNode* _EditPLine( TAddFlow * aFlow, afNode* aOldNode,  MPoints* aPoints, bool IsPolygon, double aAreaWdt,
                    double aLineWdt, double aScaleFactor, bool IsCoordTrans )
{
  if ( aFlow == NULL || IsValidPLine( aPoints ) == false )
    return NULL;

  if( aOldNode==NULL )
    return _AddPLine( aFlow, aPoints, IsPolygon, aAreaWdt, aLineWdt, aScaleFactor, IsCoordTrans );

  //修订模式,非自定义afNode
  if( aOldNode->CustomShapeIndex<0 )
  {
    //if( aPoints->Count == 2 )
    //{

    //}
    return aOldNode;
  }

  afCustomShape* aCustNode = aFlow->CustomShapes->get_Item(aOldNode->CustomShapeIndex);
  if( aCustNode==NULL )
    return NULL;

  aCustNode->Clear();
  SetPLineToNode( aOldNode, aCustNode, aPoints, IsPolygon, aAreaWdt, aLineWdt,  aScaleFactor, IsCoordTrans );
  return aOldNode;
}

afNode* AddPolygon( TAddFlow * aFlow, MPoints* aPoints, double aLineWdt, double aScaleFactor, bool IsCoordTrans )
{
   return _AddPLine( aFlow, aPoints, true, 10.0, aLineWdt, aScaleFactor, IsCoordTrans );
}

afNode* AddPLine( TAddFlow * aFlow, MPoints* aPoints, double aAreaWdt, double aLineWdt, double aScaleFactor, bool IsCoordTrans )
{
   return _AddPLine( aFlow, aPoints, false, aAreaWdt, aLineWdt, aScaleFactor, IsCoordTrans );
}

afNode* _AddPLine( TAddFlow * aFlow, MPoints* aPoints, bool IsPolygon, double aAreaWdt, double aLineWdt, double aScaleFactor, bool IsCoordTrans )
{
  if ( aFlow == NULL || IsValidPLine( aPoints ) == false )
     return NULL;

  afCustomShape* aCustNode = aFlow->CustomShapes->Add();
  afNode* aNode  = aFlow->Nodes->Add( 0, 0, 1, 1 );

  aNode->UserData == NULL;
  aNode->Shape = afCustomShape_ ;
  aNode->CustomShapeIndex = aFlow->CustomShapes->Count-1;

  SetPLineToNode( aNode, aCustNode, aPoints, IsPolygon, aAreaWdt, aLineWdt, aScaleFactor, IsCoordTrans );
  return aNode;
}

//------------------------------------------------------------------------------
// [ aNode : 显示PLine用的afNode ]
// [ aCustNode : 定义Pline形状的afCustomShape ]
// [ aPoints : 多义线的点集合 ]
// [ IsPolygon : true / 绘制为Polygon  false / 绘制为PLine ]
// [ aAreaWdt : PLine宽度 ]
// [ aLineWdt : 边界线宽度 ]

  //特殊Plank的处理，以便减少CustomShape的数量 ??
  //if( aPoints->IsRect() )
  //{
  //   double aLeft, double aTop, double aWdt, double aHgt;
  //   aPLine->GetRect( aLeft, aTop, aWdt, aHgt );
  //   AddNode( fFlow,aLeft,aTop,aWdt,aHgt,aType );
  //   return
  //}

//------------------------------------------------------------------------------
void SetPLineToNode( afNode* aNode, afCustomShape* aCustNode,  MPoints* aPoints, bool IsPolygon,
                     double aAreaWdt, double aLineWdt,  double aScaleFactor, bool IsCoordTrans   )
{
  if( aNode == NULL )
    return;

  if( aPoints->Count<=0 )
    return;

  //记录PLine端点到UserData
  MPoints* cPoints = (MPoints*)aNode->UserData;
  if( cPoints == NULL )
    cPoints = new MPoints();
  *cPoints = *aPoints;
  cPoints->Node = aNode;
  aNode->UserData = (long) ((void*) cPoints );

  //计算显示端点
  MPoints* bPoints;
  if( IsPolygon )
    bPoints = aPoints;
  else
    bPoints = OffsetPLine(aPoints, aAreaWdt, 1,true,true);

  try
  {
    double aMinX,aMinY,aMinZ,aMaxX,aMaxY,aMaxZ;
    bPoints->GetExtent( aMinX, aMinY, aMinZ, aMaxX, aMaxY, aMaxZ );

    double aWdt = aMaxX-aMinX;         //计算Node的区域
    double aHgt = aMaxY-aMinY;

    if( aWdt==0 || aHgt==0 )
      return;


    //生成自定义节点（ 注意节点的坐标为相对于Node的Wdt和Hgt的百分比形式 ）

    for ( int i = 0; i < bPoints->Count; i++ )
    {
      MPoint* aPoint = bPoints->Items[i];
      aCustNode->AddPoint( (aPoint->x-aMinX) / aWdt * 100 + 0.5 , (aPoint->y-aMinY) / aHgt * 100 + 0.5 );
    }

    //bPoints->SaveToFile( "c:\\test.txt" );

    //生成节点

    //aFlow->FillColor = Yellow;
    aNode->DrawWidth = aLineWdt;
    aNode->FillColor = clBlack;

    if( IsCoordTrans )
    {
      aNode->Left = PixelsToTwips(aMinX);
      aNode->Top = PixelsToTwips(aMinY);
      aNode->Width = PixelsToTwips( aWdt );
      aNode->Height = PixelsToTwips( aHgt );
    }
    else
    {
      aNode->Left = aMinX;
      aNode->Top = aMinY;
      aNode->Width = aWdt;
      aNode->Height = aHgt;
    }

    //afNode* aNode  = aFlow->Nodes->Add( PixelsToTwips(aMinX), PixelsToTwips(aMinY), PixelsToTwips( aWdt ) , PixelsToTwips( aHgt ) );
    aNode->Refresh();
  }
  __finally
  {
    if( !IsPolygon )
      delete bPoints;
  }
}

//----------------------- AddFlow -----------------------------------------

void GetAddFlowBoundXY( TAddFlow * aFlow ,int & x,int &y )
{
  if( aFlow==NULL )
    return;
    
  x = 0;
  y =0;
  for (int i = 1; i <= aFlow->Nodes->Count; i++)
  {
   afNode * aNode = aFlow->Nodes->Item(Variant(i));

   int aR =  aNode->Left+aNode->Width;
   int aD =   aNode->Top+aNode->Height;
   x =  aR> x ?aR:x;
   y = aD > y ?aD:y;

   for (int j = 1; j <= aNode->OutLinks->Count; j++)
   {
      afLink * aL = aNode->OutLinks->Item(Variant(j));
      for (int k = 1; k < aL->ExtraPoints->Count; k++)
      {
        afLinkPoint * aPt = aL->ExtraPoints->get_Item(k);
        x =  aPt->x> x ? aPt->x:x;
        y = aPt->y > y ? aPt->y:y;
      }
   }
  }

}

void SetAddFlowFit( TAddFlow * aFlow,int aType )
{
  int x,y;
  GetAddFlowBoundXY( aFlow, x, y );
  aFlow->ZoomRectangle( aType, 0, 0, x+200, y+200 );
}

void ZoomFlow( TAddFlow * aFlow,int aScal )
{
  aFlow->xZoom = aFlow->xZoom + aScal;
  aFlow->yZoom = aFlow->yZoom + aScal;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void SetAddFlowAutoRout(TAddFlow *aFlow)
{
   aFlow->AdjustDst = true;
   aFlow->AdjustOrg = true;
   aFlow->Autorouting = true;
   SetAddFlowReadOnly(aFlow);
   aFlow->OrthogonalDynamic=true;
  // aFlow->LinkStyle = afHVH;

}

void SetAddFlowReadOnly(TAddFlow *aFlow)
{
   aFlow->CanDrawLink = false;
   aFlow->CanDrawNode = false;
   aFlow->CanSizeNode = false;
   aFlow->EditMode = afEditNone;
}

void SetNodeToLine(afNode *aNode,String aTag)
{
  aNode->Shape = afRectangle;
  //aNode->Sizeable = false;
  //aNode->DrawColor = clBlack;
  aNode->FillColor = aNode->DrawColor;
  aNode->Tag = WideString(aTag);
}

void SetNodeTransparent( afNode * aNode )
{
   aNode->DrawStyle = afTransparent;
   aNode->Selectable = false;
}

void SetLinkTransparent( afLink * aLink )
{
   aLink->DrawStyle = afTransparent;
   aLink->Selectable = false;
}
void SetLinkDragMode( TAddFlow * aFlow )
{
   aFlow->OrthogonalDynamic=true;
   aFlow->AdjustOrg=true;
   aFlow->AdjustDst=true;
   aFlow->LinkStyle = afHVH;
}
void SetLinkRigid( afLink * aLink , bool IsTransParent ,String aTag)
{
   aLink->Rigid = true;
   aLink->Selectable = false;
   if ( IsTransParent )
    aLink->DrawStyle = afTransparent;
   if (aTag !="" )
    aLink->Tag = (WideString)aTag;
}
void SetNodeShape( afNode *aNode , int aShape , String aTag )
{
  aNode->Shape = aShape;
  aNode->FillColor = clRed;
  aNode->Tag = WideString(aTag);
  aNode->Moveable = false;
}

void ClearFlow(TAddFlow * aFlow)
{
  aFlow->SelectAll();
  aFlow->DeleteSel();
}
void BindNodes(TAddFlow * aFlow ,afNode *aNode,afNode *bNode,String aTag)
{
   SetLinkRigid(aFlow->AddLink(aNode,bNode),true,aTag);
   SetLinkRigid(aFlow->AddLink(bNode,aNode),true,aTag);
}

afNode * FindMatchNode( TAddFlow * aFlow , String NodeText )
{
  if( aFlow ==NULL )
    return NULL;
    
  for (int i =1 ; i <= aFlow->Nodes->Count; i++ )
  {
    afNode * aNode = aFlow->Nodes->Item(Variant(i));
    if ( (String)aNode->Text == NodeText ) return aNode;
  }
  return NULL;
}

void UnMarkedAll( TAddFlow* aFlow )
{
  if( aFlow==NULL )
    return;

  for( int i=1; i<=aFlow->Nodes->Count; i++ )
  {
     afNode* aNode = aFlow->Nodes->Item(Variant(i));
     if( aNode->Marked )
       aNode->Marked = false;
  }
}

void afDeletNode( TAddFlow* aFlow, afNode* aNode )
{
  if( aFlow== NULL || aNode == NULL )
    return;

  UnMarkedAll( aFlow );
  aNode->Marked = true;
  aFlow->DeleteMarked();
}

void afNodeSetMarked( afNode* aNode, bool aBool )
{
  if( aNode == NULL )
    return;
  aNode->Marked = aBool;
}

int FindAfNodeEdge( TAddFlow* aFlow, afNode* aNode, double x1, double y1 )
{
  MPoint aPoi1( x1, y1 );
  MPoints* aPoints = GetAfNodePoints( aNode );
  if( aPoints!=NULL )
    return aPoints->FindNearEdgeByPoint( aPoi1 );
  else
    return -1;
}

void MovAfNodeEdge( TAddFlow* aFlow, afNode* aNode, double x1, double y1, double x2, double y2 )
{
   MoveAfNodeEdge( aFlow, aNode, FindAfNodeEdge(aFlow,aNode,x1,y1),  x1, y1, x2, y2 );
}

void MoveAfNode( afNode* aNode, double x1, double y1, double x2, double y2 )
{
   if( aNode == NULL  )
     return;

   if( aNode->XMoveable )
     aNode->Left = aNode->Left + x2 - x1;

   if( aNode->YMoveable )
     aNode->Top = aNode->Top + y2 - y1;
}

void MoveAfNodeEdge( TAddFlow* aFlow, afNode* aNode, int aEdge,  double x1, double y1, double x2, double y2 )
{
   if( aFlow==NULL || aNode == NULL || aEdge<0 )
     return;

   MPoints* aPoints = GetAfNodePoints( aNode );

   if( aPoints != NULL )
   {

     MPoint aPoi1( x1, y1, 0.0 );
     MPoint aPoi2( x2, y2, 0.0 );

     MPoint* Vert1 = aPoints->Items[ aEdge ];
     MPoint* Vert2 = aPoints->Items[ aEdge+1 ];

     double aWdt = LengthOfLine(aPoi2,aPoi1); //Math::Min( fabs( LengthOfPointAndLine( Vert1, Vert2, aPoi2 ) - LengthOfPointAndLine( Vert1, Vert2, aPoi1 ) ), 1000.0 );
     int aDir = OffsetLineDir( Vert1, Vert2, aPoi1, aPoi2 );

     MPoint aPoi3 = *OffsetPointPrpLine( Vert1, Vert2, aPoints->Items[ aEdge ], aWdt, aDir );
     MPoint aPoi4 = *OffsetPointPrpLine( Vert1, Vert2, aPoints->Items[ aEdge+1 ], aWdt, aDir );

     //MPoint aPoi3, aPoi4;
     //OffsetLine( *aPoints->Items[ aEdge ], *aPoints->Items[ aEdge+1 ], aPoi2, &aPoi3, &aPoi4 );

     *aPoints->Items[ aEdge ] = aPoi3;
     *aPoints->Items[ aEdge+1 ] = aPoi4;

     aPoints->Show( aFlow );
     //aNode = EditPLine( aFlow, aNode, aPoints, PixelsToTwips(10), PixelsToTwips(1), 1, false );
   }
   else
   {
      MoveAfNode( aNode,  x1, y1, x2, y2 );
      //aNode->Left = aNode->Left + x2 - x1;
      //aNode->Top = aNode->Top + x2 - x1;
   }
}

double PixelsToTwips( double aPixels )
{
  return ( aPixels*1440.0/Screen->PixelsPerInch );
}

double TwipsToPixels( double aTwips )
{
  return ( aTwips * Screen->PixelsPerInch / 1440 );
}

//---------------------------------------------------------------------------

#pragma package(smart_init)
