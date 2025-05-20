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
/// <param name="barrierDefenseAction">�R���g���[���[</param>
/// <param name="owner">���L��</param>
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
/// �f�X�g���N�^
/// </summary>
BarrierPreliminaryAction::~BarrierPreliminaryAction()
{
	// do nothing.
}

/// <summary>
/// ������
/// </summary>
void BarrierPreliminaryAction::Initialize()
{
	
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
/// <returns>�I�����p����</returns>
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
/// ��Ԃɓ�������
/// </summary>
void BarrierPreliminaryAction::Enter()
{

	m_time = 0.0f;

	m_owner->ChangeAnimation("Barrier");

}

/// <summary>
/// ��Ԃ𔲂�����
/// </summary>
void BarrierPreliminaryAction::Exit()
{



}
