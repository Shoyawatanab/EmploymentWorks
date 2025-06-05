#include "pch.h"
#include "PlaySceneCameraTPS.h"
#include "Game/Camera/PayScene/PlaySceneCamera.h"
#include "Game/Player/Player2.h"
#include "GameBase/Component/Components.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="stateMachine">�X�e�[�g�}�V�[��</param>
/// <param name="camera">�J����</param>
PlaySceneCameraTPS::PlaySceneCameraTPS(PlaySceneCameraStateMachine* stateMachine, PlaySceneCamera* camera)
	:
	m_camera{camera}
	,m_stateMAchine{stateMachine}
	,m_rotationX{}
	,m_rotationY{}
	,m_forward{DirectX::SimpleMath::Vector3::Forward}
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlaySceneCameraTPS::~PlaySceneCameraTPS()
{
}

void PlaySceneCameraTPS::Update(const float& elapsedTime)
{
	using namespace DirectX;;
	using namespace DirectX::SimpleMath;

	//�}�E�X����
	MouseOperation();
	
	Vector3 target = m_camera->GetPlayer()->GetTransform()->GetWorldPosition() +  Vector3(0, 1, 0);

	//X����]�̌v�Z
	Quaternion rotateX = Quaternion::CreateFromAxisAngle(Vector3::UnitY, XMConvertToRadians(m_rotationX));
	//��]�̌v�Z
	Quaternion rotate = Quaternion::CreateFromYawPitchRoll(m_rotationY, m_rotationX, 0.0f);
	// �J�������^�[�Q�b�g����ǂꂭ�炢����Ă��邩
	Vector3 eye = Vector3::UnitZ * CAMERA_DISTANCE;
	//���_�̉�]
	eye = Vector3::Transform(eye, rotate);

	eye += target;

	m_camera->SetEyePosition(eye);
	m_camera->SetTargetPosition(target);

}

void PlaySceneCameraTPS::Enter()
{
	//�����l�ݒ�
	SetCursorPos(MOUSE_POSITION.x,MOUSE_POSITION.y);

}

void PlaySceneCameraTPS::Exit()
{
}

/// <summary>
/// �}�E�X����
/// </summary>
void PlaySceneCameraTPS::MouseOperation()
{

	using namespace DirectX;
	using namespace DirectX::SimpleMath;
	//�}�E�X���W�ϐ�
	POINT mousePosition;
	//�}�E�X���W�̎擾
	GetCursorPos(&mousePosition);
	//���������߂�
	Vector2 diff;
	diff.x = MOUSE_POSITION.x - mousePosition.x;
	diff.y = MOUSE_POSITION.y - mousePosition.y;
	//�ړ��ʂ̉��Z
	m_rotationX += diff.y * MOUSE_SENSITIVITY;
	m_rotationY += diff.x * MOUSE_SENSITIVITY;

	//�����l�ݒ�
	SetCursorPos(MOUSE_POSITION.x, MOUSE_POSITION.y);
	//��̐���
	if (m_rotationX >= ROTATE_LIMIT)
	{
		m_rotationX = ROTATE_LIMIT;
	}
	//���̐���
	if (m_rotationX <= -ROTATE_LIMIT)
	{
		m_rotationX = -ROTATE_LIMIT;
	}

	//�v���C�J�����ɃZ�b�g
	m_camera->SetRotationX(m_rotationX);
	m_camera->SetRotationY(m_rotationY);
}
