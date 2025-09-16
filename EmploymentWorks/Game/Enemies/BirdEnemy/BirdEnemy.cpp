/*
	�N���X��     : BirdEnemy
	����         : ���G
	�⑫�E���ӓ_ :
*/
#include "pch.h"
#include "BirdEnemy.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Component/Components.h"
#include "Game/Enemies/BirdEnemy/Model/BirdEnemyModel.h"
#include "Game/Enemies/BirdEnemy/State/BirdEnemyStateMachine.h"
#include "Game/Player/Player.h"
#include "Game/Enemies/BirdEnemy/Bullet/BirdEnemyBullet.h"
#include "Game/Messenger/Messengers.h"
#include "Game/Fade/FadeManager.h"
#include "Game/Params.h"
#include "Game/Enemies/EnemyManager.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="scene">�V�[��</param>
/// <param name="player">�v���C��</param>
BirdEnemy::BirdEnemy(Scene* scene, DirectX::SimpleMath::Vector3 scale
	, DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Quaternion rotation
	, EnemyManager* manager, Player* player)
	:
	EnemyBase(scene,Params::BIRDENEMY_HP,manager)
	,m_target{player}
	,m_bullets{}
{

	using namespace DirectX::SimpleMath;

	//�����蔻��̒ǉ�
	AddComponent<AABB>(this, CollisionType::COLLISION
		, Vector3(1.5f,1.5f,1.5f) * scale
		, 3.0f * std::max({ scale.x, scale.y, scale.z }));

	//�e�̒ǉ�
	auto shadow = AddComponent<RoundShadowComponent>(this, Params::BIRDENEMY_SHADOW_RADIUS);

	shadow->SetActive(false);

	//���f���̍쐬
	auto model = GetScene()->AddActor<BirdEnemyModel>(GetScene());
	//�e�q�֌W���Z�b�g
	model->GetTransform()->SetParent(GetTransform());
	//���f���̃Z�b�g
	SetModel(model);
	//���g���^�[�Q�b�g�Ƃ��ēo�^
	GetEnemyManger()->AddTargets({ this });

	//�e�̍쐬
	for (int i = 0; i < MAX_BULLET; i++)
	{
		auto bullet = GetScene()->AddActor<BirdEnemyBullet>(GetScene(), this);
		
		m_bullets.push_back(bullet);
	}

	//������Ԃ̓K�p Json�ŊǗ�
	GetTransform()->SetScale(scale);
	GetTransform()->Translate(position);
	GetTransform()->SetRotate(rotation);

	//�X�e�[�g�}�V�[���̍쐬
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
	UNREFERENCED_PARAMETER(deltaTime);

	if (FadeManager::GetInstance()->GetIsFade())
	{
		return;
	}

	return;

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

	switch (collider->GetActor()->GetObjectTag())
	{
		case Actor::ObjectTag::BOOMERANG:
		{
			//HP�̌���
			HpDecrease(Params::BOOMERANG_DAMAGE);

		}

		//Hp���O�ɂȂ��
		if (GetHp() <= 0)
		{
			//�ǉ��f�[�^�̍쐬
			ExplosionEffectDatas datas;
			datas.Position = GetTransform()->GetWorldPosition();
			datas.Scale = GetTransform()->GetWorldScale();
			//�����G�t�F�N�g�̒ʒm
			Messenger<SceneMessageType>::GetInstance()->Notify(SceneMessageType::EXPLOSITION_EFFECT, &datas);
			//�I�u�W�F�N�g�𖳌���
			SetActive(false);
			//�}�l�[�W���[�Ɏ��S�̒ʒm
			auto manager = GetEnemyManger();
			manager->DeathEnemy(this);
		}
		else
		{
			//�\���̂̍쐬
			EnemyDamageDatas datas;
			//�f�[�^�̃Z�b�g
			datas.Damage = Params::BOOMERANG_DAMAGE;
			datas.Position = GetTransform()->GetWorldPosition();
			//�G�_���[�W��UI�̒ʒm
			Messenger<SceneMessageType>::GetInstance()->Notify(SceneMessageType::ENEMY_DAMAGE, &datas);
		}

			break;
		default:
			break;
	}

}


/// <summary>
/// �^�[�Q�b�g�ɑ΂��ĉ�]
/// </summary>
/// <param name="deltaTime"></param>
void BirdEnemy::Rotate(const float& deltaTime)
{
	using namespace DirectX::SimpleMath;

	UNREFERENCED_PARAMETER(deltaTime);

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

/// <summary>
/// ��A�N�e�B�u�̒e�̎擾
/// </summary>
/// <returns>�e or nullptr</returns>
BirdEnemyBullet* BirdEnemy::GetInactiveBullet()
{

	for (auto& bullet : m_bullets)
	{
		if (!bullet->GetActive())
		{
			return bullet;
		}
	}


	return nullptr;

}





