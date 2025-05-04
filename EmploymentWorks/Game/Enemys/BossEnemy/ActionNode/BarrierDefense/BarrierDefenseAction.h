/*
	@file	BarrierDefenseAction.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "Game/Entities/ActionStateController.h"
#include "Game/Interface/IObserver.h"

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


class BarrierDefenseAction : public ActionStateController , IObserver
{

public:



	BarrierPreliminaryAction* GetBarrierPreliminaryAction() { return m_preliminaryAction.get(); }

	BarrierDeployment* GetBarrierDeployment() { return m_deployment.get(); }

	BarrierClose* GetBarrierClose() { return m_close.get(); }


public:
	BarrierDefenseAction(CommonResources* resources,
		BossEnemy* bossEnemy
		,Barrier* barrier
);
	//デストラクタ
	~BarrierDefenseAction() ;




	//IObserver
//通知時に呼ばれる関数
	void Notify(const Telegram& telegram)  override;



private:
	// 共通リソース
	CommonResources* m_commonResources;

	std::unique_ptr<BarrierPreliminaryAction> m_preliminaryAction;
	std::unique_ptr<BarrierDeployment> m_deployment;

	std::unique_ptr<BarrierClose> m_close;

	Barrier* m_barrier;

};
