#include "pch.h"
#include "framework.h"
#include "GameManager.h"
#include "FTime.h"
#include "Debug.h"


GameManager* GameManager::m_instance = nullptr;

GameManager* GameManager::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new GameManager();
	}
	return m_instance;
}


void GameManager::Initialize(HINSTANCE& _hinst)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.lpfnWndProc = WndProc;
	wcex.hInstance = _hinst;
	wcex.cbWndExtra = 0;
	wcex.cbClsExtra = 0;
	wcex.lpszClassName = m_szClassName;
	wcex.lpszMenuName = nullptr;
	wcex.hIcon = LoadIcon(_hinst, IDI_APPLICATION);
	wcex.hIconSm = LoadIcon(_hinst, IDI_APPLICATION);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.hCursor = LoadCursor(_hinst, IDI_APPLICATION);


	RegisterClassEx(&wcex);

	m_hwnd = CreateWindow(m_szClassName, m_szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		nullptr,
		nullptr,
		_hinst,
		nullptr
	);


	if (m_hwnd == nullptr)
	{
		return;
	}



	ShowWindow(m_hwnd, SW_SHOWDEFAULT);
	UpdateWindow(m_hwnd);

	D2DGrahpics::GetInstance()->Initalize(m_hwnd);


	//컴포넌트의 시초

	m_pEventExcuteSystem = EventExcuteSystem::GetInstance();

	m_pTestGameObj1 = new GameObject();

	m_pTestGameObj1->AddComponent<CircleCollider>();
	m_pTestGameObj1->GetComponent<CircleCollider>()->SetColliderDraw(true);
	m_pTestGameObj1->GetComponent<CircleCollider>()->SetColliderSize(100,100,150,150);

	
	m_pTestGameObj1->m_pTransform->m_Position.x = 100;
	m_pTestGameObj1->m_pTransform->m_Position.y = 100;

	/*m_pTestGameObj1->AddComponent<Rigidbody>();
	m_pTestGameObj1->GetComponent<Rigidbody>();
	m_pTestGameObj1->AddComponent<Sprite>();
	m_pTestGameObj1->GetComponent<Sprite>();
	
	m_pTestGameObj1->AddComponent<CircleCollider>();
	m_pTestGameObj1->GetComponent<CircleCollider>();*/

	m_pTestGameObj1->AddComponent<Input>();
	


	//샌드백
	//m_pTestGameObj2 = new GameObject(Collider::Shape::Circle);
	//m_pTestGameObj2->GetCollider()->SetColliderInfo(true);
	//m_pTestGameObj2->GetCollider()->SetColliderDraw(true);
	////---
	//m_pTestGameObj1->m_spr = new Sprite();


	m_pEventExcuteSystem->SendEventMessage(EnumEvent::Awake);

	m_pEventExcuteSystem->Update();

	//벡터에 json파일을 저장합니다.
//	m_ResourceTxtNames.push_back(_T("test.txt"));
//
//
//	//PATH_RESOURCE = 리소스저장경로
//	//벡터안에 있는 리소스의 텍스트파일을 읽어들여서
//	//불러들인다.
//	for (auto k = m_ResourceTxtNames.begin() ; k != m_ResourceTxtNames.end(); k++)
//	{
//		CString _tempCstr = (*k);
//		m_pTestGameObj1->m_spr->LoadSprite(PATH_RESOURCE_UNI+_tempCstr, 100, 100);
//	}
//	//프레임 제어를 위한
//	//타이머를 생성한다.
//	enTime = new FTime();
//
//	FAudio::Init();
//
//	//m_pTestGameObj1->GetCollider()->SetColliderSize(m_p1_x, m_p1_y, 150, 150);
//	//m_pTestGameObj1->m_spr->SetPosition(m_p1_x, m_p1_y);
//	//m_pTestGameObj1->m_pTransform->Translate(m_p1_x, m_p1_y);
//	//m_pTestGameObj1->GetCollider()->Collisition(m_pTestGameObj2->GetCollider());
//	//m_pTestGameObj1->GetCollider()->OnRender();
//	//m_pTestGameObj1->GetCollider()->Update();
//
//	////사이즈를 정해준다.
//	//m_pTestGameObj2->GetCollider()->SetColliderSize(m_target_x, m_target_y, 150, 150);
//	//m_pTestGameObj2->GetCollider()->OnRender();
//	//m_pTestGameObj2->GetCollider()->Update();
//
//	//저장할 키와 파일명을 입력한다. //상대경로 맞춤은 나중에 맞춰주자
//	/*FAudio::GetInstance()->m_AudioMaps.insert(pair<int,const char*>(1,"../../singing.wav"));
//
//
//	for (auto k = FAudio::GetInstance()->m_AudioMaps.begin(); k != FAudio::GetInstance()->m_AudioLists.end(); k++)
//	{
//		k->first;
//	}*/
//
//	//왜 상대경로는 잡히는데 절대경로는 안잡히냐? ㅋㅋ루삥뽕
//	//GameManager::GetInstance()->m_SoundTrack = new FAudio("../../Sound/file_example_WAV_1MG.wav", true);
//	
//#if _DEBUG
//
//	GameManager::GetInstance()->m_SoundTrack = new FAudio("../../Sound/file_example_WAV_1MG.wav", true);
//#else
//	GameManager::GetInstance()->m_SoundTrack = new FAudio("../Sound/file_example_WAV_1MG.wav", true);
//#endif
//
//	//GameManager::GetInstance()->m_SoundTrack = new FAudio("../../Sound/singing.wav", true);
//	GameManager::GetInstance()->m_SoundTrack->GetInstance()->play();
//
//	GameManager::GetInstance()->m_SoundTrack->play();
//	GameManager::GetInstance()->m_SoundTrack->volumeUp();
//
//	int a;
}




void GameManager::On_Upadate()
{

	// Allocate Object
	//2번째 매개변수의 true ,false에 따라 반복,혹은 단일재생만 할수 있도록 설정됨

	MSG msg;
	while (1)
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
			GameProccess();
			// Play Sound | 사운드 재생 시작
			
			//Debug::LogFormat("사운드 파일실행중");
		
			//GameManager::GetInstance()->m_SoundTrack->Update();
			
		}
	}
	


}
void GameManager::Off_Upadate()
{
	//delete GameManager::GetInstance()->m_SoundTrack;
	//FAudio::Release();

	//delete enTime;
	//enTime = nullptr;
}


void GameManager::GetInput()
{
}


void GameManager::GameProccess()
{
	D2DGrahpics::GetInstance()->BeginRender();
	/*m_pTestGameObj1->m_spr->Update(1000);
	enTime->Update();
	GetInput();*/
	//m_pTestGameObj1->GetCollider()->SetColliderSize(m_p1_x, m_p1_y, 150, 150);
	//m_pTestGameObj1->m_spr->SetPosition(m_p1_x, m_p1_y);
	//m_pTestGameObj1->m_pTransform->Translate(m_p1_x, m_p1_y);
	//m_pTestGameObj1->GetCollider()->Collisition(m_pTestGameObj2->GetCollider());
	//m_pTestGameObj1->GetCollider()->OnRender();
	//m_pTestGameObj1->GetCollider()->Update();


	m_pEventExcuteSystem->SendEventMessage(EnumEvent::Update);
	m_pEventExcuteSystem->Update();

	m_pEventExcuteSystem->SendEventMessage(EnumEvent::OnRender);
	m_pEventExcuteSystem->Update();
	//HelpText();
	D2DGrahpics::GetInstance()->EndRender();
	
}

void GameManager::HelpText()
{
	float _fps = enTime->GetFPS();
	float _dtime = enTime->GetDeltaTimeMS();

	GraphicEngine->D2DXDrawText(200, 0, 10, 10, D2D1::ColorF::White,L"인게임 정보를 표시합니다");
	GraphicEngine->D2DXDrawText(1200, 0, 10, 10, D2D1::ColorF::White, L"출력 디버깅");
	GraphicEngine->D2DXDrawText(1200, 50, 10, 10, D2D1::ColorF::White, L"F1:원");
	GraphicEngine->D2DXDrawText(1200, 75, 10, 10, D2D1::ColorF::White, L"F2:사각형");
	GraphicEngine->D2DXDrawText(1200, 100, 10, 10, D2D1::ColorF::White, L"x: %d:", (short)m_p1_x);
	GraphicEngine->D2DXDrawText(1200, 150, 10, 10, D2D1::ColorF::White, L"y: %d:", (short)m_p1_y);
	GraphicEngine->D2DXDrawText(1200, 200, 10, 10, D2D1::ColorF::White, L"현재1p 충돌타입 :%d", m_pTestGameObj1->GetCollider()->GetColliderType());


	GraphicEngine->D2DXDrawText(20, 0, 10, 10, D2D1::ColorF::White, L"FPS:");
	GraphicEngine->D2DXDrawText(50, 0, 10, 10, D2D1::ColorF::White, L"%f", _fps);
	GraphicEngine->D2DXDrawText(20, 50, 10, 10, D2D1::ColorF::White, L"DeltaTime:");
	GraphicEngine->D2DXDrawText(80, 50, 10, 10, D2D1::ColorF::White,L"%f" , _dtime);
	GraphicEngine->D2DXDrawText(20, 200, 10, 10, D2D1::ColorF::White, L"5번키 : 정보켜기");
	GraphicEngine->D2DXDrawText(20, 250, 10, 10, D2D1::ColorF::White, L"6번키 : 정보끄기");

}

LRESULT GameManager::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYDOWN:

		break;
	case WM_CREATE:
	{
	}
	break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{

		}
		break;

	case WM_PAINT:
		break;
	case WM_DESTROY:
		GameManager::GetInstance()->Off_Upadate();
		PostQuitMessage(0);

		break;

	}

	// WinProc에서 처리하지 않는 나머지 메시지를 윈도우 기본으로 처리하도록 전달

	return (DefWindowProc(hwnd, message, wParam, lParam));

}

