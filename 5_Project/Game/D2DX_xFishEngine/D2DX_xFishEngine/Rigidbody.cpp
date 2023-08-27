#include "Vector.h"
#include "pch.h"
#include "Object.h"
#include "framework.h"
#include "Component.h"
#include "Transform.h"
#include "GameObject.h"
#include "Collider.h"
#include "Rigidbody.h"

Rigidbody::Rigidbody()
{
}

void Rigidbody::Awake()
{
	m_LastPos = m_CurrPos = m_GameObject->GetPos();
}

void Rigidbody::AddForce(Vector2 force)
{
	m_Velocity += force;
}

void Rigidbody::Update()
{
	//�߷��� ������̶�� �Ź� �߷°��� �־��ش�.

	if (m_UseGravity)
	{
		m_FallSpeed += m_Gravity * _FTime->GetEngineFixedDeltaTimeSec();

		//�ִ�ġ ����
		if (m_FallSpeed >= m_MaxFallSpeed) m_FallSpeed = m_MaxFallSpeed;
		//Debug::LogFormat("Rigidbody yPos : %.2f", m_FallSpeed);
	}

	if (m_TargetCollider.size() != 0)
	{
		if (m_FallSpeed >= 0)
		{
			for (int i = 0; i < m_TargetCollider.size(); ++i)
			{
				if (m_TargetCollider[i]->GetStringTag()._Equal("Move Collider") == false) continue;
				if (m_TargetCollider[i]->IsTriggerOn() == true) continue;
				if (m_TargetCollider[i]->m_Target.size() > 0 && m_TargetCollider[i]->m_Target[0]->IsTriggerOn() == false)
				{
#pragma region y�� �̵� ����
					float yDistance = (m_GameObject->m_pTransform->GetPos().y + m_TargetCollider[i]->m_Center.y) - (m_TargetCollider[i]->m_Target[0]->m_GameObject->m_pTransform->GetPos().y + m_TargetCollider[i]->m_Target[0]->m_Center.y);

					m_TargetCollider[i]->m_CollisionStartPoint.y = m_TargetCollider[i]->m_Target[0]->m_GameObject->m_pTransform->GetPos().y + m_TargetCollider[i]->m_Target[0]->m_Center.y;
					if (yDistance < 0)
					{
						m_TargetCollider[i]->m_CollisionStartPoint.y -= yDistance;
					}
					else
					{
						m_TargetCollider[i]->m_CollisionStartPoint.y += yDistance;
					}

#pragma endregion
#pragma region x�� �̵� ����
					float xDistance = (m_GameObject->m_pTransform->GetPos().x + m_TargetCollider[i]->m_Center.x) - (m_TargetCollider[i]->m_Target[0]->m_GameObject->m_pTransform->GetPos().x + m_TargetCollider[i]->m_Target[0]->m_Center.x);

					m_TargetCollider[i]->m_CollisionStartPoint.x = m_TargetCollider[i]->m_Target[0]->m_GameObject->m_pTransform->GetPos().x + m_TargetCollider[i]->m_Target[0]->m_Center.x;
					if (xDistance < 0)
					{
						m_TargetCollider[i]->m_CollisionStartPoint.x -= (m_TargetCollider[i]->m_Target[0]->m_Size.width / 2 + m_TargetCollider[i]->m_Size.width / 2);
					}
					else
					{
						m_TargetCollider[i]->m_CollisionStartPoint.x += (m_TargetCollider[i]->m_Target[0]->m_Size.width / 2 + m_TargetCollider[i]->m_Size.width / 2);
					}

					m_TargetCollider[i]->m_CollisionStartPoint.x -= m_Velocity.x * 2;
					m_GameObject->m_pTransform->SetPos(m_TargetCollider[i]->m_CollisionStartPoint);
#pragma endregion
				}
			}
		}
		m_GameObject->m_pTransform->Translate(m_Velocity);
		//���� ū y ��ǥ�� ��ġ�� �ݶ��̴��� �����´�
		//y ��ǥ�� ȭ�� �Ʒ����� ���� ũ��

#pragma region y�� �̵� ����
		Collider* lastYCol = nullptr;

		int yIndex = 0;

		for (int i = 0; i < m_TargetCollider.size() && m_TargetCollider[i]->IsTriggerOn() == false; ++i)
		{
			float maxYPos = 1080;
			if (m_TargetCollider[i]->GetStringTag()._Equal("Jump Collider") == false) continue;
			for (auto col : m_TargetCollider[i]->m_Target)
			{
				if (col->IsTriggerOn() == true) continue;
				if (maxYPos > col->m_GameObject->GetPos().y + col->m_Center.y - (col->m_Size.height / 2 - m_TargetCollider[i]->m_Size.height / 2))
				{
					maxYPos = col->m_GameObject->GetPos().y + col->m_Center.y - (col->m_Size.height / 2 - m_TargetCollider[i]->m_Size.height / 2);
					lastYCol = col;
					yIndex = i;
				}
			}
		}

		if (lastYCol != nullptr)
		{
			//���� ������ ���� ���� ������ y��ǥ�� ����ؼ� y��ǥ�� ���� ���� �������� �����Ͽ� �ٲ۴�
			float yCurDist = (m_GameObject->GetPos().y + m_TargetCollider[yIndex]->m_Center.y) - (lastYCol->m_GameObject->GetPos().y + lastYCol->m_Center.y);
			float yDistance = (m_TargetCollider[yIndex]->m_Size.height / 2 + lastYCol->m_Size.height / 2);

			//�������� ���� ���, �浹�����Ƿ� �������� ���ǵ带 0���� �ٲ۴�
			if (m_FallSpeed > 0)
			{
				m_FallSpeed = 0;
			}

			//���� ���� ������ Ÿ�ٰ��� �Ÿ��� ���� �ݶ��̴� ����� ���� �ͺ��� ������ ��������� ��
			if (fabs(yCurDist) < yDistance)
			{
				//y �����̴� ���⿡ ���� ������

				m_TargetCollider[yIndex]->m_CollisionStartPoint.y -= (yDistance - 1 - abs(yCurDist));
			}


			//���� ����
			m_GameObject->m_pTransform->SetPos(m_GameObject->m_pTransform->GetPos().x + m_Velocity.x, m_TargetCollider[yIndex]->m_CollisionStartPoint.y);

		}
#pragma endregion
	}

	//���� �ð��� ���߸� �������� ���ǵ带 0���� 
	if (FTime::GetInstance()->m_EngineDeltaTimeScale <= 0.f)
	{
		m_FallSpeed = 0;
	}

	//�߷� ����
	m_GameObject->m_pTransform->Translate(0, m_FallSpeed);

	m_Velocity = { 0, 0 };
}

void Rigidbody::Reflect(Collider* target, bool isCollision)
{
	m_CurrPos = m_GameObject->GetPos();

	Vector2 deltaVec = Vector2(m_LastPos, m_CurrPos);

	m_LastPos = m_CurrPos;

	if (isCollision == true)
	{
		if (m_IsCollision == true)
		{
			m_Power += (target->m_GameObject->GetComponent<Rigidbody>()->GetMass() / m_Mass) / 2;
		}
		else
		{
			m_IsCollision = isCollision;

			Vector2 normalVector = Vector2(m_CurrPos, target->m_GameObject->GetPos());

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

			m_Power = target->m_GameObject->GetComponent<Rigidbody>()->GetMass() / m_Mass;

			m_CollisionVector.Normalize();
		}
	}
}
