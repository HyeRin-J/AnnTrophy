#pragma once
using namespace std;

class Transform;

class Object
{
public:
	Object();
	Object(string _name);
	virtual ~Object();

public:
	//��ӹ��� ��ü�� �̸��� ��Ÿ���� ���� �����Լ�
	virtual void	ToString();
	virtual void	Awake() {};
	virtual void	OnEnable() {};
	virtual void	Start() {};
	virtual void	FixedUpdate() {};
	virtual void	Update() {};
	virtual void	OnRender() {};
	virtual void	OnDisable() {};
	virtual void	OnDestroy() {};

private:
	string m_name;
	string m_tag;
public:
	string GetStringName() { return m_name; }
	string GetStringTag() { return m_name; }

public:
	//���� ���
	//���� �ɼ��� ������ ���ִ� �Լ�����_
	void  Instantiate(Object* _original);

public:
	//�����Լ�
	void Destroy();
	void Destroy(Object* _obj);
	void Destroy(Object* _obj, float _deleteTime);

public:
	//�� ������ �����ε�
	bool operator!=(Object& _another);	// a,b������Ʈ�� ���δٸ���?
	bool operator==(Object& _another);		// ������?
public:
	virtual void Release();

	
	bool friend operator == (Object _a, Object _b); 

};