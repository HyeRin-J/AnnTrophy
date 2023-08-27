#pragma once
using namespace std;

using MessageFunc = bool(*)(BaseMessage*);

class MessageSystem : public SingletonManager<MessageSystem>
{
private:
	
	map<string, list<MessageFunc>>* m_ListenerDictionary;//= new map<string, list<void*>>()
	deque<BaseMessage*>* m_MessageQueue; //= new deque<BaseMessage>();
	const float m_MaxQueueProcessingTime = 0.1667f;

private:

public:
	MessageSystem();

	template<typename T>
	bool AttachListener(T* _class, MessageFunc handler);

	template<typename T>
	bool DetachListener(T* _class, MessageFunc handler);

	template<typename T>
	bool QueueMesssage(T* msg);

	template<typename T>
	bool TriggerMessage(T* msg);

	void Update();
};
template<typename T>
inline bool MessageSystem::AttachListener(T* _class, MessageFunc handler)
{
	if (_class == nullptr)
	{
		std::cout << "MessagingSystem : AttachListener failed due to no message type specified" << std::endl;
		return false;
	}

	string msgName = (static_cast<BaseMessage*>(_class))->GetName();

	if (m_ListenerDictionary->count(msgName) == 0) // check contains key 0 is not contain 
	{
		m_ListenerDictionary->emplace(make_pair(msgName, list<MessageFunc>()));
	}


	auto it = m_ListenerDictionary->find(msgName);

	list<MessageFunc>& listenerList = it->second;

	bool hasHandler = false;

	for (auto it : listenerList) // check handler
	{
		if (it == handler)
		{
			hasHandler = true;
		}
	}

	if (hasHandler == true)
	{
		return false;
	}

	listenerList.push_back(handler);

	return true;
}
template<typename T>
inline bool MessageSystem::DetachListener(T* _class, MessageFunc handler)
{
	if (_class == nullptr)
	{
		std::cout << "MessagingSystem : DetachListener failed due to no message type specified" << std::endl;
		return false;
	}

	BaseMessage* message = static_cast<BaseMessage*>(_class);

	if (m_ListenerDictionary->count(message->GetName()) == 0) // check contains key 0 is not contain 
	{
		return false;
	}

	auto it = m_ListenerDictionary->find(message->GetName());
	list<MessageFunc>& listenerList = it->second;

	bool hasHandler = false;

	for (auto it : listenerList) // check handler
	{
		if (it == handler)
		{
			hasHandler = true;
		}
	}

	if (hasHandler == true)
	{
		return false;
	}


	for (auto it = listenerList.begin(); it != listenerList.end(); it++) // remove(handler)
	{
		if (*it == handler)
		{
			listenerList.erase(it);
		}
	}

	return true;
}

template<typename T>
inline bool MessageSystem::QueueMesssage(T* msg)
{
	BaseMessage* message = static_cast<BaseMessage*>(msg);

	if (m_ListenerDictionary->count(message->GetName()) == 0) // check contains key 0 is not contain 
	{
		return false;
	}

	m_MessageQueue->push_back(msg);

	return true;
}

template<typename T>
inline bool MessageSystem::TriggerMessage(T* msg)
{
	BaseMessage* message = static_cast<BaseMessage*>(msg);

	if (m_ListenerDictionary->count(message->GetName()) == 0) // check contains key 0 is not contain 
	{
		std::cout << "MessagingSystem : Message \"" << message->GetName() << "\" has no listeners!" << std::endl;
		return false;
	}

	auto it = m_ListenerDictionary->find(message->GetName());
	list<MessageFunc>& listenerList = it->second;

	for (auto it : listenerList)
	{
		if (it(msg))
		{
			return true;
		}
	}

	return true;
}