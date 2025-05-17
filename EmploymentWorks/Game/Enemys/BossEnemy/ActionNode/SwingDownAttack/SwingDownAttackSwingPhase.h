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
	SwingDownAttackSwingPhase(CommonResources* resources,
		ActionStateController* controller
		, CharacterEntity* owner
		);
	//デストラクタ
	~SwingDownAttackSwingPhase() override ;

	void Initialize() override;

	ActionState Update(const float& elapsedTime)  override ;
	//状態に入った時
	void Enter() override ;
	//状態を抜けた時
	void Exit() override;

private:
	// 共通リソース
	CommonResources* m_commonResources;
	CharacterEntity* m_owner;
	ActionStateController* m_controller;


	float m_time;
	

};
