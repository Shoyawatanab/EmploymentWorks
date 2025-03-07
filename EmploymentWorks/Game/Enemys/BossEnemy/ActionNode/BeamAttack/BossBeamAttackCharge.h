/*
	@file	BossBeamAttackCharge.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "Game/Interface/IActionState.h"

// 前方宣言
class CommonResources;
class BossEnemy;
class Beam;
class BossBeamAttackAction;


namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class BossBeamAttackCharge : public IActionState
{
public:
	BossBeamAttackCharge(CommonResources* resources
		, BossEnemy* bossEnemy
		, Beam* beam
		, BossBeamAttackAction* beamAttack);


	//デストラクタ
	~BossBeamAttackCharge() override;
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

	float m_time;

	float m_particleCreateTime;


};
