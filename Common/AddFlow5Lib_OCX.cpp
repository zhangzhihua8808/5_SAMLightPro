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
// File generated on 2007-11-8 17:33:07 from Type Library described below.

// ************************************************************************  //
// Type Lib: C:\Program Files\Lassalle Technologies\AddFlow 5\AddFlow5.ocx (1)
// LIBID: {DE173711-6CFE-432E-A95E-F4EF3EE03231}
// LCID: 0
// Helpfile: C:\Program Files\Lassalle Technologies\AddFlow 5\AddFlow5.chm
// HelpString: Lassalle AddFlow 5 ActiveX Control version
// DepndLst: 
//   (1) v2.0 stdole, (C:\WINDOWS\system32\stdole2.tlb)
// Errors:
//   Hint: Enum Member 'afCustomShape' of 'ShapeConstants' changed to 'afCustomShape_'
//   Hint: Symbol 'Click' renamed to '_Click'
// ************************************************************************ //

#include <vcl.h>
#pragma hdrstop

#include <olectrls.hpp>
#if defined(USING_ATL)
#include <atl\atlvcl.h>
#endif

#include "AddFlow5Lib_OCX.h"

#if !defined(__PRAGMA_PACKAGE_SMART_INIT)
#define      __PRAGMA_PACKAGE_SMART_INIT
#pragma package(smart_init)
#endif

namespace Addflow5lib_tlb
{



// *********************************************************************//
// OCX PROXY CLASS IMPLEMENTATION
// (The following variables/methods implement the class TAddFlow which
// allows "Lassalle AddFlow 5 ActiveX Control" to be hosted in CBuilder IDE/apps).
// *********************************************************************//
int   TAddFlow::EventDispIDs[19] = {
    0xFFFFFDA0, 0x00000001, 0x00000002, 0x00000003, 0x00000004, 0x00000005,
    0x00000006, 0x00000007, 0x00000008, 0x00000009, 0x0000000A, 0x0000000B,
    0x0000000C, 0x0000000D, 0x0000000E, 0x0000000F, 0x00000010, 0x00000011,
    0x00000012};

WCHAR TAddFlow::wLicenseKey[11] = {
    0x0055, 0x006E, 0x006C, 0x0069, 0x0063, 0x0065, 0x006E, 0x0073, 0x0065, 0x0064, 0x0000};

int TAddFlow::TFontIDs[1] = {
    0xFFFFFE00
};

int TAddFlow::TPictureIDs[2] = {
    0x00000042, 0x00000047
};

TControlData TAddFlow::CControlData =
{
  // GUID of CoClass and Event Interface of Control
  {0xC947F0AF, 0x6F1A, 0x49A7,{ 0xA6, 0x5A, 0xD0,0xF4, 0x5D, 0xC7,0x50, 0x76} }, // CoClass
  {0x9431AEF2, 0x26DB, 0x42B6,{ 0x86, 0x9F, 0x48,0xD0, 0xC9, 0x76,0x3F, 0x08} }, // Events

  // Count of Events and array of their DISPIDs
  19, &EventDispIDs,

  // Pointer to Runtime License string
  &wLicenseKey,  // HRESULT(0x00000000)

  // Flags for OnChanged PropertyNotification
  0x0000000D,
  300,// (IDE Version)

  // Count of Font Prop and array of their DISPIDs
  1, TFontIDs,

  // Count of Pict Prop and array of their DISPIDs
  2, TPictureIDs,
  0, // Reserved
  0, // Instance count (used internally)
  0, // List of Enum descriptions (internal)
};

GUID     TAddFlow::DEF_CTL_INTF = {0xBF12FD4C, 0x504D, 0x4B4D,{ 0xAC, 0x66, 0x21,0x0B, 0xF9, 0x0E,0xE5, 0x9C} };
TNoParam TAddFlow::OptParam;

static inline void ValidCtrCheck(TAddFlow *)
{
   delete new TAddFlow((TComponent*)(0));
};

void __fastcall TAddFlow::InitControlData()
{
  ControlData = &CControlData;
};

void __fastcall TAddFlow::CreateControl()
{
  if (!m_OCXIntf)
  {
    _ASSERTE(DefaultDispatch);
    DefaultDispatch->QueryInterface(DEF_CTL_INTF, (LPVOID*)&m_OCXIntf);
  }
};

_DAddFlowDisp __fastcall TAddFlow::GetDefaultInterface()
{
  CreateControl();
  return m_OCXIntf;
};

void __fastcall TAddFlow::AboutBox(void)
{
  GetDefaultInterface()->AboutBox();
}

Addflow5lib_tlb::afLink* __fastcall TAddFlow::AddLink(Addflow5lib_tlb::afNode* Org, 
                                                      Addflow5lib_tlb::afNode* Dst)
{
  return GetDefaultInterface()->AddLink(Org, Dst);
}

IPictureDisp** __fastcall TAddFlow::ExportPagePicture(float Left, float Top, float Width, 
                                                      float Height)
{
  return GetDefaultInterface()->ExportPagePicture(Left, Top, Width, Height);
}

OLE_HANDLE __fastcall TAddFlow::SaveMemory(Addflow5lib_tlb::ItemSetConstants ItemSet)
{
  return GetDefaultInterface()->SaveMemory(ItemSet);
}

void __fastcall TAddFlow::LoadMemory(OLE_HANDLE hMem)
{
  GetDefaultInterface()->LoadMemory(hMem);
}

void __fastcall TAddFlow::BeginAction(short code)
{
  GetDefaultInterface()->BeginAction(code);
}

void __fastcall TAddFlow::UndocMethod(short param)
{
  GetDefaultInterface()->UndocMethod(param);
}

void __fastcall TAddFlow::EndAction(void)
{
  GetDefaultInterface()->EndAction();
}

VARIANT_BOOL __fastcall TAddFlow::CanRedo(void)
{
  return GetDefaultInterface()->CanRedo();
}

VARIANT_BOOL __fastcall TAddFlow::CanUndo(void)
{
  return GetDefaultInterface()->CanUndo();
}

void __fastcall TAddFlow::Redo(void)
{
  GetDefaultInterface()->Redo();
}

void __fastcall TAddFlow::Undo(void)
{
  GetDefaultInterface()->Undo();
}

void __fastcall TAddFlow::ZoomRectangle(short TypeZoom, float Left, float Top, float Width, 
                                        float Height)
{
  GetDefaultInterface()->ZoomRectangle(TypeZoom, Left, Top, Width, Height);
}

void __fastcall TAddFlow::SelectRectangle(Addflow5lib_tlb::FilterConstants Filter, float Left, 
                                          float Top, float Width, float Height)
{
  GetDefaultInterface()->SelectRectangle(Filter, Left, Top, Width, Height);
}

void __fastcall TAddFlow::StartEdit(void)
{
  GetDefaultInterface()->StartEdit();
}

VARIANT_BOOL __fastcall TAddFlow::CanPaste(void)
{
  return GetDefaultInterface()->CanPaste();
}

void __fastcall TAddFlow::Paste(VARIANT_BOOL SelectPastedItems)
{
  GetDefaultInterface()->Paste(SelectPastedItems);
}

void __fastcall TAddFlow::Copy(Addflow5lib_tlb::ItemSetConstants ItemSet)
{
  GetDefaultInterface()->Copy(ItemSet);
}

void __fastcall TAddFlow::DisplayPropertyPage(short param)
{
  GetDefaultInterface()->DisplayPropertyPage(param);
}

IPictureDisp** __fastcall TAddFlow::ExportPicture(Addflow5lib_tlb::ItemSetConstants ItemSet, 
                                                  VARIANT_BOOL IncludeBackColor, 
                                                  VARIANT_BOOL IncludeBackPic)
{
  return GetDefaultInterface()->ExportPicture(ItemSet, IncludeBackColor, IncludeBackPic);
}

Addflow5lib_tlb::afLink* __fastcall TAddFlow::GetLinkAtPoint(float x, float y)
{
  return GetDefaultInterface()->GetLinkAtPoint(x, y);
}

Addflow5lib_tlb::afNode* __fastcall TAddFlow::GetNodeAtPoint(float x, float y)
{
  return GetDefaultInterface()->GetNodeAtPoint(x, y);
}

void __fastcall TAddFlow::LoadFile(BSTR file)
{
  GetDefaultInterface()->LoadFile(file);
}

void __fastcall TAddFlow::SaveFile(BSTR file)
{
  GetDefaultInterface()->SaveFile(file);
}

void __fastcall TAddFlow::DeleteMarked(void)
{
  GetDefaultInterface()->DeleteMarked();
}

void __fastcall TAddFlow::DeleteSel(void)
{
  GetDefaultInterface()->DeleteSel();
}

void __fastcall TAddFlow::GetVersion(short* major, short* minor)
{
  GetDefaultInterface()->GetVersion(major, minor);
}

void __fastcall TAddFlow::SetSelChangedFlag(VARIANT_BOOL SelChanged)
{
  GetDefaultInterface()->SetSelChangedFlag(SelChanged);
}

VARIANT_BOOL __fastcall TAddFlow::IsSelChanged(void)
{
  return GetDefaultInterface()->IsSelChanged();
}

void __fastcall TAddFlow::SaveImage(Addflow5lib_tlb::SaveImageMediumConstants tymed, 
                                    Addflow5lib_tlb::SaveImageFormatConstants format, BSTR file)
{
  GetDefaultInterface()->SaveImage(tymed, format, file);
}

void __fastcall TAddFlow::DoClick(void)
{
  GetDefaultInterface()->DoClick();
}

void __fastcall TAddFlow::SetChangedFlag(VARIANT_BOOL Changed)
{
  GetDefaultInterface()->SetChangedFlag(Changed);
}

VARIANT_BOOL __fastcall TAddFlow::IsChanged(void)
{
  return GetDefaultInterface()->IsChanged();
}

void __fastcall TAddFlow::SelectAll(void)
{
  GetDefaultInterface()->SelectAll();
}

void __fastcall TAddFlow::Refresh(void)
{
  GetDefaultInterface()->Refresh();
}

Addflow5lib_tlb::afLink* __fastcall TAddFlow::get_PointedLink()
{
  return GetDefaultInterface()->get_PointedLink();
}

void __fastcall TAddFlow::set_PointedLink(Addflow5lib_tlb::afLink* param)
{
  GetDefaultInterface()->set_PointedLink(param);
}

Addflow5lib_tlb::afSelLinks* __fastcall TAddFlow::get_SelLinks()
{
  return GetDefaultInterface()->get_SelLinks();
}

void __fastcall TAddFlow::set_SelLinks(Addflow5lib_tlb::afSelLinks* param)
{
  GetDefaultInterface()->set_SelLinks(param);
}

Addflow5lib_tlb::afSelNodes* __fastcall TAddFlow::get_SelNodes()
{
  return GetDefaultInterface()->get_SelNodes();
}

void __fastcall TAddFlow::set_SelNodes(Addflow5lib_tlb::afSelNodes* param)
{
  GetDefaultInterface()->set_SelNodes(param);
}

Addflow5lib_tlb::afPictures* __fastcall TAddFlow::get_Pictures()
{
  return GetDefaultInterface()->get_Pictures();
}

void __fastcall TAddFlow::set_Pictures(Addflow5lib_tlb::afPictures* param)
{
  GetDefaultInterface()->set_Pictures(param);
}

Addflow5lib_tlb::afNode* __fastcall TAddFlow::get_RedoNode()
{
  return GetDefaultInterface()->get_RedoNode();
}

void __fastcall TAddFlow::set_RedoNode(Addflow5lib_tlb::afNode* param)
{
  GetDefaultInterface()->set_RedoNode(param);
}

Addflow5lib_tlb::afLink* __fastcall TAddFlow::get_RedoLink()
{
  return GetDefaultInterface()->get_RedoLink();
}

void __fastcall TAddFlow::set_RedoLink(Addflow5lib_tlb::afLink* param)
{
  GetDefaultInterface()->set_RedoLink(param);
}

Addflow5lib_tlb::afLink* __fastcall TAddFlow::get_UndoLink()
{
  return GetDefaultInterface()->get_UndoLink();
}

void __fastcall TAddFlow::set_UndoLink(Addflow5lib_tlb::afLink* param)
{
  GetDefaultInterface()->set_UndoLink(param);
}

Addflow5lib_tlb::afNodes* __fastcall TAddFlow::get_Nodes()
{
  return GetDefaultInterface()->get_Nodes();
}

void __fastcall TAddFlow::set_Nodes(Addflow5lib_tlb::afNodes* param)
{
  GetDefaultInterface()->set_Nodes(param);
}

Addflow5lib_tlb::afNode* __fastcall TAddFlow::get_SelectedNode()
{
  return GetDefaultInterface()->get_SelectedNode();
}

void __fastcall TAddFlow::set_SelectedNode(Addflow5lib_tlb::afNode* param)
{
  GetDefaultInterface()->set_SelectedNode(param);
}

Addflow5lib_tlb::afNode* __fastcall TAddFlow::get_PointedNode()
{
  return GetDefaultInterface()->get_PointedNode();
}

void __fastcall TAddFlow::set_PointedNode(Addflow5lib_tlb::afNode* param)
{
  GetDefaultInterface()->set_PointedNode(param);
}

Addflow5lib_tlb::afLink* __fastcall TAddFlow::get_SelectedLink()
{
  return GetDefaultInterface()->get_SelectedLink();
}

void __fastcall TAddFlow::set_SelectedLink(Addflow5lib_tlb::afLink* param)
{
  GetDefaultInterface()->set_SelectedLink(param);
}

Addflow5lib_tlb::afCustomShapes* __fastcall TAddFlow::get_CustomShapes()
{
  return GetDefaultInterface()->get_CustomShapes();
}

void __fastcall TAddFlow::set_CustomShapes(Addflow5lib_tlb::afCustomShapes* param)
{
  GetDefaultInterface()->set_CustomShapes(param);
}

Addflow5lib_tlb::afNode* __fastcall TAddFlow::get_UndoNode()
{
  return GetDefaultInterface()->get_UndoNode();
}

void __fastcall TAddFlow::set_UndoNode(Addflow5lib_tlb::afNode* param)
{
  GetDefaultInterface()->set_UndoNode(param);
}


};     // namespace Addflow5lib_tlb


// *********************************************************************//
// The Register function is invoked by the IDE when this module is 
// installed in a Package. It provides the list of Components (including
// OCXes) implemented by this module. The following implementation
// informs the IDE of the OCX proxy classes implemented here.
// *********************************************************************//
namespace Addflow5lib_ocx
{

void __fastcall PACKAGE Register()
{
  // [1]
  TComponentClass cls_ocx[] = {
                              __classid(Addflow5lib_tlb::TAddFlow)
                           };
  RegisterComponents("ActiveX", cls_ocx,
                     sizeof(cls_ocx)/sizeof(cls_ocx[0])-1);
}

};     // namespace Addflow5lib_ocx
