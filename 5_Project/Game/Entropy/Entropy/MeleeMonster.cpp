#include "GamePCH.h"
#include "MeleeMonster.h"

void MeleeMonster::InitProperties()
{
	m_GameObject->SetStringTag("Bear");
	m_GameObject->m_pTransform->SetScale(1, 1);

	//m_GameObject->m_pTransform->SetPos(rand()%1000+100, 150);
	m_GameObject->m_pTransform->SetPos(1000, 150); //우측넣기
	//m_GameObject->m_pTransform->SetPos(300, 150);

	//속성값설정
	m_HP = 1200 * 0.8;
	//m_HP = 10;
	m_MoveSpeed = 100 * 1.2;
	m_TrackingSpeed = 200;
	m_AttackedDlay = 3.0f;
	m_DetectReach = D2D1::SizeF(800, 200);
	m_AttackReach = D2D1::SizeF(300, 200);
}

void MeleeMonster::InitColliders()
{

	//리지드 바디 설정 , 콜라이더들 설정
	m_pRigidBody = m_GameObject->AddComponent<Rigidbody>();
	m_pRigidBody->OnGravity();
	m_pRigidBody->SetFallMaxSpeed(10);
	m_pRigidBody->SetCollisionMode(CollisionDetectionMode::AABB);

	m_pHitCollider = m_GameObject->AddComponent<BoxCollider>();
	m_pHitCollider->SetRect(D2D1::Point2F(0, 0), D2D1::SizeF(192, 192));
	m_pHitCollider->SetTrigger(true);
	m_pHitCollider->SetStringTag("Hit Collider");
	m_pHitCollider->AddIgnoreTag("Move Collider");
	m_pHitCollider->AddIgnoreTag("Jump Collider");
	m_pHitCollider->AddIgnoreTag("Hit Collider");
	m_pHitCollider->AddIgnoreTag("Platform");
	m_pHitCollider->AddIgnoreTag("Floor");
	m_pHitCollider->AddIgnoreTag("Player");
	m_pHitCollider->AddIgnoreTag("Weapon");
	m_pHitCollider->AddIgnoreTag("Switch");
	m_pHitCollider->AddIgnoreTag("Gate");
	m_pHitCollider->AddIgnoreTag("Bear");
	m_pHitCollider->AddIgnoreTag("Turtle");
	m_pHitCollider->AddIgnoreTag("Crane");
	m_pHitCollider->AddIgnoreTag("Tank");

#ifdef _DEBUG
	m_pHitCollider->SetDebugDraw();
#endif

	m_pJumpCollider = this->m_GameObject->AddComponent<BoxCollider>();
	//m_pJumpCollider->SetRect(D2D1::Point2F(0, 76), D2D1::SizeF(90, 40));
	m_pJumpCollider->SetRect(D2D1::Point2F(0, 60), D2D1::SizeF(30, 40));
	m_pJumpCollider->SetTrigger(false);
	m_pJumpCollider->SetStringTag("Jump Collider");
	m_pJumpCollider->AddIgnoreTag("Move Collider");
	m_pJumpCollider->AddIgnoreTag("Player");
	m_pJumpCollider->AddIgnoreTag("Bullet");
	m_pJumpCollider->AddIgnoreTag("Weapon");
	m_pJumpCollider->AddIgnoreTag("Switch");
	m_pJumpCollider->AddIgnoreTag("Gate");
	m_pJumpCollider->AddIgnoreTag("Bear");
	m_pJumpCollider->AddIgnoreTag("Turtle");
	m_pJumpCollider->AddIgnoreTag("Crane");
	m_pJumpCollider->AddIgnoreTag("Tank");
#ifdef _DEBUG
	m_pJumpCollider->SetDebugDraw();
#endif

	m_pMoveCollider = this->m_GameObject->AddComponent<BoxCollider>();
	m_pMoveCollider->SetRect(D2D1::Point2F(0, 0), D2D1::SizeF(100, 64));
	m_pMoveCollider->SetTrigger(true);
	m_pMoveCollider->SetStringTag("Move Collider");
	m_pMoveCollider->AddIgnoreTag("Jump Collider");
	m_pMoveCollider->AddIgnoreTag("Move Collider");
	m_pMoveCollider->AddIgnoreTag("Head Collider");
	m_pMoveCollider->AddIgnoreTag("Player");
	m_pMoveCollider->AddIgnoreTag("Bullet");
	m_pMoveCollider->AddIgnoreTag("Weapon");
	m_pMoveCollider->AddIgnoreTag("Switch");
	m_pMoveCollider->AddIgnoreTag("Gate");
	m_pMoveCollider->AddIgnoreTag("Bear");
	m_pMoveCollider->AddIgnoreTag("Crane");
	m_pMoveCollider->AddIgnoreTag("Turtle");
	m_pMoveCollider->AddIgnoreTag("Tank");
#ifdef _DEBUG
	m_pMoveCollider->SetDebugDraw();
#endif


	m_pRigidBody->m_TargetCollider.push_back(m_pJumpCollider);
	m_pRigidBody->m_TargetCollider.push_back(m_pMoveCollider);
}


void MeleeMonster::InitSprites()
{
	m_MoveSprite = m_GameObject->AddComponent<Sprite>();
	m_MoveSprite->LoadSprite(_T("bear_move.txt"), _T("bear_move.png"), _T("bear"));
	m_MoveSprite->StopAnimation();
	m_MoveSprite->SetActive(false);


	m_AttackSprite = m_GameObject->AddComponent<Sprite>();
	m_AttackSprite->LoadSprite(_T("bear_attack.txt"), _T("bear_attack.png"), _T("bear"));
	m_AttackSprite->m_IsPlayOnce = true;
	m_AttackSprite->StopAnimation();
	m_AttackSprite->SetActive(false);

	m_HitedSprite = m_GameObject->AddComponent<Sprite>();
	m_HitedSprite->LoadSprite(_T("bear_hit.txt"), _T("bear_hit.png"), _T("bear"));
	m_HitedSprite->m_IsPlayOnce = true;
	m_HitedSprite->StopAnimation();
	m_HitedSprite->SetActive(false);

	m_DeadSprite = m_GameObject->AddComponent<Sprite>();
	m_DeadSprite->LoadSprite(_T("bear_die.txt"), _T("bear_die.png"), _T("bear"));
	m_DeadSprite->m_IsPlayOnce = true;
	m_DeadSprite->StopAnimation();
	m_DeadSprite->SetActive(false);

}


void MeleeMonster::Awake()
{
	///Behaivor Tree

	m_Player = SceneObjectManager::GetInstance()->m_pPlayerObject;

	//root
	auto rootSequence = new BrainTree::Selector();

	//Sequence
	auto AttackSequence = new BrainTree::Sequence();
	auto moveSequence = new BrainTree::Sequence();
	auto TrackingSequence = new BrainTree::Sequence();


	//checkers
	auto meleeAtkChecker = new BrainTree::MeleeAttackChecker();
	auto moveChecker = new BrainTree::MoveChecker();
	auto detectChecker = new BrainTree::DetectChecker();
	//auto meleeAtkChecker = new BrainTree::MeleeAttackChecker();

	//actions 
	auto meleeAtckAction = new BrainTree::MeleeAttackAction(this);
	auto moveAction = new BrainTree::MoveAction(this);
	auto trackingAction = new BrainTree::TrackingAction(this);


	//Make node
	AttackSequence->addChild(meleeAtkChecker);
	AttackSequence->addChild(meleeAtckAction);
	rootSequence->addChild(AttackSequence);

	moveSequence->addChild(moveChecker);
	moveSequence->addChild(moveAction);
	rootSequence->addChild(moveSequence);

	TrackingSequence->addChild(detectChecker);
	TrackingSequence->addChild(trackingAction);
	rootSequence->addChild(TrackingSequence);

	m_BehaviorTree.setRoot(rootSequence);

	//속성들
	InitProperties();

	//콜라이더들 설정
	InitColliders();

	//Sprite setting
	InitSprites();



}

void MeleeMonster::OnRender()
{
	BaseMonster::DamageTextOut();

	//BaseMonster::OnRender();

#ifdef DEBUG
	//test용

	if (IsMeleeAttack == true)
	{
		// 공격 표시
		auto tempX = m_GameObject->GetPos().x - (m_AttackReach.width);
		auto tempY = m_GameObject->GetPos().y - (m_AttackReach.height);

		_GraphicEngine->D2DXDrawCircle(m_GameObject->GetPos().x, m_GameObject->GetPos().y, 300, 300, D2D1::ColorF::Red, D2D1::ColorF::Red);

	}

	// 인식범위 표시
	auto tempX = m_GameObject->GetPos().x - (m_DetectReach.width / 2);
	auto tempY = m_GameObject->GetPos().y - (m_DetectReach.height / 2);

	_GraphicEngine->D2DXDrawRectrangle(tempX, tempY, m_DetectReach.width, m_DetectReach.height
		, D2D1::ColorF::Pink, D2D1::ColorF::Pink);


	//attack 범위 표시

	auto tempAtkX = m_GameObject->GetPos().x - (m_AttackReach.width / 2);
	auto tempAtkY = m_GameObject->GetPos().y - (m_AttackReach.height / 2);

	_GraphicEngine->D2DXDrawRectrangle(tempAtkX, tempAtkY, m_AttackReach.width, m_AttackReach.height
		, D2D1::ColorF::DarkGoldenrod, D2D1::ColorF::DarkGoldenrod);

	//HP

	_GraphicEngine->D2DXDrawText(m_GameObject->GetPos().x, m_GameObject->GetPos().y - 100, 100, 100, D2D1::ColorF::Aqua, _T("HP::%d"), m_HP);



#endif // DEBUG
}

void MeleeMonster::Update()
{

	//text test
	//BaseMonster::DamageTextOut();
	//BaseMonster::DamageTextFlow();



	if (IsDead() == true)
	{
		if (m_DeadSoundOut == false)
		{
			Dead();
		}
		return; // testing 몬스터 를 사라지게해야함
	}


	BaseMonster::CheckWall();

	CheckAttacked();


	IsInReach();

	IsDetected();



	BaseMonster::Update();

	BaseMonster::DamageTextFlow();
}


void MeleeMonster::FlipAnimation()
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

void MeleeMonster::StopAllAnimation()
{
	m_MoveSprite->SetActive(false);
	m_AttackSprite->SetActive(false);
	m_HitedSprite->SetActive(false);
	m_DeadSprite->SetActive(false);
}



void MeleeMonster::OnDestroy()
{
	SafeRelease(&m_MoveSprite);
	SafeRelease(&m_AttackSprite);
	SafeRelease(&m_HitedSprite);
	SafeRelease(&m_DeadSprite);
}

bool MeleeMonster::IsDead()
{

	if (m_HP <= 0)
	{
		return true;
	}

	return false;
}

bool MeleeMonster::CheckAttacked()
{
	if (m_HitedSprite->m_IsFinish == true)
	{
		m_HitFinish = true;
		//m_IsHited = false;
		//StopAllAnimation();
		//m_HitedSprite->SetActive(false);
	}

	if (m_IsHited == false)
	{

		if (m_pHitCollider->m_Target.size() > 0) // 총알에 충돌
		{
			for (auto collider : m_pHitCollider->m_Target)
			{
				if (collider->m_GameObject->GetComponent<Bullet>()->IsActive() && collider->m_GameObject->GetStringTag()._Equal("Bullet")) //총알과 충돌
				{
					//test Text

					WCHAR hitDamage[256];
					swprintf_s(hitDamage, _T("%.0f"), SceneObjectManager::GetInstance()->
						m_pPlayerObject->GetComponent<Player>()->
						m_Gun->GetComponent<Weapon>()->m_AttackDamage[_GameManager->m_CurrentState]);
					//WCHAR font[256];
					//swprintf_s(font, _T("궁서"));

					//MonsterText* text = new MonsterText(D2D1::Point2F(m_GameObject->GetPos().x, m_GameObject->GetPos().y)
					//	, hitDamage, font, D2D1::ColorF::AliceBlue);

					////text Test
					//m_DamageList.push(text);

					int ran = rand() % 2;

					if (ran == 0)
					{
						_FAudio->FPlaySound(OBJECT_BULLET_3);
					}
					else
					{
						_FAudio->FPlaySound(OBJECT_BULLET_1);
					}

					MonsterText* temp = new MonsterText();
					temp->DamageTextX = m_GameObject->GetPos().x;
					temp->DamageTextY = m_GameObject->GetPos().y - 20;
					temp->Text = hitDamage;

					m_DamageList.push_back(temp);


					m_IsHited = true;

					m_HP -= SceneObjectManager::GetInstance()->
						m_pPlayerObject->GetComponent<Player>()->
						m_Gun->GetComponent<Weapon>()->m_AttackDamage[_GameManager->m_CurrentState];

					collider->m_GameObject->GetComponent<Bullet>()->m_IsHit = true;

					m_HitFinish = false;

					m_HitedSprite->StopAnimation();
					m_HitedSprite->SetActive(true);
					m_HitedSprite->StartAnimation();

					return true;
				}
			}

			m_HitFinish = true;
			m_IsHited = false;
			return false;
		}
		else
		{
			m_HitFinish = true;
			m_IsHited = false;
			return false;
		}
	}

	//m_IsHited true


	if (m_pHitCollider->m_Target.size() <= 0)
	{
		m_IsHited = false;
	}


	// hit 여러개

	if (m_pHitCollider->m_Target.size() > 0)
	{
		for (auto collider : m_pHitCollider->m_Target)
		{
			if (collider->m_GameObject->GetComponent<Bullet>()->IsActive() && collider->m_GameObject->GetStringTag()._Equal("Bullet"))
			{
				m_IsHited = true;


				//m_HitedSprite->StopAnimation();
				//m_HitedSprite->SetActive(true);
				//m_HitedSprite->StartAnimation();

				return true;
			}
		}

		m_HitFinish = true;
		m_IsHited = false;
		return false;
	}

	return false;
}

bool MeleeMonster::IsInReach()
{
	m_DetectDelay -= _FTime->GetEngineFixedDeltaTimeSec();

	float offsetX = m_AttackReach.width / 2;
	float offsetY = m_AttackReach.height / 2;

	int check = 0;

	BoxCollider* _target = m_Player->GetComponent<Player>()->m_pHitCollider;
	D2D1_POINT_2F point = _target->m_GameObject->GetPos();

	if (fabs((point.x + _target->m_Center.x) - (m_GameObject->GetPos().x)) < (_target->m_Size.width / 2 + offsetX))
	{
		++check;
	}

	if (fabs((point.y + _target->m_Center.y) - (m_GameObject->GetPos().y)) < (_target->m_Size.height / 2 + offsetY))
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

		for (int i = 0; i < m_MessageQueue.size(); i++)
		{
			m_MessageQueue.pop();
		}


		m_MessageQueue.push(BTEventMessage::InReachMessage());
		return true;
	}
	else
	{
		return false;
	}

}



void MeleeMonster::IsDetected()
{
	float offsetX = m_DetectReach.width / 2;
	float offsetY = m_DetectReach.height / 2;


	int check = 0;

	BoxCollider* _target = m_Player->GetComponent<Player>()->m_pHitCollider;
	D2D1_POINT_2F point = _target->m_GameObject->GetPos();

	if (fabs((point.x + _target->m_Center.x) - (m_GameObject->GetPos().x)) < (_target->m_Size.width / 2 + offsetX))
	{
		++check;
	}

	if (fabs((point.y + _target->m_Center.y) - (m_GameObject->GetPos().y)) < (_target->m_Size.height / 2 + offsetY))
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

		if (m_DetectSoundOut == false)
		{
			_FAudio->FPlaySound(ENEMY_BEAR_RECOG);
			m_DetectSoundOut = true;
		}

		m_MessageQueue.push(BTEventMessage::FindPlayerMessage());
	}
	else
	{
		m_DetectSoundOut = false;

		m_MessageQueue.push(BTEventMessage::MoveMessage());
	}


}

void MeleeMonster::Move()
{
	BaseMonster::Move();

	FlipAnimation();

	if (m_HitFinish == true)
	{
		StopAllAnimation();
		m_MoveSprite->SetActive(true);
		m_MoveSprite->StartAnimation();
	}
	else
	{
		//StopAllAnimation();
		m_MoveSprite->SetActive(false);
	}
	}


void MeleeMonster::Dead()
{
#ifdef DEBUG
	Debug::Log("Melee Message :: DEAD");
#endif // DEBUG

	if (m_DeadSprite->m_IsFinish == true)
	{
		m_DeadSoundOut = true;
		_FAudio->FPause(ENEMY_BEAR_DIE);
		_FAudio->FPlaySound(ENEMY_BEAR_DIE);

	}

	m_IsDead = true;

	FlipAnimation();

	StopAllAnimation();
	m_DeadSprite->SetActive(true);
	m_DeadSprite->StartAnimation();

	m_DamageList.clear();
}

void MeleeMonster::Attack()
{

	if (m_AttackSprite->m_IsFinish == true)
	{
		_FAudio->FPlaySound(ENEMY_BEAR_ATTK);
		m_AttackSprite->StopAnimation();
		m_Player->GetComponent<Player>()->Damage(1);
	}

	if (m_HitFinish == true)
	{
		FlipAnimation();
		StopAllAnimation();

		m_AttackSprite->SetActive(true);
		m_AttackSprite->StartAnimation();
	}
	else
	{
		m_AttackSprite->SetActive(false);
	}
}