#pragma once
#include "pch.h"
#include "SingletonManager.h"
#include "SpriteData.h"
#include "D2DGraphics.h"
#include "Object.h"
#include "Component.h"
#include "Vector.h"
#include "Transform.h"
#include "GameObject.h"
#include "Collider.h"
#include "ObjectManager.h"
#include "BoxCollider.h"
#include "Rigidbody.h"

BoxCollider::BoxCollider()
{

}

BoxCollider::~BoxCollider()
{
	//debug
#ifdef _DEBUG
	std::cout << "box collider 소멸자 호출\n";
#endif
}

void BoxCollider::SetRect(float _left, float _top, float _right, float _bottom)
{
	m_Size = { _right - _left, _bottom - _top };
	m_Center = { m_Size.width / 2, m_Size.height / 2 };
}

void BoxCollider::SetRect(D2D1_POINT_2F center, D2D1_SIZE_F size)
{
	m_Center = center;
	m_Size = size;
}

bool BoxCollider::IsCheckCrash(BoxCollider* _target)
{
	if (_target == nullptr)
	{
		return false;
	}

	D2D1_POINT_2F point = _target->m_GameObject->GetPos();

	if (fabs((point.x + _target->m_Center.x) - (m_GameObject->GetPos().x + m_Center.x)) < (_target->m_Size.width / 2 + m_Size.width / 2) &&
		fabs((point.y + _target->m_Center.y) - (m_GameObject->GetPos().y + m_Center.y)) < (_target->m_Size.height / 2 + m_Size.height / 2))
	{

		m_Target.push_back(_target);

		if (m_IsCrash == false)
		{
			m_CollisionStartPoint = m_GameObject->GetPos();
			m_CollisionStartPoint.x = (int)m_CollisionStartPoint.x;
			m_CollisionStartPoint.y = (int)m_CollisionStartPoint.y;

			float yPos = m_CollisionStartPoint.y;
			float yCurDist = m_CollisionStartPoint.y - (m_Target[0]->m_GameObject->GetPos().y + m_Target[0]->m_Center.y);
			float yDistance = (m_Size.height / 2 + m_Target[0]->m_Size.height / 2);

			if (fabs(yCurDist) < yDistance)
			{
				if (yCurDist < 0)
				{
					yPos = (m_Target[0]->m_Center.y - yDistance);
				}
				else
				{
					yPos = (m_Target[0]->m_Center.y + yDistance);
				}
			}
			m_CollisionStartPoint.y = yPos;
		}

		this->m_IsCrash = true;

		return true;
	}
	else
	{
		if (m_Target.size() == 0)
		{
			this->m_IsCrash = false;
		}

		return false;
	}
}

BoxCollider* BoxCollider::IsMovePossible(D2D1_POINT_2F point, D2D1_SIZE_F targetSize, float gravity)
{
	for (auto it : ObjectManager::GetInstance()->m_Objects)
	{
		//예외처리
		if (it == nullptr || it->GetStringTag().compare("Player") == 0 || it->GetStringTag().compare("Weapon") == 0) continue;

		for (auto _com : it->GetAllComponents())
		{
			BoxCollider* col = dynamic_cast<BoxCollider*>(_com);
			if (col != nullptr)
			{
				D2D1_POINT_2F targetPoint = it->GetPos();
				int x = abs((targetPoint.x + col->m_Center.x) - (int)point.x);
				int y = abs((targetPoint.y + col->m_Center.y) - (int)point.y);

				if (x <= col->m_Size.width / 2 && y < (col->m_Size.height / 2 + targetSize.height / 3))
				{
					return col;
				}
			}
		}
	}

	return nullptr;
}

BoxCollider* BoxCollider::IsMovePossibleByLine(D2D1_POINT_2F point, D2D1_SIZE_F targetSize, float gravity)
{
	for (auto it : ObjectManager::GetInstance()->m_Objects)
	{
		//예외처리
		if (it == nullptr || it->GetStringTag().compare("Player") == 0 || it->GetStringTag().compare("Weapon") == 0) continue;

		for (auto _com : it->GetAllComponents())
		{
			BoxCollider* col = dynamic_cast<BoxCollider*>(_com);
			if (col != nullptr)
			{
				D2D1_POINT_2F targetPoint = it->GetPos();

				int x = abs((targetPoint.x + col->m_Center.x) - (int)point.x);
				int y = abs((targetPoint.y + col->m_Center.y) - (int)point.y);

				if (x <= (col->m_Size.width / 2 + targetSize.width / 2) && y < (col->m_Size.height / 2 + targetSize.height / 3))
				{
					return col;
				}
			}
		}
	}
	return nullptr;
}

void BoxCollider::Update()
{
	m_Target.clear();
	for (auto it : ObjectManager::GetInstance()->m_Objects)
	{
		if (it == nullptr || m_GameObject == it) continue;
		//예외처리
		if (it != this->m_GameObject && m_GameObject->GetStringTag().compare(it->GetStringTag()))
		{
			bool isInIgnoreList = false;
			for (auto ignoreTag : m_IgnoreList)
			{
				if (ignoreTag.compare(it->GetStringTag()) == 0)
				{
					isInIgnoreList = true;
				}
			}
			if (isInIgnoreList == false)
			{
				for (auto _com : it->GetAllComponents())
				{
					BoxCollider* col = dynamic_cast<BoxCollider*>(_com);

					if (col != nullptr)
					{
						IsCheckCrash(col);
					}
				}
			}
		}
	}
}

void BoxCollider::OnRender()
{
	D2D1::ColorF::Enum m_hColor;

	D2D1_POINT_2F point = { (m_GameObject->GetPos().x + m_Center.x), (m_GameObject->GetPos().y + m_Center.y) };

	if (m_CollderDraw == TRUE)
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
#ifdef _DEBUG
		D2DGraphics::GetInstance()->D2DXDrawRectrangle
		(
			point.x - m_Size.width / 2,
			point.y - m_Size.height / 2,
			m_Size.width,
			m_Size.height,
			m_hColor, D2D1::ColorF::Ivory
		);
#endif
	}

	//debug
	if (m_CollderInfo == TRUE)
	{
#ifdef _DEBUG
		D2DGraphics::GetInstance()->D2DXDrawText
		(
			point.x, point.y, m_Size.width, m_Size.height,
			D2D1::ColorF::White,
			L"%d | %d | %d | %d",
			(short)(point.x - m_Size.width / 2),
			(short)(point.y - m_Size.height / 2),
			(short)m_Size.width,
			(short)m_Size.height
		);
#endif

	}
}
