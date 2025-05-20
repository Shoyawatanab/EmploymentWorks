/*
	@file	BarrierDefenseAction.cpp
	@brief	�v���C�V�[���N���X
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
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
/// <param name="owner">���L��</param>
/// <param name="barrier"></param>
BarrierDefenseAction::BarrierDefenseAction(CommonResources* resources
	, CharacterEntity* owner
	, Barrier* barrier
	)
	:
	m_commonResources{resources}
	,m_preliminaryAction{}
	,m_deployment{}
	,m_barrier{barrier}
{
	//�e�s�����쐬
	m_preliminaryAction = std::make_unique<BarrierPreliminaryAction>(resources, this, owner);
	m_deployment = std::make_unique<BarrierDeployment>(resources, this,barrier);
	m_close = std::make_unique<BarrierClose>(resources, this, barrier, owner);

	//���쏇�ɒǉ�
	ActionStateController::Initialize({
		m_preliminaryAction.get()
		,m_deployment.get()
		,m_close.get()
		});

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BarrierDefenseAction::~BarrierDefenseAction()
{
	// do nothing.
}


void BarrierDefenseAction::Notify(const Telegram<GameMessageType>& telegram)
{
	UNREFERENCED_PARAMETER(telegram);
	

}






