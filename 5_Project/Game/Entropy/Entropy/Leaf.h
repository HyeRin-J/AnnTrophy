#pragma once

#include "Node.h"
#include "BTEventMessage.h"
//#include "Blackboard.h"

namespace BrainTree {

class Leaf : public Node
{
public:
    Leaf() {}
    virtual ~Leaf() {}
    
    virtual Status update() = 0;
    virtual Status updateMessage(BTEventMessage::BaseMessage message) = 0;

};

} // BrainTree
