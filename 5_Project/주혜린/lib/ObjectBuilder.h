#pragma once
class GameObject;


class ObjectBuildAlgorithm
{
protected:
	GameObject* obj;

public:
	virtual void CreateObject() { if(obj == nullptr) obj = new GameObject(); }

	void SetPosition(Vector2 pos) { obj->SetPosition(pos); }
	void SetRotation(Vector2 rot) { obj->SetRotation(rot); }
	void SetScale(Vector2 scale) { obj->SetScale(scale); }
	
	GameObject* GetInstance()
	{
		return obj; 
	}
};

class TempBuilder : public ObjectBuildAlgorithm
{
public:
	virtual void CreateObject() { if (obj == nullptr) obj = new TempObject(); }


};