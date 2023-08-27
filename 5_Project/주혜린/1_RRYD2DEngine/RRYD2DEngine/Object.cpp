#include "pch.h"
#include "SingletonManager.h"
#include "Object.h"

void Object::Destroy(Object* obj)
{
	delete obj;
}