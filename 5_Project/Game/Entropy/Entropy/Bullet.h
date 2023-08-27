#pragma once

class Bullet : public Component
{
protected:
	D2D1_POINT_2F	m_StartPos;
	D2D1_POINT_2F	m_DestPos;

	std::vector<Sprite*> m_Sprite;
	std::vector<Sprite*> m_FireSprite;
	std::vector<Sprite*> m_HitSprite;

	float		m_MoveTime = 0.f; 
public:
	bool		m_IsMoving = false;
	bool		m_IsEffectStateScale = false;

	bool		m_IsScreenBoarder = false;

	bool		m_IsHit = false;
	float		m_HitTime = 0.f;
	
	bool		m_IsMoveToWeapon = false;
	float		m_Damage;
	float		m_LerpTimeScale = 1.0f;
	BoxCollider*	m_pCollider;

	virtual void Awake();
	virtual void Update();
	virtual void Render();

	bool		IsMoving() { return m_IsMoving; }
	void		MoveStart();
	void		MoveStop();
	void		SetDestination(D2D1_POINT_2F _dest);
	void		SetStartPosition(D2D1_POINT_2F _start);

	void		IncreaseScale();

	void		Init();
};

