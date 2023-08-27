//

#pragma once
#ifndef __INCLUDE
//link
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "D3D.lib")
//include
#include <d3d11.h>
#include <directxmath.h>
#else
//link
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "D3D.lib")
//include
#include <d3d11.h>
#include <directxmath.h>
#endif // __INCLUDE





class D3DClass
{
public:
	D3DClass();
	D3DClass(const D3DClass&);
	~D3DClass();



public:
	//MemberFunction
	bool Initialize(int screenWidth, int screenHeight, bool vsync, HWND hwnd, bool fullscreen, float screenDepth, float screenNear);
	void Shutdown();
	void BeginScene(float _red,  float _green, float _blue, float _alpha);
	void EndScene();

	
	//디바이스를 받는다.
	//디바이스의 기능을 2가지로 나뉘었기때문에 이렇게하는거라고 봄.
	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();

	//MatrixFunction
	void GetProjectionMatrix(DirectX::XMMATRIX&);
	void GetWorldMatrix(DirectX::XMMATRIX&);
	void GetOrthoMatrix(DirectX::XMMATRIX&);
	void GetVideoCardInfo(char*, int&);

private:
	//Member
	bool m_Vsync_enable;

	int m_VideoCardMemory;
	char m_VideoCardDesription[128];
	//Swapchain
	IDXGISwapChain* m_SwapChain;

	//Device
	ID3D11Device* m_Device;
	ID3D11DeviceContext* m_DeviceContext;
	//Rendertarget
	ID3D11RenderTargetView* m_RenderTargetView;

	//StancillBuffer
	ID3D11Texture2D* m_DepthStencillBuffer;
	ID3D11DepthStencilState* m_DepthStencillState;
	ID3D11DepthStencilView* m_DepthStencillView;

	ID3D11RasterizerState* m_rasterState;

	//XMMatrix
	DirectX::XMMATRIX m_ProjectionMatrix;
	DirectX::XMMATRIX m_WorldMatrix;
	DirectX::XMMATRIX m_OrthoMatrix;
};

