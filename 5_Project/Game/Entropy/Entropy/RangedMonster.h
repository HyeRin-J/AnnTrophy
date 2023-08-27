#pragma once

//���ϴϱ� Melee Monster �� ��ӹ޾Ƽ� ��������...
#define TANKBULLETPOWER 10
#define TANKMAXBULLET 3

class RangedMonster : public MeleeMonster
{


	BoxCollider* m_pLeftCliffCheckCollider;// �������� üũ��
	BoxCollider* m_pRightCliffCheckCollider;// �������� üũ��



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
	void			CheckCliff(); // �÷��� �ȹ���� ����� �Լ�
	virtual void	RangeAttack();
	virtual void	Move();
	virtual void	Dead();
	virtual void	IsDetected();

//anim
public:
	//virtual void FlipAnimation();
	//virtual void StopAllAnimation();
};

