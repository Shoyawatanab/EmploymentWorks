/*
	@file	IdleingAction.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "Game/Interface/IActione.h"

// 前方宣言
class CommonResources;
class CharacterEntity;

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class IdleingAction : public IAction
{

public:



public:
	//コンストラクタ
	IdleingAction(CommonResources* resources,
		CharacterEntity* own
		);
	//デストラクタ
	~IdleingAction() override ;
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
	CharacterEntity* m_own;
	//時間
	float m_time;
};
