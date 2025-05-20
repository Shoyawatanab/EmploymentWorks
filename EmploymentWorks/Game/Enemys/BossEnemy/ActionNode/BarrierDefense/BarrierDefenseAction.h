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
class CharacterEntity;
class Barrier;

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}



class BarrierDefenseAction : public ActionStateController , IObserver<GameMessageType>
{
public:
	//コンストラクタ
	BarrierDefenseAction(CommonResources* resources,
		CharacterEntity* owner
		,Barrier* barrier
	);

	//デストラクタ
	~BarrierDefenseAction() ;





	//通知時に呼ばれる関数
	void Notify(const Telegram<GameMessageType>& telegram)  override;



private:
	// 共通リソース
	CommonResources* m_commonResources;
	//予備動作
	std::unique_ptr<BarrierPreliminaryAction> m_preliminaryAction;
	//バリア展開
	std::unique_ptr<BarrierDeployment> m_deployment;
	//バリはをしまう
	std::unique_ptr<BarrierClose> m_close;
	//バリア
	Barrier* m_barrier;

};
