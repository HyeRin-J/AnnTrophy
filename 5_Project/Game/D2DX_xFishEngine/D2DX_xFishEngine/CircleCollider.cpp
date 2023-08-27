#include "pch.h"
#include "Vector.h"
#include "SingletonManager.h"
#include "SpriteData.h"
#include "D2DGraphics.h"
#include "Object.h"
#include "Component.h"
#include "Transform.h"
#include "GameObject.h"
#include "Collider.h"
#include "ObjectManager.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "Rigidbody.h"
#include "Debug.h"

CircleCollider::CircleCollider()
{
#ifdef _DEBUG
	Debug::Log("circle collider �⺻ ������ ȣ��\n");
#endif
}

CircleCollider::CircleCollider(float _radius)
{
#ifdef _DEBUG
	Debug::Log("circle collider ������ ȣ��\n");
#endif
	m_radius = _radius;
}

CircleCollider::~CircleCollider()
{
#ifdef _DEBUG
	Debug::Log("circle collider �Ҹ��� ȣ��\n");
#endif
}
bool CircleCollider::IsCheckCrash(CircleCollider* _target)
{
	if (_target == nullptr)
	{
		return false;
	}
	//�������� ���� �浹ü�� �Ÿ����� �� �Ŀ� �ִ´�.
	float dis = Vector2::Distance
	(
		this->m_GameObject->GetPos().x,
		this->m_GameObject->GetPos().y,
		_target->m_GameObject->GetPos().x,
		_target->m_GameObject->GetPos().y
	);
	
	//�浹ó��
	Rigidbody* rb = m_GameObject->GetComponent<Rigidbody>();

	//�Ÿ����̶� ���� �����̶� ��
	if (dis <= this->m_radius + _target->m_radius)
	{
		//���������� �����ϸ� �浹!
		//printf("�浹���� �� : dis : %f.1\n", dis);
		//Debug::LogFormat("%s ��Ŭ �浹 ���� �� : dis :%f.1\n ", (this->m_GameObject->GetStringName().c_str()) , (short)dis);
#ifdef _DEBUG
		std::cout << m_GameObject->GetStringName().c_str() << " Crash"<<std::endl;
#endif
		//���ΰ� �浹�ߴٴ� �÷��׸� ����
		this->m_IsCrash = true;

		if (rb != nullptr)
		{
			rb->Reflect(_target, true);
		}

	}
	else
	{
		//Debug::LogFormat("%s �浹 ���� �� : dis :%f.1\n ", this->m_GameObject->GetStringName(), dis);
		this->m_IsCrash = false;
	
		if (rb != nullptr)
		{
			rb->Reflect(_target);
		}
	}

	


	return false;
}
void CircleCollider::Update()
{
	
	for (auto it : ObjectManager::GetInstance()->m_Objects)
	{

		if (it == nullptr) continue;

		if (it != this->m_GameObject && it->GetStringTag().compare(m_GameObject->GetStringTag()) != 0)
		{
			IsCheckCrash(it->GetComponent<CircleCollider>());
		}
	}
}
	

void CircleCollider::OnRender()
{

	D2D1::ColorF::Enum m_hColor;

	//�浹ó�� �׸��� ���̰� �������� ����
	if (m_CollderDraw == true)
	{
		//�浹������ ������ ����
		if (m_IsCrash == true)
		{
			m_hColor = D2D1::ColorF::Red;
		}
		else
		{
			m_hColor = D2D1::ColorF::Green;
		}

		D2DGraphics::GetInstance()->D2DXDrawCircle
		(
			this->m_GameObject->GetPos().x,
			this->m_GameObject->GetPos().y,
			m_radius,
			m_radius,
			m_hColor, D2D1::ColorF::Ivory
		);
	}

	float sizeLeft = this->m_GameObject->GetPos().x - m_radius;
	float sizeTop = this->m_GameObject->GetPos().y - m_radius;
	float sizeRight = this->m_GameObject->GetPos().x + m_radius;
	float sizeBottom = this->m_GameObject->GetPos().y + m_radius;

	//Dubug ��
	if (m_CollderInfo == TRUE)
	{
#ifdef _DEBUG
		D2DGraphics::GetInstance()->D2DXDrawText
		(
			this->m_GameObject->GetPos().x, this->m_GameObject->GetPos().y -15, 100, 100,
			D2D1::ColorF::White,
			L"�ݶ��̴��� ������ ǥ���մϴ� POINT = {%d , %d}",
			(short)this->m_GameObject->GetPos().x,
			(short)this->m_GameObject->GetPos().y
			
		);
		D2DGraphics::GetInstance()->D2DXDrawText
		(
			this->m_GameObject->GetPos().x, this->m_GameObject->GetPos().y, 100, 100,
			D2D1::ColorF::White,
			L"�ݶ��̴��� ������ ǥ���մϴ� Left:%d | Top:%d | Right:%d | Bottom:%d",
			(short)sizeLeft,
			(short)sizeTop,
			(short)sizeRight,
			(short)sizeBottom
		);
#endif
	}

}


