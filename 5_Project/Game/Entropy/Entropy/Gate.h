#pragma once

class Gate : public Component
{
	bool	m_IsOpen = false;
	bool	m_IsClear = false;
	float	m_InteractionTime = 0.f;
	Sprite* m_pSprite;
public:
	BoxCollider* m_Collider;

	virtual void Awake();
	virtual	void Update();
	virtual void OnRender();

	void SetOpen();
	bool IsOpen() { return m_IsOpen; }
	void Init();
};

