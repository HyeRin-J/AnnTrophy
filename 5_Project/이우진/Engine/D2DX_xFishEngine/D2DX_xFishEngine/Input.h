#pragma once

#define IsKeyDown(key)	GetAsyncKeyState(key) & 0x8000
#define IsKey(key)		GetAsyncKeyState(key) & 0x8001
#define IsKeyUp(key)	GetAsyncKeyState(key) & 0x0001


class Input :public Component
{
public:
	Input();
	~Input();
public:
	virtual void Awake();
	virtual void Update();
};

