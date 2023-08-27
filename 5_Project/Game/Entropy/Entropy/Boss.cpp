#include "GamePCH.h"
#include "Boss.h"

Boss::~Boss()
{
	SafeRelease(&m_pDieSprite_0);
	SafeRelease(&m_pDieSprite_1);
}

void Boss::Init()
{
	m_Hp = 5000;
	m_MaxHp = 5000;

	angle = 0;

	m_DeadAnimationIndex = 0;

	m_DeadTime = 0.f;
	m_IsHit = false;
	m_IsDead = false;
}

void Boss::Awake()
{
	m_pPlayer = SceneObjectManager::GetInstance()->m_pPlayerObject;
	Weapon* weapon = m_pPlayer->GetComponent<Player>()->m_Gun->GetComponent<Weapon>();
	m_FireDelay = weapon->m_FireDelay;
	m_OverloadingReduceDelay = weapon->m_OverloadingReduceDelay;
	m_OverloadingDuration = weapon->m_OverloadingDuration;

	m_AttackRange = weapon->m_AttackRange;
	m_MaxBullet = weapon->m_MaxBullet;

	m_Hp = 10000;
	m_MaxHp = 10000;

	m_pHitCollider = m_GameObject->AddComponent<BoxCollider>();
	m_pHitCollider->SetRect(D2D1::Point2F(0, 0), D2D1::SizeF(500.f, 500.f));
#ifdef _DEBUG
	m_pHitCollider->SetDebugDraw();
#endif
	m_pHitCollider->AddIgnoreTag("EnemyBullet");
	m_pHitCollider->AddIgnoreTag("Weapon");

	std::wstring dataPath = _T("boss36.txt");
	for (int i = 0; i < 2; i++)
	{
		WCHAR imageName[256];
		swprintf_s(imageName, _T("boss_sprite_%d.png"), i);
		m_pSprite.push_back(m_GameObject->AddComponent<Sprite>());
		m_pSprite[i]->LoadSprite(dataPath.c_str(), imageName, _T("boss"));
	}

	std::wstring path = PATH_IMAGE_UNI;
	path += _T("Sprite/boss/");

	_GraphicEngine->D2DLoadBitmap((path + _T("bossDestroy_sprite_0.png")).c_str(), &m_pDieSprite_0);
	_GraphicEngine->D2DLoadBitmap((path + _T("bossDestroy_sprite_1.png")).c_str(), &m_pDieSprite_1);

	for (int i = 0; i < 10; i++)
	{
		m_Bullets.push_back(ObjectFactory::CreateObject<GameObject>());
		m_Bullets[i]->AddComponent<Bullet>()->SetActive(false);
		m_Bullets[i]->SetStringTag("EnemyBullet");
		m_Bullets[i]->GetComponent<BoxCollider>()->SetStringTag("EnemyBullet");
		m_Bullets[i]->GetComponent<Bullet>()->m_LerpTimeScale = 2.5f;
		m_Bullets[i]->GetComponent<Bullet>()->m_Damage = 1;
		m_Bullets[i]->GetComponent<Bullet>()->m_IsEffectStateScale = true;
	}
}

void Boss::Update()
{
	if (FTime::GetInstance()->m_EngineDeltaTimeScale <= 0.f) { return; };

	if (m_IsDead == true)
	{
		m_pSprite[_GameManager->m_CurrentState ^ 0x01]->SetActive(false);
		m_pSprite[_GameManager->m_CurrentState]->SetActive(false);

		if (m_DeadAnimationIndex >= 30)
		{
			SceneObjectManager::GetInstance()->Release();
			SceneObjectManager::GetInstance()->LoadNextScene();
		}

		m_DeadTime += _FTime->GetObjectFixedDeltaTimeSec();
		if (m_DeadTime >= 2.0f / 30.f)
		{
			m_DeadAnimationIndex++;
			m_DeadTime = 0;
		}

		return;
	}


	if (m_IsHit == false && m_pHitCollider->m_Target.size() > 0)
	{
		for (auto col : m_pHitCollider->m_Target)
		{
			if (col->GetStringTag()._Equal("Bullet") == true)
			{
				m_IsHit = true;
				col->m_GameObject->GetComponent<Bullet>()->m_IsHit = true;

				int index = rand() % 4;
				switch (index)
				{
				case 0:
					_FAudio->FPlaySound(OBJECT_BULLET_0);
					break;
				case 1:
					_FAudio->FPlaySound(OBJECT_BULLET_1);
					break;
				case 2:
					_FAudio->FPlaySound(OBJECT_BULLET_2);
					break;
				case 3:
					_FAudio->FPlaySound(OBJECT_BULLET_3);
					break;
				}

				Damage(m_pPlayer->GetComponent<Player>()->m_Gun->GetComponent<Weapon>()->m_AttackDamage[_GameManager->m_CurrentState]);
				break;
			}
		}
	}

	if (m_pHitCollider->m_Target.size() <= 0)
	{
		m_IsHit = false;
	}

	Vector2 playerPos = Vector2(m_GameObject->GetPos(), m_pPlayer->GetPos());
	Vector2 targetVec = Vector2(m_GameObject->GetPos(), D2D1::Point2F(m_GameObject->GetPos().x, m_GameObject->GetPos().y + 1));

	Vector2 calPos = Vector2((int)playerPos.x, (int)playerPos.y);

	angle = acos(Vector2::Dot(calPos, targetVec) / calPos.Length() / targetVec.Length());

	angle = ToDegree(angle);

	if (m_pPlayer->GetPos().x >= m_GameObject->GetPos().x)
	{
		angle *= (-1);
		angle = 360 + angle;
		if (angle >= 360) angle = 0;
	}

	Debug::LogFormat("Angle : %d", (int)angle / 10);

	m_pSprite[_GameManager->m_CurrentState ^ 0x01]->SetActive(false);
	m_pSprite[_GameManager->m_CurrentState]->SetActive(true);
	m_pSprite[_GameManager->m_CurrentState]->m_SheetIndex = (int)angle / 10;

	m_IsFire = m_pPlayer->GetComponent<Player>()->m_Gun->GetComponent<Weapon>()->m_IsFire;
	m_IsOverloading = m_pPlayer->GetComponent<Player>()->m_Gun->GetComponent<Weapon>()->m_IsOverloading;

	m_FireTime += _FTime->GetEngineFixedDeltaTimeSec();

	if (m_IsFire == true && m_FireTime >= m_FireDelay * (m_IsOverloading ? m_OverloadingReduceDelay : 1.0f))
	{
		m_TargetPos = m_pPlayer->GetPos();

		//m_IsDelayFinish = false;
		m_IsFire = true;
		m_FireTime = 0;

		if (_GameManager->m_CurrentState == 0)
		{
			if (m_CurrBulletIndex < m_MaxBullet)
			{
				if (m_CurrBulletIndex < 0) m_CurrBulletIndex = 0;

				Bullet* m_pBullet = (m_Bullets[m_CurrBulletIndex]->GetComponent<Bullet>());
				m_pBullet->SetStartPosition(m_GameObject->GetPos());

				Vector2 distance = Vector2(m_TargetPos.x, m_TargetPos.y) - Vector2(m_GameObject->GetPos().x, m_GameObject->GetPos().y);
				distance.Normalize();

				Vector2 dest = Vector2(m_GameObject->GetPos().x, m_GameObject->GetPos().y) + distance * m_AttackRange;

				m_pBullet->SetDestination(D2D1::Point2F(dest.x, dest.y));
				m_pBullet->m_GameObject->m_pTransform->SetRotation(angle);
				m_pBullet->MoveStart();
				
				++m_CurrBulletIndex;
			}
		}
		else if (_GameManager->m_CurrentState == 1)
		{
			if (m_CurrBulletIndex > 0)
			{
				m_CurrBulletIndex--;

				Bullet* m_pBullet = m_Bullets[m_CurrBulletIndex]->GetComponent<Bullet>();
				m_pBullet->SetStartPosition(m_Bullets[m_CurrBulletIndex]->GetPos());
				m_pBullet->MoveStart();
				m_pBullet->m_IsMoveToWeapon = true;
			}
		}
	}

	if (_GameManager->m_CurrentState == 1)
	{
		for (int i = m_MaxBullet - 1; i >= (m_IsOverloading ? 0 : m_CurrBulletIndex); i--)
		{
			Bullet* m_pBullet = m_Bullets[i]->GetComponent<Bullet>();
			m_pBullet->SetDestination(m_GameObject->GetPos());

			if (m_IsOverloading == true && m_IsFire == true)
			{
				m_pBullet->SetStartPosition(m_pBullet->m_GameObject->GetPos());
				m_pBullet->MoveStart();
				m_pBullet->m_IsMoveToWeapon = true;
				if (m_CurrBulletIndex > 0)
				{
					--m_CurrBulletIndex;
				}
			}

			if (m_pBullet->IsMoving() == false)
			{
				m_pBullet->m_pCollider->SetActive(false);
			}
		}
	}
}

void Boss::OnRender()
{
	if (m_IsDead == true)
	{
		SpriteData data;
		data.m_BitmapPos = D2D1::Point2F(m_DeadAnimationIndex % 5 * 1920, m_DeadAnimationIndex / 5 * 1080);
		data.m_BitmapSize = D2D1::SizeF(1920, 1080);
		data.m_Pivot = D2D1::Point2F(1920 / 2, 1080 / 2);

		if (_GameManager->m_CurrentState == 0)
		{
			_GraphicEngine->DrawBitmap(D2D1::Point2F(1920 / 2, 1080 / 2), data, m_pDieSprite_0, data.m_BitmapSize, 1.0f);
		}
		else
		{
			_GraphicEngine->DrawBitmap(D2D1::Point2F(1920 / 2, 1080 / 2), data, m_pDieSprite_1, data.m_BitmapSize, 1.0f);
		}

		if (m_DeadAnimationIndex >= 30)
		{
			SceneObjectManager::GetInstance()->m_CartoonOn = true;
			SceneObjectManager::GetInstance()->GetActiveScene()->m_ChangeFinish = true;
		}
	}
}

void Boss::Damage(int _damage)
{
	m_Hp -= _damage;

#ifdef _DEBUG
	Debug::LogFormat("Boss HP : %.2f", m_Hp);
#endif

	if (m_Hp <= 0)
	{
		m_IsDead = true;	
	}
}
