#pragma once

#include "Node.h"
#include "Leaf.h"
#include <vector>

namespace BrainTree {
   
class Composite : public Node
{
public:
    virtual ~Composite() {}
    
    void addChild(Node* child) { children.push_back(child); }
    bool hasChildren() const { return !children.empty(); }
    int getIndex() const { return index; }
    
    void DeleteAllNode()
    {
        if (hasChildren() == true)
        {
            for (auto child : children)
            {
                Composite* _com = dynamic_cast<Composite*>(child);
                BrainTree::Leaf* _leaf = dynamic_cast<BrainTree::Leaf*>(child);
                if(_com != nullptr) _com->DeleteAllNode();
                if (_leaf != nullptr) delete _leaf;
            }
        }

        children.clear();
    }

protected:
    std::vector<Node*> children;
    int index = 0;
};

} // BrainTree