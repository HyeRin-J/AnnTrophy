#pragma once
#include "Leaf.h"
//#include "Blackboard.h"
#include "BTEventMessage.h"

namespace BrainTree {

	class Action : public Leaf
	{
	public:
		Action() {}
		virtual ~Action() {}
		//Action(Blackboard::Ptr blackboard) : blackboard(blackboard) {}

		void initialize() override
		{
			status = Status::Running;
		}

		Status update() override
		{
			//printf("Action, DefaultAction\n");

			return Status::Success;
		}

		Status updateMessage(BTEventMessage::BaseMessage message) override
		{
			return status;
		}

	/*protected:
		Blackboard::Ptr blackboard;*/
	};
}