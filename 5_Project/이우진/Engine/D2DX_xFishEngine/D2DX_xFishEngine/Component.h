#pragma once
using namespace std;

class Object;
class GameObject;
class Transform;

/// <summary>
/// ������Ʈ ������ �������
/// ������Ʈ���� �޼����� ���� ���־���Ѵٰ� �ô�
/// ���� �� ������ �ƴѰŰ����� 
/// ���ϱ� ������ ���ɻ������� �˰Ű���. ����͸�..����͸�..
/// </summary>

class Component : public Object
{
public:
	Component();
	virtual ~Component();
public:
	bool CampareTag(string _name);
	bool m_IsActive = true;
public:
	//������Ʈ�� ��ӹްų� �����ϰ��ִ� ������ ��ü����
	//�ش� ��ü�� ���� ������ �˼�������.
	//�׷��Ƿ� �� ������ ������ �˸��� �߰��ڰ� �ʿ��ѵ�
	//�Ʒ��� ��ü�����Ͱ� �� �߰迪���� ���Ѵ�.
	GameObject* m_GameObject;
	Transform* m_Transform;
	
	void	SetActive(bool _active);
	bool	IsActive() { return m_IsActive; }

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

