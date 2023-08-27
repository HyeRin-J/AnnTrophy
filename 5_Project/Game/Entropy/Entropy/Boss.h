#pragma once

class Boss : public Weapon
{
public:
	std::vector<Sprite*> m_pSprite;

	ID2D1Bitmap* m_pDieSprite_0;
	ID2D1Bitmap* m_pDieSprite_1;

	GameObject* m_pPlayer;
	D2D1_POINT_2F m_TargetPos;

	BoxCollider* m_pHitCollider;

	float	m_Hp = 5000;
	float	m_MaxHp = 5000;

	double angle = 0;

	int		m_DeadAnimationIndex = 0;

	float	m_DeadTime = 0.f;
	bool	m_IsHit = false;
	bool	m_IsDead = false;
public:
	~Boss();

	void Init();

	virtual void Awake();
	virtual void Update();
	virtual void OnRender();

	void Damage(int _damage);
	//보스 피 UI때문에 작성합니다.
	float GetBossHP() { return m_Hp; }
	void SetBossHP(float _v) { m_Hp = _v; }
public:
	float GetBossMaxHP() { return m_MaxHp; }

};

