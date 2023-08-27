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

	//������ �νĹ����ȿ� �÷��̾� �� �ִ�!
	class FindPlayerMessage : public BaseMessage
	{
	public:
		FindPlayerMessage():BaseMessage(BTEventMessage::MessageId::DETECTPLAYER){};

	};


	//������ ���� ���� �ȿ� �÷��̾ �ִ�!
	class InReachMessage : public BaseMessage
	{
	public:
		InReachMessage() :BaseMessage(BTEventMessage::MessageId::INREACH) {};
	};


	// Jump melee monster �� //���� ���� �÷������ִ�.
	class DetectedTopPlatform : public BaseMessage
	{
	public:
		DetectedTopPlatform() :BaseMessage(BTEventMessage::MessageId::DETECTTOPPLATFORM) {};
	};

};

