#include "GamePCH.h"
#include "AppManager.h"



AppManager::AppManager()
{

}

AppManager::~AppManager()
{

}

HRESULT AppManager::Initialize()
{
	HRESULT hr;

	// Initialize device-indpendent resources, such
	// as the Direct2D factory.

		// Register the window class.
	WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = AppManager::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = sizeof(LONG_PTR);
	wcex.hInstance = HINST_THISCOMPONENT;
	wcex.hbrBackground = NULL;
	wcex.lpszMenuName = NULL;
	wcex.hCursor = LoadCursor(NULL, IDI_APPLICATION);
	wcex.lpszClassName = L"ENTROPY";

	RegisterClassEx(&wcex);


	// Create the window.
	m_hwnd = CreateWindow(
		L"ENTROPY",
		L"ENTROPY App",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		1920,
		1080,
		NULL,
		NULL,
		HINST_THISCOMPONENT,
		this
	);

	hr = m_hwnd ? S_OK : E_FAIL;

	_GraphicEngine->Initalize(m_hwnd);
	//DDEngine::GetInstance()->CreateDeviceIndependentResources(m_hwnd);
	GameManager::GetInstance()->Initialize();

	if (SUCCEEDED(hr))
	{
		SetLayeredWindowAttributes(m_hwnd, RGB(0, 0, 0), 255, ULW_COLORKEY | LWA_ALPHA);
		SetWindowLong(m_hwnd, GWL_STYLE, 0);
		ShowWindow(m_hwnd, SW_SHOWMAXIMIZED);
		UpdateWindow(m_hwnd);
	}
	//폰트 스타일을 등록해주는 구문입니다
	_GraphicEngine->D2DXCreateFontStyle(_T("LAB디지털"), 40.0f);
	_GraphicEngine->D2DXCreateFontStyle(_T("궁서"), 20.0f);
	_GraphicEngine->D2DXCreateFontStyle(_T("굴림"), 20.0f);
	_GraphicEngine->D2DXCreateFontStyle(_T("바탕"), 20.0f);

	//사운드를 등록해주는 구문입니다.
	_FAudio->FCreate();
	_FAudio->FInit();

	srand(time(NULL));

	int index = 0;
	_FAudio->FAddBackground(BGM1, true, &GameManager::m_pBackgroundChannel[index++], _T("bgm"));
	GameManager::m_pBackgroundChannel[0]->setVolume(0.2);
	GameManager::m_pBackgroundChannel[0]->setPaused(true);
	_FAudio->FAddBackground(BGM2, true, &GameManager::m_pBackgroundChannel[index++], _T("bgm"));
	GameManager::m_pBackgroundChannel[1]->setVolume(0.2);
	GameManager::m_pBackgroundChannel[1]->setPaused(true);
	_FAudio->FAddBackground(BGM3, true, &GameManager::m_pBackgroundChannel[index++], _T("bgm"));
	GameManager::m_pBackgroundChannel[2]->setVolume(0.2);
	GameManager::m_pBackgroundChannel[2]->setPaused(true);
	_FAudio->FAddBackground(BGM4, true, &GameManager::m_pBackgroundChannel[index++], _T("bgm"));
	GameManager::m_pBackgroundChannel[3]->setVolume(0.2);
	GameManager::m_pBackgroundChannel[3]->setPaused(true);
	_FAudio->FAddBackground(BGM_BOSS, true, &GameManager::m_pBackgroundChannel[index++], _T("bgm"));
	GameManager::m_pBackgroundChannel[4]->setVolume(0.2);
	GameManager::m_pBackgroundChannel[4]->setPaused(true);
	_FAudio->FAddBackground(BGM_BRIGHT, true, &GameManager::m_pBackgroundChannel[index], _T("bgm"));
	GameManager::m_pBackgroundChannel[5]->setVolume(0.2);
	GameManager::m_pBackgroundChannel[5]->setPaused(false);
	

	//System SFX LOAD
	_FAudio->FAddSound(CONVERT_0_SFX,      false, _T("system"));
	_FAudio->FAddSound(CONVERT_1_SFX,      false, _T("system"));
	_FAudio->FAddSound(GAMEOVER_SFX,       false, _T("system"));
	_FAudio->FAddSound(OVERLOAD_SFX,       false, _T("system"));
	_FAudio->FAddSound(OVERLOAD_END_SFX,   false, _T("system"));
	_FAudio->FAddSound(OVERLOAD_START_SFX, false, _T("system"));
	_FAudio->FAddSound(UPGRADE_CLEAR,      false, _T("system"));
	_FAudio->FAddSound(UPGRADE_START,      false, _T("system"));


	//Ann(Player) SFX LOAD
	_FAudio->FAddSound(ANN_ATTK_0,					false, _T("player"));
	_FAudio->FAddSound(ANN_ATTK_1,					false, _T("player"));;
	_FAudio->FAddSound(ANN_ATTK_2,					false, _T("player"));;
	_FAudio->FAddSound(ANN_ATTK_INVERSE_0,			false, _T("player"));;
	_FAudio->FAddSound(ANN_ATTK_INVERSE_1,			false, _T("player"));;
	_FAudio->FAddSound(ANN_ATTK_OVERLOAD_NORMAL,	false, _T("player"));;
	_FAudio->FAddSound(ANN_ATTK_OVERLOAD_INVERSE,	false, _T("player"));;
	_FAudio->FAddSound(ANN_JUMP_NORMAL,				false, _T("player"));;
	_FAudio->FAddSound(ANN_JUMP_DOBLE,				false, _T("player"));;
	_FAudio->FAddSound(ANN_JUMP_BELOW,				false, _T("player"));;
	_FAudio->FAddSound(ANN_DASH,					false, _T("player"));;
	_FAudio->FAddSound(ANN_DIE,						false, _T("player"));;
	_FAudio->FAddSound(ANN_HIT,						false, _T("player"));;
	_FAudio->FAddSound(ANN_INTERACTION_PRESERVE,	false, _T("player"));;
	_FAudio->FAddSound(ANN_INTERACTION_START,		false, _T("player"));;
	_FAudio->FAddSound(ANN_LANDING,					false, _T("player"));;
	_FAudio->FAddSound(ANN_MOVE,					false, _T("player"));;


	//Ann(Player) VOICE LOAD
	_FAudio->FAddSound(ANN_VOICE_0,  false, _T("player/ann voice"));
	_FAudio->FAddSound(ANN_VOICE_1,  false, _T("player/ann voice"));
	_FAudio->FAddSound(ANN_VOICE_2,  false, _T("player/ann voice"));
	_FAudio->FAddSound(ANN_VOICE_3,  false, _T("player/ann voice"));
	_FAudio->FAddSound(ANN_VOICE_4,  false, _T("player/ann voice"));
	_FAudio->FAddSound(ANN_VOICE_5,  false, _T("player/ann voice"));
	_FAudio->FAddSound(ANN_VOICE_6,  false, _T("player/ann voice"));
	_FAudio->FAddSound(ANN_VOICE_7,  false, _T("player/ann voice"));
	_FAudio->FAddSound(ANN_VOICE_8,  false, _T("player/ann voice"));
	_FAudio->FAddSound(ANN_VOICE_9,  false, _T("player/ann voice"));
	_FAudio->FAddSound(ANN_VOICE_10, false, _T("player/ann voice"));
	_FAudio->FAddSound(ANN_VOICE_11, false, _T("player/ann voice"));
	_FAudio->FAddSound(ANN_VOICE_12, false, _T("player/ann voice"));
	_FAudio->FAddSound(ANN_VOICE_13, false, _T("player/ann voice"));
	_FAudio->FAddSound(ANN_VOICE_14, false, _T("player/ann voice"));
	_FAudio->FAddSound(ANN_VOICE_15, false, _T("player/ann voice"));
	_FAudio->FAddSound(ANN_VOICE_16, false, _T("player/ann voice"));
	_FAudio->FAddSound(ANN_VOICE_17, false, _T("player/ann voice"));
	_FAudio->FAddSound(ANN_VOICE_18, false, _T("player/ann voice"));
	_FAudio->FAddSound(ANN_VOICE_19, false, _T("player/ann voice"));
	_FAudio->FAddSound(ANN_VOICE_20, false, _T("player/ann voice"));
	_FAudio->FAddSound(ANN_VOICE_21, false, _T("player/ann voice"));
	_FAudio->FAddSound(ANN_VOICE_22, false, _T("player/ann voice"));


	//Tropy(Gun) Voice LOAD
	_FAudio->FAddSound(TROPY_VOICE_0, false, _T("player/tropy voice"));
	_FAudio->FAddSound(TROPY_VOICE_1, false, _T("player/tropy voice"));
	_FAudio->FAddSound(TROPY_VOICE_2, false, _T("player/tropy voice"));
	
	
	//EtcObject SFX Load
	_FAudio->FAddSound(OBJECT_GATE_0,      false,  _T("object"));
	_FAudio->FAddSound(OBJECT_SWITCH_0,    false,  _T("object"));
	_FAudio->FAddSound(OBJECT_SWITCH_1,    false,  _T("object"));
	_FAudio->FAddSound(OBJECT_GENERATOR_0, false,  _T("object"));
	_FAudio->FAddSound(OBJECT_VARIATION_0, false,  _T("object"));
	
	//Bullet SFX Load
	_FAudio->FAddSound(OBJECT_BULLET_0,     false, _T("object/bullet"));
	_FAudio->FAddSound(OBJECT_BULLET_1,     false, _T("object/bullet"));
	_FAudio->FAddSound(OBJECT_BULLET_2,     false, _T("object/bullet"));
	_FAudio->FAddSound(OBJECT_BULLET_3    , false, _T("object/bullet"));
	_FAudio->FAddSound(OBJECT_BULLET_DEALY, false, _T("object/bullet"));
	_FAudio->FAddSound(OBJECT_BULLET_SHILD, false, _T("object/bullet"));
	
	//EnemyObject SFX Load

	_FAudio->FAddSound(ENEMY_BEAR_MOVE,  false,    _T("monster/bear"));
	_FAudio->FAddSound(ENEMY_BEAR_ATTK,  false,    _T("monster/bear"));
	_FAudio->FAddSound(ENEMY_BEAR_RECOG, false,    _T("monster/bear"));
	_FAudio->FAddSound(ENEMY_BEAR_DIE,   false,    _T("monster/bear"));
													 
	_FAudio->FAddSound(ENEMY_TUTLE_MOVE,  false,   _T("monster/turtle"));
	_FAudio->FAddSound(ENEMY_TUTLE_ATTK,  false,   _T("monster/turtle"));
	_FAudio->FAddSound(ENEMY_TUTLE_HIT,   false,   _T("monster/turtle"));
	_FAudio->FAddSound(ENEMY_TUTLE_RECOG, false,   _T("monster/turtle"));
	_FAudio->FAddSound(ENEMY_TUTLE_DIE,   false,   _T("monster/turtle"));
													 
	_FAudio->FAddSound(ENEMY_TANK_MOVE,   false,   _T("monster/tank"));
	_FAudio->FAddSound(ENEMY_TANK_ATTK_0, false,   _T("monster/tank"));
	_FAudio->FAddSound(ENEMY_TANK_ATTK_1, false,   _T("monster/tank"));
	_FAudio->FAddSound(ENEMY_TANK_MOVE,   false,   _T("monster/tank"));
	_FAudio->FAddSound(ENEMY_TANK_RECOG,  false,   _T("monster/tank"));
	_FAudio->FAddSound(ENEMY_TANK_DIE,    false,   _T("monster/tank"));
													 
	_FAudio->FAddSound(ENEMY_CRANE_MOVE,  false,   _T("monster/crane"));
	_FAudio->FAddSound(ENEMY_CRANE_ATTK,  false,   _T("monster/crane"));
	_FAudio->FAddSound(ENEMY_CRANE_JUMP,  false,   _T("monster/crane"));
	_FAudio->FAddSound(ENEMY_CRANE_RECOG, false,   _T("monster/crane"));
	_FAudio->FAddSound(ENEMY_CRANE_DIE,   false,   _T("monster/crane"));
													 
	_FAudio->FAddSound(BOSS_VOICE_1,	  false,   _T("boss/boss voice"));
	_FAudio->FAddSound(BOSS_VOICE_2,	  false,   _T("boss/boss voice"));
	_FAudio->FAddSound(BOSS_VOICE_3,	  false,   _T("boss/boss voice"));





	

	//FAudio::m_pBackgroundChannel->stop();

	//_FAudio->FSoundAllPlay(false);

	return hr;
}


void AppManager::RunMessageLoop()
{
	MSG msg;
	// 기본 메시지 루프입니다:
	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			if (FTime::GetInstance()->FixedUpdate())
			{
				InputManager::KeyUpdate();
				FTime::GetInstance()->SetFixedDeltaTimeSec();
				GameManager::GetInstance()->MainLoop();
			}
			//m_SoundTrack->Update();

		}
	}

}

LRESULT AppManager::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
		EndPaint(hwnd, &ps);
	}
	break;
	case WM_DESTROY:
		_FAudio->FRelease();
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;
}



void AppManager::OnResize(UINT width, UINT height)
{
	//if (DDEngine::GetInstance()->m_pRenderTarget)
	//{
	//	// Note: This method can fail, but it's okay to ignore the
	//	// error here, because the error will be returned again
	//	// the next time EndDraw is called.
	//	DDEngine::GetInstance()->m_pRenderTarget->Resize(D2D1::SizeU(width, height));
	//}
}


