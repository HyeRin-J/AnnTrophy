#pragma once
#include "pch.h"
#include "SpriteData.h"
#include "SingletonManager.h"
#include "D2DGraphics.h"
#include "InputManager.h"


KeyState InputManager::mKeyStateArr[256];
D2D1_POINT_2F InputManager::MousePosScreen;
D2D1_POINT_2F InputManager::MousePosClient;

void InputManager::KeyUpdate()
{
	for (int index = 0; index < 255; index++)
	{
		mKeyStateArr[index].prev = mKeyStateArr[index].current;
		mKeyStateArr[index].current = HIWORD(GetAsyncKeyState(index));
	}
}

bool InputManager::InputKey(int vk)
{
	return mKeyStateArr[vk].current;
}

bool InputManager::InputKeyDown(int vk)
{
	return !mKeyStateArr[vk].prev && mKeyStateArr[vk].current;
}

bool InputManager::InputKeyUp(int vk)
{
	return mKeyStateArr[vk].prev && !mKeyStateArr[vk].current;
}

D2D1_POINT_2F InputManager::GetMousePos(HWND hwnd)
{
	POINT MousePosScreen;

	GetCursorPos(&MousePosScreen);

	//바로 현재 윈도우 핸들에 client area 좌표값으로 변환됨
	// 아래의 함수 가 실행되면 전체 스크린좌표 기준에서 client area 기준의 좌표로 변경됨
	ScreenToClient(hwnd, &MousePosScreen);

	RECT rc;

	GetClientRect(hwnd, &rc);

	return D2D1::Point2F((1920.f * MousePosScreen.x) / rc.right, (1080.f * MousePosScreen.y) / rc.bottom);
}


