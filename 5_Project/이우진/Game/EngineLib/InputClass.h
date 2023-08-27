#pragma once
#ifdef _DEFINE
#include "DLL_Define .h"
const unsigned int MAX_KEYS = 256U;
#else
#include "DLL_Define .h"
const unsigned int MAX_KEYS = 256U;
#endif // _DEFINE



class InputClass
{
public:
	InputClass();
	InputClass(const InputClass&);
	~InputClass();
public:
	//void Initialize();
	//
	//void KeyDown(unsigned int);
	//void KeyUp(unsigned int);
	//
	//bool IsKeyDown(unsigned int);//현재 키가 눌려있는지 체크
private:
	bool m_keys[256];
public:
	bool* GetKey() { return m_keys; }
};

extern "C"
{
	MYDLL_DECLSPEC InputClass* CreateInputClass();
	MYDLL_DECLSPEC void  _InputInitialize(InputClass* );
	MYDLL_DECLSPEC void   _KeyDown(InputClass* ,unsigned int);
	MYDLL_DECLSPEC void   _KeyUp(InputClass*, unsigned int);
	MYDLL_DECLSPEC bool  _IsKeyDown(InputClass*, unsigned int);//현재 키가 눌려있는지 체크
}
