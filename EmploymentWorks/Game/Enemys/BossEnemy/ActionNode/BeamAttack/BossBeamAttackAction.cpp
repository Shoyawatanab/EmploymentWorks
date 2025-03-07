/*
	@file	BossBeamAttackAction.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "BossBeamAttackAction.h"
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
BossBeamAttackAction::BossBeamAttackAction(CommonResources* resources
	,BossEnemy* bossenemy
	,Beam* beam
	, Player* player)
	:
	m_commonResources{resources}
	,m_currentState{}
	,m_preliminaryAction{}
	,m_charge{}
	,m_shot{}
	,m_attackEnd{}
{
	m_preliminaryAction = std::make_unique<BossBeamAttackPreliminaryAction>(m_commonResources,bossenemy,beam,this);
	m_charge = std::make_unique<BossBeamAttackCharge>(m_commonResources, bossenemy, beam,this);
	m_shot = std::make_unique<BossBeamAttackShot>(m_commonResources, bossenemy, beam,this,player);
	m_attackEnd = std::make_unique<BossBeamAttackEnd>(m_commonResources, bossenemy, beam,this);
	m_idel = std::make_unique<BossBeamAttackIdel>(m_commonResources, bossenemy, beam,this);

}

/// <summary>
/// デストラクタ
/// </summary>
BossBeamAttackAction::~BossBeamAttackAction()
{
	// do nothing.
}

void BossBeamAttackAction::Initialize()
{

	m_currentState = m_idel.get();
	m_currentState->Enter();

	//イベントタイプの登録
	Messenger::Attach(EventParams::EventType::BossBeamHit, this);

}

IBehaviorNode::State BossBeamAttackAction::Update(float elapsdTime)
{

	

	return m_currentState->Update(elapsdTime);

}

void BossBeamAttackAction::Notify(EventParams::EventType type, void* datas)
{

	switch (type)
	{
		case EventParams::EventType::BossBeamHit:
			if (m_currentState != m_attackEnd.get())
			{
				ChangeState(m_attackEnd.get());
			}
			break;
		default:
			break;
	}

}



/// <summary>
/// ステートの切り替え
/// </summary>
/// <param name="nextState">次のステート</param>
void BossBeamAttackAction::ChangeState(IActionState* nextState)
{

	m_currentState->Exit();
	m_currentState = nextState;
	m_currentState->Enter();

}


