#pragma once

class MovePlayer : public Component
{
	Rigidbody* m_Rigidbody;

	bool		m_IsJumping = false;
	bool		m_IsDownJumping = false;
	bool		m_RichMaxHeight = false;
	bool		m_IsDashMode = false;
	bool		m_IsDashCoolDown = false;

	Vector2		m_JumpStartPos = { 0, 0 };
	float		m_JumpTime = 0.f;
	float		m_DashTime = 0.f;
	float		m_StartDashTime = 0.3f;
	float		m_DashCoolTime = 2.f;

	float		m_MoveSpeed = 200;
	float		m_JumpSpeed = 450;

	int			m_JumpCount = 0;

public:
	BoxCollider* m_JumpCollider, *m_MoveCollider, *m_HeadCollider;
	Player*		m_pPlayer;

	virtual void	Awake();
	virtual void	Update();
	virtual void	OnRender();
};

