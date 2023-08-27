#include "GamePCH.h"
#include "MovePlayer.h"

void MovePlayer::Awake()
{
	m_JumpCollider = this->m_GameObject->AddComponent<BoxCollider>();
	m_JumpCollider->SetRect(D2D1::Point2F(0, 50), D2D1::SizeF(50, 50));
	m_JumpCollider->SetTrigger(false);
	m_JumpCollider->SetStringTag("Jump Collider");
	m_JumpCollider->AddIgnoreTag("Move Collider");
	m_JumpCollider->AddIgnoreTag("Hit Collider");
	m_JumpCollider->AddIgnoreTag("Bullet");
	m_JumpCollider->AddIgnoreTag("Weapon");
	m_JumpCollider->AddIgnoreTag("Switch");
	m_JumpCollider->AddIgnoreTag("Gate");
	m_JumpCollider->AddIgnoreTag("Bear");
	m_JumpCollider->AddIgnoreTag("Turtle");
	m_JumpCollider->AddIgnoreTag("Crane");
	m_JumpCollider->AddIgnoreTag("Tank");
#ifdef _DEBUG
	m_JumpCollider->SetDebugDraw();
#endif

	m_MoveCollider = this->m_GameObject->AddComponent<BoxCollider>();
	m_MoveCollider->SetRect(D2D1::Point2F(0, 0), D2D1::SizeF(100, 32));
	m_MoveCollider->SetTrigger(false);
	m_MoveCollider->SetStringTag("Move Collider");
	m_MoveCollider->AddIgnoreTag("Jump Collider");
	m_MoveCollider->AddIgnoreTag("Hit Collider");
	m_MoveCollider->AddIgnoreTag("Bullet");
	m_MoveCollider->AddIgnoreTag("Weapon");
	m_MoveCollider->AddIgnoreTag("Switch");
	m_MoveCollider->AddIgnoreTag("Gate");
	m_MoveCollider->AddIgnoreTag("Bear");
	m_MoveCollider->AddIgnoreTag("Turtle");
	m_MoveCollider->AddIgnoreTag("Crane");
	m_MoveCollider->AddIgnoreTag("Tank");
#ifdef _DEBUG
	m_MoveCollider->SetDebugDraw();
#endif

	m_HeadCollider = m_GameObject->AddComponent<BoxCollider>();
	m_HeadCollider->SetRect(D2D1::Point2F(0, -100), D2D1::SizeF(50, 32));
	m_HeadCollider->SetTrigger(false);
	m_HeadCollider->SetStringTag("Head Collider");
	m_HeadCollider->AddIgnoreTag("Jump Collider");
	m_HeadCollider->AddIgnoreTag("Move Collider");
	m_HeadCollider->AddIgnoreTag("Hit Collider");
	m_HeadCollider->AddIgnoreTag("Bullet");
	m_HeadCollider->AddIgnoreTag("Weapon");
	m_HeadCollider->AddIgnoreTag("Switch");
	m_HeadCollider->AddIgnoreTag("Gate");
	m_HeadCollider->AddIgnoreTag("Bear");
	m_HeadCollider->AddIgnoreTag("Turtle");
	m_HeadCollider->AddIgnoreTag("Crane");
	m_HeadCollider->AddIgnoreTag("Tank");
#ifdef _DEBUG
	m_HeadCollider->SetDebugDraw();
#endif

	m_Rigidbody = this->m_GameObject->AddComponent<Rigidbody>();
	m_Rigidbody->SetCollisionMode(CollisionDetectionMode::AABB);
	m_Rigidbody->OnGravity();
	m_Rigidbody->SetFallMaxSpeed(10);

	m_Rigidbody->m_TargetCollider.push_back(m_JumpCollider);
	m_Rigidbody->m_TargetCollider.push_back(m_MoveCollider);
}

void MovePlayer::Update()
{
	//있으면 좌표 보정
	if (_FTime->m_EngineDeltaTimeScale <= 0) return;

	//제일 위에 있는 y 충돌체
	Collider* minYCol = nullptr;
	float minYPos = 1080;

	//충돌체 찾기
	for (auto col : m_JumpCollider->m_Target)
	{
		if (minYPos > (col->m_GameObject->GetPos().y + col->m_Center.y + m_Rigidbody->GetFallSpeed()) - (col->m_Size.height / 2 - m_JumpCollider->m_Size.height / 2))
		{
			minYPos = (col->m_GameObject->GetPos().y + col->m_Center.y + m_Rigidbody->GetFallSpeed()) - (col->m_Size.height / 2 - m_JumpCollider->m_Size.height / 2);
			minYCol = col;
		}
	}
	if (minYCol != nullptr)
	{
		//현재 거리
		float xDistance = (m_GameObject->GetPos().x + m_JumpCollider->m_Center.x) - (minYCol->m_GameObject->GetPos().x + minYCol->m_Center.x);
		float yDistance = (m_GameObject->GetPos().y + m_JumpCollider->m_Center.y) - (minYCol->m_GameObject->GetPos().y + minYCol->m_Center.y);

		//플레이어가 더 위에 있을 때만 점프가 끝난 것
		if (yDistance < 0 && abs(yDistance) <= m_JumpCollider->m_Size.height / 2 + minYCol->m_Size.height / 2 + 1.0f && abs(xDistance) <= m_JumpCollider->m_Size.width / 2 + minYCol->m_Size.width / 2)
		{
			//다음으로 떨어질 좌표
			float currBoundaryY = m_GameObject->GetPos().y + m_JumpCollider->m_Center.y + m_JumpCollider->m_Size.height / 2;
			//타겟의 콜라이더 위쪽 y좌표
			float targetBoundaryY = m_JumpCollider->m_GameObject->GetPos().y + m_JumpCollider->m_Center.y - m_JumpCollider->m_Size.height / 2;

			//선 충돌검사
			//점프 상태를 다 꺼준다
			if (currBoundaryY - m_Rigidbody->GetFallSpeed() * _FTime->GetEngineFixedDeltaTimeSec() <= targetBoundaryY <= currBoundaryY + m_Rigidbody->GetFallSpeed() * _FTime->GetEngineFixedDeltaTimeSec())
			{
				//m_JumpCollider->SetTrigger(false);
				if (m_IsJumping == true || m_IsDownJumping == true)
				{
					_FAudio->FPlaySound(ANN_LANDING);
				}
				m_IsJumping = false;
				m_IsDownJumping = false;
				m_MoveCollider->SetTrigger(false);
				m_JumpCollider->SetTrigger(false);
				m_RichMaxHeight = false;
				m_pPlayer->m_IsMoving = false;
				m_pPlayer->m_IsDoubleJump = false;
				m_pPlayer->m_JumpState = -1;
				m_MoveCollider->DeleteIgnoreTag("Platform");
				m_JumpCollider->DeleteIgnoreTag("Platform");
				//m_pPlayer->m_pAnimationController->SetCondition("Jump", false);
				//m_pPlayer->m_pAnimationController->SetCondition("Down Jump", false);
				//m_pPlayer->m_pAnimationController->SetCondition("Fall", false);
				//m_pPlayer->m_pAnimationController->SetCondition("Double Jump", false);
				m_JumpCount = 0;
				m_JumpStartPos = { 0, 0 };
				m_JumpTime = 0;
			}
		}
	}


	Vector2 moveVector;

	if (m_pPlayer->m_IsInteraction == false && m_pPlayer->m_IsConvert == false && m_pPlayer->m_IsDead == false)
	{
		if (InputManager::InputKey(VK_D))	//VK_D
		{
			moveVector = Vector2(1, 0) * m_MoveSpeed * _FTime->GetEngineFixedDeltaTimeSec();

			if (m_pPlayer->m_JumpState == -1 && _FAudio->FIsPlaying(ANN_MOVE) == false)
			{
				_FAudio->FPlaySound(ANN_MOVE);
			}
		}

		if (InputManager::InputKey(VK_A)) //VK_A
		{
			if (m_pPlayer->m_JumpState == -1 && _FAudio->FIsPlaying(ANN_MOVE) == false)
			{
				_FAudio->FPlaySound(ANN_MOVE);
			}
			moveVector = Vector2(-1, 0) * m_MoveSpeed * _FTime->GetEngineFixedDeltaTimeSec();
		}

		if (InputManager::InputKeyDown(VK_SHIFT))
		{
			if (m_IsDashCoolDown == false && m_IsDashMode == false)
			{
				_FAudio->FPlaySound(ANN_DASH);
				m_pPlayer->m_IsDash = true;
				m_IsDashMode = true;
				m_DashTime = m_StartDashTime;
				//Debug::LogFormat("Dash Start");
			}
		}
	}

	if (m_IsDashMode == true)
	{
		if (m_DashTime <= 0)
		{
			m_IsDashMode = false;
			m_IsDashCoolDown = true;
			m_pPlayer->m_IsDash = false;
			//Debug::LogFormat("Dash End");
		}
		else
		{
			m_DashTime -= _FTime->GetEngineFixedDeltaTimeSec();
			moveVector *= m_MoveSpeed * 1.1f * _FTime->GetEngineFixedDeltaTimeSec();
		}
	}
	else
	{
		if (m_IsDashCoolDown == true)
		{
			m_DashCoolTime -= _FTime->GetEngineFixedDeltaTimeSec();

			if (m_DashCoolTime <= 0)
			{
				m_DashCoolTime = 2.0f;
				m_IsDashCoolDown = false;
			}
		}
	}


	if (m_MoveCollider->IsCrash() == false || (m_MoveCollider->IsCrash() == true && m_MoveCollider->m_Target.size() > 0 && m_MoveCollider->m_Target[0]->IsTriggerOn() == true) ||
		m_IsJumping == true)
	{
		m_Rigidbody->AddForce(moveVector);

		if (moveVector.Length() <= 0)
		{
			m_pPlayer->m_IsMoving = false;
		}
		else
		{
			if (moveVector.x > 0)
			{
				m_pPlayer->m_Direction = 1;
			}
			else if (moveVector.x < 0)
			{
				m_pPlayer->m_Direction = -1;
			}

			m_pPlayer->m_IsMoving = true;
		}
	}

	if (m_pPlayer->m_IsDead == false && m_pPlayer->m_IsInteraction == false && m_pPlayer->m_IsConvert == false)
	{
		if (InputManager::InputKey(VK_S) == false && InputManager::InputKeyDown(VK_SPACE))
		{
			if (m_JumpCount < 2)
			{
				++m_JumpCount;
				if (m_JumpCount == 2)
				{
					m_pPlayer->m_IsDoubleJump = true;
					//m_pPlayer->m_pAnimationController->SetCondition("Double Jump", true);
					//m_pPlayer->m_pAnimationController->SetCondition("Jump", false);
					_FAudio->FPlaySound(ANN_JUMP_DOBLE);
				}
				else
				{
					//m_pPlayer->m_pAnimationController->SetCondition("Jump", true);
					_FAudio->FPlaySound(ANN_JUMP_NORMAL);
				}
				//Debug::LogFormat("JumpCount : %d\n", m_JumpCount);
				m_JumpTime = 0;
				m_RichMaxHeight = false;
				//m_MoveCollider->SetTrigger(true);
				m_JumpStartPos = { m_GameObject->GetPos().x, m_GameObject->GetPos().y };

				if (m_IsJumping == false)
				{
					m_IsJumping = true;
					//m_JumpCollider->AddIgnoreTag("Platform");
					m_MoveCollider->AddIgnoreTag("Platform");
					m_GameObject->m_pTransform->SetPos(m_JumpStartPos.x, m_JumpStartPos.y - 5);
				}
			}
		}

		if (m_JumpCollider->m_Target.size() > 0 && m_JumpCollider->m_Target[0]->GetStringTag()._Equal("Floor") == false &&
			InputManager::InputKey(VK_S) && InputManager::InputKeyDown(VK_SPACE))	//VK_S
		{
			_FAudio->FPlaySound(ANN_JUMP_BELOW);
			//m_JumpCollider->SetTrigger(true);
			//m_MoveCollider->SetTrigger(true);
			m_JumpTime = 0;

			m_JumpCollider->AddIgnoreTag("Platform");
			m_MoveCollider->AddIgnoreTag("Platform");
			//m_pPlayer->m_pAnimationController->SetCondition("Down Jump", true);
			//m_GameObject->m_pTransform->SetPos(m_GameObject->GetPos().x, m_GameObject->GetPos().y + TILE_SIZE * 5.5f);

			m_pPlayer->m_JumpState = 1;
			m_IsDownJumping = true;
		}
	}

	if (m_IsJumping == false)
	{
		//if (m_IsDownJumping == false)
		//{
		//	m_JumpCollider->DeleteIgnoreTag("Platform");
		//	m_MoveCollider->DeleteIgnoreTag("Platform");
		//}
		//else
		if (m_IsDownJumping == true)
		{
			m_JumpTime += _FTime->GetEngineFixedDeltaTimeSec();

			if (m_JumpTime >= 0.7f)
			{
				m_JumpCollider->DeleteIgnoreTag("Platform");
			}
		}
		else
		{
			m_MoveCollider->DeleteIgnoreTag("Platform");
		}
	}
	else
	{
		m_pPlayer->m_JumpState = 0;
		m_JumpTime += _FTime->GetEngineFixedDeltaTimeSec();
		//m_JumpCollider->SetTrigger(true);
		//m_MoveCollider->SetTrigger(true);

		if (m_GameObject->m_pTransform->GetPos().y - m_JumpStartPos.y < -128)
		{
			m_RichMaxHeight = true;
			//m_MoveCollider->SetTrigger(false);
		}

		if (m_HeadCollider->IsCrash())
		{
			m_IsJumping = false;
		}

		if (m_JumpTime <= 1.f && m_RichMaxHeight == false)
		{
			m_Rigidbody->SetFallSpeed(-m_JumpSpeed * _FTime->GetEngineFixedDeltaTimeSec());
			m_pPlayer->m_IsMoving = true;
		}
		//else
		//{
		//	m_JumpCollider->DeleteIgnoreTag("Platform");
		//	m_MoveCollider->DeleteIgnoreTag("Platform");
		//}
	}
}

void MovePlayer::OnRender()
{
}
