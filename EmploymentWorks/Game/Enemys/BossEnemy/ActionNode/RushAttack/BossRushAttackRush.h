/*
	@file	BossRushAttackRush.h
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


class BossRushAttackRush : public IAction
{


public:
	//コンストラクタ
	BossRushAttackRush(CommonResources* resources,
		BossRushAttackAction* parent
		,BossEnemy* bossEnemy
		, Player* player);
	//デストラクタ
	~BossRushAttackRush() override ;
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
	//コントローラー
	BossRushAttackAction* m_parent;
	//
	DirectX::SimpleMath::Vector3 m_rushDirection;


};
