#pragma once
#include "Game/Interface/IBehaviorNode.h"


class ICompositeNode : public IBehaviorNode
{
public:

	//ノードの追加
	virtual void AddNode(std::unique_ptr<IBehaviorNode> node) = 0;

};

