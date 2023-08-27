#include "pch.h"
#include "framework.h"
#include "D2DGraphics.h"
#include "GameManager.h"




#ifdef _DEBUG


#ifdef UNICODE
	//유니코드
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

#endif



int main()
{
	
}


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow)
{



	GameManager::GetInstance()->Initialize(hInstance);
	GameManager::GetInstance()->On_Upadate();
	GameManager::GetInstance()->Off_Upadate();
	return 0;
}