#pragma once

class KeyState
{
public:
	KeyState() : current(false), prev(false) {};
	~KeyState() {};

public:
	bool current;
	bool prev;
};

class InputManager
{
private:
	static KeyState mKeyStateArr[256];

	//update 필요
	static D2D1_POINT_2F MousePosScreen;
	static D2D1_POINT_2F MousePosClient;

public:
	static void KeyUpdate();
	static bool InputKey(int vk);
	static bool InputKeyDown(int vk);
	static bool InputKeyUp(int vk);

	//update 필요
	static D2D1_POINT_2F GetMousePos(HWND hwnd);
};

