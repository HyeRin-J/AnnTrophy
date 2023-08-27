#pragma once
/*
WinMain , D2D 초기 세팅 하는 곳
*/

template<class Interface>
inline void SafeRelease(
	Interface** ppInterfaceToRelease
)
{
	if (*ppInterfaceToRelease != NULL)
	{
		(*ppInterfaceToRelease)->Release();

		(*ppInterfaceToRelease) = NULL;
	}
}


#ifndef Assert
#if defined( DEBUG ) || defined( _DEBUG )
#define Assert(b) do {if (!(b)) {OutputDebugStringA("Assert: " #b "\n");}} while(0)
#else
#define Assert(b)
#endif //DEBUG || _DEBUG
#endif



#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif

class AppManager : public SingletonManager<AppManager>
{
private:
	//main
	//FAudio* m_SoundTrack; // soundManaging
public:
	HWND m_hwnd;

	AppManager();
	~AppManager();


	// Register the window class and call methods for instantiating drawing resources
	HRESULT Initialize();
	// Process and dispatch messages
	void RunMessageLoop();
	// Release device-dependent resource.
	

protected:

	static LRESULT CALLBACK WndProc(
		HWND hWnd,
		UINT message,
		WPARAM wParam,
		LPARAM lParam
	);
	
	// Resize the render target.
	void OnResize(UINT width, UINT height);
	// The windows procedure.

};
