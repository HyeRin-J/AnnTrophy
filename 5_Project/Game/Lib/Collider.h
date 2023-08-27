#pragma once


// 충돌체 전용 클래스를만든다
// 이 충돌체 클래스에선 여러 충돌체에게 상속시킬 자료들만 가진다.

class Collider : public Component
{
public:
	Collider();
	~Collider();
public:
	enum class Shape
	{
		Circle,
		Rect,
	};
protected:
	std::vector<std::string> m_IgnoreList;

	bool m_CollderInfo = false; // debug 용
	bool m_CollderDraw; // collider 를 그릴 건지 말건지
	bool m_IsTrigger; // 충돌 처리 여부
	bool m_IsCrash; // 충돌 여부
public:
	//std::vector<std::string> m_IgnoreList;
	
	std::vector<Collider*>	m_Target;
	D2D1_SIZE_F			m_Size;
	D2D1_POINT_2F		m_Center;
	D2D1_POINT_2F		m_CollisionStartPoint;

	void SetDebug() { m_CollderInfo = true; m_CollderDraw = true; };
	void SetDebugDraw() { m_CollderDraw = true; };
	bool IsTriggerOn() const { return m_IsTrigger; }
	void SetTrigger(bool _v) { m_IsTrigger = _v; }
	bool IsCrash() const { return m_IsCrash; }
	void SetCrash(bool _v) { m_IsCrash = _v; }

	void AddIgnoreTag(std::string tag) { m_IgnoreList.push_back(tag); }
	void DeleteIgnoreTag(std::string tag);


public:
	//virtual void	Awake() {};
	//virtual void	OnEnable() {};
	//virtual void	Start() {};
	//virtual void	FixedUpdate() {};
	//virtual void	Update() {};
	//virtual void	OnRender() {};
	//virtual void	OnDisable() {};
	//virtual void	OnDestroy() {};
};

