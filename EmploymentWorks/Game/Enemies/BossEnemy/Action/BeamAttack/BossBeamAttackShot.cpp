/*
	�N���X��     : BossBeamAttackShot
	����         : �{�X�G�̃r�[���U���̃V���b�g���
	�⑫�E���ӓ_ :
*/
#include "pch.h"
#include "BossBeamAttackShot.h"
#include "GameBase/Common/Commons.h"
#include "Game/Params.h"
#include "Game/Player/Player.h"
#include "Game/Component/Components.h"
#include "Game/Enemies/BossEnemy/Beam/BossEnemyBeam.h"
#include "Game/Enemies/BossEnemy/Beam/EnergyBall/BossEnemyBeamEnergyBall.h"
#include "Game/Enemies/BossEnemy/Beam/Rays/BossEnemyBeamRays.h"


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
	m_bossEnemy{ bossEnemy }
	, m_beam{ beam }
	,m_beamAttack{beamAttack}
	,m_player{player}
	,m_moveDirection{DirectX::SimpleMath::Vector3::Backward}
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
BossBeamAttackShot::ActionState BossBeamAttackShot::Update(const float& deltaTime)
{

	using namespace DirectX::SimpleMath;
	//�{�[���̎擾
	auto ball = m_beam->GetEnergyBall();
	//�{�[���̍��W���{Z�����Ɉړ�
	ball->GetTransform()->SetPosition(ball->GetTransform()->GetPosition() + m_moveDirection * deltaTime * SHOT_SPEED);
	//�����̎擾
	auto rays = m_beam->GetRays();
	//�����̑傫���̎擾
	auto raysScale = rays->GetTransform()->GetScale();
	//�r�[���S�̂ƃ{�[���̋��������߂�
	float distaance = Vector3::Distance(m_beam->GetTransform()->GetWorldPosition() , ball->GetTransform()->GetWorldPosition());
	//�����W�������ɂ���
	raysScale.z = distaance;
	//�����̑傫���̃Z�b�g
	rays->GetTransform()->SetScale(raysScale);

	//���s���@�@�@�e�������������ɏ�Ԃ�؂�ւ���
	return ActionState::RUNNING;

}

/// <summary>
/// ��Ԃɓ�������
/// </summary>
void BossBeamAttackShot::Enter()
{


	//�����̎擾
	auto rays = m_beam->GetRays();
	//�����̏����̑傫���̃Z�b�g
	rays->GetTransform()->SetScale(Params::BOSSENEMY_BEAM_RAYS_MAX_SCALE);
	//������L��
	m_beam->GetRays()->SetActive(true);

	//�r�[���S�̂��^�[�Q�b�g�����ɉ�]
	m_beam->TargetToRotation();
}

/// <summary>
/// ��Ԃ𔲂�����
/// </summary>
void BossBeamAttackShot::Exit()
{

	m_beam->GetEnergyBall()->GetComponent<AABB>()->SetActive(false);

}

