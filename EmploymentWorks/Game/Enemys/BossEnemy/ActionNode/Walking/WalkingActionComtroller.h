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




public:
	WalkingActionComtroller(CommonResources* resources,
		CharacterEntity* own
		, CharacterEntity* target);
	//デストラクタ
	~WalkingActionComtroller();



private:
	// 共通リソース
	CommonResources* m_commonResources;

	CharacterEntity* m_target;

	CharacterEntity* m_own;

	std::unique_ptr<WalkingAction> m_walkingAction;

	std::unique_ptr<OrientationAction> m_orientation;

};
