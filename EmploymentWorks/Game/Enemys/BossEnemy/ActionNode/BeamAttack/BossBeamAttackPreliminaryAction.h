/*
	@file	BossBeamAttackPreliminaryAction.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "Game/Interface/IActione.h"

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



class BossBeamAttackPreliminaryAction : public IAction
{
public:
	BossBeamAttackPreliminaryAction(CommonResources* resources
		,BossEnemy* bossEnemy
		,Beam* beam
		, BossBeamAttackAction* beamAttack);

	//継承関係
		//デストラクタ
	~BossBeamAttackPreliminaryAction() override;
	//初期化
	void Initialize() override;
	// 更新する
	ActionState Update(const float& elapsedTime) override;
	//状態に入った時
	void Enter() override;
	//状態を抜けた時
	void Exit() override ;
private:
	// 共通リソース
	CommonResources* m_commonResources;

	//経過時間
	float m_time;

	BossEnemy* m_bossEnemy;
	Beam* m_beam;
	BossBeamAttackAction* m_beamAttack;


};
