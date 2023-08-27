#include "pch.h"
#include <functional>
#include "SpriteData.h"
#include "SingletonManager.h"
#include "ObjectManager.h"
#include "RRYD2DEngine.h"
#include "Object.h"
#include "GameObject.h"
#include "Component.h"
#include "Transform.h"
#include "EventExcuteSystem.h"

Transform::Transform()
{

};

void Transform::Update()
{
	
}

void Transform::Translate(Vector2 vec)
{
	m_Position.x += vec.x;
	m_Position.y += vec.y;
}

void Transform::Rotate(float angle)
{
}
