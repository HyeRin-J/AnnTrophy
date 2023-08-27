#include "pch.h"
#include "Vector2.h"
#include "FMatrix3x2.h"
#include "Object.h"
#include "Component.h"
#include "Transform.h"
#include "Collider.h"
#include "Debug.h"


Object::Object() : m_name("")
{
}

Object::Object(string _name)
{
}

Object::~Object()
{
}

void Object::ToString()
{
}

bool operator==(Object _a, Object _b)
{
	return false;
}

void Object::Destroy()
{
	delete this;
	
}

void Object::Destroy(Object* _obj)
{
	Debug::LogFormat("해당객체를 삭제합니다");
	delete _obj;
	_obj = nullptr;
}

void Object::Destroy(Object* _obj, float _deleteTime)
{
	Debug::LogFormat("%f 만큼 시간이 경과되어 삭제합니다", _deleteTime);
	delete _obj;
	_obj = nullptr;
}

bool Object::operator!=(Object& _another)
{
	return false;
}

bool Object::operator==(Object& _another)
{
	return false;
}

void Object::Release()
{

}
