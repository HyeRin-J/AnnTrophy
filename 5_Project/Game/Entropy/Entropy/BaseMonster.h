#pragma once

class BaseMonster : public Component
{
public:
	enum class State 
	{
		NONE = 0,
		IDLE,
		MOVE,
		TRACKING,
		ATTACK,
		DEAD,
		JUMP,
		MAX
	};
	
	enum class Direction
	{
		RIGHT,
		LEFT,
		TOP,
		BOTTOM,
		MAX
	};



protected:
	//속성값들
	GameObject* m_Player; // player
	Direction m_Direction = Direction::LEFT;
	int		m_HP;
	int		m_Damage;
	float	m_MoveSpeed;

	bool	m_IsDead = false;
	float	m_DeadTime;

	D2D1_SIZE_F	m_DetectReach; // width, height 로 사각형으로 detect 함
	
	float	m_DetectDelay;
	float	m_AttackedDlay; // 초단위? //공격받을시 한번 받고 바로 안받게


	float	m_TrackingSpeed; // 플레이어 감지후 MoveSpeed 에 더해지는 값
	
	float	m_AttackSpeed;
	float	m_AttackDelay;

	//Text
	struct MonsterText 
	{
		float DamageTextX;
		float DamageTextY;
		std::wstring Text;
		bool IsGray = false;
	};
	float	m_TextTime = 1.0f;

	int m_TextLeftOffset = 130;
	int m_TextRightOffset = 70;
	std::vector<MonsterText*> m_DamageList;
	

protected:
	//기본 콜라이더 및 리지드바디
	Rigidbody* m_pRigidBody;
	BoxCollider* m_pHitCollider;
	BoxCollider* m_pJumpCollider;
	BoxCollider* m_pMoveCollider;

	Sprite*		m_DeadSprite;
public:
	std::queue<BTEventMessage::BaseMessage> m_MessageQueue;
	BrainTree::BehaviorTree m_BehaviorTree;
	
public:
	BaseMonster() {};
	BaseMonster(GameObject* _player) :m_Player(_player){};
	~BaseMonster();
	 
	//component func
	virtual void	Awake();
	virtual void	Update();//프레임 고정x
	virtual void	OnRender();//그려주는 기능
public:
	//Monster func
	//virtual void	IsDetected(D2D1_POINT_2F _playerPos);
	virtual void	Move();
	virtual void	CheckWall(); // 벽충돌 했을때 플립
	virtual void	Tracking();
	virtual void	IsDetected();
	virtual void	FlipAnimation();
	virtual void	CheckMapOut();

	
	
	virtual void	DamageTextOut();
	virtual void	DamageTextFlow();

	virtual void Attack() = 0;
};

//원거리 몬스터
//class RangedMonster : public BaseMonster
//{
//public:
//	D2D1_SIZE_F	m_ProjectileRange; // 투사체 날아가는 범위/거리
//	float		m_ProjectileSpeed; // 투사체 스피드
//
//public:
//	virtual void Attack();
//	
//};