#pragma once

class GameObject;
class Transform;

class Component : public Object
{
	bool			m_IsActive = true;
public:
	GameObject* m_GameObject;

	Component();
	~Component();

	void			SetActive(bool _active);
	bool			IsActive() { return m_IsActive; }

	virtual void	Awake() {};
	virtual void	OnEnable() {};
	virtual void	Start() {};
	virtual void	FixedUpdate() {};
	virtual void	Update() {};
	virtual void	OnRender() {};
	virtual void	OnDisable() {};
	virtual void	OnDestroy() {};
};