#pragma once
class MonsterEventFactory
{
public:
	const static int SENDER_ID = 1000;
	const static int RECEIVER_ID = 2000; // 현재 쓸대는없는거같은데......과연?
	const static int MONSTER_ID = 10;

	const static int MAX_COUNT = 2;

public:
	MonsterEventFactory();
	~MonsterEventFactory();

public:
	// 샘플 메시지 데이터 만들기
	static void makeSampleDataMessage(std::queue<EventMessage::Ptr>& messageQueue);

	// 샘플 행동 트리 데이터 만들기
	static void makeSampleDataBehaviorTree(BrainTree::BehaviorTree& behaviorTree);
};

