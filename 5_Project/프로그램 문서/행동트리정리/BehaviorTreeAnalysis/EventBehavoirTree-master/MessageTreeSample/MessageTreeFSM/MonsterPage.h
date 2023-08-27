#pragma once
#include "stdafx.h"

class MonsterFSM;

class MonsterPage {
public:
	using Ptr = std::shared_ptr<MonsterPage>;

public:
	MonsterPage(int pageId, MonsterFSM* owner);
	~MonsterPage();

public:
	/// 로직 인터페이스
	// 시작
	void onStart();
	// 주기 업데이트
	void onUpdate();
	// 종료
	void onEnd();
	// 메시지
	void onMessage(EventMessage::Ptr message);

public:
	/// 더미 데이터
	// 샘플 BT를 만든다.
	void makeSample();

public:
	/// Getter/Setter
	int getPageId() const { return pageId_; }
	void setRoot(const BrainTree::Node::Ptr& node) { behaviorTree_.setRoot(node); };
	MonsterFSM* getOwner() const { return owner_; }

private:
	int pageId_ = 0;
	MonsterFSM* owner_ = nullptr;
	BrainTree::BehaviorTree behaviorTree_;
};


