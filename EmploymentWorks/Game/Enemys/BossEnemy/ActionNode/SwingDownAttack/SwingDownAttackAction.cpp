/*
	@file	SwingDownAttackAction.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "SwingDownAttackAction.h"
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

#include "Game/Enemies/BossEnemy/BossEnemy.h"
#include "Game/Enemys/BossEnemy/Beam/Beam.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;



/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">�o�ߎ���</param>
/// <param name="owner">���L��</param>
SwingDownAttackAction::SwingDownAttackAction(CommonResources* resources
	, CharacterEntity* owner
	)
	:
	ActionStateController{},
	m_commonResources{resources}
{

	//�e��Ԃ̍쐬
	m_raisePhase = std::make_unique<SwingDownAttackRaisePhase>(m_commonResources,this, owner);

	m_swingPhase = std::make_unique<SwingDownAttackSwingPhase>(m_commonResources, this, owner);


	//m_currentState->Enter();


	//���쏇�ɒǉ�
	ActionStateController::Initialize({
		m_raisePhase.get()
		,m_swingPhase.get()
		});


}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SwingDownAttackAction::~SwingDownAttackAction()
{
	// do nothing.
}







