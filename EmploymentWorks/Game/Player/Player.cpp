/*
	�N���X��     : Player
	����         : �v���C��
	�⑫�E���ӓ_ :
*/
#include "pch.h"
#include "Player.h"
#include "GameBase/Managers.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Params.h"
#include "Game/Player/State/PlayerStateMachine.h"
#include "Game/Component/Components.h"
#include "Game/Player/Model/PlayerModel.h"
#include "Game/Player/Animation/PlayerAnimationController.h"
#include "GameBase/Common/Commons.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include "Game/Weapon/Boomerang/Boomerang.h"
#include "Game/Messenger/Scene/SceneMessages.h"
#include "Game/Player/PlayerUsually.h"
#include "Game/Fade/FadeManager.h"


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
	,m_hp{Params::PLAYER_HP}
	,m_throwState{BoomerangThrowState::RIGHT}
{

	m_rigidBody = AddComponent<RigidbodyComponent>(this);
	//�����蔻��̍쐬
	AddComponent<AABB>(this,  CollisionType::COLLISION
	, Params::PLAYER_BOX_COLLIDER_SIZE
	, Params::PLAYER_SPHERE_COLLIDER_SIZE);

	//�ۉe
	AddComponent<RoundShadowComponent>(this, Params::PLAYER_SHADOW_RADIUS);



	m_picker = AddComponent<PickerComponent>(this, PickUpManager::PickUpType::PLAYER_PICKUP_WEAPON);
	m_picker->SetIsPickUp(true);
	m_picker->SetRecoverableFunction(std::bind(&Player::WeaponRecoverable, this));
	m_picker->SetUnrecoverableFunction(std::bind(&Player::WeaponUnrecoverable, this));

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
	//���̓R���|�[�l���g
	auto input = AddComponent<InputComponent>(this);
	input->Rigister({ DirectX::Keyboard::Keyboard::A
		,DirectX::Keyboard::Keyboard::W
		,DirectX::Keyboard::Keyboard::D
		,DirectX::Keyboard::Keyboard::S}
	, std::bind(&PlayerUsually::OnInput, m_usually.get(), std::placeholders::_1));


	//�ʒm���󂯎���ނ̐ݒ�
	SceneMessenger::GetInstance()->Rigister(
		{
			SceneMessageType::MOUSE_WHEEL_UP
			,SceneMessageType::MOUSE_WHEEL_DOWN
		}, this
	);
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
	//�ړ����̃A�j���[�V����
	m_animation->SetFloat("Move", speed);

	//���W�̕ۑ�
	m_lastPosition = GetTransform()->GetPosition();

	// �L�[�{�[�h�X�e�[�g�g���b�J�[���擾����
	const auto& kbTracker = CommonResources::GetInstance()->GetInputManager()->GetKeyboardTracker();

	if (kbTracker->released.F)
	{
		m_picker->TryPickUp();
	}

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
		case Actor::ObjectTag::BEAM:
		case Actor::ObjectTag::BIRD_BULLET:
		case Actor::ObjectTag::BOSS_ENEMY_PARTS:
		{
			//�_���[�W�G�t�F�N�g
			//�ʒm
			SceneMessenger::GetInstance()->Notify(SceneMessageType::PLAYER_DAMAGE);
			SceneMessenger::GetInstance()->Notify(SceneMessageType::TPS_CAMERA_SHAKE);
			AddDamage();
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
/// ���������ł���悤�ɂȂ���
/// </summary>
void Player::WeaponRecoverable()
{
	SceneMessenger::GetInstance()->Notify(SceneMessageType::PLAYER_PICKUP_POSSIBLE);
}

/// <summary>
/// ���������ł��Ȃ��Ȃ����Ƃ�
/// </summary>
void Player::WeaponUnrecoverable()
{
	SceneMessenger::GetInstance()->Notify(SceneMessageType::PLAYER_PICKUP_IMPOSSIBLE);

}

/// <summary>
/// �ʒm���ɌĂяo�����֐�
/// </summary>
/// <param name="type">�ʒm�̎��</param>
/// <param name="datas">�ǉ��f�[�^</param>
void Player::Notify(SceneMessageType type, void* datas)
{
	UNREFERENCED_PARAMETER(datas);
	switch (type)
	{	
		case SceneMessageType::MOUSE_WHEEL_UP:
			m_throwState = BoomerangThrowState::RIGHT;
			break;
		case SceneMessageType::MOUSE_WHEEL_DOWN:
			m_throwState = BoomerangThrowState::LEFT;
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

/// <summary>
/// �_���[�W��H������Ƃ�
/// </summary>
void Player::AddDamage()
{
	//HP�̌���
	m_hp--;
	//0�ȉ��ɂȂ�Ȃ��悤��
	m_hp = std::max(m_hp, 0);

	if (m_hp == 0)
	{
		//�Q�[���I�[�o�[�̒ʒm
		SceneMessenger::GetInstance()->Notify(SceneMessageType::GAME_OVER);
	}

}

