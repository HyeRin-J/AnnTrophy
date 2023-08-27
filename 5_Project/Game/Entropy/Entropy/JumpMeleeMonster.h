#pragma once
//도약형 근접 몬스터
class JumpMeleeMonster : public MeleeMonster
{

public:
	//도약형
	float	m_JumpSpeed; 
	
	//detect delay
	float m_DetectDelay = 1.0f;


	//jump lerp data
	bool IsJumping = false;
	D2D1_POINT_2F m_JumpDest;// = D2D1::Point2F(0.f, 9999.f);
	Collider* m_JumpTarget = nullptr;

	float m_jumpTime = 0.f;


	//jump Attack
	bool IsJumpAttacking = false;
	bool IsAttackJumpFinish = false;
	D2D1_POINT_2F m_PrevPlayerPos;
	//D2D1_POINT_2F m_PlayerLerpPos;
	D2D1_POINT_2F m_LerpTarget;
	D2D1_POINT_2F m_PrevMonsterPos;
	float m_JumpATKTime = 0.f;

	//test debug 용
	D2D1_POINT_2F m_middlePos;
	D2D1_POINT_2F m_destPos;


protected:
	Sprite* m_JumpSprite;
	BoxCollider* m_HeadCollider;


public:
	~JumpMeleeMonster() { OnDestroy(); };

	virtual void InitProperties();
	virtual void InitColliders();
	virtual void InitSprites();

	virtual void Awake();
	virtual void Update();
	virtual void OnDestroy();

	//testing
	virtual void OnRender();

public:
	//virtual void Attack();
	
	bool CheckTopPlatform();
	

	void DetectPlayer();
	virtual void Move();
	virtual void Dead();
	void Jump(); // platform 을 뛴다

	void JumpAttack(); // 플레이어에게 뛴다
	void PushMe();


public:
	virtual void StopAllAnimation();
	void SetActiveAllCollider(bool _state);
};
