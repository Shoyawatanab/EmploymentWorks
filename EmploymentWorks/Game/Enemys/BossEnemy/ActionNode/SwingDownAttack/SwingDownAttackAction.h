/*
	@file	SwingDownAttackAction.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "Game/Entities/ActionStateController.h"
#include "Game/Interface/IObserver.h"
#include "Game/Enemys/BossEnemy/ActionNode/SwingDownAttack/SwingDownAttackRaisePhase.h"
#include "Game/Enemys/BossEnemy/ActionNode/SwingDownAttack/SwingDownAttackSwingPhase.h"


// 前方宣言
class CommonResources;
class CharacterEntity;
class Beam;
class Player;

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class SwingDownAttackAction : public ActionStateController , IObserver<GameMessageType>
{

public:

	static  constexpr float JUMPPOWER = 0.3f;

	static  constexpr float MOVESPEED = 9.0f;

public:




public:
	SwingDownAttackAction(CommonResources* resources,
		CharacterEntity* owner
		);

	//デストラクタ
	~SwingDownAttackAction();


	//IObserver
//通知時に呼ばれる関数
	void Notify(const Telegram<GameMessageType>& telegram)  override;


private:
	// 共通リソース
	CommonResources* m_commonResources;

	//振り上げ
	std::unique_ptr<SwingDownAttackRaisePhase> m_raisePhase;
	//振り下ろし
	std::unique_ptr<SwingDownAttackSwingPhase> m_swingPhase;

};
