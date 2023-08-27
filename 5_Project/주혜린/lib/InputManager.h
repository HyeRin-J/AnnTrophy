#pragma once

class InputManager : public SingletonManager<InputManager>
{
};

#define IsKeyDown(key)	GetAsyncKeyState(key) & 0x8000
#define IsKey(key)		GetAsyncKeyState(key) & 0x8001
#define IsKeyUp(key)	GetAsyncKeyState(key) & 0x0001
