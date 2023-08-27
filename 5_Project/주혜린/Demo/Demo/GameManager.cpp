#include "pch.h"
#include <iostream>
#include "framework.h"
#include "resource.h"
#include "MoveCircle.h"
#include "Time.h"
#include "GameManager.h"

using namespace std;

GameObject* circle = ObjectFactory::CreateObject<GameObject>();
GameObject* circle2 = ObjectFactory::CreateObject<GameObject>();

void GameManager::Initialize(HINSTANCE inst)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = inst;
	wcex.hIcon = LoadIcon(inst, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	RegisterClassEx(&wcex);

	// 애플리케이션 초기화를 수행합니다:

	HWND hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, m_ScreenWidth, m_ScreenHeight, nullptr, nullptr, inst, nullptr);

	if (!hWnd)
	{
		return;
	}

	m_pEngine = RRYD2DEngine::GetInstance();
	m_pEngine->Initialize(hWnd);
	m_pEventSystem = EventExcuteSystem::GetInstance();

	circle->SetName("Circle");
	circle->AddComponent<BoundCircle>();
	circle->AddComponent<Animator>();
	Animator* animator = circle->GetComponent<Animator>();
	circle->AddComponent<RigidBody>();
	circle->GetComponent<RigidBody>()->SetMass(5);

	//********커스텀 Component 상속 예제****************//
	circle->AddComponent< MoveCircle>();

	animator->SetPath(_T("test.txt"));

	circle2->AddComponent<BoundCircle>();
	circle2->m_Transform->SetPosition(400, 400);
	circle2->m_Transform->SetScale(2, 2);
	circle2->GetComponent<BoundCircle>()->SetRadius(50);
	circle2->AddComponent<RigidBody>();
	circle2->GetComponent<RigidBody>()->SetMass(20);

	m_pEventSystem->SendEventMessage(EnumEvent::Awake);
	m_pEventSystem->Update();

	ShowWindow(hWnd, SW_SHOWMAXIMIZED);
	UpdateWindow(hWnd);
}

void GameManager::Looping()
{
	MSG msg;
	MessageSystem* plz = MessageSystem::GetInstance();

	CustomClass cla;

	CustomMessage* message = new CustomMessage();
	CustomMessage* message1 = new CustomMessage();
	CustomMessage* message2 = new CustomMessage();

	message->SetValue(0);
	message1->SetValue(1);
	message2->SetValue(2);

	// 기본 메시지 루프입니다:
	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT)
			{
				break;
			}
		}
		else
		{
			static DWORD64 startTick = GetTickCount64();
			DWORD64 currTick = GetTickCount64();

			float nextFrameTime = 1.f / 60;
			float deltaTime = (currTick - startTick) / 100.f;

			if (deltaTime > nextFrameTime)
			{
				startTick = currTick;
				
				GameProc();
			}
		}
	}
}

void GameManager::GameProc()
{
	m_pEngine->BeginRender();

	m_pEventSystem->SendEventMessage(EnumEvent::Update);

	m_pEngine->PrintText(400, 180, ColorF::Red, _T("F1 : 초기화"));
	m_pEngine->PrintText(400, 200, ColorF::Red, _T("x: %f, y : %f"), circle->m_Transform->GetPosition().x, circle->m_Transform->GetPosition().y);

	m_pEventSystem->SendEventMessage(EnumEvent::OnRender);
	m_pEventSystem->Update();

	m_pEngine->EndRender();
}

void GameManager::Finish()
{
	delete m_pEngine;
	delete m_pEventSystem;
}

LRESULT GameManager::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
