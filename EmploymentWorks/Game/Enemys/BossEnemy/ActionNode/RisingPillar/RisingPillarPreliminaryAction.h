/*
	@file	RisingPillarPreliminaryAction.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "Game/Interface/IActionState.h"

// 前方宣言
class CommonResources;
class BossEnemy;
class RisingPillarvAction;


namespace mylib
{
	class DebugCamera;
	class GridFloor;
}



class RisingPillarPreliminaryAction : public IActionState
{
public:
	RisingPillarPreliminaryAction(
		RisingPillarvAction* risingPillarvAction,
		BossEnemy* bossEnemy
		);
	//デストラクタ
	~RisingPillarPreliminaryAction() override;
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
	RisingPillarvAction* m_risingPillarvAction;


};
