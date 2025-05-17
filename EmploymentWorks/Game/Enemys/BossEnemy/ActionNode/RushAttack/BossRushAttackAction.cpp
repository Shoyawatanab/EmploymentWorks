/*
	@file	BossRushAttackAction.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "BossRushAttackAction.h"
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

#include "Game/Enemys/BossEnemy/BossEnemy.h"
#include "Game/Enemys/BossEnemy/Beam/Beam.h"
#include "BossRushAttackAction.h"
using namespace DirectX;
using namespace DirectX::SimpleMath;



/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
BossRushAttackAction::BossRushAttackAction(CommonResources* resources
	,BossEnemy* bossenemy
	, Player* player)
	:
	ActionStateController{}
	,m_commonResources{resources}
{



	m_charge = std::make_unique<BossRushAttackCharge>(resources,this,bossenemy,player);
	m_rush = std::make_unique<BossRushAttackRush>(resources, this, bossenemy, player);


	//イベントタイプの登録
	Messenger::GetInstance()->Rigister(GameMessageType::BossBeamHit, this);

	ActionStateController::Initialize({
		m_charge.get()
		,m_rush.get()
	});

}

/// <summary>
/// デストラクタ
/// </summary>
BossRushAttackAction::~BossRushAttackAction()
{
	// do nothing.
}

void BossRushAttackAction::Notify(const Telegram<GameMessageType>& telegram)
{
	
	switch (telegram.messageType)
	{
		case GameMessageType::BossBeamHit:
			break;
		default:
			break;
	}

}


