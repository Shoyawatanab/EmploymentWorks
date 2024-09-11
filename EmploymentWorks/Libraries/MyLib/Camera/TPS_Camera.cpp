/*
	@file	TPS_Camera.cpp
	@brief	TPS�J�����N���X
*/
#include "pch.h"
#include "TPS_Camera.h"
#include "Game/Screen.h"
#include "Game/Object/Player/Player.h"
#include "Libraries/MyLib/Mouse.h"

const POINT MOUSESENSITIVITY = { 0.001f,0.001f };      // �}�E�X�̊��x
const int MAXANGLEY = 100;

const float EXPANSIOOSPEED = 0.7f;   //�g�厞�̃X�s�[�h

//-------------------------------------------------------------------
// �R���X�g���N�^
//-------------------------------------------------------------------
mylib::TPS_Camera::TPS_Camera(Player* player)
	:
	m_view{},
	m_projection{},
	m_eye{},
	m_target{},
	m_up{ DirectX::SimpleMath::Vector3::UnitY },
	m_player{player},
	m_angle{},
	m_mouseSensitivity{ 0.001f,0.001f },
	m_lerpTime{},
	m_moveEye{},
	m_zoomState{ ZoomState::None }
{
	m_mouse = new mylib::Mouse;
	m_mouse->Initialize();

}


void mylib::TPS_Camera::Initialize()
{

	m_mouse->Initialize();
	m_angle = {0,0};

	m_target = m_player->GetPosition();

	CalculateEyePosition();
	CalculateViewMatrix();
	CalculateProjectionMatrix();

}

//-------------------------------------------------------------------
// �X�V����
//-------------------------------------------------------------------
void mylib::TPS_Camera::Update(const float& elapsedTime)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	DirectX::Keyboard::State key = DirectX::Keyboard::Get().GetState();


	m_mouse->Update(elapsedTime);

	// target�̈ʒu���X�V����
	m_target = m_player->GetPosition();

	m_angle.x -= m_mouse->GetDiffX();
	m_angle.y -= m_mouse->GetDiffY();

	//���̐���
	if (m_angle.y > 2100)
	{
		m_angle.y = 2100;
	}
	//��̐���
	if (m_angle.y < -950)
	{
		m_angle.y = -950;
	}
	if (key.IsKeyDown(Keyboard::Keyboard::Space))
	{
		m_zoomState = ZoomState::ZoomIn;
	}

	if (key.IsKeyUp(Keyboard::Keyboard::Space) && m_zoomState == ZoomState::ZoomIn)
	{
		m_zoomState = ZoomState::ZoomOut;
	}

	Vector3 direction = Vector3::Zero;
	switch (m_zoomState)
	{
		case mylib::TPS_Camera::ZoomState::None:
			break;
		case mylib::TPS_Camera::ZoomState::ZoomIn:
			//�����Ă������
			direction = m_target - m_eye;
			direction.Normalize();
			direction *= 4;
			if (m_lerpTime < 1)
			{
				m_lerpTime += 0.1f * EXPANSIOOSPEED;
			}
			m_moveEye = Vector3::Lerp(Vector3::Zero, direction, m_lerpTime);
			break;
		case mylib::TPS_Camera::ZoomState::ZoomOut:
			//�����Ă������
			direction = m_target - m_eye;
			direction.Normalize();
			direction *= 2;
			if (m_lerpTime > 0)
			{
				m_lerpTime -= 0.1f * EXPANSIOOSPEED;
				m_moveEye = Vector3::Lerp(Vector3::Zero, direction, m_lerpTime);
			}
			else
			{
				m_lerpTime = 0;
				m_moveEye = Vector3::Zero;
				m_zoomState = ZoomState::None;
			}
			break;
		default:
			break;
	}




	// �J�������W���v�Z����
	CalculateEyePosition();
	// �r���[�s����X�V����
	CalculateViewMatrix();
}

//-------------------------------------------------------------------
// �r���[�s����v�Z����
//-------------------------------------------------------------------
void mylib::TPS_Camera::CalculateViewMatrix()
{
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_eye + m_moveEye, m_target, m_up);
}

//-------------------------------------------------------------------
// �v���W�F�N�V�����s����v�Z����
//-------------------------------------------------------------------
void mylib::TPS_Camera::CalculateProjectionMatrix()
{
	// �E�B���h�E�T�C�Y
	const float width = static_cast<float>(Screen::WIDTH);
	const float height = static_cast<float>(Screen::HEIGHT);
	
	// ��ʏc����
	const float aspectRatio = width / height;

	m_projection = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		FOV, aspectRatio, NEAR_PLANE, FAR_PLANE);
}

//-------------------------------------------------------------------
// �J�������W���v�Z����
//-------------------------------------------------------------------
void mylib::TPS_Camera::CalculateEyePosition()
{
	DirectX::SimpleMath::Vector3 angleX = DirectX::SimpleMath::Vector3(0, m_angle.x * m_mouseSensitivity.x, 0);
	m_rotationX = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(angleX);

	//�}�E�X�̍�������p�x�̍쐬
	DirectX::SimpleMath::Vector3 angle = DirectX::SimpleMath::Vector3(m_angle.y * m_mouseSensitivity.y, m_angle.x * m_mouseSensitivity.x, 0);
	DirectX::SimpleMath::Quaternion Rotation = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(angle);
	//float a = Rotation.x;
	// ����̐i�s�����x�N�g��
	DirectX::SimpleMath::Vector3 forward = DirectX::SimpleMath::Vector3::Forward;

	// �J�������^�[�Q�b�g����ǂꂭ�炢����Ă��邩
	forward.y = CAMERA_HIGHT;
	forward.z = CAMERA_DISTANCE;

	m_player->SetCameraRotate(m_rotationX);


	// �^�[�Q�b�g�̌����Ă�������ɒǏ]����
	forward = DirectX::SimpleMath::Vector3::Transform(forward, Rotation);
	// �J�������W���v�Z����
	m_eye = m_target + forward;
}


void mylib::TPS_Camera::Enter()
{

	m_angle = { 400,800 };

}


void mylib::TPS_Camera::Exit()
{

}



