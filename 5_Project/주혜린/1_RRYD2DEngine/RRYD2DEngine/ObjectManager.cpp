#include "pch.h"
#include "SingletonManager.h"
#include "Object.h"
#include "GameObject.h"
#include "ObjectManager.h"
#include "Component.h"
#include "Transform.h"

void ObjectManager::Destroy(GameObject** obj)
{
	for (auto it = GetInstance()->m_Objects.begin(); it <= GetInstance()->m_Objects.end(); it++)
	{
		if (*it == *obj)
		{
			GetInstance()->m_Objects.erase(it);
			break;
		}
	}

	delete *obj;
}
