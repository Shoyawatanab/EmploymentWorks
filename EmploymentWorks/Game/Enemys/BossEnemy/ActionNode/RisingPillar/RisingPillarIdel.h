#pragma once
#include <pch.h>
#include "Game/Interface/IActionState.h"
class CommonResources;
class RisingPillarvAction;


// RisingPillarIdelクラスを定義する
class RisingPillarIdel : public IActionState
{
public:
	// コンストラクタ
	RisingPillarIdel(RisingPillarvAction* risingPillarvAction);
	// デストラクタ
	~RisingPillarIdel();
	//初期化
	void Initialize(CommonResources* resources) override;
	// 更新する
	IBehaviorNode::State Update(const float& elapsedTime);
	//状態に入った時
	void Enter() override;
	//状態を抜けた時
	void Exit() override;


private:

	// 共通リソース
	CommonResources* m_commonResources;

	RisingPillarvAction* m_risingPillarvAction;

};

