#pragma once
using namespace std;

class Object;
class GameObject;
class Transform;

/// <summary>
/// 컴포넌트 엔진을 만들려니
/// 컴포넌트간의 메세지를 연결 해주어야한다고 봤다
/// 아직 할 레벨은 아닌거같은데 
/// 보니깐 대충은 어케생긴지는 알거같다. 생긴것만..생긴것만..
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
	//컴포넌트를 상속받거나 포함하고있는 구조의 객체들은
	//해당 객체에 대한 정보를 알수가없다.
	//그러므로 그 사이의 정보를 알만한 중계자가 필요한데
	//아래의 객체포인터가 그 중계역할을 지닌다.
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

