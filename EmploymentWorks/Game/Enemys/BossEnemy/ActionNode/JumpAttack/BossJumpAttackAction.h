/*
	@file	BossJumpAttackAction.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "Game/Entities/ActionStateController.h"
#include "Game/Interface/IObserver.h"
#include "Game/Enemys/BossEnemy/ActionNode/JumpAttack/BossJumpAttackCharge.h"
#include "Game/Enemys/BossEnemy/ActionNode/JumpAttack/BossJumpAttackJump.h"
#include "Game/Enemys/BossEnemy/ActionNode/Orientation/OrientationAction.h"


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


class BossJumpAttackAction : public ActionStateController 
{

public:

	static  constexpr float JUMPPOWER = 0.3f;

	static  constexpr float MOVESPEED = 9.0f;

public:



	BossJumpAttackCharge* GetBossJumpAttackCharge() { return m_charge.get(); }

	BossJumpAttackJump* GetBossJumpAttackJump() { return m_jump.get(); }


public:
	//コンストラクタ
	BossJumpAttackAction(CommonResources* resources,
		BossEnemy* bossEnemy
		, Player* player);
	//デストラクタ
	~BossJumpAttackAction();




private:
	// 共通リソース
	CommonResources* m_commonResources;

	//チャージ
	std::unique_ptr<BossJumpAttackCharge> m_charge;
	//ジャンプ
	std::unique_ptr<BossJumpAttackJump> m_jump;


};
