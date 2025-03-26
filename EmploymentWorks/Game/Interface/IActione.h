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

	virtual IBehaviorNode::State Update(const float& elapsedTime) = 0;
	//状態に入った時
	virtual void Enter() = 0;
	//状態を抜けた時
	virtual void Exit() = 0;

};
