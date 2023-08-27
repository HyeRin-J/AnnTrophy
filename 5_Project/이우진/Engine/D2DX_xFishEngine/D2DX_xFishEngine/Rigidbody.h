#pragma once

/// <summary>
/// 중력, 충돌의 효과를 만들어줄 클래스입니다
/// </summary>
class Rigidbody : public Component
{
public:
	Rigidbody();
	virtual ~Rigidbody();
private:
	float m_Drag;
	float m_Mass;
	bool m_UseGravity;

public:
	Vector2 m_Velocity;
	void AddForce();
	float GetDrag() { return m_Drag;  }
	float GetMass() { return m_Drag;  }
	void SetDrag(float _v) { m_Drag = _v; }
	void SetMass(float _v) { m_Drag = _v; }

	
	virtual void	ToString();
	virtual void	Awake() {};
	virtual void	OnEnable() {};
	virtual void	Start() {};
	virtual void	FixedUpdate() {};
	virtual void	Update() {};
	virtual void	OnRender() {};
	virtual void	OnDisable() {};
	virtual void	OnDestroy() {};

	
};

