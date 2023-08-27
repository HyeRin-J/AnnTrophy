#include "pch.h"
#include "D2DGraphics.h"
#include "Object.h"
#include "Component.h"
#include "SpriteData.h"
#include "Sprite.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "GameObject.h"
#include "Debug.h"

BoxCollider::BoxCollider()
{
}


BoxCollider::BoxCollider(float _left, float _top, float _right, float _bottom) : BoxCollider()
{
	m_ColliderSize.left = _left;
	m_ColliderSize.right = _top;
	m_ColliderSize.top = _right;
	m_ColliderSize.bottom = _bottom;
}

BoxCollider::~BoxCollider()
{
	printf("box collider 소멸자 호출\n");
}

void BoxCollider::OnRender()
{
	//충돌처리 그림을 보이게 해줄지의 여부
	if (m_CollderDraw == TRUE)
	{
		//충돌상태의 여부의 색상
		if (m_isTrigger == true)
		{
			m_hColor = D2D1::ColorF::Red;
		}
		else
		{
			m_hColor = D2D1::ColorF::Green;
		}

		D2DGrahpics::GetInstance()->D2DXDrawRectrangle
		(
			m_ColliderSize.left,
			m_ColliderSize.top,
			m_ColliderSize.right,
			m_ColliderSize.bottom,
			m_hColor, D2D1::ColorF::Ivory
		);
	}
	

}



void BoxCollider::Release()
{
}

void BoxCollider::ToString()
{
}


void BoxCollider::Update()
{
	if (m_CollderInfo == TRUE)
	{

		Debug::LogFormat
		("콜라이더의 정보를 표시합니다 Left:%d | Top:%d | Right:%d | Bottom:%d\n",
			(short)this->m_ColliderSize.left,
			(short)this->m_ColliderSize.top,
			(short)this->m_ColliderSize.right,
			(short)this->m_ColliderSize.bottom
		);

		D2DGrahpics::GetInstance()->D2DXDrawText
		(
			m_ColliderSize.left, m_ColliderSize.top, 100, 100,
			D2D1::ColorF::White,
			L"콜라이더의 정보를 표시합니다 Left:%d | Top:%d | Right:%d | Bottom:%d",
			(short)this->m_ColliderSize.left,
			(short)this->m_ColliderSize.top,
			(short)this->m_ColliderSize.right,
			(short)this->m_ColliderSize.bottom
		);

	}
}
