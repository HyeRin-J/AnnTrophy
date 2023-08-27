#include "GamePCH.h"
#include "Bullet.h"

void Bullet::Awake()
{
	m_GameObject->SetScale(D2D1::SizeF(0.5f, 0.5f));

	for (int i = 0; i < 2; ++i)
	{
		WCHAR imageName[256];
		m_Sprite.push_back(m_GameObject->AddComponent<Sprite>());
		swprintf_s(imageName, _T("bullet_sprite_%d.png"), i);
		m_Sprite[i]->LoadSprite(_T("bullet.txt"), imageName, _T("bullet"));
		m_Sprite[i]->SetActive(false);
		m_Sprite[i]->StartAnimation();

		m_FireSprite.push_back(m_GameObject->AddComponent<Sprite>());
		swprintf_s(imageName, _T("bullet_fire_sprite_%d.png"), i);
		m_FireSprite[i]->LoadSprite(_T("bullet_fire.txt"), imageName, _T("bullet"));
		m_FireSprite[i]->SetActive(false);
		m_FireSprite[i]->StartAnimation();

		m_HitSprite.push_back(m_GameObject->AddComponent<Sprite>());
		swprintf_s(imageName, _T("bullet_hit_sprite_%d.png"), i);
		m_HitSprite[i]->LoadSprite(_T("bullet_hit.txt"), imageName, _T("bullet"));
		m_HitSprite[i]->SetActive(false);
		m_HitSprite[i]->StartAnimation();
		m_HitSprite[i]->m_IsPlayOnce = true;

		if (i == 1)
		{
			m_Sprite[i]->m_IsInversePlay = true;
			m_FireSprite[i]->m_IsInversePlay = true;
			m_HitSprite[i]->m_IsInversePlay = true;
		}
	}

	m_pCollider = m_GameObject->AddComponent<BoxCollider>();
	m_pCollider->SetStringTag("Bullet");
	m_pCollider->AddIgnoreTag("Player");
	m_pCollider->AddIgnoreTag("Weapon");
	m_pCollider->AddIgnoreTag("Platform");
	m_pCollider->AddIgnoreTag("Jump Collider");
	m_pCollider->AddIgnoreTag("Move Collider");
	m_pCollider->AddIgnoreTag("Gate");
	m_pCollider->AddIgnoreTag("Switch");
	m_pCollider->SetRect(m_GameObject->GetPos(), D2D1::SizeF(50, 50));
#ifdef _DEBUG
	m_pCollider->SetDebugDraw();
#endif
	SetActive(false);
}

void Bullet::Update()
{
	m_FireSprite[_GameManager->m_CurrentState ^ 0x01]->SetActive(false);
	m_Sprite[_GameManager->m_CurrentState ^ 0x01]->SetActive(false);

	if (m_IsHit == true)
	{
		m_HitSprite[_GameManager->m_CurrentState]->SetActive(true);
		m_HitSprite[_GameManager->m_CurrentState]->StartAnimation();

		if (m_HitSprite[_GameManager->m_CurrentState]->m_IsFinish == true)
		{
			m_IsHit = false;
			m_HitSprite[_GameManager->m_CurrentState]->StopAnimation();
			m_HitSprite[_GameManager->m_CurrentState]->SetActive(false);
		}
	}
	else
	{
		m_HitSprite[_GameManager->m_CurrentState]->StopAnimation();
		m_HitSprite[_GameManager->m_CurrentState]->SetActive(false);
		m_HitSprite[_GameManager->m_CurrentState ^ 0x01]->StopAnimation();
		m_HitSprite[_GameManager->m_CurrentState ^ 0x01]->SetActive(false);
	}

	if (m_IsMoving == false)
	{
		if (_GameManager->GetInstance()->m_CurrentState == 0)
		{
			if (m_IsMoveToWeapon == false)
			{
				m_Sprite[0]->SetActive(true);

				m_Sprite[1]->SetActive(false);
			}
		}
		else
		{
			if (m_IsMoveToWeapon == false)
			{
				m_Sprite[1]->SetActive(true);

				m_Sprite[0]->SetActive(false);
			}
		}
	}
	else
	{
		if (m_GameObject->GetPos().x < m_pCollider->m_Size.width / 2)
		{
			m_GameObject->SetPos(D2D1::Point2F(m_pCollider->m_Size.width / 2, m_GameObject->GetPos().y));
			m_DestPos = m_GameObject->GetPos();
			m_IsScreenBoarder = true;

			MoveStop();
			if (m_IsMoveToWeapon == true)
			{
				m_HitSprite[0]->SetActive(false);
				m_HitSprite[1]->SetActive(false);
				m_Sprite[0]->SetActive(false);
				m_Sprite[1]->SetActive(false);
				m_FireSprite[0]->SetActive(false);
				m_FireSprite[1]->SetActive(false);
				m_pCollider->SetActive(false);
				m_IsMoveToWeapon = false;
				SetActive(false);

				return;
			}
		}
		else if (m_GameObject->GetPos().x > 1920 - m_pCollider->m_Size.width / 2)
		{
			m_GameObject->SetPos(D2D1::Point2F(1920 - m_pCollider->m_Size.width / 2, m_GameObject->GetPos().y));
			m_DestPos = m_GameObject->GetPos();
			m_IsScreenBoarder = true;

			MoveStop();
			if (m_IsMoveToWeapon == true)
			{
				m_HitSprite[0]->SetActive(false);
				m_HitSprite[1]->SetActive(false);
				m_Sprite[0]->SetActive(false);
				m_Sprite[1]->SetActive(false);
				m_FireSprite[0]->SetActive(false);
				m_FireSprite[1]->SetActive(false);
				m_pCollider->SetActive(false);
				m_IsMoveToWeapon = false;
				SetActive(false);

				return;
			}
		}

		if (m_GameObject->GetPos().y < m_pCollider->m_Size.height / 2)
		{
			m_GameObject->SetPos(D2D1::Point2F(m_GameObject->GetPos().x, m_pCollider->m_Size.height / 2));
			m_DestPos = m_GameObject->GetPos();
			m_IsScreenBoarder = true;

			MoveStop();
			if (m_IsMoveToWeapon == true)
			{
				m_HitSprite[0]->SetActive(false);
				m_HitSprite[1]->SetActive(false);
				m_Sprite[0]->SetActive(false);
				m_Sprite[1]->SetActive(false);
				m_FireSprite[0]->SetActive(false);
				m_FireSprite[1]->SetActive(false);
				m_pCollider->SetActive(false);
				m_IsMoveToWeapon = false;
				SetActive(false);

				return;
			}
		}
		else if (m_GameObject->GetPos().y > 1080 - m_pCollider->m_Size.height / 2)
		{
			m_GameObject->SetPos(D2D1::Point2F(m_GameObject->GetPos().x, 1080 - m_pCollider->m_Size.height / 2));
			m_DestPos = m_GameObject->GetPos();
			
			m_IsScreenBoarder = true;

			MoveStop();
			if (m_IsMoveToWeapon == true)
			{
				m_HitSprite[0]->SetActive(false);
				m_HitSprite[1]->SetActive(false);
				m_Sprite[0]->SetActive(false);
				m_Sprite[1]->SetActive(false);
				m_FireSprite[0]->SetActive(false);
				m_FireSprite[1]->SetActive(false);
				m_pCollider->SetActive(false);
				m_IsMoveToWeapon = false;
				SetActive(false);

				return;
			}
		}

		m_MoveTime += _FTime->GetEngineFixedDeltaTimeSec();
		m_FireSprite[_GameManager->m_CurrentState]->SetActive(true);

		m_Sprite[0]->SetActive(false);
		m_Sprite[1]->SetActive(false);

		if (Vector2::Distance(Vector2(m_GameObject->GetPos().x, m_GameObject->GetPos().y), Vector2(m_DestPos.x, m_DestPos.y)) <= 20)
		{
			m_GameObject->SetPos(m_DestPos);

			if (m_IsMoveToWeapon == true)
			{
				m_FireSprite[0]->SetActive(false);
				m_FireSprite[1]->SetActive(false);
				m_HitSprite[0]->SetActive(false);
				m_HitSprite[1]->SetActive(false);
				m_pCollider->SetActive(false);
				m_IsMoveToWeapon = false;
				SetActive(false);
				return;
			}
			MoveStop();
		}
		else
		{
			double angle = 0;

			Vector2 currPos = Vector2(m_GameObject->GetPos().x, m_GameObject->GetPos().y);
			Vector2 targetVec = Vector2(m_GameObject->GetPos(), D2D1::Point2F(m_GameObject->GetPos().x, 0));

			angle = acos(Vector2::Dot(currPos, targetVec) / currPos.Length() / targetVec.Length());

			angle = ToDegree(angle);

			m_GameObject->m_pTransform->SetRotation(angle);

			float LerpTime = 0.4f * m_LerpTimeScale;

			if (m_IsEffectStateScale == true)
			{
				LerpTime *= (_GameManager->m_CurrentState == 1 ? 0.5f : 1.0f);
			}

			Vector2 pos = Vector2::Lerp(Vector2(m_StartPos.x, m_StartPos.y), Vector2(m_DestPos.x, m_DestPos.y), m_MoveTime / LerpTime);
			m_GameObject->m_pTransform->SetPos(pos.x, pos.y);
		}
	}
}

void Bullet::Render()
{

}

void Bullet::MoveStart()
{
	m_IsScreenBoarder = false;

	m_IsMoving = true;
	SetActive(true);
	m_pCollider->SetActive(true);

	if (m_GameObject->GetPos().x < m_pCollider->m_Size.width / 2)
	{
		m_GameObject->SetPos(D2D1::Point2F(m_pCollider->m_Size.width / 2, m_GameObject->GetPos().y));
		m_StartPos = m_GameObject->GetPos();
	}
	else if (m_GameObject->GetPos().x > 1920 - m_pCollider->m_Size.width / 2)
	{
		m_GameObject->SetPos(D2D1::Point2F(1920 - m_pCollider->m_Size.width / 2, m_GameObject->GetPos().y));
		m_StartPos = m_GameObject->GetPos();
	}

	if (m_GameObject->GetPos().y < m_pCollider->m_Size.height / 2)
	{
		m_GameObject->SetPos(D2D1::Point2F(m_GameObject->GetPos().x, m_pCollider->m_Size.height / 2));
		m_StartPos = m_GameObject->GetPos();
	}
	else if (m_GameObject->GetPos().y > 1080 - m_pCollider->m_Size.height / 2)
	{
		m_GameObject->SetPos(D2D1::Point2F(m_GameObject->GetPos().x, 1080 - m_pCollider->m_Size.height / 2));
		m_StartPos = m_GameObject->GetPos();
	}
}

void Bullet::MoveStop()
{
	for (int i = 0; i < 2; i++)
	{
		m_HitSprite[i]->StopAnimation();
		m_HitSprite[i]->SetActive(false);
		m_FireSprite[i]->StopAnimation();
		m_FireSprite[i]->SetActive(false);
	}
	
	m_Sprite[_GameManager->m_CurrentState]->SetActive(true);

	m_IsMoving = false;
}

void Bullet::SetDestination(D2D1_POINT_2F _dest)
{
	m_DestPos = _dest;
}

void Bullet::SetStartPosition(D2D1_POINT_2F _start)
{
	m_StartPos = _start;
	m_GameObject->SetPos(_start);
	m_MoveTime = 0;
}

void Bullet::IncreaseScale()
{
	D2D1_SIZE_F size = m_GameObject->GetScale();

	if (size.width < 1.f)
	{
		size.width += 0.1f;
		size.height += 0.1f;

		m_GameObject->SetScale(size);
	}
}

void Bullet::Init()
{
	m_IsScreenBoarder = false;
	m_GameObject->SetPos(D2D1::Point2F(-50, -50));
	for (int i = 0; i < 2; i++)
	{
		m_Sprite[i]->SetActive(false);
		m_FireSprite[i]->SetActive(false);
		m_HitSprite[i]->SetActive(false);
	}
	m_pCollider->SetActive(false);
	SetActive(false);
}
