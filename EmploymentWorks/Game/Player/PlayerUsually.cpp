/*
	�N���X��     : PlayerUsually
	����         : �v���C���̏�ɏ����������̂̃N���X
	�⑫�E���ӓ_ :
*/
#include "pch.h"
#include "PlayerUsually.h"
#include "GameBase/Common/Commons.h"
#include "Libraries/MyLib/InputManager.h"
#include "Game/Player/Player.h"
#include "Game/Player/State/PlayerStateMachine.h"
#include "Game/Component/Components.h"
#include "Game/Params.h"
#include "Game/Camera/PlayScene/PlaySceneCamera.h"
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
	//���ʃ��\�[�X
	m_commonResources = CommonResources::GetInstance();
	//�d��
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


	//�ړ�
	Move(deltatime);

	//��]
	Rotate(deltatime);

	CheckMouseWheel();

	m_moveDirection = Vector3::Zero;


}

/// <summary>
/// �ʒm�󂯎��֐�
/// </summary>
/// <param name="type">�ʒm�̎��</param>
/// <param name="datas">�ǉ��f�[�^</param>
void PlayerUsually::Notify(SceneMessageType type, void* datas)
{
	UNREFERENCED_PARAMETER(datas);

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

	float moveSpeed = Params::PLAYER_MOVE_SPEED * deltatime;


	//�J�����̉��̉�]�������]�̌v�Z
	Quaternion rotationX =Quaternion::CreateFromYawPitchRoll(m_player->GetPlaySceneCamera()->GetRotationY(),0.0f,0.0f);
	//�J�����̉�]�ɉ����ĉ�]
	m_moveDirection = Vector3::Transform(m_moveDirection, rotationX);

	//�ړ�
	m_rigidbody->AddForce(m_moveDirection * moveSpeed);

}

/// <summary>
/// ��]
/// </summary>
/// <param name="deltatime">�o�ߎ���</param>
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

/// <summary>
/// �}�E�X�z�C�[���̃`�F�b�N
/// </summary>
void PlayerUsually::CheckMouseWheel()
{
	using namespace DirectX;

	const auto& state = m_commonResources->GetInputManager()->GetMouseState();

	int scrollWheelValue = state.scrollWheelValue;

	//��ɉ�]
	if (scrollWheelValue > 0)
	{
		SceneMessenger::GetInstance()->Notify(SceneMessageType::MOUSE_WHEEL_UP, nullptr);
	}
	//���ɉ�]
	else if (scrollWheelValue < 0)
	{

		SceneMessenger::GetInstance()->Notify(SceneMessageType::MOUSE_WHEEL_DOWN, nullptr);

	}
	//�}�E�X�z�C�[���̈ړ��l�̃��Z�b�g
	Mouse::Get().ResetScrollWheelValue();

}

/// <summary>
/// ���͎�
/// </summary>
/// <param name="key"></param>
void PlayerUsually::OnInput(const DirectX::Keyboard::Keys& key)
{
	using namespace DirectX;

	switch (key)
	{
		case Keyboard::W:
			m_moveDirection.z--;
			break;
		case Keyboard::S:
			m_moveDirection.z++;
			break;
		case Keyboard::A:
			m_moveDirection.x--;
			break;
		case Keyboard::D:
			m_moveDirection.x++;
			break;
		default:
			break;
	}

}


