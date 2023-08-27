#include "pch.h"
#include "Object.h"
#include "Component.h"
#include "Collider.h"
#include "Vector2.h"
#include "FMatrix3x2.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "Transform.h"
#include "GameObject.h"
#include "SingletonManager.h"
#include "EventExcuteSystem.h"

Component::Component()
{
	EventExcuteSystem* eventSystem = EventExcuteSystem::GetInstance();

	std::function<void()> awake = std::bind(&Component::Awake, this);
	eventSystem->AttachEvent(this, EnumEvent::Awake, awake);

	std::function<void()> enable = std::bind(&Component::OnEnable, this);
	eventSystem->AttachEvent(this, EnumEvent::OnEnable, enable);

	std::function<void()> start = std::bind(&Component::Start, this);
	eventSystem->AttachEvent(this, EnumEvent::Start, start);

	std::function<void()> fixedUpdate = std::bind(&Component::FixedUpdate, this);
	eventSystem->AttachEvent(this, EnumEvent::FixedUpdate, fixedUpdate);

	std::function<void()> update = std::bind(&Component::Update, this);
	eventSystem->AttachEvent(this, EnumEvent::Update, update);

	std::function<void()> render = std::bind(&Component::OnRender, this);
	eventSystem->AttachEvent(this, EnumEvent::OnRender, render);

	std::function<void()> disable = std::bind(&Component::OnDisable, this);
	eventSystem->AttachEvent(this, EnumEvent::OnDisable, disable);

	std::function<void()> destroy = std::bind(&Component::OnDestroy, this);
	eventSystem->AttachEvent(this, EnumEvent::OnDestroy, destroy);
}
Component::~Component()
{
	EventExcuteSystem* eventSystem = EventExcuteSystem::GetInstance();

	std::function<void()> awake = std::bind(&Component::Awake, this);
	eventSystem->DetachEvent(this, EnumEvent::Awake, awake);

	std::function<void()> enable = std::bind(&Component::OnEnable, this);
	eventSystem->DetachEvent(this, EnumEvent::OnEnable, enable);

	std::function<void()> start = std::bind(&Component::Start, this);
	eventSystem->DetachEvent(this, EnumEvent::Start, start);

	std::function<void()> fixedUpdate = std::bind(&Component::FixedUpdate, this);
	eventSystem->DetachEvent(this, EnumEvent::FixedUpdate, fixedUpdate);

	std::function<void()> update = std::bind(&Component::Update, this);
	eventSystem->DetachEvent(this, EnumEvent::Update, update);

	std::function<void()> render = std::bind(&Component::OnRender, this);
	eventSystem->DetachEvent(this, EnumEvent::OnRender, render);

	std::function<void()> disable = std::bind(&Component::OnDisable, this);
	eventSystem->DetachEvent(this, EnumEvent::OnDisable, disable);

	std::function<void()> destroy = std::bind(&Component::OnDestroy, this);
	eventSystem->DetachEvent(this, EnumEvent::OnDestroy, destroy);
}

bool Component::CampareTag(string _name)
{
	if (_name.c_str())
	{
		//어떤 조건을걸고..
		//오브젝트의 담긴 태그를 출력하게 하면 되겠지?
	}
	return false;
}

void Component::SetActive(bool _active)
{
	if (_active)
	{
		EventExcuteSystem::GetInstance()->SendEventMessage(this, EnumEvent::OnEnable);
	}
	else
	{
		EventExcuteSystem::GetInstance()->SendEventMessage(this, EnumEvent::OnDisable);
	}
	m_IsActive = _active;
}

void Component::ToString()
{
}


