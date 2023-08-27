#include "GamePCH.h"
#include "RangedMonster.h"

void RangedMonster::InitBullets()
{
	for (int i = 0; i < TANKMAXBULLET; i++)
	{
		m_TankBullets.push_back(ObjectFactory::CreateObject<GameObject>());
		m_TankBullets[i]->AddComponent<TankBullet>()->SetActive(false);
		m_TankBullets[i]->SetStringTag("EnemyBullet");
		m_TankBullets[i]->GetComponent<TankBullet>()->m_Damage = TANKBULLETPOWER;
		m_TankBullets[i]->SetPos(m_GameObject->GetPos());
		m_TankBullets[i]->GetComponent<TankBullet>()->m_Damage = 1;
		m_TankBullets[i]->GetComponent<TankBullet>()->m_LerpTimeScale = 10.0f;
		m_TankBullets[i]->GetComponent<TankBullet>()->m_IsMoveToWeapon = true;
	}

}

void RangedMonster::InitProperties()
{
	m_GameObject->SetStringTag("Tank");
	m_GameObject->m_pTransform->SetScale(1, 1);

	//m_GameObject->m_pTransform->SetPos(rand()%1000+100, 150);
	m_GameObject->m_pTransform->SetPos(1000, 150); //우측넣기
	//m_GameObject->m_pTransform->SetPos(300, 150);

	//속성값설정
	m_HP = 1500 * 0.8;
	m_MoveSpeed = 100 * 1.2;
	m_TrackingSpeed = 200;
	m_AttackedDlay = 3.0f; // 쓸라면 쓰시오

	m_DetectReach = D2D1::SizeF(800 * 1.2, 500 * 1.2);
	m_AttackReach = D2D1::SizeF(800 * 1.2, 500 * 1.2);
	

}
void RangedMonster::InitColliders()
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

	//platform 만 체크해야함

	m_pLeftCliffCheckCollider = this->m_GameObject->AddComponent<BoxCollider>();
	m_pLeftCliffCheckCollider->SetRect(D2D1::Point2F(-150, 90), D2D1::SizeF(50, 20));
	m_pLeftCliffCheckCollider->SetTrigger(false);
	m_pLeftCliffCheckCollider->SetStringTag("Move Collider");
	m_pLeftCliffCheckCollider->AddIgnoreTag("Jump Collider");
	m_pLeftCliffCheckCollider->AddIgnoreTag("Move Collider");
	m_pLeftCliffCheckCollider->AddIgnoreTag("Head Collider");
	m_pLeftCliffCheckCollider->AddIgnoreTag("Player");
	m_pLeftCliffCheckCollider->AddIgnoreTag("Bullet");
	m_pLeftCliffCheckCollider->AddIgnoreTag("Weapon");
	m_pLeftCliffCheckCollider->AddIgnoreTag("Switch");
	m_pLeftCliffCheckCollider->AddIgnoreTag("Gate");
	m_pLeftCliffCheckCollider->AddIgnoreTag("Bear");
	m_pLeftCliffCheckCollider->AddIgnoreTag("Crane");
	m_pLeftCliffCheckCollider->AddIgnoreTag("Turtle");
	m_pLeftCliffCheckCollider->AddIgnoreTag("Tank");
#ifdef _DEBUG
	m_pLeftCliffCheckCollider->SetDebugDraw();
#endif

	//platform 만 체크해야함

	m_pRightCliffCheckCollider = this->m_GameObject->AddComponent<BoxCollider>();
	m_pRightCliffCheckCollider->SetRect(D2D1::Point2F(150, 90), D2D1::SizeF(50, 20));
	m_pRightCliffCheckCollider->SetTrigger(false);
	m_pRightCliffCheckCollider->SetStringTag("Move Collider");
	m_pRightCliffCheckCollider->AddIgnoreTag("Jump Collider");
	m_pRightCliffCheckCollider->AddIgnoreTag("Move Collider");
	m_pRightCliffCheckCollider->AddIgnoreTag("Head Collider");
	m_pRightCliffCheckCollider->AddIgnoreTag("Player");
	m_pRightCliffCheckCollider->AddIgnoreTag("Bullet");
	m_pRightCliffCheckCollider->AddIgnoreTag("Weapon");
	m_pRightCliffCheckCollider->AddIgnoreTag("Switch");
	m_pRightCliffCheckCollider->AddIgnoreTag("Gate");
	m_pRightCliffCheckCollider->AddIgnoreTag("Bear");
	m_pRightCliffCheckCollider->AddIgnoreTag("Crane");
	m_pRightCliffCheckCollider->AddIgnoreTag("Turtle");
	m_pRightCliffCheckCollider->AddIgnoreTag("Tank");
#ifdef _DEBUG
	m_pRightCliffCheckCollider->SetDebugDraw();
#endif


	m_pRigidBody->m_TargetCollider.push_back(m_pJumpCollider);
	m_pRigidBody->m_TargetCollider.push_back(m_pMoveCollider);

}


void RangedMonster::InitSprites()
{
	m_MoveSprite = m_GameObject->AddComponent<Sprite>();
	m_MoveSprite->LoadSprite(_T("tank_move.txt"), _T("tank_move.png"), _T("tank"));
	m_MoveSprite->StopAnimation();
	m_MoveSprite->SetActive(false);


	m_AttackSprite = m_GameObject->AddComponent<Sprite>();
	m_AttackSprite->LoadSprite(_T("tank_attack.txt"), _T("tank_attack.png"), _T("tank"));
	m_AttackSprite->m_IsPlayOnce = true;
	m_AttackSprite->StopAnimation();
	m_AttackSprite->SetActive(false);

	m_HitedSprite = m_GameObject->AddComponent<Sprite>();
	m_HitedSprite->LoadSprite(_T("tank_hit.txt"), _T("tank_hit.png"), _T("tank"));
	m_HitedSprite->m_IsPlayOnce = true;
	m_HitedSprite->StopAnimation();
	m_HitedSprite->SetActive(false);

	m_DeadSprite = m_GameObject->AddComponent<Sprite>();
	m_DeadSprite->LoadSprite(_T("tank_die.txt"), _T("tank_die.png"), _T("tank"));
	m_DeadSprite->m_IsPlayOnce = true;
	m_DeadSprite->StopAnimation();
	m_DeadSprite->SetActive(false);



}


void RangedMonster::Awake()
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
	auto rangedAtckAction = new BrainTree::RangeAttackAction(this);
	auto moveAction = new BrainTree::MoveAction(this);
	auto trackingAction = new BrainTree::TrackingAction(this);


	//Make node
	AttackSequence->addChild(meleeAtkChecker);
	AttackSequence->addChild(rangedAtckAction);
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

	//탄환설정
	InitBullets();
}

void RangedMonster::Update()
{
	if (IsDead() == true)
	{
		if (m_DeadSoundOut == false)
		{
			RangedMonster::Dead();
		}
		return; // testing 몬스터 를 사라지게해야함
	}

	
	CheckCliff();
	
	SetShoot();

	BaseMonster::CheckWall();

	MeleeMonster::CheckAttacked();

	MeleeMonster::IsInReach();

	//RangedMonster::IsDetected();
	
	MeleeMonster::Update();

	BaseMonster::DamageTextFlow();

}

void RangedMonster::OnRender()
{
	BaseMonster::DamageTextOut();
#ifdef DEBUG

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

	// attack point 
	_GraphicEngine->D2DXDrawRectrangle(m_ShootPointLeft.x, m_ShootPointLeft.y, 20, 20
		, D2D1::ColorF::Blue, D2D1::ColorF::Blue);

	_GraphicEngine->D2DXDrawRectrangle(m_ShootPointRight.x, m_ShootPointRight.y, 20, 20
		, D2D1::ColorF::Blue, D2D1::ColorF::Blue);



	//HP

	_GraphicEngine->D2DXDrawText(m_GameObject->GetPos().x, m_GameObject->GetPos().y - 100, 100, 100, D2D1::ColorF::Aqua, _T("HP::%d"), m_HP);

#endif // DEBUG

}

void RangedMonster::OnDestroy()
{
	MeleeMonster::OnDestroy();

	for (int i = 0; i < TANKMAXBULLET; i++)
	{
		ObjectManager::GetInstance()->Destroy(&m_TankBullets[i]);
	}
}

void RangedMonster::CheckCliff()
{
	if (m_Direction == BaseMonster::Direction::LEFT)
	{
		if (m_pLeftCliffCheckCollider->m_Target.size() == 0)// 무조건 플랫폼, floor 만 체크
		{
			m_Direction = BaseMonster::Direction::RIGHT;
		}
	}
	else
	{
		if (m_pRightCliffCheckCollider->m_Target.size() == 0)// 무조건 플랫폼, floor 만 체크
		{
			m_Direction = BaseMonster::Direction::LEFT;
		}
	}
}

void RangedMonster::SetShoot()
{
	D2D1_POINT_2F pointOffset = D2D1::Point2F(60.f,-50.f);
	
	m_ShootPointLeft = D2D1::Point2F(m_GameObject->GetPos().x - pointOffset.x - 30.f, m_GameObject->GetPos().y + pointOffset.y);
	m_ShootPointRight = D2D1::Point2F(m_GameObject->GetPos().x + pointOffset.x, m_GameObject->GetPos().y + pointOffset.y);


	for (int i = 0; i < TANKMAXBULLET; i++)
	{
		if (m_TankBullets[i]->GetComponent<TankBullet>()->m_IsScreenBoarder == true)
		{
			m_TankBullets[i]->GetComponent<TankBullet>()->m_IsMoving = false;
			m_TankBullets[i]->GetComponent<TankBullet>()->SetActive(false);
			m_TankBullets[i]->GetComponent<TankBullet>()->DisableSprite();
		}

		//m_TankBullets[i]->GetComponent<TankBullet>()->SetActive(false);

		//if (m_TankBullets[i]->GetComponent<TankBullet>()->m_GameObject->GetPos().x >= 1850
		//	|| m_TankBullets[i]->GetComponent<TankBullet>()->m_GameObject->GetPos().x <= 30
		//	|| m_TankBullets[i]->GetComponent<TankBullet>()->m_GameObject->GetPos().y <= 30
		//	|| m_TankBullets[i]->GetComponent<TankBullet>()->m_GameObject->GetPos().y >= 980
		//	)
		//{
		//	m_TankBullets[i]->GetComponent<TankBullet>()->m_IsMoving = false;
		//	m_TankBullets[i]->GetComponent<TankBullet>()->SetActive(false);
		//	m_TankBullets[i]->GetComponent<TankBullet>()->m_pCollider->SetActive(false);
		//	m_TankBullets[i]->GetComponent<TankBullet>()->DisableSprite();
		//
		//}

	}
	
}

void RangedMonster::Dead()
{
#ifdef DEBUG
	Debug::Log("Melee Message :: DEAD");
#endif // DEBUG

	if (m_DeadSprite->m_IsFinish == true)
	{
		m_DeadSoundOut = true;
		_FAudio->FPause(ENEMY_TANK_DIE);
		_FAudio->FPlaySound(ENEMY_TANK_DIE);

	}

	m_IsDead = true;

	FlipAnimation();

	StopAllAnimation();
	m_DeadSprite->SetActive(true);
	m_DeadSprite->StartAnimation();


	for (int i = 0; i < TANKMAXBULLET; i++)
	{
		m_TankBullets[i]->GetComponent<TankBullet>()->SetActive(false);	
		m_TankBullets[i]->GetComponent<TankBullet>()->DisableSprite();
	}

	m_DamageList.clear();
}

void RangedMonster::IsDetected()
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
			_FAudio->FPlaySound(ENEMY_CRANE_RECOG);
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


void RangedMonster::RangeAttack()
{
	//shot 세팅

	if (m_Direction == BaseMonster::Direction::LEFT)
	{
		if (m_TankBullets[0]->GetComponent<TankBullet>()->IsActive() == false)
		{
			m_TankBullets[0]->GetComponent<TankBullet>()->SetStartPosition(m_ShootPointLeft);
			m_TankBullets[0]->GetComponent<TankBullet>()->SetDestination(D2D1::Point2F(-50, m_ShootPointLeft.y));
		}
		if (m_TankBullets[1]->GetComponent<TankBullet>()->IsActive() == false)
		{
			m_TankBullets[1]->GetComponent<TankBullet>()->SetStartPosition(m_ShootPointLeft);
			m_TankBullets[1]->GetComponent<TankBullet>()->SetDestination(D2D1::Point2F(-50, m_ShootPointLeft.y- 400));
		}
		if (m_TankBullets[2]->GetComponent<TankBullet>()->IsActive() == false)
		{
			m_TankBullets[2]->GetComponent<TankBullet>()->SetStartPosition(m_ShootPointLeft);
			m_TankBullets[2]->GetComponent<TankBullet>()->SetDestination(D2D1::Point2F(-50, m_ShootPointLeft.y + 400));
		}
	}
	else
	{

		if (m_TankBullets[0]->GetComponent<TankBullet>()->IsActive() == false)
		{
			m_TankBullets[0]->GetComponent<TankBullet>()->SetStartPosition(m_ShootPointRight);
			m_TankBullets[0]->GetComponent<TankBullet>()->SetDestination(D2D1::Point2F(1990, m_ShootPointRight.y));
		}
		if (m_TankBullets[1]->GetComponent<TankBullet>()->IsActive() == false)
		{
			m_TankBullets[1]->GetComponent<TankBullet>()->SetStartPosition(m_ShootPointRight);
			m_TankBullets[1]->GetComponent<TankBullet>()->SetDestination(D2D1::Point2F(1990, m_ShootPointRight.y - 400));
		}

		if (m_TankBullets[2]->GetComponent<TankBullet>()->IsActive() == false)
		{
			m_TankBullets[2]->GetComponent<TankBullet>()->SetStartPosition(m_ShootPointRight);
			m_TankBullets[2]->GetComponent<TankBullet>()->SetDestination(D2D1::Point2F(1990, m_ShootPointRight.y + 400));
		}

	}

	//shoot

	if (_FAudio->FIsPlaying(ENEMY_TANK_ATTK_1) == false)
	{
		_FAudio->FPlaySound(ENEMY_TANK_ATTK_1);
	}


	for (int i = 0; i < TANKMAXBULLET; i++)
	{
		if (m_TankBullets[i]->GetComponent<TankBullet>()->IsActive() == false)
		{
			m_TankBullets[i]->GetComponent<TankBullet>()->m_IsScreenBoarder = false;
			m_TankBullets[i]->GetComponent<TankBullet>()->SetActive(true);
			m_TankBullets[i]->GetComponent<TankBullet>()->MoveStart();
		}
	}

}

void RangedMonster::Move()
{
	MeleeMonster::Move();
}


