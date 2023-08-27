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
	// ��Ÿ��ȿ� ���Դ�.!
	messageQueue.push(std::make_shared<FindPlayerMessage>(SENDER_ID, RECEIVER_ID));
	
	//��¼�� ��¼�� �Ѵ�.

	//���� ���!
	messageQueue.push(std::make_shared<MonsterDeadMessage>(SENDER_ID, RECEIVER_ID, MONSTER_ID));

}

void MonsterEventFactory::makeSampleDataBehaviorTree(BrainTree::BehaviorTree& behaviorTree)
{
	auto sequence = std::make_shared<BrainTree::Sequence>();

	// In ���� üĿ
	auto ObserveChecker = std::make_shared<BrainTree::MonsterObserveChecker>(MONSTER_ID);
	
	// ������Ʈ ī��Ʈ��.
	auto pollingUpdateCountChecker = std::make_shared<BrainTree::UpdateCountChecker>(MAX_COUNT);

	sequence->addChild(ObserveChecker);
	sequence->addChild(pollingUpdateCountChecker);

	auto action = std::make_shared<BrainTree::Action>(); //���� �� �������� �ϴ°� ���� �� ��ӹ޾Ƽ� ���������� ����!
	sequence->addChild(action);

	// ��Ʈ ����.
	behaviorTree.setRoot(sequence);


}
