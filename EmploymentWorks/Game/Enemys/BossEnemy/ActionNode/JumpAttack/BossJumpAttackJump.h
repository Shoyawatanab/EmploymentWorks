/*
	@file	BossJumpAttackJump.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "Game/Interface/IActione.h"

// 前方宣言
class CommonResources;
class BossEnemy;
class Beam;
class Player;
class BossJumpAttackAction;

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class BossJumpAttackJump : public IAction
{


public:
	//コンストラクタ
	BossJumpAttackJump(CommonResources* resources,
		BossJumpAttackAction* parent
		,BossEnemy* bossEnemy
		, Player* player);
	//デストラクタ
	~BossJumpAttackJump() override ;
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
	BossJumpAttackAction* m_parent;
	//ジャンプ方向
	DirectX::SimpleMath::Vector3 m_jumpDirection;


};
