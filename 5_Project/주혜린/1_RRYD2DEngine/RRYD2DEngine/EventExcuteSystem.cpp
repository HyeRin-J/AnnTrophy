#include "pch.h"
#include <iostream>
#include "Object.h"
#include "Component.h"
#include "SingletonManager.h"
#include "EventExcuteSystem.h"

EventExcuteSystem::EventExcuteSystem()
{
	m_EventDictionary = new std::map<Component*, std::map<EnumEvent, std::function<void()>>>();
	m_EventQueue = new std::deque<std::function<void()>>();
}

bool EventExcuteSystem::AttachEvent(Component* _component, EnumEvent _eventName, std::function<void()> _func)
{
	//������Ʈ ��ü�� ���ų�(�׷� ���� ������)
	//�̺�Ʈ �̸��� ���������� ���� ���
	if (_component == nullptr || _eventName == EnumEvent::None)
	{
		std::cout << "EventExcute : component is nullptr or event name is empty" << std::endl;
		return false;
	}

	//���� ���� ��ü�� ��ϵ� �̺�Ʈ �Լ� ���̺��� ���� ���
	if (m_EventDictionary->count(_component) == 0)
	{
		//�Լ� ���̺��� ���� �����
		m_EventDictionary->emplace(make_pair(_component, std::map < EnumEvent, std::function<void()>>()));
	}

	//���� ������Ʈ ��ü�� Ű�� �ϴ� ���̺��� �����´�.
	auto it = m_EventDictionary->find(_component);

	//map�̹Ƿ� ���̺��� value�� �ش��Ѵ�
	std::map<EnumEvent, std::function<void()>>& eventList = it->second;

	bool hasEventFunc = false;

	// check handler
	for (auto it : eventList)
	{
		//�̹� ��ϵ� �̺�Ʈ �Լ��� ������ üũ���ش�
		if (it.first == _eventName)
		{
			hasEventFunc = true;
			break;
		}
	}

	//����� �Ǿ� ������ �Լ� ����
	if (hasEventFunc == true)
	{
		return false;
	}

	//����� �� �Ǿ� ������ ���� ����Ѵ�.
	eventList.emplace(make_pair(_eventName, _func));
	return true;
}

bool EventExcuteSystem::DetachEvent(Component* _component, EnumEvent _eventName, std::function<void()> _func)
{
	//������Ʈ ��ü�� ���ų�(�׷� ���� ������)
	//�̺�Ʈ �̸��� ���������� ���� ���
	if (_component == nullptr || _eventName == EnumEvent::None)
	{
		std::cout << "EventExcute : component is nullptr or event name is empty" << std::endl;
		return false;
	}

	//���� ��ϵ� �̺�Ʈ �Լ��� ������ ����
	if (m_EventDictionary->count(_component) == 0) 
	{
		return false;
	}

	//�̺�Ʈ �Լ� ���̺��� ��������
	auto it = m_EventDictionary->find(_component);
	std::map<EnumEvent, std::function<void()>>& EventList = it->second;

	bool hasEventFunc = false;

	// check handler
	for (auto it : EventList) 
	{
		if (it.first == _eventName)
		{
			hasEventFunc = true;
			break;
		}
	}

	if (hasEventFunc == false)
	{
		return false;
	}

	//��ϵ� �̺�Ʈ �Լ��� �����Ѵ�.
	for (auto it = EventList.begin(); it != EventList.end(); it++)
	{
		if ((*it).first == _eventName)
		{
			EventList.erase(it);
			break;
		}
	}

	return true;
}

bool EventExcuteSystem::QueueEvent(std::function<void()> _func)
{
	//ť�� �Լ��� ����Ѵ�
	m_EventQueue->push_back(_func);

	return true;
}

void EventExcuteSystem::SendEventMessage(EnumEvent _event)
{
	//�̺�Ʈ �Լ� ���̺��� ���鼭
	for (auto it = m_EventDictionary->begin() ; it != m_EventDictionary->end(); it++)
	{
		//���� ���� ������Ʈ�� ��Ȱ��ȭ �����̸� ��������
		if (it->first->IsActive() == false) continue;
		
		//�޽����� ���� �̺�Ʈ �Լ��� ť�� �ִ´�.
		QueueEvent((it->second)[_event]);
	}
}

void EventExcuteSystem::SendEventMessage(Component* _component, EnumEvent _event)
{
	// �� ��ü�� �̺�Ʈ �Լ� ���̺��� �����´�
	auto it = m_EventDictionary->find(_component);
	std::map<EnumEvent, std::function<void()>>& EventList = it->second;

	//�Լ� ���̺��� ã�´�.
	auto func = EventList[_event];

	//�̺�Ʈ �Լ��� ť�� �ִ´�
	QueueEvent(func);
}

void EventExcuteSystem::Update()
{
	//ť�� ����ִ� �̺�Ʈ�� ������
	while (m_EventQueue->size() > 0)
	{
		//���� ���� ���� �����ͼ�
		std::function<void()>& func = m_EventQueue->front();

		//�Լ��� �����ϰ�
		if (func != nullptr)
		{
			func();
		}

		//ť���� �����Ѵ�.
		m_EventQueue->pop_front();
	}
}
