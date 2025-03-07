/*
	@file	RisingPillarvAction.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "RisingPillarvAction.h"
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


using namespace DirectX;
using namespace DirectX::SimpleMath;



/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
RisingPillarvAction::RisingPillarvAction(CommonResources* resources
	,BossEnemy* bossenemy
	, Player* player
	, StageObjectManager* stageObjectManger)
	:
	m_commonResources{resources}
	,m_currentState{}
	,m_idle{}
	,m_rise{}
	,m_preliminaryAction{}
	,m_pillars{}
{

	m_idle = std::make_unique<RisingPillarIdel>(this);
	m_rise = std::make_unique<RisingPillarRise>(this,stageObjectManger);
	m_preliminaryAction = std::make_unique<RisingPillarPreliminaryAction>(this,bossenemy);

}

/// <summary>
/// デストラクタ
/// </summary>
RisingPillarvAction::~RisingPillarvAction()
{
	// do nothing.
}

void RisingPillarvAction::Initialize()
{

	m_idle->Initialize(m_commonResources);
	m_rise->Initialize(m_commonResources);
	m_preliminaryAction->Initialize(m_commonResources);

	m_currentState = m_idle.get();
	m_currentState->Enter();


}

IBehaviorNode::State RisingPillarvAction::Update(float elapsdTime)
{

	

	return m_currentState->Update(elapsdTime);

}





/// <summary>
/// ステートの切り替え
/// </summary>
/// <param name="nextState">次のステート</param>
void RisingPillarvAction::ChangeState(IActionState* nextState)
{

	m_currentState->Exit();
	m_currentState = nextState;
	m_currentState->Enter();

}


