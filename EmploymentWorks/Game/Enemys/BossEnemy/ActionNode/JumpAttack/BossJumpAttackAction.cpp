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
using namespace DirectX;
using namespace DirectX::SimpleMath;



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



	m_charge = std::make_unique<BossJumpAttackCharge>(resources,this,bossenemy,player);
	m_jump = std::make_unique<BossJumpAttackJump>(resources, this, bossenemy, player);


	//m_currentState->Enter();

	//イベントタイプの登録
	Messenger::GetInstance()->Attach(MessageType::BossBeamHit, this);

	
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


void BossJumpAttackAction::Notify(const Telegram& telegram)
{
	
	switch (telegram.messageType)
	{
		case MessageType::BossBeamHit:
			break;
		default:
			break;
	}

}




