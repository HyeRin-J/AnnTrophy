#pragma once
#include "MessageEnum.h"

namespace BTEventMessage
{
	class BaseMessage 
	{
	public:
		//GameObject m_SourceObject;
		BTEventMessage::MessageId m_state;

	public:

		//BaseMessage(GameObject& _object, BTEventMessage::MessageId _state) : m_SourceObject(_object), m_state(_state) {};

		//GameObject& GetGameObject() { return m_SourceObject; };
		//void SetGameObject(GameObject& _object) { m_SourceObject = _object; };

		BaseMessage( BTEventMessage::MessageId _state) : m_state(_state) {};

		BTEventMessage::MessageId& GetState() { return m_state; };
		void SetState(BTEventMessage::MessageId& _state) { m_state = _state; };

	};

	class MoveMessage : public BaseMessage
	{
	public:
		MoveMessage() :BaseMessage(MessageId::MOVE) {};
	};

	//몬스터의 인식범위안에 플레이어 가 있다!
	class FindPlayerMessage : public BaseMessage
	{
	public:
		FindPlayerMessage():BaseMessage(BTEventMessage::MessageId::DETECTPLAYER){};

	};


	//몬스터의 공격 범위 안에 플레이어가 있다!
	class InReachMessage : public BaseMessage
	{
	public:
		InReachMessage() :BaseMessage(BTEventMessage::MessageId::INREACH) {};
	};


	// Jump melee monster 용 //몬스터 위에 플랫폼이있다.
	class DetectedTopPlatform : public BaseMessage
	{
	public:
		DetectedTopPlatform() :BaseMessage(BTEventMessage::MessageId::DETECTTOPPLATFORM) {};
	};

};

