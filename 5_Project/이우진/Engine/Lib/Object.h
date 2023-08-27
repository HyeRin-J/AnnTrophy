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
	//상속받을 객체의 이름을 나타내는 순수 가상함수
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
	//생성 기능
	//생성 옵션을 지정을 해주는 함수모음_
	void  Instantiate(Object* _original);

public:
	//삭제함수
	void Destroy();
	void Destroy(Object* _obj);
	void Destroy(Object* _obj, float _deleteTime);

public:
	//논리 연산자 오버로딩
	bool operator!=(Object& _another);	// a,b오브젝트가 서로다른가?
	bool operator==(Object& _another);		// 같은가?
public:
	virtual void Release();

	
	bool friend operator == (Object _a, Object _b); 

};