//---------------------------------------------------------------------------

#ifndef UnitGenDXFThreadH
#define UnitGenDXFThreadH
//---------------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------
class  MAMProject;


class TGenDXFThread : public TThread
{
private:
       MAMProject*  fProject;
       bool         fSaveCatalog;
       String       fCliFile;
protected:
        void __fastcall Execute();
public:
        __fastcall TGenDXFThread(bool CreateSuspended,MAMProject* aProject,bool bSaveCat,String aCliFile);

        void __fastcall UpdateTreeNode();
};
//---------------------------------------------------------------------------
#endif
