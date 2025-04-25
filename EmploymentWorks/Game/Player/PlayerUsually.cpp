#include "pch.h"
#include "PlayerUsually.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"

#include "Libraries/WataLib/Camera/TPS_Camera.h"
#include "Game/Player/Player.h"
#include "Game/Player/State/PlayerStateMachine.h"
#include "Game/Observer/Messenger.h"
#include "Game/Params.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayerUsually::PlayerUsually()
	:
	m_commonResources{}
	,m_palyer{}
	,m_tpsCamera{}
	,m_gravity{}
	,m_isGetReady{false}
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerUsually::~PlayerUsually()
{
}


/// <summary>
/// �K�v�ȃ|�C���^�̒ǉ�
/// </summary>
/// <param name="player">�v���C��</param>
/// <param name="tpsCamera">TPS�J����</param>
void PlayerUsually::AddPointer(Player* player, WataLib::TPS_Camera* tpsCamera)
{
	m_palyer = player;

	m_tpsCamera = tpsCamera;
}

/// <summary>
/// ������
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
void PlayerUsually::Initialize(CommonResources* resources)
{
	m_commonResources = resources;


	m_gravity = Params::GRAVITY;

	//�C�x���g��Observer�Ƃ��ēo�^
	Messenger::GetInstance()->Attach(::MessageType::BoomerangGetReady, this);
	Messenger::GetInstance()->Attach(::MessageType::BoomerangGetReadyEnd, this);
}


/// <summary>
/// ����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
/// <param name="moveDirection">��������</param>
void PlayerUsually::Move(const float& elapsedTime, DirectX::SimpleMath::Vector3 moveDirection)
{
	//�v���C�����W�̎擾
	Vector3 position = m_palyer->GetPosition();
	
	position += moveDirection * elapsedTime * Params::PLAYER_MOVE_SPEED;

	//�v���C���̍��W��ݒ�
	m_palyer->SetPosition(position);


}

/// <summary>
/// ��]
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
/// <param name="moveDirection">��������</param>
void PlayerUsually::Rotation(const float& elapsedTime, DirectX::SimpleMath::Vector3 moveDirection)
{
	//�\���Ă��Ȃ��Ƃ�
	//if (m_palyer->GetPlayerStateMachine()->GetCurrentState() != m_palyer->GetPlayerStateMachine()->GetPlayerAttack())
	if (!m_isGetReady)
	{
		//�v���C���̉�]�̎擾
		Quaternion rotation = m_palyer->GetRotation();
		//�v���C���̐���
		Vector3 playerUsuallyForward = Vector3::Transform(Vector3::Forward, rotation);
		//��]�������߂�
		Vector3 rotationAxis = moveDirection.Cross(playerUsuallyForward);

		//�����O�̎�
		if (rotationAxis == Vector3::Zero)
		{
			return;
		}
		//���K��
		rotationAxis.Normalize();
		//���̔��]
		rotationAxis *= -1;
		//�p�x�����߂�
		float angle = Vector3::Distance(moveDirection, playerUsuallyForward);

		angle *= elapsedTime * Params::PLAYER_ROTATION_SPEED;
		//��]�����Z����
		rotation *= Quaternion::CreateFromAxisAngle(rotationAxis, angle);
		//��]��ݒ�
		m_palyer->SetRotation(rotation);
	}
	//�\���Ă���Ƃ�
	else
	{

		Quaternion rotation = m_tpsCamera->GetRotationX();


		m_palyer->SetRotation(rotation);

	}
}

/// <summary>
/// �ʒm���󂯎��֐�
/// </summary>
/// <param name="type">���</param>
/// <param name="datas">�f�[�^</param>
void PlayerUsually::Notify(const Telegram& telegram)
{
	
	//�C�x���g�̎��
	switch (telegram.messageType)
	{
		case ::MessageType::BoomerangGetReady:
			//�\���Ă���
			m_isGetReady = true;
			break;
		case ::MessageType::BoomerangGetReadyEnd:
			//�\���Ă��Ȃ�
			m_isGetReady = false;
			break;
		default:
			break;
	}
}






/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void PlayerUsually::Update(const float& elapsedTime)
{
	// �L�[�{�[�h�X�e�[�g���擾����
	DirectX::Keyboard::State key = DirectX::Keyboard::Get().GetState();



	Vector3 moveDirection = Vector3::Zero;

	if (key.IsKeyDown(Keyboard::Keyboard::W))
	{
		moveDirection.z--;
	}
	if (key.IsKeyDown(Keyboard::Keyboard::S))
	{
		moveDirection.z++;
	}
	if (key.IsKeyDown(Keyboard::Keyboard::A))
	{
		moveDirection.x--;
	}
	if (key.IsKeyDown(Keyboard::Keyboard::D))
	{
		moveDirection.x++;
	}

	//�J�����̌����Ă�����������Ƃɉ�]
	moveDirection = Vector3::Transform(moveDirection, m_tpsCamera->GetRotationX());
	moveDirection.Normalize();


	Move(elapsedTime,moveDirection);

	Rotation(elapsedTime, moveDirection);

	//�d��
	Vector3 position = m_palyer->GetPosition();

	position.y -= m_gravity * elapsedTime;

	m_palyer->SetPosition(position);

	Vector3 velocity = m_palyer->GetVelocity();

	velocity.y -= m_gravity * elapsedTime;




	//�A�j���[�V�������Ǘ�
	//�����Ă���
	if (moveDirection != Vector3::Zero)
	{
		//�v���C���A�j���[�V������Idle��ԂȂ�
		if (m_palyer->GetCurrentAnimationType() == "Idle")
		{
			//�A�j���[�V������ύX
			m_palyer->ChangeAnimation("Move");
		}
	}
	//�����Ă��Ȃ�
	else
	{
		//�v���C���A�j���[�V������Idle��ԂȂ�
		if (m_palyer->GetCurrentAnimationType() == "Move")
		{
			//�A�j���[�V������ύX
			m_palyer->ChangeAnimation("Idle");
		}

	}

}





