#pragma once

class BoundShape;
class Transform;
class ObjectFactory;
class Component;

class GameObject : public Object
{
protected:

public:
	Transform* m_Transform;
	std::vector<Component*> m_Components;

	GameObject();
	~GameObject();

	template<typename T>
	void		AddComponent();
	template<typename T>
	T*			GetComponent();
};

template<typename T>
inline void		GameObject::AddComponent()
{
	T* com = new T();
	com->m_GameObject = this;

	m_Components.push_back(com);
}

template<typename T>
inline T* GameObject::GetComponent()
{
	for (auto com : m_Components)
	{
		T* c = dynamic_cast<T*>(com);
		if (c != nullptr)
		{
			return c;
		}
	}

	return nullptr;
}
