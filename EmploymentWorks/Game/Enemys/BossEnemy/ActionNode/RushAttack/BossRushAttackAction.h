/*
	@file	BossRushAttackAction.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "Game/Entities/ActionStateController.h"
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


class BossRushAttackAction : public ActionStateController
{


public:
	//コンストラクタ
	BossRushAttackAction(CommonResources* resources,
		BossEnemy* bossEnemy
		, Player* player);
	//デストラクタ
	~BossRushAttackAction() ;





private:
	// 共通リソース
	CommonResources* m_commonResources;
	//チャージ
	std::unique_ptr<BossRushAttackCharge> m_charge;
	//ラッシュ
	std::unique_ptr<BossRushAttackRush> m_rush;

};
