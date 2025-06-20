/*
	@file	WalkActionComtroller.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "WalkActionComtroller.h"
#include "Game/Enemies/BossEnemy/Action/Walk/WalkActionComtroller.h"
#include "Game/Params.h"



using namespace DirectX;
using namespace DirectX::SimpleMath;



/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
/// <param name="own">���L��</param>
/// <param name="target">�^�[�Q�b�g</param>
WalkActionComtroller::WalkActionComtroller(Actor* own
	, Actor* target)
	:
	m_commonResources{}
	,m_own{own}
	,m_target{target}
{
	//�e��Ԃ̍쐬
	m_walkingAction = std::make_unique<WalkAction>(m_own,m_target);
	m_orientation = std::make_unique<OrientationAction>(m_own, m_target);

	//���쏇�ɒǉ�
	AddAction({
		m_walkingAction.get() 
		});

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
WalkActionComtroller::~WalkActionComtroller()
{
	// do nothing.
}


