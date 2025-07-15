/*
	�N���X��     : Boomerang
	����         : �u�[������
	�⑫�E���ӓ_ :
*/
#include "pch.h"
#include "Boomerang.h"
#include "Game/Component/Components.h"
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
	,m_lastPosition{}
{

	//�����蔻��̍쐬
	auto aabbCollider = AddComponent<AABB>(this, CollisionType::COLLISION
		, Params::BOOMERANG_BOX_COLLIDER_SIZE
		, Params::BOOMERANG_SPHERE_COLLIDER_SIZE);

	//�����蔻��𖳌���
	aabbCollider->SetActive(false);

	aabbCollider->SetNotHitObjectTag({
		Actor::ObjectTag::PLAYER
		,Actor::ObjectTag::PLAYER_PARTS
		});

	auto shadow = AddComponent<RoundShadowComponent>(this, Params::PLAYER_SHADOW_RADIUS);

	auto rigidbody = AddComponent<RigidbodyComponent>(this);
	rigidbody->SetActive(false);

	auto pcikable = AddComponent<PickableComponent>(this,PickUpManager::PickUpType::PLAYER_PICKUP_WEAPON);
	pcikable->SetOnPickUpFunction(std::bind(&Boomerang::PickUp,this));

	//�������̍쐬
	m_strikeSE = AddComponent<SoundComponent>(this, "BoomerangHit", SoundComponent::SoundType::SE);


	//�������̓K�p
	GetTransform()->SetScale(Params::BOOMERANG_SCALE);
	GetTransform()->Translate(Params::Params::BOOMERANG_POSITION);
	GetTransform()->SetRotate(Params::Params::BOOMERANG_ROTATION);



	AddComponent<ModelComponent>(this, "Boomerang");

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

	//���W�̕ۑ�
	m_lastPosition = GetTransform()->GetPosition();

}


/// <summary>
/// �����������̊֐�
/// </summary>
/// <param name="collider"></param>
void Boomerang::OnCollisionEnter(ColliderComponent* collider)
{

	switch (collider->GetActor()->GetObjectTag())
	{
		case Actor::ObjectTag::STAGE:

			if (m_stateMachine->GetCurrentState() == BoomerangState::THROW)
			{
				m_stateMachine->ChangeState(BoomerangState::BOUNCE);
			}
			else if (m_stateMachine->GetCurrentState() == BoomerangState::BOUNCE)
			{
				m_stateMachine->ChangeState(BoomerangState::DORP);
			}
			break;
		case Actor::ObjectTag::BOSS_ENEMY_PARTS:
			m_strikeSE->Play();
			break;
		default:
			break;
	}

}

/// <summary>
/// �X�e�[�g�̕ύX
/// </summary>
/// <param name="state">���̃X�e�[�g</param>
void Boomerang::ActorChangeState(BoomerangState nextState)
{

	switch (nextState)
	{
		case BoomerangState::IDEL:
			m_stateMachine->ChangeState(BoomerangState::IDEL);
			break;
		case BoomerangState::GET_READY:
			m_stateMachine->ChangeState(BoomerangState::GET_READY);
			break;
		case BoomerangState::THROW:
			m_stateMachine->ChangeState(BoomerangState::THROW);
			break;
		default:
			break;
	}

}

/// <summary>
/// ���
/// </summary>
void Boomerang::PickUp()
{
	m_stateMachine->ChangeState(BoomerangState::IDEL);
}
