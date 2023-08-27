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
	Debug::Log("circle collider 기본 생성자 호출\n");
#endif
}

CircleCollider::CircleCollider(float _radius)
{
#ifdef _DEBUG
	Debug::Log("circle collider 생성자 호출\n");
#endif
	m_radius = _radius;
}

CircleCollider::~CircleCollider()
{
#ifdef _DEBUG
	Debug::Log("circle collider 소멸자 호출\n");
#endif
}
bool CircleCollider::IsCheckCrash(CircleCollider* _target)
{
	if (_target == nullptr)
	{
		return false;
	}
	//마지막에 비교한 충돌체의 거리값을 비교 후에 넣는다.
	float dis = Vector2::Distance
	(
		this->m_GameObject->GetPos().x,
		this->m_GameObject->GetPos().y,
		_target->m_GameObject->GetPos().x,
		_target->m_GameObject->GetPos().y
	);
	
	//충돌처리
	Rigidbody* rb = m_GameObject->GetComponent<Rigidbody>();

	//거리값이랑 원의 지름이랑 비교
	if (dis <= this->m_radius + _target->m_radius)
	{
		//일정영역에 도달하면 충돌!
		//printf("충돌범위 안 : dis : %f.1\n", dis);
		//Debug::LogFormat("%s 써클 충돌 범위 안 : dis :%f.1\n ", (this->m_GameObject->GetStringName().c_str()) , (short)dis);
#ifdef _DEBUG
		std::cout << m_GameObject->GetStringName().c_str() << " Crash"<<std::endl;
#endif
		//서로가 충돌했다는 플래그를 설정
		this->m_IsCrash = true;

		if (rb != nullptr)
		{
			rb->Reflect(_target, true);
		}

	}
	else
	{
		//Debug::LogFormat("%s 충돌 범위 밖 : dis :%f.1\n ", this->m_GameObject->GetStringName(), dis);
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

	//충돌처리 그림을 보이게 해줄지의 여부
	if (m_CollderDraw == true)
	{
		//충돌상태의 여부의 색상
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

	//Dubug 용
	if (m_CollderInfo == TRUE)
	{
#ifdef _DEBUG
		D2DGraphics::GetInstance()->D2DXDrawText
		(
			this->m_GameObject->GetPos().x, this->m_GameObject->GetPos().y -15, 100, 100,
			D2D1::ColorF::White,
			L"콜라이더의 정보를 표시합니다 POINT = {%d , %d}",
			(short)this->m_GameObject->GetPos().x,
			(short)this->m_GameObject->GetPos().y
			
		);
		D2DGraphics::GetInstance()->D2DXDrawText
		(
			this->m_GameObject->GetPos().x, this->m_GameObject->GetPos().y, 100, 100,
			D2D1::ColorF::White,
			L"콜라이더의 정보를 표시합니다 Left:%d | Top:%d | Right:%d | Bottom:%d",
			(short)sizeLeft,
			(short)sizeTop,
			(short)sizeRight,
			(short)sizeBottom
		);
#endif
	}

}


