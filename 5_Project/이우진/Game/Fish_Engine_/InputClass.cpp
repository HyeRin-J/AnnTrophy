#include "pch.h"
#include "InputClass.h"

InputClass::InputClass()
{
#ifdef _DEBUG
	std::cout << "CreaterInputClass" << std::endl;
#endif 
	ZeroMemory(m_keys, sizeof(m_keys));
}
InputClass::InputClass(const InputClass&)
{
#ifdef _DEBUG
	std::cout << "CopyCreaterInputClass" << std::endl;
#endif 
	ZeroMemory(m_keys, sizeof(m_keys));
}
InputClass::~InputClass()
{
#ifdef _DEBUG
	std::cout << "DeleteCreaterInputClass" << std::endl;
#endif 
}


InputClass* CreateInputClass()
{
#ifdef _DEBUG
	std::cout << "ReturntClass" << std::endl;
#endif 

	return new InputClass();
}

/*
Input 클래스는 사용자의 키보드 입력을 처리합니다. 이
클래스는 SystemClass::MessageHandler 함수에서 입력을 받습니다.
입력 객체는 키보드의 모든 키에 대한 상태를 가지고 있습니다.
*/
void  _InputInitialize(InputClass* _Input)
{
	for (int index = 0; index < MAX_KEYS; index++)
	{
		_Input->GetKey()[index] = false;
	}

	return ;
}

void  _KeyDown(InputClass* _Input, unsigned int _keyIndex)
{
	// If a key is pressed then save that state in the key array.
	//만약 어떤 키가 눌렸을때 그 키를 눌렀다 라고 해당 배열에 저장해줍니다.
	_Input->GetKey()[_keyIndex] = true;
	return ;
}

void  _KeyUp(InputClass* _Input, unsigned int _keyIndex)
{
	//키가 초기화 된경우의 그 배열의 상태를 지웁니다.
	_Input->GetKey()[_keyIndex] = false;
	return ;
}

bool  _IsKeyDown(InputClass* _Input, unsigned int _keyIndex)
{
	//반환값으로 키의상태가 눌렸는지 아닌지를 반환합니다.
	return _Input->GetKey()[_keyIndex]; //m_keys[_keyIndex];
}
