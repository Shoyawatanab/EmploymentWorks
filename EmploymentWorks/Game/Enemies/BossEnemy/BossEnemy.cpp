/*
	�N���X��     : BossEnemy
	����         : �{�X�G
	�⑫�E���ӓ_ :
*/
#include "pch.h"
#include "BossEnemy.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Component/Components.h"
#include "Game/Enemies/BossEnemy/BossEnemyParts.h"
#include "Game/Messenger/Scene/SceneMessages.h"
#include "Game/Enemies/BossEnemy/BehavirTree/BossBehaviorTree.h"
#include "Game/Params.h"
#include "Game/Enemies/BossEnemy/Model/BossEnemyModel.h"
#include "Game/Enemies/BossEnemy/Animation/BossAnimationController.h"
#include "Game/Enemies/BossEnemy/Action/BossEnemyActionManager.h"
#include "Game/Player/Player.h"
#include "Game/Camera/PlayScene/PlaySceneCamera.h"
#include "Game/Fade/FadeManager.h"
#include "Game/Enemies/BossEnemy/Beam/BossEnemyBeam.h"
#include "Game/Enemies/EnemyManager.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="scene">�V�[��</param>
/// <param name="player">�v���C��</param>
BossEnemy::BossEnemy(Scene* scene, DirectX::SimpleMath::Vector3 scale
	, DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Quaternion rotation
	, EnemyManager* manager, Player* player)
	:
	EnemyBase(scene,Params::BOSSENEMY_MAX_HP,manager)
	,m_behavior{}
	,m_actionManager{}
	,m_animation{}
	,m_isGround{}
	,m_player{player}
{

	using namespace DirectX::SimpleMath;


	m_rigidBody = AddComponent<RigidbodyComponent>(this);
	//�����蔻��̍쐬
	auto collider = AddComponent<AABB>(this,  CollisionType::COLLISION
		, Params::BOSSENEMY_BOX_COLLIDER_SIZE
		, Params::BOSSENEMY_SPHERE_COLLIDER_SIZE);

	collider->SetNotHitObjectTag({
		Actor::ObjectTag::BOSS_ENEMY_PARTS
		,Actor::ObjectTag::BEAM

		});


	AddComponent<RoundShadowComponent>(this, Params::BOSSENEMY_SHADOW_RADIUS);


	//���f���̍쐬
	auto model = GetScene()->AddActor<BossEnemyModel>(GetScene(),this);
	//�e�q�֌W���Z�b�g
	model->GetTransform()->SetParent(GetTransform());
	
	SetModel(model);

	//���n��
	m_landingSE = AddComponent<SoundComponent>(this, "Landing", SoundComponent::SoundType::SE);



//�p�[�c���}�l�[�W���[�Ƀ^�[�Q�b�g�Ƃ��ēo�^
	//�p�[�c�̎擾
	auto partss = model->GetParts();
	//�ۑ��z��
	std::vector<Actor*> partssActor;
	for (auto& part : partss)
	{
		//Actor�����𒊏o����
		partssActor.push_back(part.second);
	}
//�����܂�

	GetEnemyManger()->AddTargets(partssActor);

	//������Ԃ̓K�p
	GetTransform()->SetScale(scale);
	GetTransform()->Translate(position);
	GetTransform()->SetRotate(rotation);

	auto beam = GetScene()->AddActor<BossEnemyBeam>(GetScene());
	beam->GetTransform()->SetParent(GetTransform());
	beam->SetTarget(player);

	//�r�w�C�r�A�c���[
	m_behavior = std::make_unique<BossBehaviorTree>(player,this);

	//�A�j���[�V�����R���|�[�l���g�̒ǉ�
	m_animation = AddComponent<AnimatorComponent>(this, std::make_unique<BossAnimationController>(this));

	m_actionManager = std::make_unique<BossEnemyActionManager>(this,player,beam);



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
	//�t�F�[�h���s��
	if (FadeManager::GetInstance()->GetIsFade())
	{
		return;
	}



	if (m_actionManager->Update(deltaTime))
	{
		//�r�w�C�r�A�c���[�̍X�V
		//m_behavior->Update(deltaTime);
		SceneMessenger::GetInstance()->Notify(SceneMessageType::BOSS_BEAM_ATTACK_STATE);
		//SceneMessenger::GetInstance()->Notify(SceneMessageType::BOSS_JUMP_ATTACK_STATE);
		//SceneMessenger::GetInstance()->Notify(SceneMessageType::BOSS_WAKING_STATE);
		//SceneMessenger::GetInstance()->Notify(SceneMessageType::BOSS_SWING_DOWN_STATE);

	}



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
/// �_���[�W��H������Ƃ�
/// </summary>
/// <param name="damage">�_���[�W</param>
void BossEnemy::AddDamage(int damage)
{

	HpDecrease(damage);
	


	float ratio = GetHpRatio();
	SceneMessenger::GetInstance()->Notify(SceneMessageType::BOSS_DAMAGE, &ratio);


	if (GetHp() <= 0)
	{
		auto camera = GetScene()->GetCamera();

		auto* playCamera = static_cast<PlaySceneCamera*>(camera);
		playCamera->SetTarget(this);

		m_actionManager->ChangeAction("Death");

	}
	

}

/// <summary>
/// ��]
/// </summary>
/// <param name="deltaTime">�o�ߎ���</param>
void BossEnemy::Rotation(const float& deltaTime)
{
	using namespace DirectX::SimpleMath;

	auto ownerPosition = GetTransform()->GetPosition();

	auto targetPosition = m_player->GetTransform()->GetPosition();

	ownerPosition.y = 0.0f;
	targetPosition.y = 0.0f;

	//������������
	Vector3 direction = targetPosition - ownerPosition;
	direction.Normalize();
	//���̓G�̑O����
	Vector3 forward = GetTransform()->GetForwardVector();
	//forward.Normalize();
	//��]���̍쐬
	Vector3 moveAxis = forward.Cross(direction);

	if (moveAxis.y >= 0.0f)
	{
		//���Ȃ�����
		moveAxis = Vector3::Up;
	}
	else
	{
		//���Ȃ牺����
		moveAxis = DirectX::SimpleMath::Vector3::Down;
	}

	//�p�x�����߂�
	float moveAngle = forward.Dot(direction);

	moveAngle = std::clamp(moveAngle, -1.0f, 1.0f);

	//���W�A���l�ɕϊ�
	moveAngle = acosf(moveAngle);

	//�p�x�Ƒ��x�̔�r�ŏ������ق����擾
	moveAngle = std::min(moveAngle, Params::BOSSENEMY_ROTATION_SPEED * deltaTime);

	//�G�̉�]�̎擾
	DirectX::SimpleMath::Quaternion Rotate = GetTransform()->GetRotate();
	//Y���ɑ΂��ĉ�]��������
	Rotate *= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(moveAxis, moveAngle);
	GetTransform()->SetRotate(Rotate);

}

/// <summary>
/// ���n���̍Đ�
/// </summary>
void BossEnemy::PlayLandingSE()
{
	//���n��
	m_landingSE->Play();

}

/// <summary>
/// ���n�����Ƃ�
/// </summary>
void BossEnemy::Landing()
{
	m_rigidBody->ResetGravity();
	m_isGround = true;
}
















