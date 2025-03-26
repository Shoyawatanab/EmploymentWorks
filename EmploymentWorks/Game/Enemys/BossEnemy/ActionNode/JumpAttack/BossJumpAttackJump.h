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
	BossJumpAttackJump(CommonResources* resources,
		BossJumpAttackAction* parent
		,BossEnemy* bossEnemy
		, Player* player);
	//デストラクタ
	~BossJumpAttackJump() override ;

	void Initialize() override;

	IBehaviorNode::State Update(const float& elapsedTime)  override ;
	//状態に入った時
	void Enter() override ;
	//状態を抜けた時
	void Exit() override;

private:
	// 共通リソース
	CommonResources* m_commonResources;
	BossEnemy* m_bossEnemy;
	Player* m_player;
	BossJumpAttackAction* m_parent;


	DirectX::SimpleMath::Vector3 m_jumpDirection;


};
