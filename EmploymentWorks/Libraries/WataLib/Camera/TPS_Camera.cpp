/*
	@file	TPS_Camera.cpp
	@brief	TPS�J�����N���X
*/
#include "pch.h"
#include "TPS_Camera.h"
#include "Game/Screen.h"
#include "Game/Player/Player.h"
#include "Libraries/WataLib/Mouse.h"
#include "Game/Observer/Messenger.h"
#include <cassert>
#include <random>


const POINT MOUSESENSITIVITY = { static_cast<LONG> (0.001f),static_cast<LONG> (0.001f) };      // �}�E�X�̊��x
const int MAXANGLEY = 100;

const float EXPANSIOOSPEED = 0.7f;   //�g�厞�̃X�s�[�h

/// <summary>
/// �R���X�g���N�^
/// </summary>
WataLib::TPS_Camera::TPS_Camera()
	:
	m_view{},
	m_projection{},
	m_eye{},
	m_target{},
	m_up{ DirectX::SimpleMath::Vector3::UnitY },
	m_player{},
	m_angle{},
	m_mouseSensitivity{ 0.001f,0.001f },
	m_lerpTime{},
	m_moveEye{},
	m_zoomState{}
	,m_shakePosition{}
	,m_shaleTime{}
	,m_shakePower{}
{
	m_mouse = std::make_unique<WataLib::Mouse>();

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
WataLib::TPS_Camera::~TPS_Camera()
{


}

/// <summary>
/// ������
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
void WataLib::TPS_Camera::Initialize(CommonResources* resources)
{
	assert(resources);
	m_mouse->Initialize();
	m_angle = {0,0};
	m_zoomState = ZoomState::NONE;

	m_target = m_player->GetPosition() + Vector3(0, 1, 0);

	CalculateEyePosition();
	CalculateViewMatrix();
	CalculateProjectionMatrix();


	//���b�Z�[�W�N���X�ɓo�^
	Messenger::GetInstance()->Rigister(GameMessageType::BOOMERANG_GET_READY, this);
	Messenger::GetInstance()->Rigister(GameMessageType::BOOMERANG_GET_READY_END, this);
	Messenger::GetInstance()->Rigister(GameMessageType::CAMERA_SHAKE, this);

}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void WataLib::TPS_Camera::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	DirectX::Keyboard::State key = DirectX::Keyboard::Get().GetState();


	m_mouse->Update();

	// target�̈ʒu���X�V����
	m_target = m_player->GetPosition() + TARGET_OFFSET;

	m_angle.x -= static_cast<LONG>( m_mouse->GetDiffX());
	m_angle.y -= static_cast<LONG>( m_mouse->GetDiffY());

	//���̐���
	if (m_angle.y > ANGELE_UPPER_LIMIT)
	{
		m_angle.y = ANGELE_UPPER_LIMIT;
	}
	//��̐���
	if (m_angle.y < ANGELE_LOWER_LIMIT)
	{
		m_angle.y = ANGELE_LOWER_LIMIT;

	}


	//������
	m_moveEye = Vector3::Zero;

	switch (m_zoomState)
	{

		case WataLib::TPS_Camera::ZoomState::ZOOM_IN:
			//�����Ă������
			if (m_lerpTime < 1)
			{
				m_lerpTime += 0.1f * EXPANSIOOSPEED;
			}
			m_moveEye = Vector3::Lerp(Vector3::Zero, ZOOM_DIRECTION, m_lerpTime);
			break;
		case WataLib::TPS_Camera::ZoomState::ZOOM_OUT:
			//�����Ă������
			if (m_lerpTime > 0)
			{
				m_lerpTime -= 0.1f * EXPANSIOOSPEED;
				m_moveEye = Vector3::Lerp(Vector3::Zero, ZOOM_DIRECTION, m_lerpTime);
			}
			else
			{
				m_lerpTime = 0;
				m_moveEye = Vector3::Zero;
				m_zoomState = ZoomState::NONE;
			}
			break;
		default:
			break;
	}


	Shake(elapsedTime);

	// �J�������W���v�Z����
	CalculateEyePosition();
	// �r���[�s����X�V����
	CalculateViewMatrix();

	//���ʃx�N�g�������߂�



}

void WataLib::TPS_Camera::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	assert(&view);
	assert(&projection);
}

/// <summary>
// �r���[�s��̌v�Z
/// </summary>
void WataLib::TPS_Camera::CalculateViewMatrix()
{
	using namespace DirectX::SimpleMath;


	m_view = Matrix::CreateLookAt(m_eye + m_shakePosition, m_target + m_shakePosition, m_up);
}

/// <summary>
/// �v���W�F�N�V�����s��̌v�Z
/// </summary>
void WataLib::TPS_Camera::CalculateProjectionMatrix()
{
	using namespace DirectX::SimpleMath;


	// �E�B���h�E�T�C�Y
	const float width = static_cast<float>(Screen::WIDTH);
	const float height = static_cast<float>(Screen::HEIGHT);
	
	// ��ʏc����
	const float aspectRatio = width / height;

	m_projection = Matrix::CreatePerspectiveFieldOfView(
		FOV, aspectRatio, NEAR_PLANE, FAR_PLANE);
}

/// <summary>
/// �J�������W�̌v�Z
/// </summary>
void WataLib::TPS_Camera::CalculateEyePosition()
{

	using namespace DirectX::SimpleMath;


	//�v���C���̉�]�Ɏg�p
	Vector3 angleX = Vector3(0, m_angle.x * m_mouseSensitivity.x, 0);
	m_rotationX = Quaternion::CreateFromYawPitchRoll(angleX);

	//�}�E�X�̍�������p�x�̍쐬
	Vector3 angle =  Vector3(m_angle.y * m_mouseSensitivity.y, m_angle.x * m_mouseSensitivity.x, 0);

	Vector3 angle2 = Vector3(m_angle.y * m_mouseSensitivity.y, 0, 0);

	//�J�E�X�̈ړ��ʂ����]�𐶐�
	Quaternion Rotation = Quaternion::CreateFromYawPitchRoll(angle);
	//float a = Rotation.x;
	// ����̐i�s�����x�N�g��
	Vector3 forward = Vector3::Forward;

	// �J�������^�[�Q�b�g����ǂꂭ�炢����Ă��邩
	forward.y = CAMERA_HIGHT;
	forward.z = CAMERA_DISTANCE;




	// �^�[�Q�b�g�̌����Ă�������ɒǏ]����
	forward =   Vector3::Transform(forward, Rotation);
	m_moveEye = Vector3::Transform(m_moveEye, Rotation);

	m_moveEye += forward;

	m_moveEye += m_target;

	// �J�������W���v�Z����
	m_eye = m_moveEye;


	//���ʃx�N�g�������߂�
	m_forward = (m_target - m_eye);
	m_forward.Normalize();

}

void WataLib::TPS_Camera::AddPointer(Player* Player)
{

	m_player = Player;

}


/// <summary>
/// ��Ԃɓ�������
/// </summary>
void WataLib::TPS_Camera::Enter()
{

	m_angle = { 400,800 };

}


/// <summary>
/// ��Ԃ𔲂�����
/// </summary>
void WataLib::TPS_Camera::Exit()
{

}

/// <summary>
/// �ʒm���󂯎��֐�
/// </summary>
/// <param name="telegram">�f�[�^</param>
void WataLib::TPS_Camera::Notify(const Telegram<GameMessageType>& telegram)
{
	
	switch (telegram.messageType)
	{
		case GameMessageType::BOOMERANG_GET_READY:
			m_zoomState = ZoomState::ZOOM_IN;
			break;
		case GameMessageType::BOOMERANG_GET_READY_END:
			m_zoomState = ZoomState::ZOOM_OUT;
			break;
		case GameMessageType::CAMERA_SHAKE:
			
			m_shaleTime = SHAKETIME;
			m_isShake = true;

			m_shakePower = *static_cast<float*>(telegram.extraInfo);

			break;

		default:
			break;
	}

}

/// <summary>
/// ��ʂ̗h��
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void WataLib::TPS_Camera::Shake(const float& elapsedTime)
{

	if (!m_isShake)
	{
		return;
	}


	m_shaleTime -= elapsedTime;


	if (m_shaleTime <= 0.0f)
	{
		m_isShake = false;
		m_shakePosition = Vector3::Zero;
		return;
	}

	float power = (m_shaleTime / SHAKETIME) * m_shakePower;

	//	���S�ȃ����_�����n�[�h�E�F�A�I�ɐ������邽�߂̃N���X�̕ϐ�
	std::random_device seed;
	//	��L�̊��S�ȃ����_���͓��삪�x�����߁Aseed�l�̌���݂̂Ɏg�p����
	//	���udefault_random_engine�v��using�Łumt19937�v�ƂȂ��Ă���
	std::default_random_engine engine(seed());
	//	�������ė~���������_���͈̔͂�Distribution�ɔC����B�����0�`2PI
	std::uniform_real_distribution<> dist(-power, power);

	float x = static_cast<float>(dist(engine));
	float y = static_cast<float>(dist(engine));
	float z = static_cast<float>(dist(engine));
	
	m_shakePosition = Vector3(x, y, z);



}




