/*
	@file	FPS_Camera.cpp
	@brief	FPS�J�����N���X
*/
#include "pch.h"
#include "FPS_Camera.h"
#include "Game/Screen.h"

#include "Game/Object/Player/Player.h"
#include "Libraries/MyLib/Mouse.h"

//-------------------------------------------------------------------
// �R���X�g���N�^
//-------------------------------------------------------------------
mylib::FPS_Camera::FPS_Camera(
	const DirectX::SimpleMath::Vector3& eye,
	const DirectX::SimpleMath::Vector3& target,
	const DirectX::SimpleMath::Vector3& up
)
	:
	m_view{},
	m_projection{},
	m_eye{eye  },
	m_target{target  },
	m_up{ up },
	m_angle{}
{
	m_mouse = new mylib::Mouse;
	m_mouse->Initialize();

}

mylib::FPS_Camera::~FPS_Camera()
{
	delete m_mouse;

}


void mylib::FPS_Camera::Initialize()
{
	CalculateViewMatrix();
	CalculateProjectionMatrix();

	m_mouse->Initialize();
	m_angle = DirectX::SimpleMath::Vector2::Zero;


}

void mylib::FPS_Camera::Update(const float& elapsedTime)
{
	using namespace DirectX::SimpleMath;


	// �Â�eye��ێ�����
	DirectX::SimpleMath::Vector3 oldEye = m_eye;

	// eye�̈ʒu���X�V����
	m_eye = m_player->GetPlayerEyePosition();

	//m_eye = m_player->GetPos() + DirectX::SimpleMath::Vector3(0,3,5);

	// �ړ��x�N�g�������߂�
	DirectX::SimpleMath::Vector3 velocity = m_eye - oldEye;

	// target�̈ʒu���X�V����
	//m_target += velocity;

	m_mouse->Update();



	m_angle.x -= m_mouse->GetDiffX() * 0.002f;
	m_angle.y -= m_mouse->GetDiffY() * 0.002f;


	if (m_angle.y > 1.5f)
	{
		m_angle.y = 1.5f;
	}
	else if (m_angle.y < -1.5)
	{
		m_angle.y = -1.5;
	}

	Quaternion Rotate =  Quaternion::CreateFromYawPitchRoll(m_angle.x, m_angle.y, 0.0f);

	Vector3 forward = Vector3::Transform(Vector3::Forward, Rotate );

	m_target = m_eye + forward;

	//�v���C���̉�]�ŉ��̉�]���~��������
	Quaternion RotateX = Quaternion::CreateFromYawPitchRoll(m_angle.x, 0, 0);

	m_player->SetCameraRotate(Rotate);

	// �r���[�s����X�V����
	CalculateViewMatrix();

}

void mylib::FPS_Camera::Enter()
{
	m_angle = DirectX::SimpleMath::Vector2::Zero;

}

void mylib::FPS_Camera::Exit()
{
}

//-------------------------------------------------------------------
// �r���[�s����v�Z����
//-------------------------------------------------------------------
void mylib::FPS_Camera::CalculateViewMatrix()
{
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_eye, m_target, m_up);
}

//-------------------------------------------------------------------
// �v���W�F�N�V�����s����v�Z����
//-------------------------------------------------------------------
void mylib::FPS_Camera::CalculateProjectionMatrix()
{
	// �E�B���h�E�T�C�Y
	const float width = static_cast<float>(Screen::WIDTH);
	const float height = static_cast<float>(Screen::HEIGHT);
	
	// ��ʏc����
	const float aspectRatio = width / height;

	m_projection = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		FOV, aspectRatio, NEAR_PLANE, FAR_PLANE);
}

void mylib::FPS_Camera::RegistrationInformation(Player* Player)
{

	m_player = Player;

}
