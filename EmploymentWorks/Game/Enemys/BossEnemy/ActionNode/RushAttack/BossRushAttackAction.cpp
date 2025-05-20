/*
	@file	BossRushAttackAction.cpp
	@brief	�v���C�V�[���N���X
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




/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
/// <param name="bossenemy">���L��</param>
/// <param name="player">�v���C��</param>
BossRushAttackAction::BossRushAttackAction(CommonResources* resources
	,BossEnemy* bossenemy
	, Player* player)
	:
	ActionStateController{}
	,m_commonResources{resources}
{


	//�e��Ԃ��쐬
	m_charge = std::make_unique<BossRushAttackCharge>(resources,this,bossenemy,player);
	m_rush = std::make_unique<BossRushAttackRush>(resources, this, bossenemy, player);



	//���쏇�ɒǉ�
	ActionStateController::Initialize({
		m_charge.get()
		,m_rush.get()
	});

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BossRushAttackAction::~BossRushAttackAction()
{
	// do nothing.
}




