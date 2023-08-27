#pragma once


enum class Shape;
class Transform;
// �浹ü ���� Ŭ�����������
// �� �浹ü Ŭ�������� ���� �浹ü���� ��ӽ�ų �ڷ�鸸 ������.
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
		//���..
	};

	enum class CollistionType
	{
		CC = 0,
		AABB,
		OBB,
		//���..
	};

protected:
	bool m_CollderInfo;
	bool m_CollderDraw;
public:
	//ǥ�õ� �ݶ��̴��� ��ǥ�� ũ���� �������
	D2D1_RECT_F m_ColliderSize;
	//�ڽ��� �浹�� �� ���ΰ�?
	bool m_isCollistion;
	//���� �浹 ó�� ���θ� ���ִ°�?
	bool m_isTrigger;
public:
	//�ݶ��̴��� ���¸� ���� get/set
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
	//��� �浹Ÿ���� ������ ������ ����
	CollistionType m_ColliderType;
public:
	CollistionType GetColliderType() const { return m_ColliderType; }
	void SetCollistionType(CollistionType _v) { m_ColliderType = _v; }
public:
	void SetColliderInfo(bool _v) { m_CollderInfo = _v; }
	void SetColliderDraw(bool _v) { m_CollderDraw = _v; }

public:
	//�浹�׸���� ����� ���������� �ٸ��� ������ ���������Լ��� �ݶ��̴��� OnDraw�Լ��� ����. 

	virtual void Release();
public:
	//�浹�� � ������� ó�����ٰ��ΰ� CC/AABB/OBB ����� �з���
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

