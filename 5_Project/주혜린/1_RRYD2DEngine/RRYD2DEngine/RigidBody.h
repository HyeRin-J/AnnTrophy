#pragma once

class RigidBody : public Component
{
	enum class CollisionDetectionMode
	{
		CC, AABB, OBB
	} m_CollMode;

	float	m_Drag = 0.1f;
	float	m_Mass = 1;

	bool	m_UseGravity = false;

	D2D1_POINT_2F m_LastPos, m_CurrPos;

	float	m_Power = 0;
	bool	m_IsCollision = false;
	Vector2 m_CollisionVector = { 0, 0 };
	
public:
	RigidBody();

	void	Awake();

	//리지드바디의 속력 벡터를 나타냅니다.
	Vector2	m_Velocity = { 0, 0 };

	void	SetCollisionMode(CollisionDetectionMode mode) { m_CollMode = mode; }

	void	SetDrag(float d) { m_Drag = d; }
	float	GetDrag() { return m_Drag; }

	void	SetMass(float m) { m_Mass = m; }
	float	GetMass() { return m_Mass; }

	bool	OnGravity() { m_UseGravity = true; }
	bool	OffGravity() { m_UseGravity = false; }

	void	AddForce(Vector2 force);

	virtual void Update();

	void	Reflect(BoundShape* target, bool isCollision = false);
};

