// GameDemo.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "GamePch.h"
#include "framework.h"
#include "AppDemo.h"
#include "GameManager.h"
#include "SystemClass.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);



#ifdef _DEBUG

#ifdef UNICODE
//유니코드
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

#endif




int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	
    if (GameManager::GetInstance()->Initialize() == true)
    {
        GameManager::GetInstance()->Update();
    }
    GameManager::GetInstance()->Release();

    
	return 0;
}
