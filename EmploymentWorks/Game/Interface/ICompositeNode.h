#pragma once
#include "Game/Interface/IBehaviorNode.h"


class ICompositeNode : public IBehaviorNode
{
public:

	//�m�[�h�̒ǉ�
	virtual void AddNode(std::unique_ptr<IBehaviorNode> node) = 0;

};

