#include "pch.h"
#include "PlayerWalk.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"


#include "Game/Player/Player2.h"
#include "Game/Player/State/PlayerStateMachine.h"
#include "Game/Observer/Messenger.h"
#include "GameBase/Component/Components.h"
#include "Game/Params.h"
#include "Game/Camera/PayScene/PlaySceneCamera.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayerWalk::PlayerWalk(PlayerStateMachine* stateMachine, Player2* player)
	:
	m_stateMahine{stateMachine}
	, m_player{ player }
	,m_rigidbody{}
	,m_moveDirection{}
{

	m_rigidbody=  player->GetComponent<RigidbodyComponent>();

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerWalk::~PlayerWalk()
{
}



/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void PlayerWalk::Update(const float& deltatime)
{
	using namespace DirectX::SimpleMath;

	m_moveDirection = Vector3::Zero;

	//�ړ�
	Move(deltatime);

	//��]
	Rotate(deltatime);




}


/// <summary>
/// ��Ԃɓ�������
/// </summary>
void PlayerWalk::Enter()
{

	//�������̐ݒ�
	m_rigidbody->SetDeceleration(Params::GRAUND_FRICTION);


}

/// <summary>
/// ��Ԃ𔲂�����
/// </summary>
void PlayerWalk::Exit()
{
}

/// <summary>
/// �ړ�
/// </summary>
void PlayerWalk::Move(const float& deltatime)
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
	Quaternion rotationX =Quaternion::CreateFromYawPitchRoll( m_player->GetPlaySceneCamera()->GetRotationY(),0.0f,0.0f);
	//�J�����̉�]�ɉ����ĉ�]
	m_moveDirection = Vector3::Transform(m_moveDirection, rotationX);

	//�ړ�
	m_rigidbody->AddForce(m_moveDirection * moveSpeed);

}

void PlayerWalk::Rotate(const float& deltatime)
{
	using namespace DirectX::SimpleMath;

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
	//�l�����������͐��K��
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



