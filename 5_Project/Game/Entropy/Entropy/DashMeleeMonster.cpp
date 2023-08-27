#include "GamePCH.h"
#include "DashMeleeMonster.h"

void DashMeleeMonster::InitProperties()
{
	m_GameObject->SetStringTag("Turtle");
	m_GameObject->m_pTransform->SetScale(1, 1);

	//m_GameObject->m_pTransform->SetPos(rand()%1000+100, 150);
	//m_GameObject->m_pTransform->SetPos(1000,150); //우측넣기
	m_GameObject->m_pTransform->SetPos(300, 200);

	//속성값설정
	//m_HP = 2000;
	m_HP = 1000;
	m_MoveSpeed = 80 * 1.2;
	m_TrackingSpeed = 0;
	m_DashSpeed = 100.f;

	//m_TextLeftOffset;
	m_TextRightOffset -= 10;
	m_DetectReach = D2D1::SizeF(600, 200);
	m_AttackReach = D2D1::SizeF(400, 200); // 대쉬거리
}

void DashMeleeMonster::InitColliders()
{
	//리지드 바디 설정 , 콜라이더들 설정
	m_pRigidBody = m_GameObject->AddComponent<Rigidbody>();
	m_pRigidBody->OnGravity();
	m_pRigidBody->SetFallMaxSpeed(10);
	m_pRigidBody->SetCollisionMode(CollisionDetectionMode::AABB);

	m_pHitCollider = m_GameObject->AddComponent<BoxCollider>();
	m_pHitCollider->SetRect(D2D1::Point2F(0, 0), D2D1::SizeF(100, 192)); // 192
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
	m_pMoveCollider->SetTrigger(false);
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

	m_pLeftShieldCollider = this->m_GameObject->AddComponent<BoxCollider>();
	m_pLeftShieldCollider->SetRect(D2D1::Point2F(-110, 0), D2D1::SizeF(1, 250));
	m_pLeftShieldCollider->SetTrigger(false);
	m_pLeftShieldCollider->SetStringTag("Left Shield Collider");
	m_pLeftShieldCollider->AddIgnoreTag("Jump Collider");
	m_pLeftShieldCollider->AddIgnoreTag("Move Collider");
	m_pLeftShieldCollider->AddIgnoreTag("Head Collider");
	m_pLeftShieldCollider->AddIgnoreTag("Player");
	//m_pMoveCollider->AddIgnoreTag("Bullet");
	m_pLeftShieldCollider->AddIgnoreTag("Weapon");
	m_pLeftShieldCollider->AddIgnoreTag("Switch");
	m_pLeftShieldCollider->AddIgnoreTag("Gate");
	m_pLeftShieldCollider->AddIgnoreTag("Bear");
	m_pLeftShieldCollider->AddIgnoreTag("Crane");
	m_pLeftShieldCollider->AddIgnoreTag("Turtle");
	m_pLeftShieldCollider->AddIgnoreTag("Tank");
	m_pLeftShieldCollider->AddIgnoreTag("Platform");
	m_pLeftShieldCollider->AddIgnoreTag("Floor");
#ifdef _DEBUG
	m_pLeftShieldCollider->SetDebugDraw();
#endif

	m_pRightShieldCollider = this->m_GameObject->AddComponent<BoxCollider>();
	m_pRightShieldCollider->SetRect(D2D1::Point2F(110, 0), D2D1::SizeF(1, 250));
	m_pRightShieldCollider->SetTrigger(false);
	m_pRightShieldCollider->SetStringTag("Right Shield Collider");
	m_pRightShieldCollider->AddIgnoreTag("Jump Collider");
	m_pRightShieldCollider->AddIgnoreTag("Move Collider");
	m_pRightShieldCollider->AddIgnoreTag("Head Collider");
	m_pRightShieldCollider->AddIgnoreTag("Player");
	//m_pMoveCollider->AddIgnoreTag("Bullet");
	m_pRightShieldCollider->AddIgnoreTag("Weapon");
	m_pRightShieldCollider->AddIgnoreTag("Switch");
	m_pRightShieldCollider->AddIgnoreTag("Gate");
	m_pRightShieldCollider->AddIgnoreTag("Bear");
	m_pRightShieldCollider->AddIgnoreTag("Crane");
	m_pRightShieldCollider->AddIgnoreTag("Turtle");
	m_pRightShieldCollider->AddIgnoreTag("Tank");
	m_pRightShieldCollider->AddIgnoreTag("Platform");
	m_pRightShieldCollider->AddIgnoreTag("Floor");
#ifdef _DEBUG
	m_pRightShieldCollider->SetDebugDraw();
#endif


	/*m_pUpShieldCollider = this->m_GameObject->AddComponent<BoxCollider>();
	m_pUpShieldCollider->SetRect(D2D1::Point2F(0, -110), D2D1::SizeF(250, 1));
	m_pUpShieldCollider->SetTrigger(false);
	m_pUpShieldCollider->SetStringTag("Right Shield Collider");
	m_pUpShieldCollider->AddIgnoreTag("Jump Collider");
	m_pUpShieldCollider->AddIgnoreTag("Move Collider");
	m_pUpShieldCollider->AddIgnoreTag("Head Collider");
	m_pUpShieldCollider->AddIgnoreTag("Player");
	m_pUpShieldCollider->AddIgnoreTag("Weapon");
	m_pUpShieldCollider->AddIgnoreTag("Switch");
	m_pUpShieldCollider->AddIgnoreTag("Gate");
	m_pUpShieldCollider->AddIgnoreTag("Bear");
	m_pUpShieldCollider->AddIgnoreTag("Crane");
	m_pUpShieldCollider->AddIgnoreTag("Turtle");
	m_pUpShieldCollider->AddIgnoreTag("Tank");
	m_pUpShieldCollider->AddIgnoreTag("Platform");
	m_pUpShieldCollider->AddIgnoreTag("Floor");
#ifdef _DEBUG
	m_pUpShieldCollider->SetDebugDraw();
#endif

	m_pDownShieldCollider = this->m_GameObject->AddComponent<BoxCollider>();
	m_pDownShieldCollider->SetRect(D2D1::Point2F(0, 110), D2D1::SizeF(250, 1));
	m_pDownShieldCollider->SetTrigger(false);
	m_pDownShieldCollider->SetStringTag("Right Shield Collider");
	m_pDownShieldCollider->AddIgnoreTag("Jump Collider");
	m_pDownShieldCollider->AddIgnoreTag("Move Collider");
	m_pDownShieldCollider->AddIgnoreTag("Head Collider");
	m_pDownShieldCollider->AddIgnoreTag("Player");
	m_pDownShieldCollider->AddIgnoreTag("Weapon");
	m_pDownShieldCollider->AddIgnoreTag("Switch");
	m_pDownShieldCollider->AddIgnoreTag("Gate");
	m_pDownShieldCollider->AddIgnoreTag("Bear");
	m_pDownShieldCollider->AddIgnoreTag("Crane");
	m_pDownShieldCollider->AddIgnoreTag("Turtle");
	m_pDownShieldCollider->AddIgnoreTag("Tank");
	m_pDownShieldCollider->AddIgnoreTag("Platform");
	m_pDownShieldCollider->AddIgnoreTag("Floor");
#ifdef _DEBUG
	m_pDownShieldCollider->SetDebugDraw();
#endif*/


	m_pRigidBody->m_TargetCollider.push_back(m_pJumpCollider);
	m_pRigidBody->m_TargetCollider.push_back(m_pMoveCollider);
}


void DashMeleeMonster::InitSprites()
{
	m_MoveSprite = m_GameObject->AddComponent<Sprite>();
	m_MoveSprite->LoadSprite(_T("turtle_move.txt"), _T("turtle_move.png"), _T("turtle"));
	m_MoveSprite->StopAnimation();
	m_MoveSprite->SetActive(false);


	m_AttackSprite = m_GameObject->AddComponent<Sprite>();
	m_AttackSprite->LoadSprite(_T("turtle_attack.txt"), _T("turtle_attack.png"), _T("turtle"));
	m_AttackSprite->m_IsPlayOnce = true;
	m_AttackSprite->StopAnimation();
	m_AttackSprite->SetActive(false);

	m_HitedSprite = m_GameObject->AddComponent<Sprite>();
	m_HitedSprite->LoadSprite(_T("turtle_hit.txt"), _T("turtle_hit.png"), _T("turtle"));
	m_HitedSprite->m_IsPlayOnce = true;
	m_HitedSprite->StopAnimation();
	m_HitedSprite->SetActive(false);

	m_DeadSprite = m_GameObject->AddComponent<Sprite>();
	m_DeadSprite->LoadSprite(_T("turtle_die.txt"), _T("turtle_die.png"), _T("turtle"));
	m_DeadSprite->m_IsPlayOnce = true;
	m_DeadSprite->StopAnimation();
	m_DeadSprite->SetActive(false);

}


void DashMeleeMonster::Awake()
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
	//auto meleeAtckAction = new BrainTree::MeleeAttackAction(this);
	auto dashAction = new BrainTree::DashAction(this);

	auto moveAction = new BrainTree::MoveAction(this);
	auto trackingAction = new BrainTree::TrackingAction(this);


	//Make node
	AttackSequence->addChild(meleeAtkChecker);
	AttackSequence->addChild(dashAction);
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

void DashMeleeMonster::OnRender()
{
	BaseMonster::DamageTextOut();
	//test용
#ifdef DEBUG
	if (IsAttack == true)
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

	//hp
	_GraphicEngine->D2DXDrawText(m_GameObject->GetPos().x, m_GameObject->GetPos().y - 100, 100, 100, D2D1::ColorF::Aqua, _T("HP::%d"), m_HP);
#endif // DEBUG
}

void DashMeleeMonster::Update()
{
	
	CheckDefenseIN();

	//MeleeMonster::Update();

	//melee update
	if (IsDead() == true)
	{
		if (m_DeadSoundOut == false)
		{
			DashMeleeMonster::Dead();
		}
		return; // testing 몬스터 를 사라지게해야함
	}


	BaseMonster::CheckWall();

	MeleeMonster::CheckAttacked();


	MeleeMonster::IsInReach();

	DashMeleeMonster::IsDetected();

	BaseMonster::Update();
	//

	CheckDefenseOUT();
	
	BaseMonster::DamageTextFlow();

}



void DashMeleeMonster::Move()
{
	MeleeMonster::Move();
}

void DashMeleeMonster::Dead()
{
#ifdef DEBUG
	Debug::Log("DashMelee Message :: DEAD");
#endif // DEBUG

	m_IsDead = true;
	if (m_DeadSprite->m_IsFinish == true)
	{
		m_DeadSoundOut = true;
		_FAudio->FPause(ENEMY_TUTLE_DIE);
		_FAudio->FPlaySound(ENEMY_TUTLE_DIE);
	}
	FlipAnimation();

	StopAllAnimation();
	m_DeadSprite->SetActive(true);
	m_DeadSprite->StartAnimation();

	m_DamageList.clear();

}

void DashMeleeMonster::IsDetected()
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
			if (_FAudio->FIsPlaying(ENEMY_TUTLE_RECOG) == false)
			{
				_FAudio->FPlaySound(ENEMY_TUTLE_RECOG);
			}
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



void DashMeleeMonster::CheckDefenseIN()
{
	
	if (m_Direction == BaseMonster::Direction::LEFT)
	{

		if (m_pLeftShieldCollider->m_Target.size() > 0)// 무조건 총알만 충돌함
		{

			if (m_IsDead == false)
			{
				if (_FAudio->FIsPlaying(OBJECT_BULLET_SHILD) == false)
				{
					MonsterText* temp = new MonsterText();
					temp->DamageTextX = m_GameObject->GetPos().x;
					temp->DamageTextY = m_GameObject->GetPos().y - 20;
					temp->Text = _T("BLOCK!");
					temp->IsGray = true;
					m_DamageList.push_back(temp);

					_FAudio->FPlaySound(OBJECT_BULLET_SHILD);
				}
			}
			m_pHitCollider->SetActive(false);

		}

	}
	else
	{
		if (m_pRightShieldCollider->m_Target.size() > 0)// 무조건 총알만 충돌함
		{

			if (m_IsDead == false)
			{
				if (_FAudio->FIsPlaying(OBJECT_BULLET_SHILD) == false)
				{
					MonsterText* temp = new MonsterText();
					temp->DamageTextX = m_GameObject->GetPos().x;
					temp->DamageTextY = m_GameObject->GetPos().y - 20;
					temp->Text = _T("BLOCK!");
					temp->IsGray = true;
					m_DamageList.push_back(temp);
					_FAudio->FPlaySound(OBJECT_BULLET_SHILD);
				}
			}
			m_pHitCollider->SetActive(false);
		}
	}
}

void DashMeleeMonster::CheckDefenseOUT()
{
	if (m_Direction == BaseMonster::Direction::LEFT)
	{
		if (m_pRightShieldCollider->m_Target.size() > 0)// 오른쪽
		{
			m_pHitCollider->SetActive(true);
		}
	}
	else
	{
		if (m_pLeftShieldCollider->m_Target.size() > 0)
		{
			m_pHitCollider->SetActive(true);
		}

	}
}

void DashMeleeMonster::PushPlayer()
{

	if (fabs(m_GameObject->GetPos().x - m_Player->GetPos().x) < 50 || fabs(m_GameObject->GetPos().y - m_Player->GetPos().y) < 30)
	{
		if (m_Direction == BaseMonster::Direction::LEFT)
		{
			m_Player->SetPos(D2D1::Point2F(m_Player->GetPos().x - 300, m_Player->GetPos().y));
		}
		else
		{
			m_Player->SetPos(D2D1::Point2F(m_Player->GetPos().x + 300, m_Player->GetPos().y));
		}
	}

}



void DashMeleeMonster::Dash()
{
#ifdef DEBUG
	Debug::Log("Tutle Message :: Dash Attacking");
#endif // DEBUG

	//m_DashDelay -= _FTime->GetEngineFixedDeltaTimeSec();
	//m_DashTime -= _FTime->GetEngineFixedDeltaTimeSec();


	if (m_AttackSprite->m_IsFinish == true)
	{
		if (_FAudio->FIsPlaying(ENEMY_TUTLE_ATTK) == false)
		{
			_FAudio->FPlaySound(ENEMY_TUTLE_ATTK);
		}
		//DashSoundOut = true;
		//m_MoveStop = false;
		m_AttackSprite->StopAnimation();
		m_Player->GetComponent<Player>()->Damage(1);

		PushPlayer();
	}



	Vector2 moveVector;

	if (m_Direction == BaseMonster::Direction::LEFT)
	{
		moveVector = Vector2(-1, 0) * (m_MoveSpeed + m_DashSpeed) * _FTime->GetEngineFixedDeltaTimeSec();

		//m_GameObject->SetPos(D2D1::Point2F(m_GameObject->GetPos().x - m_DashSpeed, m_GameObject->GetPos().y));
	}
	else if (m_Direction == BaseMonster::Direction::RIGHT)
	{
		moveVector = Vector2(1, 0) * (m_MoveSpeed + m_DashSpeed) * _FTime->GetEngineFixedDeltaTimeSec();
		//m_GameObject->SetPos(D2D1::Point2F(m_GameObject->GetPos().x + m_DashSpeed, m_GameObject->GetPos().y));
	}

	Rigidbody* rigidbody = m_GameObject->GetComponent<Rigidbody>();
	rigidbody->AddForce(moveVector);


	if (m_HitFinish == true)
	{
		//sprite set

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


void DashMeleeMonster::OnDestroy()
{

	SafeRelease(&m_MoveSprite);
	SafeRelease(&m_AttackSprite);
	SafeRelease(&m_HitedSprite);
	SafeRelease(&m_DeadSprite);
}

void DashMeleeMonster::StopAllAnimation()
{
	m_MoveSprite->SetActive(false);
	m_AttackSprite->SetActive(false);
	m_HitedSprite->SetActive(false);
	m_DeadSprite->SetActive(false);
}



