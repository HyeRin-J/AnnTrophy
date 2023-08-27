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
	/// ���� �������̽�
	// ����
	void onStart();
	// �ֱ� ������Ʈ
	void onUpdate();
	// ����
	void onEnd();
	// �޽���
	void onMessage(EventMessage::Ptr message);

public:
	/// ���� ������
	// ���� BT�� �����.
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


