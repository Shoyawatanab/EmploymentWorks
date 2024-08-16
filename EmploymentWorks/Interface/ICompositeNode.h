#pragma once
#include "Interface/IBehaviorNode.h"


class ICompositeNode : public IBehaviorNode
{
public:

	virtual void AddNode(std::unique_ptr<IBehaviorNode> node) = 0;

};

