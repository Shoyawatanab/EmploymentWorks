/*
	@file	SwingDownAttackSwingPhase.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "Game/Interface/IActione.h"

// 前方宣言
class CommonResources;
class CharacterEntity;
class ActionStateController;

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class SwingDownAttackSwingPhase : public IAction
{
public:
	//振り下ろし時間
	static constexpr float SWING_TIME = 3.0f;


public:
	//コンストラクタ
	SwingDownAttackSwingPhase(CommonResources* resources,
		ActionStateController* controller
		, CharacterEntity* owner
		);
	//デストラクタ
	~SwingDownAttackSwingPhase() override ;
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
	CharacterEntity* m_owner;
	//コントローラー
	ActionStateController* m_controller;


	float m_time;
	

};
