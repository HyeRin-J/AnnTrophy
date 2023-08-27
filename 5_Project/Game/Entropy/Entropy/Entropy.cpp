// Entropy.cpp : Defines the entry point for the application.
//

#include "GamePCH.h"
#include "framework.h"
#include "Entropy.h"

#define APP AppManager::GetInstance()
#ifdef _DEBUG


#ifdef UNICODE
    //�����ڵ�
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#endif

#endif


#define _DEVENI  1 //����ȯ���� �����ڵ����� ����

#ifdef _DEVENI
//����ȯ�� ����

#ifdef UNICODE
//��Ƽ ����Ʈ
int g_Dev_Environment = UNICODE + 1;
#else
//���� �ڵ�
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
