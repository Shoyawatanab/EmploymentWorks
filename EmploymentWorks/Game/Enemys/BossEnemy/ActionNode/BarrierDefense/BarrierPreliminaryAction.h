/*
	@file	BarrierPreliminaryAction.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "Game/Interface/IActionState.h"

// 前方宣言
class CommonResources;
class BossEnemy;
class BarrierDefenseAction;


namespace mylib
{
	class DebugCamera;
	class GridFloor;
}



class BarrierPreliminaryAction : public IActionState
{
public:
	BarrierPreliminaryAction(
		BarrierDefenseAction* barrierDefenseAction,
		BossEnemy* bossEnemy
		);


	//デストラクタ
	~BarrierPreliminaryAction() override;
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

	//経過時間
	float m_time;

	BossEnemy* m_bossEnemy;
	BarrierDefenseAction* m_barrierDefenseAction;


};
