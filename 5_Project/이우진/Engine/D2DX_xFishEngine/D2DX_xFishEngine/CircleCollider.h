#pragma once

class D2DGrahpics;
class Collider;
class CircleCollider : public Collider
{
public:
	CircleCollider();
	CircleCollider(float _radius);
	virtual ~CircleCollider();
private:
	float m_radius = 20;
public:
	double GetRaudius() { return m_radius; }
	void SetRaudius(float _v) { m_radius = _v; }
public:
	virtual void Release();

	virtual void	ToString();
	virtual void	Awake() {};
	virtual void	OnEnable() {};
	virtual void	Start() {};
	virtual void	FixedUpdate() {};
	virtual void	Update();
	virtual void	OnRender() ;
	virtual void	OnDisable() {};
	virtual void	OnDestroy() {};

};

