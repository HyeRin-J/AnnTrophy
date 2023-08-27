#include "GamePCH.h"
#include "TankBullet.h"

void TankBullet::Awake()
{
	m_GameObject->SetScale(D2D1::SizeF(0.5f, 0.5f));

	SetActive(false);

	m_IsMoveToWeapon = true;

	for (int i = 0; i < 2; ++i)
	{
		WCHAR imageName[256];
		m_Sprite.push_back(m_GameObject->AddComponent<Sprite>());
		m_Sprite[i]->LoadSprite(_T("tank_bullet.txt"), _T("tank_bullet.png"), _T("tank"));
		m_Sprite[i]->SetActive(false);
		m_Sprite[i]->StartAnimation();

		m_FireSprite.push_back(m_GameObject->AddComponent<Sprite>());
		m_FireSprite[i]->LoadSprite(_T("tank_bullet.txt"), _T("tank_bullet.png"), _T("tank"));
		m_FireSprite[i]->SetActive(false);
		m_FireSprite[i]->StartAnimation();

		m_HitSprite.push_back(m_GameObject->AddComponent<Sprite>());
		m_HitSprite[i]->LoadSprite(_T("tank_bullet.txt"), _T("tank_bullet.png"), _T("tank"));
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
	
	//m_pCollider->SetTrigger(true);

	m_pCollider->SetStringTag("EnemyBullet");
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

void TankBullet::DisableSprite()
{
	for (int i = 0; i < 2; i++)
	{
	
		m_Sprite[i]->SetActive(false);
		m_FireSprite[i]->SetActive(false);
		m_HitSprite[i]->SetActive(false);
	}
	m_pCollider->SetActive(false);
	SetActive(false);

	//m_pCollider->OnDisable();
	//m_GameObject->GetComponent<BoxCollider>()->SetActive(false);
	//m_GameObject->OnDisable();
}
