#include "pch.h"
#include "SingletonManager.h"
#include "SpriteData.h"
#include "RRYD2DEngine.h"
#include "ObjectManager.h"
#include "Object.h"
#include "GameObject.h"
#include "Component.h"
#include "Transform.h"
#include "SpriteData.h"
#include "BoundShape.h"
#include "BoundCircle.h"
#include "BoundRect.h"
#include "ObjectBuildAlgorithm.h"
#include "Builder.h"

GameObject::GameObject()
{
	m_Transform = new Transform();
}

GameObject::~GameObject()
{
	delete m_Transform;

	for (auto it : m_Components)
	{
		Object::Destroy(it);
	}
}