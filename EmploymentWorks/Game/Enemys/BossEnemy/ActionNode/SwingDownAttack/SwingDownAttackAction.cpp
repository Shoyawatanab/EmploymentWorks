/*
	@file	SwingDownAttackAction.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "SwingDownAttackAction.h"
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

using namespace DirectX;
using namespace DirectX::SimpleMath;



/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
SwingDownAttackAction::SwingDownAttackAction(CommonResources* resources
	, CharacterEntity* owner
	)
	:
	ActionStateController{},
	m_commonResources{resources}
{

	m_raisePhase = std::make_unique<SwingDownAttackRaisePhase>(m_commonResources,this, owner);

	m_swingPhase = std::make_unique<SwingDownAttackSwingPhase>(m_commonResources, this, owner);


	//m_currentState->Enter();

	//イベントタイプの登録
	Messenger::GetInstance()->Rigister(GameMessageType::BossBeamHit, this);

	
	ActionStateController::Initialize({
		m_raisePhase.get()
		,m_swingPhase.get()
		});


}

/// <summary>
/// デストラクタ
/// </summary>
SwingDownAttackAction::~SwingDownAttackAction()
{
	// do nothing.
}


void SwingDownAttackAction::Notify(const Telegram<GameMessageType>& telegram)
{
	
	switch (telegram.messageType)
	{
		case GameMessageType::BossBeamHit:
			break;
		default:
			break;
	}

}




