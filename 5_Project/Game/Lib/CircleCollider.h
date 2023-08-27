#pragma once

class Collider;

class CircleCollider : public Collider
{
public:
	CircleCollider();
	CircleCollider(float _radius);
	virtual ~CircleCollider();
private:
	float m_radius = 20.f;
public:
	double GetRaudius() { return m_radius; }
	void SetRaudius(float _v) { m_radius = _v; }
public:
	bool IsCheckCrash(CircleCollider* _target);
	virtual void	Update();
	virtual void	OnRender() ;
	virtual void	OnDestroy() {};
};

