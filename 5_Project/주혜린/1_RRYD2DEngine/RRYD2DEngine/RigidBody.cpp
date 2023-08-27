#include "pch.h"
#include "SpriteData.h"
#include "SingletonManager.h"
#include "RRYD2DEngine.h"
#include "Object.h"
#include "Component.h"
#include "GameObject.h"
#include "Transform.h"
#include "BoundShape.h"
#include "RigidBody.h"

RigidBody::RigidBody()
{

}

void RigidBody::Awake()
{
	m_LastPos = m_CurrPos = m_GameObject->m_Transform->m_Position;
}

void RigidBody::AddForce(Vector2 force)
{
	m_Velocity += force;
}

void RigidBody::Update()
{
	if (m_UseGravity)
	{
		m_Velocity += Vector2(0, m_Mass * 0.5f);
	}

	if (m_IsCollision)
	{
		m_Power -= m_Power * m_Drag;

		if (m_Power <= 0.3f)
		{
			m_IsCollision = false;
			m_Power = 0;
			m_CollisionVector = { 0, 0 };
		}

		m_GameObject->m_Transform->Translate(m_CollisionVector * m_Power);
	}
	else
	{
		m_GameObject->m_Transform->Translate(m_Velocity);
	}
}

void RigidBody::Reflect(BoundShape* target, bool isCollision)
{
	m_CurrPos = m_GameObject->m_Transform->m_Position;

	Vector2 deltaVec = Vector2(m_LastPos, m_CurrPos);

	m_LastPos = m_CurrPos;

	if (isCollision == true)
	{
		if(m_IsCollision == true)
		{
			m_Power += (target->m_GameObject->GetComponent<RigidBody>()->GetMass() / m_Mass) / 2;
		}
		else
		{
			m_IsCollision = isCollision;

			Vector2 normalVector = Vector2(m_CurrPos, target->m_GameObject->m_Transform->m_Position);

			normalVector.Normalize();
			deltaVec.Normalize();

			if (deltaVec.Length() > 0.1f)
			{
				m_CollisionVector = Vector2::Reflect(deltaVec, normalVector);
			}
			else
			{
				m_CollisionVector = normalVector * (-1);
			}

			m_Power = target->m_GameObject->GetComponent<RigidBody>()->GetMass() / m_Mass;

			m_CollisionVector.Normalize();
		}
	}
}
