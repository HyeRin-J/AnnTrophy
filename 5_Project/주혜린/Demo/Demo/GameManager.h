#pragma once

class GameManager : public SingletonManager<GameManager>
{
	// 스크린 사이즈
	const int m_ScreenWidth = 800;
	const int m_ScreenHeight = 600;

	// 윈도우 핸들
	HWND m_hWnd;
	const WCHAR* szWindowClass = _T("Game Demo");
	const WCHAR* szTitle = _T("Game Demo");

	// 그래픽스 엔진
	RRYD2DEngine* m_pEngine;
	EventExcuteSystem* m_pEventSystem;

public:
	void Initialize(HINSTANCE inst);
	void Looping();
	void GameProc();
	void Finish();

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

