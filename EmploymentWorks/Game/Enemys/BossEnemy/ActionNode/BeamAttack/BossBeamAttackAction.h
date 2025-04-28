/*
	@file	BossBeamAttackAction.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "Game/Interface/IActione.h"
#include "Game/Interface/IObserver.h"
#include "Game/Enemys/BossEnemy/ActionNode/BeamAttack/BossBeamAttackIdel.h"
#include "Game/Enemys/BossEnemy/ActionNode/BeamAttack/BossBeamAttackPreliminaryAction.h"
#include "Game/Enemys/BossEnemy/ActionNode/BeamAttack/BossBeamAttackCharge.h"
#include "Game/Enemys/BossEnemy/ActionNode/BeamAttack/BossBeamAttackShot.h"
#include "Game/Enemys/BossEnemy/ActionNode/BeamAttack/BossBeamAttackEnd.h"

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


class BossBeamAttackAction : public IAction , IObserver
{

public:


	BossBeamAttackPreliminaryAction* GetBossBeamAttackPreliminaryAction() { return m_preliminaryAction.get(); }

	BossBeamAttackCharge* GetBossBeamAttackCharge() { return m_charge.get(); }

	BossBeamAttackShot* GetBossBeamAttackShot() { return m_shot.get(); }

	BossBeamAttackEnd* GetBossBeamAttackEnd() { return m_attackEnd.get(); }

	BossBeamAttackIdel* GetBossBeamAttackIdel() { return m_idel.get(); }

	IAction* GetCurrentState() { return m_currentState; }


public:
	BossBeamAttackAction(CommonResources* resources,
		BossEnemy* bossEnemy
		, Beam* beam
		, Player* player);
	//デストラクタ
	~BossBeamAttackAction() override ;

	void Initialize() override;

	ActionState Update(const float& elapsedTime)  override ;

	//状態に入った時
	void Enter() override;
	//状態を抜けた時
	void Exit() override;


	//IObserver
//通知時に呼ばれる関数
	void Notify(const Telegram& telegram)  override;

	//状態の変更
	void ChangeState(IAction* nextState);


private:
	// 共通リソース
	CommonResources* m_commonResources;

	IAction* m_currentState;

	std::unique_ptr<BossBeamAttackPreliminaryAction> m_preliminaryAction;

	std::unique_ptr<BossBeamAttackCharge> m_charge;

	std::unique_ptr<BossBeamAttackShot> m_shot;

	std::unique_ptr<BossBeamAttackEnd> m_attackEnd;

	std::unique_ptr<BossBeamAttackIdel> m_idel;
};
