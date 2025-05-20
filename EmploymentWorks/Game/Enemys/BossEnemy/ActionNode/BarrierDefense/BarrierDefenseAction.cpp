/*
	@file	BarrierDefenseAction.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "BarrierDefenseAction.h"
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
#include "Game/Enemys/BossEnemy/Barrier/Barrier.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;



/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
/// <param name="owner">所有者</param>
/// <param name="barrier"></param>
BarrierDefenseAction::BarrierDefenseAction(CommonResources* resources
	, CharacterEntity* owner
	, Barrier* barrier
	)
	:
	m_commonResources{resources}
	,m_preliminaryAction{}
	,m_deployment{}
	,m_barrier{barrier}
{
	//各行動を作成
	m_preliminaryAction = std::make_unique<BarrierPreliminaryAction>(resources, this, owner);
	m_deployment = std::make_unique<BarrierDeployment>(resources, this,barrier);
	m_close = std::make_unique<BarrierClose>(resources, this, barrier, owner);

	//動作順に追加
	ActionStateController::Initialize({
		m_preliminaryAction.get()
		,m_deployment.get()
		,m_close.get()
		});

}

/// <summary>
/// デストラクタ
/// </summary>
BarrierDefenseAction::~BarrierDefenseAction()
{
	// do nothing.
}


void BarrierDefenseAction::Notify(const Telegram<GameMessageType>& telegram)
{
	UNREFERENCED_PARAMETER(telegram);
	

}






