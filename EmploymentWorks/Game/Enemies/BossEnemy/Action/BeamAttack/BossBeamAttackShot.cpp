/*
	@file	BossBeamAttackShot.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "BossBeamAttackShot.h"
#include "GameBase/Common/Commons.h"


#include "Game/Params.h"
#include "Game/Player/Player.h"




/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
/// <param name="bossEnemy">���L��</param>
/// <param name="beam">�r�[��</param>
/// <param name="beamAttack">�r�[���U��</param>
/// <param name="player">�v���C��</param>
BossBeamAttackShot::BossBeamAttackShot(Actor* bossEnemy
	, BossEnemyBeam* beam
	, BossBeamAttackActionController* beamAttack
	, Actor* player)
	:
	m_commonResources{}
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


/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
/// <returns>�p�����I����</returns>
BossBeamAttackShot::ActionState BossBeamAttackShot::Update(const float& elapsedTime)
{
	////�G�l���M�[�e�̎擾
	//Vector3 position = m_beam->GetBeamEnergyBall()->GetLocalPosition();
	////����������
	//Vector3 moveDirection = Vector3::UnitZ;
	////�ǂꂾ����������
	//moveDirection *= elapsedTime * Params::BOSSENEMY_BEAM_BALL_MOVE_SPPED;
	////���W�����Z
	//position += moveDirection;
	////���W�̓o�^
	//m_beam->GetBeamEnergyBall()->SetLocalPosition(position);

	////�r�[�������̑傫���̎擾
	//Vector3 scale = m_beam->GetBeamRays()->GetLocalScale();

	////�r�[���̋��������߂�
	//float distance = Vector3::Distance(m_beam->GetPosition(), m_beam->GetBeamEnergyBall()->GetPosition());

	////���f���̃T�C�Y�̂���0.5�����炻�̂܂܂ł����v
	////�������T�C�Y��
	//scale.z = distance;

	////�r�[�������̑傫����
	//m_beam->GetBeamRays()->SetLocalScale(scale);

	return ActionState::RUNNING;

}

/// <summary>
/// ��Ԃɓ�������
/// </summary>
void BossBeamAttackShot::Enter()
{

	//m_beam->GetBeamRays()->SetLocalScale(Params::BOSSENEMY_BEAM_RAYS_MAX_SCALE);

	//Vector3 s = m_beam->GetScale();
	////�G�̌��݂̍��W�̎擾
	//Vector3 startPosition = m_beam->GetPosition();
	////�v���C���̌��݂̍��W�̎擾�@�������_���悤�ɂ���
	//Vector3 endPosition = m_player->GetPosition() + TARGET_OFFSET;
	////�G����v���C���̕����x�N�g���̌v�Z
	//Vector3 toPlayer = endPosition - startPosition;
	////yaw�̌v�Z�@�i���E��]�j
	////xz���ʂœG����v���C���̕��������߂�
	//float yaw = atan2(toPlayer.x, toPlayer.z);
	////pitch�̌v�Z�i�㉺��]�j
	////�G����v���C���̃E�ᒺ���������߂�
	//float pitch = atan2(toPlayer.y, sqrt(toPlayer.x * toPlayer.x + toPlayer.z * toPlayer.z));
	////yaw pitch�����]���v�Z pitch�͔��]������
	//m_beam->SetRotation(Quaternion::CreateFromYawPitchRoll(yaw, -pitch, 0.0f));

	//m_beam->GetBeamRays()->SetIsEntityActive(true);

	//m_beam->GetBeamEnergyBall()->SetIsCollisionActive(true);


}

/// <summary>
/// ��Ԃ𔲂�����
/// </summary>
void BossBeamAttackShot::Exit()
{
	//m_beam->GetBeamEnergyBall()->SetIsCollisionActive(false);

}

