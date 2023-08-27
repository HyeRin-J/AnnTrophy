#pragma once
#include "..\Share\Action.h"
#include "PageFSM.h"
#include "MonsterFSM.h"

namespace BrainTree {
	
	// 다음 페이지로 전환
	class NextPageAction : public Action
	{
	public:
		NextPageAction(Page* page) : onwer_(page) {}
		virtual ~NextPageAction() {}

		Status update() override
		{
			printf("Action, NextPageAction\n");

			// FSM을 호출
			auto fsm = onwer_->getOwner();
			if (fsm != nullptr)
			{
				fsm->nextPage();
			}

			return Status::Success;
		}

	protected:
		Blackboard::Ptr blackboard;
		Page* onwer_ = nullptr;
	};
}


namespace BrainTree {

	// 다음 페이지로 전환
	class MNextPageAction : public Action
	{
	public:
		MNextPageAction(MonsterPage* page) : onwer_(page) {}
		virtual ~MNextPageAction() {}

		Status update() override
		{
			printf("Action, NextPageAction\n");

			// FSM을 호출
			auto fsm = onwer_->getOwner();
			if (fsm != nullptr)
			{
				fsm->nextPage();
			}

			return Status::Success;
		}

	protected:
		Blackboard::Ptr blackboard;
		MonsterPage* onwer_ = nullptr;
	};
}