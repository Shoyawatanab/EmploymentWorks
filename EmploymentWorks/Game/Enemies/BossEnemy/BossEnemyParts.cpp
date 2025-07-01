#include "pch.h"
#include "BossEnemyParts.h"
#include "GameBase/Component/Components.h"
#include "Game/Enemies/BossEnemy/BossEnemy.h"
#include "Game/Params.h"
#include "Game/Messenger/Scene/SceneMessages.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene">�V�[��</param>
/// <param name="partsName">�p�[�c��</param>
/// <param name="modelName">���f����</param>
/// <param name="hp">�p�[�cHP</param>
/// <param name="boss">��{�̃N���X</param>
BossEnemyParts::BossEnemyParts(Scene* scene, std::string partsName,std::string modelName
	,int hp, DirectX::SimpleMath::Vector3 boxColliderExtens, float sphereRadius
	, BossEnemy* boss)
	:
	ModelPartsBase(scene,partsName,modelName)
	,m_hp{}
	,m_bossEnemy{boss}
{

	auto obb = AddComponent<OBB>(this, ColliderComponent::ColliderTag::OBB, CollisionType::TRIGGER
		, boxColliderExtens
		, DirectX::SimpleMath::Quaternion::Identity
		, sphereRadius);

	obb->SetNotHitObjectTag({
		Actor::ObjectTag::BOSS_ENEMY
		});

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BossEnemyParts::~BossEnemyParts()
{
}

/// <summary>
/// �����������̊֐�
/// </summary>
/// <param name="collider">����̃R���C�_�[</param>
void BossEnemyParts::OnCollisionEnter(ColliderComponent* collider)
{

	switch (collider->GetActor()->GetObjectTag())
	{
		case ObjectTag::BOOMERANG:
		{
			//�p�[�c��Hp����
			HpDecrease(Params::BOOMERANG_DAMAGE);

			//�\���̂̍쐬
			EnemyDamageDatas datas;
			//�f�[�^�̃Z�b�g
			datas.Damage = Params::BOOMERANG_DAMAGE;
			datas.Position = GetTransform()->GetWorldPosition();


			SceneMessenger::GetInstance()->Notify(SceneMessageType::ENEMY_DAMAGE, &datas);

			//�{�X�G�Ƀ_���[�W�̉��Z
			m_bossEnemy->AddDamage(Params::BOOMERANG_DAMAGE);
		}
			break;
		default:
			break;
	}

	OnCollisionEnterActor(collider);

}

/// <summary>
/// HP����
/// </summary>
/// <param name="damage">�_���[�W</param>
void BossEnemyParts::HpDecrease(int damage)
{

	m_hp -= damage;

	m_hp = std::max(m_hp, 0);

}
