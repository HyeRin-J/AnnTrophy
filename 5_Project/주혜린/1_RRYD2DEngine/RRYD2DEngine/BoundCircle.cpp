#include "pch.h"
#include "SingletonManager.h"
#include "SpriteData.h"
#include "RRYD2DEngine.h"
#include "ObjectManager.h"
#include "Object.h"
#include "GameObject.h"
#include "Component.h"
#include "Transform.h"
#include "RigidBody.h"
#include "BoundShape.h"
#include "BoundCircle.h"
#include "BoundRect.h"
#include "ObjectBuildAlgorithm.h"
#include "Builder.h"

void BoundCircle::OnRender()
{
	RRYD2DEngine::GetInstance()->DrawHollowEllipse(m_GameObject->m_Transform->m_Position.x, m_GameObject->m_Transform->m_Position.y, m_Radius * m_GameObject->m_Transform->m_Scale.width, m_Radius * m_GameObject->m_Transform->m_Scale.height, m_DrawColor);
}

void BoundCircle::Update()
{
	for (auto it : ObjectManager::GetInstance()->m_Objects)
	{
		if (it != this->m_GameObject)
			IsCheckCollision(it->GetComponent<BoundCircle>());
	}
}

bool BoundCircle::IsCheckCollision(BoundCircle* c)
{
	D2D1_POINT_2F point = { c->m_GameObject->m_Transform->GetPosition().x, c->m_GameObject->m_Transform->GetPosition().y };

	bool isCollision = sqrt(pow(point.x - m_GameObject->m_Transform->GetPosition().x, 2) + pow(point.y - m_GameObject->m_Transform->GetPosition().y, 2))
		< c->GetRadius() + GetRadius();

	RigidBody* rb = m_GameObject->GetComponent<RigidBody>();
	
	if (m_IsCollision == false)
	{
		if (isCollision)
		{
			SetColor(ColorF::Red);
			m_IsCollision = true;

			if (rb != nullptr)
			{
				rb->Reflect(c, true);
			}

			return true;
		}

		if (rb != nullptr)
		{
			rb->Reflect(c);
		}
	}
	else
	{
		if (isCollision == false)
		{
			m_IsCollision = false;
			SetColor(ColorF::White);

			return false;
		}
		else
		{
			if (rb != nullptr)
			{
				rb->Reflect(c, true);
			}
		}
	}
}
