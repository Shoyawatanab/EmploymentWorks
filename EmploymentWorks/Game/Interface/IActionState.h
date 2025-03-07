/*
* ステーとパターンのインターフェース
*/
#pragma once
#include "pch.h"
#include "Game/Interface/IBehaviorNode.h"

class CommonResources;


class IActionState
{
public:
	//デストラクタ
	virtual ~IActionState() = default;
	//初期化
	virtual void Initialize(CommonResources* resources) = 0;
	// 更新する
	virtual IBehaviorNode::State Update(const float& elapsedTime) = 0;
	//状態に入った時
	virtual void Enter() = 0;
	//状態を抜けた時
	virtual void Exit() = 0;



};
