#pragma once

class GameObject;
class BoundCircle;
class BoundRect;

class ObjectBuildAlgorithm
{
protected:
	Object* obj;

public:
	virtual void CreateObject() { if (obj == nullptr) obj = new Object(); }

	Object* GetInstance()
	{
		return obj;
	}
};

class GameObjectAlogorithm : public ObjectBuildAlgorithm
{
public:
	virtual void CreateObject()
	{
		if (obj == nullptr)
			obj = new GameObject();
	}
};