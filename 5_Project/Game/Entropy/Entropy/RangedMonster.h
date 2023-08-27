#pragma once

//급하니깐 Melee Monster 로 상속받아서 재사용하자...
#define TANKBULLETPOWER 10
#define TANKMAXBULLET 3

class RangedMonster : public MeleeMonster
{


	BoxCollider* m_pLeftCliffCheckCollider;// 낭떠러지 체크용
	BoxCollider* m_pRightCliffCheckCollider;// 낭떠러지 체크용



	float m_ShotDelay = 1.0f;

	std::vector<GameObject*> m_TankBullets;

	D2D1_POINT_2F m_ShootPointLeft;
	D2D1_POINT_2F m_ShootPointRight;


public:
	~RangedMonster() { OnDestroy(); };
	virtual void	Awake();
	virtual void	Update();
	virtual void	OnDestroy();
	//testing
	virtual void OnRender();

	//Setting
	virtual void InitColliders();
	virtual void InitProperties();
	virtual void InitSprites();
	void		 InitBullets();

public:
	void			SetShoot();
	void			CheckCliff(); // 플랫폼 안벗어나게 만드는 함수
	virtual void	RangeAttack();
	virtual void	Move();
	virtual void	Dead();
	virtual void	IsDetected();

//anim
public:
	//virtual void FlipAnimation();
	//virtual void StopAllAnimation();
};

