#pragma once

#ifdef _DEFINE
#include "DLL_Define.h"
#else
#include "DLL_Define.h"
#endif // _DEFINE

#ifdef _DEBUG
#include "D3DClass.h"
#endif // _DEBUG

// GLOBALS //
//公具龋~ 公具龋~ 公具龋~ 公具龋~ 公具龋~ 公具龋~ 公具龋~ 公具龋~ 公具龋~
// 公具龋~ 公具龋~ 公具龋~ 公具龋~ 公具龋~ 公具龋~ 公具龋~ 公具龋~ 公具龋~
//公具龋~ 公具龋~ 公具龋~ 公具龋~ 公具龋~ 公具龋~ 公具龋~ 公具龋~ 公具龋~
// 公具龋~ 公具龋~ 公具龋~ 公具龋~ 公具龋~ 公具龋~ 公具龋~ 公具龋~ 公具龋~
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

class Graphics
{
public:
	Graphics();

	
private:
	D3DClass* m_Direct3D;
public:
	D3DClass* GetDirect3DObject()
	{
		if (m_Direct3D == nullptr)
		{
			//m_Direct3D = new D3DClass();
			m_Direct3D = (D3DClass*)_aligned_malloc(sizeof(D3DClass), 16);
		}
		return m_Direct3D;
	};
	void SetD3DObject(D3DClass* _v) { m_Direct3D = _v; }
};

extern "C"
{
	MYDLL_DECLSPEC Graphics* CreateGraphics();
	MYDLL_DECLSPEC bool GraphicsInitialize(Graphics* _graphics,int, int, HWND);
	MYDLL_DECLSPEC void GraphicsShutdown(Graphics* _graphics);
	MYDLL_DECLSPEC bool GraphicsFrame(Graphics* _graphics);

	MYDLL_DECLSPEC bool GraphicsRender(Graphics* _graphics);
}