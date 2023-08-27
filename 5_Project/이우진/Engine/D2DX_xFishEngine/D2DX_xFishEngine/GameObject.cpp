#include "pch.h"
#include "Vector2.h"
#include "Object.h"
#include "Component.h"
#include "Transform.h"
#include "Collider.h"
#include "CircleCollider.h"
#include "BoxCollider.h"
#include "Sprite.h"
#include "GameObject.h"
#include "D2DGraphics.h"
#include "Debug.h"

GameObject::GameObject() : m_Collider(nullptr), m_pTransform(nullptr)
{
	//기본값은 boxcollider로 지정해준다
	m_Collider = new BoxCollider();
	m_pTransform = new Transform();

}
/// <summary>
/// 어떠한 충돌체가질지 정의 할 수있다.
/// </summary>
/// <param name="_v">어떠한 충돌체를 생성할지 지닌다.
/// </param>
GameObject::GameObject(Collider::Shape _v) : m_Collider(nullptr), m_pTransform(nullptr)
{
	switch (_v)
	{
	case Collider::Shape::Circle:
		m_Collider = new CircleCollider();
		break;
	case Collider::Shape::Rect:
		m_Collider = new BoxCollider();
		break;
	}
	m_pTransform = new Transform();
}

GameObject::GameObject(string _name) : m_Collider(nullptr), m_pTransform(nullptr)
{
}

GameObject::GameObject(float _x, float _y, float _width, float _height) :GameObject()
{
}


GameObject::~GameObject()
{
	delete m_Collider;
	m_Collider = nullptr;

	delete m_pTransform;
	m_pTransform = nullptr;

}
/// <summary>
/// 동적인상태에서 충돌체의 모양을 변경하고싶을때
/// </summary>
/// <param name="_v">
/// </param>
void GameObject::SetCollider(Collider::Shape _v)
{
	Release();
	switch (_v)
	{
	case Collider::Shape::Circle:
		m_Collider = new CircleCollider();
		Debug::LogFormat("사각 모양 체인지!\n");
		break;
	case Collider::Shape::Rect:
		m_Collider = new BoxCollider();
		Debug::LogFormat("사각 모양 체인지!\n");
		break;
	}
}

void GameObject::SetCollistion(Collider::CollistionType _v)
{
	switch (_v)
	{
	case Collider::CollistionType::CC:
		m_Collider->SetCollistionType(Collider::CollistionType::CC);
		printf("변경cc");
		break;
	case Collider::CollistionType::AABB:
		m_Collider->SetCollistionType(Collider::CollistionType::AABB);
		printf("변경aabb");
		break;
	case Collider::CollistionType::OBB:
		m_Collider->SetCollistionType(Collider::CollistionType::OBB);
		printf("변경obb");
		break;
	}
}


void GameObject::Release()
{
	delete m_Collider;
	m_Collider = nullptr;
}

void GameObject::ToString()
{
}
