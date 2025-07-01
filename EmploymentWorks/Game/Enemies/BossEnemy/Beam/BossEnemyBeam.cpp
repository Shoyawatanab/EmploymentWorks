#include "pch.h"
#include "BossEnemyBeam.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Enemies/BossEnemy/Beam/Rays/BossEnemyBeamRays.h"
#include "Game/Enemies/BossEnemy/Beam/EnergyBall/BossEnemyBeamEnergyBall.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="scene"></param>
BossEnemyBeam::BossEnemyBeam(Scene* scene)
	:
	Actor(scene)
	,m_target{}
{

	//����
	m_rays = GetScene()->AddActor<BossEnemyBeamRays>(GetScene());
	m_rays->GetTransform()->SetParent(GetTransform());

	//�e
	m_energyBall = GetScene()->AddActor<BossEnemyBeamEnergyBall>(GetScene());
	m_energyBall->GetTransform()->SetParent(GetTransform());

	GetTransform()->SetPosition(DirectX::SimpleMath::Vector3(-1.6f, 4, 0));


	SetActive(false);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BossEnemyBeam::~BossEnemyBeam()
{
}

/// <summary>
/// �ʂ̃A�b�v�f�[�g
/// </summary>
/// <param name="deltaTime"></param>
void BossEnemyBeam::UpdateActor(const float& deltaTime)
{



}

/// <summary>
/// �^�[�Q�b�g�Ɍ����ĉ�]
/// </summary>
/// <param name="deltaTime"></param>
void BossEnemyBeam::TargetToRotation()
{
	//�^�[�Q�b�g���Ȃ����
	if (!m_target)
	{
		return;
	}


	using namespace DirectX::SimpleMath;


	//�G�̌��݂̍��W�̎擾
	Vector3 enemyPosition = GetTransform()->GetWorldPosition();
	//�v���C���̌��݂̍��W�̎擾
	Vector3 playerPosition = m_target->GetTransform()->GetWorldPosition();
	//�G����v���C���̕����x�N�g���̌v�Z
	Vector3 toPlayer = playerPosition - enemyPosition;
	//yaw�̌v�Z�@�i���E��]�j
	//xz���ʂœG����v���C���̕��������߂�
	float yaw = atan2(toPlayer.x, toPlayer.z);
	//pitch�̌v�Z�i�㉺��]�j
	//�G����v���C���̃E�ᒺ���������߂�
	float pitch = atan2(toPlayer.y, sqrt(toPlayer.x * toPlayer.x + toPlayer.z * toPlayer.z));

	//yaw pitch�����]���v�Z pitch�͔��]������
	GetTransform()->SetRotate(Quaternion::CreateFromYawPitchRoll(0, -pitch, 0.0f));


}
