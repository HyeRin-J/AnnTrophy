#include "stdafx.h"
#include "MonsterObserveChecker.h"
#include "MonsterEventFactory.h"

MonsterEventFactory::MonsterEventFactory()
{
}

MonsterEventFactory::~MonsterEventFactory()
{
}

void MonsterEventFactory::makeSampleDataMessage(std::queue<EventMessage::Ptr>& messageQueue)
{
	// 사거리안에 들어왔다.!
	messageQueue.push(std::make_shared<FindPlayerMessage>(SENDER_ID, RECEIVER_ID));
	
	//어쩌구 저쩌구 한다.

	//몬스터 사망!
	messageQueue.push(std::make_shared<MonsterDeadMessage>(SENDER_ID, RECEIVER_ID, MONSTER_ID));

}

void MonsterEventFactory::makeSampleDataBehaviorTree(BrainTree::BehaviorTree& behaviorTree)
{
	auto sequence = std::make_shared<BrainTree::Sequence>();

	// In 정찰 체커
	auto ObserveChecker = std::make_shared<BrainTree::MonsterObserveChecker>(MONSTER_ID);
	
	// 업데이트 카운트함.
	auto pollingUpdateCountChecker = std::make_shared<BrainTree::UpdateCountChecker>(MAX_COUNT);

	sequence->addChild(ObserveChecker);
	sequence->addChild(pollingUpdateCountChecker);

	auto action = std::make_shared<BrainTree::Action>(); //어택 및 여러가지 하는거 따로 또 상속받아서 만들어줘야함 노드로!
	sequence->addChild(action);

	// 루트 지정.
	behaviorTree.setRoot(sequence);


}
