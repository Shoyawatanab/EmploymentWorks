#pragma once
#include <pch.h>
#include "Game/Interface/IActionState.h"
class CommonResources;
class BarrierDefenseAction;


// BarrierIdelクラスを定義する
class BarrierIdel : public IActionState
{
public:
	// コンストラクタ
	BarrierIdel(BarrierDefenseAction* barrierDefenseAction);
	// デストラクタ
	~BarrierIdel();
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

	BarrierDefenseAction* m_barrierDefenseAction;

};

