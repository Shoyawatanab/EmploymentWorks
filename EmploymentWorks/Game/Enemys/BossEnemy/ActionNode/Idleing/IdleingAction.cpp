/*
	@file	IdleingAction.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "IdleingAction.h"
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

#include "IdleingAction.h"
#include "Game/Entities/CharacterEntity.h"




/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
/// <param name="own">所有者</param>
/// <param name="target">ターゲット</param>
IdleingAction::IdleingAction(CommonResources* resources
	, CharacterEntity* own
	)
	:
	m_commonResources{resources}
	,m_own{own}
	,m_time{}
{



}

/// <summary>
/// デストラクタ
/// </summary>
IdleingAction::~IdleingAction()
{
	// do nothing.
}

/// <summary>
/// 初期化
/// </summary>
void IdleingAction::Initialize()
{

}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
/// <returns>継続か終了か</returns>
IdleingAction:: ActionState IdleingAction::Update(const float& elapsedTime)
{

	return ActionState::END;

}


/// <summary>
/// 状態に入った時
/// </summary>
void IdleingAction::Enter()
{

	m_own->ChangeAnimation("Idel");

	m_time = 0;
}

/// <summary>
/// 状態を抜けた時
/// </summary>
void IdleingAction::Exit()
{
}
