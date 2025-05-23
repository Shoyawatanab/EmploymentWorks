/*
	@file	OrientationAction.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "Game/Interface/IActione.h"

// 前方宣言
class CommonResources;
class BaseEntity;

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class OrientationAction : public IAction
{

public:

	static  constexpr float ROTATESPEED = 1.0f;


public:
	//コンストラクタ
	OrientationAction(CommonResources* resources,
		BaseEntity* own
		, BaseEntity* target);
	//デストラクタ
	~OrientationAction() override ;
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
	//ターゲット
	BaseEntity* m_target;
	//所有者
	BaseEntity* m_own;
};
