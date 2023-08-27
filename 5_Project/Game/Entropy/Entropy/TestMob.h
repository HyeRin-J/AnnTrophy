#pragma once
class TestMob : public Component
{
private:
	BTMob::MobState m_state = BTMob::MobState::None;
	BTMob::Sequence* BtRoot;

	float		m_MoveSpeed = 100;
	float		m_JumpSpeed = 200;

	BoxCollider* m_Collider;
	Rigidbody* m_Rigidbody;

	BoxCollider* m_Range;
public:

	virtual void	Awake();
	virtual void	Update();
	virtual void	OnRender();

};

