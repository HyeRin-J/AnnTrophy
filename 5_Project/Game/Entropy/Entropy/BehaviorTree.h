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
	// �ֱ� ó��
    Status update() { return root->tick(); }

	// �̺�Ʈ �帮�� ó��
	Status updateMessage(BTEventMessage::BaseMessage message)
	{
		return root->onMessage(message);
	}

	// ��Ʈ ����
	bool hasRoot() {
		return root != nullptr;
	}

	// ���� �Ǿ���?
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
