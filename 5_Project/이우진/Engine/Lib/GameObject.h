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



//���� ������Ʈ�� (�ֻ���)������Ʈ�� ��ӹ޴´�
class GameObject : public Object
{
public:
	//�Ϲ� ����
	GameObject();
	//��� �浹����� ����ä ����
	GameObject(Collider::Shape _v);
	//�̸��� ������ ä�� ����
	GameObject(string _name);
	//����� ������ ä��  ����
	GameObject(float _x,float _y , float _width ,float _height);

	virtual ~GameObject();

	//Sprite* m_spr;

private:
	//�浹ü�� ���� �������
	Collider* m_Collider;
public:
	//�浹ü�� ������ �����λ��¿��� ��ü�� ������ �ʿ��Ҷ��� ��� �Լ�
	Collider* GetCollider() { return m_Collider; }
	void SetCollider(Collider::Shape _v);
	void SetCollistion(Collider::CollistionType _v);

public:
	//���� �� ��ġ ������ transform �����ͺ���
	Transform* m_pTransform;
	
public:
	//�ش� ���ӿ�����Ʈ�� ���� ������Ʈ�� ����
	vector<Component*> m_Components;

	//���ø��� �޴� ������
	//��� ���·� ������ �𸣰�����
	//�ϴ� �ް���, Ÿ��id������ �ڷ����¸� �˾Ƴ��� �װͿ� �´� ������Ʈ�� �߰��ϱ� ����
	//���ø����� �����Ͽ���.
	//���� �� �����δ� ��� ���°� ���� �𸣱⋚���� nullüũ�� �ݵ�� ���־���Ѵ�.
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

//��� �ڷḦ ���� �� ��� Ÿ���� �޴��� �𸣰����� ���ϴ� Ÿ������ ĳ������ ���Ҷ�
//���ø����� �޾��ְ� , �ش�Ÿ�Կ� ���� ��ü�� �����Ѵ�.
template<typename T>
inline void GameObject::AddComponent()
{
	//���ϴ� Ÿ���� ��ü�� ����(������ �ܰ迡�� ������)
	T* _com = new T();
	//�ϴ� ������Ʈ�� �� ��ü�� �𸥴�.
	//�� ���� ������Ʈ���� �񱳸� ���� �� ����� �Ͼ�� ��.
	//�׷��⸦ �����ϱ����� ������Ʈ�� ��ü�� �˾ƾ��� �ʿ䰡����
	//�׷��� ���ؼ� �ش� ��ü�� ���� (�ڽ���)�ּҸ� �־������ν�
	//�ش� ������Ʈ�� �˼��ְ�
	//�� ������Ʈ�� �ش簴ü�� ���ӵȴ�.
	_com->m_GameObject = this;
	//_com->m_pTransform = this->m_pTransform;
	//��ü�� �ʱ���¸� ȣ��
	_com->Awake();

	//������Ʈ�� �߰��ɶ�����
	//�ش� ���ӿ�����Ʈ ��ü�� ������Ʈ�� �߰��Ѵ�.
	m_Components.push_back(_com);

}

template<typename T>
inline T* GameObject::GetComponent()
{
	//m_Components�� �����ŭ com�� �ִ´ٴ� �ǹ̷�..
	// com <= m_Components 
	//������Ʈ�� ������ ���Ϳ��� 
	//autoŰ����� �ش��ڷḦ �о���δ�.
	//auto�� ������� ���� Components*������ ���� ������ ���ʹϱ�
	//Components* com�� �Ǵµ� ���� ���ϴ°� Components*�� �����Ͱ��ƴ�
	//T*Ÿ���� ������ ���ϴ� �ؿ��� �ѹ� �� dynamic_cast<> �� �����Ѵ�.

	for (auto com : m_Components)
	{
		//���� ���ø� Ÿ�Կ� �´� �ٿ�ĳ������ �����Ѵ�.
		//���̳��� ĳ��Ʈ�� ĳ���� ���� �� ���
		//nullptr�� ��ȯ�Ѵ�.
		T* c = dynamic_cast<T*>(com);
		//nullptr�� �ƴѰ�� �ش� �ڷḦ ��ȯ�Ѵ�.
		if (c != nullptr)
		{
			return c;
		}
	}
	return nullptr;
}
