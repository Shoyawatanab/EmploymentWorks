/*
	@file	BossJumpAttackAction.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "Game/Interface/IActione.h"
#include"Game/Interface/IActionState.h"
#include "Game/Interface/IObserver.h"
#include "Game/Enemys/BossEnemy/ActionNode/JumpAttack/BossJumpAttackCharge.h"
#include "Game/Enemys/BossEnemy/ActionNode/JumpAttack/BossJumpAttackJump.h"

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


class BossJumpAttackAction : public IAction , IObserver
{

public:

	static  constexpr float JUMPPOWER = 0.3f;

	static  constexpr float MOVESPEED = 9.0f;

public:


	IAction* GetCurrentState() { return m_currentState; }

	BossJumpAttackCharge* GetBossJumpAttackCharge() { return m_charge.get(); }

	BossJumpAttackJump* GetBossJumpAttackJump() { return m_jump.get(); }

public:
	BossJumpAttackAction(CommonResources* resources,
		BossEnemy* bossEnemy
		, Player* player);
	//デストラクタ
	~BossJumpAttackAction() override ;

	void Initialize() override;

	IBehaviorNode::State Update(const float& elapsedTime)  override ;
	//状態に入った時
	void Enter() override ;
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

	std::unique_ptr<BossJumpAttackCharge> m_charge;

	std::unique_ptr<BossJumpAttackJump> m_jump;

};
