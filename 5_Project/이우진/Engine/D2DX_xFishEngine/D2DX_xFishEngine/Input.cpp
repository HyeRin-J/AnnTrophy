#include "pch.h"
#include "framework.h"
#include "SingletonManager.h"
#include "Input.h"

Input::Input()
{
}

Input::~Input()
{
}

void Input::Awake()
{
	Debug::LogFormat("��ǲ�� �����մϴ�");
}

void Input::Update()
{

	m_GameObject->m_pTransform;
	Vector2 _vector2;
	_vector2.x = 0.f;
	_vector2.y = 0.f;

	if (IsKey(VK_LEFT) & 0x8000)
	{
		Debug::LogFormat("���ʹ���");
		//_vector2.x -= 5;
		m_GameObject->m_pTransform->m_Position.x -= 5;
	}
	else if (IsKey(VK_RIGHT) & 0x8000)
	{
		Debug::LogFormat("�����ʹ���");
		//_vector2.x += 5;
		m_GameObject->m_pTransform->m_Position.x += 5;
	}
	else if (IsKey(VK_UP) & 0x8000)
	{
		Debug::LogFormat("���ʹ���");
		//_vector2.y -= 5;
		m_GameObject->m_pTransform->m_Position.y -= 5;
	}
	else if (IsKey(VK_DOWN) & 0x8000)
	{
		Debug::LogFormat("�Ʒ��ʹ���");
		//_vector2.y += 5;
		m_GameObject->m_pTransform->m_Position.y += 5;
	}
	

	//_vector2 *= 10;

	//m_GameObject->m_pTransform->Translate(_vector2);


	
	
}
