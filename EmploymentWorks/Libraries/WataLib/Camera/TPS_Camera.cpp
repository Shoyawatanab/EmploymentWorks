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

using namespace DirectX;
using namespace DirectX::SimpleMath;


const POINT MOUSESENSITIVITY = { static_cast<LONG> (0.001f),static_cast<LONG> (0.001f) };      // �}�E�X�̊��x
const int MAXANGLEY = 100;

const float EXPANSIOOSPEED = 0.7f;   //�g�厞�̃X�s�[�h

//-------------------------------------------------------------------
// �R���X�g���N�^
//-------------------------------------------------------------------
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
{
	m_mouse = std::make_unique<WataLib::Mouse>();

}

WataLib::TPS_Camera::~TPS_Camera()
{
}


void WataLib::TPS_Camera::Initialize(CommonResources* resources)
{

	m_mouse->Initialize();
	m_angle = {0,0};
	m_zoomState = ZoomState::None;

	m_target = m_player->GetPosition() + Vector3(0, 1, 0);

	CalculateEyePosition();
	CalculateViewMatrix();
	CalculateProjectionMatrix();


	//�C�x���g��Observer�Ƃ��ēo�^

	Messenger::Attach(EventParams::EventType::BoomerangGetReady, this);
	Messenger::Attach(EventParams::EventType::BoomerangGetReadyEnd, this);

}

//-------------------------------------------------------------------
// �X�V����
//-------------------------------------------------------------------
void WataLib::TPS_Camera::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	DirectX::Keyboard::State key = DirectX::Keyboard::Get().GetState();


	m_mouse->Update();

	// target�̈ʒu���X�V����
	m_target = m_player->GetPosition() + Vector3(0,1,0);

	m_angle.x -= static_cast<LONG>( m_mouse->GetDiffX());
	m_angle.y -= static_cast<LONG>( m_mouse->GetDiffY());

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


	Vector3 direction = Vector3(0.2, 0, -1);
	//������
	m_moveEye = Vector3::Zero;

	switch (m_zoomState)
	{
		case WataLib::TPS_Camera::ZoomState::None:
			break;
		case WataLib::TPS_Camera::ZoomState::ZoomIn:
			//�����Ă������
			if (m_lerpTime < 1)
			{
				m_lerpTime += 0.1f * EXPANSIOOSPEED;
			}
			m_moveEye = Vector3::Lerp(Vector3::Zero, direction, m_lerpTime);
			break;
		case WataLib::TPS_Camera::ZoomState::ZoomOut:
			//�����Ă������
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

	//���ʃx�N�g�������߂�



}

void WataLib::TPS_Camera::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
}

//-------------------------------------------------------------------
// �r���[�s����v�Z����
//-------------------------------------------------------------------
void WataLib::TPS_Camera::CalculateViewMatrix()
{
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_eye, m_target, m_up);
}

//-------------------------------------------------------------------
// �v���W�F�N�V�����s����v�Z����
//-------------------------------------------------------------------
void WataLib::TPS_Camera::CalculateProjectionMatrix()
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
void WataLib::TPS_Camera::CalculateEyePosition()
{
	//�v���C���̉�]�Ɏg�p
	DirectX::SimpleMath::Vector3 angleX = DirectX::SimpleMath::Vector3(0, m_angle.x * m_mouseSensitivity.x, 0);
	m_rotationX = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(angleX);

	//�}�E�X�̍�������p�x�̍쐬
	DirectX::SimpleMath::Vector3 angle = DirectX::SimpleMath::Vector3(m_angle.y * m_mouseSensitivity.y, m_angle.x * m_mouseSensitivity.x, 0);

	DirectX::SimpleMath::Vector3 angle2 = DirectX::SimpleMath::Vector3(m_angle.y * m_mouseSensitivity.y, 0, 0);

	//�J�E�X�̈ړ��ʂ����]�𐶐�
	DirectX::SimpleMath::Quaternion Rotation = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(angle);
	//float a = Rotation.x;
	// ����̐i�s�����x�N�g��
	DirectX::SimpleMath::Vector3 forward = DirectX::SimpleMath::Vector3::Forward;

	// �J�������^�[�Q�b�g����ǂꂭ�炢����Ă��邩
	forward.y = CAMERA_HIGHT;
	forward.z = CAMERA_DISTANCE;




	// �^�[�Q�b�g�̌����Ă�������ɒǏ]����
	forward = DirectX::SimpleMath::Vector3::Transform(forward, Rotation);
	m_moveEye = DirectX::SimpleMath::Vector3::Transform(m_moveEye, Rotation);

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



void WataLib::TPS_Camera::Enter()
{

	m_angle = { 400,800 };

}


void WataLib::TPS_Camera::Exit()
{

}

void WataLib::TPS_Camera::Notify(EventParams::EventType type, void* datas)
{

	switch (type)
	{
		case EventParams::EventType::BoomerangGetReady:
			m_zoomState = ZoomState::ZoomIn;
			break;
		case EventParams::EventType::BoomerangGetReadyEnd:
			m_zoomState = ZoomState::ZoomOut;
			break;
		default:
			break;
	}

}




