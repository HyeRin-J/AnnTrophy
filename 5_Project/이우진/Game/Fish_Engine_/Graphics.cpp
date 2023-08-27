#include "pch.h"
#include "Graphics.h"


/*
���� ù ��° ���� ������ Ŭ���� �������Դϴ�. 
���⿡���� ��� Ŭ���� �����Ϳ� ���������� �������� ������ 
�����͸� null�� �ʱ�ȭ�մϴ�.
*/
Graphics::Graphics() : m_Direct3D(nullptr)
{
	//�ʱ�ȭ�� ���� ������� visual studio���� �ʱ�ȭ�� �Ϸ��ϱ� ������
	//������ �߻��Ѵ�.
	//�� ������ �Ƹ��� �����Ⱚ�� ���°� ����.
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

�� ��° ���� ������ GraphicsClass ���� Initialize �Լ��Դϴ�. 
���⿡�� D3DClass ��ü�� ���� �� ���� D3DClass Initialize �Լ��� ȣ���մϴ�. 
�� �Լ��� ȭ�� �ʺ�, ȭ�� ����, â �ڵ� �� Graphicsclass.h 
������ �� ���� ���� ������ �����ϴ�. D3DClass���� ��� ������ ����Ͽ�
Direct3D �ý����� �����մϴ�. d3dclass.cpp ������ ���캸�� 
�̿� ���� �ڼ��� �����ϰڽ��ϴ�.



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
Frame �Լ��� ������Ʈ�Ǿ� ���� �� �����Ӹ��� Render �Լ��� ȣ���մϴ�.

*/
 bool GraphicsFrame(Graphics* _graphics)
{
	 bool result;
	 // Render the graphics scene.
	 result = GraphicsRender(_graphics);
	 //�������� �����ϰ�� �������� �Լ��� ��������ʰ� �ٷ� ����ϴ�.
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

�� Ŭ������ ������ ���� ������ Render �Լ��Դϴ�. 
ȭ���� ����Ÿ�� �ʱ�ȭ ���� D3D ��ü�� ȣ���մϴ�. 
�� �� EndScene�� ȣ���Ͽ� ȸ���� â�� ǥ�õǵ����մϴ�.


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
	//	 //m_Direct3D�� �˴ٿ� �Լ��� ȣ���մϴ�. 
	//	 m_Direct3D->Shutdown();
	//	 //�޸𸮸� �Ҵ��� �����ϰ� 
	//	 delete m_Direct3D;
	//	 //���� �ʱ�ȭ ���ݴϴ�. 
	//	 m_Direct3D = nullptr;
	// }
	// return;
 //}

 //bool Graphics::Frame()
 //{
	// bool result;
	// // Render the graphics scene.
	// result = Render();
	// //�������� �����ϰ�� �������� �Լ��� ��������ʰ� �ٷ� ����ϴ�.
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

