#pragma once
#include "MonsterPage.h"
#include "..\Share\EventMessage.h"

class MonsterFSM
{
public:
	enum class StateType
	{
		None,	// 초기
		Observe, // 정찰 // 플레이어 범위안에 드나 확인
		Tracking,// 추격
		Dead,	// 사망
	};

	using Ptr = std::shared_ptr<MonsterFSM>;

public:
	MonsterFSM();

public:
	void onTick(int tickIndex = 0, int interval = 0);
	void onMessage(EventMessage::Ptr message);
	void nextPage();

	//sample
	void makeSample();

private:
	void init();
	void change(int nextId);
	void insert(MonsterPage::Ptr ptrPage);

private:
	std::map<int, MonsterPage::Ptr> pages_;
	MonsterPage::Ptr current_;
	StateType state_ = StateType::None;

};

