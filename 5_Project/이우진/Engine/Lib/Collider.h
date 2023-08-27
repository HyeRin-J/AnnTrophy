#pragma once


enum class Shape;
class Transform;
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
		Circle=0,
		Rect,
		//등등..
	};

	enum class CollistionType
	{
		CC = 0,
		AABB,
		OBB,
		//등등..
	};

protected:
	bool m_CollderInfo;
	bool m_CollderDraw;
public:
	//표시될 콜라이더의 좌표와 크기의 멤버변수
	D2D1_RECT_F m_ColliderSize;
	//자신은 충돌을 할 것인가?
	bool m_isCollistion;
	//현재 충돌 처리 여부를 해주는가?
	bool m_isTrigger;
public:
	//콜라이더의 상태를 받을 get/set
	D2D1_RECT_F GetColliderSize() { return m_ColliderSize; }
	void SetColliderSize(float _left, float _top, float _right, float _bottom);
public:
	bool GetIsCollition() const { return m_isCollistion; }
	void SetIsCollition(bool _v) { m_isCollistion = _v; }
public:
	bool GetIsTrigger() const { return m_isTrigger; }
	void SetIsTrigger(bool _v) { m_isTrigger = _v; }

protected:
	D2D1::ColorF::Enum m_hColor;
public:
	D2D1::ColorF::Enum GetEnumSetColor() { return m_hColor; }
protected:
	//어떠한 충돌타입을 가질지 가지는 변수
	CollistionType m_ColliderType;
public:
	CollistionType GetColliderType() const { return m_ColliderType; }
	void SetCollistionType(CollistionType _v) { m_ColliderType = _v; }
public:
	void SetColliderInfo(bool _v) { m_CollderInfo = _v; }
	void SetColliderDraw(bool _v) { m_CollderDraw = _v; }

public:
	//충돌그리기는 사용자 시점에따라 다르기 때문에 순수가상함수로 콜라이더의 OnDraw함수는 제외. 

	virtual void Release();
public:
	//충돌을 어떤 방식으로 처리해줄것인가 CC/AABB/OBB 등등을 분류함
	BOOL Collisition(Collider* _target);

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

