// ************************************************************************ //
// WARNING                                                                    
// -------                                                                    
// The types declared in this file were generated from data read from a       
// Type Library. If this type library is explicitly or indirectly (via        
// another type library referring to this type library) re-imported, or the   
// 'Refresh' command of the Type Library Editor activated while editing the   
// Type Library, the contents of this file will be regenerated and all        
// manual modifications will be lost.                                         
// ************************************************************************ //

// C++ TLBWRTR : $Revision:   1.151.1.0.1.27  $
// File generated on 2016/10/23 19:34:00 from Type Library described below.

// ************************************************************************  //
// Type Lib: C:\Windows\SysWOW64\PcommServer.exe (1)
// LIBID: {50ECCF67-B73C-431B-A53D-9EDDAF3CE611}
// LCID: 0
// Helpfile: 
// HelpString: PcommServer 1.0 Type Library
// DepndLst: 
//   (1) v2.0 stdole, (C:\Windows\SysWOW64\stdole2.tlb)
// Errors:
//   Error creating palette bitmap of (TPmacDevice) : Could not load "C:\Windows\SysWOW64\PcommServer.exe". The OLE control may possibly require support libraries that are not on the current search path or are not present on your system
//   Error creating palette bitmap of (TPmacNC) : Could not load "C:\Windows\SysWOW64\PcommServer.exe". The OLE control may possibly require support libraries that are not on the current search path or are not present on your system
// ************************************************************************ //

#include <vcl.h>
#pragma hdrstop

#include "PCOMMSERVERLib_TLB.h"

#if !defined(__PRAGMA_PACKAGE_SMART_INIT)
#define      __PRAGMA_PACKAGE_SMART_INIT
#pragma package(smart_init)
#endif

namespace Pcommserverlib_tlb
{


// *********************************************************************//
// GUIDS declared in the TypeLibrary                                      
// *********************************************************************//
const GUID LIBID_PCOMMSERVERLib = {0x50ECCF67, 0xB73C, 0x431B,{ 0xA5, 0x3D, 0x9E,0xDD, 0xAF, 0x3C,0xE6, 0x11} };
const GUID GUID_DEVVBGWFORMAT = {0x393DA2FF, 0x814B, 0x4B76,{ 0xA2, 0x7A, 0x9C,0xD4, 0xE2, 0x2D,0xCA, 0x61} };
const GUID GUID_DEVBGVREADSTATUS = {0x5B24D4EE, 0x2ADF, 0x47A0,{ 0x9A, 0xE1, 0xC4,0x4F, 0xC9, 0xF6,0x0D, 0x64} };
const GUID GUID_DEVPLC_STATUS_STRUCT = {0x3AE1BF80, 0xC9DB, 0x421D,{ 0x98, 0x10, 0xF9,0x22, 0xC7, 0xF4,0x83, 0x53} };
const GUID GUID_DEVPLCC_STATUS_STRUCT = {0x4285678F, 0x0504, 0x49C0,{ 0xAD, 0x56, 0x9E,0x50, 0xDC, 0x66,0x09, 0xEC} };
const GUID GUID_DEVTOTAL_PLC_STATUS_STRUCT = {0x886BD577, 0x3E89, 0x4888,{ 0xA1, 0xB8, 0x5D,0x5B, 0x49, 0x9B,0x63, 0xEC} };
const GUID GUID_DEVWTG_EX = {0x4A568FA4, 0x62CE, 0x485D,{ 0xB4, 0x12, 0x2A,0x5D, 0x7C, 0xEF,0xB5, 0x9B} };
const GUID GUID_DEVGATHER_INFO = {0x8806F6C1, 0xC9AD, 0x400B,{ 0x8A, 0xE0, 0x01,0xC8, 0x36, 0x8F,0xE0, 0x81} };
const GUID GUID_DEVGATHER_HEADER = {0x8806F6C1, 0xC9AE, 0x400B,{ 0x8A, 0xE0, 0x01,0xC8, 0x36, 0x8F,0xE0, 0x81} };
const GUID GUID_DEVULTRALIGHT_INFO = {0x487269C0, 0xF8D0, 0x4427,{ 0x96, 0x4E, 0x25,0x50, 0x62, 0xAB,0x06, 0xAD} };
const GUID GUID_DEVFGMOTORTURBO = {0x3EA804DC, 0x232C, 0x4034,{ 0x87, 0x82, 0x6C,0x96, 0x19, 0x3C,0xB5, 0xDB} };
const GUID GUID_DEVFGMOTOR = {0x30D26998, 0xDE15, 0x4A48,{ 0x98, 0xE9, 0xD6,0x77, 0x5F, 0xB9,0xCF, 0x07} };
const GUID GUID_DEVBGCOORD = {0xAB7AA06E, 0x496B, 0x4B00,{ 0xAE, 0x82, 0x12,0x3E, 0xAF, 0xEF,0xFA, 0x97} };
const GUID GUID_DEVBGCOORDTURBO = {0xAA40823A, 0x421B, 0x4356,{ 0xAA, 0xE4, 0xAE,0xD6, 0x6B, 0xBC,0x38, 0x23} };
const GUID GUID_DEVPOSDATASTRUCT = {0x0F4295F0, 0xD83B, 0x4DEA,{ 0xA2, 0x7E, 0x60,0xE8, 0xAD, 0xFB,0xA6, 0xD6} };
const GUID GUID_DEVDATA = {0xA1670AD2, 0x1F58, 0x4A32,{ 0x8B, 0xAD, 0x34,0x93, 0x18, 0x4B,0x2D, 0x27} };
const GUID GUID_DEVPOSDATA = {0x6387F23B, 0x2BCC, 0x4865,{ 0xA0, 0x16, 0xC9,0xD6, 0x67, 0x7B,0x44, 0xDE} };
const GUID GUID_pmacStripPlotDATA = {0xA1670AD2, 0x1F57, 0x4A32,{ 0x8B, 0xAD, 0x34,0x93, 0x18, 0x4B,0x2D, 0x27} };
const GUID GUID_DEVMSTURBO = {0xF655ABB9, 0xD995, 0x4F86,{ 0x96, 0x4B, 0xCA,0x37, 0xAD, 0xCE,0x3B, 0x73} };
const GUID GUID_DEVMSNONTURBO = {0xD655ABB9, 0xD095, 0x4F96,{ 0x96, 0x4B, 0xCA,0x36, 0xAD, 0xCE,0x3B, 0x73} };
const GUID GUID_DEVGSTURBO = {0xD666ABC9, 0xD195, 0x4F95,{ 0x96, 0x5B, 0xCA,0x36, 0xAD, 0xDE,0x4B, 0x73} };
const GUID GUID_DEVGSNONTURBO = {0xD656ABB9, 0xD195, 0x4F95,{ 0x96, 0x5B, 0xCA,0x36, 0xAD, 0xCE,0x3B, 0x73} };
const GUID GUID_DEVCSTURBO = {0xD353ABB9, 0xD135, 0x4F35,{ 0x96, 0x5B, 0xCA,0x36, 0xAD, 0xCE,0x3B, 0x33} };
const GUID GUID_DEVCSNONTURBO = {0xD344ABB9, 0xD435, 0x4F35,{ 0x96, 0x5B, 0xCA,0x46, 0xAD, 0xCE,0x3B, 0x44} };
const GUID GUID_DEVUPLOAD = {0xD377ABB9, 0xD435, 0x4F35,{ 0x97, 0x5B, 0xCA,0x47, 0xAD, 0xCE,0x3B, 0x77} };
const GUID IID_IPmacDevice = {0x8A00B576, 0x9C14, 0x425B,{ 0x88, 0x78, 0x49,0x3C, 0x91, 0xD8,0xDE, 0x5C} };
const GUID DIID__IPmacDeviceEvents = {0xD1C5C7C8, 0x5E0C, 0x495E,{ 0x9A, 0xAF, 0x85,0xB1, 0x46, 0xDA,0x5F, 0x13} };
const GUID CLSID_PmacDevice = {0xB544D2BD, 0x354C, 0x456E,{ 0x9E, 0x88, 0x20,0xF7, 0x16, 0x25,0xE7, 0xDF} };
const GUID GUID_NCTOOL = {0xDC1E4F4D, 0x460F, 0x4BB6,{ 0xAF, 0xB6, 0x63,0x49, 0xED, 0x9F,0x7A, 0x52} };
const GUID GUID_NCTOOLLIFE = {0xBF167284, 0x5EBC, 0x4B7C,{ 0xAA, 0x59, 0x5B,0x31, 0x2E, 0x8E,0x5C, 0x7C} };
const GUID GUID_NCDATA = {0x5B1330B2, 0xD46E, 0x4F0C,{ 0x91, 0x2D, 0x2B,0xB8, 0x1B, 0xA7,0x6C, 0x20} };
const GUID IID_IPmacNC = {0x0A322163, 0xC2E1, 0x4152,{ 0xAD, 0xED, 0x91,0x74, 0x0A, 0xCE,0x75, 0x13} };
const GUID DIID__IPmacNCEvents = {0x32C9ADDE, 0x9F29, 0x4658,{ 0x8E, 0xC3, 0xF1,0xB8, 0x39, 0x5F,0xE1, 0x9F} };
const GUID CLSID_PmacNC = {0x450149A8, 0xE6B7, 0x4563,{ 0x80, 0x38, 0xFB,0xCA, 0xD0, 0x25,0xD0, 0x56} };

};     // namespace Pcommserverlib_tlb