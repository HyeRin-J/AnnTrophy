#pragma once

#include "Node.h"
#include "Composite.h"
//#include "Blackboard.h"
#include "BTEventMessage.h"

namespace BrainTree {

class BehaviorTree : public Node
{
public:
   // BehaviorTree() : blackboard(std::make_shared<Blackboard>()) {}
	BehaviorTree() {};
    BehaviorTree(Node* rootNode) : BehaviorTree() { root = rootNode; }
    
public:
	// 주기 처리
    Status update() { return root->tick(); }

	// 이벤트 드리븐 처리
	Status updateMessage(BTEventMessage::BaseMessage message)
	{
		return root->onMessage(message);
	}

	// 루트 상태
	bool hasRoot() {
		return root != nullptr;
	}

	// 종료 되었나?
	bool isTerminatedRoot()
	{
		return root->isTerminated();
	}

	void DeleteAllNode()
	{
		if (hasRoot() == true)
		{
			dynamic_cast<BrainTree::Composite*>(root)->DeleteAllNode();
		}
	}

	///Node* GetRoot() { return root; }

public:
    void setRoot(Node* node) { root = node; }
    //Blackboard::Ptr getBlackboard() const { return blackboard; }
    
private:
    Node* root = nullptr;
    //Blackboard::Ptr blackboard = nullptr;
};

} // BrainTree
