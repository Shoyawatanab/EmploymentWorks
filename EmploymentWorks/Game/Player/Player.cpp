#include "pch.h"
#include "Player.h"
#include "GameBase/Managers.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Params.h"
#include "Game/Player/State/PlayerStateMachine.h"
#include "GameBase/Component/Components.h"
#include "Game/Player/Model/PlayerModel.h"
#include "Game/Player/Animation/PlayerAnimationController.h"
#include "GameBase/Common/Commons.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include "Game/Weapon/Boomerang/Boomerang.h"
#include "Game/Messenger/Scene/SceneMessages.h"
#include "Game/Player/PlayerUsually.h"
#include "Game/Particle/PlayerDust.h"

#include "Game/Fade/FadeManager.h"

#include "Libraries/MyLib/DebugString.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene">�V�[��</param>
Player::Player(Scene* scene)
	:
	Actor(scene)
	,m_playSceneCamera{}
	,m_rigidBody{}
	,m_usually{}
	,m_isGround{}
	,m_targetMarker{}
{

	m_dust = GetScene()->AddActor<PlayerDust>(GetScene());
	m_dust->GetTransform()->SetParent(GetTransform());
	m_rigidBody = AddComponent<RigidbodyComponent>(this);
	//�����蔻��̍쐬
	auto aABBCollider = AddComponent<AABB>(this, ColliderComponent::ColliderTag::AABB, CollisionType::COLLISION
	, Params::PLAYER_BOX_COLLIDER_SIZE
	, Params::PLAYER_SPHERE_COLLIDER_SIZE);


	//���f���̍쐬
	m_model =  GetScene()->AddActor<PlayerModel>(GetScene());
	//�e�q�֌W���Z�b�g
	m_model->GetTransform()->SetParent(GetTransform());


	//�������̓K�p
	GetTransform()->SetScale(Params::PLAYER_SCALE);
	GetTransform()->Translate(Params::PLAYER_POSITION);
	GetTransform()->SetRotate(Params::PLAYER_ROTATION);

	//�X�e�[�g�̍쐬
	m_stateMachine = std::make_unique<PlayerStateMachine>(this);

	//�A�j���[�V�����R���|�[�l���g�̒ǉ�
	m_animation  = AddComponent<AnimatorComponent>(this, std::make_unique<PlayerAnimationController>(this));
	
	m_usually = std::make_unique<PlayerUsually>(this);
	
	//������Ԃ�
	m_lastPosition = GetTransform()->GetPosition();




	//auto a = AddComponent<ParticleSystem>(this);

	//ParticleSystem::MainModule setting;
	//setting.LifeTime = { 2 };
	//setting.StartSpeed = 3;
	//setting.MinSize = { DirectX::SimpleMath::Vector3(0.1f,0.1f,0.1f) };
	//setting.MaxSize = { DirectX::SimpleMath::Vector3(0.8f,0.8f,0.8f) };
	//setting.MaxParticles = 10000;
	//setting.Duration = 0.1f;
	//auto box = std::make_shared<ShapeBox>(DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f) , 1);
	//auto cone = std::make_shared<ShapeCone>(3, 30, DirectX::SimpleMath::Vector3::Up);

	//ParticleSystem::Burst burst;
	//ParticleSystem::EasingOverLifeTime lifeEas;

	//lifeEas.SizeEasing = NakashiLib::Easing::EasingType::OutBounce;

	//ParticleSystem::EmissionModule emitter;
	//emitter.RateOverTime = 30;

	//ParticleSystem::ForceOverLifeTimeSpeed force;
	//force.ForcePower.Set(DirectX::SimpleMath::Vector3::Right);

	//a->SetMainModule(setting)
	//	->SetEasing(lifeEas);
	//a->SetEmission(emitter);
	//a->SetForce(force);
	//a->SetShape(cone);
	////a->AddBurst(0, 100);




}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Player::~Player()
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime"></param>
void Player::UpdateActor(const float& deltaTime)
{
	using namespace DirectX::SimpleMath;

	if (FadeManager::GetInstance()->GetIsFade())
	{
		return;
	}

	m_stateMachine->Update(deltaTime);
	m_usually->Update(deltaTime);
	//�ړ��ʂ̌v�Z
	Vector3 movement = GetTransform()->GetPosition() - m_lastPosition;
	//�ړ��ʂ���X�s�[�h�����߂�
	float speed = movement.Length() / deltaTime;

	m_animation->SetFloat("Move", speed);

	if (speed > 3)
	{
		//�p�[�e�B�N���̐����J�n
		m_dust->GetComponent<ParticleSystem>()->PlayParticle();
	}
	else
	{
		//�p�[�e�B�N���̐����̃X�g�b�v
		m_dust->GetComponent<ParticleSystem>()->StopParticle();

	}

	//���W�̕ۑ�
	m_lastPosition = GetTransform()->GetPosition();

	//// �f�o�b�O����\������
	auto debugString = CommonResources::GetInstance()->GetDebugString();
	debugString->AddString("X %f", speed);

	

}

/// <summary>
/// �����������ɌĂ΂��֐�
/// </summary>
/// <param name="collider">����̃R���C�_�[</param>
void Player::OnCollisionEnter(ColliderComponent* collider)
{
	switch (collider->GetActor()->GetObjectTag())
	{
		case Actor::ObjectTag::STAGE:
			Landing();
			break;
		case Actor::ObjectTag::BIRD_BULLET:
		{
			//�_���[�W�G�t�F�N�g

			//�ʒm
			SceneMessenger::GetInstance()->Notify(SceneMessageType::PLAYER_DAMAGE);

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
void Player::OnCollisionStay(ColliderComponent* collider)
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
void Player::OnCollisionExit(ColliderComponent* collider)
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
void Player::Landing()
{
	m_rigidBody->ResetGravity();
	m_isGround = true;
}

