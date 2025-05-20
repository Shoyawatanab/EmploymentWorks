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




/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
/// <param name="bossenemy">所有者</param>
/// <param name="player">プレイヤ</param>
BossRushAttackAction::BossRushAttackAction(CommonResources* resources
	,BossEnemy* bossenemy
	, Player* player)
	:
	ActionStateController{}
	,m_commonResources{resources}
{


	//各状態を作成
	m_charge = std::make_unique<BossRushAttackCharge>(resources,this,bossenemy,player);
	m_rush = std::make_unique<BossRushAttackRush>(resources, this, bossenemy, player);



	//動作順に追加
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




