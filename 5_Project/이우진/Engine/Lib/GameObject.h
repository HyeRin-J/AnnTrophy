#pragma once
using namespace std;
#include "Collider.h"
class Transform;
class Vector3;
class D2DGrahpics;
class Collider;
class CircleCollider;
class BoxCollider;
class Sprite;
enum class CollistionType;
enum class Shape;



//게임 오브젝트는 (최상위)오브젝트를 상속받는다
class GameObject : public Object
{
public:
	//일반 생성
	GameObject();
	//어떠한 충돌모양을 지닌채 생성
	GameObject(Collider::Shape _v);
	//이름을 정해진 채로 생성
	GameObject(string _name);
	//사이즈를 정해준 채로  생성
	GameObject(float _x,float _y , float _width ,float _height);

	virtual ~GameObject();

	//Sprite* m_spr;

private:
	//충돌체를 지닌 멤버변수
	Collider* m_Collider;
public:
	//충돌체의 정보나 동적인상태에서 객체의 수정이 필요할때의 멤버 함수
	Collider* GetCollider() { return m_Collider; }
	void SetCollider(Collider::Shape _v);
	void SetCollistion(Collider::CollistionType _v);

public:
	//생성 및 위치 선언의 transform 포인터변수
	Transform* m_pTransform;
	
public:
	//해당 게임오브젝트를 지닌 컴포넌트의 벡터
	vector<Component*> m_Components;

	//템플릿을 받는 이유는
	//어떤한 형태로 들어올지 모르겠지만
	//일단 받고나서, 타입id등으로 자료형태를 알아내고 그것에 맞는 컴포넌트를 추가하기 위해
	//템플릿으로 선언하였다.
	//주의 할 점으로는 어떠한 형태가 올지 모르기떄문에 null체크를 반드시 해주어야한다.
	template<typename T>
	void AddComponent();

	template<typename T>
	T* GetComponent();


	virtual void Release() override;

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

//어떠한 자료를 받을 지 어떠한 타입을 받는지 모르겠지만 원하는 타입으로 캐스팅을 원할때
//템플릿으로 받아주고 , 해당타입에 대한 객체를 생성한다.
template<typename T>
inline void GameObject::AddComponent()
{
	//원하는 타입의 객체를 생성(컴파일 단계에서 생성됨)
	T* _com = new T();
	//일단 컴포넌트는 이 객체를 모른다.
	//그 전에 컴포넌트간의 비교를 했을 때 어떤일이 일어날지 모름.
	//그러기를 방지하기위해 컴포넌트를 객체를 알아야할 필요가있음
	//그러기 위해선 해당 객체가 가진 (자신의)주소를 넣어줌으로써
	//해당 컴포넌트를 알수있고
	//그 컴포넌트는 해당객체의 종속된다.
	_com->m_GameObject = this;
	//_com->m_pTransform = this->m_pTransform;
	//객체의 초기상태를 호출
	_com->Awake();

	//컴포넌트가 추가될때마다
	//해당 게임오브젝트 객체의 컴포넌트를 추가한다.
	m_Components.push_back(_com);

}

template<typename T>
inline T* GameObject::GetComponent()
{
	//m_Components의 사이즈만큼 com에 넣는다는 의미로..
	// com <= m_Components 
	//컴포넌트를 저장한 벡터에서 
	//auto키워드로 해당자료를 읽어들인다.
	//auto로 읽을경우 현재 Components*형태의 값을 저장한 벡터니까
	//Components* com이 되는데 내가 원하는건 Components*의 포인터가아닌
	//T*타입의 변수를 원하니 밑에서 한번 더 dynamic_cast<> 를 진행한다.

	for (auto com : m_Components)
	{
		//들어온 템플릿 타입에 맞는 다운캐스팅을 진행한다.
		//다이나믹 캐스트는 캐스팅 실패 할 경우
		//nullptr을 반환한다.
		T* c = dynamic_cast<T*>(com);
		//nullptr이 아닌경우 해당 자료를 반환한다.
		if (c != nullptr)
		{
			return c;
		}
	}
	return nullptr;
}
