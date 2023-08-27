#include "GamePch.h"

#include "SystemClass.h"
#include "../EngineLib/InputClass.h"
#include "../EngineLib/InputClass.cpp"

SystemClass::SystemClass()
{
 	m_hinstance = nullptr;
 	m_hwnd = nullptr;
 	m_Graphics = nullptr;
 	m_Input = nullptr;
 	m_applicationName = _T("Muyaho~");
}

SystemClass::SystemClass(const SystemClass&)
{
	m_hinstance = nullptr;
	m_hwnd = nullptr;
	m_Graphics = nullptr;
	m_Input = nullptr;
	m_applicationName = _T("Muyaho~");
}

SystemClass::~SystemClass()
{
}

bool SystemClass::Initialize()
{
	int screenWidth, screenHeight;
	bool result;

	/*
	Initialize the width and height of the screen to zero 
	before sending the variables into the function.
	*/
	screenWidth = 0;
	screenHeight = 0;

	// Initialize the windows api.
	InitializeWindows(screenWidth, screenHeight);

	// Create the input object.  
	//This object will be used to handle reading the keyboard input from the user.
	m_Input = new InputClass();

	if (m_Input == nullptr)
	{
		return false;
	}
	// 키값을 전부 초기화(눌리지않은 것으로)
	//m_Input->Initialize();

	_InputInitialize(m_Input);

	// 그래픽 오브젝트를 생성해준다.
	//이 객체는 이 응용프로그램의 모든 그래픽  렌더링 처리에 대한 것.
	/*m_Graphics = new Graphics();
	if (m_Graphics == nullptr)
	{
		return false;
	}*/

	//CreateGraphics();
	// 그래픽 오브젝트를 초기화 해준다.

	m_Graphics = CreateGraphics();

	result = m_Graphics->GetDirect3DObject();

	if (m_Graphics->GetDirect3DObject() == nullptr)
	{
		return false;
	}

	result = GraphicsInitialize(m_Graphics, screenWidth, screenHeight, m_hwnd);

	if (result == false)
	{
		return false;
	}

	return true;
}

void SystemClass::Shutdown()
{
	// Release the graphics object.
	if (m_Graphics != nullptr)
	{
		//m_Graphics->Shutdown();
		GraphicsShutdown(m_Graphics);
		/*delete m_Graphics;
		m_Graphics = nullptr;*/
	}

	//인풋 클래스를 초기화한다.
	if (m_Input != nullptr)
	{
		delete m_Input;
		m_Input = nullptr;
	}

	// Shutdown the window.
	ShutdownWindows();

	return;
}
/*
이 (run(실행))함수는 해당 응용프로그램이 루프(계속돌고) 그만두기 전까지 모든 처리를 수행하는곳입니다.
응용프로그래밍 처리는 frame함수에서 수행합니다.

아직 끝나지 않은 동안에
Windows 시스템 메시지 확인
시스템 메시지 처리
프로세스 응용 프로그램 루프
사용자가 프레임 처리 중에 종료할지 여부 확인

*/

void SystemClass::Run()
{
	MSG msg;
	bool done, result;

	// 메세지 구조체를 초기화
	ZeroMemory(&msg, sizeof(MSG));

	// 사용자 혹은 창(window)의 종료가 입력이 되기 전까지 메세지 루프를 반복한다.
	done = false;

	while (!done)
	{
		// Handle the windows messages.
		// 현재창의 처리 메세지 입니다.
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// 만약 창이 종료신호를 받았다면 이 응용프로그램을 종료합니다.
		if (msg.message == WM_QUIT)
		{
			done = true;
		}
		else
		{
			// 그렇지 않다면 프레임을 처리한다.
			result = Frame();
			//result = GraphicsFrame(m_Graphics);
			//만약 프레임처리중 에러가 발생되면 종료 코드를 on시키고 종료한다.
			if (result == false)
			{
				done = true;
			}
		}

	}

	return;
}

LRESULT SystemClass::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	switch (umsg)
	{
		// 키보드에서 어떠한 키가 눌렸는지 체크한다.
	case WM_KEYDOWN:
	{
		// 만약 키를 눌렀을때  해당 상태를(that state)를 기록할 수 있도록 그 입력객체로 보낸다.(send it to the input object)
		//m_Input->KeyDown((unsigned int)wparam);
		_KeyDown(m_Input,(unsigned int)wparam);
		
		return 0;
	}

	// 키가 때어졌는지 확인
	case WM_KEYUP:
	{
		//m_Input->KeyUp((unsigned int)wparam);
		_KeyUp(m_Input,(unsigned int)wparam);
		return 0;
	}

	// 여기 있는 기본 메세지 외의 다른 입력을 받았을때 그 메세지를 사용하지 않겟다는뜻
	default:
	{
		return DefWindowProc(hwnd, umsg, wparam, lparam);
	}
	}
}

/*
The following Frame function is where all the processing for our application is done.
So far it is fairly simple, we check the input object to see if the user has pressed escape 
and wants to quit. If they don't want to quit then we call the graphics object to do its 
frame processing which will render the graphics for that frame. 
As the application grows we'll place more code inside here.
*/
bool SystemClass::Frame()
{
	bool result;


	// Check if the user pressed escape and wants to exit the application.
	//if (m_Input->IsKeyDown(VK_ESCAPE))
	if (_IsKeyDown(m_Input,VK_ESCAPE))
	{
		return false;
	}

	// Do the frame processing for the graphics object.
	result = GraphicsFrame(m_Graphics);
	//result = Frame();
	if (!result)
	{
		return false;
	}

	return true;
}
#include "Resource.h"

void SystemClass::InitializeWindows(int& screenWidth, int& screenHeight)
{
	WNDCLASSEX wc;//윈도우 클래스 구조체
	//개발자 모드 구조체인것 같다.
	DEVMODE dmScreenSettings;
	//아마 윈도우 생성 위치 변수?
	int posX = 0, posY = 0;


	//이 객체에 대한 외부포인터를 가져온다.
	ApplicationHandle = this;

	
	// GetModuleHandle = 
	//파라미터로 문자열을 입력받는데 이 문자열은 모듈값이된다.
	//명시된 모듈명칭(lpModuleName)에 해당하는 모듈이 해당 프로세스 주소공간에 연결(mapping)되어
	//있다면 해당 모듈의 핸들을 반환한다.
	//실행파일(DLL,EXE)..등 Module의 값을 가져오는데 사용하는 함수이다.
	//인자를 NULL로 채우면 자신(소스를 작성하고 있는 곳)의 Module값을 가져오는데에도 사용.

	//  
	m_hinstance = GetModuleHandle(NULL);

	// Give the application a name.
	m_applicationName = _T("Engine");


	// Setup the windows class with default settings.
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hinstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	// 창 클래스를 등록합니다.
	RegisterClassEx(&wc);

	// 클라이언트 데스크톱 화면의 해상도를 결정합니다
	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);


	// 전체 화면 또는 창 모드에서 실행 중인지 여부에 따라 화면 설정을 설정합니다.
	if (FULL_SCREEN == true)
	{
		//전체 화면이 표시되면 화면을 사용자 데스크톱의 최대 크기 및 32비트로 설정합니다.
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)screenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// 디스플레이 설정을 전체 화면으로 변경합니다
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		//창의 위치를 왼쪽 상단 모서리로 설정합니다.
		posX = posY = 0;
	}
	else
	{
		//창이 나타나면 800x600 해상도로 설정합니다
		screenWidth = 800;
		screenHeight = 600;

		// 창을 화면 가운데에 놓습니다.
		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
	}

	// Create the window with the screen settings and get the handle to it.
	m_hwnd = CreateWindowExW(WS_EX_APPWINDOW, m_applicationName, m_applicationName,
		WS_VISIBLE|WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
		posX, posY, screenWidth, screenHeight, NULL, NULL, m_hinstance, NULL);

	// Bring the window up on the screen and set it as main focus.
	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);

	// Hide the mouse cursor.
	ShowCursor(false);

	return;
}




void SystemClass::ShutdownWindows()
{
	// 마우스 커서를 표시합니다.
	ShowCursor(true);

	// 전체 화면 모드를 종료할 경우 디스플레이 설정을 수정합니다.
	if (FULL_SCREEN == true)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	// 창을 제거합니다.
	DestroyWindow(m_hwnd);
	m_hwnd = nullptr;

	//응용 프로그램 인스턴스(상태)를 제거합니다.
	UnregisterClass(m_applicationName, m_hinstance);
	m_hinstance = nullptr;

	// Release the pointer to this class.
	ApplicationHandle = nullptr;

	return;
}
/*
The WndProc function is where windows sends its messages to.
You'll notice we tell windows the name of it when we initialize the window class with
wc.lpfnWndProc = WndProc in the InitializeWindows function above. I included it in
this class file since we tie it directly into the system class by having it send all the messages
to the MessageHandler function defined inside SystemClass. This allows us to hook the messaging
functionality straight into our class and keep the code clean.


*/


LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch (umessage)
	{
		// Check if the window is being destroyed.
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}

	// Check if the window is being closed.
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		return 0;
	}

	// All other messages pass to the message handler in the system class.
	default:
	{
		return ApplicationHandle->MessageHandler(hwnd, umessage, wparam, lparam);
	}
	}
}