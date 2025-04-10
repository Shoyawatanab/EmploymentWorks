/*
	@file	BossRushAttackAction.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "BossRushAttackAction.h"
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
#include "BossRushAttackAction.h"
using namespace DirectX;
using namespace DirectX::SimpleMath;



/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
BossRushAttackAction::BossRushAttackAction(CommonResources* resources
	,BossEnemy* bossenemy
	, Player* player)
	:
	m_commonResources{resources}
	,m_currentState{}
{


	m_charge = std::make_unique<BossRushAttackCharge>(resources,this,bossenemy,player);
	m_rush = std::make_unique<BossRushAttackRush>(resources, this, bossenemy, player);

}

/// <summary>
/// デストラクタ
/// </summary>
BossRushAttackAction::~BossRushAttackAction()
{
	// do nothing.
}

void BossRushAttackAction::Initialize()
{
	m_currentState = m_charge.get();
	//m_currentState->Enter();

	//イベントタイプの登録
	Messenger::Attach(EventParams::EventType::BossBeamHit, this);

}

IBehaviorNode::State BossRushAttackAction::Update(const float& elapsedTime)
{

	

	return m_currentState->Update(elapsedTime);

}

void BossRushAttackAction::Notify(EventParams::EventType type, void* datas)
{

	switch (type)
	{
		case EventParams::EventType::BossBeamHit:
			break;
		default:
			break;
	}

}



/// <summary>
/// ステートの切り替え
/// </summary>
/// <param name="nextState">次のステート</param>
void BossRushAttackAction::ChangeState(IAction* nextState)
{

	m_currentState->Exit();
	m_currentState = nextState;
	m_currentState->Enter();

}

void BossRushAttackAction::Enter()
{

	ChangeState(m_charge.get());

}

void BossRushAttackAction::Exit()
{
	ChangeState(m_charge.get());
}
