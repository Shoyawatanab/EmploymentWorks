/*
	@file	BossRushAttackCharge.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "Game/Interface/IActione.h"

// 前方宣言
class CommonResources;
class BossEnemy;
class Beam;
class Player;
class BossRushAttackAction;

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class BossRushAttackCharge : public IAction
{
public:
	//チャージ時間
	static constexpr float CHARGE_TIME = 1.5f;
	//エフェクトの大きさ
	static constexpr DirectX::SimpleMath::Vector3 EFFECTE_SCALE{ 5.0f, 5.0f, 5.0f };


public:
	//コンストラクタ
	BossRushAttackCharge(CommonResources* resources,
		BossRushAttackAction* parent
		,BossEnemy* bossEnemy
		, Player* player);
	//デストラクタ
	~BossRushAttackCharge() override ;
	//初期化
	void Initialize() override;
	//更新処理
	ActionState Update(const float& elapsedTime)  override ;
	//状態に入った時
	void Enter() override ;
	//状態を抜けた時
	void Exit() override;



private:
	// 共通リソース
	CommonResources* m_commonResources;
	//所有者
	BossEnemy* m_bossEnemy;
	//プレイヤ
	Player* m_player;
	//時間
	float m_time;
	//コントローラー
	BossRushAttackAction* m_parent;


};
