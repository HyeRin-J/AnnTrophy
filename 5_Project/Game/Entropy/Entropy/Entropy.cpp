// Entropy.cpp : Defines the entry point for the application.
//

#include "GamePCH.h"
#include "framework.h"
#include "Entropy.h"

#define APP AppManager::GetInstance()
#ifdef _DEBUG


#ifdef UNICODE
    //유니코드
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#endif

#endif


#define _DEVENI  1 //개발환경이 유니코드인지 설정

#ifdef _DEVENI
//개발환경 설정

#ifdef UNICODE
//멀티 바이트
int g_Dev_Environment = UNICODE + 1;
#else
//유니 코드
int g_Dev_Environment = UNICODE;
#endif

#endif
int WINAPI WinMain(
    HINSTANCE /* hInstance */,
    HINSTANCE /* hPrevInstance */,
    LPSTR /* lpCmdLine */,
    int /* nCmdShow */
)
{
    // Use HeapSetInformation to specify that the process should
    // terminate if the heap manager detects an error in any heap used
    // by the process.
    // The return value is ignored, because we want to continue running in the
    // unlikely event that HeapSetInformation fails.
    HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

    if (SUCCEEDED(CoInitialize(NULL)))
    {
        {

            if (SUCCEEDED(APP->Initialize()))
            {
                APP->RunMessageLoop();
            }
        }
        CoUninitialize();
    }

    return 0;
}
