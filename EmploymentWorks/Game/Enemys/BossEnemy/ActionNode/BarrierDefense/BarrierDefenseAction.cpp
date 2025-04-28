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
BarrierDefenseAction::BarrierDefenseAction(CommonResources* resources
	,BossEnemy* bossEnemy
	, Barrier* barrier
	)
	:
	m_commonResources{resources}
	,m_currentState{}
	,m_idel{}
	,m_preliminaryAction{}
	,m_deployment{}
	,m_barrier{barrier}
{
	
	m_idel = std::make_unique<BarrierIdel>(resources, this);
	m_preliminaryAction = std::make_unique<BarrierPreliminaryAction>(resources, this,bossEnemy);
	m_deployment = std::make_unique<BarrierDeployment>(resources, this,barrier);
	m_close = std::make_unique<BarrierClose>(resources, this, barrier,bossEnemy);


	m_currentState = m_idel.get();
	m_currentState->Enter();

	//イベントタイプの登録
	Messenger::GetInstance()->Attach(MessageType::BossBeamHit, this);

}

/// <summary>
/// デストラクタ
/// </summary>
BarrierDefenseAction::~BarrierDefenseAction()
{
	// do nothing.
}

void BarrierDefenseAction::Initialize()
{

}

BarrierDefenseAction::ActionState BarrierDefenseAction::Update(const float& elapsedTime)
{

	

	return	m_currentState->Update(elapsedTime);

}

void BarrierDefenseAction::Enter()
{
	ChangeState(m_idel.get());
}

void BarrierDefenseAction::Exit()
{
}

void BarrierDefenseAction::Notify(const Telegram& telegram)
{
	UNREFERENCED_PARAMETER(telegram);
	

}



/// <summary>
/// ステートの切り替え
/// </summary>
/// <param name="nextState">次のステート</param>
void BarrierDefenseAction::ChangeState(IAction* nextState)
{

	m_currentState->Exit();
	m_currentState = nextState;
	m_currentState->Enter();

}


