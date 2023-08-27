#pragma once
class MonsterEventFactory
{
public:
	const static int SENDER_ID = 1000;
	const static int RECEIVER_ID = 2000; // ���� ����¾��°Ű�����......����?
	const static int MONSTER_ID = 10;

	const static int MAX_COUNT = 2;

public:
	MonsterEventFactory();
	~MonsterEventFactory();

public:
	// ���� �޽��� ������ �����
	static void makeSampleDataMessage(std::queue<EventMessage::Ptr>& messageQueue);

	// ���� �ൿ Ʈ�� ������ �����
	static void makeSampleDataBehaviorTree(BrainTree::BehaviorTree& behaviorTree);
};

