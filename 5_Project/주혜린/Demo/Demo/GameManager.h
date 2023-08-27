#pragma once

class GameManager : public SingletonManager<GameManager>
{
	// ��ũ�� ������
	const int m_ScreenWidth = 800;
	const int m_ScreenHeight = 600;

	// ������ �ڵ�
	HWND m_hWnd;
	const WCHAR* szWindowClass = _T("Game Demo");
	const WCHAR* szTitle = _T("Game Demo");

	// �׷��Ƚ� ����
	RRYD2DEngine* m_pEngine;
	EventExcuteSystem* m_pEventSystem;

public:
	void Initialize(HINSTANCE inst);
	void Looping();
	void GameProc();
	void Finish();

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

