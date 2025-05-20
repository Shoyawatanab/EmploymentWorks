/*
	@file	BarrierPreliminaryAction.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "Game/Interface/IActione.h"

// 前方宣言
class CommonResources;
class CharacterEntity;
class BarrierDefenseAction;


namespace mylib
{
	class DebugCamera;
	class GridFloor;
}



class BarrierPreliminaryAction : public IAction
{
public:
	//動作時間
	static constexpr float  PRELOMINARY_TIME = 2.0f;

public:
	//コンストラクタ
	BarrierPreliminaryAction(CommonResources* resources,
		BarrierDefenseAction* barrierDefenseAction,
		CharacterEntity* owner
		);

	//デストラクタ
	~BarrierPreliminaryAction() override;
	//初期化
	void Initialize() override;
	// 更新する
	ActionState Update(const float& elapsedTime) override;
	//状態に入った時
	void Enter() override;
	//状態を抜けた時
	void Exit() override;
private:
	// 共通リソース
	CommonResources* m_commonResources;

	//経過時間
	float m_time;
	//所有者
	CharacterEntity* m_owner;
	//コントローラー
	BarrierDefenseAction* m_barrierDefenseAction;


};
