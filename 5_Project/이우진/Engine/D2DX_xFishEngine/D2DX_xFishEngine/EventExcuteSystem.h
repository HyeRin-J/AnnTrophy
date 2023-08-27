#pragma once

enum class EnumEvent
{
	None = -1, Awake, OnEnable, 
	Start, FixedUpdate, Update, OnRender, OnDisable, OnDestroy
};


class EventExcuteSystem : public SingletonManager<EventExcuteSystem>
{
	//등록한 이벤트 함수
	std::map < Component*, std::map<EnumEvent, std::function<void()>>>*m_EventDictionary;
	//실행할 이벤트 큐
	std::deque< std::function<void()>>* m_EventQueue;

	//이벤트를 큐에 넣는다
	bool QueueEvent(std::function<void()> _func);


public:
	//기본 생성자
	EventExcuteSystem();

	/// <summary>
	/// 이벤트 함수를 등록한다
	/// </summary>
	/// <param name="_component">컴포넌트의 객체</param>
	/// <param name="_eventName">등록할 이벤트 이름</param>
	/// <param name="_func">등록할 이벤트 멤버 함수</param>
	/// <returns></returns>
	bool AttachEvent(Component* _component, EnumEvent _eventName, std::function<void()> _func);
	bool DetachEvent(Component* _component, EnumEvent _eventName, std::function<void()> _func);

	/// <summary>
	/// 전체 메시지, Update 같은 거
	/// </summary>
	/// <param name="_event"></param>
	void SendEventMessage(EnumEvent _event);

	/// <summary>
	/// OnEnable or OnDisable
	/// </summary>
	/// <param name="_component"></param>
	/// <param name="_event"></param>
	void SendEventMessage(Component* _component, EnumEvent _event);

	/// <summary>
	/// 큐를 처리한다
	/// </summary>
	void Update();
};

