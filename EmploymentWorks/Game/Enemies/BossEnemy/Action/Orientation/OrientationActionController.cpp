/*
	@file	OrientationActionController.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "OrientationActionController.h"
#include "GameBase/Common/Commons.h"
#include "Game/Params.h"
#include "Game/Player/Player.h"
#include "Game/Enemies/BossEnemy/BossEnemy.h"



/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
OrientationActionController::OrientationActionController(BossEnemy* bossenemy
	, Player* player)
	:
	m_commonResources{}
{

	m_commonResources = CommonResources::GetInstance();

	//�e��Ԃ��쐬
	m_orientation = std::make_unique<OrientationAction>(bossenemy, player);


	//m_currentState->Enter();


	//���쏇�ɒǉ�
	AddAction({
		m_orientation.get()
		});


}

/// <summary>
/// �f�X�g���N�^
/// </summary>
OrientationActionController::~OrientationActionController()
{
	// do nothing.
}






