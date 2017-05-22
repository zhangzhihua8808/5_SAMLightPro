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

#include <olectrls.hpp>
#include <oleserver.hpp>
#if defined(USING_ATL)
#include <atl\atlvcl.h>
#endif

#include "PCOMMSERVERLib_OCX.h"

#if !defined(__PRAGMA_PACKAGE_SMART_INIT)
#define      __PRAGMA_PACKAGE_SMART_INIT
#pragma package(smart_init)
#endif

namespace Pcommserverlib_tlb
{



// *********************************************************************//
// OCX PROXY CLASS IMPLEMENTATION
// (The following variables/methods implement the class TPmacDevice which
// allows "PmacDevice Class" to be hosted in CBuilder IDE/apps).
// *********************************************************************//
int   TPmacDevice::EventDispIDs[6] = {
    0x00000001, 0x00000002, 0x00000003, 0x00000004, 0x00000005, 0x00000006};

TControlData TPmacDevice::CControlData =
{
  // GUID of CoClass and Event Interface of Control
  {0xB544D2BD, 0x354C, 0x456E,{ 0x9E, 0x88, 0x20,0xF7, 0x16, 0x25,0xE7, 0xDF} }, // CoClass
  {0xD1C5C7C8, 0x5E0C, 0x495E,{ 0x9A, 0xAF, 0x85,0xB1, 0x46, 0xDA,0x5F, 0x13} }, // Events

  // Count of Events and array of their DISPIDs
  6, &EventDispIDs,

  // Pointer to Runtime License string
  NULL,  // HRESULT(0x80004002)

  // Flags for OnChanged PropertyNotification
  0x00000000,
  300,// (IDE Version)

  // Count of Font Prop and array of their DISPIDs
  0, NULL,

  // Count of Pict Prop and array of their DISPIDs
  0, NULL,
  0, // Reserved
  0, // Instance count (used internally)
  0, // List of Enum descriptions (internal)
};

GUID     TPmacDevice::DEF_CTL_INTF = {0x8A00B576, 0x9C14, 0x425B,{ 0x88, 0x78, 0x49,0x3C, 0x91, 0xD8,0xDE, 0x5C} };
TNoParam TPmacDevice::OptParam;

static inline void ValidCtrCheck(TPmacDevice *)
{
   delete new TPmacDevice((TComponent*)(0));
};

void __fastcall TPmacDevice::InitControlData()
{
  ControlData = &CControlData;
};

void __fastcall TPmacDevice::CreateControl()
{
  if (!m_OCXIntf)
  {
    _ASSERTE(DefaultDispatch);
    DefaultDispatch->QueryInterface(DEF_CTL_INTF, (LPVOID*)&m_OCXIntf);
  }
};

TCOMIPmacDevice __fastcall TPmacDevice::GetDefaultInterface()
{
  CreateControl();
  return m_OCXIntf;
};

void __fastcall TPmacDevice::Open(long dwDevice/*[in]*/, VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->Open(dwDevice/*[in]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::Close(long dwDevice/*[in]*/)
{
  GetDefaultInterface()->Close(dwDevice/*[in]*/);
}

void __fastcall TPmacDevice::DataStart(long dwDevice/*[in]*/, long resolution/*[in]*/, 
                                       long period/*[in]*/)
{
  GetDefaultInterface()->DataStart(dwDevice/*[in]*/, resolution/*[in]*/, period/*[in]*/);
}

void __fastcall TPmacDevice::DataStop(long dwDevice/*[in]*/)
{
  GetDefaultInterface()->DataStop(dwDevice/*[in]*/);
}

void __fastcall TPmacDevice::DataCollect(long dwDevice/*[in]*/, VARIANT* pvArray/*[in,out]*/, 
                                         VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->DataCollect(dwDevice/*[in]*/, pvArray/*[in,out]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::DPRBackGroundVar(long dwDevice/*[in]*/, VARIANT_BOOL bOn/*[in]*/)
{
  GetDefaultInterface()->DPRBackGroundVar(dwDevice/*[in]*/, bOn/*[in]*/);
}

void __fastcall TPmacDevice::DPRAddressRange(long dwDevice/*[in]*/, VARIANT_BOOL bUpper/*[in]*/, 
                                             VARIANT_BOOL bPC/*[in]*/, long* pVal/*[out]*/)
{
  GetDefaultInterface()->DPRAddressRange(dwDevice/*[in]*/, bUpper/*[in]*/, bPC/*[in]*/, 
                                         pVal/*[out]*/);
}

void __fastcall TPmacDevice::GetPmacType(long dwDevice/*[in]*/, 
                                         Pcommserverlib_tlb::DEVPMACTYPE* pVal/*[out]*/)
{
  GetDefaultInterface()->GetPmacType(dwDevice/*[in]*/, pVal/*[out]*/);
}

void __fastcall TPmacDevice::DPRVarBufRemove(long dwDevice/*[in]*/, long index/*[in]*/, 
                                             VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->DPRVarBufRemove(dwDevice/*[in]*/, index/*[in]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::DPRVarBufRead(long dwDevice/*[in]*/, long h/*[in]*/, 
                                           long entryNum/*[in]*/, VARIANT* pVal/*[in,out]*/, 
                                           VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->DPRVarBufRead(dwDevice/*[in]*/, h/*[in]*/, entryNum/*[in]*/, 
                                       pVal/*[in,out]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::DPRGetFloat(long dwDevice/*[in]*/, long offset/*[in]*/, 
                                         float* pVal/*[out]*/, VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->DPRGetFloat(dwDevice/*[in]*/, offset/*[in]*/, pVal/*[out]*/, 
                                     pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::DPRGetLong(long dwDevice/*[in]*/, long offset/*[in]*/, 
                                        long* pVal/*[out]*/, VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->DPRGetLong(dwDevice/*[in]*/, offset/*[in]*/, pVal/*[out]*/, 
                                    pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::DPRVarBufInit(long dwDevice/*[in]*/, VARIANT vAddressArray/*[in]*/, 
                                           VARIANT vTypeArray/*[in]*/, long* pHandle/*[out]*/, 
                                           VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->DPRVarBufInit(dwDevice/*[in]*/, vAddressArray/*[in]*/, vTypeArray/*[in]*/, 
                                       pHandle/*[out]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::DPRSetFloat(long dwDevice/*[in]*/, long offset/*[in]*/, 
                                         float newVal/*[in]*/, VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->DPRSetFloat(dwDevice/*[in]*/, offset/*[in]*/, newVal/*[in]*/, 
                                     pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::DPRSetLong(long dwDevice/*[in]*/, long offset/*[in]*/, 
                                        long newVal/*[in]*/, VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->DPRSetLong(dwDevice/*[in]*/, offset/*[in]*/, newVal/*[in]*/, 
                                    pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::DPRVarBufWrite(long dwDevice/*[in]*/, VARIANT vData/*[in]*/, 
                                            VARIANT vAddresses/*[in]*/, VARIANT vTypes/*[in]*/, 
                                            long* pWritten/*[out]*/)
{
  GetDefaultInterface()->DPRVarBufWrite(dwDevice/*[in]*/, vData/*[in]*/, vAddresses/*[in]*/, 
                                        vTypes/*[in]*/, pWritten/*[out]*/);
}

void __fastcall TPmacDevice::DPRFloat(__int64 d/*[in]*/, double scale/*[in]*/, double* pVal/*[out]*/)
{
  GetDefaultInterface()->DPRFloat(d/*[in]*/, scale/*[in]*/, pVal/*[out]*/);
}

void __fastcall TPmacDevice::GetRomVersion(long dwDevice/*[in]*/, BSTR* pVal/*[out]*/)
{
  GetDefaultInterface()->GetRomVersion(dwDevice/*[in]*/, pVal/*[out]*/);
}

void __fastcall TPmacDevice::GetRomDate(long dwDevice/*[in]*/, BSTR* pVal/*[out]*/)
{
  GetDefaultInterface()->GetRomDate(dwDevice/*[in]*/, pVal/*[out]*/);
}

void __fastcall TPmacDevice::GetPmacLocation(long dwDevice/*[in]*/, 
                                             Pcommserverlib_tlb::DEVLOCATIONTYPE* pVal/*[out]*/)
{
  GetDefaultInterface()->GetPmacLocation(dwDevice/*[in]*/, pVal/*[out]*/);
}

void __fastcall TPmacDevice::GetResponse(long dwDevice/*[in]*/, BSTR question/*[in]*/, 
                                         BSTR* pAnswer/*[out]*/)
{
  GetDefaultInterface()->GetResponse(dwDevice/*[in]*/, question/*[in]*/, pAnswer/*[out]*/);
}

void __fastcall TPmacDevice::SelectDevice(long hWindow/*[in]*/, long* pDeviceNumber/*[out]*/, 
                                          VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->SelectDevice(hWindow/*[in]*/, pDeviceNumber/*[out]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::SetChecksums(long dwDevice/*[in]*/, VARIANT_BOOL bActive/*[in]*/)
{
  GetDefaultInterface()->SetChecksums(dwDevice/*[in]*/, bActive/*[in]*/);
}

void __fastcall TPmacDevice::GetControlResponse(long dwDevice/*[in]*/, short question/*[in]*/, 
                                                BSTR* pAnswer/*[out]*/)
{
  GetDefaultInterface()->GetControlResponse(dwDevice/*[in]*/, question/*[in]*/, pAnswer/*[out]*/);
}

void __fastcall TPmacDevice::GetLastCommErrorStr(long dwDevice/*[in]*/, BSTR* pVal/*[out]*/)
{
  GetDefaultInterface()->GetLastCommErrorStr(dwDevice/*[in]*/, pVal/*[out]*/);
}

void __fastcall TPmacDevice::GetMacroIVariableLong(long dwDevice/*[in]*/, long node/*[in]*/, 
                                                   long num/*[in]*/, long def/*[in]*/, 
                                                   long* pVal/*[out]*/)
{
  GetDefaultInterface()->GetMacroIVariableLong(dwDevice/*[in]*/, node/*[in]*/, num/*[in]*/, 
                                               def/*[in]*/, pVal/*[out]*/);
}

void __fastcall TPmacDevice::GetIVariableLong(long dwDevice/*[in]*/, long num/*[in]*/, 
                                              long def/*[in]*/, long* pVal/*[out]*/)
{
  GetDefaultInterface()->GetIVariableLong(dwDevice/*[in]*/, num/*[in]*/, def/*[in]*/, pVal/*[out]*/);
}

void __fastcall TPmacDevice::GetIVariableDouble(long dwDevice/*[in]*/, long num/*[in]*/, 
                                                double def/*[in]*/, double* pVal/*[out]*/)
{
  GetDefaultInterface()->GetIVariableDouble(dwDevice/*[in]*/, num/*[in]*/, def/*[in]*/, 
                                            pVal/*[out]*/);
}

void __fastcall TPmacDevice::SetIVariableLong(long dwDevice/*[in]*/, long num/*[in]*/, 
                                              long newVal/*[in]*/)
{
  GetDefaultInterface()->SetIVariableLong(dwDevice/*[in]*/, num/*[in]*/, newVal/*[in]*/);
}

void __fastcall TPmacDevice::SetIVariableDouble(long dwDevice/*[in]*/, long num/*[in]*/, 
                                                double newVal/*[in]*/)
{
  GetDefaultInterface()->SetIVariableDouble(dwDevice/*[in]*/, num/*[in]*/, newVal/*[in]*/);
}

void __fastcall TPmacDevice::GetAsciiComm(long dwDevice/*[in]*/, 
                                          Pcommserverlib_tlb::DEVASCIIMODE* pVal/*[out]*/)
{
  GetDefaultInterface()->GetAsciiComm(dwDevice/*[in]*/, pVal/*[out]*/);
}

void __fastcall TPmacDevice::SetAsciiComm(long dwDevice/*[in]*/, 
                                          Pcommserverlib_tlb::DEVASCIIMODE newVal/*[in]*/)
{
  GetDefaultInterface()->SetAsciiComm(dwDevice/*[in]*/, newVal/*[in]*/);
}

void __fastcall TPmacDevice::GetVariableLong(long dwDevice/*[in]*/, short ch/*[in]*/, 
                                             long num/*[in]*/, long def/*[in]*/, long* pVal/*[out]*/, 
                                             VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->GetVariableLong(dwDevice/*[in]*/, ch/*[in]*/, num/*[in]*/, def/*[in]*/, 
                                         pVal/*[out]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::GetVariableDouble(long dwDevice/*[in]*/, short ch/*[in]*/, 
                                               long num/*[in]*/, double def/*[in]*/, 
                                               double* pVal/*[out]*/, 
                                               VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->GetVariableDouble(dwDevice/*[in]*/, ch/*[in]*/, num/*[in]*/, def/*[in]*/, 
                                           pVal/*[out]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::SetVariableLong(long dwDevice/*[in]*/, short ch/*[in]*/, 
                                             long num/*[in]*/, long newVal/*[in]*/, 
                                             VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->SetVariableLong(dwDevice/*[in]*/, ch/*[in]*/, num/*[in]*/, newVal/*[in]*/, 
                                         pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::SetVariableDouble(long dwDevice/*[in]*/, short ch/*[in]*/, 
                                               long num/*[in]*/, double newVal/*[in]*/, 
                                               VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->SetVariableDouble(dwDevice/*[in]*/, ch/*[in]*/, num/*[in]*/, newVal/*[in]*/, 
                                           pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::RestoreLinkList(BSTR firmwareVersion/*[in]*/, 
                                             VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->RestoreLinkList(firmwareVersion/*[in]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::BackupLinkList(long dwDevice/*[in]*/, VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->BackupLinkList(dwDevice/*[in]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::SetCriticalIVars(long dwDevice/*[in]*/, 
                                              VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->SetCriticalIVars(dwDevice/*[in]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::GetLocAndEnum(long dwDevice/*[in]*/, long* pLoc/*[out]*/, 
                                           long* pEnum/*[out]*/, VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->GetLocAndEnum(dwDevice/*[in]*/, pLoc/*[out]*/, pEnum/*[out]*/, 
                                       pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::GetProgramInfo(long dwDevice/*[in]*/, VARIANT_BOOL bPlc/*[in]*/, 
                                            long num/*[in]*/, long* pSAdr/*[out]*/, 
                                            long* pFAdr/*[out]*/)
{
  GetDefaultInterface()->GetProgramInfo(dwDevice/*[in]*/, bPlc/*[in]*/, num/*[in]*/, pSAdr/*[out]*/, 
                                        pFAdr/*[out]*/);
}

void __fastcall TPmacDevice::DownloadFile(long dwDevice/*[in]*/, BSTR filePath/*[in]*/)
{
  GetDefaultInterface()->DownloadFile(dwDevice/*[in]*/, filePath/*[in]*/);
}

void __fastcall TPmacDevice::AbortDownload(long dwDevice/*[in]*/)
{
  GetDefaultInterface()->AbortDownload(dwDevice/*[in]*/);
}

void __fastcall TPmacDevice::DownloadFirmwareFile(long dwDevice/*[in]*/, BSTR filePath/*[in]*/, 
                                                  VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->DownloadFirmwareFile(dwDevice/*[in]*/, filePath/*[in]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::Download(long dwDevice/*[in]*/, BSTR filePath/*[in]*/, 
                                      VARIANT_BOOL bMacro/*[in]*/, VARIANT_BOOL bMap/*[in]*/, 
                                      VARIANT_BOOL bLog/*[in]*/, VARIANT_BOOL bDnld/*[in]*/, 
                                      VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->Download(dwDevice/*[in]*/, filePath/*[in]*/, bMacro/*[in]*/, bMap/*[in]*/, 
                                  bLog/*[in]*/, bDnld/*[in]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::CompilePLCC(long dwDevice/*[in]*/, BSTR inFilePath/*[in]*/, 
                                         BSTR outFilePath/*[in]*/, VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->CompilePLCC(dwDevice/*[in]*/, inFilePath/*[in]*/, outFilePath/*[in]*/, 
                                     pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::SendCommand(long dwDevice/*[in]*/, BSTR cmd/*[in]*/, 
                                         long* pstatus/*[out]*/)
{
  GetDefaultInterface()->SendCommand(dwDevice/*[in]*/, cmd/*[in]*/, pstatus/*[out]*/);
}

void __fastcall TPmacDevice::GetPlcStatus(long dwDevice/*[in]*/, long* pNumPlc/*[out]*/, 
                                          long* pNumPlcc/*[out]*/, long* pI5/*[out]*/)
{
  GetDefaultInterface()->GetPlcStatus(dwDevice/*[in]*/, pNumPlc/*[out]*/, pNumPlcc/*[out]*/, 
                                      pI5/*[out]*/);
}

void __fastcall TPmacDevice::GetFirstPlcc(long dwDevice/*[in]*/, VARIANT_BOOL* pbLoaded/*[out]*/, 
                                          VARIANT_BOOL* pbEnabled/*[out]*/, long* pStartAdr/*[out]*/, 
                                          long* pLastAdr/*[out]*/, long* pSize/*[out]*/, 
                                          VARIANT_BOOL* pbMore/*[out]*/)
{
  GetDefaultInterface()->GetFirstPlcc(dwDevice/*[in]*/, pbLoaded/*[out]*/, pbEnabled/*[out]*/, 
                                      pStartAdr/*[out]*/, pLastAdr/*[out]*/, pSize/*[out]*/, 
                                      pbMore/*[out]*/);
}

void __fastcall TPmacDevice::GetNextPlcc(long dwDevice/*[in]*/, VARIANT_BOOL* pbLoaded/*[out]*/, 
                                         VARIANT_BOOL* pbEnabled/*[out]*/, long* pStartAdr/*[out]*/, 
                                         long* pLastAdr/*[out]*/, long* pSize/*[out]*/, 
                                         VARIANT_BOOL* pbMore/*[out]*/)
{
  GetDefaultInterface()->GetNextPlcc(dwDevice/*[in]*/, pbLoaded/*[out]*/, pbEnabled/*[out]*/, 
                                     pStartAdr/*[out]*/, pLastAdr/*[out]*/, pSize/*[out]*/, 
                                     pbMore/*[out]*/);
}

void __fastcall TPmacDevice::GetFirstPlc(long dwDevice/*[in]*/, VARIANT_BOOL* pbEnabled/*[out]*/, 
                                         long* pStartAdr/*[out]*/, long* pLastAdr/*[out]*/, 
                                         long* pSize/*[out]*/, VARIANT_BOOL* pbMore/*[out]*/)
{
  GetDefaultInterface()->GetFirstPlc(dwDevice/*[in]*/, pbEnabled/*[out]*/, pStartAdr/*[out]*/, 
                                     pLastAdr/*[out]*/, pSize/*[out]*/, pbMore/*[out]*/);
}

void __fastcall TPmacDevice::GetNextPlc(long dwDevice/*[in]*/, VARIANT_BOOL* pbEnabled/*[out]*/, 
                                        long* pStartAdr/*[out]*/, long* pLastAdr/*[out]*/, 
                                        long* pSize/*[out]*/, VARIANT_BOOL* pbMore/*[out]*/)
{
  GetDefaultInterface()->GetNextPlc(dwDevice/*[in]*/, pbEnabled/*[out]*/, pStartAdr/*[out]*/, 
                                    pLastAdr/*[out]*/, pSize/*[out]*/, pbMore/*[out]*/);
}

void __fastcall TPmacDevice::GetGlobalStatus(long dwDevice/*[in]*/, long* pStatusX/*[out]*/, 
                                             long* pStatusY/*[out]*/, 
                                             VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->GetGlobalStatus(dwDevice/*[in]*/, pStatusX/*[out]*/, pStatusY/*[out]*/, 
                                         pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::GetCoordStatus(long dwDevice/*[in]*/, long dwCoord/*[in]*/, 
                                            long* pStatusX/*[out]*/, long* pStatusY/*[out]*/, 
                                            VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->GetCoordStatus(dwDevice/*[in]*/, dwCoord/*[in]*/, pStatusX/*[out]*/, 
                                        pStatusY/*[out]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::GetMotorStatus(long dwDevice/*[in]*/, long lMotor/*[in]*/, 
                                            long* pStatusX/*[out]*/, long* pStatusY/*[out]*/, 
                                            VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->GetMotorStatus(dwDevice/*[in]*/, lMotor/*[in]*/, pStatusX/*[out]*/, 
                                        pStatusY/*[out]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::GetCommandedPos(long dwDevice/*[in]*/, long mtr/*[in]*/, 
                                             double scale/*[in]*/, double* pVal/*[out]*/)
{
  GetDefaultInterface()->GetCommandedPos(dwDevice/*[in]*/, mtr/*[in]*/, scale/*[in]*/, pVal/*[out]*/);
}

void __fastcall TPmacDevice::GetPosition(long dwDevice/*[in]*/, long mtr/*[in]*/, 
                                         double scale/*[in]*/, double* pVal/*[out]*/)
{
  GetDefaultInterface()->GetPosition(dwDevice/*[in]*/, mtr/*[in]*/, scale/*[in]*/, pVal/*[out]*/);
}

void __fastcall TPmacDevice::GetNetActualPosition(long dwDevice/*[in]*/, long mtr/*[in]*/, 
                                                  double scale/*[in]*/, double* pVal/*[out]*/)
{
  GetDefaultInterface()->GetNetActualPosition(dwDevice/*[in]*/, mtr/*[in]*/, scale/*[in]*/, 
                                              pVal/*[out]*/);
}

void __fastcall TPmacDevice::GetFollowError(long dwDevice/*[in]*/, long mtr/*[in]*/, 
                                            double scale/*[in]*/, double* pVal/*[out]*/)
{
  GetDefaultInterface()->GetFollowError(dwDevice/*[in]*/, mtr/*[in]*/, scale/*[in]*/, pVal/*[out]*/);
}

void __fastcall TPmacDevice::GetVelocity(long dwDevice/*[in]*/, long mtr/*[in]*/, 
                                         double scale/*[in]*/, double* pVal/*[out]*/)
{
  GetDefaultInterface()->GetVelocity(dwDevice/*[in]*/, mtr/*[in]*/, scale/*[in]*/, pVal/*[out]*/);
}

void __fastcall TPmacDevice::GetMasterPos(long dwDevice/*[in]*/, long mtr/*[in]*/, 
                                          double scale/*[in]*/, double* pVal/*[out]*/)
{
  GetDefaultInterface()->GetMasterPos(dwDevice/*[in]*/, mtr/*[in]*/, scale/*[in]*/, pVal/*[out]*/);
}

void __fastcall TPmacDevice::GetCompensationPos(long dwDevice/*[in]*/, long mtr/*[in]*/, 
                                                double scale/*[in]*/, double* pVal/*[out]*/)
{
  GetDefaultInterface()->GetCompensationPos(dwDevice/*[in]*/, mtr/*[in]*/, scale/*[in]*/, 
                                            pVal/*[out]*/);
}

void __fastcall TPmacDevice::GetTargetPos(long dwDevice/*[in]*/, long mtr/*[in]*/, 
                                          double scale/*[in]*/, double* pVal/*[out]*/)
{
  GetDefaultInterface()->GetTargetPos(dwDevice/*[in]*/, mtr/*[in]*/, scale/*[in]*/, pVal/*[out]*/);
}

void __fastcall TPmacDevice::GetBiasPos(long dwDevice/*[in]*/, long mtr/*[in]*/, 
                                        double scale/*[in]*/, double* pVal/*[out]*/)
{
  GetDefaultInterface()->GetBiasPos(dwDevice/*[in]*/, mtr/*[in]*/, scale/*[in]*/, pVal/*[out]*/);
}

void __fastcall TPmacDevice::GetProgExecPoint(long dwDevice/*[in]*/, long dwCoord/*[in]*/, 
                                              long* pVal/*[out]*/)
{
  GetDefaultInterface()->GetProgExecPoint(dwDevice/*[in]*/, dwCoord/*[in]*/, pVal/*[out]*/);
}

void __fastcall TPmacDevice::GetRotBufFull(long dwDevice/*[in]*/, long dwCoord/*[in]*/, 
                                           VARIANT_BOOL* pVal/*[out]*/)
{
  GetDefaultInterface()->GetRotBufFull(dwDevice/*[in]*/, dwCoord/*[in]*/, pVal/*[out]*/);
}

void __fastcall TPmacDevice::SetJogReturn(long dwDevice/*[in]*/, long mtr/*[in]*/)
{
  GetDefaultInterface()->SetJogReturn(dwDevice/*[in]*/, mtr/*[in]*/);
}

void __fastcall TPmacDevice::GetWhyMotorNotMoving(long dwDevice/*[in]*/, long motor/*[in]*/, 
                                                  long* pVal/*[out]*/)
{
  GetDefaultInterface()->GetWhyMotorNotMoving(dwDevice/*[in]*/, motor/*[in]*/, pVal/*[out]*/);
}

void __fastcall TPmacDevice::GetWhyMotorNotMovingStr(long err/*[in]*/, BSTR* pVal/*[in,out]*/)
{
  GetDefaultInterface()->GetWhyMotorNotMovingStr(err/*[in]*/, pVal/*[in,out]*/);
}

void __fastcall TPmacDevice::GetWhyCSNotMoving(long dwDevice/*[in]*/, long cs/*[in]*/, 
                                               long* pVal/*[out]*/)
{
  GetDefaultInterface()->GetWhyCSNotMoving(dwDevice/*[in]*/, cs/*[in]*/, pVal/*[out]*/);
}

void __fastcall TPmacDevice::GetWhyCSNotMovingStr(long err/*[in]*/, BSTR* pVal/*[in,out]*/)
{
  GetDefaultInterface()->GetWhyCSNotMovingStr(err/*[in]*/, pVal/*[in,out]*/);
}

void __fastcall TPmacDevice::GetNumGatherSources(long dwDevice/*[in]*/, long* pVal/*[out]*/)
{
  GetDefaultInterface()->GetNumGatherSources(dwDevice/*[in]*/, pVal/*[out]*/);
}

void __fastcall TPmacDevice::GetNumGatherSamples(long dwDevice/*[in]*/, long* pVal/*[out]*/)
{
  GetDefaultInterface()->GetNumGatherSamples(dwDevice/*[in]*/, pVal/*[out]*/);
}

void __fastcall TPmacDevice::SetGather(long dwDevice/*[in]*/, long num/*[in]*/, BSTR str/*[in]*/, 
                                       VARIANT_BOOL bEnable/*[in]*/, 
                                       VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->SetGather(dwDevice/*[in]*/, num/*[in]*/, str/*[in]*/, bEnable/*[in]*/, 
                                   pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::SetQuickGather(long dwDevice/*[in]*/, long lComMask/*[in]*/, 
                                            long lEncMask/*[in]*/, long lDacMask/*[in]*/, 
                                            long lCurMask/*[in]*/, VARIANT_BOOL bEnable/*[in]*/, 
                                            VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->SetQuickGather(dwDevice/*[in]*/, lComMask/*[in]*/, lEncMask/*[in]*/, 
                                        lDacMask/*[in]*/, lCurMask/*[in]*/, bEnable/*[in]*/, 
                                        pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::SetQuickGatherWithDirectCurrent(long dwDevice/*[in]*/, 
                                                             long lComMask/*[in]*/, 
                                                             long lEncMask/*[in]*/, 
                                                             long lDacMask/*[in]*/, 
                                                             long lCurMask/*[in]*/, 
                                                             VARIANT_BOOL bEnable/*[in]*/, 
                                                             VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->SetQuickGatherWithDirectCurrent(dwDevice/*[in]*/, lComMask/*[in]*/, 
                                                         lEncMask/*[in]*/, lDacMask/*[in]*/, 
                                                         lCurMask/*[in]*/, bEnable/*[in]*/, 
                                                         pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::GetGather(long dwDevice/*[in]*/, long num/*[in]*/, 
                                       BSTR* pStr/*[in,out]*/, VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->GetGather(dwDevice/*[in]*/, num/*[in]*/, pStr/*[in,out]*/, 
                                   pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::ClearGather(long dwDevice/*[in]*/)
{
  GetDefaultInterface()->ClearGather(dwDevice/*[in]*/);
}

void __fastcall TPmacDevice::InitGather(long dwDevice/*[in]*/, long size/*[in]*/, 
                                        double msec/*[in]*/, VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->InitGather(dwDevice/*[in]*/, size/*[in]*/, msec/*[in]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::ClearGatherData(long dwDevice/*[in]*/)
{
  GetDefaultInterface()->ClearGatherData(dwDevice/*[in]*/);
}

void __fastcall TPmacDevice::CollectGatherData(long dwDevice/*[in]*/, long* pSources/*[out]*/, 
                                               long* pSamples/*[out]*/, 
                                               VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->CollectGatherData(dwDevice/*[in]*/, pSources/*[out]*/, pSamples/*[out]*/, 
                                           pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::GetGatherSamples(long dwDevice/*[in]*/, long sourceNum/*[in]*/, 
                                              VARIANT* pVariant/*[in,out]*/, 
                                              VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->GetGatherSamples(dwDevice/*[in]*/, sourceNum/*[in]*/, pVariant/*[in,out]*/, 
                                          pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::GetGatherPoint(long dwDevice/*[in]*/, long sourceNum/*[in]*/, 
                                            long sampleNum/*[in]*/, double* pVal/*[out]*/, 
                                            VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->GetGatherPoint(dwDevice/*[in]*/, sourceNum/*[in]*/, sampleNum/*[in]*/, 
                                        pVal/*[out]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::StartGather(long dwDevice/*[in]*/, VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->StartGather(dwDevice/*[in]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::StopGather(long dwDevice/*[in]*/)
{
  GetDefaultInterface()->StopGather(dwDevice/*[in]*/);
}

void __fastcall TPmacDevice::InitPlotGather(long dwDevice/*[in]*/, long size/*[in]*/, 
                                            long period/*[in]*/, VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->InitPlotGather(dwDevice/*[in]*/, size/*[in]*/, period/*[in]*/, 
                                        pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::ReadGatherFile(long dwDevice/*[in]*/, BSTR bsFilePath/*[in]*/, 
                                            VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->ReadGatherFile(dwDevice/*[in]*/, bsFilePath/*[in]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::WriteGatherFile(long dwDevice/*[in]*/, BSTR bsFilePath/*[in]*/, 
                                             VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->WriteGatherFile(dwDevice/*[in]*/, bsFilePath/*[in]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::strtod48f(BSTR str/*[in]*/, double* pVal/*[out]*/)
{
  GetDefaultInterface()->strtod48f(str/*[in]*/, pVal/*[out]*/);
}

void __fastcall TPmacDevice::strtod48l(BSTR str/*[in]*/, double* pVal/*[out]*/)
{
  GetDefaultInterface()->strtod48l(str/*[in]*/, pVal/*[out]*/);
}

void __fastcall TPmacDevice::strtod24(BSTR str/*[in]*/, double* pVal/*[out]*/)
{
  GetDefaultInterface()->strtod24(str/*[in]*/, pVal/*[out]*/);
}

void __fastcall TPmacDevice::strtod32dp(BSTR str/*[in]*/, double* pVal/*[out]*/)
{
  GetDefaultInterface()->strtod32dp(str/*[in]*/, pVal/*[out]*/);
}

void __fastcall TPmacDevice::strto32f(BSTR str/*[in]*/, double* pVal/*[out]*/)
{
  GetDefaultInterface()->strto32f(str/*[in]*/, pVal/*[out]*/);
}

void __fastcall TPmacDevice::UploadMacroConfig(long dwDevice/*[in]*/, BSTR bsFilePath/*[in]*/, 
                                               VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->UploadMacroConfig(dwDevice/*[in]*/, bsFilePath/*[in]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::DownloadCurrentFeedbackTest(long dwDevice/*[in]*/, short mtr/*[in]*/, 
                                                         double pwmDutyCycle/*[in]*/, 
                                                         short pwmFreq/*[in]*/, 
                                                         VARIANT_BOOL bMacro/*[in]*/, 
                                                         VARIANT_BOOL bUltra/*[in]*/, 
                                                         VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->DownloadCurrentFeedbackTest(dwDevice/*[in]*/, mtr/*[in]*/, 
                                                     pwmDutyCycle/*[in]*/, pwmFreq/*[in]*/, 
                                                     bMacro/*[in]*/, bUltra/*[in]*/, 
                                                     pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::ReadResultsFromCurrentFeedbackTest(long dwDevice/*[in]*/, 
                                                                short mtr/*[in]*/, 
                                                                long* pVal/*[out]*/)
{
  GetDefaultInterface()->ReadResultsFromCurrentFeedbackTest(dwDevice/*[in]*/, mtr/*[in]*/, 
                                                            pVal/*[out]*/);
}

void __fastcall TPmacDevice::DownloadVoltageSixStepTest(long dwDevice/*[in]*/, short mtr/*[in]*/, 
                                                        double pwmDutyCycle/*[in]*/, 
                                                        VARIANT_BOOL bMacro/*[in]*/, 
                                                        VARIANT_BOOL bUltra/*[in]*/, 
                                                        VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->DownloadVoltageSixStepTest(dwDevice/*[in]*/, mtr/*[in]*/, 
                                                    pwmDutyCycle/*[in]*/, bMacro/*[in]*/, 
                                                    bUltra/*[in]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::ReadResultsFromSixStepTest(long dwDevice/*[in]*/, 
                                                        VARIANT_BOOL bSipFirstStep/*[in]*/, 
                                                        VARIANT* pvStepArray/*[in,out]*/, 
                                                        long* pResult/*[out]*/)
{
  GetDefaultInterface()->ReadResultsFromSixStepTest(dwDevice/*[in]*/, bSipFirstStep/*[in]*/, 
                                                    pvStepArray/*[in,out]*/, pResult/*[out]*/);
}

void __fastcall TPmacDevice::DownloadCurrentSixStepTest(long dwDevice/*[in]*/, short motor/*[in]*/, 
                                                        double pwmDutyCycle/*[in]*/, 
                                                        VARIANT_BOOL bMacro/*[in]*/, 
                                                        VARIANT_BOOL bUltra/*[in]*/, 
                                                        VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->DownloadCurrentSixStepTest(dwDevice/*[in]*/, motor/*[in]*/, 
                                                    pwmDutyCycle/*[in]*/, bMacro/*[in]*/, 
                                                    bUltra/*[in]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::DownloadOpenLoopTest(long dwDevice/*[in]*/, short motor/*[in]*/, 
                                                  short magnitude/*[in]*/, short time/*[in]*/, 
                                                  short reps/*[in]*/, 
                                                  VARIANT_BOOL bGatherCurrents/*[in]*/, 
                                                  VARIANT_BOOL bMacro/*[in]*/, 
                                                  VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->DownloadOpenLoopTest(dwDevice/*[in]*/, motor/*[in]*/, magnitude/*[in]*/, 
                                              time/*[in]*/, reps/*[in]*/, bGatherCurrents/*[in]*/, 
                                              bMacro/*[in]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::DownloadOpenLoopTest1(long dwDevice/*[in]*/, short motor/*[in]*/, 
                                                   short magnitude/*[in]*/, short time/*[in]*/, 
                                                   short reps/*[in]*/, 
                                                   VARIANT_BOOL bGatherCurrents/*[in]*/, 
                                                   VARIANT_BOOL bMacro/*[in]*/, 
                                                   VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->DownloadOpenLoopTest1(dwDevice/*[in]*/, motor/*[in]*/, magnitude/*[in]*/, 
                                               time/*[in]*/, reps/*[in]*/, bGatherCurrents/*[in]*/, 
                                               bMacro/*[in]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::DownloadVelLimitPLC(long dwDevice/*[in]*/, short motor/*[in]*/, 
                                                 long maxspd/*[in]*/, 
                                                 VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->DownloadVelLimitPLC(dwDevice/*[in]*/, motor/*[in]*/, maxspd/*[in]*/, 
                                             pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::DownloadPosLimitPLC(long dwDevice/*[in]*/, short motor/*[in]*/, 
                                                 VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->DownloadPosLimitPLC(dwDevice/*[in]*/, motor/*[in]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::DownloadUVWSixStepTest(long dwDevice/*[in]*/, short motor/*[in]*/, 
                                                    double pwmDutyCycle/*[in]*/, 
                                                    VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->DownloadUVWSixStepTest(dwDevice/*[in]*/, motor/*[in]*/, 
                                                pwmDutyCycle/*[in]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::ReadResultsFromUVWSixStepTest(long dwDevice/*[in]*/, 
                                                           VARIANT* pvArray/*[in,out]*/, 
                                                           long* pResult/*[out]*/)
{
  GetDefaultInterface()->ReadResultsFromUVWSixStepTest(dwDevice/*[in]*/, pvArray/*[in,out]*/, 
                                                       pResult/*[out]*/);
}

void __fastcall TPmacDevice::SetIVarForFeedback(long dwDevice/*[in]*/, short ivar/*[in]*/, 
                                                long address/*[in]*/, 
                                                Pcommserverlib_tlb::DEVFEEDBACKTYPE fbType/*[in]*/, 
                                                VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->SetIVarForFeedback(dwDevice/*[in]*/, ivar/*[in]*/, address/*[in]*/, 
                                            fbType/*[in]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::DownloadAndRunRoughPhasePLC(long dwDevice/*[in]*/, short motor/*[in]*/, 
                                                         VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->DownloadAndRunRoughPhasePLC(dwDevice/*[in]*/, motor/*[in]*/, 
                                                     pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::CreateIncrementalFinePhasePLC(long dwDevice/*[in]*/, 
                                                           BSTR filePath/*[in]*/, 
                                                           short PLCNumber/*[in]*/, 
                                                           short motor/*[in]*/, 
                                                           VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->CreateIncrementalFinePhasePLC(dwDevice/*[in]*/, filePath/*[in]*/, 
                                                       PLCNumber/*[in]*/, motor/*[in]*/, 
                                                       pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::DoACurrentLoopStep(long dwDevice/*[in]*/, short motor/*[in]*/, 
                                                short dwellTime/*[in]*/, long magnitude/*[in]*/, 
                                                VARIANT_BOOL bAutoTune/*[in]*/, 
                                                BSTR* pbsCTSCurrent/*[out]*/, 
                                                double pwmDutyCycle/*[in]*/, short divisor/*[in]*/, 
                                                VARIANT_BOOL bUltra/*[in]*/)
{
  GetDefaultInterface()->DoACurrentLoopStep(dwDevice/*[in]*/, motor/*[in]*/, dwellTime/*[in]*/, 
                                            magnitude/*[in]*/, bAutoTune/*[in]*/, 
                                            pbsCTSCurrent/*[out]*/, pwmDutyCycle/*[in]*/, 
                                            divisor/*[in]*/, bUltra/*[in]*/);
}

void __fastcall TPmacDevice::DoACurrentLoopStepBrush(long dwDevice/*[in]*/, short motor/*[in]*/, 
                                                     short dwellTime/*[in]*/, long magnitude/*[in]*/, 
                                                     VARIANT_BOOL bAutoTune/*[in]*/, 
                                                     BSTR* pbsCTSCurrent/*[out]*/, 
                                                     double pwmDutyCycle/*[in]*/, 
                                                     short divisor/*[in]*/, 
                                                     VARIANT_BOOL bUltra/*[in]*/)
{
  GetDefaultInterface()->DoACurrentLoopStepBrush(dwDevice/*[in]*/, motor/*[in]*/, dwellTime/*[in]*/, 
                                                 magnitude/*[in]*/, bAutoTune/*[in]*/, 
                                                 pbsCTSCurrent/*[out]*/, pwmDutyCycle/*[in]*/, 
                                                 divisor/*[in]*/, bUltra/*[in]*/);
}

void __fastcall TPmacDevice::DoAPositionLoopStep(long dwDevice/*[in]*/, short motor/*[in]*/, 
                                                 short stepSize/*[in]*/, short stepTime/*[in]*/, 
                                                 VARIANT_BOOL bBiDirectional/*[in]*/, 
                                                 VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->DoAPositionLoopStep(dwDevice/*[in]*/, motor/*[in]*/, stepSize/*[in]*/, 
                                             stepTime/*[in]*/, bBiDirectional/*[in]*/, 
                                             pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::DoAParabolicMove(long dwDevice/*[in]*/, short motor/*[in]*/, 
                                              long stepSize/*[in]*/, short stepTime/*[in]*/, 
                                              VARIANT_BOOL bBiDirectional/*[in]*/, 
                                              VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->DoAParabolicMove(dwDevice/*[in]*/, motor/*[in]*/, stepSize/*[in]*/, 
                                          stepTime/*[in]*/, bBiDirectional/*[in]*/, 
                                          pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::DoAGantryPositionLoopStep(long dwDevice/*[in]*/, short motor/*[in]*/, 
                                                       short motor2/*[in]*/, short stepSize/*[in]*/, 
                                                       short stepTime/*[in]*/, 
                                                       VARIANT_BOOL bBiDirectional/*[in]*/, 
                                                       VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->DoAGantryPositionLoopStep(dwDevice/*[in]*/, motor/*[in]*/, motor2/*[in]*/, 
                                                   stepSize/*[in]*/, stepTime/*[in]*/, 
                                                   bBiDirectional/*[in]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::DoAGantryParabolicMove(long dwDevice/*[in]*/, short motor/*[in]*/, 
                                                    short motor2/*[in]*/, long stepSize/*[in]*/, 
                                                    short stepTime/*[in]*/, 
                                                    VARIANT_BOOL bBiDirectional/*[in]*/, 
                                                    VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->DoAGantryParabolicMove(dwDevice/*[in]*/, motor/*[in]*/, motor2/*[in]*/, 
                                                stepSize/*[in]*/, stepTime/*[in]*/, 
                                                bBiDirectional/*[in]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::DoAGantryParabolic(long dwDevice/*[in]*/, short motor/*[in]*/, 
                                                short motor2/*[in]*/, 
                                                VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->DoAGantryParabolic(dwDevice/*[in]*/, motor/*[in]*/, motor2/*[in]*/, 
                                            pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::ConvertWordToStringFloat(BSTR word/*[in]*/, BSTR* pVal/*[out]*/)
{
  GetDefaultInterface()->ConvertWordToStringFloat(word/*[in]*/, pVal/*[out]*/);
}

void __fastcall TPmacDevice::ConvertWordToShort(BSTR word/*[in]*/, short offset/*[in]*/, 
                                                short* pVal/*[out]*/)
{
  GetDefaultInterface()->ConvertWordToShort(word/*[in]*/, offset/*[in]*/, pVal/*[out]*/);
}

void __fastcall TPmacDevice::ConvertWordToLong(BSTR word/*[in]*/, long* pVal/*[out]*/)
{
  GetDefaultInterface()->ConvertWordToLong(word/*[in]*/, pVal/*[out]*/);
}

void __fastcall TPmacDevice::RestoreModifiedIVars(long dwDevice/*[in]*/, short motor/*[in]*/)
{
  GetDefaultInterface()->RestoreModifiedIVars(dwDevice/*[in]*/, motor/*[in]*/);
}

void __fastcall TPmacDevice::CalculateStepStatistics(VARIANT* pvData/*[in,out]*/, 
                                                     long stepSize/*[in]*/, long I10/*[in]*/, 
                                                     long I19/*[in]*/, BSTR* pbsRiseTime/*[out]*/, 
                                                     BSTR* pbsPeakTime/*[out]*/, 
                                                     BSTR* pbsNatFreq/*[out]*/, 
                                                     BSTR* pbsOvershoot/*[out]*/, 
                                                     BSTR* pbsDamping/*[out]*/, 
                                                     BSTR* pbsSettleTime/*[out]*/)
{
  GetDefaultInterface()->CalculateStepStatistics(pvData/*[in,out]*/, stepSize/*[in]*/, I10/*[in]*/, 
                                                 I19/*[in]*/, pbsRiseTime/*[out]*/, 
                                                 pbsPeakTime/*[out]*/, pbsNatFreq/*[out]*/, 
                                                 pbsOvershoot/*[out]*/, pbsDamping/*[out]*/, 
                                                 pbsSettleTime/*[out]*/);
}

void __fastcall TPmacDevice::LowPassFilterTheData(VARIANT* pvData/*[in,out]*/, 
                                                  BSTR bsCurrent/*[in]*/)
{
  GetDefaultInterface()->LowPassFilterTheData(pvData/*[in,out]*/, bsCurrent/*[in]*/);
}

void __fastcall TPmacDevice::DifferentiateTheData(VARIANT* pvData/*[in,out]*/, long I10/*[in]*/, 
                                                  long I19/*[in]*/, long* pMinVal/*[out]*/, 
                                                  long* pMaxVal/*[out]*/)
{
  GetDefaultInterface()->DifferentiateTheData(pvData/*[in,out]*/, I10/*[in]*/, I19/*[in]*/, 
                                              pMinVal/*[out]*/, pMaxVal/*[out]*/);
}

void __fastcall TPmacDevice::DownloadAutoTuningPLC(long dwDevice/*[in]*/, short motor/*[in]*/, 
                                                   VARIANT_BOOL bCurrentLoop/*[in]*/, 
                                                   VARIANT_BOOL bBypassJog/*[in]*/, 
                                                   VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->DownloadAutoTuningPLC(dwDevice/*[in]*/, motor/*[in]*/, bCurrentLoop/*[in]*/, 
                                               bBypassJog/*[in]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::DownloadGantryAutoTuningPLCP1(long dwDevice/*[in]*/, 
                                                           short motor/*[in]*/, short motor2/*[in]*/, 
                                                           VARIANT_BOOL bCurrentLoop/*[in]*/, 
                                                           VARIANT_BOOL bBypassJog/*[in]*/, 
                                                           VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->DownloadGantryAutoTuningPLCP1(dwDevice/*[in]*/, motor/*[in]*/, 
                                                       motor2/*[in]*/, bCurrentLoop/*[in]*/, 
                                                       bBypassJog/*[in]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::DownloadGantryAutoTuningPLC(long dwDevice/*[in]*/, short motor/*[in]*/, 
                                                         short motor2/*[in]*/, 
                                                         VARIANT_BOOL bCurrentLoop/*[in]*/, 
                                                         VARIANT_BOOL bBypassJog/*[in]*/, 
                                                         double MaxTravel/*[in]*/, long time/*[in]*/, 
                                                         VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->DownloadGantryAutoTuningPLC(dwDevice/*[in]*/, motor/*[in]*/, motor2/*[in]*/, 
                                                     bCurrentLoop/*[in]*/, bBypassJog/*[in]*/, 
                                                     MaxTravel/*[in]*/, time/*[in]*/, 
                                                     pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::MagEstimation(long dwDevice/*[in]*/, BSTR filePath/*[in]*/, 
                                           VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->MagEstimation(dwDevice/*[in]*/, filePath/*[in]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::SlopeEstimation(long dwDevice/*[in]*/, BSTR filePath/*[in]*/, 
                                             VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->SlopeEstimation(dwDevice/*[in]*/, filePath/*[in]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::SetCurrentGather(long dwDevice/*[in]*/, long mask/*[in]*/, 
                                              VARIANT_BOOL bEnable/*[in]*/, 
                                              VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->SetCurrentGather(dwDevice/*[in]*/, mask/*[in]*/, bEnable/*[in]*/, 
                                          pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::DownloadOpenLoopTestForPMAC1(long dwDevice/*[in]*/, short motor/*[in]*/, 
                                                          short magnitude/*[in]*/, 
                                                          short time/*[in]*/, short reps/*[in]*/, 
                                                          VARIANT_BOOL bGatherCurrents/*[in]*/, 
                                                          VARIANT_BOOL bMacro/*[in]*/, 
                                                          VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->DownloadOpenLoopTestForPMAC1(dwDevice/*[in]*/, motor/*[in]*/, 
                                                      magnitude/*[in]*/, time/*[in]*/, reps/*[in]*/, 
                                                      bGatherCurrents/*[in]*/, bMacro/*[in]*/, 
                                                      pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::GetMacroNodes(long dwDevice/*[in]*/, long* pNumMacroStations/*[out]*/, 
                                           long* pNumActiveNodes/*[out]*/)
{
  GetDefaultInterface()->GetMacroNodes(dwDevice/*[in]*/, pNumMacroStations/*[out]*/, 
                                       pNumActiveNodes/*[out]*/);
}

void __fastcall TPmacDevice::GetMacroNodeInfo(long dwDevice/*[in]*/, long modeNum/*[in]*/, 
                                              VARIANT_BOOL* pbEnabled/*[out]*/, 
                                              VARIANT_BOOL* pbIsIONode/*[out]*/, long* pID/*[out]*/)
{
  GetDefaultInterface()->GetMacroNodeInfo(dwDevice/*[in]*/, modeNum/*[in]*/, pbEnabled/*[out]*/, 
                                          pbIsIONode/*[out]*/, pID/*[out]*/);
}

void __fastcall TPmacDevice::SetMacroIVariableString(long dwDevice/*[in]*/, long node/*[in]*/, 
                                                     long num/*[in]*/, BSTR bsMIVarValue/*[in]*/, 
                                                     VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->SetMacroIVariableString(dwDevice/*[in]*/, node/*[in]*/, num/*[in]*/, 
                                                 bsMIVarValue/*[in]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::GetMacroIVariableString(long dwDevice/*[in]*/, long node/*[in]*/, 
                                                     long num/*[in]*/, BSTR bsDefault/*[in]*/, 
                                                     BSTR* pbsVal/*[out]*/)
{
  GetDefaultInterface()->GetMacroIVariableString(dwDevice/*[in]*/, node/*[in]*/, num/*[in]*/, 
                                                 bsDefault/*[in]*/, pbsVal/*[out]*/);
}

void __fastcall TPmacDevice::GetCommandLogging(long dwDevice/*[in]*/, VARIANT_BOOL* pbON/*[out]*/)
{
  GetDefaultInterface()->GetCommandLogging(dwDevice/*[in]*/, pbON/*[out]*/);
}

void __fastcall TPmacDevice::SetCommandLogging(long dwDevice/*[in]*/, VARIANT_BOOL bOn/*[in]*/, 
                                               BSTR bsFilePath/*[in]*/, 
                                               VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->SetCommandLogging(dwDevice/*[in]*/, bOn/*[in]*/, bsFilePath/*[in]*/, 
                                           pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::GetEnumeration(long dwDevice/*[in]*/, long* pVal/*[out]*/)
{
  GetDefaultInterface()->GetEnumeration(dwDevice/*[in]*/, pVal/*[out]*/);
}

void __fastcall TPmacDevice::GetControlValues(long dwDevice/*[in]*/, short ctrlCh/*[in]*/, 
                                              VARIANT* pVariant/*[in,out]*/, 
                                              VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->GetControlValues(dwDevice/*[in]*/, ctrlCh/*[in]*/, pVariant/*[in,out]*/, 
                                          pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::MultiDownload(long dwDevice/*[in]*/, BSTR outFile/*[in]*/, 
                                           BSTR iniFile/*[in]*/, BSTR userID/*[in]*/, 
                                           VARIANT_BOOL bMacro/*[in]*/, VARIANT_BOOL bMap/*[in]*/, 
                                           VARIANT_BOOL bLog/*[in]*/, VARIANT_BOOL bDnld/*[in]*/, 
                                           VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->MultiDownload(dwDevice/*[in]*/, outFile/*[in]*/, iniFile/*[in]*/, 
                                       userID/*[in]*/, bMacro/*[in]*/, bMap/*[in]*/, bLog/*[in]*/, 
                                       bDnld/*[in]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::AddDownloadFile(long dwDevice/*[in]*/, BSTR iniFile/*[in]*/, 
                                             BSTR userID/*[in]*/, BSTR dlFile/*[in]*/, 
                                             VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->AddDownloadFile(dwDevice/*[in]*/, iniFile/*[in]*/, userID/*[in]*/, 
                                         dlFile/*[in]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::RemoveDownloadFile(long dwDevice/*[in]*/, BSTR iniFile/*[in]*/, 
                                                BSTR userID/*[in]*/, BSTR dlFile/*[in]*/, 
                                                VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->RemoveDownloadFile(dwDevice/*[in]*/, iniFile/*[in]*/, userID/*[in]*/, 
                                            dlFile/*[in]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::RenumberFiles(long dwDevice/*[in]*/, long fileNumber/*[in]*/, 
                                           BSTR iniFile/*[in]*/)
{
  GetDefaultInterface()->RenumberFiles(dwDevice/*[in]*/, fileNumber/*[in]*/, iniFile/*[in]*/);
}

void __fastcall TPmacDevice::GetVariableStr(long dwDevice/*[in]*/, short ch/*[in]*/, 
                                            long num/*[in]*/, BSTR* pVal/*[out]*/, 
                                            VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->GetVariableStr(dwDevice/*[in]*/, ch/*[in]*/, num/*[in]*/, pVal/*[out]*/, 
                                        pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::DPRVarBufReadAll(long dwDevice/*[in]*/, long h/*[in]*/, 
                                              VARIANT* pVal/*[in,out]*/, 
                                              VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->DPRVarBufReadAll(dwDevice/*[in]*/, h/*[in]*/, pVal/*[in,out]*/, 
                                          pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::UltraLightAnalyze(long dwDevice/*[in]*/, VARIANT* pVal/*[in,out]*/, 
                                               long* pActiveNodes/*[out]*/)
{
  GetDefaultInterface()->UltraLightAnalyze(dwDevice/*[in]*/, pVal/*[in,out]*/, pActiveNodes/*[out]*/);
}

void __fastcall TPmacDevice::GetPlcStatusStructure(long dwDevice/*[in]*/, VARIANT* pVal/*[in,out]*/, 
                                                   long* pPrograms/*[out]*/)
{
  GetDefaultInterface()->GetPlcStatusStructure(dwDevice/*[in]*/, pVal/*[in,out]*/, 
                                               pPrograms/*[out]*/);
}

void __fastcall TPmacDevice::GetBitValue(BSTR hexStr/*[in]*/, short bit/*[in]*/, 
                                         VARIANT_BOOL* pVal/*[out]*/)
{
  GetDefaultInterface()->GetBitValue(hexStr/*[in]*/, bit/*[in]*/, pVal/*[out]*/);
}

void __fastcall TPmacDevice::GetNumDeviceKeys(long* pVal/*[out]*/)
{
  GetDefaultInterface()->GetNumDeviceKeys(pVal/*[out]*/);
}

void __fastcall TPmacDevice::DPRGetLongDouble(long dwDevice/*[in]*/, long address/*[in]*/, 
                                              double* pVal/*[out]*/, 
                                              VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->DPRGetLongDouble(dwDevice/*[in]*/, address/*[in]*/, pVal/*[out]*/, 
                                          pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::DPRGetFixedDouble(long dwDevice/*[in]*/, long address/*[in]*/, 
                                               double* pVal/*[out]*/, 
                                               VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->DPRGetFixedDouble(dwDevice/*[in]*/, address/*[in]*/, pVal/*[out]*/, 
                                           pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::DPRGetShort(long dwDevice/*[in]*/, long address/*[in]*/, 
                                         short* pVal/*[out]*/, VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->DPRGetShort(dwDevice/*[in]*/, address/*[in]*/, pVal/*[out]*/, 
                                     pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::DPRSetShort(long dwDevice/*[in]*/, long address/*[in]*/, 
                                         short newVal/*[in]*/, VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->DPRSetShort(dwDevice/*[in]*/, address/*[in]*/, newVal/*[in]*/, 
                                     pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::DPRDWordBitSet(long dwDevice/*[in]*/, long offset/*[in]*/, 
                                            long bit/*[in]*/, VARIANT_BOOL* pVal/*[out]*/, 
                                            VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->DPRDWordBitSet(dwDevice/*[in]*/, offset/*[in]*/, bit/*[in]*/, pVal/*[out]*/, 
                                        pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::DPRResetDWordBit(long dwDevice/*[in]*/, long offset/*[in]*/, 
                                              long bit/*[in]*/, VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->DPRResetDWordBit(dwDevice/*[in]*/, offset/*[in]*/, bit/*[in]*/, 
                                          pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::DPRSetDWordBit(long dwDevice/*[in]*/, long offset/*[in]*/, 
                                            long bit/*[in]*/, VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->DPRSetDWordBit(dwDevice/*[in]*/, offset/*[in]*/, bit/*[in]*/, 
                                        pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::GetFirmwareType(long dwDevice/*[in]*/, 
                                             Pcommserverlib_tlb::DEVPMACFIRMWARETYPE* pVal/*[out]*/)
{
  GetDefaultInterface()->GetFirmwareType(dwDevice/*[in]*/, pVal/*[out]*/);
}

void __fastcall TPmacDevice::GetResponseEx(long dwDevice/*[in]*/, BSTR question/*[in]*/, 
                                           VARIANT_BOOL bAddLF/*[in]*/, BSTR* pAnswer/*[out]*/, 
                                           long* pstatus/*[out]*/)
{
  GetDefaultInterface()->GetResponseEx(dwDevice/*[in]*/, question/*[in]*/, bAddLF/*[in]*/, 
                                       pAnswer/*[out]*/, pstatus/*[out]*/);
}

void __fastcall TPmacDevice::DPRVarBufWriteEx(long dwDevice/*[in]*/, VARIANT vData/*[in]*/, 
                                              long* pWritten/*[out]*/)
{
  GetDefaultInterface()->DPRVarBufWriteEx(dwDevice/*[in]*/, vData/*[in]*/, pWritten/*[out]*/);
}

void __fastcall TPmacDevice::DPRGetDWordMask(long dwDevice/*[in]*/, long offset/*[in]*/, 
                                             long mask/*[in]*/, long* pVal/*[out]*/)
{
  GetDefaultInterface()->DPRGetDWordMask(dwDevice/*[in]*/, offset/*[in]*/, mask/*[in]*/, 
                                         pVal/*[out]*/);
}

void __fastcall TPmacDevice::DPRSetDWordMask(long dwDevice/*[in]*/, long offset/*[in]*/, 
                                             long mask/*[in]*/, long Val/*[in]*/)
{
  GetDefaultInterface()->DPRSetDWordMask(dwDevice/*[in]*/, offset/*[in]*/, mask/*[in]*/, Val/*[in]*/);
}

void __fastcall TPmacDevice::DPRRotBufRemove(long dwDevice/*[in]*/, long bufnum/*[in]*/)
{
  GetDefaultInterface()->DPRRotBufRemove(dwDevice/*[in]*/, bufnum/*[in]*/);
}

void __fastcall TPmacDevice::DPRRotBufInit(long dwDevice/*[in]*/, VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->DPRRotBufInit(dwDevice/*[in]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::DPRRotBufClr(long dwDevice/*[in]*/, long bufnum/*[in]*/)
{
  GetDefaultInterface()->DPRRotBufClr(dwDevice/*[in]*/, bufnum/*[in]*/);
}

void __fastcall TPmacDevice::DPRSetRotBuf(long dwDevice/*[in]*/, VARIANT_BOOL on/*[in]*/)
{
  GetDefaultInterface()->DPRSetRotBuf(dwDevice/*[in]*/, on/*[in]*/);
}

void __fastcall TPmacDevice::DPRAsciiStrToRotEx(long dwDevice/*[in]*/, BSTR inpstr/*[in]*/, 
                                                long bufnum/*[in]*/, 
                                                VARIANT_BOOL bSendRemaining/*[in]*/, 
                                                long* pstatus/*[out]*/)
{
  GetDefaultInterface()->DPRAsciiStrToRotEx(dwDevice/*[in]*/, inpstr/*[in]*/, bufnum/*[in]*/, 
                                            bSendRemaining/*[in]*/, pstatus/*[out]*/);
}

void __fastcall TPmacDevice::DPRAsciiStrToRot(long dwDevice/*[in]*/, BSTR inpstr/*[in]*/, 
                                              long bufnum/*[in]*/, long* pstatus/*[out]*/)
{
  GetDefaultInterface()->DPRAsciiStrToRot(dwDevice/*[in]*/, inpstr/*[in]*/, bufnum/*[in]*/, 
                                          pstatus/*[out]*/);
}

void __fastcall TPmacDevice::GetProgramMode(long dwDevice/*[in]*/, long dwCoord/*[in]*/, 
                                            Pcommserverlib_tlb::DEVPROGRAMMODE* pVal/*[out]*/)
{
  GetDefaultInterface()->GetProgramMode(dwDevice/*[in]*/, dwCoord/*[in]*/, pVal/*[out]*/);
}

void __fastcall TPmacDevice::GetProgramMotionMode(long dwDevice/*[in]*/, long dwCoord/*[in]*/, 
                                                  Pcommserverlib_tlb::DEVMOTIONMODE* pVal/*[out]*/)
{
  GetDefaultInterface()->GetProgramMotionMode(dwDevice/*[in]*/, dwCoord/*[in]*/, pVal/*[out]*/);
}

void __fastcall TPmacDevice::MapDeviceNumToEnum(long location/*[in]*/, long enumeration/*[in]*/, 
                                                long* pDeviceNumber/*[out]*/)
{
  GetDefaultInterface()->MapDeviceNumToEnum(location/*[in]*/, enumeration/*[in]*/, 
                                            pDeviceNumber/*[out]*/);
}

void __fastcall TPmacDevice::MapLocAndEnumFromDeviceNum(long dwDevice/*[in]*/, 
                                                        long* pLocation/*[out]*/, 
                                                        long* pEnumeration/*[out]*/)
{
  GetDefaultInterface()->MapLocAndEnumFromDeviceNum(dwDevice/*[in]*/, pLocation/*[out]*/, 
                                                    pEnumeration/*[out]*/);
}

void __fastcall TPmacDevice::GetFeedRateAndMode(long dwDevice/*[in]*/, long dwCoord/*[in]*/, 
                                                double* pRate/*[out]*/, VARIANT_BOOL* pMode/*[out]*/)
{
  GetDefaultInterface()->GetFeedRateAndMode(dwDevice/*[in]*/, dwCoord/*[in]*/, pRate/*[out]*/, 
                                            pMode/*[out]*/);
}

void __fastcall TPmacDevice::GetMotorMotionMode(long dwDevice/*[in]*/, long dwMotor/*[in]*/, 
                                                Pcommserverlib_tlb::DEVMOTION* pVal/*[out]*/)
{
  GetDefaultInterface()->GetMotorMotionMode(dwDevice/*[in]*/, dwMotor/*[in]*/, pVal/*[out]*/);
}

void __fastcall TPmacDevice::CommandLog(long dwDevice/*[in]*/, BSTR bStr/*[in]*/, 
                                        VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->CommandLog(dwDevice/*[in]*/, bStr/*[in]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::DPRGetMem(long dwDevice/*[in]*/, long offset/*[in]*/, 
                                       long bytes/*[in]*/, VARIANT* pVal/*[in,out]*/, 
                                       VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->DPRGetMem(dwDevice/*[in]*/, offset/*[in]*/, bytes/*[in]*/, pVal/*[in,out]*/, 
                                   pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::DPRSetMem(long dwDevice/*[in]*/, long offset/*[in]*/, 
                                       long bytes/*[in]*/, VARIANT Val/*[in]*/, 
                                       VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->DPRSetMem(dwDevice/*[in]*/, offset/*[in]*/, bytes/*[in]*/, Val/*[in]*/, 
                                   pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::GetResponseProgress(long dwDevice/*[in]*/, BSTR question/*[in]*/, 
                                                 VARIANT_BOOL bAddLF/*[in]*/, BSTR* pAnswer/*[out]*/, 
                                                 long* pstatus/*[out]*/)
{
  GetDefaultInterface()->GetResponseProgress(dwDevice/*[in]*/, question/*[in]*/, bAddLF/*[in]*/, 
                                             pAnswer/*[out]*/, pstatus/*[out]*/);
}

void __fastcall TPmacDevice::Abort(long dwDevice/*[in]*/)
{
  GetDefaultInterface()->Abort(dwDevice/*[in]*/);
}

void __fastcall TPmacDevice::PmacSave(long dwDevice/*[in]*/, BSTR question/*[in]*/, 
                                      long* pstatus/*[out]*/)
{
  GetDefaultInterface()->PmacSave(dwDevice/*[in]*/, question/*[in]*/, pstatus/*[out]*/);
}

void __fastcall TPmacDevice::PmacReset(long dwDevice/*[in]*/, BSTR question/*[in]*/, 
                                       VARIANT_BOOL bAsciiRingComm/*[in]*/, long* pstatus/*[out]*/)
{
  GetDefaultInterface()->PmacReset(dwDevice/*[in]*/, question/*[in]*/, bAsciiRingComm/*[in]*/, 
                                   pstatus/*[out]*/);
}

void __fastcall TPmacDevice::PhaseMotor(long dwDevice/*[in]*/, BSTR question/*[in]*/, 
                                        long* pStatuss/*[out]*/)
{
  GetDefaultInterface()->PhaseMotor(dwDevice/*[in]*/, question/*[in]*/, pStatuss/*[out]*/);
}

void __fastcall TPmacDevice::GetControlResponseEx(long dwDevice/*[in]*/, short question/*[in]*/, 
                                                  BSTR* pAnswer/*[out]*/, long* pstatus/*[out]*/)
{
  GetDefaultInterface()->GetControlResponseEx(dwDevice/*[in]*/, question/*[in]*/, pAnswer/*[out]*/, 
                                              pstatus/*[out]*/);
}

void __fastcall TPmacDevice::DPRTest(long dwDevice/*[in]*/, VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->DPRTest(dwDevice/*[in]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::AbortTest(long dwDevice/*[in]*/)
{
  GetDefaultInterface()->AbortTest(dwDevice/*[in]*/);
}

void __fastcall TPmacDevice::DPRGetMotorRpt(long dwDevice/*[in]*/, long motor/*[in]*/, 
                                            Pcommserverlib_tlb::DEVFGMOTOR* pStruct/*[in,out]*/, 
                                            long* pServo/*[out]*/, VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->DPRGetMotorRpt(dwDevice/*[in]*/, motor/*[in]*/, pStruct/*[in,out]*/, 
                                        pServo/*[out]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::DPRGetMotorRptTurbo(long dwDevice/*[in]*/, long motor/*[in]*/, 
                                                 Pcommserverlib_tlb::DEVFGMOTORTURBO* pStruct/*[in,out]*/, 
                                                 long* pServo/*[out]*/, 
                                                 VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->DPRGetMotorRptTurbo(dwDevice/*[in]*/, motor/*[in]*/, pStruct/*[in,out]*/, 
                                             pServo/*[out]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::DPRGetCoordRpt(long dwDevice/*[in]*/, long coord/*[in]*/, 
                                            Pcommserverlib_tlb::DEVBGCOORD* pStruct/*[in,out]*/, 
                                            long* pServo/*[out]*/, VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->DPRGetCoordRpt(dwDevice/*[in]*/, coord/*[in]*/, pStruct/*[in,out]*/, 
                                        pServo/*[out]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::DPRGetCoordRptTurbo(long dwDevice/*[in]*/, long coord/*[in]*/, 
                                                 Pcommserverlib_tlb::DEVBGCOORDTURBO* pStruct/*[in,out]*/, 
                                                 long* pServo/*[out]*/, 
                                                 VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->DPRGetCoordRptTurbo(dwDevice/*[in]*/, coord/*[in]*/, pStruct/*[in,out]*/, 
                                             pServo/*[out]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::UltraLightAnalyzeStruct(long dwDevice/*[in]*/, 
                                                     Pcommserverlib_tlb::DEVULTRALIGHT_INFO* pStruct/*[in,out]*/, 
                                                     long* pActiveNodes/*[out]*/)
{
  GetDefaultInterface()->UltraLightAnalyzeStruct(dwDevice/*[in]*/, pStruct/*[in,out]*/, 
                                                 pActiveNodes/*[out]*/);
}

void __fastcall TPmacDevice::GetPlcStatusStruct(long dwDevice/*[in]*/, 
                                                Pcommserverlib_tlb::DEVTOTAL_PLC_STATUS_STRUCT* pStruct/*[in,out]*/, 
                                                long* pPrograms/*[out]*/)
{
  GetDefaultInterface()->GetPlcStatusStruct(dwDevice/*[in]*/, pStruct/*[in,out]*/, 
                                            pPrograms/*[out]*/);
}

TOLEBOOL __fastcall TPmacDevice::get_DPRTesting(long dwDevice/*[in]*/)
{
  return GetDefaultInterface()->get_DPRTesting(dwDevice/*[in]*/);
}

void __fastcall TPmacDevice::RawGetResponseEx(long dwDevice/*[in]*/, BSTR question/*[in]*/, 
                                              VARIANT_BOOL bAddLF/*[in]*/, BSTR* pAnswer/*[out]*/, 
                                              long* pstatus/*[out]*/)
{
  GetDefaultInterface()->RawGetResponseEx(dwDevice/*[in]*/, question/*[in]*/, bAddLF/*[in]*/, 
                                          pAnswer/*[out]*/, pstatus/*[out]*/);
}

void __fastcall TPmacDevice::RawGetControlResponseEx(long dwDevice/*[in]*/, short question/*[in]*/, 
                                                     BSTR* pAnswer/*[out]*/, long* pstatus/*[out]*/)
{
  GetDefaultInterface()->RawGetControlResponseEx(dwDevice/*[in]*/, question/*[in]*/, 
                                                 pAnswer/*[out]*/, pstatus/*[out]*/);
}

void __fastcall TPmacDevice::ModBusCommand(long dwDevice/*[in]*/, unsigned_char command/*[in]*/, 
                                           VARIANT* counters/*[out]*/, 
                                           VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->ModBusCommand(dwDevice/*[in]*/, command/*[in]*/, counters/*[out]*/, 
                                       pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::ModbusAvailable(long dwDevice/*[in]*/, unsigned_char command/*[in]*/, 
                                             VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->ModbusAvailable(dwDevice/*[in]*/, command/*[in]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::DPRSetupBuffers(unsigned_long dwDevice/*[in]*/, 
                                             VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->DPRSetupBuffers(dwDevice/*[in]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::DPRBackground(long dwDevice/*[in]*/, long on/*[in]*/, 
                                           long period/*[in]*/, long coord/*[in]*/, 
                                           VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->DPRBackground(dwDevice/*[in]*/, on/*[in]*/, period/*[in]*/, coord/*[in]*/, 
                                       pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::GetTurboMotorStatusEx(long dwDevice/*[in]*/, long lMotor/*[in]*/, 
                                                   Pcommserverlib_tlb::DEVMSTURBO* pstatus/*[in,out]*/, 
                                                   VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->GetTurboMotorStatusEx(dwDevice/*[in]*/, lMotor/*[in]*/, pstatus/*[in,out]*/, 
                                               pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::GetNTMotorStatusEx(long dwDevice/*[in]*/, long lMotor/*[in]*/, 
                                                Pcommserverlib_tlb::DEVMSNONTURBO* pstatus/*[in,out]*/, 
                                                VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->GetNTMotorStatusEx(dwDevice/*[in]*/, lMotor/*[in]*/, pstatus/*[in,out]*/, 
                                            pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::GetTurboGlobalStatusEx(long dwDevice/*[in]*/, 
                                                    Pcommserverlib_tlb::DEVGSTURBO* pstatus/*[in,out]*/, 
                                                    VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->GetTurboGlobalStatusEx(dwDevice/*[in]*/, pstatus/*[in,out]*/, 
                                                pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::GetNTGlobalStatusEx(long dwDevice/*[in]*/, 
                                                 Pcommserverlib_tlb::DEVGSNONTURBO* pstatus/*[in,out]*/, 
                                                 VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->GetNTGlobalStatusEx(dwDevice/*[in]*/, pstatus/*[in,out]*/, 
                                             pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::GetTurboCoordinateStatusEx(long dwDevice/*[in]*/, long dwCoord/*[in]*/, 
                                                        Pcommserverlib_tlb::DEVCSTURBO* pstatus/*[in,out]*/, 
                                                        VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->GetTurboCoordinateStatusEx(dwDevice/*[in]*/, dwCoord/*[in]*/, 
                                                    pstatus/*[in,out]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::GetNTCoordinateStatusEx(long dwDevice/*[in]*/, long dwCoord/*[in]*/, 
                                                     Pcommserverlib_tlb::DEVCSNONTURBO* pstatus/*[in,out]*/, 
                                                     VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->GetNTCoordinateStatusEx(dwDevice/*[in]*/, dwCoord/*[in]*/, 
                                                 pstatus/*[in,out]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::DataGather(long dwDevice/*[in]*/, LPSAFEARRAY* pvArray/*[in,out]*/, 
                                        VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->DataGather(dwDevice/*[in]*/, pvArray/*[in,out]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacDevice::Upload(long dwDevice/*[in]*/, 
                                    Pcommserverlib_tlb::DEVUPLOAD pUpload/*[in]*/, 
                                    BSTR* pData/*[out]*/, long* pstatus/*[out]*/)
{
  GetDefaultInterface()->Upload(dwDevice/*[in]*/, pUpload/*[in]*/, pData/*[out]*/, pstatus/*[out]*/);
}

void __fastcall TPmacDevice::ModbusActive(long dwDevice/*[in]*/, VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->ModbusActive(dwDevice/*[in]*/, pbSuccess/*[out]*/);
}

long __fastcall TPmacDevice::get_DPRSize(long dwDevice/*[in]*/)
{
  return GetDefaultInterface()->get_DPRSize(dwDevice/*[in]*/);
}

TOLEBOOL __fastcall TPmacDevice::get_DPRAvailable(long dwDevice/*[in]*/)
{
  return GetDefaultInterface()->get_DPRAvailable(dwDevice/*[in]*/);
}

long __fastcall TPmacDevice::get_LastCommError(long dwDevice/*[in]*/)
{
  return GetDefaultInterface()->get_LastCommError(dwDevice/*[in]*/);
}

TOLEBOOL __fastcall TPmacDevice::get_DoChecksums(long dwDevice/*[in]*/)
{
  return GetDefaultInterface()->get_DoChecksums(dwDevice/*[in]*/);
}

void __fastcall TPmacDevice::set_DoChecksums(long dwDevice/*[in]*/, VARIANT_BOOL pVal/*[in]*/)
{
  GetDefaultInterface()->set_DoChecksums(dwDevice/*[in]*/, pVal/*[in]*/);
}

TOLEBOOL __fastcall TPmacDevice::get_InBootStrapMode(long dwDevice/*[in]*/)
{
  return GetDefaultInterface()->get_InBootStrapMode(dwDevice/*[in]*/);
}

TOLEBOOL __fastcall TPmacDevice::get_MotionBufferOpen(long dwDevice/*[in]*/)
{
  return GetDefaultInterface()->get_MotionBufferOpen(dwDevice/*[in]*/);
}

TOLEBOOL __fastcall TPmacDevice::get_RotaryBufferOpen(long dwDevice/*[in]*/)
{
  return GetDefaultInterface()->get_RotaryBufferOpen(dwDevice/*[in]*/);
}

TOLEBOOL __fastcall TPmacDevice::get_IsTurbo(long dwDevice/*[in]*/)
{
  return GetDefaultInterface()->get_IsTurbo(dwDevice/*[in]*/);
}

TOLEBOOL __fastcall TPmacDevice::get_Downloading(long dwDevice/*[in]*/)
{
  return GetDefaultInterface()->get_Downloading(dwDevice/*[in]*/);
}

TOLEBOOL __fastcall TPmacDevice::get_IsAnyPlcRunning(long dwDevice/*[in]*/)
{
  return GetDefaultInterface()->get_IsAnyPlcRunning(dwDevice/*[in]*/);
}

TOLEBOOL __fastcall TPmacDevice::get_SysServoError(long dwDevice/*[in]*/)
{
  return GetDefaultInterface()->get_SysServoError(dwDevice/*[in]*/);
}

TOLEBOOL __fastcall TPmacDevice::get_SysReEntryError(long dwDevice/*[in]*/)
{
  return GetDefaultInterface()->get_SysReEntryError(dwDevice/*[in]*/);
}

TOLEBOOL __fastcall TPmacDevice::get_SysMemChecksumError(long dwDevice/*[in]*/)
{
  return GetDefaultInterface()->get_SysMemChecksumError(dwDevice/*[in]*/);
}

TOLEBOOL __fastcall TPmacDevice::get_SysPromChecksumError(long dwDevice/*[in]*/)
{
  return GetDefaultInterface()->get_SysPromChecksumError(dwDevice/*[in]*/);
}

TOLEBOOL __fastcall TPmacDevice::get_SysInposition(long dwDevice/*[in]*/, long dwCoord/*[in]*/)
{
  return GetDefaultInterface()->get_SysInposition(dwDevice/*[in]*/, dwCoord/*[in]*/);
}

TOLEBOOL __fastcall TPmacDevice::get_SysWarnFError(long dwDevice/*[in]*/, long dwCoord/*[in]*/)
{
  return GetDefaultInterface()->get_SysWarnFError(dwDevice/*[in]*/, dwCoord/*[in]*/);
}

TOLEBOOL __fastcall TPmacDevice::get_SysFatalFError(long dwDevice/*[in]*/, long dwCoord/*[in]*/)
{
  return GetDefaultInterface()->get_SysFatalFError(dwDevice/*[in]*/, dwCoord/*[in]*/);
}

TOLEBOOL __fastcall TPmacDevice::get_SysRuntimeError(long dwDevice/*[in]*/, long dwCoord/*[in]*/)
{
  return GetDefaultInterface()->get_SysRuntimeError(dwDevice/*[in]*/, dwCoord/*[in]*/);
}

TOLEBOOL __fastcall TPmacDevice::get_SysCircleRadError(long dwDevice/*[in]*/, long dwCoord/*[in]*/)
{
  return GetDefaultInterface()->get_SysCircleRadError(dwDevice/*[in]*/, dwCoord/*[in]*/);
}

TOLEBOOL __fastcall TPmacDevice::get_SysAmpFaultError(long dwDevice/*[in]*/, long dwCoord/*[in]*/)
{
  return GetDefaultInterface()->get_SysAmpFaultError(dwDevice/*[in]*/, dwCoord/*[in]*/);
}

TOLEBOOL __fastcall TPmacDevice::get_ProgramRunning(long dwDevice/*[in]*/, long dwCoord/*[in]*/)
{
  return GetDefaultInterface()->get_ProgramRunning(dwDevice/*[in]*/, dwCoord/*[in]*/);
}

TOLEBOOL __fastcall TPmacDevice::get_ProgramStepping(long dwDevice/*[in]*/, long dwCoord/*[in]*/)
{
  return GetDefaultInterface()->get_ProgramStepping(dwDevice/*[in]*/, dwCoord/*[in]*/);
}

TOLEBOOL __fastcall TPmacDevice::get_ProgramContMotion(long dwDevice/*[in]*/, long dwCoord/*[in]*/)
{
  return GetDefaultInterface()->get_ProgramContMotion(dwDevice/*[in]*/, dwCoord/*[in]*/);
}

TOLEBOOL __fastcall TPmacDevice::get_ProgramContRequest(long dwDevice/*[in]*/, long dwCoord/*[in]*/)
{
  return GetDefaultInterface()->get_ProgramContRequest(dwDevice/*[in]*/, dwCoord/*[in]*/);
}

long __fastcall TPmacDevice::get_ProgramRemaining(long dwDevice/*[in]*/, long dwCoord/*[in]*/)
{
  return GetDefaultInterface()->get_ProgramRemaining(dwDevice/*[in]*/, dwCoord/*[in]*/);
}

TOLEBOOL __fastcall TPmacDevice::get_MotionBufOpen(long dwDevice/*[in]*/)
{
  return GetDefaultInterface()->get_MotionBufOpen(dwDevice/*[in]*/);
}

TOLEBOOL __fastcall TPmacDevice::get_ProgramFeedMode(long dwDevice/*[in]*/, long dwCoord/*[in]*/)
{
  return GetDefaultInterface()->get_ProgramFeedMode(dwDevice/*[in]*/, dwCoord/*[in]*/);
}

TOLEBOOL __fastcall TPmacDevice::get_MotorAmpEnabled(long dwDevice/*[in]*/, long mtr/*[in]*/)
{
  return GetDefaultInterface()->get_MotorAmpEnabled(dwDevice/*[in]*/, mtr/*[in]*/);
}

TOLEBOOL __fastcall TPmacDevice::get_MotorWarnFError(long dwDevice/*[in]*/, long mtr/*[in]*/)
{
  return GetDefaultInterface()->get_MotorWarnFError(dwDevice/*[in]*/, mtr/*[in]*/);
}

TOLEBOOL __fastcall TPmacDevice::get_MotorFatalFError(long dwDevice/*[in]*/, long mtr/*[in]*/)
{
  return GetDefaultInterface()->get_MotorFatalFError(dwDevice/*[in]*/, mtr/*[in]*/);
}

TOLEBOOL __fastcall TPmacDevice::get_MotorAmpFault(long dwDevice/*[in]*/, long mtr/*[in]*/)
{
  return GetDefaultInterface()->get_MotorAmpFault(dwDevice/*[in]*/, mtr/*[in]*/);
}

TOLEBOOL __fastcall TPmacDevice::get_MotorOnPositionLimit(long dwDevice/*[in]*/, long mtr/*[in]*/)
{
  return GetDefaultInterface()->get_MotorOnPositionLimit(dwDevice/*[in]*/, mtr/*[in]*/);
}

TOLEBOOL __fastcall TPmacDevice::get_MotorHomeComplete(long dwDevice/*[in]*/, long mtr/*[in]*/)
{
  return GetDefaultInterface()->get_MotorHomeComplete(dwDevice/*[in]*/, mtr/*[in]*/);
}

TOLEBOOL __fastcall TPmacDevice::get_MotorInPosition(long dwDevice/*[in]*/, long mtr/*[in]*/)
{
  return GetDefaultInterface()->get_MotorInPosition(dwDevice/*[in]*/, mtr/*[in]*/);
}

long __fastcall TPmacDevice::get_TimRemInMove(long dwDevice/*[in]*/, long dwCoord/*[in]*/)
{
  return GetDefaultInterface()->get_TimRemInMove(dwDevice/*[in]*/, dwCoord/*[in]*/);
}

long __fastcall TPmacDevice::get_TimeRemInTATS(long dwDevice/*[in]*/, long dwCoord/*[in]*/)
{
  return GetDefaultInterface()->get_TimeRemInTATS(dwDevice/*[in]*/, dwCoord/*[in]*/);
}

TOLEBOOL __fastcall TPmacDevice::get_MotorDataBlockError(long dwDevice/*[in]*/, long mtr/*[in]*/)
{
  return GetDefaultInterface()->get_MotorDataBlockError(dwDevice/*[in]*/, mtr/*[in]*/);
}

TOLEBOOL __fastcall TPmacDevice::get_MotorPhased(long dwDevice/*[in]*/, long mtr/*[in]*/)
{
  return GetDefaultInterface()->get_MotorPhased(dwDevice/*[in]*/, mtr/*[in]*/);
}

TOLEBOOL __fastcall TPmacDevice::get_MotorEnabled(long dwDevice/*[in]*/, long mtr/*[in]*/)
{
  return GetDefaultInterface()->get_MotorEnabled(dwDevice/*[in]*/, mtr/*[in]*/);
}

TOLEBOOL __fastcall TPmacDevice::get_MotorHandwheelEnabled(long dwDevice/*[in]*/, long mtr/*[in]*/)
{
  return GetDefaultInterface()->get_MotorHandwheelEnabled(dwDevice/*[in]*/, mtr/*[in]*/);
}

TOLEBOOL __fastcall TPmacDevice::get_MotorOpenLoop(long dwDevice/*[in]*/, long mtr/*[in]*/)
{
  return GetDefaultInterface()->get_MotorOpenLoop(dwDevice/*[in]*/, mtr/*[in]*/);
}

TOLEBOOL __fastcall TPmacDevice::get_MotorOnNegLimit(long dwDevice/*[in]*/, long mtr/*[in]*/)
{
  return GetDefaultInterface()->get_MotorOnNegLimit(dwDevice/*[in]*/, mtr/*[in]*/);
}

TOLEBOOL __fastcall TPmacDevice::get_MotorOnPosLimit(long dwDevice/*[in]*/, long mtr/*[in]*/)
{
  return GetDefaultInterface()->get_MotorOnPosLimit(dwDevice/*[in]*/, mtr/*[in]*/);
}

TOLEBOOL __fastcall TPmacDevice::get_BufferOpen(long dwDevice/*[in]*/)
{
  return GetDefaultInterface()->get_BufferOpen(dwDevice/*[in]*/);
}

long __fastcall TPmacDevice::get_GatherPeriod(long dwDevice/*[in]*/)
{
  return GetDefaultInterface()->get_GatherPeriod(dwDevice/*[in]*/);
}

void __fastcall TPmacDevice::set_GatherPeriod(long dwDevice/*[in]*/, long pVal/*[in]*/)
{
  GetDefaultInterface()->set_GatherPeriod(dwDevice/*[in]*/, pVal/*[in]*/);
}

TOLEBOOL __fastcall TPmacDevice::get_GatherEnabled(long dwDevice/*[in]*/, long num/*[in]*/)
{
  return GetDefaultInterface()->get_GatherEnabled(dwDevice/*[in]*/, num/*[in]*/);
}

void __fastcall TPmacDevice::set_GatherEnabled(long dwDevice/*[in]*/, long num/*[in]*/, 
                                               VARIANT_BOOL pVal/*[in]*/)
{
  GetDefaultInterface()->set_GatherEnabled(dwDevice/*[in]*/, num/*[in]*/, pVal/*[in]*/);
}

Pcommserverlib_tlb::DEVGATMODE __fastcall TPmacDevice::get_GatherMode(long dwDevice/*[in]*/)
{
  return GetDefaultInterface()->get_GatherMode(dwDevice/*[in]*/);
}

void __fastcall TPmacDevice::set_GatherMode(long dwDevice/*[in]*/, 
                                            Pcommserverlib_tlb::DEVGATMODE pVal/*[in]*/)
{
  GetDefaultInterface()->set_GatherMode(dwDevice/*[in]*/, pVal/*[in]*/);
}

double __fastcall TPmacDevice::get_GatherSampleTime(long dwDevice/*[in]*/)
{
  return GetDefaultInterface()->get_GatherSampleTime(dwDevice/*[in]*/);
}

void __fastcall TPmacDevice::set_GatherSampleTime(long dwDevice/*[in]*/, double pVal/*[in]*/)
{
  GetDefaultInterface()->set_GatherSampleTime(dwDevice/*[in]*/, pVal/*[in]*/);
}

TOLEBOOL __fastcall TPmacDevice::get_InterruptsEnabled(long dwDevice/*[in]*/)
{
  return GetDefaultInterface()->get_InterruptsEnabled(dwDevice/*[in]*/);
}

void __fastcall TPmacDevice::set_InterruptsEnabled(long dwDevice/*[in]*/, VARIANT_BOOL pVal/*[in]*/)
{
  GetDefaultInterface()->set_InterruptsEnabled(dwDevice/*[in]*/, pVal/*[in]*/);
}

long __fastcall TPmacDevice::get_InterruptMask(long dwDevice/*[in]*/)
{
  return GetDefaultInterface()->get_InterruptMask(dwDevice/*[in]*/);
}

void __fastcall TPmacDevice::set_InterruptMask(long dwDevice/*[in]*/, long pVal/*[in]*/)
{
  GetDefaultInterface()->set_InterruptMask(dwDevice/*[in]*/, pVal/*[in]*/);
}

TOLEBOOL __fastcall TPmacDevice::get_USMonitoringEnabled(long dwDevice/*[in]*/)
{
  return GetDefaultInterface()->get_USMonitoringEnabled(dwDevice/*[in]*/);
}

void __fastcall TPmacDevice::set_USMonitoringEnabled(long dwDevice/*[in]*/, 
                                                     VARIANT_BOOL pVal/*[in]*/)
{
  GetDefaultInterface()->set_USMonitoringEnabled(dwDevice/*[in]*/, pVal/*[in]*/);
}

long __fastcall TPmacDevice::get_USMonitoringPeriod(long dwDevice/*[in]*/)
{
  return GetDefaultInterface()->get_USMonitoringPeriod(dwDevice/*[in]*/);
}

void __fastcall TPmacDevice::set_USMonitoringPeriod(long dwDevice/*[in]*/, long pVal/*[in]*/)
{
  GetDefaultInterface()->set_USMonitoringPeriod(dwDevice/*[in]*/, pVal/*[in]*/);
}

TOLEBOOL __fastcall TPmacDevice::get_DPRMotorRptEnabled(long dwDevice/*[in]*/)
{
  return GetDefaultInterface()->get_DPRMotorRptEnabled(dwDevice/*[in]*/);
}

void __fastcall TPmacDevice::set_DPRMotorRptEnabled(long dwDevice/*[in]*/, VARIANT_BOOL pVal/*[in]*/)
{
  GetDefaultInterface()->set_DPRMotorRptEnabled(dwDevice/*[in]*/, pVal/*[in]*/);
}

long __fastcall TPmacDevice::get_DPRMotorRptMask(long dwDevice/*[in]*/)
{
  return GetDefaultInterface()->get_DPRMotorRptMask(dwDevice/*[in]*/);
}

void __fastcall TPmacDevice::set_DPRMotorRptMask(long dwDevice/*[in]*/, long pVal/*[in]*/)
{
  GetDefaultInterface()->set_DPRMotorRptMask(dwDevice/*[in]*/, pVal/*[in]*/);
}

long __fastcall TPmacDevice::get_DPRMotorRptMSec(long dwDevice/*[in]*/)
{
  return GetDefaultInterface()->get_DPRMotorRptMSec(dwDevice/*[in]*/);
}

void __fastcall TPmacDevice::set_DPRMotorRptMSec(long dwDevice/*[in]*/, long pVal/*[in]*/)
{
  GetDefaultInterface()->set_DPRMotorRptMSec(dwDevice/*[in]*/, pVal/*[in]*/);
}

TOLEBOOL __fastcall TPmacDevice::get_DPRCoordRptEnabled(long dwDevice/*[in]*/)
{
  return GetDefaultInterface()->get_DPRCoordRptEnabled(dwDevice/*[in]*/);
}

void __fastcall TPmacDevice::set_DPRCoordRptEnabled(long dwDevice/*[in]*/, VARIANT_BOOL pVal/*[in]*/)
{
  GetDefaultInterface()->set_DPRCoordRptEnabled(dwDevice/*[in]*/, pVal/*[in]*/);
}

long __fastcall TPmacDevice::get_DPRCoordRptMSec(long dwDevice/*[in]*/)
{
  return GetDefaultInterface()->get_DPRCoordRptMSec(dwDevice/*[in]*/);
}

void __fastcall TPmacDevice::set_DPRCoordRptMSec(long dwDevice/*[in]*/, long pVal/*[in]*/)
{
  GetDefaultInterface()->set_DPRCoordRptMSec(dwDevice/*[in]*/, pVal/*[in]*/);
}

long __fastcall TPmacDevice::get_DPRCoordRptMax(long dwDevice/*[in]*/)
{
  return GetDefaultInterface()->get_DPRCoordRptMax(dwDevice/*[in]*/);
}

void __fastcall TPmacDevice::set_DPRCoordRptMax(long dwDevice/*[in]*/, long pVal/*[in]*/)
{
  GetDefaultInterface()->set_DPRCoordRptMax(dwDevice/*[in]*/, pVal/*[in]*/);
}

TOLEBOOL __fastcall TPmacDevice::get_DataCollectionEnabled(long dwDevice/*[in]*/)
{
  return GetDefaultInterface()->get_DataCollectionEnabled(dwDevice/*[in]*/);
}

long __fastcall TPmacDevice::get_DataCollectionResolution(long dwDevice/*[in]*/)
{
  return GetDefaultInterface()->get_DataCollectionResolution(dwDevice/*[in]*/);
}



// *********************************************************************//
// OCX PROXY CLASS IMPLEMENTATION
// (The following variables/methods implement the class TPmacNC which
// allows "PmacNC Class" to be hosted in CBuilder IDE/apps).
// *********************************************************************//
int   TPmacNC::EventDispIDs[8] = {
    0x00000001, 0x00000002, 0x00000003, 0x00000004, 0x00000005, 0x00000006,
    0x00000007, 0x00000008};

TControlData TPmacNC::CControlData =
{
  // GUID of CoClass and Event Interface of Control
  {0x450149A8, 0xE6B7, 0x4563,{ 0x80, 0x38, 0xFB,0xCA, 0xD0, 0x25,0xD0, 0x56} }, // CoClass
  {0x32C9ADDE, 0x9F29, 0x4658,{ 0x8E, 0xC3, 0xF1,0xB8, 0x39, 0x5F,0xE1, 0x9F} }, // Events

  // Count of Events and array of their DISPIDs
  8, &EventDispIDs,

  // Pointer to Runtime License string
  NULL,  // HRESULT(0x80004002)

  // Flags for OnChanged PropertyNotification
  0x00000000,
  300,// (IDE Version)

  // Count of Font Prop and array of their DISPIDs
  0, NULL,

  // Count of Pict Prop and array of their DISPIDs
  0, NULL,
  0, // Reserved
  0, // Instance count (used internally)
  0, // List of Enum descriptions (internal)
};

GUID     TPmacNC::DEF_CTL_INTF = {0x0A322163, 0xC2E1, 0x4152,{ 0xAD, 0xED, 0x91,0x74, 0x0A, 0xCE,0x75, 0x13} };
TNoParam TPmacNC::OptParam;

static inline void ValidCtrCheck(TPmacNC *)
{
   delete new TPmacNC((TComponent*)(0));
};

void __fastcall TPmacNC::InitControlData()
{
  ControlData = &CControlData;
};

void __fastcall TPmacNC::CreateControl()
{
  if (!m_OCXIntf)
  {
    _ASSERTE(DefaultDispatch);
    DefaultDispatch->QueryInterface(DEF_CTL_INTF, (LPVOID*)&m_OCXIntf);
  }
};

TCOMIPmacNC __fastcall TPmacNC::GetDefaultInterface()
{
  CreateControl();
  return m_OCXIntf;
};

void __fastcall TPmacNC::Open(long Device/*[in]*/, long Control/*[in]*/, 
                              VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->Open(Device/*[in]*/, Control/*[in]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacNC::Close(long Control/*[in]*/)
{
  GetDefaultInterface()->Close(Control/*[in]*/);
}

void __fastcall TPmacNC::OpenFile(long Control/*[in]*/, long dwCoord/*[in]*/, 
                                  BSTR szFilePath/*[in]*/, VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->OpenFile(Control/*[in]*/, dwCoord/*[in]*/, szFilePath/*[in]*/, 
                                  pbSuccess/*[out]*/);
}

void __fastcall TPmacNC::CloseFile(long Control/*[in]*/, long dwCoord/*[in]*/, 
                                   VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->CloseFile(Control/*[in]*/, dwCoord/*[in]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacNC::SetMachineMode(long Control/*[in]*/, 
                                        Pcommserverlib_tlb::NCMODE mode/*[in]*/)
{
  GetDefaultInterface()->SetMachineMode(Control/*[in]*/, mode/*[in]*/);
}

void __fastcall TPmacNC::GetMachineMode(long Control/*[in]*/, 
                                        Pcommserverlib_tlb::NCMODE* pMode/*[out]*/)
{
  GetDefaultInterface()->GetMachineMode(Control/*[in]*/, pMode/*[out]*/);
}

void __fastcall TPmacNC::GetRegistryBool(long Control/*[in]*/, BSTR section/*[in]*/, 
                                         BSTR name/*[in]*/, VARIANT_BOOL def/*[in]*/, 
                                         VARIANT_BOOL* pVal/*[out]*/, 
                                         VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->GetRegistryBool(Control/*[in]*/, section/*[in]*/, name/*[in]*/, def/*[in]*/, 
                                         pVal/*[out]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacNC::SetRegistryBool(long Control/*[in]*/, BSTR section/*[in]*/, 
                                         BSTR name/*[in]*/, VARIANT_BOOL bVal/*[in]*/, 
                                         VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->SetRegistryBool(Control/*[in]*/, section/*[in]*/, name/*[in]*/, 
                                         bVal/*[in]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacNC::GetRegistryLong(long Control/*[in]*/, BSTR section/*[in]*/, 
                                         BSTR name/*[in]*/, long def/*[in]*/, long* pVal/*[out]*/, 
                                         VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->GetRegistryLong(Control/*[in]*/, section/*[in]*/, name/*[in]*/, def/*[in]*/, 
                                         pVal/*[out]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacNC::SetRegistryLong(long Control/*[in]*/, BSTR section/*[in]*/, 
                                         BSTR name/*[in]*/, long lVal/*[in]*/, 
                                         VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->SetRegistryLong(Control/*[in]*/, section/*[in]*/, name/*[in]*/, 
                                         lVal/*[in]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacNC::GetRegistryString(long Control/*[in]*/, BSTR section/*[in]*/, 
                                           BSTR name/*[in]*/, BSTR def/*[in]*/, 
                                           BSTR* pVal/*[in,out]*/, VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->GetRegistryString(Control/*[in]*/, section/*[in]*/, name/*[in]*/, 
                                           def/*[in]*/, pVal/*[in,out]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacNC::SetRegistryString(long Control/*[in]*/, BSTR section/*[in]*/, 
                                           BSTR name/*[in]*/, BSTR Val/*[in]*/, 
                                           VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->SetRegistryString(Control/*[in]*/, section/*[in]*/, name/*[in]*/, 
                                           Val/*[in]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacNC::GetRegistryDouble(long Control/*[in]*/, BSTR section/*[in]*/, 
                                           BSTR name/*[in]*/, double def/*[in]*/, 
                                           double* pVal/*[out]*/, VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->GetRegistryDouble(Control/*[in]*/, section/*[in]*/, name/*[in]*/, 
                                           def/*[in]*/, pVal/*[out]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacNC::SetRegistryDouble(long Control/*[in]*/, BSTR section/*[in]*/, 
                                           BSTR name/*[in]*/, double Val/*[in]*/, 
                                           VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->SetRegistryDouble(Control/*[in]*/, section/*[in]*/, name/*[in]*/, 
                                           Val/*[in]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacNC::GetAxisEnabled(long Control/*[in]*/, long coord/*[in]*/, short axis/*[in]*/, 
                                        VARIANT_BOOL* pVal/*[out]*/)
{
  GetDefaultInterface()->GetAxisEnabled(Control/*[in]*/, coord/*[in]*/, axis/*[in]*/, pVal/*[out]*/);
}

void __fastcall TPmacNC::GetProgramName(long Control/*[in]*/, long coord/*[in]*/, 
                                        VARIANT_BOOL bMain/*[in]*/, BSTR* pVal/*[in,out]*/)
{
  GetDefaultInterface()->GetProgramName(Control/*[in]*/, coord/*[in]*/, bMain/*[in]*/, 
                                        pVal/*[in,out]*/);
}

void __fastcall TPmacNC::GetProgramPath(long Control/*[in]*/, long coord/*[in]*/, 
                                        VARIANT_BOOL bMain/*[in]*/, BSTR* pVal/*[in,out]*/)
{
  GetDefaultInterface()->GetProgramPath(Control/*[in]*/, coord/*[in]*/, bMain/*[in]*/, 
                                        pVal/*[in,out]*/);
}

void __fastcall TPmacNC::GetProgramStatus(long Control/*[in]*/, long coord/*[in]*/, 
                                          long* pProgID/*[out]*/, long* pNumLines/*[out]*/, 
                                          long* pLine/*[out]*/, long* pParseLine/*[out]*/, 
                                          long* pRepeat/*[out]*/, long* pCount/*[out]*/, 
                                          VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->GetProgramStatus(Control/*[in]*/, coord/*[in]*/, pProgID/*[out]*/, 
                                          pNumLines/*[out]*/, pLine/*[out]*/, pParseLine/*[out]*/, 
                                          pRepeat/*[out]*/, pCount/*[out]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacNC::GetProgramNumber(long Control/*[in]*/, long coord/*[in]*/, 
                                          long* pVal/*[out]*/)
{
  GetDefaultInterface()->GetProgramNumber(Control/*[in]*/, coord/*[in]*/, pVal/*[out]*/);
}

void __fastcall TPmacNC::GetCurrentLabel(long Control/*[in]*/, long coord/*[in]*/, 
                                         long* pVal/*[out]*/)
{
  GetDefaultInterface()->GetCurrentLabel(Control/*[in]*/, coord/*[in]*/, pVal/*[out]*/);
}

void __fastcall TPmacNC::GetJogStep(long Control/*[in]*/, long coord/*[in]*/, double* pVal/*[out]*/)
{
  GetDefaultInterface()->GetJogStep(Control/*[in]*/, coord/*[in]*/, pVal/*[out]*/);
}

void __fastcall TPmacNC::GetHandleStep(long Control/*[in]*/, long coord/*[in]*/, 
                                       double* pVal/*[out]*/)
{
  GetDefaultInterface()->GetHandleStep(Control/*[in]*/, coord/*[in]*/, pVal/*[out]*/);
}

void __fastcall TPmacNC::SetOrigin(long Control/*[in]*/, long coord/*[in]*/, 
                                   VARIANT_BOOL bOrginAll/*[in]*/, 
                                   Pcommserverlib_tlb::NCADDRESS adr/*[in]*/, 
                                   VARIANT_BOOL bClear/*[in]*/, double Val/*[in]*/, 
                                   VARIANT_BOOL metric/*[in]*/)
{
  GetDefaultInterface()->SetOrigin(Control/*[in]*/, coord/*[in]*/, bOrginAll/*[in]*/, adr/*[in]*/, 
                                   bClear/*[in]*/, Val/*[in]*/, metric/*[in]*/);
}

void __fastcall TPmacNC::ZeroShift(long Control/*[in]*/, long coord/*[in]*/, 
                                   VARIANT_BOOL bShiftAll/*[in]*/, 
                                   Pcommserverlib_tlb::NCADDRESS adr/*[in]*/, 
                                   VARIANT_BOOL bClear/*[in]*/, double Val/*[in]*/, 
                                   VARIANT_BOOL bMetric/*[in]*/)
{
  GetDefaultInterface()->ZeroShift(Control/*[in]*/, coord/*[in]*/, bShiftAll/*[in]*/, adr/*[in]*/, 
                                   bClear/*[in]*/, Val/*[in]*/, bMetric/*[in]*/);
}

void __fastcall TPmacNC::GetVectorVelocity(long Control/*[in]*/, long coord/*[in]*/, 
                                           double* pVal/*[out]*/)
{
  GetDefaultInterface()->GetVectorVelocity(Control/*[in]*/, coord/*[in]*/, pVal/*[out]*/);
}

void __fastcall TPmacNC::ReadMdiBuffer(long Control/*[in]*/, long coord/*[in]*/, long* hDlg/*[in]*/, 
                                       long idControl/*[in]*/)
{
  GetDefaultInterface()->ReadMdiBuffer(Control/*[in]*/, coord/*[in]*/, hDlg/*[in]*/, 
                                       idControl/*[in]*/);
}

void __fastcall TPmacNC::LoadMdiBuffer(long Control/*[in]*/, long coord/*[in]*/, long* hDlg/*[in]*/, 
                                       long idControl/*[in]*/, long nRepeat/*[in]*/)
{
  GetDefaultInterface()->LoadMdiBuffer(Control/*[in]*/, coord/*[in]*/, hDlg/*[in]*/, 
                                       idControl/*[in]*/, nRepeat/*[in]*/);
}

void __fastcall TPmacNC::ClearTextBuffer(long Control/*[in]*/, long coord/*[in]*/)
{
  GetDefaultInterface()->ClearTextBuffer(Control/*[in]*/, coord/*[in]*/);
}

void __fastcall TPmacNC::GetCurrentGValue(long Control/*[in]*/, long coord/*[in]*/, 
                                          long group/*[in]*/, long* pVal/*[out]*/)
{
  GetDefaultInterface()->GetCurrentGValue(Control/*[in]*/, coord/*[in]*/, group/*[in]*/, 
                                          pVal/*[out]*/);
}

void __fastcall TPmacNC::GetInposition(long Control/*[in]*/, long coord/*[in]*/, 
                                       VARIANT_BOOL* pVal/*[out]*/)
{
  GetDefaultInterface()->GetInposition(Control/*[in]*/, coord/*[in]*/, pVal/*[out]*/);
}

void __fastcall TPmacNC::GetProgramMode(long Control/*[in]*/, long coord/*[in]*/, 
                                        Pcommserverlib_tlb::DEVPROGRAMMODE* pVal/*[out]*/)
{
  GetDefaultInterface()->GetProgramMode(Control/*[in]*/, coord/*[in]*/, pVal/*[out]*/);
}

void __fastcall TPmacNC::GetSelectedBufferMode(long Control/*[in]*/, 
                                               Pcommserverlib_tlb::NCBUFFERMODE* pVal/*[out]*/)
{
  GetDefaultInterface()->GetSelectedBufferMode(Control/*[in]*/, pVal/*[out]*/);
}

void __fastcall TPmacNC::GetSelectedAxisMotionMode(long Control/*[in]*/, 
                                                   Pcommserverlib_tlb::DEVMOTIONMODE* pVal/*[out]*/)
{
  GetDefaultInterface()->GetSelectedAxisMotionMode(Control/*[in]*/, pVal/*[out]*/);
}

void __fastcall TPmacNC::GetProgramMotionMode(long Control/*[in]*/, long coord/*[in]*/, 
                                              Pcommserverlib_tlb::DEVMOTIONMODE* pVal/*[out]*/)
{
  GetDefaultInterface()->GetProgramMotionMode(Control/*[in]*/, coord/*[in]*/, pVal/*[out]*/);
}

void __fastcall TPmacNC::GetBufferOpen(long Control/*[in]*/, VARIANT_BOOL* pVal/*[out]*/)
{
  GetDefaultInterface()->GetBufferOpen(Control/*[in]*/, pVal/*[out]*/);
}

void __fastcall TPmacNC::GetBufferRemaining(long Control/*[in]*/, long coord/*[in]*/, 
                                            long* pRemain/*[out]*/, long* pParsed/*[out]*/)
{
  GetDefaultInterface()->GetBufferRemaining(Control/*[in]*/, coord/*[in]*/, pRemain/*[out]*/, 
                                            pParsed/*[out]*/);
}

void __fastcall TPmacNC::GetSpindleActRPM(long Control/*[in]*/, long* pVal/*[out]*/)
{
  GetDefaultInterface()->GetSpindleActRPM(Control/*[in]*/, pVal/*[out]*/);
}

void __fastcall TPmacNC::GetFeedrate(long Control/*[in]*/, long coord/*[in]*/, 
                                     Pcommserverlib_tlb::NCFEEDRATEMODE* pMode/*[out]*/, 
                                     double* pVal/*[out]*/)
{
  GetDefaultInterface()->GetFeedrate(Control/*[in]*/, coord/*[in]*/, pMode/*[out]*/, pVal/*[out]*/);
}

void __fastcall TPmacNC::SetFeedrate(long Control/*[in]*/, long coord/*[in]*/, 
                                     Pcommserverlib_tlb::NCFEEDRATEMODE mode/*[in]*/, 
                                     double newVal/*[in]*/)
{
  GetDefaultInterface()->SetFeedrate(Control/*[in]*/, coord/*[in]*/, mode/*[in]*/, newVal/*[in]*/);
}

void __fastcall TPmacNC::GetNumOfTools(long Control/*[in]*/, long coord/*[in]*/, long* pVal/*[out]*/)
{
  GetDefaultInterface()->GetNumOfTools(Control/*[in]*/, coord/*[in]*/, pVal/*[out]*/);
}

void __fastcall TPmacNC::SetToolHolderNumber(long Control/*[in]*/, long coord/*[in]*/, 
                                             long tool/*[in]*/, long holder/*[in]*/)
{
  GetDefaultInterface()->SetToolHolderNumber(Control/*[in]*/, coord/*[in]*/, tool/*[in]*/, 
                                             holder/*[in]*/);
}

void __fastcall TPmacNC::GetToolHolderNumber(long Control/*[in]*/, long coord/*[in]*/, 
                                             long tool/*[in]*/, long* pVal/*[out]*/)
{
  GetDefaultInterface()->GetToolHolderNumber(Control/*[in]*/, coord/*[in]*/, tool/*[in]*/, 
                                             pVal/*[out]*/);
}

void __fastcall TPmacNC::ZeroAllToolOffsets(long Control/*[in]*/, long coord/*[in]*/)
{
  GetDefaultInterface()->ZeroAllToolOffsets(Control/*[in]*/, coord/*[in]*/);
}

void __fastcall TPmacNC::GetTypeToolOffset(long Control/*[in]*/, long coord/*[in]*/, 
                                           long tool/*[in]*/, BSTR chAxis/*[in]*/, 
                                           Pcommserverlib_tlb::NCTOOLOFSTYPE type/*[in]*/, 
                                           VARIANT_BOOL bMetric/*[in]*/, double* pVal/*[out]*/)
{
  GetDefaultInterface()->GetTypeToolOffset(Control/*[in]*/, coord/*[in]*/, tool/*[in]*/, 
                                           chAxis/*[in]*/, type/*[in]*/, bMetric/*[in]*/, 
                                           pVal/*[out]*/);
}

void __fastcall TPmacNC::SetTypeToolOffset(long Control/*[in]*/, long coord/*[in]*/, 
                                           long tool/*[in]*/, BSTR chAxis/*[in]*/, 
                                           Pcommserverlib_tlb::NCTOOLOFSTYPE type/*[in]*/, 
                                           VARIANT_BOOL bMetric/*[in]*/, 
                                           VARIANT_BOOL bConfirm/*[in]*/, double newVal/*[in]*/, 
                                           VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->SetTypeToolOffset(Control/*[in]*/, coord/*[in]*/, tool/*[in]*/, 
                                           chAxis/*[in]*/, type/*[in]*/, bMetric/*[in]*/, 
                                           bConfirm/*[in]*/, newVal/*[in]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacNC::GetActiveGCode(long Control/*[in]*/, long coord/*[in]*/, long group/*[in]*/, 
                                        double* pVal/*[out]*/)
{
  GetDefaultInterface()->GetActiveGCode(Control/*[in]*/, coord/*[in]*/, group/*[in]*/, pVal/*[out]*/);
}

void __fastcall TPmacNC::GetActiveGCodeStr(long Control/*[in]*/, long coord/*[in]*/, 
                                           long group/*[in]*/, BSTR* pVal/*[in,out]*/)
{
  GetDefaultInterface()->GetActiveGCodeStr(Control/*[in]*/, coord/*[in]*/, group/*[in]*/, 
                                           pVal/*[in,out]*/);
}

void __fastcall TPmacNC::GetToolOffset(long Control/*[in]*/, long coord/*[in]*/, long* pVal/*[out]*/)
{
  GetDefaultInterface()->GetToolOffset(Control/*[in]*/, coord/*[in]*/, pVal/*[out]*/);
}

void __fastcall TPmacNC::GetCompOffset(long Control/*[in]*/, long coord/*[in]*/, long* pVal/*[out]*/)
{
  GetDefaultInterface()->GetCompOffset(Control/*[in]*/, coord/*[in]*/, pVal/*[out]*/);
}

void __fastcall TPmacNC::UpdateAllMotors(long Control/*[in]*/)
{
  GetDefaultInterface()->UpdateAllMotors(Control/*[in]*/);
}

void __fastcall TPmacNC::GetOperatingTime(long Control/*[in]*/, long* pDays/*[out]*/, 
                                          long* pHours/*[out]*/, long* pMinutes/*[out]*/, 
                                          long* pSeconds/*[out]*/)
{
  GetDefaultInterface()->GetOperatingTime(Control/*[in]*/, pDays/*[out]*/, pHours/*[out]*/, 
                                          pMinutes/*[out]*/, pSeconds/*[out]*/);
}

void __fastcall TPmacNC::GetTotalCuttingTime(long Control/*[in]*/, long* pDays/*[out]*/, 
                                             long* pHours/*[out]*/, long* pMinutes/*[out]*/, 
                                             long* pSeconds/*[out]*/)
{
  GetDefaultInterface()->GetTotalCuttingTime(Control/*[in]*/, pDays/*[out]*/, pHours/*[out]*/, 
                                             pMinutes/*[out]*/, pSeconds/*[out]*/);
}

void __fastcall TPmacNC::GetRunningTime(long Control/*[in]*/, long* pDays/*[out]*/, 
                                        long* pHours/*[out]*/, long* pMinutes/*[out]*/, 
                                        long* pSeconds/*[out]*/)
{
  GetDefaultInterface()->GetRunningTime(Control/*[in]*/, pDays/*[out]*/, pHours/*[out]*/, 
                                        pMinutes/*[out]*/, pSeconds/*[out]*/);
}

void __fastcall TPmacNC::GetPartTime(long Control/*[in]*/, long* pHours/*[out]*/, 
                                     long* pMinutes/*[out]*/, long* pSeconds/*[out]*/)
{
  GetDefaultInterface()->GetPartTime(Control/*[in]*/, pHours/*[out]*/, pMinutes/*[out]*/, 
                                     pSeconds/*[out]*/);
}

void __fastcall TPmacNC::GetCycleCuttingTime(long Control/*[in]*/, long* pHours/*[out]*/, 
                                             long* pMinutes/*[out]*/, long* pSeconds/*[out]*/)
{
  GetDefaultInterface()->GetCycleCuttingTime(Control/*[in]*/, pHours/*[out]*/, pMinutes/*[out]*/, 
                                             pSeconds/*[out]*/);
}

void __fastcall TPmacNC::GetCycleTime(long Control/*[in]*/, long* pHours/*[out]*/, 
                                      long* pMinutes/*[out]*/, long* Seconds/*[out]*/)
{
  GetDefaultInterface()->GetCycleTime(Control/*[in]*/, pHours/*[out]*/, pMinutes/*[out]*/, 
                                      Seconds/*[out]*/);
}

void __fastcall TPmacNC::GetNumDisplayedAxis(long Control/*[in]*/, long coord/*[in]*/, 
                                             long* pVal/*[out]*/)
{
  GetDefaultInterface()->GetNumDisplayedAxis(Control/*[in]*/, coord/*[in]*/, pVal/*[out]*/);
}

void __fastcall TPmacNC::GetNumDisplayAxisTotal(long Control/*[in]*/, long* pVal/*[out]*/)
{
  GetDefaultInterface()->GetNumDisplayAxisTotal(Control/*[in]*/, pVal/*[out]*/);
}

void __fastcall TPmacNC::GetMotorPosStr(long Control/*[in]*/, long coord/*[in]*/, long motor/*[in]*/, 
                                        Pcommserverlib_tlb::NCPOSTYPE t/*[in]*/, 
                                        VARIANT_BOOL bCombined/*[in]*/, BSTR* pAdr/*[in,out]*/, 
                                        BSTR* pPos/*[in,out]*/, VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->GetMotorPosStr(Control/*[in]*/, coord/*[in]*/, motor/*[in]*/, t/*[in]*/, 
                                        bCombined/*[in]*/, pAdr/*[in,out]*/, pPos/*[in,out]*/, 
                                        pbSuccess/*[out]*/);
}

void __fastcall TPmacNC::GetMotorUnitsStr(long Control/*[in]*/, long coord/*[in]*/, 
                                          long motor/*[in]*/, BSTR* pVal/*[in,out]*/, 
                                          VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->GetMotorUnitsStr(Control/*[in]*/, coord/*[in]*/, motor/*[in]*/, 
                                          pVal/*[in,out]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacNC::GetProgramLines(long Control/*[in]*/, long coord/*[in]*/, 
                                         long start/*[in]*/, long count/*[in]*/, 
                                         VARIANT* pVal/*[in,out]*/, VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->GetProgramLines(Control/*[in]*/, coord/*[in]*/, start/*[in]*/, 
                                         count/*[in]*/, pVal/*[in,out]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacNC::GetProgramLine(long Control/*[in]*/, long coord/*[in]*/, 
                                        long lineNumber/*[in]*/, BSTR* pVal/*[out]*/, 
                                        VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->GetProgramLine(Control/*[in]*/, coord/*[in]*/, lineNumber/*[in]*/, 
                                        pVal/*[out]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacNC::GetInputLong(long Control/*[in]*/, long num/*[in]*/, long* pVal/*[out]*/)
{
  GetDefaultInterface()->GetInputLong(Control/*[in]*/, num/*[in]*/, pVal/*[out]*/);
}

void __fastcall TPmacNC::GetOutputLong(long Control/*[in]*/, long num/*[in]*/, long* pVal/*[out]*/)
{
  GetDefaultInterface()->GetOutputLong(Control/*[in]*/, num/*[in]*/, pVal/*[out]*/);
}

void __fastcall TPmacNC::GetCommandLong(long Control/*[in]*/, long num/*[in]*/, long* pVal/*[out]*/)
{
  GetDefaultInterface()->GetCommandLong(Control/*[in]*/, num/*[in]*/, pVal/*[out]*/);
}

void __fastcall TPmacNC::GetStatusLong(long Control/*[in]*/, long num/*[in]*/, long* pVal/*[out]*/)
{
  GetDefaultInterface()->GetStatusLong(Control/*[in]*/, num/*[in]*/, pVal/*[out]*/);
}

void __fastcall TPmacNC::command(long Control/*[in]*/, long id/*[in]*/, long iv/*[in]*/, 
                                 double fv/*[in]*/, BSTR bStr/*[in]*/, 
                                 VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->command(Control/*[in]*/, id/*[in]*/, iv/*[in]*/, fv/*[in]*/, bStr/*[in]*/, 
                                 pbSuccess/*[out]*/);
}

void __fastcall TPmacNC::AddErrorRecord(long Control/*[in]*/, long errnum/*[in]*/, 
                                        Pcommserverlib_tlb::NCERRORMODE em/*[in]*/, 
                                        Pcommserverlib_tlb::NCERRORTYPE et/*[in]*/, 
                                        long Line/*[in]*/, short ax/*[in]*/, BSTR Msg/*[in]*/)
{
  GetDefaultInterface()->AddErrorRecord(Control/*[in]*/, errnum/*[in]*/, em/*[in]*/, et/*[in]*/, 
                                        Line/*[in]*/, ax/*[in]*/, Msg/*[in]*/);
}

void __fastcall TPmacNC::GetParametricDouble(long Control/*[in]*/, long coord/*[in]*/, 
                                             BSTR region/*[in]*/, long index/*[in]*/, 
                                             double* pVal/*[out]*/, VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->GetParametricDouble(Control/*[in]*/, coord/*[in]*/, region/*[in]*/, 
                                             index/*[in]*/, pVal/*[out]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacNC::SetParametricDouble(long Control/*[in]*/, long coord/*[in]*/, 
                                             BSTR region/*[in]*/, long index/*[in]*/, 
                                             double newVal/*[in]*/, VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->SetParametricDouble(Control/*[in]*/, coord/*[in]*/, region/*[in]*/, 
                                             index/*[in]*/, newVal/*[in]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacNC::GetSelectedAxisChar(long Control/*[in]*/, short* pAxChar/*[out]*/)
{
  GetDefaultInterface()->GetSelectedAxisChar(Control/*[in]*/, pAxChar/*[out]*/);
}

void __fastcall TPmacNC::GetAxisFormat(long Control/*[in]*/, long coord/*[in]*/, short ax/*[in]*/, 
                                       VARIANT_BOOL bMetric/*[in]*/, long* pLen/*[out]*/, 
                                       long* pDecPlaces/*[out]*/)
{
  GetDefaultInterface()->GetAxisFormat(Control/*[in]*/, coord/*[in]*/, ax/*[in]*/, bMetric/*[in]*/, 
                                       pLen/*[out]*/, pDecPlaces/*[out]*/);
}

void __fastcall TPmacNC::GetAxisFormatStr(long Control/*[in]*/, long coord/*[in]*/, short ax/*[in]*/, 
                                          VARIANT_BOOL bMetric/*[in]*/, BSTR* pVal/*[in,out]*/)
{
  GetDefaultInterface()->GetAxisFormatStr(Control/*[in]*/, coord/*[in]*/, ax/*[in]*/, 
                                          bMetric/*[in]*/, pVal/*[in,out]*/);
}

void __fastcall TPmacNC::SetAxisFormat(long Control/*[in]*/, long coord/*[in]*/, short ax/*[in]*/, 
                                       VARIANT_BOOL bMetric/*[in]*/, long len/*[in]*/, 
                                       long decPlaces/*[in]*/)
{
  GetDefaultInterface()->SetAxisFormat(Control/*[in]*/, coord/*[in]*/, ax/*[in]*/, bMetric/*[in]*/, 
                                       len/*[in]*/, decPlaces/*[in]*/);
}

void __fastcall TPmacNC::GetFirstError(long Control/*[in]*/, BSTR* pHeader/*[in,out]*/, 
                                       BSTR* pMessage/*[in,out]*/, BSTR* pCode/*[in,out]*/, 
                                       BSTR* pFilename/*[in,out]*/, long* pCount/*[out]*/, 
                                       long* pChanged/*[out]*/)
{
  GetDefaultInterface()->GetFirstError(Control/*[in]*/, pHeader/*[in,out]*/, pMessage/*[in,out]*/, 
                                       pCode/*[in,out]*/, pFilename/*[in,out]*/, pCount/*[out]*/, 
                                       pChanged/*[out]*/);
}

void __fastcall TPmacNC::GetNextError(long Control/*[in]*/, BSTR* pHeader/*[in,out]*/, 
                                      BSTR* pMessage/*[in,out]*/, BSTR* pCode/*[in,out]*/, 
                                      BSTR* pFilename/*[in,out]*/, VARIANT_BOOL* pbMore/*[out]*/)
{
  GetDefaultInterface()->GetNextError(Control/*[in]*/, pHeader/*[in,out]*/, pMessage/*[in,out]*/, 
                                      pCode/*[in,out]*/, pFilename/*[in,out]*/, pbMore/*[out]*/);
}

void __fastcall TPmacNC::OffsetsUpdateClear(long Control/*[in]*/, long clearMask/*[in]*/)
{
  GetDefaultInterface()->OffsetsUpdateClear(Control/*[in]*/, clearMask/*[in]*/);
}

void __fastcall TPmacNC::OffsetsUpdate(long Control/*[in]*/, long* pVal/*[out]*/)
{
  GetDefaultInterface()->OffsetsUpdate(Control/*[in]*/, pVal/*[out]*/);
}

void __fastcall TPmacNC::ReadErrorMsgBoxText(long Control/*[in]*/, long index/*[in]*/, 
                                             long* pCount/*[out]*/, BSTR* pText/*[in,out]*/, 
                                             BSTR* pTitle/*[in,out]*/)
{
  GetDefaultInterface()->ReadErrorMsgBoxText(Control/*[in]*/, index/*[in]*/, pCount/*[out]*/, 
                                             pText/*[in,out]*/, pTitle/*[in,out]*/);
}

void __fastcall TPmacNC::ResetMsgBoxError(long Control/*[in]*/, long errRetVal/*[in]*/)
{
  GetDefaultInterface()->ResetMsgBoxError(Control/*[in]*/, errRetVal/*[in]*/);
}

void __fastcall TPmacNC::SaveParametricVars(long Control/*[in]*/)
{
  GetDefaultInterface()->SaveParametricVars(Control/*[in]*/);
}

void __fastcall TPmacNC::LoadParametricVars(long Control/*[in]*/)
{
  GetDefaultInterface()->LoadParametricVars(Control/*[in]*/);
}

void __fastcall TPmacNC::ResetCycleTime(long Control/*[in]*/)
{
  GetDefaultInterface()->ResetCycleTime(Control/*[in]*/);
}

void __fastcall TPmacNC::GetToolGuageOffset(long Control/*[in]*/, long coord/*[in]*/, 
                                            long tool/*[in]*/, VARIANT_BOOL bMulti/*[in]*/, 
                                            short ax/*[in]*/, VARIANT_BOOL bMetric/*[in]*/, 
                                            double* pVal/*[out]*/)
{
  GetDefaultInterface()->GetToolGuageOffset(Control/*[in]*/, coord/*[in]*/, tool/*[in]*/, 
                                            bMulti/*[in]*/, ax/*[in]*/, bMetric/*[in]*/, 
                                            pVal/*[out]*/);
}

void __fastcall TPmacNC::SetToolGuageOffset(long Control/*[in]*/, long coord/*[in]*/, 
                                            long tool/*[in]*/, VARIANT_BOOL bMulti/*[in]*/, 
                                            short ax/*[in]*/, VARIANT_BOOL bMetric/*[in]*/, 
                                            double newVal/*[in]*/)
{
  GetDefaultInterface()->SetToolGuageOffset(Control/*[in]*/, coord/*[in]*/, tool/*[in]*/, 
                                            bMulti/*[in]*/, ax/*[in]*/, bMetric/*[in]*/, 
                                            newVal/*[in]*/);
}

void __fastcall TPmacNC::AutoSetToolOffset(long Control/*[in]*/, long coord/*[in]*/, 
                                           long tool/*[in]*/, short axis/*[in]*/)
{
  GetDefaultInterface()->AutoSetToolOffset(Control/*[in]*/, coord/*[in]*/, tool/*[in]*/, 
                                           axis/*[in]*/);
}

void __fastcall TPmacNC::GetOffsetValue(long Control/*[in]*/, long coord/*[in]*/, short axis/*[in]*/, 
                                        Pcommserverlib_tlb::NCCOORDTYPE t/*[in]*/, 
                                        VARIANT_BOOL bMetric/*[in]*/, double* pVal/*[out]*/)
{
  GetDefaultInterface()->GetOffsetValue(Control/*[in]*/, coord/*[in]*/, axis/*[in]*/, t/*[in]*/, 
                                        bMetric/*[in]*/, pVal/*[out]*/);
}

void __fastcall TPmacNC::SetOffsetValue(long Control/*[in]*/, long coord/*[in]*/, short axis/*[in]*/, 
                                        Pcommserverlib_tlb::NCCOORDTYPE t/*[in]*/, 
                                        VARIANT_BOOL bMetric/*[in]*/, VARIANT_BOOL bConfirm/*[in]*/, 
                                        double newVal/*[in]*/, VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->SetOffsetValue(Control/*[in]*/, coord/*[in]*/, axis/*[in]*/, t/*[in]*/, 
                                        bMetric/*[in]*/, bConfirm/*[in]*/, newVal/*[in]*/, 
                                        pbSuccess/*[out]*/);
}

void __fastcall TPmacNC::AutoSetWorkOffset(long Control/*[in]*/, long coord/*[in]*/, 
                                           short axis/*[in]*/, 
                                           Pcommserverlib_tlb::NCCOORDTYPE t/*[in]*/, 
                                           VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->AutoSetWorkOffset(Control/*[in]*/, coord/*[in]*/, axis/*[in]*/, t/*[in]*/, 
                                           pbSuccess/*[out]*/);
}

void __fastcall TPmacNC::SearchText(long Control/*[in]*/, long coord/*[in]*/, BSTR text/*[in]*/, 
                                    VARIANT_BOOL bMatchCase/*[in]*/, 
                                    VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->SearchText(Control/*[in]*/, coord/*[in]*/, text/*[in]*/, bMatchCase/*[in]*/, 
                                    pbSuccess/*[out]*/);
}

void __fastcall TPmacNC::SearchTextNext(long Control/*[in]*/, long coord/*[in]*/, BSTR text/*[in]*/, 
                                        VARIANT_BOOL bMatchCase/*[in]*/, 
                                        VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->SearchTextNext(Control/*[in]*/, coord/*[in]*/, text/*[in]*/, 
                                        bMatchCase/*[in]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacNC::GetBufferText(long Control/*[in]*/, long coord/*[in]*/, 
                                       VARIANT_BOOL bMDI/*[in]*/, BSTR* pVal/*[in,out]*/)
{
  GetDefaultInterface()->GetBufferText(Control/*[in]*/, coord/*[in]*/, bMDI/*[in]*/, 
                                       pVal/*[in,out]*/);
}

void __fastcall TPmacNC::SetBufferText(long Control/*[in]*/, long coord/*[in]*/, long repeat/*[in]*/, 
                                       VARIANT_BOOL bMDI/*[in]*/, BSTR newVal/*[in]*/)
{
  GetDefaultInterface()->SetBufferText(Control/*[in]*/, coord/*[in]*/, repeat/*[in]*/, bMDI/*[in]*/, 
                                       newVal/*[in]*/);
}

void __fastcall TPmacNC::GetProcessorClocks(double* pIO/*[out]*/, double* pLA/*[out]*/, 
                                            double* pParse/*[out]*/, double* pFormat/*[out]*/, 
                                            double* pWrite/*[out]*/)
{
  GetDefaultInterface()->GetProcessorClocks(pIO/*[out]*/, pLA/*[out]*/, pParse/*[out]*/, 
                                            pFormat/*[out]*/, pWrite/*[out]*/);
}

void __fastcall TPmacNC::GetMetricInput(long Control/*[in]*/, long coord/*[in]*/, 
                                        VARIANT_BOOL* pVal/*[out]*/)
{
  GetDefaultInterface()->GetMetricInput(Control/*[in]*/, coord/*[in]*/, pVal/*[out]*/);
}

void __fastcall TPmacNC::GetToolInfo(long Control/*[in]*/, long coord/*[in]*/, 
                                     long* pCurrentTool/*[out]*/, long* pNextTool/*[out]*/, 
                                     long* pHolder/*[out]*/, long* pHolderTool/*[out]*/)
{
  GetDefaultInterface()->GetToolInfo(Control/*[in]*/, coord/*[in]*/, pCurrentTool/*[out]*/, 
                                     pNextTool/*[out]*/, pHolder/*[out]*/, pHolderTool/*[out]*/);
}

void __fastcall TPmacNC::GetToolData(long Control/*[in]*/, long coord/*[in]*/, long tool/*[in]*/, 
                                     VARIANT* pVal/*[in,out]*/)
{
  GetDefaultInterface()->GetToolData(Control/*[in]*/, coord/*[in]*/, tool/*[in]*/, pVal/*[in,out]*/);
}

void __fastcall TPmacNC::ZeroAllTypeToolOffsets(long Control/*[in]*/, long coord/*[in]*/, 
                                                Pcommserverlib_tlb::NCTOOLOFSTYPE type/*[in]*/)
{
  GetDefaultInterface()->ZeroAllTypeToolOffsets(Control/*[in]*/, coord/*[in]*/, type/*[in]*/);
}

void __fastcall TPmacNC::SearchLine(long Control/*[in]*/, long coord/*[in]*/, long Line/*[in]*/, 
                                    VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->SearchLine(Control/*[in]*/, coord/*[in]*/, Line/*[in]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacNC::GetAxisMotor(long Control/*[in]*/, long coord/*[in]*/, short axis/*[in]*/, 
                                      long* pMotor/*[out]*/, VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->GetAxisMotor(Control/*[in]*/, coord/*[in]*/, axis/*[in]*/, pMotor/*[out]*/, 
                                      pbSuccess/*[out]*/);
}

void __fastcall TPmacNC::GetMotorAxis(long Control/*[in]*/, long coord/*[in]*/, long motor/*[in]*/, 
                                      short* pAxis/*[out]*/, VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->GetMotorAxis(Control/*[in]*/, coord/*[in]*/, motor/*[in]*/, pAxis/*[out]*/, 
                                      pbSuccess/*[out]*/);
}

void __fastcall TPmacNC::GetMotorPos(long Control/*[in]*/, long coord/*[in]*/, long motor/*[in]*/, 
                                     Pcommserverlib_tlb::NCPOSTYPE t/*[in]*/, BSTR* pAdr/*[out]*/, 
                                     double* pPos/*[out]*/, VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->GetMotorPos(Control/*[in]*/, coord/*[in]*/, motor/*[in]*/, t/*[in]*/, 
                                     pAdr/*[out]*/, pPos/*[out]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacNC::GetAllAxisPos(long Control/*[in]*/, long coord/*[in]*/, 
                                       Pcommserverlib_tlb::NCPOSTYPE t/*[in]*/, 
                                       LPSAFEARRAY* pvAdrArray/*[in,out]*/, 
                                       LPSAFEARRAY* pvPosArray/*[in,out]*/, 
                                       VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->GetAllAxisPos(Control/*[in]*/, coord/*[in]*/, t/*[in]*/, 
                                       pvAdrArray/*[in,out]*/, pvPosArray/*[in,out]*/, 
                                       pbSuccess/*[out]*/);
}

void __fastcall TPmacNC::GetAllAxisPosStr(long Control/*[in]*/, long coord/*[in]*/, 
                                          Pcommserverlib_tlb::NCPOSTYPE t/*[in]*/, 
                                          VARIANT_BOOL bCoord/*[in]*/, 
                                          LPSAFEARRAY* pvArray/*[in,out]*/, 
                                          VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->GetAllAxisPosStr(Control/*[in]*/, coord/*[in]*/, t/*[in]*/, bCoord/*[in]*/, 
                                          pvArray/*[in,out]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacNC::GetMaxFeedrates(long Control/*[in]*/, long coord/*[in]*/, 
                                         double* pMaxPerRev/*[out]*/, double* pMaxPerMinute/*[out]*/)
{
  GetDefaultInterface()->GetMaxFeedrates(Control/*[in]*/, coord/*[in]*/, pMaxPerRev/*[out]*/, 
                                         pMaxPerMinute/*[out]*/);
}

void __fastcall TPmacNC::SetMaxFeedrates(long Control/*[in]*/, long coord/*[in]*/, 
                                         double MaxPerRev/*[in]*/, double MaxPerMinute/*[in]*/)
{
  GetDefaultInterface()->SetMaxFeedrates(Control/*[in]*/, coord/*[in]*/, MaxPerRev/*[in]*/, 
                                         MaxPerMinute/*[in]*/);
}

void __fastcall TPmacNC::ClearOffsetValue(long Control/*[in]*/, long coord/*[in]*/, 
                                          short axis/*[in]*/, 
                                          Pcommserverlib_tlb::NCCOORDTYPE t/*[in]*/, 
                                          VARIANT_BOOL bMetric/*[in]*/, double newVal/*[in]*/, 
                                          VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->ClearOffsetValue(Control/*[in]*/, coord/*[in]*/, axis/*[in]*/, t/*[in]*/, 
                                          bMetric/*[in]*/, newVal/*[in]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacNC::GetToolDataStruct(long Control/*[in]*/, long coord/*[in]*/, 
                                           long tool/*[in]*/, 
                                           Pcommserverlib_tlb::NCTOOL* pStruct/*[in,out]*/)
{
  GetDefaultInterface()->GetToolDataStruct(Control/*[in]*/, coord/*[in]*/, tool/*[in]*/, 
                                           pStruct/*[in,out]*/);
}

void __fastcall TPmacNC::StartDataCollection(long Control/*[in]*/, long CollectionMSec/*[in]*/, 
                                             long BufferSize/*[in]*/, 
                                             VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->StartDataCollection(Control/*[in]*/, CollectionMSec/*[in]*/, 
                                             BufferSize/*[in]*/, pbSuccess/*[out]*/);
}

void __fastcall TPmacNC::StopDataCollection(long Control/*[in]*/)
{
  GetDefaultInterface()->StopDataCollection(Control/*[in]*/);
}

void __fastcall TPmacNC::DataCollect(long Control/*[in]*/, long coord/*[in]*/, 
                                     LPSAFEARRAY* pvArray/*[in,out]*/, 
                                     VARIANT_BOOL* pbSuccess/*[out]*/)
{
  GetDefaultInterface()->DataCollect(Control/*[in]*/, coord/*[in]*/, pvArray/*[in,out]*/, 
                                     pbSuccess/*[out]*/);
}

void __fastcall TPmacNC::ResetPartsCount(long Control/*[in]*/)
{
  GetDefaultInterface()->ResetPartsCount(Control/*[in]*/);
}

void __fastcall TPmacNC::ResetPartsTotal(long Control/*[in]*/)
{
  GetDefaultInterface()->ResetPartsTotal(Control/*[in]*/);
}

void __fastcall TPmacNC::GetWorkOffset(long Control/*[in]*/, long coord/*[in]*/, 
                                       Pcommserverlib_tlb::NCCOORDTYPE* t/*[out]*/, 
                                       long* pExtendedVal/*[out]*/)
{
  GetDefaultInterface()->GetWorkOffset(Control/*[in]*/, coord/*[in]*/, t/*[out]*/, 
                                       pExtendedVal/*[out]*/);
}

void __fastcall TPmacNC::GetLatheSetXDiameter(long Control/*[in]*/, long coord/*[in]*/, 
                                              VARIANT_BOOL bMetric/*[in]*/, double* pVal/*[out]*/)
{
  GetDefaultInterface()->GetLatheSetXDiameter(Control/*[in]*/, coord/*[in]*/, bMetric/*[in]*/, 
                                              pVal/*[out]*/);
}

void __fastcall TPmacNC::SetLatheSetXDiameter(long Control/*[in]*/, long coord/*[in]*/, 
                                              VARIANT_BOOL bMetric/*[in]*/, double newVal/*[in]*/)
{
  GetDefaultInterface()->SetLatheSetXDiameter(Control/*[in]*/, coord/*[in]*/, bMetric/*[in]*/, 
                                              newVal/*[in]*/);
}

BSTR __fastcall TPmacNC::get_Title(long Control/*[in]*/)
{
  return GetDefaultInterface()->get_Title(Control/*[in]*/);
}

void __fastcall TPmacNC::set_Title(long Control/*[in]*/, BSTR pVal/*[in]*/)
{
  GetDefaultInterface()->set_Title(Control/*[in]*/, pVal/*[in]*/);
}

long __fastcall TPmacNC::get_DeviceNumber(long Control/*[in]*/)
{
  return GetDefaultInterface()->get_DeviceNumber(Control/*[in]*/);
}

TOLEBOOL __fastcall TPmacNC::get_IsOpen(long Control/*[in]*/)
{
  return GetDefaultInterface()->get_IsOpen(Control/*[in]*/);
}

Pcommserverlib_tlb::NCMODE __fastcall TPmacNC::get_mode(long Control/*[in]*/)
{
  return GetDefaultInterface()->get_mode(Control/*[in]*/);
}

void __fastcall TPmacNC::set_mode(long Control/*[in]*/, Pcommserverlib_tlb::NCMODE pVal/*[in]*/)
{
  GetDefaultInterface()->set_mode(Control/*[in]*/, pVal/*[in]*/);
}

long __fastcall TPmacNC::get_CoordSystem(long Control/*[in]*/)
{
  return GetDefaultInterface()->get_CoordSystem(Control/*[in]*/);
}

void __fastcall TPmacNC::set_CoordSystem(long Control/*[in]*/, long pVal/*[in]*/)
{
  GetDefaultInterface()->set_CoordSystem(Control/*[in]*/, pVal/*[in]*/);
}

long __fastcall TPmacNC::get_NumCoordSystems(long Control/*[in]*/)
{
  return GetDefaultInterface()->get_NumCoordSystems(Control/*[in]*/);
}

TOLEBOOL __fastcall TPmacNC::get_SingleBlock(long Control/*[in]*/)
{
  return GetDefaultInterface()->get_SingleBlock(Control/*[in]*/);
}

void __fastcall TPmacNC::set_SingleBlock(long Control/*[in]*/, VARIANT_BOOL pVal/*[in]*/)
{
  GetDefaultInterface()->set_SingleBlock(Control/*[in]*/, pVal/*[in]*/);
}

TOLEBOOL __fastcall TPmacNC::get_BlockDelete(long Control/*[in]*/)
{
  return GetDefaultInterface()->get_BlockDelete(Control/*[in]*/);
}

void __fastcall TPmacNC::set_BlockDelete(long Control/*[in]*/, VARIANT_BOOL pVal/*[in]*/)
{
  GetDefaultInterface()->set_BlockDelete(Control/*[in]*/, pVal/*[in]*/);
}

TOLEBOOL __fastcall TPmacNC::get_OptionalStop(long Control/*[in]*/)
{
  return GetDefaultInterface()->get_OptionalStop(Control/*[in]*/);
}

void __fastcall TPmacNC::set_OptionalStop(long Control/*[in]*/, VARIANT_BOOL pVal/*[in]*/)
{
  GetDefaultInterface()->set_OptionalStop(Control/*[in]*/, pVal/*[in]*/);
}

TOLEBOOL __fastcall TPmacNC::get_MachineLock(long Control/*[in]*/)
{
  return GetDefaultInterface()->get_MachineLock(Control/*[in]*/);
}

void __fastcall TPmacNC::set_MachineLock(long Control/*[in]*/, VARIANT_BOOL pVal/*[in]*/)
{
  GetDefaultInterface()->set_MachineLock(Control/*[in]*/, pVal/*[in]*/);
}

TOLEBOOL __fastcall TPmacNC::get_DryRun(long Control/*[in]*/, long coord/*[in]*/)
{
  return GetDefaultInterface()->get_DryRun(Control/*[in]*/, coord/*[in]*/);
}

void __fastcall TPmacNC::set_DryRun(long Control/*[in]*/, long coord/*[in]*/, 
                                    VARIANT_BOOL pVal/*[in]*/)
{
  GetDefaultInterface()->set_DryRun(Control/*[in]*/, coord/*[in]*/, pVal/*[in]*/);
}

Pcommserverlib_tlb::NCMACHINETYPE __fastcall TPmacNC::get_MachineType(long Control/*[in]*/)
{
  return GetDefaultInterface()->get_MachineType(Control/*[in]*/);
}

Pcommserverlib_tlb::NCJOGSELECT __fastcall TPmacNC::get_JogSelect(long Control/*[in]*/)
{
  return GetDefaultInterface()->get_JogSelect(Control/*[in]*/);
}

void __fastcall TPmacNC::set_JogSelect(long Control/*[in]*/, 
                                       Pcommserverlib_tlb::NCJOGSELECT pVal/*[in]*/)
{
  GetDefaultInterface()->set_JogSelect(Control/*[in]*/, pVal/*[in]*/);
}

Pcommserverlib_tlb::NCSPEEDSELECT __fastcall TPmacNC::get_SpeedSelect(long Control/*[in]*/)
{
  return GetDefaultInterface()->get_SpeedSelect(Control/*[in]*/);
}

void __fastcall TPmacNC::set_SpeedSelect(long Control/*[in]*/, 
                                         Pcommserverlib_tlb::NCSPEEDSELECT pVal/*[in]*/)
{
  GetDefaultInterface()->set_SpeedSelect(Control/*[in]*/, pVal/*[in]*/);
}

TOLEBOOL __fastcall TPmacNC::get_ProgramLoaded(long Control/*[in]*/, long coord/*[in]*/)
{
  return GetDefaultInterface()->get_ProgramLoaded(Control/*[in]*/, coord/*[in]*/);
}

long __fastcall TPmacNC::get_Semaphore(long Control/*[in]*/, long coord/*[in]*/)
{
  return GetDefaultInterface()->get_Semaphore(Control/*[in]*/, coord/*[in]*/);
}

void __fastcall TPmacNC::set_Semaphore(long Control/*[in]*/, long coord/*[in]*/, long pVal/*[in]*/)
{
  GetDefaultInterface()->set_Semaphore(Control/*[in]*/, coord/*[in]*/, pVal/*[in]*/);
}

Pcommserverlib_tlb::NCSPEEDSELECT __fastcall TPmacNC::get_DistanceSelect(long Control/*[in]*/)
{
  return GetDefaultInterface()->get_DistanceSelect(Control/*[in]*/);
}

void __fastcall TPmacNC::set_DistanceSelect(long Control/*[in]*/, 
                                            Pcommserverlib_tlb::NCSPEEDSELECT pVal/*[in]*/)
{
  GetDefaultInterface()->set_DistanceSelect(Control/*[in]*/, pVal/*[in]*/);
}

Pcommserverlib_tlb::NCAXISSELECT __fastcall TPmacNC::get_AxisSelect(long Control/*[in]*/, 
                                                                    long coord/*[in]*/)
{
  return GetDefaultInterface()->get_AxisSelect(Control/*[in]*/, coord/*[in]*/);
}

void __fastcall TPmacNC::set_AxisSelect(long Control/*[in]*/, long coord/*[in]*/, 
                                        Pcommserverlib_tlb::NCAXISSELECT pVal/*[in]*/)
{
  GetDefaultInterface()->set_AxisSelect(Control/*[in]*/, coord/*[in]*/, pVal/*[in]*/);
}

Pcommserverlib_tlb::NCBUFFERMODE __fastcall TPmacNC::get_BufferMode(long Control/*[in]*/, 
                                                                    long coord/*[in]*/)
{
  return GetDefaultInterface()->get_BufferMode(Control/*[in]*/, coord/*[in]*/);
}

void __fastcall TPmacNC::set_BufferMode(long Control/*[in]*/, long coord/*[in]*/, 
                                        Pcommserverlib_tlb::NCBUFFERMODE pVal/*[in]*/)
{
  GetDefaultInterface()->set_BufferMode(Control/*[in]*/, coord/*[in]*/, pVal/*[in]*/);
}

Pcommserverlib_tlb::NCSPINDLESELECT __fastcall TPmacNC::get_SpindleSelect(long Control/*[in]*/)
{
  return GetDefaultInterface()->get_SpindleSelect(Control/*[in]*/);
}

void __fastcall TPmacNC::set_SpindleSelect(long Control/*[in]*/, 
                                           Pcommserverlib_tlb::NCSPINDLESELECT pVal/*[in]*/)
{
  GetDefaultInterface()->set_SpindleSelect(Control/*[in]*/, pVal/*[in]*/);
}

long __fastcall TPmacNC::get_SpindleRPM(long Control/*[in]*/)
{
  return GetDefaultInterface()->get_SpindleRPM(Control/*[in]*/);
}

void __fastcall TPmacNC::set_SpindleRPM(long Control/*[in]*/, long pVal/*[in]*/)
{
  GetDefaultInterface()->set_SpindleRPM(Control/*[in]*/, pVal/*[in]*/);
}

double __fastcall TPmacNC::get_SpindleCSS(long Control/*[in]*/)
{
  return GetDefaultInterface()->get_SpindleCSS(Control/*[in]*/);
}

void __fastcall TPmacNC::set_SpindleCSS(long Control/*[in]*/, double pVal/*[in]*/)
{
  GetDefaultInterface()->set_SpindleCSS(Control/*[in]*/, pVal/*[in]*/);
}

TOLEBOOL __fastcall TPmacNC::get_SpindleCSSMode(long Control/*[in]*/)
{
  return GetDefaultInterface()->get_SpindleCSSMode(Control/*[in]*/);
}

void __fastcall TPmacNC::set_SpindleCSSMode(long Control/*[in]*/, VARIANT_BOOL pVal/*[in]*/)
{
  GetDefaultInterface()->set_SpindleCSSMode(Control/*[in]*/, pVal/*[in]*/);
}

double __fastcall TPmacNC::get_SpindleCSSUnits(long Control/*[in]*/)
{
  return GetDefaultInterface()->get_SpindleCSSUnits(Control/*[in]*/);
}

void __fastcall TPmacNC::set_SpindleCSSUnits(long Control/*[in]*/, double pVal/*[in]*/)
{
  GetDefaultInterface()->set_SpindleCSSUnits(Control/*[in]*/, pVal/*[in]*/);
}

long __fastcall TPmacNC::get_SpindleMaxRPM(long Control/*[in]*/)
{
  return GetDefaultInterface()->get_SpindleMaxRPM(Control/*[in]*/);
}

void __fastcall TPmacNC::set_SpindleMaxRPM(long Control/*[in]*/, long pVal/*[in]*/)
{
  GetDefaultInterface()->set_SpindleMaxRPM(Control/*[in]*/, pVal/*[in]*/);
}

long __fastcall TPmacNC::get_SpindleOverride(long Control/*[in]*/, long coord/*[in]*/)
{
  return GetDefaultInterface()->get_SpindleOverride(Control/*[in]*/, coord/*[in]*/);
}

void __fastcall TPmacNC::set_SpindleOverride(long Control/*[in]*/, long coord/*[in]*/, 
                                             long pVal/*[in]*/)
{
  GetDefaultInterface()->set_SpindleOverride(Control/*[in]*/, coord/*[in]*/, pVal/*[in]*/);
}

double __fastcall TPmacNC::get_FeedrateOverride(long Control/*[in]*/, long coord/*[in]*/)
{
  return GetDefaultInterface()->get_FeedrateOverride(Control/*[in]*/, coord/*[in]*/);
}

void __fastcall TPmacNC::set_FeedrateOverride(long Control/*[in]*/, long coord/*[in]*/, 
                                              double pVal/*[in]*/)
{
  GetDefaultInterface()->set_FeedrateOverride(Control/*[in]*/, coord/*[in]*/, pVal/*[in]*/);
}

double __fastcall TPmacNC::get_RapidOverride(long Control/*[in]*/, long coord/*[in]*/)
{
  return GetDefaultInterface()->get_RapidOverride(Control/*[in]*/, coord/*[in]*/);
}

void __fastcall TPmacNC::set_RapidOverride(long Control/*[in]*/, long coord/*[in]*/, 
                                           double pVal/*[in]*/)
{
  GetDefaultInterface()->set_RapidOverride(Control/*[in]*/, coord/*[in]*/, pVal/*[in]*/);
}

Pcommserverlib_tlb::NCCLNTSELECT __fastcall TPmacNC::get_CoolantSelect(long Control/*[in]*/)
{
  return GetDefaultInterface()->get_CoolantSelect(Control/*[in]*/);
}

void __fastcall TPmacNC::set_CoolantSelect(long Control/*[in]*/, 
                                           Pcommserverlib_tlb::NCCLNTSELECT pVal/*[in]*/)
{
  GetDefaultInterface()->set_CoolantSelect(Control/*[in]*/, pVal/*[in]*/);
}

Pcommserverlib_tlb::NCTIMEBASEMODE __fastcall TPmacNC::get_TimebaseMode(long Control/*[in]*/, 
                                                                        long coord/*[in]*/)
{
  return GetDefaultInterface()->get_TimebaseMode(Control/*[in]*/, coord/*[in]*/);
}

void __fastcall TPmacNC::set_TimebaseMode(long Control/*[in]*/, long coord/*[in]*/, 
                                          Pcommserverlib_tlb::NCTIMEBASEMODE pVal/*[in]*/)
{
  GetDefaultInterface()->set_TimebaseMode(Control/*[in]*/, coord/*[in]*/, pVal/*[in]*/);
}

double __fastcall TPmacNC::get_ThreadLead(long Control/*[in]*/, long coord/*[in]*/)
{
  return GetDefaultInterface()->get_ThreadLead(Control/*[in]*/, coord/*[in]*/);
}

void __fastcall TPmacNC::set_ThreadLead(long Control/*[in]*/, long coord/*[in]*/, 
                                        double pVal/*[in]*/)
{
  GetDefaultInterface()->set_ThreadLead(Control/*[in]*/, coord/*[in]*/, pVal/*[in]*/);
}

long __fastcall TPmacNC::get_CurrentToolNumber(long Control/*[in]*/, long coord/*[in]*/)
{
  return GetDefaultInterface()->get_CurrentToolNumber(Control/*[in]*/, coord/*[in]*/);
}

void __fastcall TPmacNC::set_CurrentToolNumber(long Control/*[in]*/, long coord/*[in]*/, 
                                               long pVal/*[in]*/)
{
  GetDefaultInterface()->set_CurrentToolNumber(Control/*[in]*/, coord/*[in]*/, pVal/*[in]*/);
}

long __fastcall TPmacNC::get_NextToolNumber(long Control/*[in]*/, long coord/*[in]*/)
{
  return GetDefaultInterface()->get_NextToolNumber(Control/*[in]*/, coord/*[in]*/);
}

void __fastcall TPmacNC::set_NextToolNumber(long Control/*[in]*/, long coord/*[in]*/, 
                                            long pVal/*[in]*/)
{
  GetDefaultInterface()->set_NextToolNumber(Control/*[in]*/, coord/*[in]*/, pVal/*[in]*/);
}

long __fastcall TPmacNC::get_CurrentToolHolderNumber(long Control/*[in]*/, long coord/*[in]*/)
{
  return GetDefaultInterface()->get_CurrentToolHolderNumber(Control/*[in]*/, coord/*[in]*/);
}

void __fastcall TPmacNC::set_CurrentToolHolderNumber(long Control/*[in]*/, long coord/*[in]*/, 
                                                     long pVal/*[in]*/)
{
  GetDefaultInterface()->set_CurrentToolHolderNumber(Control/*[in]*/, coord/*[in]*/, pVal/*[in]*/);
}

long __fastcall TPmacNC::get_ToolInSpindle(long Control/*[in]*/, long coord/*[in]*/)
{
  return GetDefaultInterface()->get_ToolInSpindle(Control/*[in]*/, coord/*[in]*/);
}

void __fastcall TPmacNC::set_ToolInSpindle(long Control/*[in]*/, long coord/*[in]*/, 
                                           long pVal/*[in]*/)
{
  GetDefaultInterface()->set_ToolInSpindle(Control/*[in]*/, coord/*[in]*/, pVal/*[in]*/);
}

Pcommserverlib_tlb::NCTOOLDIRECTION __fastcall TPmacNC::get_ToolDirection(long Control/*[in]*/, 
                                                                          long coord/*[in]*/, 
                                                                          long tool/*[in]*/)
{
  return GetDefaultInterface()->get_ToolDirection(Control/*[in]*/, coord/*[in]*/, tool/*[in]*/);
}

void __fastcall TPmacNC::set_ToolDirection(long Control/*[in]*/, long coord/*[in]*/, 
                                           long tool/*[in]*/, 
                                           Pcommserverlib_tlb::NCTOOLDIRECTION pVal/*[in]*/)
{
  GetDefaultInterface()->set_ToolDirection(Control/*[in]*/, coord/*[in]*/, tool/*[in]*/, 
                                           pVal/*[in]*/);
}

double __fastcall TPmacNC::get_SpindleCountsPerRev(long Control/*[in]*/)
{
  return GetDefaultInterface()->get_SpindleCountsPerRev(Control/*[in]*/);
}

void __fastcall TPmacNC::set_SpindleCountsPerRev(long Control/*[in]*/, double pVal/*[in]*/)
{
  GetDefaultInterface()->set_SpindleCountsPerRev(Control/*[in]*/, pVal/*[in]*/);
}

double __fastcall TPmacNC::get_SpindleGearRatio(long Control/*[in]*/)
{
  return GetDefaultInterface()->get_SpindleGearRatio(Control/*[in]*/);
}

void __fastcall TPmacNC::set_SpindleGearRatio(long Control/*[in]*/, double pVal/*[in]*/)
{
  GetDefaultInterface()->set_SpindleGearRatio(Control/*[in]*/, pVal/*[in]*/);
}

TOLEBOOL __fastcall TPmacNC::get_SpindleDetect(long Control/*[in]*/)
{
  return GetDefaultInterface()->get_SpindleDetect(Control/*[in]*/);
}

void __fastcall TPmacNC::set_SpindleDetect(long Control/*[in]*/, VARIANT_BOOL pVal/*[in]*/)
{
  GetDefaultInterface()->set_SpindleDetect(Control/*[in]*/, pVal/*[in]*/);
}

TOLEBOOL __fastcall TPmacNC::get_SpindleAtSpeed(long Control/*[in]*/)
{
  return GetDefaultInterface()->get_SpindleAtSpeed(Control/*[in]*/);
}

void __fastcall TPmacNC::set_SpindleAtSpeed(long Control/*[in]*/, VARIANT_BOOL pVal/*[in]*/)
{
  GetDefaultInterface()->set_SpindleAtSpeed(Control/*[in]*/, pVal/*[in]*/);
}

TOLEBOOL __fastcall TPmacNC::get_SpindleAtZero(long Control/*[in]*/)
{
  return GetDefaultInterface()->get_SpindleAtZero(Control/*[in]*/);
}

void __fastcall TPmacNC::set_SpindleAtZero(long Control/*[in]*/, VARIANT_BOOL pVal/*[in]*/)
{
  GetDefaultInterface()->set_SpindleAtZero(Control/*[in]*/, pVal/*[in]*/);
}

TOLEBOOL __fastcall TPmacNC::get_SpindleFPR(long Control/*[in]*/)
{
  return GetDefaultInterface()->get_SpindleFPR(Control/*[in]*/);
}

void __fastcall TPmacNC::set_SpindleFPR(long Control/*[in]*/, VARIANT_BOOL pVal/*[in]*/)
{
  GetDefaultInterface()->set_SpindleFPR(Control/*[in]*/, pVal/*[in]*/);
}

TOLEBOOL __fastcall TPmacNC::get_HomeInit(long Control/*[in]*/)
{
  return GetDefaultInterface()->get_HomeInit(Control/*[in]*/);
}

void __fastcall TPmacNC::set_HomeInit(long Control/*[in]*/, VARIANT_BOOL pVal/*[in]*/)
{
  GetDefaultInterface()->set_HomeInit(Control/*[in]*/, pVal/*[in]*/);
}

long __fastcall TPmacNC::get_HomeMotorMask(long Control/*[in]*/)
{
  return GetDefaultInterface()->get_HomeMotorMask(Control/*[in]*/);
}

void __fastcall TPmacNC::set_HomeMotorMask(long Control/*[in]*/, long pVal/*[in]*/)
{
  GetDefaultInterface()->set_HomeMotorMask(Control/*[in]*/, pVal/*[in]*/);
}

long __fastcall TPmacNC::get_PartsRequired(long Control/*[in]*/)
{
  return GetDefaultInterface()->get_PartsRequired(Control/*[in]*/);
}

void __fastcall TPmacNC::set_PartsRequired(long Control/*[in]*/, long pVal/*[in]*/)
{
  GetDefaultInterface()->set_PartsRequired(Control/*[in]*/, pVal/*[in]*/);
}

long __fastcall TPmacNC::get_PartsCount(long Control/*[in]*/)
{
  return GetDefaultInterface()->get_PartsCount(Control/*[in]*/);
}

void __fastcall TPmacNC::set_PartsCount(long Control/*[in]*/, long pVal/*[in]*/)
{
  GetDefaultInterface()->set_PartsCount(Control/*[in]*/, pVal/*[in]*/);
}

long __fastcall TPmacNC::get_PartsTotal(long Control/*[in]*/)
{
  return GetDefaultInterface()->get_PartsTotal(Control/*[in]*/);
}

void __fastcall TPmacNC::set_PartsTotal(long Control/*[in]*/, long pVal/*[in]*/)
{
  GetDefaultInterface()->set_PartsTotal(Control/*[in]*/, pVal/*[in]*/);
}

TOLEBOOL __fastcall TPmacNC::get_IsSpindle(long Control/*[in]*/, long coord/*[in]*/, 
                                           long motor/*[in]*/)
{
  return GetDefaultInterface()->get_IsSpindle(Control/*[in]*/, coord/*[in]*/, motor/*[in]*/);
}

void __fastcall TPmacNC::set_IsSpindle(long Control/*[in]*/, long coord/*[in]*/, long motor/*[in]*/, 
                                       VARIANT_BOOL pVal/*[in]*/)
{
  GetDefaultInterface()->set_IsSpindle(Control/*[in]*/, coord/*[in]*/, motor/*[in]*/, pVal/*[in]*/);
}

TOLEBOOL __fastcall TPmacNC::get_IsDisplayed(long Control/*[in]*/, long coord/*[in]*/, 
                                             long motor/*[in]*/)
{
  return GetDefaultInterface()->get_IsDisplayed(Control/*[in]*/, coord/*[in]*/, motor/*[in]*/);
}

void __fastcall TPmacNC::set_IsDisplayed(long Control/*[in]*/, long coord/*[in]*/, 
                                         long motor/*[in]*/, VARIANT_BOOL pVal/*[in]*/)
{
  GetDefaultInterface()->set_IsDisplayed(Control/*[in]*/, coord/*[in]*/, motor/*[in]*/, pVal/*[in]*/);
}

TOLEBOOL __fastcall TPmacNC::get_HomeInProgress(long Control/*[in]*/)
{
  return GetDefaultInterface()->get_HomeInProgress(Control/*[in]*/);
}

long __fastcall TPmacNC::get_SpindleCmdRPM(long Control/*[in]*/)
{
  return GetDefaultInterface()->get_SpindleCmdRPM(Control/*[in]*/);
}

Pcommserverlib_tlb::NCERRORMODE __fastcall TPmacNC::get_CurrentErrorLevel(long Control/*[in]*/)
{
  return GetDefaultInterface()->get_CurrentErrorLevel(Control/*[in]*/);
}

void __fastcall TPmacNC::set_CurrentErrorLevel(long Control/*[in]*/, 
                                               Pcommserverlib_tlb::NCERRORMODE pVal/*[in]*/)
{
  GetDefaultInterface()->set_CurrentErrorLevel(Control/*[in]*/, pVal/*[in]*/);
}

long __fastcall TPmacNC::get_CurrentErrorCount(long Control/*[in]*/)
{
  return GetDefaultInterface()->get_CurrentErrorCount(Control/*[in]*/);
}

long __fastcall TPmacNC::get_BlocksPerSecond(long Control/*[in]*/, long coord/*[in]*/)
{
  return GetDefaultInterface()->get_BlocksPerSecond(Control/*[in]*/, coord/*[in]*/);
}

TOLEBOOL __fastcall TPmacNC::get_DataCollectionEnabled(long Control/*[in]*/)
{
  return GetDefaultInterface()->get_DataCollectionEnabled(Control/*[in]*/);
}

long __fastcall TPmacNC::get_DataCollectionResolution(long Control/*[in]*/)
{
  return GetDefaultInterface()->get_DataCollectionResolution(Control/*[in]*/);
}


};     // namespace Pcommserverlib_tlb


// *********************************************************************//
// The Register function is invoked by the IDE when this module is 
// installed in a Package. It provides the list of Components (including
// OCXes) implemented by this module. The following implementation
// informs the IDE of the OCX proxy classes implemented here.
// *********************************************************************//
namespace Pcommserverlib_ocx
{

void __fastcall PACKAGE Register()
{
  // [2]
  TComponentClass cls_ocx[] = {
                              __classid(Pcommserverlib_tlb::TPmacDevice), 
                              __classid(Pcommserverlib_tlb::TPmacNC)
                           };
  RegisterComponents("ActiveX", cls_ocx,
                     sizeof(cls_ocx)/sizeof(cls_ocx[0])-1);
}

};     // namespace Pcommserverlib_ocx
