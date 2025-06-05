/*
	@file	WalkingActionComtroller.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "WalkingActionComtroller.h"
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

#include "WalkingActionComtroller.h"
#include "Game/Entities/CharacterEntity.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;



/// <summary>
/// コンストラク
/// </summary>
/// <param name="resources">共通リソース</param>
/// <param name="own">所有者</param>
/// <param name="target">ターゲット</param>
WalkingActionComtroller::WalkingActionComtroller(CommonResources* resources
	, CharacterEntity* own
	, CharacterEntity* target)
	:
	m_commonResources{resources}
	,m_own{own}
	,m_target{target}
{
	//各状態の作成
	m_walkingAction = std::make_unique<WalkingAction>(m_commonResources,m_own,m_target);
	//m_orientation = std::make_unique<OrientationAction>(m_commonResources, m_own, m_target);

	//動作順に追加
	ActionStateController::Initialize({ 
		m_walkingAction.get() 
		});

}

/// <summary>
/// デストラクタ
/// </summary>
WalkingActionComtroller::~WalkingActionComtroller()
{
	// do nothing.
}


