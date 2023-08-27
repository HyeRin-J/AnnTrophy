#pragma once

class ObjectManager;

class Object
{
protected:
	std::string name;

public:
	std::string GetName() { return name; }
	void SetName(std::string _name) { name = _name; }
	virtual void	Update() {};

	static void Destroy(Object* obj);

	static Object* Create() { return new Object(); }
};