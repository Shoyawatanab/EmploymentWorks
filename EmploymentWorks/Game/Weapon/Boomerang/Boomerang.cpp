#include "pch.h"
#include "Boomerang.h"
#include "GameBase/Component/Components.h"
#include "Game/Params.h"
#include "Game/Weapon/Boomerang/State/BoomerangStateMachine.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="scene">�V�[��</param>
/// <param name="player">�v���C��</param>
Boomerang::Boomerang(Scene* scene,Player* player)
	:
	WeaponBase(scene)
{

	//�����蔻��̍쐬
	auto aabbCollider = AddComponent<AABB>(this, ColliderComponent::ColliderTag::AABB, CollisionType::COLLISION
		, Params::BOOMERANG_BOX_COLLIDER_SIZE
		, Params::BOOMERANG_SPHERE_COLLIDER_SIZE);
	//�����蔻��𖳌���
	aabbCollider->SetActive(false);

	aabbCollider->SetNotHitObjectTag({
		Actor::ObjectTag::PLAYER
		,Actor::ObjectTag::PLAYER_PARTS
		});

	auto shadow = AddComponent<RoundShadowComponent>(this, Params::PLAYER_SHADOW_RADIUS);


	//�������̓K�p
	GetTransform()->SetScale(Params::BOOMERANG_SCALE);
	GetTransform()->Translate(Params::Params::BOOMERANG_POSITION);
	GetTransform()->SetRotate(Params::Params::BOOMERANG_ROTATION);



	auto model = AddComponent<ModelComponent>(this, "Boomerang");

	m_stateMachine = std::make_unique<BoomerangStateMachine>(this, player);

	shadow->SetActive(false);

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Boomerang::~Boomerang()
{
}

/// <summary>
/// �ʃA�b�v�f�[�g
/// </summary>
/// <param name="deltaTime"></param>
void Boomerang::UpdateActor(const float& deltaTime)
{
	m_stateMachine->Update(deltaTime);
}

/// <summary>
/// �����������̊֐�
/// </summary>
/// <param name="collider"></param>
void Boomerang::OnCollisionEnter(ColliderComponent* collider)
{

}

/// <summary>
/// �X�e�[�g�̕ύX
/// </summary>
/// <param name="state">���̃X�e�[�g</param>
void Boomerang::ActorChangeState(WeaponState nextState)
{

	switch (nextState)
	{
		case WeaponBase::WeaponState::BOOMERANG_IDLE:
			m_stateMachine->ChangeState(BoomerangState::IDEL);
			break;
		case WeaponBase::WeaponState::BOOMERANG_GET_READY:
			m_stateMachine->ChangeState(BoomerangState::GET_READY);
			break;
		case WeaponBase::WeaponState::BOOMERANG_THROW:
			m_stateMachine->ChangeState(BoomerangState::THROW);
			break;
		default:
			break;
	}

}
