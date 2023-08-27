#include "pch.h"
#include "D2DGraphics.h"
#include "Vector2.h"
#include "Object.h"
#include "Component.h"
#include "Transform.h"
#include "Collider.h"
#include "CircleCollider.h"
#include "SpriteData.h"
#include "Sprite.h"
#include "GameObject.h"
#include "Debug.h"

CircleCollider::CircleCollider()
{
}

CircleCollider::CircleCollider(float _radius)
{
}

CircleCollider::~CircleCollider()
{
	printf("circle collider �Ҹ��� ȣ��\n");
}

void CircleCollider::OnRender()
{
	//�浹ó�� �׸��� ���̰� �������� ����
	if (m_CollderDraw == TRUE)
	{
		//�浹������ ������ ����
		if (m_isTrigger == true)
		{
			m_hColor = D2D1::ColorF::Red;
		}
		else
		{
			m_hColor = D2D1::ColorF::Green;
		}

		D2DGrahpics::GetInstance()->D2DXDrawCircle
		(
			this->m_GameObject->m_pTransform->m_Position.x,
			this->m_GameObject->m_pTransform->m_Position.y,
			m_radius * m_GameObject->m_pTransform->m_Scale.width,
			m_radius * m_GameObject->m_pTransform->m_Scale.height,
			m_hColor, D2D1::ColorF::Ivory
		);
	}
}

void CircleCollider::Release()
{
}

void CircleCollider::ToString()
{
}


void CircleCollider::Update()
{
	if (m_CollderInfo == TRUE)
	{

		Debug::LogFormat
		("�ݶ��̴��� ������ ǥ���մϴ� Left:%d | Top:%d | Right:%d | Bottom:%d |\n",
			(short)this->m_ColliderSize.left,
			(short)this->m_ColliderSize.top,
			(short)this->m_ColliderSize.right,
			(short)this->m_ColliderSize.bottom
		);

		D2DGrahpics::GetInstance()->D2DXDrawText
		(
			m_ColliderSize.left, m_ColliderSize.top, 100, 100,
			D2D1::ColorF::White,
			L"�ݶ��̴��� ������ ǥ���մϴ� Left:%d | Top:%d | Right:%d | Bottom:%d",
			(short)this->m_ColliderSize.left,
			(short)this->m_ColliderSize.top,
			(short)this->m_ColliderSize.right,
			(short)this->m_ColliderSize.bottom
		);

	}
}
