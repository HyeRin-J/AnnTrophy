// Default.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
#include <iostream>
#include "framework.h"
#include "GameManager.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 여기에 코드를 입력합니다.
	GameManager* gm = GameManager::GetInstance();
	gm->Initialize(hInstance);
	gm->Looping();
	gm->Finish();

	return 0;
}