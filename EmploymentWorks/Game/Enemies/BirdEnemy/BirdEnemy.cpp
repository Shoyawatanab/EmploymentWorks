#include "pch.h"
#include "BirdEnemy.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Enemies/BirdEnemy/Model/BirdEnemyModel.h"
#include "Game/Enemies/BirdEnemy/State/BirdEnemyStateMachine.h"
#include "Game/Player/Player.h"
#include "Game/Enemies/BirdEnemy/Bullet/BirdEnemyBullet.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="scene">�V�[��</param>
/// <param name="player">�v���C��</param>
BirdEnemy::BirdEnemy(Scene* scene, Player* player)
	:
	EnemyBase(scene,10)
	,m_target{player}
	,m_bullets{}
{
	using namespace DirectX::SimpleMath;


	//���f���̍쐬
	auto model = GetScene()->AddActor<BirdEnemyModel>(GetScene());
	//���f���̑傫�����v���C���̐ݒ��
	model->GetTransform()->SetScale(Vector3(0.5f,0.5f,0.5f));
	model->GetTransform()->Translate(Vector3::Zero);
	model->GetTransform()->SetRotate(Quaternion::Identity);
	//�e�q�֌W���Z�b�g
	model->GetTransform()->SetParent(GetTransform());

	SetModel(model);

	for (int i = 0; i < 1; i++)
	{
		auto bullet = GetScene()->AddActor<BirdEnemyBullet>(GetScene(), this);
		m_bullets.push_back(bullet);
	}

	//������Ԃ̓K�p Json�ŊǗ�
	GetTransform()->SetScale(Vector3::One);
	GetTransform()->Translate(Vector3(0,3,0));
	GetTransform()->SetRotate(Quaternion::Identity);

	m_stateMachine = std::make_unique<BirdEnemyStateMachine>(this);




}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BirdEnemy::~BirdEnemy()
{
}

/// <summary>
/// �ʃA�b�v�f�[�g
/// </summary>
/// <param name="deltaTime"></param>
void BirdEnemy::UpdateActor(const float& deltaTime)
{
	m_stateMachine->Update(deltaTime);

	//��Ƀ^�[�Q�b�g�Ɍ����悤��
	Rotate(deltaTime);

}

/// <summary>
/// 
/// </summary>
/// <param name="collider"></param>
void BirdEnemy::OnCollisionEnter(ColliderComponent* collider)
{

}

/// <summary>
/// 
/// </summary>
/// <param name="collider"></param>
void BirdEnemy::OnCollisionStay(ColliderComponent* collider)
{
}


/// <summary>
/// 
/// </summary>
/// <param name="collider"></param>
void BirdEnemy::OnCollisionExit(ColliderComponent* collider)
{
}

/// <summary>
/// �^�[�Q�b�g�ɑ΂��ĉ�]
/// </summary>
/// <param name="deltaTime"></param>
void BirdEnemy::Rotate(const float& deltaTime)
{
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
	GetTransform()->SetRotate(Quaternion::CreateFromYawPitchRoll(yaw, -pitch, 0.0f));



}
