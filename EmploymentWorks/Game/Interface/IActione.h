/*
	IBehaviorNode.h
	渡邊翔也
	行動のインタフェース
*/
#pragma once
#include "pch.h"
#include "Game/Interface/IBehaviorNode.h"


class IAction
{
public:
	virtual ~IAction() = default;

	virtual void Initialize() = 0;

	virtual IBehaviorNode::State Update(float elapsdTime) = 0;



};
