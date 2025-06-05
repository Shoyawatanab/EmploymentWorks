#include "pch.h"
#include "Player2.h"
#include "GameBase/Managers.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Params.h"
#include "Game/Player/State/PlayerStateMachine.h"
#include "GameBase/Component/Components.h"
#include "Game/Player/Model/PlayerModel.h"
#include "Game/Player/Animation/PlayerAnimationController.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene">�V�[��</param>
Player2::Player2(Scene* scene)
	:
	Actor(scene)
	,m_playSceneCamera{}
	,m_rigidBody{}
{

	m_rigidBody = AddComponent<RigidbodyComponent>(this);
	//�����蔻��̍쐬
	auto aABBCollider = AddComponent<AABB>(this, ColliderComponent::ColliderTag::AABB, CollisionType::COLLISION
	, Params::PLAYER_BOX_COLLIDER_SIZE
	, Params::PLAYER_SPHERE_COLLIDER_SIZE);
	//�������̓K�p
	GetTransform()->SetScale(Params::PLAYER_SCALE);
	GetTransform()->Translate(Params::PLAYER_POSITION);
	GetTransform()->SetRotate(Params::PLAYER_ROTATION);

	//���f���̍쐬
	m_model =  GetScene()->AddActor<PlayerModel>(GetScene());
	m_model->GetTransform()->SetParent(GetTransform());
	//�X�e�[�g�̍쐬
	m_stateMachine = std::make_unique<PlayerStateMachine>(this);

	//�A�j���[�V�����R���|�[�l���g�̒ǉ�
	auto animator = AddComponent<AnimatorComponent>(this, std::make_unique<PlayerAnimationController>(this));
	

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Player2::~Player2()
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime"></param>
void Player2::UpdateActor(const float& deltaTime)
{

	m_stateMachine->Update(deltaTime);

}

void Player2::OnCollisionEnter(ColliderComponent* collider)
{
	switch (collider->GetActor()->GetObjectTag())
	{
		case Actor::ObjectTag::STAGE:
		{
			int a = 1;
		}
			break;
		default:
			break;
	}

}

void Player2::OnCollisionStay(ColliderComponent* collider)
{
	switch (collider->GetActor()->GetObjectTag())
	{
		case Actor::ObjectTag::STAGE:
		
			m_rigidBody->ResetGravity();
		break;
		default:
			break;
	}
}
