#include "pch.h"
#include <iostream>
#include <deque>
#include <map>
#include <list>
#include <string>

#include "BaseMessage.h"
#include "CustomMessage.h"
#include "SingletonManager.h"
#include "MessageSystem.h"
#include "CustomClass.h"

MessageSystem::MessageSystem()
{
	m_ListenerDictionary = new map<string, list<MessageFunc>>();
	m_MessageQueue = new deque<BaseMessage*>();
}

void MessageSystem::Update()
{
	float timer = 0.0f;
	while (m_MessageQueue->size() > 0)
	{
		if (m_MaxQueueProcessingTime > 0.0f)
		{
			if (timer > m_MaxQueueProcessingTime)
				return;
		}

		BaseMessage* msg = dynamic_cast<BaseMessage*>(m_MessageQueue->front());
		m_MessageQueue->pop_front();


		if (!TriggerMessage(msg))
		{
			cout << "MessagingSystem : Error when processing message - " << typeid(msg).name() << endl;
		}
	}

}

