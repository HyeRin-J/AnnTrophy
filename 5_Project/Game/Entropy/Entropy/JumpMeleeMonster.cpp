#include "GamePCH.h"
#include "JumpMeleeMonster.h"

void JumpMeleeMonster::InitProperties()
{
	m_GameObject->SetStringTag("Crane");
	m_GameObject->m_pTransform->SetScale(1, 1);

	//m_GameObject->m_pTransform->SetPos(rand()%1000+100, 150);
	//m_GameObject->m_pTransform->SetPos(1000,150); //우측넣기
	m_GameObject->m_pTransform->SetPos(300, 150);

	//속성값설정
	m_HP = 1500 * 0.8;
	m_MoveSpeed = 300 * 1.2;
	m_TrackingSpeed = 100;
	m_AttackedDlay = 5.0f;

	m_JumpSpeed = 200;
	//m_AttackReach = D2D1::SizeF(400, 200); 
	m_DetectReach = D2D1::SizeF(600, 10);

}

void JumpMeleeMonster::InitColliders()
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
	m_pJumpCollider->SetRect(D2D1::Point2F(0, 45), D2D1::SizeF(30, 40));
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
	//위에 플랫폼이랑 충돌하는지 헤드로 체크
	m_HeadCollider = m_GameObject->AddComponent<BoxCollider>();
	m_HeadCollider->SetRect(D2D1::Point2F(0, -150), D2D1::SizeF(50, 250));
	//m_HeadCollider->SetRect(D2D1::Point2F(0, -200), D2D1::SizeF(50, 200));
	m_HeadCollider->SetTrigger(false);
	m_HeadCollider->SetStringTag("Head Collider");
	m_HeadCollider->AddIgnoreTag("Jump Collider");
	m_HeadCollider->AddIgnoreTag("Move Collider");
	m_HeadCollider->AddIgnoreTag("Hit Collider");
	m_HeadCollider->AddIgnoreTag("Bullet");
	m_HeadCollider->AddIgnoreTag("Player");
	m_HeadCollider->AddIgnoreTag("Weapon");
	m_HeadCollider->AddIgnoreTag("Switch");
	m_HeadCollider->AddIgnoreTag("Gate");
	m_HeadCollider->AddIgnoreTag("Bear");
	m_HeadCollider->AddIgnoreTag("Turtle"); // 플랫폼말고는 모두 ignore !!!
	m_HeadCollider->AddIgnoreTag("Crane");
	m_HeadCollider->AddIgnoreTag("Tank");
#ifdef _DEBUG
	m_HeadCollider->SetDebugDraw();
#endif

	m_pRigidBody->m_TargetCollider.push_back(m_pJumpCollider);
	m_pRigidBody->m_TargetCollider.push_back(m_pMoveCollider);
	//m_pRigidBody->m_TargetCollider.push_back(m_HeadCollider);
}

void JumpMeleeMonster::InitSprites()
{
	m_MoveSprite = m_GameObject->AddComponent<Sprite>();
	m_MoveSprite->LoadSprite(_T("crane_move.txt"), _T("crane_move.png"), _T("crane"));
	m_MoveSprite->StopAnimation();
	m_MoveSprite->SetActive(false);


	m_AttackSprite = m_GameObject->AddComponent<Sprite>();
	m_AttackSprite->LoadSprite(_T("crane_attack.txt"), _T("crane_attack.png"), _T("crane"));
	m_AttackSprite->m_IsPlayOnce = true;
	m_AttackSprite->StopAnimation();
	m_AttackSprite->SetActive(false);

	m_HitedSprite = m_GameObject->AddComponent<Sprite>();
	m_HitedSprite->LoadSprite(_T("crane_hit.txt"), _T("crane_hit.png"), _T("crane"));
	m_HitedSprite->m_IsPlayOnce = true;
	m_HitedSprite->StopAnimation();
	m_HitedSprite->SetActive(false);

	m_DeadSprite = m_GameObject->AddComponent<Sprite>();
	m_DeadSprite->LoadSprite(_T("crane_die.txt"), _T("crane_die.png"), _T("crane"));
	m_DeadSprite->m_IsPlayOnce = true;
	m_DeadSprite->StopAnimation();
	m_DeadSprite->SetActive(false);


	m_JumpSprite = m_GameObject->AddComponent<Sprite>();
	m_JumpSprite->LoadSprite(_T("crane_jump.txt"), _T("crane_jump.png"), _T("crane"));
	m_JumpSprite->m_IsPlayOnce = true;
	m_JumpSprite->StopAnimation();
	m_JumpSprite->SetActive(false);

}



void JumpMeleeMonster::Awake()
{
	///Behaivor Tree

	m_Player = SceneObjectManager::GetInstance()->m_pPlayerObject;

	//root
	auto rootSequence = new BrainTree::Selector();

	//Sequence
	auto PlatformJumpSequence = new BrainTree::Sequence();
	auto moveSequence = new BrainTree::Sequence();
	auto AttackSequence = new BrainTree::Sequence();


	//checkers
	auto topPlatformChecker = new BrainTree::TopPlatformChecker();
	auto moveChecker = new BrainTree::MoveChecker();
	auto detectChecker = new BrainTree::DetectChecker(); // attack 거리재는용

	//actions 
	auto jumpAction = new BrainTree::JumpAction(this); // 플랫폼 올라가는 용
	auto moveAction = new BrainTree::MoveAction(this);
	auto jumpAtkAction = new BrainTree::JumpAttackAction(this);

	//Make node
	PlatformJumpSequence->addChild(topPlatformChecker);
	PlatformJumpSequence->addChild(jumpAction);
	rootSequence->addChild(PlatformJumpSequence);

	AttackSequence->addChild(detectChecker);
	AttackSequence->addChild(jumpAtkAction);
	rootSequence->addChild(AttackSequence);

	moveSequence->addChild(moveChecker);
	moveSequence->addChild(moveAction);
	rootSequence->addChild(moveSequence);


	m_BehaviorTree.setRoot(rootSequence);


	//속성들
	InitProperties();

	//콜라이더들 설정
	InitColliders();

	//Sprite setting
	InitSprites();
}

void JumpMeleeMonster::Update()
{

	BaseMonster::CheckMapOut();

	if (IsDead() == true)
	{
		if (m_DeadSoundOut == false)
		{
			JumpMeleeMonster::Dead();
		}
		return; // testing 몬스터 를 사라지게해야함
	}


	BaseMonster::CheckWall();

	MeleeMonster::CheckAttacked();

	DetectPlayer();

	if (IsJumpAttacking == false && CheckTopPlatform() == false)
	{
		SetActiveAllCollider(true);
	}
	else 
	{
		SetActiveAllCollider(false);
	}

	BaseMonster::Update();


	BaseMonster::DamageTextFlow();
}



bool JumpMeleeMonster::CheckTopPlatform()
{

	if (m_HeadCollider->IsCrash() && IsJumpAttacking == false) // 충돌체크를 플랫폼만이랑 해야됨!
	{
		IsJumping = true;
		m_jumpTime += _FTime->GetEngineFixedDeltaTimeSec();

		// 위에있는 부딪힌 플랫폼중 가장아래꺼 찾기

		float min = 0; // magic number
		Collider* minColl = nullptr;

		auto targets = m_HeadCollider->m_Target;

		for (int i = 0; i < targets.size(); i++)
		{

			if (targets[i]->m_Center.y > min)
			{
				min = targets[i]->m_Center.y;
				minColl = targets[i];
			}

		}

		m_JumpTarget = minColl;
		

		m_JumpDest = m_GameObject->GetPos();

		m_HeadCollider->SetActive(false);


		for (int i = 0; i < m_MessageQueue.size(); i++)
		{
			m_MessageQueue.pop();
		}
		m_MessageQueue.push(BTEventMessage::DetectedTopPlatform());


		return true;
	}
	else
	{
		m_JumpTarget = nullptr;
		IsJumping = false;
		m_jumpTime = 0.f;
		m_JumpDest = m_GameObject->GetPos();

	

		return false;
	}
}

void JumpMeleeMonster::DetectPlayer()
{
	m_DetectDelay -= _FTime->GetEngineFixedDeltaTimeSec();

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

		//jump attacking 초기 세팅
		if (m_DetectDelay <= 0.f)
		{

			_FAudio->FPlaySound(ENEMY_CRANE_ATTK);

			IsJumpAttacking = true;
			m_DetectDelay = 1.0f;
			m_PrevPlayerPos = m_Player->GetPos();
			m_PrevMonsterPos = m_GameObject->GetPos();
		}
	}

	if (IsJumpAttacking == true)
	{

		for (int i = 0; i < m_MessageQueue.size(); i++)
		{
			m_MessageQueue.pop();
		}
	

		m_MessageQueue.push(BTEventMessage::FindPlayerMessage());
	}
	else
	{

		m_MessageQueue.push(BTEventMessage::MoveMessage());
	}

}

void JumpMeleeMonster::Move()
{
	if(IsJumpAttacking == false)
	BaseMonster::Move();

	FlipAnimation();

	StopAllAnimation();

	m_MoveSprite->SetActive(true);
	m_MoveSprite->StartAnimation();

}

void JumpMeleeMonster::Dead()
{
#ifdef DEBUG
	Debug::Log("Crane Message :: DEAD");
#endif // DEBUG

	if (m_DeadSprite->m_IsFinish == true)
	{
		m_DeadSoundOut = true;
		_FAudio->FPause(ENEMY_CRANE_DIE);
		_FAudio->FPlaySound(ENEMY_CRANE_DIE);

	}

	FlipAnimation();

	StopAllAnimation();
	m_DeadSprite->SetActive(true);
	m_DeadSprite->StartAnimation();

	m_DamageList.clear();
}

void JumpMeleeMonster::Jump()
{

	if (IsJumping == true && m_JumpTarget != nullptr)
	{

		D2D1_POINT_2F SrcPos = m_GameObject->GetPos();
		D2D1_POINT_2F DestPos = m_JumpTarget->m_Center;

		// 뛰는곳 위치조정

		if (m_Direction == BaseMonster::Direction::RIGHT)
		{
			DestPos.x = DestPos.x - (m_JumpTarget->m_Size.width / 3);
		}
		else
		{
			DestPos.x = DestPos.x + (m_JumpTarget->m_Size.width / 3);
		}


		//test
		if (DestPos.y <= m_JumpTarget->m_Center.y)
		{
			DestPos.y -= (m_pHitCollider->m_Size.height+ m_JumpTarget->m_Size.height);
		}

		//test
		m_destPos = DestPos;

		Vector2 pos = Vector2::Lerp(Vector2(SrcPos.x, SrcPos.y), Vector2(DestPos.x, DestPos.y), m_jumpTime);


		//test
		m_middlePos.x = pos.x;
		m_middlePos.y = pos.y;


		if (DestPos.x == pos.x && DestPos.y == pos.y)
		{
			SetActiveAllCollider(true);
		}
		else
		{
			SetActiveAllCollider(false);
		}

		m_GameObject->m_pTransform->SetPos(pos.x, pos.y);

		StopAllAnimation();
		m_JumpSprite->SetActive(true);
		m_JumpSprite->StartAnimation();
	}

	if (m_JumpSprite->m_IsFinish == false)
	{
		_FAudio->FPause(ENEMY_CRANE_JUMP);
		_FAudio->FPlaySound(ENEMY_CRANE_JUMP);
	}



}


void JumpMeleeMonster::JumpAttack()
{

	if (IsJumpAttacking == true)
	{
		m_JumpATKTime += _FTime->GetEngineFixedDeltaTimeSec();

		double distance;

		D2D1_POINT_2F TargetPos;
		if (m_GameObject->GetPos().x <= m_Player->GetPos().x) // 플레이어가 오른쪽에있다.
		{

			distance = m_PrevPlayerPos.x - m_PrevMonsterPos.x;

			this->m_Direction = Direction::RIGHT;
			
			FlipAnimation();
			
			TargetPos = D2D1::Point2F(m_PrevMonsterPos.x + distance/2, m_PrevMonsterPos.y - 200);
		}
		else
		{
			distance = m_PrevMonsterPos.x - m_PrevPlayerPos.x;

			this->m_Direction = Direction::LEFT;

			FlipAnimation();

			TargetPos = D2D1::Point2F(m_PrevMonsterPos.x - distance/2, m_PrevMonsterPos.y - 200);
		}


		m_LerpTarget = TargetPos; //중간지점


		Vector2 pos = Vector2::Lerp(Vector2(m_PrevMonsterPos.x, m_PrevMonsterPos.y), Vector2(TargetPos.x, TargetPos.y), m_JumpATKTime / 0.2f);


		//test
		if (m_PrevMonsterPos.y <= pos.y)
		{
			pos.y = m_PrevMonsterPos.y;
		}


		if (IsAttackJumpFinish == false && fabs(pos.x - m_LerpTarget.x) <= 1.f && fabs(pos.y - m_LerpTarget.y) <= 1.f)
		{
			IsAttackJumpFinish = true;
			m_PrevMonsterPos = m_GameObject->GetPos();
			m_JumpATKTime = 0;
		}

		if (IsAttackJumpFinish)
		{
			pos = Vector2::Lerp(Vector2(m_PrevMonsterPos.x, m_PrevMonsterPos.y), Vector2(m_PrevPlayerPos.x, m_PrevPlayerPos.y), m_JumpATKTime / 0.1f);
			
		}

		m_GameObject->m_pTransform->SetPos(pos.x, pos.y);

		if (fabs(pos.x - m_PrevPlayerPos.x) <= 1.f && fabs(pos.y - m_PrevPlayerPos.y) <= 1.f) // 목표도달
		//if (m_JumpATKTime >= 1.f)
		{		
			m_PrevMonsterPos = m_GameObject->GetPos();
			IsAttackJumpFinish = false;
			IsJumpAttacking = false;
			m_JumpATKTime = 0.f;
			m_DetectDelay = 2.0f;

			m_HeadCollider->SetActive(true);

			for (int i = 0; i < m_MessageQueue.size(); i++)
			{
				m_MessageQueue.pop();
			}

			
			m_Player->GetComponent<Player>()->Damage(1);
			PushMe();

		}

	
		FlipAnimation();

		StopAllAnimation();

		m_AttackSprite->SetActive(true);
		m_AttackSprite->StartAnimation();

	}


}

void JumpMeleeMonster::PushMe()
{
	if (fabs(m_GameObject->GetPos().x - m_Player->GetPos().x) < 50 || fabs(m_GameObject->GetPos().y - m_Player->GetPos().y) < 30)
	{
		if (m_Direction == BaseMonster::Direction::LEFT)
		{
			m_GameObject->SetPos(D2D1::Point2F(m_Player->GetPos().x - 100, m_Player->GetPos().y));
		}
		else
		{
			m_GameObject->SetPos(D2D1::Point2F(m_Player->GetPos().x + 100, m_Player->GetPos().y));
		}
	}


}

void JumpMeleeMonster::OnDestroy()
{
	SafeRelease(&m_MoveSprite);
	SafeRelease(&m_AttackSprite);
	SafeRelease(&m_HitedSprite);
	SafeRelease(&m_DeadSprite);
	SafeRelease(&m_JumpSprite);
}

void JumpMeleeMonster::OnRender()
{
	BaseMonster::DamageTextOut();
#ifdef DEBUG
	// 인식범위 표시
	auto tempX = m_GameObject->GetPos().x - (m_DetectReach.width / 2);
	auto tempY = m_GameObject->GetPos().y - (m_DetectReach.height / 2);

	_GraphicEngine->D2DXDrawRectrangle(tempX, tempY, m_DetectReach.width, m_DetectReach.height
		, D2D1::ColorF::Pink, D2D1::ColorF::Pink);



	if (m_JumpTarget != nullptr)
	{

		//뛸목표
		auto temp1X = m_JumpTarget->m_Center.x;
		auto temp1Y = m_JumpTarget->m_Center.y;

		_GraphicEngine->D2DXDrawRectrangle(temp1X, temp1Y, 50, 50
			, D2D1::ColorF::Red, D2D1::ColorF::Red);

		//실제 뛸 중간 좌표

		_GraphicEngine->D2DXDrawRectrangle(m_middlePos.x, m_middlePos.y, 50, 50
			, D2D1::ColorF::Red, D2D1::ColorF::Red);

		//실제 뛸 목표 좌표
		_GraphicEngine->D2DXDrawRectrangle(m_destPos.x, m_destPos.y, 50, 50
			, D2D1::ColorF::DarkGray, D2D1::ColorF::DarkGray);


	}


	//뛸목표
	auto jumpatkx = m_PrevPlayerPos.x;
	auto jumpatky = m_PrevPlayerPos.y;

	_GraphicEngine->D2DXDrawRectrangle(jumpatkx, jumpatky, 50, 50
		, D2D1::ColorF::Black, D2D1::ColorF::Black);

	//실제 뛸 중간 좌표

	_GraphicEngine->D2DXDrawRectrangle(m_LerpTarget.x, m_LerpTarget.y, 50, 50
		, D2D1::ColorF::Blue, D2D1::ColorF::Blue);

	//실제 뛸 목표 좌표
	_GraphicEngine->D2DXDrawRectrangle(m_PrevMonsterPos.x, m_PrevMonsterPos.y, 50, 50
		, D2D1::ColorF::Blue, D2D1::ColorF::Blue);

	//HP

	_GraphicEngine->D2DXDrawText(m_GameObject->GetPos().x, m_GameObject->GetPos().y - 100, 100, 100, D2D1::ColorF::Aqua, _T("HP::%d"), m_HP);




#endif // DEBUG
}

void JumpMeleeMonster::StopAllAnimation()
{
	m_MoveSprite->SetActive(false);
	m_AttackSprite->SetActive(false);
	m_HitedSprite->SetActive(false);
	m_DeadSprite->SetActive(false);
	m_JumpSprite->SetActive(false);
}

void JumpMeleeMonster::SetActiveAllCollider(bool _state)
{
	m_pRigidBody->SetActive(_state);
	m_pHitCollider->SetActive(_state);
	m_pJumpCollider->SetActive(_state);
	m_pMoveCollider->SetActive(_state);
	m_HeadCollider->SetActive(_state);
}
