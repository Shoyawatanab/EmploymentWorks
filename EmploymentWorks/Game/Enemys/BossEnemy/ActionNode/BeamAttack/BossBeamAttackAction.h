/*
	@file	BossBeamAttackAction.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "Game/Entities/ActionStateController.h"
#include "Game/Interface/IObserver.h"


// 前方宣言
class CommonResources;
class CharacterEntity;
class Beam;
class BossBeamAttackPreliminaryAction;
class BossBeamAttackCharge;
class BossBeamAttackShot;
class BossBeamAttackEnd;

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class BossBeamAttackAction : public ActionStateController, IObserver<GameMessageType>
{

public:

public:
	BossBeamAttackAction(CommonResources* resources,
		CharacterEntity* bossEnemy
		, Beam* beam
		, CharacterEntity* player);
	//デストラクタ
	~BossBeamAttackAction() ;

	//IObserver
//通知時に呼ばれる関数
	void Notify(const Telegram<GameMessageType>& telegram)  override;



private:
	// 共通リソース
	CommonResources* m_commonResources;

	std::unique_ptr<BossBeamAttackPreliminaryAction> m_preliminaryAction;

	std::unique_ptr<BossBeamAttackCharge> m_charge;

	std::unique_ptr<BossBeamAttackShot> m_shot;

	std::unique_ptr<BossBeamAttackEnd> m_attackEnd;

};
