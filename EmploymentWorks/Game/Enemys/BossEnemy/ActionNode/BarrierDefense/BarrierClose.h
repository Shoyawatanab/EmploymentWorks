#pragma once
#include <pch.h>
#include "Game/Interface/IActione.h"
class CommonResources;
class BarrierDefenseAction;
class Barrier;
class BossEnemy;

// BarrierCloseクラスを定義する
class BarrierClose : public IAction
{
public:
	// コンストラクタ
	BarrierClose(CommonResources* resources,BarrierDefenseAction* barrierDefenseAction, Barrier* barrier, BossEnemy* bossEnemy);
	// デストラクタ
	~BarrierClose();
	//初期化
	void Initialize() override;
	// 更新する
	ActionState Update(const float& elapsedTime);
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

