#pragma once

class D2DGrahpics;
class Collider;
class BoxCollider : public Collider
{
public:
	BoxCollider();
	BoxCollider(float _left, float _top, float _right, float _bottom);
	virtual ~BoxCollider();
public:
	
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

