//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("..\src\UnitFileSelect.cpp", FormFileCombine);
USEFORM("..\src\UnitFormGY.cpp", FormGYDesign);
USEFORM("..\src\UnitFormLaserPen.cpp", FormLaserPen);
USEFORM("..\src\UnitFormLaserSetting.cpp", FormLaserSetting);
USEFORM("..\src\UnitFormMain.cpp", FormMain);
USEFORM("..\src\UnitFormMechConfig.cpp", FormMechConfig);
USEFORM("..\src\UnitFormPMac.cpp", FormPmac);
USEFORM("..\src\UnitFormSamLight.cpp", FormSamLight);
USEFORM("..\src\UnitModelLoad.cpp", FormLoadModel);
USEFORM("..\src\UnitNewProject.cpp", FormNewProject);
USEFORM("..\src\UnitOpenProject.cpp", FormOpenProject);
USEFORM("..\src\UnitSystemTest.cpp", FormSystemTest);
USEFORM("..\src\UnitTestInstance.cpp", FormTestInstance);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TFormMain), &FormMain);
                 Application->CreateForm(__classid(TFormFileCombine), &FormFileCombine);
                 Application->CreateForm(__classid(TFormGYDesign), &FormGYDesign);
                 Application->CreateForm(__classid(TFormLaserPen), &FormLaserPen);
                 Application->CreateForm(__classid(TFormLaserSetting), &FormLaserSetting);
                 Application->CreateForm(__classid(TFormMechConfig), &FormMechConfig);
                 Application->CreateForm(__classid(TFormPmac), &FormPmac);
                 Application->CreateForm(__classid(TFormSamLight), &FormSamLight);
                 Application->CreateForm(__classid(TFormLoadModel), &FormLoadModel);
                 Application->CreateForm(__classid(TFormNewProject), &FormNewProject);
                 Application->CreateForm(__classid(TFormOpenProject), &FormOpenProject);
                 Application->CreateForm(__classid(TFormSystemTest), &FormSystemTest);
                 Application->CreateForm(__classid(TFormTestInstance), &FormTestInstance);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        catch (...)
        {
                 try
                 {
                         throw Exception("");
                 }
                 catch (Exception &exception)
                 {
                         Application->ShowException(&exception);
                 }
        }
        return 0;
}
//---------------------------------------------------------------------------
