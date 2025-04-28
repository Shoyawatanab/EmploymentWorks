/*
	@file	BarrierPreliminaryAction.cpp
	@brief	�v���C�V�[���N���X
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
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
BarrierPreliminaryAction::BarrierPreliminaryAction(CommonResources* resources,
	BarrierDefenseAction* barrierDefenseAction,
	BossEnemy* bossEnemy
	)
	:
	m_commonResources{ resources },
	m_time{}
	, m_bossEnemy{ bossEnemy }
	, m_barrierDefenseAction{ barrierDefenseAction }
{
}



/// <summary>
/// �f�X�g���N�^
/// </summary>
BarrierPreliminaryAction::~BarrierPreliminaryAction()
{
	// do nothing.
}

void BarrierPreliminaryAction::Initialize()
{
	
}

BarrierPreliminaryAction::ActionState BarrierPreliminaryAction::Update(const float& elapsedTime)
{
	
	if (m_time >= 2.0f)
	{
		m_barrierDefenseAction->ChangeState(m_barrierDefenseAction->GetBarrierDeployment());
	}



	m_time += elapsedTime;
	return ActionState::Running;

}


void BarrierPreliminaryAction::Enter()
{

	m_time = 0.0f;

	m_bossEnemy->ChangeAnimation("Barrier");

}

void BarrierPreliminaryAction::Exit()
{



}
