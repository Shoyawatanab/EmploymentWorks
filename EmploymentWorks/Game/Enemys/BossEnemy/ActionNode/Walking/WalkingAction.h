/*
	@file	WalkingAction.h
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


class WalkingAction : public IAction
{

public:

	static  constexpr float ROTATESPEED = 1.0f;


public:




public:
	WalkingAction(CommonResources* resources,
		CharacterEntity* own
		, CharacterEntity* target);
	//デストラクタ
	~WalkingAction() override ;

	void Initialize() override;

	ActionState Update(const float& elapsedTime)  override ;
	//状態に入った時
	void Enter() override ;
	//状態を抜けた時
	void Exit() override;



private:
	// 共通リソース
	CommonResources* m_commonResources;

	CharacterEntity* m_target;

	CharacterEntity* m_own;
	
	float m_time;
};
