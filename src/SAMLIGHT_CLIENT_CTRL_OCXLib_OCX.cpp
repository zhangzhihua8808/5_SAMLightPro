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
// File generated on 2016/8/12 11:42:18 from Type Library described below.

// ************************************************************************  //
// Type Lib: C:\Windows\system32\sc_x64_samlight_client_ctrl.ocx (1)
// LIBID: {22C1DCFD-1974-40FB-9193-1D299C09903C}
// LCID: 0
// Helpfile: C:\Windows\system32\samlight_client_ctrl_ocx.hlp
// HelpString: SCAPS SAM SamlightClientCtrl
// DepndLst: 
//   (1) v2.0 stdole, (C:\Windows\SysWOW64\stdole2.tlb)
// ************************************************************************ //

#include <vcl.h>
#pragma hdrstop

#include <olectrls.hpp>
#if defined(USING_ATL)
#include <atl\atlvcl.h>
#endif

#include "SAMLIGHT_CLIENT_CTRL_OCXLib_OCX.h"

#if !defined(__PRAGMA_PACKAGE_SMART_INIT)
#define      __PRAGMA_PACKAGE_SMART_INIT
#pragma package(smart_init)
#endif

namespace Samlight_client_ctrl_ocxlib_tlb
{



// *********************************************************************//
// OCX PROXY CLASS IMPLEMENTATION
// (The following variables/methods implement the class TScSamlightClientCtrl which
// allows "SCAPS SAM SamlightClientCtrl" to be hosted in CBuilder IDE/apps).
// *********************************************************************//
TControlData TScSamlightClientCtrl::CControlData =
{
  // GUID of CoClass and Event Interface of Control
  {0x5BBCB419, 0x0B12, 0x4F87,{ 0x85, 0xAF, 0xC0,0xB6, 0x6A, 0x73,0xDE, 0xCB} }, // CoClass
  {0x5F3246AD, 0x5086, 0x45E1,{ 0xA3, 0xDA, 0xCB,0x9B, 0x0B, 0xA2,0x34, 0xED} }, // Events

  // Count of Events and array of their DISPIDs
  0, NULL,

  // Pointer to Runtime License string
  NULL,  // HRESULT(0x80004005)

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

GUID     TScSamlightClientCtrl::DEF_CTL_INTF = {0x05D31AA6, 0x1306, 0x4DA0,{ 0x9A, 0xE2, 0xA8,0x77, 0x1F, 0xF6,0xFA, 0x94} };
TNoParam TScSamlightClientCtrl::OptParam;

static inline void ValidCtrCheck(TScSamlightClientCtrl *)
{
   delete new TScSamlightClientCtrl((TComponent*)(0));
};

void __fastcall TScSamlightClientCtrl::InitControlData()
{
  ControlData = &CControlData;
};

void __fastcall TScSamlightClientCtrl::CreateControl()
{
  if (!m_OCXIntf)
  {
    _ASSERTE(DefaultDispatch);
    DefaultDispatch->QueryInterface(DEF_CTL_INTF, (LPVOID*)&m_OCXIntf);
  }
};

_DSamlight_client_ctrl_ocxDisp __fastcall TScSamlightClientCtrl::GetDefaultInterface()
{
  CreateControl();
  return m_OCXIntf;
};

long __fastcall TScSamlightClientCtrl::ScIsRunning(void)
{
  return GetDefaultInterface()->ScIsRunning();
}

long __fastcall TScSamlightClientCtrl::ScExecCommand(long CmdID)
{
  return GetDefaultInterface()->ScExecCommand(CmdID);
}

long __fastcall TScSamlightClientCtrl::ScChangeTextByName(BSTR EntityName, BSTR Text)
{
  return GetDefaultInterface()->ScChangeTextByName(EntityName, Text);
}

long __fastcall TScSamlightClientCtrl::ScMarkEntityByName(BSTR EntityName, long WaitForMarkEnd)
{
  return GetDefaultInterface()->ScMarkEntityByName(EntityName, WaitForMarkEnd);
}

long __fastcall TScSamlightClientCtrl::ScIsMarking(void)
{
  return GetDefaultInterface()->ScIsMarking();
}

long __fastcall TScSamlightClientCtrl::ScStopMarking(void)
{
  return GetDefaultInterface()->ScStopMarking();
}

long __fastcall TScSamlightClientCtrl::ScLoadJob(BSTR FileName, long LoadEntities, 
                                                 long OverwriteEntities, long LoadMaterials)
{
  return GetDefaultInterface()->ScLoadJob(FileName, LoadEntities, OverwriteEntities, LoadMaterials);
}

double __fastcall TScSamlightClientCtrl::ScGetEntityOutline(BSTR EntityName, long Index)
{
  return GetDefaultInterface()->ScGetEntityOutline(EntityName, Index);
}

double __fastcall TScSamlightClientCtrl::ScGetWorkingArea(long Index)
{
  return GetDefaultInterface()->ScGetWorkingArea(Index);
}

long __fastcall TScSamlightClientCtrl::ScOpticMatrixReset(void)
{
  return GetDefaultInterface()->ScOpticMatrixReset();
}

long __fastcall TScSamlightClientCtrl::ScOpticMatrixTranslate(double X, double Y, double Z)
{
  return GetDefaultInterface()->ScOpticMatrixTranslate(X, Y, Z);
}

long __fastcall TScSamlightClientCtrl::ScOpticMatrixRotate(double CenterX, double CenterY, 
                                                           double Angle)
{
  return GetDefaultInterface()->ScOpticMatrixRotate(CenterX, CenterY, Angle);
}

long __fastcall TScSamlightClientCtrl::ScSetMarkFlags(long Flags)
{
  return GetDefaultInterface()->ScSetMarkFlags(Flags);
}

long __fastcall TScSamlightClientCtrl::ScGetMarkFlags(void)
{
  return GetDefaultInterface()->ScGetMarkFlags();
}

long __fastcall TScSamlightClientCtrl::ScOpenEthernetConnection(BSTR SenderAddr, long SenderPort, 
                                                                BSTR RecipientAddr, 
                                                                long RecipientPort)
{
  return GetDefaultInterface()->ScOpenEthernetConnection(SenderAddr, SenderPort, RecipientAddr, 
                                                         RecipientPort);
}

long __fastcall TScSamlightClientCtrl::ScCloseEthernetConnection(void)
{
  return GetDefaultInterface()->ScCloseEthernetConnection();
}

long __fastcall TScSamlightClientCtrl::ScGetInterfaceVersion(void)
{
  return GetDefaultInterface()->ScGetInterfaceVersion();
}

long __fastcall TScSamlightClientCtrl::ScSetDoubleValue(long Type, double Value)
{
  return GetDefaultInterface()->ScSetDoubleValue(Type, Value);
}

double __fastcall TScSamlightClientCtrl::ScGetDoubleValue(long Type)
{
  return GetDefaultInterface()->ScGetDoubleValue(Type);
}

long __fastcall TScSamlightClientCtrl::ScSetLongValue(long Type, long Value)
{
  return GetDefaultInterface()->ScSetLongValue(Type, Value);
}

long __fastcall TScSamlightClientCtrl::ScGetLongValue(long Type)
{
  return GetDefaultInterface()->ScGetLongValue(Type);
}

long __fastcall TScSamlightClientCtrl::ScSetLongData(long Type, VARIANT* Data, BSTR FileName)
{
  return GetDefaultInterface()->ScSetLongData(Type, Data, FileName);
}

long __fastcall TScSamlightClientCtrl::ScTranslateEntity(BSTR EntityName, double X, double Y, 
                                                         double Z)
{
  return GetDefaultInterface()->ScTranslateEntity(EntityName, X, Y, Z);
}

long __fastcall TScSamlightClientCtrl::ScScaleEntity(BSTR EntityName, double ScaleX, double ScaleY, 
                                                     double ScaleZ)
{
  return GetDefaultInterface()->ScScaleEntity(EntityName, ScaleX, ScaleY, ScaleZ);
}

long __fastcall TScSamlightClientCtrl::ScRotateEntity(BSTR EntityName, double X, double Y, 
                                                      double Angle)
{
  return GetDefaultInterface()->ScRotateEntity(EntityName, X, Y, Angle);
}

long __fastcall TScSamlightClientCtrl::ScImport(BSTR EntityName, BSTR FileName, BSTR Type, 
                                                double Resolution, long Flags)
{
  return GetDefaultInterface()->ScImport(EntityName, FileName, Type, Resolution, Flags);
}

long __fastcall TScSamlightClientCtrl::ScSetEntityLongData(BSTR EntityName, long DataId, long Data)
{
  return GetDefaultInterface()->ScSetEntityLongData(EntityName, DataId, Data);
}

long __fastcall TScSamlightClientCtrl::ScGetEntityLongData(BSTR EntityName, long DataId)
{
  return GetDefaultInterface()->ScGetEntityLongData(EntityName, DataId);
}

long __fastcall TScSamlightClientCtrl::ScDeleteEntity(BSTR EntityName)
{
  return GetDefaultInterface()->ScDeleteEntity(EntityName);
}

long __fastcall TScSamlightClientCtrl::ScGetLongData(long Type, VARIANT* Data, BSTR FileName)
{
  return GetDefaultInterface()->ScGetLongData(Type, Data, FileName);
}

long __fastcall TScSamlightClientCtrl::ScGetConnectionStatus(void)
{
  return GetDefaultInterface()->ScGetConnectionStatus();
}

long __fastcall TScSamlightClientCtrl::ScSetStringValue(long Type, BSTR Value)
{
  return GetDefaultInterface()->ScSetStringValue(Type, Value);
}

long __fastcall TScSamlightClientCtrl::ScGetStringValue(long Type, BSTR* Value)
{
  return GetDefaultInterface()->ScGetStringValue(Type, Value);
}

long __fastcall TScSamlightClientCtrl::ScShutDown(void)
{
  return GetDefaultInterface()->ScShutDown();
}

long __fastcall TScSamlightClientCtrl::ScGetOpticMatrix(long Index, double* Value)
{
  return GetDefaultInterface()->ScGetOpticMatrix(Index, Value);
}

long __fastcall TScSamlightClientCtrl::ScMoveAbs(double X, double Y, double Z)
{
  return GetDefaultInterface()->ScMoveAbs(X, Y, Z);
}

long __fastcall TScSamlightClientCtrl::ScSwitchLaser(long LaserOnOff)
{
  return GetDefaultInterface()->ScSwitchLaser(LaserOnOff);
}

long __fastcall TScSamlightClientCtrl::ScSetPen(long pen)
{
  return GetDefaultInterface()->ScSetPen(pen);
}

long __fastcall TScSamlightClientCtrl::ScGetPen(long* pen)
{
  return GetDefaultInterface()->ScGetPen(pen);
}

long __fastcall TScSamlightClientCtrl::ScShowApp(long Show)
{
  return GetDefaultInterface()->ScShowApp(Show);
}

long __fastcall TScSamlightClientCtrl::ScSetHead(long Head)
{
  return GetDefaultInterface()->ScSetHead(Head);
}

long __fastcall TScSamlightClientCtrl::ScGetHead(long* Head)
{
  return GetDefaultInterface()->ScGetHead(Head);
}

long __fastcall TScSamlightClientCtrl::ScSaveJob(BSTR FileName, long Flags)
{
  return GetDefaultInterface()->ScSaveJob(FileName, Flags);
}

long __fastcall TScSamlightClientCtrl::ScSetEntityDoubleData(BSTR EntityName, long DataId, 
                                                             double Data)
{
  return GetDefaultInterface()->ScSetEntityDoubleData(EntityName, DataId, Data);
}

long __fastcall TScSamlightClientCtrl::ScGetEntityDoubleData(BSTR EntityName, long DataId, 
                                                             double* Data)
{
  return GetDefaultInterface()->ScGetEntityDoubleData(EntityName, DataId, Data);
}

long __fastcall TScSamlightClientCtrl::ScSetEntityStringData(BSTR EntityName, long DataId, BSTR Data)
{
  return GetDefaultInterface()->ScSetEntityStringData(EntityName, DataId, Data);
}

long __fastcall TScSamlightClientCtrl::ScGetEntityStringData(BSTR EntityName, long DataId, 
                                                             BSTR* Data)
{
  return GetDefaultInterface()->ScGetEntityStringData(EntityName, DataId, Data);
}

long __fastcall TScSamlightClientCtrl::ScSetStringLongValue(long Type, BSTR SValue, long LValue)
{
  return GetDefaultInterface()->ScSetStringLongValue(Type, SValue, LValue);
}

long __fastcall TScSamlightClientCtrl::ScSetStringDblValue(long Type, BSTR SValue, double DValue)
{
  return GetDefaultInterface()->ScSetStringDblValue(Type, SValue, DValue);
}

long __fastcall TScSamlightClientCtrl::ScGetStringDblValue(long Type, BSTR SValue, double* RValue)
{
  return GetDefaultInterface()->ScGetStringDblValue(Type, SValue, RValue);
}

long __fastcall TScSamlightClientCtrl::ScGetIDStringData(long Type, long Index, BSTR* Data)
{
  return GetDefaultInterface()->ScGetIDStringData(Type, Index, Data);
}

long __fastcall TScSamlightClientCtrl::ScOpenTCPConnection(BSTR RecipientAddr, long RecipientPort)
{
  return GetDefaultInterface()->ScOpenTCPConnection(RecipientAddr, RecipientPort);
}

long __fastcall TScSamlightClientCtrl::ScOpenUDPConnection(BSTR SenderAddr, long SenderPort, 
                                                           BSTR RecipientAddr, long RecipientPort)
{
  return GetDefaultInterface()->ScOpenUDPConnection(SenderAddr, SenderPort, RecipientAddr, 
                                                    RecipientPort);
}

long __fastcall TScSamlightClientCtrl::ScOpticMatrixScale(double ScaleX, double ScaleY)
{
  return GetDefaultInterface()->ScOpticMatrixScale(ScaleX, ScaleY);
}

long __fastcall TScSamlightClientCtrl::ScSetPixelMapForPen(long pen, long pixel_zone0, 
                                                           long pixel_zone1, long pixel_zone2, 
                                                           long pixel_zone3, long pixel_zone4, 
                                                           long pixel_zone5)
{
  return GetDefaultInterface()->ScSetPixelMapForPen(pen, pixel_zone0, pixel_zone1, pixel_zone2, 
                                                    pixel_zone3, pixel_zone4, pixel_zone5);
}

long __fastcall TScSamlightClientCtrl::ScSetMode(long Mode)
{
  return GetDefaultInterface()->ScSetMode(Mode);
}

long __fastcall TScSamlightClientCtrl::ScGetMode(long* Mode)
{
  return GetDefaultInterface()->ScGetMode(Mode);
}

long __fastcall TScSamlightClientCtrl::ScDuplicateEntity(BSTR EntityName, BSTR DuplicatedEntityName)
{
  return GetDefaultInterface()->ScDuplicateEntity(EntityName, DuplicatedEntityName);
}

long __fastcall TScSamlightClientCtrl::ScProcessFlashJob(BSTR Name, long JobNum, long Mode, 
                                                         long Flags)
{
  return GetDefaultInterface()->ScProcessFlashJob(Name, JobNum, Mode, Flags);
}

BSTR __fastcall TScSamlightClientCtrl::ScFlashCommand(BSTR Command, long Flags, BSTR* Return)
{
  return GetDefaultInterface()->ScFlashCommand(Command, Flags, Return);
}

long __fastcall TScSamlightClientCtrl::ScSetIDStringData(long Type, long Index, BSTR Data)
{
  return GetDefaultInterface()->ScSetIDStringData(Type, Index, Data);
}

long __fastcall TScSamlightClientCtrl::ScExport(BSTR EntityName, BSTR FileName, BSTR Type, 
                                                double Resolution, long Flags)
{
  return GetDefaultInterface()->ScExport(EntityName, FileName, Type, Resolution, Flags);
}

long __fastcall TScSamlightClientCtrl::ScSlice(BSTR EntityName, BSTR LayerSolidName, 
                                               double sliceThickness, long doSliceOnlySelected, 
                                               long doReverseDirection)
{
  return GetDefaultInterface()->ScSlice(EntityName, LayerSolidName, sliceThickness, 
                                        doSliceOnlySelected, doReverseDirection);
}

long __fastcall TScSamlightClientCtrl::ScSetPenPathForPen(short* pen, short* enable, 
                                                          short* penToUse1, int* loopOfPenToUse1, 
                                                          short* penToUse2, int* loopOfPenToUse2, 
                                                          short* penToUse3, int* loopOfPenToUse3, 
                                                          short* penToUse4, int* loopOfPenToUse4, 
                                                          short* penToUse5, int* loopOfPenToUse5)
{
  return GetDefaultInterface()->ScSetPenPathForPen(pen, enable, penToUse1, loopOfPenToUse1, 
                                                   penToUse2, loopOfPenToUse2, penToUse3, 
                                                   loopOfPenToUse3, penToUse4, loopOfPenToUse4, 
                                                   penToUse5, loopOfPenToUse5);
}

long __fastcall TScSamlightClientCtrl::ScGetPenPathForPen(short* pen, short* enable, 
                                                          short* penToUse1, int* loopOfPenToUse1, 
                                                          short* penToUse2, int* loopOfPenToUse2, 
                                                          short* penToUse3, int* loopOfPenToUse3, 
                                                          short* penToUse4, int* loopOfPenToUse4, 
                                                          short* penToUse5, int* loopOfPenToUse5)
{
  return GetDefaultInterface()->ScGetPenPathForPen(pen, enable, penToUse1, loopOfPenToUse1, 
                                                   penToUse2, loopOfPenToUse2, penToUse3, 
                                                   loopOfPenToUse3, penToUse4, loopOfPenToUse4, 
                                                   penToUse5, loopOfPenToUse5);
}

long __fastcall TScSamlightClientCtrl::ScRotateEntity3D(BSTR EntityName, double px, double py, 
                                                        double pz, double vx, double vy, double vz, 
                                                        double Angle)
{
  return GetDefaultInterface()->ScRotateEntity3D(EntityName, px, py, pz, vx, vy, vz, Angle);
}

long __fastcall TScSamlightClientCtrl::ScGetEntityOutline2D(BSTR EntityName, double* MinX, 
                                                            double* MinY, double* MaxX, double* MaxY)
{
  return GetDefaultInterface()->ScGetEntityOutline2D(EntityName, MinX, MinY, MaxX, MaxY);
}

long __fastcall TScSamlightClientCtrl::ScGetEntityOutline3D(BSTR EntityName, double* MinX, 
                                                            double* MinY, double* MaxX, double* MaxY, 
                                                            double* MinZ, double* MaxZ)
{
  return GetDefaultInterface()->ScGetEntityOutline3D(EntityName, MinX, MinY, MaxX, MaxY, MinZ, MaxZ);
}



// *********************************************************************//
// OCX PROXY CLASS IMPLEMENTATION
// (The following variables/methods implement the class TScConnectionToolCtrl which
// allows "ScConnectionToolCtrl" to be hosted in CBuilder IDE/apps).
// *********************************************************************//
int   TScConnectionToolCtrl::EventDispIDs[1] = {
    0x000007D0};

TControlData TScConnectionToolCtrl::CControlData =
{
  // GUID of CoClass and Event Interface of Control
  {0x27B1C6DC, 0x6EBD, 0x44EA,{ 0x8A, 0x68, 0x27,0x5F, 0x9D, 0xDF,0xC8, 0xEE} }, // CoClass
  {0x9B5B5103, 0xC107, 0x4CD7,{ 0x9D, 0x58, 0xAA,0x11, 0x40, 0x80,0x37, 0xA3} }, // Events

  // Count of Events and array of their DISPIDs
  1, &EventDispIDs,

  // Pointer to Runtime License string
  NULL,  // HRESULT(0x80004005)

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

GUID     TScConnectionToolCtrl::DEF_CTL_INTF = {0x7EB1D711, 0x5F08, 0x4708,{ 0xB3, 0x7C, 0xBA,0x0E, 0xC0, 0xA7,0x2F, 0x65} };
TNoParam TScConnectionToolCtrl::OptParam;

static inline void ValidCtrCheck(TScConnectionToolCtrl *)
{
   delete new TScConnectionToolCtrl((TComponent*)(0));
};

void __fastcall TScConnectionToolCtrl::InitControlData()
{
  ControlData = &CControlData;
};

void __fastcall TScConnectionToolCtrl::CreateControl()
{
  if (!m_OCXIntf)
  {
    _ASSERTE(DefaultDispatch);
    DefaultDispatch->QueryInterface(DEF_CTL_INTF, (LPVOID*)&m_OCXIntf);
  }
};

TCOMSC_IConnectionToolCtrl __fastcall TScConnectionToolCtrl::GetDefaultInterface()
{
  CreateControl();
  return m_OCXIntf;
};

long __fastcall TScConnectionToolCtrl::ScInitWriteBuffer(void)
{
  return GetDefaultInterface()->ScInitWriteBuffer();
}

long __fastcall TScConnectionToolCtrl::ScInitReadBuffer(void)
{
  return GetDefaultInterface()->ScInitReadBuffer();
}

long __fastcall TScConnectionToolCtrl::ScOpenConnection(BSTR ListenName/*[in]*/, 
                                                        long ListenPort/*[in]*/, 
                                                        BSTR RecipientName/*[in]*/, 
                                                        long RecipientPort/*[in]*/)
{
  return GetDefaultInterface()->ScOpenConnection(ListenName/*[in]*/, ListenPort/*[in]*/, 
                                                 RecipientName/*[in]*/, RecipientPort/*[in]*/);
}

long __fastcall TScConnectionToolCtrl::ScAddString(BSTR Str/*[in]*/)
{
  return GetDefaultInterface()->ScAddString(Str/*[in]*/);
}

long __fastcall TScConnectionToolCtrl::ScAddLong(long Value/*[in]*/)
{
  return GetDefaultInterface()->ScAddLong(Value/*[in]*/);
}

long __fastcall TScConnectionToolCtrl::ScAddDouble(double Value/*[in]*/)
{
  return GetDefaultInterface()->ScAddDouble(Value/*[in]*/);
}

BSTR __fastcall TScConnectionToolCtrl::ScGetString(void)
{
  return GetDefaultInterface()->ScGetString();
}

long __fastcall TScConnectionToolCtrl::ScGetLong(void)
{
  return GetDefaultInterface()->ScGetLong();
}

double __fastcall TScConnectionToolCtrl::ScGetDouble(void)
{
  return GetDefaultInterface()->ScGetDouble();
}

long __fastcall TScConnectionToolCtrl::ScSend(void)
{
  return GetDefaultInterface()->ScSend();
}

long __fastcall TScConnectionToolCtrl::ScWaitForReceived(long TimeOut/*[in]*/)
{
  return GetDefaultInterface()->ScWaitForReceived(TimeOut/*[in]*/);
}

long __fastcall TScConnectionToolCtrl::ScGetLastResult(void)
{
  return GetDefaultInterface()->ScGetLastResult();
}

long __fastcall TScConnectionToolCtrl::ScCreateSocket(BSTR ListenName/*[in]*/, 
                                                      long ListenPort/*[in]*/)
{
  return GetDefaultInterface()->ScCreateSocket(ListenName/*[in]*/, ListenPort/*[in]*/);
}

long __fastcall TScConnectionToolCtrl::ScConnectTo(BSTR RecipientName/*[in]*/, 
                                                   long RecipientPort/*[in]*/)
{
  return GetDefaultInterface()->ScConnectTo(RecipientName/*[in]*/, RecipientPort/*[in]*/);
}

long __fastcall TScConnectionToolCtrl::ScClose(void)
{
  return GetDefaultInterface()->ScClose();
}

long __fastcall TScConnectionToolCtrl::ScGetLastError(void)
{
  return GetDefaultInterface()->ScGetLastError();
}


};     // namespace Samlight_client_ctrl_ocxlib_tlb


// *********************************************************************//
// The Register function is invoked by the IDE when this module is 
// installed in a Package. It provides the list of Components (including
// OCXes) implemented by this module. The following implementation
// informs the IDE of the OCX proxy classes implemented here.
// *********************************************************************//
namespace Samlight_client_ctrl_ocxlib_ocx
{

void __fastcall PACKAGE Register()
{
  // [2]
  TComponentClass cls_ocx[] = {
                              __classid(Samlight_client_ctrl_ocxlib_tlb::TScSamlightClientCtrl), 
                              __classid(Samlight_client_ctrl_ocxlib_tlb::TScConnectionToolCtrl)
                           };
  RegisterComponents("ActiveX", cls_ocx,
                     sizeof(cls_ocx)/sizeof(cls_ocx[0])-1);
}

};     // namespace Samlight_client_ctrl_ocxlib_ocx
