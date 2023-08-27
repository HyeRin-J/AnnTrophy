#pragma once


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
		Circle,
		Rect,
	};
protected:
	std::vector<std::string> m_IgnoreList;

	bool m_CollderInfo = false; // debug ��
	bool m_CollderDraw; // collider �� �׸� ���� ������
	bool m_IsTrigger; // �浹 ó�� ����
	bool m_IsCrash; // �浹 ����
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

