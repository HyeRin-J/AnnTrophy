#pragma once
#include "Checker.h"
#include "BTEventMessage.h"

namespace BrainTree {

	// GOAL: 메시지 기반으로 체크하는 조건자
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