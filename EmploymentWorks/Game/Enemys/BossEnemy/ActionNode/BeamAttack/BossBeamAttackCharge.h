/*
	@file	BossBeamAttackCharge.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "Game/Interface/IActione.h"

// 前方宣言
class CommonResources;
class CharacterEntity;
class Beam;
class BossBeamAttackAction;


namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class BossBeamAttackCharge : public IAction
{
public:
	//コンストラクタ
	BossBeamAttackCharge(CommonResources* resources
		, CharacterEntity* bossEnemy
		, Beam* beam
		, BossBeamAttackAction* beamAttack);


	//デストラクタ
	~BossBeamAttackCharge() override;
	//初期化
	void Initialize() override;
	// 更新処理
	ActionState Update(const float& elapsedTime) override;

	//状態に入った時
	void Enter() override;
	//状態を抜けた時
	void Exit() override;
private:
	// 共通リソース
	CommonResources* m_commonResources;
	//ボステキ
	CharacterEntity* m_bossEnemy;
	//ビーム
	Beam* m_beam;
	//時間
	float m_time;
	//パーティクル生成時間
	float m_particleCreateTime;


};
