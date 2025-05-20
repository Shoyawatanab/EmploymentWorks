/*
	@file	WalkingActionComtroller.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "Game/Entities/ActionStateController.h"
#include "Game/Enemys/BossEnemy/ActionNode/Walking/WalkingAction.h"
#include "Game/Enemys/BossEnemy/ActionNode/Orientation/OrientationAction.h"

// 前方宣言
class CommonResources;
class CharacterEntity;

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class WalkingActionComtroller : public ActionStateController
{

public:

	static  constexpr float ROTATESPEED = 1.0f;

public:
	//コンストラク
	WalkingActionComtroller(CommonResources* resources,
		CharacterEntity* own
		, CharacterEntity* target);
	//デストラクタ
	~WalkingActionComtroller();

private:
	// 共通リソース
	CommonResources* m_commonResources;
	//ターゲット
	CharacterEntity* m_target;
	//所有者
	CharacterEntity* m_own;
	//歩き状態
	std::unique_ptr<WalkingAction> m_walkingAction;
	//回転状態
	std::unique_ptr<OrientationAction> m_orientation;

};
