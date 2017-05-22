//---------------------------------------------------------------------------

#ifndef UnitTool_AddFlowH
#define UnitTool_AddFlowH

//---------------------------------------------------------------------------
#include "AddFlow5Lib_OCX.h"
#include "unitmath.h"

afNode* EditPolygon( TAddFlow * aFlow, afNode* aOldNode, MPoints* aPoints, double aLineWdt=4, double aScaleFactor=1, bool IsCoordTrans=true  );
afNode* EditPLine( TAddFlow * aFlow,  afNode* aOldNode, MPoints* aPoints, double aAreaWdt=10, double aLineWdt=4, double aScaleFactor=1, bool IsCoordTrans=true );

afNode* AddPolygon( TAddFlow * aFlow, MPoints* aPoints, double aLineWdt=4, double aScaleFactor=1, bool IsCoordTrans=true );
afNode* AddPLine( TAddFlow * aFlow, MPoints* aPoints, double aAreaWdt=10, double aLineWdt=4, double aScaleFactor=1, bool IsCoordTrans=true );

afNode* _EditPLine( TAddFlow * aFlow, afNode* aOldNode,  MPoints* aPoints, bool IsPolygon, double aAreaWdt, double aLineWdt, double aScaleFactor, bool IsCoordTrans=true );
afNode* _AddPLine( TAddFlow * aFlow, MPoints* aPoints, bool IsPolygon, double aAreaWdt, double aLineWdt, double aScaleFactor, bool IsCoordTrans=true );

void SetPLineToNode( afNode* aNode, afCustomShape* aCustNode, MPoints* aPoints,
                     bool IsPolygon, double aAreaWdt, double aLineWdt, double aScaleFactor, bool IsCoordTrans=true  );

MPoints* GetAfNodePoints( afNode* aNode );
MPoints* GetAfLinkPoints( afLink* aLink );

void MoveAfNode( afNode* aNode, double x1, double y1, double x2, double y2 );
int FindAfNodeEdge( TAddFlow* aFlow, afNode* aNode, double x1, double y1 );
void MoveAfNodeEdge( TAddFlow* aFlow, afNode* aNode, int aEdge,  double x1, double y1, double x2, double y2 );
void MoveAfNodeEdge( TAddFlow* aFlow, afNode* aNode, double x1, double y1, double x2, double y2 );

//--------------------------------AddFlow---------------------------------------
double PixelsToTwips( double twipsVal);
double TwipsToPixels( double aTwips );

void MousePointToTwipsPoint( TAddFlow* aFlow, double X, double Y, double* aX, double* aY );
void MousePointToPixelPoint( TAddFlow* aFlow, double X, double Y, double* aX, double* aY );

//void MousePointToFlowPoint( TAddFlow* aFlow, double X, double Y, double* aX, double* aY );

void SetLinkDragMode( TAddFlow * aFlow );
void SetAddFlowAutoRout(TAddFlow *aFlow);
void SetAddFlowReadOnly(TAddFlow *aFlow);
void SetNodeToLine(afNode *aNode,String aTag);
void SetNodeTransparent( afNode * aNode );
void SetLinkTransparent( afLink * aLink );
void SetLinkRigid( afLink * aLink , bool IsTransParent = true,String aTag ="");
void SetNodeShape( afNode *aNode , int aShape = 66 ,String aTag = "PlankJoint");
void ClearFlow(TAddFlow * aFlow);
void BindNodes(TAddFlow * aFlow ,afNode *aNode,afNode *bNode,String aTag ="");
afNode * FindMatchNode( TAddFlow * aFlow , String NodeText );

void GetAddFlowBoundXY(TAddFlow * aFlow ,int & x,int &y);
void SetAddFlowFit( TAddFlow * aFlow,int aType =1 );//int aType =0,各项同性，=1非各项同性
void ZoomFlow( TAddFlow * aFlow,int aScal );

void UnMarkedAll( TAddFlow* aFlow );
void afDeletNode( TAddFlow* aFlow, afNode* aNode );
void afNodeSetMarked( afNode* aNode, bool aBool );

//-------------------Class------------------------------------------------------


#endif
