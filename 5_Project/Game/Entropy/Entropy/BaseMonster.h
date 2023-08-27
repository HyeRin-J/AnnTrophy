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
	//�Ӽ�����
	GameObject* m_Player; // player
	Direction m_Direction = Direction::LEFT;
	int		m_HP;
	int		m_Damage;
	float	m_MoveSpeed;

	bool	m_IsDead = false;
	float	m_DeadTime;

	D2D1_SIZE_F	m_DetectReach; // width, height �� �簢������ detect ��
	
	float	m_DetectDelay;
	float	m_AttackedDlay; // �ʴ���? //���ݹ����� �ѹ� �ް� �ٷ� �ȹް�


	float	m_TrackingSpeed; // �÷��̾� ������ MoveSpeed �� �������� ��
	
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
	//�⺻ �ݶ��̴� �� ������ٵ�
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
	virtual void	Update();//������ ����x
	virtual void	OnRender();//�׷��ִ� ���
public:
	//Monster func
	//virtual void	IsDetected(D2D1_POINT_2F _playerPos);
	virtual void	Move();
	virtual void	CheckWall(); // ���浹 ������ �ø�
	virtual void	Tracking();
	virtual void	IsDetected();
	virtual void	FlipAnimation();
	virtual void	CheckMapOut();

	
	
	virtual void	DamageTextOut();
	virtual void	DamageTextFlow();

	virtual void Attack() = 0;
};

//���Ÿ� ����
//class RangedMonster : public BaseMonster
//{
//public:
//	D2D1_SIZE_F	m_ProjectileRange; // ����ü ���ư��� ����/�Ÿ�
//	float		m_ProjectileSpeed; // ����ü ���ǵ�
//
//public:
//	virtual void Attack();
//	
//};