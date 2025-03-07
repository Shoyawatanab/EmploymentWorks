/*
	@file	RisingPillarvAction.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "Game/Interface/IActione.h"
#include"Game/Interface/IActionState.h"

#include "Game/Enemys/BossEnemy/ActionNode/RisingPillar/RisingPillarIdel.h"
#include "Game/Enemys/BossEnemy/ActionNode/RisingPillar/RisingPillarRise.h"
#include "Game/Enemys/BossEnemy/ActionNode/RisingPillar/RisingPillarPreliminaryAction.h"


// 前方宣言
class CommonResources;
class BossEnemy;
class Player;
class Pillar;
class StageObjectManager;

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class RisingPillarvAction : public IAction
{

public:


	IActionState* GetCurrentState() { return m_currentState; }

	//状態の変更
	void ChangeState(IActionState* nextState);

	RisingPillarIdel* GetPillarIdel() { return m_idle.get(); }

	RisingPillarRise* GetPillarRise() { return m_rise.get(); }

	RisingPillarPreliminaryAction* GetPillarpreliminaryAction() { return m_preliminaryAction.get(); }

public:
	RisingPillarvAction(CommonResources* resources,
		BossEnemy* bossEnemy
		, Player* player
		, StageObjectManager* stageObjectManger);

	//デストラクタ
	~RisingPillarvAction() override ;

	void Initialize() override;

	IBehaviorNode::State Update(float elapsdTime)  override ;




private:
	// 共通リソース
	CommonResources* m_commonResources;

	IActionState* m_currentState;


	//通常状態
	std::unique_ptr<RisingPillarIdel> m_idle;
	//上昇
	std::unique_ptr<RisingPillarRise> m_rise;
	//予備動作
	std::unique_ptr<RisingPillarPreliminaryAction> m_preliminaryAction;

	std::vector<Pillar*> m_pillars;

};
