/*
	@file	BossRushAttackAction.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "Game/Interface/IActione.h"
#include"Game/Interface/IActionState.h"
#include "Game/Interface/IObserver.h"
#include "Game/Enemys/BossEnemy/ActionNode/RushAttack/BossRushAttackCharge.h"
#include "Game/Enemys/BossEnemy/ActionNode/RushAttack/BossRushAttackRush.h"

// 前方宣言
class CommonResources;
class BossEnemy;
class Beam;
class Player;

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class BossRushAttackAction : public IAction , IObserver
{

public:


	IAction* GetCurrentState() { return m_currentState; }

	BossRushAttackCharge* GetBossRushAttackCharge() { return m_charge.get(); }

	BossRushAttackRush* GetBossRushAttackRush() { return m_rush.get(); }

public:
	BossRushAttackAction(CommonResources* resources,
		BossEnemy* bossEnemy
		, Player* player);
	//デストラクタ
	~BossRushAttackAction() override ;

	void Initialize() override;

	IBehaviorNode::State Update(const float& elapsedTime)  override ;
	//状態に入った時
	void Enter() override ;
	//状態を抜けた時
	void Exit() override;


	//IObserver
//通知時に呼ばれる関数
	void Notify(EventParams::EventType type, void* datas)  override;

	//状態の変更
	void ChangeState(IAction* nextState);


private:
	// 共通リソース
	CommonResources* m_commonResources;

	IAction* m_currentState;

	std::unique_ptr<BossRushAttackCharge> m_charge;

	std::unique_ptr<BossRushAttackRush> m_rush;

};
