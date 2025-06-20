#include "pch.h"
#include "BossEnemy.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Enemies/BossEnemy/BossEnemyParts.h"
#include "GameBase/Messenger/Messenger.h"
#include "Game/Enemies/BossEnemy/BehavirTree/BossBehaviorTree.h"
#include "Game/Params.h"
#include "Game/Enemies/BossEnemy/Model/BossEnemyModel.h"
#include "Game/Enemies/BossEnemy/Animation/BossAnimationController.h"
#include "Game/Enemies/BossEnemy/Action/BossEnemyActionManager.h"
#include "Game/Player/Player.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
/// <param name="scale">�傫��</param>
/// <param name="position">���W</param>
/// <param name="rotation">��]</param>
BossEnemy::BossEnemy(Scene* scene, Player* player)
	:
	Actor(scene)
	,m_behavior{}
	,m_actionManager{}
	,m_animation{}
	,m_isGround{}
{

	using namespace DirectX::SimpleMath;

	m_rigidBody = AddComponent<RigidbodyComponent>(this);
	//�����蔻��̍쐬
	auto aABBCollider = AddComponent<AABB>(this, ColliderComponent::ColliderTag::AABB, CollisionType::COLLISION
		, Params::BOSSENEMY_BOX_COLLIDER_SIZE
		, Params::BOSSENEMY_SPHERE_COLLIDER_SIZE);

	Vector3 position = Vector3(0, 3.5f, -5);

	//������Ԃ̓K�p
	GetTransform()->SetScale(Vector3::One);
	GetTransform()->Translate(position);
	GetTransform()->SetRotate(Quaternion::Identity);

	//���f���̍쐬
	m_model = GetScene()->AddActor<BossEnemyModel>(GetScene());
	//���f���̑傫�����v���C���̐ݒ��
	m_model->GetTransform()->SetScale(Vector3::One);
	m_model->GetTransform()->Translate(position);
	m_model->GetTransform()->SetRotate(Quaternion::Identity);
	//�e�q�֌W���Z�b�g
	m_model->GetTransform()->SetParent(GetTransform());

	//�r�w�C�r�A�c���[
	m_behavior = std::make_unique<BossBehaviorTree>(player,this);

	//�A�j���[�V�����R���|�[�l���g�̒ǉ�
	m_animation = AddComponent<AnimatorComponent>(this, std::make_unique<BossAnimationController>(this));

	m_actionManager = std::make_unique<BossEnemyActionManager>(this, player);

	Messenger::GetInstance()->Rigister(
		{
			MessageType::BOSS_BEAM_ATTACK_STATE
			,MessageType::BOSS_JUMP_ATTACK_STATE
			,MessageType::BOSS_SWING_DOWN_STATE
			,MessageType::BOSS_WAKING_STATE
		}
		, this
	);

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BossEnemy::~BossEnemy()
{

}

void BossEnemy::UpdateActor(const float& deltaTime)
{
	
	//if (m_actionManager->Update(deltaTime))
	//{
	//	//�r�w�C�r�A�c���[�̍X�V
	//	//m_behavior->Update(deltaTime);

	//	Messenger::GetInstance()->Notify(MessageType::BOSS_JUMP_ATTACK_STATE);

	//}

	float ratio = 0.5f;

	Messenger::GetInstance()->Notify(MessageType::BOSS_DAMAGE, &ratio);

}

/// <summary>
/// �����������ɌĂ΂��֐�
/// </summary>
/// <param name="collider">����̃R���C�_�[</param>
void BossEnemy::OnCollisionEnter(ColliderComponent* collider)
{
	switch (collider->GetActor()->GetObjectTag())
	{
		case Actor::ObjectTag::STAGE:
			Landing();
			break;
		default:
			break;
	}

}

/// <summary>
/// �������Ă���Ƃ��ɌĂяo�����֐�
/// </summary>
/// <param name="collider">����̃R���C�_�[</param>
void BossEnemy::OnCollisionStay(ColliderComponent* collider)
{
	switch (collider->GetActor()->GetObjectTag())
	{
		case Actor::ObjectTag::STAGE:
			Landing();
			break;
		default:
			break;
	}
}

/// <summary>
/// ���ꂽ���ɌĂяo�����֐�
/// </summary>
/// <param name="collider"></param>
void BossEnemy::OnCollisionExit(ColliderComponent* collider)
{

	switch (collider->GetActor()->GetObjectTag())
	{
		case Actor::ObjectTag::STAGE:
			m_isGround = false;
			break;
		default:
			break;
	}
}

/// <summary>
/// ���n�����Ƃ�
/// </summary>
void BossEnemy::Landing()
{
	m_rigidBody->ResetGravity();
	m_isGround = true;
}
/// <summary>
/// �ʒm���󂯎��֐�
/// </summary>
/// <param name="type">�ʒm�̎��</param>
/// <param name="datas">�ǉ��f�[�^</param>
void BossEnemy::Notify(MessageType type, void* datas)
{

	switch (type)
	{
		case MessageType::BOSS_BEAM_ATTACK_STATE:
			break;
		case MessageType::BOSS_JUMP_ATTACK_STATE:
			break;
		case MessageType::BOSS_WAKING_STATE:
			break;
		case MessageType::BOSS_SWING_DOWN_STATE:
			break;
		default:
			break;
	}

}















