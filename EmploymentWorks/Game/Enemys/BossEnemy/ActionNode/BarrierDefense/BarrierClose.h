#pragma once
#include <pch.h>
#include "Game/Interface/IActionState.h"
class CommonResources;
class BarrierDefenseAction;
class Barrier;
class BossEnemy;

// BarrierCloseクラスを定義する
class BarrierClose : public IActionState
{
public:
	// コンストラクタ
	BarrierClose(BarrierDefenseAction* barrierDefenseAction, Barrier* barrier, BossEnemy* bossEnemy);
	// デストラクタ
	~BarrierClose();
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

	Barrier* m_barrier;

	float m_time;

	BossEnemy* m_bossEnemy;

};

