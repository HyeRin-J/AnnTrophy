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
	// Ű���� ���� �ʱ�ȭ(���������� ������)
	//m_Input->Initialize();

	_InputInitialize(m_Input);

	// �׷��� ������Ʈ�� �������ش�.
	//�� ��ü�� �� �������α׷��� ��� �׷���  ������ ó���� ���� ��.
	/*m_Graphics = new Graphics();
	if (m_Graphics == nullptr)
	{
		return false;
	}*/

	//CreateGraphics();
	// �׷��� ������Ʈ�� �ʱ�ȭ ���ش�.

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

	//��ǲ Ŭ������ �ʱ�ȭ�Ѵ�.
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
�� (run(����))�Լ��� �ش� �������α׷��� ����(��ӵ���) �׸��α� ������ ��� ó���� �����ϴ°��Դϴ�.
�������α׷��� ó���� frame�Լ����� �����մϴ�.

���� ������ ���� ���ȿ�
Windows �ý��� �޽��� Ȯ��
�ý��� �޽��� ó��
���μ��� ���� ���α׷� ����
����ڰ� ������ ó�� �߿� �������� ���� Ȯ��

*/

void SystemClass::Run()
{
	MSG msg;
	bool done, result;

	// �޼��� ����ü�� �ʱ�ȭ
	ZeroMemory(&msg, sizeof(MSG));

	// ����� Ȥ�� â(window)�� ���ᰡ �Է��� �Ǳ� ������ �޼��� ������ �ݺ��Ѵ�.
	done = false;

	while (!done)
	{
		// Handle the windows messages.
		// ����â�� ó�� �޼��� �Դϴ�.
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// ���� â�� �����ȣ�� �޾Ҵٸ� �� �������α׷��� �����մϴ�.
		if (msg.message == WM_QUIT)
		{
			done = true;
		}
		else
		{
			// �׷��� �ʴٸ� �������� ó���Ѵ�.
			result = Frame();
			//result = GraphicsFrame(m_Graphics);
			//���� ������ó���� ������ �߻��Ǹ� ���� �ڵ带 on��Ű�� �����Ѵ�.
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
		// Ű���忡�� ��� Ű�� ���ȴ��� üũ�Ѵ�.
	case WM_KEYDOWN:
	{
		// ���� Ű�� ��������  �ش� ���¸�(that state)�� ����� �� �ֵ��� �� �Է°�ü�� ������.(send it to the input object)
		//m_Input->KeyDown((unsigned int)wparam);
		_KeyDown(m_Input,(unsigned int)wparam);
		
		return 0;
	}

	// Ű�� ���������� Ȯ��
	case WM_KEYUP:
	{
		//m_Input->KeyUp((unsigned int)wparam);
		_KeyUp(m_Input,(unsigned int)wparam);
		return 0;
	}

	// ���� �ִ� �⺻ �޼��� ���� �ٸ� �Է��� �޾����� �� �޼����� ������� �ʰٴٴ¶�
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
	WNDCLASSEX wc;//������ Ŭ���� ����ü
	//������ ��� ����ü�ΰ� ����.
	DEVMODE dmScreenSettings;
	//�Ƹ� ������ ���� ��ġ ����?
	int posX = 0, posY = 0;


	//�� ��ü�� ���� �ܺ������͸� �����´�.
	ApplicationHandle = this;

	
	// GetModuleHandle = 
	//�Ķ���ͷ� ���ڿ��� �Է¹޴µ� �� ���ڿ��� ��Ⱚ�̵ȴ�.
	//��õ� ����Ī(lpModuleName)�� �ش��ϴ� ����� �ش� ���μ��� �ּҰ����� ����(mapping)�Ǿ�
	//�ִٸ� �ش� ����� �ڵ��� ��ȯ�Ѵ�.
	//��������(DLL,EXE)..�� Module�� ���� �������µ� ����ϴ� �Լ��̴�.
	//���ڸ� NULL�� ä��� �ڽ�(�ҽ��� �ۼ��ϰ� �ִ� ��)�� Module���� �������µ����� ���.

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

	// â Ŭ������ ����մϴ�.
	RegisterClassEx(&wc);

	// Ŭ���̾�Ʈ ����ũ�� ȭ���� �ػ󵵸� �����մϴ�
	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);


	// ��ü ȭ�� �Ǵ� â ��忡�� ���� ������ ���ο� ���� ȭ�� ������ �����մϴ�.
	if (FULL_SCREEN == true)
	{
		//��ü ȭ���� ǥ�õǸ� ȭ���� ����� ����ũ���� �ִ� ũ�� �� 32��Ʈ�� �����մϴ�.
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)screenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// ���÷��� ������ ��ü ȭ������ �����մϴ�
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		//â�� ��ġ�� ���� ��� �𼭸��� �����մϴ�.
		posX = posY = 0;
	}
	else
	{
		//â�� ��Ÿ���� 800x600 �ػ󵵷� �����մϴ�
		screenWidth = 800;
		screenHeight = 600;

		// â�� ȭ�� ����� �����ϴ�.
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
	// ���콺 Ŀ���� ǥ���մϴ�.
	ShowCursor(true);

	// ��ü ȭ�� ��带 ������ ��� ���÷��� ������ �����մϴ�.
	if (FULL_SCREEN == true)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	// â�� �����մϴ�.
	DestroyWindow(m_hwnd);
	m_hwnd = nullptr;

	//���� ���α׷� �ν��Ͻ�(����)�� �����մϴ�.
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