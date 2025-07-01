#include "pch.h"
#include "PlaySceneCameraTPS.h"
#include "Game/Camera/PayScene/PlaySceneCamera.h"
#include "Game/Player/Player.h"
#include "GameBase/Component/Components.h"
#include "Game/Messenger/Scene/SceneMessages.h"

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
	,m_zoomState{}
	,m_zoomMovement{}
	,m_zoomTime{}
{

	//���b�Z���W���[�ɓo�^
	SceneMessenger::GetInstance()->Rigister(
		{
			SceneMessageType::PLAYER_GET_REDAY
			,SceneMessageType::PLAYER_GET_REDAY_END
		}
		, this
	);


}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlaySceneCameraTPS::~PlaySceneCameraTPS()
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime">�o�ߎ���</param>
void PlaySceneCameraTPS::Update(const float& deltaTime)
{
	using namespace DirectX;;
	using namespace DirectX::SimpleMath;

	//�}�E�X����
	MouseOperation();
	//�Y�[���̍X�V
	ZoomUpdate(deltaTime);
	//�^�[�Q�b�g
	Vector3 target = m_camera->GetTarget()->GetTransform()->GetWorldPosition() +  Vector3(0, 1, 0);
	//X����]�̌v�Z
	Quaternion rotateX = Quaternion::CreateFromAxisAngle(Vector3::UnitY, XMConvertToRadians(m_rotationX));
	//��]�̌v�Z
	Quaternion rotate = Quaternion::CreateFromYawPitchRoll(m_rotationY, m_rotationX, 0.0f);
	// �J�������^�[�Q�b�g����ǂꂭ�炢����Ă��邩
	Vector3 eye = Vector3::UnitZ * CAMERA_DISTANCE;
	//���_�̉�]
	eye = Vector3::Transform(eye, rotate);
	eye += target;

	//�Y�[�����̉�]
	Vector3 movemement = Vector3::Transform(m_zoomMovement, rotate);

	//�J�����ɃZ�b�g
	m_camera->SetEyePosition(eye + movemement);
	m_camera->SetTargetPosition(target);

	//���ʃx�N�g��
	Vector3 forward = target - eye;
	forward.Normalize();
	m_camera->SetForwardVector(forward);

}

/// <summary>
/// ��Ԃɂ͂�������
/// </summary>
void PlaySceneCameraTPS::Enter()
{
	//�����l�ݒ�
	SetCursorPos(MOUSE_POSITION.x,MOUSE_POSITION.y);
	m_rotationX = 0.0f;
	m_rotationY = 0.0f;
	m_zoomTime = 0.0f;
	m_zoomState = ZoomState::NONE;

	ShowCursor(false);

}

/// <summary>
/// ��Ԃ𔲂�����
/// </summary>
void PlaySceneCameraTPS::Exit()
{
	ShowCursor(true);

}

/// <summary>
/// �ʒm���󂯎��֐�
/// </summary>
/// <param name="type">�ʒm�̎��</param>
/// <param name="datas">�ǉ��f�[�^</param>
void PlaySceneCameraTPS::Notify(SceneMessageType type, void* datas)
{
	switch (type)
	{
		case SceneMessageType::PLAYER_GET_REDAY:
			m_zoomState = ZoomState::ZOOM_IN;
			m_zoomTime = 0.0f;
			break;
		case SceneMessageType::PLAYER_GET_REDAY_END:
			m_zoomState = ZoomState::ZOOM_OUT;
			m_zoomMovement = DirectX::SimpleMath::Vector3::Zero;
			m_zoomTime = 0.0f;

			break;

		default:
			break;
	}

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
	m_camera->SetRotationY(m_rotationY );
}

/// <summary>
/// �Y�[���̍X�V
/// </summary>
/// <param name="deltaTime">�o�ߎ���</param>
void PlaySceneCameraTPS::ZoomUpdate(const float& deltaTime)
{
	using namespace DirectX::SimpleMath;

	if (m_zoomState == ZoomState::NONE)
	{
		return;
	}

	//������
	m_zoomMovement = Vector3::Zero;

	//�i�s����
	float ratio = m_zoomTime / ZOOME_MAX_TIME;

	ratio = std::min(ratio, 1.0f);

	switch (m_zoomState)
	{
		case PlaySceneCameraTPS::ZoomState::NONE:
			break;
		case PlaySceneCameraTPS::ZoomState::ZOOM_IN:

			m_zoomMovement = Vector3::Lerp(
				Vector3::Zero, ZOOM_DIRECTION
				,ratio
				);

			break;
		case PlaySceneCameraTPS::ZoomState::ZOOM_OUT:
			m_zoomMovement = Vector3::Lerp(
				ZOOM_DIRECTION,Vector3::Zero
				, ratio
			);
			break;
		default:
			break;
	}


	m_zoomTime += deltaTime;
}

/// <summary>
/// ��ʂ̗h��
/// </summary>
/// <param name="deltaTime">�o�ߎ���</param>
void PlaySceneCameraTPS::Shake(const float& deltaTime)
{

	//using namespace DirectX::SimpleMath;
	//
	//if (!m_isShake)
	//{
	//	return;
	//}


	//m_shaleTime -= deltaTime;


	//if (m_shaleTime <= 0.0f)
	//{
	//	m_isShake = false;
	//	m_shakePosition = Vector3::Zero;
	//	return;
	//}

	//float power = (m_shaleTime / SHAKETIME) * m_shakePower;

	////	���S�ȃ����_�����n�[�h�E�F�A�I�ɐ������邽�߂̃N���X�̕ϐ�
	//std::random_device seed;
	////	��L�̊��S�ȃ����_���͓��삪�x�����߁Aseed�l�̌���݂̂Ɏg�p����
	////	���udefault_random_engine�v��using�Łumt19937�v�ƂȂ��Ă���
	//std::default_random_engine engine(seed());
	////	�������ė~���������_���͈̔͂�Distribution�ɔC����B�����0�`2PI
	//std::uniform_real_distribution<> dist(-power, power);

	//float x = static_cast<float>(dist(engine));
	//float y = static_cast<float>(dist(engine));
	//float z = static_cast<float>(dist(engine));

	//m_shakePosition = Vector3(x, y, z);


}
