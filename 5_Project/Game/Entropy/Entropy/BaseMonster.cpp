#include "GamePCH.h"
#include "BaseMonster.h"

BaseMonster::~BaseMonster()
{
	m_Player = nullptr;

	while (m_MessageQueue.empty() == false)
	{
		m_MessageQueue.pop();
	}

	m_BehaviorTree.DeleteAllNode();
}

void BaseMonster::Awake()
{

}

void BaseMonster::Update()
{

	if (m_DeadTime >= 1.0f)
	{
		for (Component* com : m_GameObject->GetAllComponents())
		{
			com->SetActive(false);
		}
	}

	if (!m_BehaviorTree.hasRoot())
	{
		return;
	}
		
	/*
	if (m_BehaviorTree.isTerminatedRoot())
	{
		return;
	}	
	*/

	/// 폴링과 이벤트 드리븐 같이 처리
	// A. 이벤트 드리븐 처리
	if (!m_MessageQueue.empty())
	{
		auto message = m_MessageQueue.front();
		m_MessageQueue.pop();
		
		m_BehaviorTree.updateMessage(message);
	}	
	// B. 폴링 처리
	m_BehaviorTree.update();
}

void BaseMonster::OnRender()
{
	if (m_IsDead == true)
	{
		m_DeadTime += _FTime->GetObjectFixedDeltaTimeSec();

		_GraphicEngine->DrawBitmap(m_GameObject->GetPos(), m_DeadSprite->m_SpriteSheets[m_DeadSprite->m_SpriteSheets.size() - 1], m_DeadSprite->m_BitMap, D2D1::SizeF(), 1 - m_DeadTime);
	}
}

void BaseMonster::Move()
{

	Vector2 moveVector;

	if (m_Direction == BaseMonster::Direction::LEFT)
	{
		moveVector = Vector2(-1, 0) * m_MoveSpeed * _FTime->GetObjectFixedDeltaTimeSec();
	}
	else if (m_Direction == BaseMonster::Direction::RIGHT)
	{
		moveVector = Vector2(1, 0) * m_MoveSpeed * _FTime->GetObjectFixedDeltaTimeSec();
	}

	Rigidbody* rigidbody = m_GameObject->GetComponent<Rigidbody>();
	rigidbody->AddForce(moveVector);
	
}

void BaseMonster::CheckWall()
{
	if (m_GameObject->GetPos().x - m_pHitCollider->m_Size.width / 2 <= 0)
	{
		m_Direction = BaseMonster::Direction::RIGHT;		
	}
	else if (m_GameObject->GetPos().x + m_pHitCollider->m_Size.width / 2 >= _GameManager->pSceneManager->GetActiveScene()->m_Data.MapSize.width * TILE_SIZE)
	{
		m_Direction = BaseMonster::Direction::LEFT;		
	}

	if ((m_pMoveCollider->IsCrash() == true && m_pMoveCollider->m_Target.size() > 0))
	{
		if (m_Direction == BaseMonster::Direction::LEFT)
		{
			m_Direction = BaseMonster::Direction::RIGHT;
			m_GameObject->SetPos(D2D1::Point2F(m_GameObject->GetPos().x + 10, m_GameObject->GetPos().y));
		}
		else
		{
			m_Direction = BaseMonster::Direction::LEFT;
			m_GameObject->SetPos(D2D1::Point2F(m_GameObject->GetPos().x - 10, m_GameObject->GetPos().y));
		}
	}
}

void BaseMonster::Tracking()
{
	Vector2 moveVector;

	FlipAnimation();

	if (m_Direction == BaseMonster::Direction::LEFT)
	{
		moveVector = Vector2(-1, 0) * (m_MoveSpeed + m_TrackingSpeed) * _FTime->GetObjectFixedDeltaTimeSec();
	}
	else if (m_Direction == BaseMonster::Direction::RIGHT)
	{
		moveVector = Vector2(1, 0) * (m_MoveSpeed + m_TrackingSpeed) * _FTime->GetObjectFixedDeltaTimeSec();
	}

	Rigidbody* rigidbody = m_GameObject->GetComponent<Rigidbody>();
	rigidbody->AddForce(moveVector);
}

void BaseMonster::IsDetected()
{
		float offsetX = m_DetectReach.width / 2;
		float offsetY = m_DetectReach.height / 2;


		int check = 0;

		BoxCollider* _target = m_Player->GetComponent<Player>()->m_pHitCollider;
		D2D1_POINT_2F point = _target->m_GameObject->GetPos();

		if (fabs((point.x + _target->m_Center.x) - (m_GameObject->GetPos().x )) < (_target->m_Size.width / 2 + offsetX))
		{
			++check; 
		}
			
		if (fabs((point.y + _target->m_Center.y) - (m_GameObject->GetPos().y )) < (_target->m_Size.height / 2 + offsetY))
		{
			++check;
		}
			

		if (check == 2)
		{
			if (m_GameObject->GetPos().x <= m_Player->GetPos().x) // 플레이어가 오른쪽에있다.
			{
				this->m_Direction = Direction::RIGHT;
			}
			else
			{
				this->m_Direction = Direction::LEFT;
			}

			FlipAnimation();

			m_MessageQueue.push(BTEventMessage::FindPlayerMessage());
		}
		else 
		{
			m_MessageQueue.push(BTEventMessage::MoveMessage());
		}
		
		
}
void BaseMonster::FlipAnimation()
{
	if (m_Direction == BaseMonster::Direction::LEFT)
	{
		m_GameObject->m_pTransform->SetScale(fabs(m_GameObject->m_pTransform->GetScale().width) * -1, m_GameObject->m_pTransform->GetScale().height);
	}
	else
	{
		m_GameObject->m_pTransform->SetScale(fabs(m_GameObject->m_pTransform->GetScale().width) * 1, m_GameObject->m_pTransform->GetScale().height);
	}

}

void BaseMonster::CheckMapOut()
{
	if (m_GameObject->GetPos().x - m_pHitCollider->m_Size.width / 2 <= 0)
	{
		m_GameObject->SetPos(D2D1::Point2F(m_pHitCollider->m_Size.width / 2, m_GameObject->GetPos().y));
	}
	else if (m_GameObject->GetPos().x + m_pHitCollider->m_Size.width / 2 >= _GameManager->pSceneManager->GetActiveScene()->m_Data.MapSize.width * TILE_SIZE)
	{
		m_GameObject->SetPos(D2D1::Point2F(_GameManager->pSceneManager->GetActiveScene()->m_Data.MapSize.width * TILE_SIZE - m_pHitCollider->m_Size.width / 2, m_GameObject->GetPos().y));
	}

	if (m_GameObject->GetPos().y + m_pHitCollider->m_Size.height / 2 >= (_GameManager->pSceneManager->GetActiveScene()->m_Data.MapSize.height - 2) * TILE_SIZE)
	{
		m_GameObject->SetPos(D2D1::Point2F(m_GameObject->GetPos().x, (_GameManager->pSceneManager->GetActiveScene()->m_Data.MapSize.height - 2) * TILE_SIZE - m_pHitCollider->m_Size.height / 2));
	}


}

void BaseMonster::DamageTextOut()
{
	if (m_DamageList.empty() == false)
	{
		for (int i = 0; i < m_DamageList.size(); i++)
		{
			
			auto text = m_DamageList[i];
			//D2D1::Point2F(m_GameObject->GetPos().x -10 , m_GameObject->GetPos().y -30), _T(_damage), _T("궁서"), D2D1::ColorF::AliceBlue
			//MonsterText::Out(D2D1::Point2F(m_GameObject->GetPos().x - 10, m_GameObject->GetPos().y - 30), text.c_str(), _T("궁서"), D2D1::ColorF::AliceBlue);
			
			if (text->IsGray == true)
			{

				_GraphicEngine->D2DXDrawText
				(
					text->DamageTextX, text->DamageTextY, 10, 10, D2D1::ColorF::Gray, _T("LAB디지털"), text->Text.c_str()
				);
			}
			else 
			{
				if (_GameManager->m_CurrentState == 0)//순행
				{
					_GraphicEngine->D2DXDrawText
					(
						text->DamageTextX, text->DamageTextY, 10,10, D2D1::ColorF::Cyan,_T("LAB디지털"),text->Text.c_str()
					);
				}
				else 
				{
					_GraphicEngine->D2DXDrawText
					(
						text->DamageTextX, text->DamageTextY, 10, 10, D2D1::ColorF::IndianRed, _T("LAB디지털"), text->Text.c_str()
					);
				}
			}

		}

	}

}

void BaseMonster::DamageTextFlow()
{
	m_TextTime -= _FTime->GetEngineFixedDeltaTimeSec();

	if (m_TextTime <= 0.f)
	{
		m_TextTime = 1.0f;
		if (m_DamageList.empty() == false)
		{
			//auto text = m_DamageList.front();
			//m_DamageList.pop();
			m_DamageList.erase(m_DamageList.begin());
		}
	}
	else
	{
		for (int i = 0; i < m_DamageList.size(); i++)
		{
			auto text = m_DamageList[i];

			if (m_Direction == BaseMonster::Direction::LEFT)
			{
				text->DamageTextX = m_GameObject->GetPos().x - m_TextLeftOffset;

			}
			else
			{
				text->DamageTextX = m_GameObject->GetPos().x + m_TextRightOffset;
			}

			text->DamageTextY -= 1;
			
		}

	}
}
