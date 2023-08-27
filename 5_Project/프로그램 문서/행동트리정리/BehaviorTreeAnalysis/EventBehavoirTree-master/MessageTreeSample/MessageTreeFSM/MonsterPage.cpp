#include "stdafx.h"
#include "NextPageAction.h"
#include "MonsterFSM.h"
#include "MonsterPage.h"

MonsterPage::MonsterPage(int pageId, MonsterFSM* owner)
	: pageId_(pageId)
	, owner_(owner)
{
}

MonsterPage::~MonsterPage()
{
}

void MonsterPage::onStart()
{
	UTIL::doLog("===[Monster Page Start:", pageId_, "]===");
}

void MonsterPage::onUpdate()
{
	// Not
	if (!behaviorTree_.hasRoot())
	{
		return;
	}

	// is Terminated ?
	if (behaviorTree_.isTerminatedRoot())
	{
		return;
	}

	behaviorTree_.update();
}

void MonsterPage::onEnd()
{
	UTIL::doLog("===[Monster Page End:", pageId_, "]===");
}

void MonsterPage::onMessage(EventMessage::Ptr message)
{
	// Not
	if (!behaviorTree_.hasRoot())
	{
		return;
	}

	// is Terminated ?
	if (behaviorTree_.isTerminatedRoot())
	{
		return;
	}

	behaviorTree_.onMessage(message);
}

void MonsterPage::makeSample()
{
	const int TEST_COUNT = 2;

	if (!behaviorTree_.hasRoot())
	{
		auto sequence = std::make_shared<BrainTree::Sequence>();
		auto updateCountChecker = std::make_shared<BrainTree::UpdateCountChecker>(TEST_COUNT);
		auto action = std::make_shared<BrainTree::Action>();
		auto nextPageAction = std::make_shared<BrainTree::MNextPageAction>(this);

		sequence->addChild(updateCountChecker);
		sequence->addChild(action);
		sequence->addChild(nextPageAction);

		// 루트 지정
		setRoot(sequence);
	}


}
