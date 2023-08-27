#pragma once

class Object;
class GameObject;

class ObjectManager : public SingletonManager<ObjectManager>
{
public:
	std::vector<GameObject*> m_Objects;

	void Destroy(GameObject** obj);
};

