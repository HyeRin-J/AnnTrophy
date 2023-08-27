#pragma once

#ifndef _SYSTEMCLASS_H_
#define _SYSTEMCLASS_H_



#include <windows.h>

#include "Graphics.h"
#include "InputClass.h"
#include "FText.h"

#endif
class InputClass;

class SystemClass
{
public:
	SystemClass();
	SystemClass(const SystemClass&);
	~SystemClass();

	bool Initialize();
	void Shutdown();
	void Run();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);
private:
	bool Frame();
	void InitializeWindows(int&, int&);
	void ShutdownWindows();

private:
	LPCWSTR m_applicationName;
	HINSTANCE m_hinstance;
	HWND m_hwnd;

	InputClass* m_Input;

	Graphics* m_Graphics;
};

static SystemClass* ApplicationHandle = 0;

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
