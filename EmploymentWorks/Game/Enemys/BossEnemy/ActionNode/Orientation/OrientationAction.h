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




public:
	OrientationAction(CommonResources* resources,
		BaseEntity* own
		, BaseEntity* target);
	//デストラクタ
	~OrientationAction() override ;

	void Initialize() override;

	ActionState Update(const float& elapsedTime)  override ;
	//状態に入った時
	void Enter() override ;
	//状態を抜けた時
	void Exit() override;



private:
	// 共通リソース
	CommonResources* m_commonResources;

	BaseEntity* m_target;

	BaseEntity* m_own;
};
