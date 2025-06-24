#include "pch.h"
#include "BossEnemy.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Enemies/BossEnemy/BossEnemyParts.h"
#include "Game/Messenger/Messenger.h"
#include "Game/Enemies/BossEnemy/BehavirTree/BossBehaviorTree.h"
#include "Game/Params.h"
#include "Game/Enemies/BossEnemy/Model/BossEnemyModel.h"
#include "Game/Enemies/BossEnemy/Animation/BossAnimationController.h"
#include "Game/Enemies/BossEnemy/Action/BossEnemyActionManager.h"
#include "Game/Player/Player.h"

#include "Game/Camera/PayScene/PlaySceneCamera.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="scene">�V�[��</param>
/// <param name="player">�v���C��</param>
BossEnemy::BossEnemy(Scene* scene, Player* player)
	:
	EnemyBase(scene,Params::BOSSENEMY_MAX_HP)
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
	auto model = GetScene()->AddActor<BossEnemyModel>(GetScene());
	//���f���̑傫�����v���C���̐ݒ��
	model->GetTransform()->SetScale(Vector3::One);
	model->GetTransform()->Translate(position);
	model->GetTransform()->SetRotate(Quaternion::Identity);
	//�e�q�֌W���Z�b�g
	model->GetTransform()->SetParent(GetTransform());

	SetModel(model);

	//�r�w�C�r�A�c���[
	m_behavior = std::make_unique<BossBehaviorTree>(player,this);

	//�A�j���[�V�����R���|�[�l���g�̒ǉ�
	m_animation = AddComponent<AnimatorComponent>(this, std::make_unique<BossAnimationController>(this));

	m_actionManager = std::make_unique<BossEnemyActionManager>(this, player);



}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BossEnemy::~BossEnemy()
{

}

/// <summary>
/// �ʃA�b�v�f�[�g
/// </summary>
/// <param name="deltaTime"></param>
void BossEnemy::UpdateActor(const float& deltaTime)
{
	
	//if (m_actionManager->Update(deltaTime))
	//{
	//	//�r�w�C�r�A�c���[�̍X�V
	//	//m_behavior->Update(deltaTime);

	//	Messenger::GetInstance()->Notify(MessageType::BOSS_JUMP_ATTACK_STATE);

	//}


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
		case Actor::ObjectTag::BOOMERANG:
			{
				int damage = Params::BOOMERANG_DAMAGE;

				HpDecrease(damage);
				Messenger::GetInstance()->Notify(MessageType::ENEMY_DAMAGE, &damage);
			

				float ratio = GetHpRatio();
				Messenger::GetInstance()->Notify(MessageType::BOSS_DAMAGE, &ratio);

			}

			//Hp���O�ɂȂ��
			if (GetHp() <= 0)
			{

				auto camera = GetScene()->GetCamera();

				auto* playCamera = static_cast<PlaySceneCamera*>(camera);
				playCamera->SetTarget(this);

				Messenger::GetInstance()->Notify(MessageType::BOSS_DEFEATED);

			}

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

	

}















