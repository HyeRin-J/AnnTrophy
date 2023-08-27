#pragma once

class ObjectBuildAlgorithm;
class GameObject;

class Builder
{
protected:
	ObjectBuildAlgorithm* algorithm;

public:
	Builder() : algorithm(nullptr) {};

	Builder(ObjectBuildAlgorithm* algo) { algorithm = algo; }

	Builder* SetAlgorithm(ObjectBuildAlgorithm* algo) { algorithm = algo; return this; }

	ObjectBuildAlgorithm* GetInstance() { return algorithm; }

	ObjectBuildAlgorithm* build();
	
};

class ObjectFactory
{
public:
	template <typename T>	static T* CreateObject();
	template <typename T>	static void DeleteObject(T* obj);
};


template <typename T>
inline T* ObjectFactory::CreateObject()
{
	const type_info& id = typeid(T);
	Builder builder;

	if (id == typeid(GameObject))
	{
		builder.SetAlgorithm(new GameObjectAlogorithm());
		
	}

	Object* obj = builder.build()->GetInstance();
	ObjectManager::GetInstance()->m_Objects.push_back(static_cast<T*>(obj));

	return static_cast<T*>(obj);
}

template<typename T>
inline void ObjectFactory::DeleteObject(T* obj)
{
	ObjectManager::GetInstance()->Destroy(&obj);
}