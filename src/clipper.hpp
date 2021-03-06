// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'clipper.pas' rev: 6.00

#ifndef clipperHPP
#define clipperHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Math.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Types.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Clipper
{
//-- type declarations -------------------------------------------------------
typedef int cInt;

struct TIntPoint;
typedef TIntPoint *PIntPoint;

#pragma pack(push, 4)
struct TIntPoint
{
	int X;
	int Y;
} ;
#pragma pack(pop)

#pragma pack(push, 4)
struct TIntRect
{
	int Left;
	int Top;
	int Right;
	int Bottom;
} ;
#pragma pack(pop)

struct TDoublePoint
{
	double X;
	double Y;
} ;

typedef DynamicArray<TDoublePoint >  TArrayOfDoublePoint;

#pragma option push -b-
enum TInitOption { ioReverseSolution, ioStrictlySimple, ioPreserveCollinear };
#pragma option pop

typedef Set<TInitOption, ioReverseSolution, ioPreserveCollinear>  TInitOptions;

#pragma option push -b-
enum TClipType { ctIntersection, ctUnion, ctDifference, ctXor };
#pragma option pop

#pragma option push -b-
enum TPolyType { ptSubject, ptClip };
#pragma option pop

#pragma option push -b-
enum TPolyFillType { pftEvenOdd, pftNonZero, pftPositive, pftNegative };
#pragma option pop

#pragma option push -b-
enum TJoinType { jtSquare, jtRound, jtMiter };
#pragma option pop

#pragma option push -b-
enum TEndType { etClosedPolygon, etClosedLine, etOpenButt, etOpenSquare, etOpenRound };
#pragma option pop

typedef DynamicArray<TIntPoint >  TPath;

typedef DynamicArray<DynamicArray<TIntPoint > >  TPaths;

class DELPHICLASS TPolyNode;
typedef DynamicArray<TPolyNode* >  TArrayOfPolyNode;

class DELPHICLASS TPolyNode;
class PASCALIMPLEMENTATION TPolyNode : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	DynamicArray<TIntPoint >  FPath;
	TPolyNode* FParent;
	int FIndex;
	int FCount;
	int FBuffLen;
	bool FIsOpen;
	DynamicArray<TPolyNode* >  FChilds;
	TJoinType FJoinType;
	TEndType FEndType;
	TPolyNode* __fastcall GetChild(int Index);
	bool __fastcall IsHoleNode(void);
	void __fastcall AddChild(TPolyNode* PolyNode);
	TPolyNode* __fastcall GetNextSiblingUp(void);
	
public:
	TPolyNode* __fastcall GetNext(void);
	__property int ChildCount = {read=FCount, nodefault};
	__property TPolyNode* Childs[int index] = {read=GetChild};
	__property TPolyNode* Parent = {read=FParent};
	__property bool IsHole = {read=IsHoleNode, nodefault};
	__property bool IsOpen = {read=FIsOpen, nodefault};
	__property TPath Contour = {read=FPath};
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TPolyNode(void) : System::TObject() { }
	#pragma option pop
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TPolyNode(void) { }
	#pragma option pop
	
};


class DELPHICLASS TPolyTree;
class PASCALIMPLEMENTATION TPolyTree : public TPolyNode 
{
	typedef TPolyNode inherited;
	
private:
	DynamicArray<TPolyNode* >  FAllNodes;
	int __fastcall GetTotal(void);
	
public:
	void __fastcall Clear(void);
	TPolyNode* __fastcall GetFirst(void);
	__fastcall virtual ~TPolyTree(void);
	__property int Total = {read=GetTotal, nodefault};
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TPolyTree(void) : TPolyNode() { }
	#pragma option pop
	
};


#pragma option push -b-
enum TEdgeSide { esLeft, esRight };
#pragma option pop

#pragma option push -b-
enum TDirection { dRightToLeft, dLeftToRight };
#pragma option pop

struct TOutPt;
typedef TOutPt *POutPt;

struct TEdge;
typedef TEdge *PEdge;

struct TEdge
{
	TIntPoint Bot;
	TIntPoint Curr;
	TIntPoint Top;
	TIntPoint Delta;
	double Dx;
	TPolyType PolyType;
	TEdgeSide Side;
	int WindDelta;
	int WindCnt;
	int WindCnt2;
	int OutIdx;
	TEdge *Next;
	TEdge *Prev;
	TEdge *NextInLML;
	TEdge *PrevInAEL;
	TEdge *NextInAEL;
	TEdge *PrevInSEL;
	TEdge *NextInSEL;
} ;

typedef TEdge TEdgeArray[24403223];

typedef TEdge *PEdgeArray;

struct TScanbeam;
typedef TScanbeam *PScanbeam;

#pragma pack(push, 4)
struct TScanbeam
{
	int Y;
	TScanbeam *Next;
} ;
#pragma pack(pop)

#pragma pack(push, 4)
struct TIntersectNode
{
	TEdge *Edge1;
	TEdge *Edge2;
	TIntPoint Pt;
} ;
#pragma pack(pop)

typedef TIntersectNode *PIntersectNode;

struct TLocalMinimum;
typedef TLocalMinimum *PLocalMinimum;

#pragma pack(push, 4)
struct TLocalMinimum
{
	int Y;
	TEdge *LeftBound;
	TEdge *RightBound;
} ;
#pragma pack(pop)

struct TOutRec;
typedef TOutRec *POutRec;

#pragma pack(push, 4)
struct TOutRec
{
	int Idx;
	TOutPt *BottomPt;
	bool IsHole;
	bool IsOpen;
	TOutRec *FirstLeft;
	TOutPt *Pts;
	TPolyNode* PolyNode;
} ;
#pragma pack(pop)

#pragma pack(push, 4)
struct TOutPt
{
	int Idx;
	TIntPoint Pt;
	TOutPt *Next;
	TOutPt *Prev;
} ;
#pragma pack(pop)

#pragma pack(push, 4)
struct TJoin
{
	TOutPt *OutPt1;
	TOutPt *OutPt2;
	TIntPoint OffPt;
} ;
#pragma pack(pop)

typedef TJoin *PJoin;

typedef TList TEgdeList;
;

typedef TList TLocMinList;
;

class DELPHICLASS TClipperBase;
class PASCALIMPLEMENTATION TClipperBase : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	Classes::TList* FEdgeList;
	bool FUse64BitRange;
	bool FHasOpenPaths;
	void __fastcall DisposeLocalMinimaList(void);
	void __fastcall DisposePolyPts(POutPt PP);
	PEdge __fastcall ProcessBound(PEdge E, bool NextIsForward);
	
protected:
	Classes::TList* FLocMinList;
	int FCurrentLocMinIdx;
	bool FPreserveCollinear;
	virtual void __fastcall Reset(void);
	__property bool HasOpenPaths = {read=FHasOpenPaths, nodefault};
	
public:
	__fastcall virtual TClipperBase(void);
	__fastcall virtual ~TClipperBase(void);
	virtual void __fastcall Clear(void);
	bool __fastcall AddPath(const TPath Path, TPolyType PolyType, bool Closed);
	bool __fastcall AddPaths(const TPaths Paths, TPolyType PolyType, bool Closed);
	__property bool PreserveCollinear = {read=FPreserveCollinear, write=FPreserveCollinear, nodefault};
};


typedef TList TPolyOutList;
;

typedef TList TJoinList;
;

typedef TList TIntersecList;
;

class DELPHICLASS TClipper;
class PASCALIMPLEMENTATION TClipper : public TClipperBase 
{
	typedef TClipperBase inherited;
	
private:
	Classes::TList* FPolyOutList;
	Classes::TList* FJoinList;
	Classes::TList* FGhostJoinList;
	Classes::TList* FIntersectList;
	TClipType FClipType;
	TScanbeam *FScanbeam;
	TEdge *FActiveEdges;
	TEdge *FSortedEdges;
	TPolyFillType FClipFillType;
	TPolyFillType FSubjFillType;
	bool FExecuteLocked;
	bool FReverseOutput;
	bool FStrictSimple;
	bool FUsingPolyTree;
	void __fastcall DisposeScanbeamList(void);
	void __fastcall InsertScanbeam(const int Y);
	int __fastcall PopScanbeam(void);
	void __fastcall SetWindingCount(PEdge Edge);
	bool __fastcall IsEvenOddFillType(PEdge Edge);
	bool __fastcall IsEvenOddAltFillType(PEdge Edge);
	void __fastcall AddEdgeToSEL(PEdge Edge);
	void __fastcall CopyAELToSEL(void);
	void __fastcall InsertLocalMinimaIntoAEL(const int BotY);
	void __fastcall SwapPositionsInAEL(PEdge E1, PEdge E2);
	void __fastcall SwapPositionsInSEL(PEdge E1, PEdge E2);
	void __fastcall ProcessHorizontal(PEdge HorzEdge, bool IsTopOfScanbeam);
	void __fastcall ProcessHorizontals(bool IsTopOfScanbeam);
	bool __fastcall ProcessIntersections(const int TopY);
	void __fastcall BuildIntersectList(const int TopY);
	void __fastcall ProcessIntersectList(void);
	void __fastcall DeleteFromAEL(PEdge E);
	void __fastcall DeleteFromSEL(PEdge E);
	void __fastcall IntersectEdges(PEdge E1, PEdge E2, const TIntPoint &Pt);
	void __fastcall DoMaxima(PEdge E);
	void __fastcall UpdateEdgeIntoAEL(PEdge &E);
	bool __fastcall FixupIntersectionOrder(void);
	void __fastcall ProcessEdgesAtTopOfScanbeam(const int TopY);
	bool __fastcall IsContributing(PEdge Edge);
	POutRec __fastcall CreateOutRec(void);
	POutPt __fastcall AddOutPt(PEdge E, const TIntPoint &Pt);
	void __fastcall AddLocalMaxPoly(PEdge E1, PEdge E2, const TIntPoint &Pt);
	POutPt __fastcall AddLocalMinPoly(PEdge E1, PEdge E2, const TIntPoint &Pt);
	POutRec __fastcall GetOutRec(int Idx);
	void __fastcall AppendPolygon(PEdge E1, PEdge E2);
	void __fastcall DisposeAllOutRecs(void);
	void __fastcall DisposeOutRec(int Index);
	void __fastcall DisposeIntersectNodes(void);
	TPaths __fastcall BuildResult();
	bool __fastcall BuildResult2(TPolyTree* PolyTree);
	void __fastcall FixupOutPolygon(POutRec OutRec);
	void __fastcall SetHoleState(PEdge E, POutRec OutRec);
	void __fastcall AddJoin(POutPt Op1, POutPt Op2, const TIntPoint &OffPt);
	void __fastcall ClearJoins(void);
	void __fastcall AddGhostJoin(POutPt OutPt, const TIntPoint &OffPt);
	void __fastcall ClearGhostJoins(void);
	bool __fastcall JoinPoints(PJoin Jr, POutRec OutRec1, POutRec OutRec2);
	void __fastcall FixupFirstLefts1(POutRec OldOutRec, POutRec NewOutRec);
	void __fastcall FixupFirstLefts2(POutRec OldOutRec, POutRec NewOutRec);
	void __fastcall DoSimplePolygons(void);
	void __fastcall JoinCommonEdges(void);
	void __fastcall FixHoleLinkage(POutRec OutRec);
	
protected:
	virtual void __fastcall Reset(void);
	virtual bool __fastcall ExecuteInternal(void);
	
public:
	bool __fastcall Execute(TClipType clipType, /* out */ TPaths &solution, TPolyFillType subjFillType = (TPolyFillType)(0x0), TPolyFillType clipFillType = (TPolyFillType)(0x0))/* overload */;
	bool __fastcall Execute(TClipType clipType, /* out */ TPolyTree* &PolyTree, TPolyFillType subjFillType = (TPolyFillType)(0x0), TPolyFillType clipFillType = (TPolyFillType)(0x0))/* overload */;
	__fastcall TClipper(TInitOptions InitOptions)/* overload */;
	__fastcall virtual ~TClipper(void);
	__property bool ReverseSolution = {read=FReverseOutput, write=FReverseOutput, nodefault};
	__property bool StrictlySimple = {read=FStrictSimple, write=FStrictSimple, nodefault};
};


class DELPHICLASS TClipperOffset;
class PASCALIMPLEMENTATION TClipperOffset : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	double FDelta;
	Extended FSinA;
	Extended FSin;
	Extended FCos;
	double FMiterLim;
	double FStepsPerRad;
	DynamicArray<TDoublePoint >  FNorms;
	DynamicArray<DynamicArray<TIntPoint > >  FSolution;
	int FOutPos;
	DynamicArray<TIntPoint >  FInP;
	DynamicArray<TIntPoint >  FOutP;
	TIntPoint FLowest;
	TPolyNode* FPolyNodes;
	double FMiterLimit;
	double FArcTolerance;
	void __fastcall AddPoint(const TIntPoint &Pt);
	void __fastcall DoSquare(int J, int K);
	void __fastcall DoMiter(int J, int K, double R);
	void __fastcall DoRound(int J, int K);
	void __fastcall OffsetPoint(int J, int &K, TJoinType JoinType);
	void __fastcall FixOrientations(void);
	void __fastcall DoOffset(double Delta);
	
public:
	__fastcall TClipperOffset(double MiterLimit, double ArcTolerance);
	__fastcall virtual ~TClipperOffset(void);
	void __fastcall AddPath(const TPath Path, TJoinType JoinType, TEndType EndType);
	void __fastcall AddPaths(const TPaths Paths, TJoinType JoinType, TEndType EndType);
	void __fastcall Clear(void);
	void __fastcall Execute(/* out */ TPaths &solution, double Delta)/* overload */;
	void __fastcall Execute(/* out */ TPolyTree* &solution, double Delta)/* overload */;
	__property double MiterLimit = {read=FMiterLimit, write=FMiterLimit};
	__property double ArcTolerance = {read=FArcTolerance, write=FArcTolerance};
};


//-- var, const, procedure ---------------------------------------------------
#define def_arc_tolerance  (2.500000E-01)
extern PACKAGE int LoRange;
extern PACKAGE int HiRange;
extern PACKAGE TIntPoint __fastcall IntPoint(const int X, const int Y)/* overload */;
extern PACKAGE TIntPoint __fastcall IntPoint(const double X, const double Y)/* overload */;
extern PACKAGE TDoublePoint __fastcall DoublePoint(const double X, const double Y)/* overload */;
extern PACKAGE TDoublePoint __fastcall DoublePoint(const TIntPoint &Ip)/* overload */;
extern PACKAGE double __fastcall Area(const TPath Pts)/* overload */;
extern PACKAGE bool __fastcall Orientation(const TPath Pts)/* overload */;
extern PACKAGE TPath __fastcall ReversePath(const TPath Pts);
extern PACKAGE TPaths __fastcall ReversePaths(const TPaths Pts);
extern PACKAGE TIntRect __fastcall GetBounds(const TPaths polys);
extern PACKAGE int __fastcall PointInPolygon(const TIntPoint &pt, const TPath poly)/* overload */;
extern PACKAGE TPaths __fastcall SimplifyPolygon(const TPath Poly, TPolyFillType FillType = (TPolyFillType)(0x0));
extern PACKAGE TPaths __fastcall SimplifyPolygons(const TPaths Polys, TPolyFillType FillType = (TPolyFillType)(0x0));
extern PACKAGE TPath __fastcall CleanPolygon(const TPath Poly, double Distance = 1.415000E+00);
extern PACKAGE TPaths __fastcall CleanPolygons(const TPaths Polys, double Distance = 1.415000E+00);
extern PACKAGE TPaths __fastcall MinkowskiSum(const TPath Pattern, const TPath Path, bool PathIsClosed)/* overload */;
extern PACKAGE TPaths __fastcall MinkowskiSum(const TPath Pattern, const TPaths Paths, TPolyFillType PathFillType, bool PathIsClosed)/* overload */;
extern PACKAGE TPaths __fastcall MinkowskiDiff(const TPath Poly1, const TPath Poly2);
extern PACKAGE TPaths __fastcall PolyTreeToPaths(TPolyTree* PolyTree);
extern PACKAGE TPaths __fastcall ClosedPathsFromPolyTree(TPolyTree* PolyTree);
extern PACKAGE TPaths __fastcall OpenPathsFromPolyTree(TPolyTree* PolyTree);

}	/* namespace Clipper */
using namespace Clipper;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// clipper
