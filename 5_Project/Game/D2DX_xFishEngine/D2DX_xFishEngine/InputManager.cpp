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

	//�ٷ� ���� ������ �ڵ鿡 client area ��ǥ������ ��ȯ��
	// �Ʒ��� �Լ� �� ����Ǹ� ��ü ��ũ����ǥ ���ؿ��� client area ������ ��ǥ�� �����
	ScreenToClient(hwnd, &MousePosScreen);

	RECT rc;

	GetClientRect(hwnd, &rc);

	return D2D1::Point2F((1920.f * MousePosScreen.x) / rc.right, (1080.f * MousePosScreen.y) / rc.bottom);
}


