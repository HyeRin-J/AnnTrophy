#pragma once

class SystemClass;
class GameManager : public SingletonManager<GameManager>
{
public:
	int m_Result;
public:
	GameManager();
	~GameManager();
public:
	bool Initialize();
	bool BeginRender();
	bool Rendering();
	bool EndRender();
	bool Update();

	void Release();

private:
	SystemClass* m_System;
		

};

