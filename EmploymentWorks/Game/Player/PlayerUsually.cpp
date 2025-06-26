#include "pch.h"
#include "PlayerUsually.h"
#include "GameBase/Common/Commons.h"
#include "Libraries/MyLib/InputManager.h"


#include "Game/Player/Player.h"
#include "Game/Player/State/PlayerStateMachine.h"
#include "GameBase/Component/Components.h"
#include "Game/Params.h"
#include "Game/Camera/PayScene/PlaySceneCamera.h"
#include "Game/Params.h"
#include "Game/Messenger/Scene/SceneMessages.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayerUsually::PlayerUsually(Player* player)
	:
	m_player{ player }
	,m_rigidbody{}
	,m_moveDirection{}
	,m_isGetReady{false}
{

	m_rigidbody=  player->GetComponent<RigidbodyComponent>();
	m_rigidbody->SetDeceleration(Params::GRAUND_FRICTION);


	SceneMessenger::GetInstance()->Rigister(
		{
			SceneMessageType::PLAYER_GET_REDAY
			,SceneMessageType::PLAYER_GET_REDAY_END
		}
		, this);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerUsually::~PlayerUsually()
{
}



/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void PlayerUsually::Update(const float& deltatime)
{
	using namespace DirectX::SimpleMath;

	m_moveDirection = Vector3::Zero;

	//�ړ�
	Move(deltatime);

	//��]
	Rotate(deltatime);




}

/// <summary>
/// �ʒm�󂯎��֐�
/// </summary>
/// <param name="type">�ʒm�̎��</param>
/// <param name="datas">�ǉ��f�[�^</param>
void PlayerUsually::Notify(SceneMessageType type, void* datas)
{
	switch (type)
	{
		case SceneMessageType::PLAYER_GET_REDAY:
			m_isGetReady = true;
			break;
		case SceneMessageType::PLAYER_GET_REDAY_END:
			m_isGetReady = false;
			break;
		default:
			break;
	}

}


/// <summary>
/// �ړ�
/// </summary>
void PlayerUsually::Move(const float& deltatime)
{

	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	// �L�[�{�[�h�X�e�[�g���擾����
	DirectX::Keyboard::State key = DirectX::Keyboard::Get().GetState();

	Transform* transform = m_player->GetTransform();

	float moveSpeed = Params::PLAYER_MOVE_SPEED * deltatime;


	if (key.IsKeyDown(Keyboard::Keyboard::W))
	{
		m_moveDirection.z--;
	}
	if (key.IsKeyDown(Keyboard::Keyboard::S))
	{
		m_moveDirection.z++;
	}
	if (key.IsKeyDown(Keyboard::Keyboard::A))
	{
		m_moveDirection.x--;
	}
	if (key.IsKeyDown(Keyboard::Keyboard::D))
	{
		m_moveDirection.x++;
	}

	//�J�����̉��̉�]�������]�̌v�Z
	Quaternion rotationX =Quaternion::CreateFromYawPitchRoll(m_player->GetPlaySceneCamera()->GetRotationY(),0.0f,0.0f);
	//�J�����̉�]�ɉ����ĉ�]
	m_moveDirection = Vector3::Transform(m_moveDirection, rotationX);

	//�ړ�
	m_rigidbody->AddForce(m_moveDirection * moveSpeed);

}

void PlayerUsually::Rotate(const float& deltatime)
{
	using namespace DirectX::SimpleMath;

	if (!m_isGetReady)
	{
		Quaternion rotate = m_player->GetTransform()->GetRotate();
		//���ʃx�N�g���̎擾
		Vector3 playerForward = m_player->GetTransform()->GetForwardVector();
		//��]�������߂�
		Vector3 rotationAxis = m_moveDirection.Cross(playerForward);
		//�����Z���Ȃ�
		if (rotationAxis == Vector3::Zero)
		{
			return;
		}

		//�l�����������͐��K�����Ȃ�
		if (m_moveDirection.LengthSquared() > 0.0001f)
		{
			m_moveDirection.Normalize();
		}

		//���̔��]
		rotationAxis *= -1;
		//�p�x�����߂�
		float angle = Vector3::Distance(m_moveDirection, playerForward);

		angle *= deltatime * Params::PLAYER_ROTATION_SPEED;
		//��]�����Z����
		Quaternion rotation = Quaternion::CreateFromAxisAngle(rotationAxis, angle);

		m_player->GetTransform()->SetRotate(m_player->GetTransform()->GetRotate() * rotation);
	}
	else
	{

		Quaternion rotationX = Quaternion::CreateFromYawPitchRoll(m_player->GetPlaySceneCamera()->GetRotationY() + DirectX::XM_PI, 0.0f, 0.0f);
		m_player->GetTransform()->SetRotate(rotationX);
	}

}



