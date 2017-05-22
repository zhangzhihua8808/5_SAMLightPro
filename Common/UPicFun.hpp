// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'UPicFun.pas' rev: 6.00

#ifndef UPicFunHPP
#define UPicFunHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <jpeg.hpp>	// Pascal unit
#include <ExtDlgs.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Variants.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Upicfun
{
//-- type declarations -------------------------------------------------------
//-- var, const, procedure ---------------------------------------------------
extern PACKAGE void __fastcall CombinBmp(Classes::TStrings* BmpFilNames, AnsiString MType, Graphics::TBitmap* &Desbmp)/* overload */;
extern PACKAGE void __fastcall CombinBmp(Classes::TStrings* BmpFilNames, int HNum, int ZNum, Graphics::TBitmap* &Desbmp)/* overload */;
extern PACKAGE Graphics::TBitmap* __fastcall LoadGraphicsFile(const AnsiString Filename);
extern PACKAGE void __fastcall GetLocalPic(AnsiString FileName, int EndX, int EndY, int StX, int StY, Graphics::TBitmap* &Bmp);
extern PACKAGE void __fastcall Bmp2Jpg(Graphics::TBitmap* Bmp, int Quality, Jpeg::TJPEGImage* &Jpg);
extern PACKAGE double __fastcall DuFenMiao_To_Miao(AnsiString aDuFenMiao);
extern PACKAGE AnsiString __fastcall Miao_To_DuFenMiao(double i_Miao, AnsiString aDu_Sp = "-", AnsiString aFen_Sp = "-", AnsiString aMiao_Sp = "");
extern PACKAGE void __fastcall bmpSaveasJpg(Graphics::TBitmap* Tmpbmp, AnsiString FilePath);
extern PACKAGE void __fastcall CombinPic(int ZNum, int HNum, AnsiString StJd, AnsiString StWd, AnsiString DeltJd, AnsiString DeltWd, AnsiString Filepath, AnsiString SavePath, bool IsGoOn = true);

}	/* namespace Upicfun */
using namespace Upicfun;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// UPicFun
