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
	Debug::LogFormat("�ش簴ü�� �����մϴ�");
	delete _obj;
	_obj = nullptr;
}

void Object::Destroy(Object* _obj, float _deleteTime)
{
	Debug::LogFormat("%f ��ŭ �ð��� ����Ǿ� �����մϴ�", _deleteTime);
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
