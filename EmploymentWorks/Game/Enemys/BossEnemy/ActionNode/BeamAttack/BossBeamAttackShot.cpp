/*
	@file	BossBeamAttackShot.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "BossBeamAttackShot.h"
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
#include "Game/Enemys/BossEnemy/Beam/BeamEnergyBall.h"
#include "Game/Enemys/BossEnemy/Beam/BeamChargeEffect.h"
#include "Game/Enemys/BossEnemy/Beam/BeamRays.h"
#include "Game/Player/Player.h"
using namespace DirectX;
using namespace DirectX::SimpleMath;




/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
BossBeamAttackShot::BossBeamAttackShot(CommonResources* resources
	, BossEnemy* bossEnemy
	, Beam* beam
	, BossBeamAttackAction* beamAttack
	, Player* player)
	:
	m_commonResources{resources}
	, m_bossEnemy{ bossEnemy }
	, m_beam{ beam }
	,m_beamAttack{beamAttack}
	,m_player{player}
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BossBeamAttackShot::~BossBeamAttackShot()
{
	// do nothing.
}

void BossBeamAttackShot::Initialize()
{
}

IBehaviorNode::State BossBeamAttackShot::Update(const float& elapsedTime)
{

	Vector3 position = m_beam->GetBeamEnergyBall()->GetLocalPosition();

	Vector3 moveDirection = Vector3::UnitZ;

	moveDirection *= elapsedTime * Params::BOSSENEMY_BEAM_BALL_MOVE_SPPED;

	position += moveDirection;

	m_beam->GetBeamEnergyBall()->SetLocalPosition(position);

	//�r�[�������̑傫���̎擾
	Vector3 scale = m_beam->GetBeamRays()->GetLocalScale();

	//�r�[���̋��������߂�
	float distance = Vector3::Distance(m_beam->GetPosition(), m_beam->GetBeamEnergyBall()->GetPosition());

	//���f���̃T�C�Y�̂���0.5�����炻�̂܂܂ł����v
	//�������T�C�Y��
	scale.z = distance;

	//�r�[�������̑傫����
	m_beam->GetBeamRays()->SetLocalScale(scale);

	return IBehaviorNode::State::Runngin;

}


void BossBeamAttackShot::Enter()
{

	m_beam->GetBeamRays()->SetLocalScale(Params::BOSSENEMY_BEAM_RAYS_MAX_SCALE);

	Vector3 s = m_beam->GetScale();
	//�G�̌��݂̍��W�̎擾
	Vector3 startPosition = m_beam->GetPosition();
	//�v���C���̌��݂̍��W�̎擾
	Vector3 endPosition = m_player->GetPosition() + Vector3(0,1,0);
	//�G����v���C���̕����x�N�g���̌v�Z
	Vector3 toPlayer = endPosition - startPosition;
	//yaw�̌v�Z�@�i���E��]�j
	//xz���ʂœG����v���C���̕��������߂�
	float yaw = atan2(toPlayer.x, toPlayer.z);
	//pitch�̌v�Z�i�㉺��]�j
	//�G����v���C���̃E�ᒺ���������߂�
	float pitch = atan2(toPlayer.y, sqrt(toPlayer.x * toPlayer.x + toPlayer.z * toPlayer.z));
	//yaw pitch�����]���v�Z pitch�͔��]������
	m_beam->SetRotation(Quaternion::CreateFromYawPitchRoll(yaw, -pitch, 0.0f));

	m_beam->GetBeamRays()->SetIsEntityActive(true);


}

void BossBeamAttackShot::Exit()
{
}

