#include "pch.h"
#include "Graphics.h"


/*
따라서 첫 번째 변경 사항은 클래스 생성자입니다. 
여기에서는 모든 클래스 포인터와 마찬가지로 안전상의 이유로 
포인터를 null로 초기화합니다.
*/
Graphics::Graphics() : m_Direct3D(nullptr)
{
	//초기화를 하지 않을경우 visual studio에서 초기화를 하려하기 때문에
	//문제가 발생한다.
	//그 문제는 아마도 쓰레기값이 들어가는것 같다.
}


Graphics* CreateGraphics()
{
#ifdef _DEBUG
	std::cout << "CreateGraphicsClass" << std::endl;
#endif 
	return new Graphics();
}

/*
The second change is in the Initialize function inside the GraphicsClass.
Here we create the D3DClass object and then call the D3DClass Initialize function.
We send this function the screen width, screen height,
handle to the window, and the four global variables from the Graphicsclass.h file.
The D3DClass will use all these variables to setup the Direct3D system.
We'll go into more detail about that once we look at the d3dclass.cpp file.

두 번째 변경 사항은 GraphicsClass 내의 Initialize 함수입니다. 
여기에서 D3DClass 객체를 생성 한 다음 D3DClass Initialize 함수를 호출합니다. 
이 함수에 화면 너비, 화면 높이, 창 핸들 및 Graphicsclass.h 
파일의 네 가지 전역 변수를 보냅니다. D3DClass는이 모든 변수를 사용하여
Direct3D 시스템을 설정합니다. d3dclass.cpp 파일을 살펴보면 
이에 대해 자세히 설명하겠습니다.



*/

 bool GraphicsInitialize(Graphics* _graphics,int _screenWidth, int _screenHeight, HWND _hwnd)
{
	 bool result;

	 if (_graphics->GetDirect3DObject() == nullptr)
	 {
		 return false;
	 }
	 // Initialize the Direct3D object.
	 result = _graphics->GetDirect3DObject()->Initialize
	 (_screenWidth, _screenHeight, VSYNC_ENABLED, _hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);

	 if (result == false)
	 {
		 MessageBox(_hwnd, _T("Could Not Initialize Direct3D"), _T("Error"), MB_OK);
		 return false;
	 }
	 return true;

}

 void GraphicsShutdown(Graphics* _graphics)
 {
	 if (_graphics != nullptr)
	 {
		 if (_graphics->GetDirect3DObject() != nullptr)
		 {
			 _graphics->GetDirect3DObject()->Shutdown();
			 _aligned_free(_graphics->GetDirect3DObject());
			// delete _graphics->GetDirect3DObject();
			 //_graphics->SetD3DObject(nullptr);
		 }
		
		 delete _graphics;
		 _graphics = nullptr;

		 return;
	 }
	 return;
}
 /*
The Frame function has been updated so that it now 
calls the Render function each frame.
Frame 함수가 업데이트되어 이제 각 프레임마다 Render 함수를 호출합니다.

*/
 bool GraphicsFrame(Graphics* _graphics)
{
	 bool result;
	 // Render the graphics scene.
	 result = GraphicsRender(_graphics);
	 //렌더링의 거짓일경우 프레임을 함수를 사용하지않고 바로 종료니다.
	 if (!result)
	 {
		 return false;
	 }

	 return true;
}
 /*
The final change to this class is in the Render function.
We call the m_Direct3D object to clear the screen to a Magenta color.
After that we call EndScene so that the grey color is presented to the window.

이 클래스의 마지막 변경 사항은 Render 함수입니다. 
화면을 마젠타로 초기화 위해 D3D 개체를 호출합니다. 
그 후 EndScene을 호출하여 회색이 창에 표시되도록합니다.


*/
 bool GraphicsRender(Graphics* _graphics)
{
	 // Clear the buffers to begin the scene.
	 _graphics->GetDirect3DObject()->BeginScene(1.0f, 0.0f, 1.0f, 1.0f);


	 // Present the rendered scene to the screen.
	 _graphics->GetDirect3DObject()->EndScene();

	return true;
}





 //bool Graphics::Initialize(int _screenWidth, int _screenHeight, HWND _hwnd)
 //{
	// bool result;
	// // Create the Direct3D object.
	// //if (!m_Direct3D )

	// m_Direct3D = new D3DClass();
	// if (m_Direct3D == nullptr)
	// {
	//	 return false;
	// }
	// // Initialize the Direct3D object.
	// result = m_Direct3D->Initialize
	// (_screenWidth, _screenHeight, VSYNC_ENABLED, _hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);

	// if (result == false)
	// {
	//	 MessageBox(_hwnd, _T("Could Not Initialize Direct3D"), _T("Error"), MB_OK);
	//	 return false;
	// }
	// return true;

 //}
 ///*
 //The next change is in the Shutdown function in the GraphicsClass.
 //Shut down of all graphics objects occur here so we have placed the D3DClass shutdown in this function.
 //Note that I check to see if the pointer was initialized or not.
 //If it wasn't we can assume it was never set up and not try to shut it down.
 //That is why it is important to set all the pointers to null in the class constructor.
 //If it does find the pointer has been initialized then it will attempt to shut down the
 //D3DClass and then clean up the pointer afterwards.

 
 //void Graphics::Shutdown()
 //{
	// // Release the Direct3D object.
	// if (m_Direct3D != nullptr)
	// {
	//	 //m_Direct3D의 셧다운 함수를 호출합니다. 
	//	 m_Direct3D->Shutdown();
	//	 //메모리를 할당을 해제하고 
	//	 delete m_Direct3D;
	//	 //값을 초기화 해줍니다. 
	//	 m_Direct3D = nullptr;
	// }
	// return;
 //}

 //bool Graphics::Frame()
 //{
	// bool result;
	// // Render the graphics scene.
	// result = Render();
	// //렌더링의 거짓일경우 프레임을 함수를 사용하지않고 바로 종료니다.
	// if (!result)
	// {
	//	 return false;
	// }

	// return true;
 //}

 //bool Graphics::Render()
 //{
	// // Clear the buffers to begin the scene.
	// m_Direct3D->BeginScene(0.5f, 0.5f, 0.5f, 1.0f);


	// // Present the rendered scene to the screen.
	// m_Direct3D->EndScene();

	// return true;
 //}

