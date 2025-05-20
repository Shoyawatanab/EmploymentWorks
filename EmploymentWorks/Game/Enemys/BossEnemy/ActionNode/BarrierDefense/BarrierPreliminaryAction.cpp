/*
	@file	BarrierPreliminaryAction.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "BarrierPreliminaryAction.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>

#include "Game/Params.h"
#include "Game/Enemys/BossEnemy/BossEnemy.h"
#include "Game/Enemys/BossEnemy/Beam/Beam.h"
#include "Game/Enemys/BossEnemy/ActionNode/BeamAttack/BossBeamAttackAction.h"
#include "Game/Enemys/BossEnemy/ActionNode/BarrierDefense/BarrierDefenseAction.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;




/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
/// <param name="barrierDefenseAction">コントローラー</param>
/// <param name="owner">所有者</param>
BarrierPreliminaryAction::BarrierPreliminaryAction(CommonResources* resources,
	BarrierDefenseAction* barrierDefenseAction,
	CharacterEntity* owner
	)
	:
	m_commonResources{ resources },
	m_time{}
	, m_owner{ owner }
	, m_barrierDefenseAction{ barrierDefenseAction }
{
}



/// <summary>
/// デストラクタ
/// </summary>
BarrierPreliminaryAction::~BarrierPreliminaryAction()
{
	// do nothing.
}

/// <summary>
/// 初期化
/// </summary>
void BarrierPreliminaryAction::Initialize()
{
	
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
/// <returns>終了か継続か</returns>
BarrierPreliminaryAction::ActionState BarrierPreliminaryAction::Update(const float& elapsedTime)
{
	
	if (m_time >= PRELOMINARY_TIME)
	{
		return ActionState::END;

	}



	m_time += elapsedTime;
	return ActionState::RUNNING;

}

/// <summary>
/// 状態に入った時
/// </summary>
void BarrierPreliminaryAction::Enter()
{

	m_time = 0.0f;

	m_owner->ChangeAnimation("Barrier");

}

/// <summary>
/// 状態を抜けた時
/// </summary>
void BarrierPreliminaryAction::Exit()
{



}
