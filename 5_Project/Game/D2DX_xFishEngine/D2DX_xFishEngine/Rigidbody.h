#pragma once

/// <summary>
/// 중력, 충돌의 효과를 만들어줄 클래스입니다
/// </summary>
/// 
/// 
class BoxCollider;

enum class CollisionDetectionMode
{
	CC, AABB, OBB
};

class Rigidbody : public Component
{
	CollisionDetectionMode m_CollMode;

	float	m_Drag = 0.1f;
	float	m_Mass = 1;
	
	//중력 관련
	float	m_Gravity = 20;
	float	m_FallSpeed = 0;
	float	m_MaxFallSpeed = 5;
	bool	m_UseGravity = false;
	bool	m_IsCrashX = false;

	D2D1_POINT_2F m_LastPos, m_CurrPos;

	float	m_Power = 0;
	Vector2 m_CollisionVector = { 0, 0 };


public:
	std::vector<BoxCollider*> m_TargetCollider;
	bool	m_IsCollision = false;

	Rigidbody();

	void	Awake();

	//리지드바디의 속력 벡터를 나타냅니다.
	Vector2	m_Velocity = { 0, 0 };

	void	SetCollisionMode(CollisionDetectionMode mode) { m_CollMode = mode; }

	void	SetDrag(float d) { m_Drag = d; }
	float	GetDrag() { return m_Drag; }

	void	SetMass(float m) { m_Mass = m; }
	float	GetMass() { return m_Mass; }

	void	OnGravity() { m_UseGravity = true; }
	void	OffGravity() { m_UseGravity = false; }
	void	SetFallSpeed(float _speed) { m_FallSpeed = _speed; }
	float	GetFallSpeed() { return m_FallSpeed; }
	void	SetFallMaxSpeed(float _speed) { m_MaxFallSpeed = _speed; }

	void	AddForce(Vector2 force);

	virtual void Update();

	void	Reflect(Collider* target, bool isCollision = false);
};

