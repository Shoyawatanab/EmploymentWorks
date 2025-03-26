/*
	@file	BarrierDefenseAction.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "Game/Interface/IActione.h"
#include"Game/Interface/IActionState.h"
#include "Game/Interface/IObserver.h"

#include "Game/Enemys/BossEnemy/ActionNode/BarrierDefense/BarrierIdel.h"
#include "Game/Enemys/BossEnemy/ActionNode/BarrierDefense/BarrierPreliminaryAction.h"
#include "Game/Enemys/BossEnemy/ActionNode/BarrierDefense/BarrierDeployment.h"
#include "Game/Enemys/BossEnemy/ActionNode/BarrierDefense/BarrierClose.h"



// 前方宣言
class CommonResources;
class BossEnemy;
class Barrier;

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class BarrierDefenseAction : public IAction , IObserver
{

public:

	IActionState* GetCurrentState() { return m_currentState; }

	BarrierIdel* GetBarrierIdel() { return m_idel.get(); }

	BarrierPreliminaryAction* GetBarrierPreliminaryAction() { return m_preliminaryAction.get(); }

	BarrierDeployment* GetBarrierDeployment() { return m_deployment.get(); }

	BarrierClose* GetBarrierClose() { return m_close.get(); }


public:
	BarrierDefenseAction(CommonResources* resources,
		BossEnemy* bossEnemy
		,Barrier* barrier
);
	//デストラクタ
	~BarrierDefenseAction() override ;

	void Initialize() override;

	IBehaviorNode::State Update(const float& elapsedTime)  override ;
	//状態に入った時
	void Enter() override;
	//状態を抜けた時
	void Exit() override;


	//IObserver
//通知時に呼ばれる関数
	void Notify(EventParams::EventType type, void* datas)  override;

	//状態の変更
	void ChangeState(IActionState* nextState);


private:
	// 共通リソース
	CommonResources* m_commonResources;

	IActionState* m_currentState;
	std::unique_ptr<BarrierIdel> m_idel;
	std::unique_ptr<BarrierPreliminaryAction> m_preliminaryAction;
	std::unique_ptr<BarrierDeployment> m_deployment;

	std::unique_ptr<BarrierClose> m_close;

	Barrier* m_barrier;

};
