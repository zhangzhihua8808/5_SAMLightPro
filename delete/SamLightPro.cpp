//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("..\src\UnitFormMain.cpp", FormMain);
USEFORM("..\src\UnitFormPMac.cpp", FormPmac);
USEFORM("..\src\UnitFormSamLight.cpp", FormSamLight);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();

                 HANDLE   hnd = CreateMutex(NULL,TRUE, "No   Previous   Instance! ");
                 if(NULL == hnd)
                 {
                      MessageBox(NULL, "创建Mutex失败! ", "NoPrev ",MB_OK|MB_SYSTEMMODAL);
                      return   0;
                 }
                 if(GetLastError()== ERROR_ALREADY_EXISTS)
                 {
                      ::MessageBox(NULL, "已经运行了一个实例! ",Application-> Title.c_str(),MB_OK|MB_SYSTEMMODAL);
                      ReleaseMutex(hnd);
                      return   0;
                 }

                 Application->CreateForm(__classid(TFormMain), &FormMain);
                 Application->CreateForm(__classid(TFormPmac), &FormPmac);
                 Application->CreateForm(__classid(TFormSamLight), &FormSamLight);
                 Application->CreateForm(__classid(TFormMain), &FormMain);
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
