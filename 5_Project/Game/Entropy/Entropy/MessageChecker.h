#pragma once
#include "Checker.h"
#include "BTEventMessage.h"

namespace BrainTree {

	// GOAL: �޽��� ������� üũ�ϴ� ������
	class MessageChecker : public Checker
	{
	public:
		MessageChecker() {}
		virtual ~MessageChecker() {}

	public:
		Status updateMessage(BTEventMessage::BaseMessage message) override
		{
			if (check(message))
			{
				return Status::Success;
			}

			return status;
		}
	};
}