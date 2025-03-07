/*
	@file	BossBeamAttackShot.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "Game/Interface/IActionState.h"

// 前方宣言
class CommonResources;
class BossEnemy;
class Beam;
class BossBeamAttackAction;
class Player;

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class BossBeamAttackShot : public IActionState
{
public:
	BossBeamAttackShot(CommonResources* resources
		, BossEnemy* bossEnemy
		, Beam* beam
		, BossBeamAttackAction* beamAttack
		, Player* player);

	//継承関係
	//デストラクタ
	~BossBeamAttackShot() override;
	//初期化
	void Initialize(CommonResources* resources);
	// 更新する
	IBehaviorNode::State Update(const float& elapsedTime);
	//状態に入った時
	void Enter();
	//状態を抜けた時
	void Exit();
private:
	// 共通リソース
	CommonResources* m_commonResources;
	BossEnemy* m_bossEnemy;
	Beam* m_beam;
	BossBeamAttackAction* m_beamAttack;
	Player* m_player;

};
