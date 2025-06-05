/*
	@file	BossBeamAttackAction.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "BossBeamAttackAction.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>

#include "Game/Params.h"
#include "Game/Observer/Messenger.h"

#include "Game/Enemies/BossEnemy/BossEnemy.h"
#include "Game/Enemys/BossEnemy/Beam/Beam.h"
#include "Game/Enemys/BossEnemy/ActionNode/BeamAttack/BossBeamAttackPreliminaryAction.h"
#include "Game/Enemys/BossEnemy/ActionNode/BeamAttack/BossBeamAttackCharge.h"
#include "Game/Enemys/BossEnemy/ActionNode/BeamAttack/BossBeamAttackShot.h"
#include "Game/Enemys/BossEnemy/ActionNode/BeamAttack/BossBeamAttackEnd.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
BossBeamAttackAction::BossBeamAttackAction(CommonResources* resources
	, CharacterEntity* bossenemy
	,Beam* beam
	, CharacterEntity* player)
	:
	m_commonResources{resources}
	,m_preliminaryAction{}
	,m_charge{}
	,m_shot{}
	,m_attackEnd{}
{
	//各状態の生成
	m_preliminaryAction = std::make_unique<BossBeamAttackPreliminaryAction>(m_commonResources,bossenemy,beam,this);
	m_charge = std::make_unique<BossBeamAttackCharge>(m_commonResources, bossenemy, beam,this);
	m_shot = std::make_unique<BossBeamAttackShot>(m_commonResources, bossenemy, beam,this,player);
	m_attackEnd = std::make_unique<BossBeamAttackEnd>(m_commonResources, bossenemy, beam,this);


	//イベントタイプの登録
	Messenger::GetInstance()->Rigister(GamePlayMessageType::BOSS_BEAM_HIT, this);

	//行動順に追加
	ActionStateController::Initialize({
		m_preliminaryAction.get()
		,m_charge.get()
		,m_shot.get()
		,m_attackEnd.get()
		}
	);

}

/// <summary>
/// デストラクタ
/// </summary>
BossBeamAttackAction::~BossBeamAttackAction()
{
	// do nothing.
	ActionStateController::~ActionStateController();
}

/// <summary>
/// 通知を受け取る関数
/// </summary>
/// <param name="telegram">情報</param>
void BossBeamAttackAction::Notify(const Telegram<GamePlayMessageType>& telegram)
{
	
	switch (telegram.messageType)
	{
		case GamePlayMessageType::BOSS_BEAM_HIT:

			ActionStateController::ChangeState();
			break;
		default:
			break;
	}

}



