/*
	@file	BossJumpAttackAction.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "BossJumpAttackAction.h"
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
#include "BossJumpAttackAction.h"




/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
BossJumpAttackAction::BossJumpAttackAction(CommonResources* resources
	,BossEnemy* bossenemy
	, Player* player)
	:
	ActionStateController{},
	m_commonResources{resources}
{


	//各状態を作成
	m_charge = std::make_unique<BossJumpAttackCharge>(resources,this,bossenemy,player);
	m_jump = std::make_unique<BossJumpAttackJump>(resources, this, bossenemy, player);


	//m_currentState->Enter();


	//動作順に追加
	ActionStateController::Initialize({
		m_charge.get(),
		m_jump.get()
		});


}

/// <summary>
/// デストラクタ
/// </summary>
BossJumpAttackAction::~BossJumpAttackAction()
{
	// do nothing.
}






