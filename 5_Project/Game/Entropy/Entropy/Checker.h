#pragma once
#include "Leaf.h"
#include "BTEventMessage.h"

namespace BrainTree {

	// 메시지 처리용
	class Checker : public Leaf
	{
	public:
		Checker() {}
		virtual ~Checker() {}

		void initialize() override
		{
			status = Status::Running;
		}

		Status update() override
		{
			return status;
		}

	protected:
		virtual bool check(BTEventMessage::BaseMessage message) = 0;
	};




} // BrainTree
