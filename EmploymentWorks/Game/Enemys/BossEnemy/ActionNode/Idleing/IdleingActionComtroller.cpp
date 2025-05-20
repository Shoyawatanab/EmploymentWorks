/*
	@file	IdleingActionComtroller.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "IdleingActionComtroller.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>

#include "IdleingActionComtroller.h"
#include "Game/Entities/CharacterEntity.h"




/// <summary>
/// コンストラク
/// </summary>
/// <param name="resources">共通リソース</param>
/// <param name="own">所有者</param>
/// <param name="target">ターゲット</param>
IdleingActionComtroller::IdleingActionComtroller(CommonResources* resources
	, CharacterEntity* own
	)
	:
	m_commonResources{resources}
	,m_own{own}
{

	m_idle = std::make_unique<IdleingAction>(m_commonResources,m_own);

	//動作順に追加
	ActionStateController::Initialize({ 
		m_idle.get()
		});

}

/// <summary>
/// デストラクタ
/// </summary>
IdleingActionComtroller::~IdleingActionComtroller()
{
	// do nothing.
}


