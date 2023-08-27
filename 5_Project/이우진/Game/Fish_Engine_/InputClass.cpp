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
Input Ŭ������ ������� Ű���� �Է��� ó���մϴ�. ��
Ŭ������ SystemClass::MessageHandler �Լ����� �Է��� �޽��ϴ�.
�Է� ��ü�� Ű������ ��� Ű�� ���� ���¸� ������ �ֽ��ϴ�.
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
	//���� � Ű�� �������� �� Ű�� ������ ��� �ش� �迭�� �������ݴϴ�.
	_Input->GetKey()[_keyIndex] = true;
	return ;
}

void  _KeyUp(InputClass* _Input, unsigned int _keyIndex)
{
	//Ű�� �ʱ�ȭ �Ȱ���� �� �迭�� ���¸� ����ϴ�.
	_Input->GetKey()[_keyIndex] = false;
	return ;
}

bool  _IsKeyDown(InputClass* _Input, unsigned int _keyIndex)
{
	//��ȯ������ Ű�ǻ��°� ���ȴ��� �ƴ����� ��ȯ�մϴ�.
	return _Input->GetKey()[_keyIndex]; //m_keys[_keyIndex];
}
