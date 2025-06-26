#include "pch.h"
#include "Camera.h"
#include "GameBase/Component/Components.h"
#include "GameBase/Screen.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene">�V�[��</param>
Camera::Camera(Scene* scene)
	:
	Actor(scene)
	,m_eye{DirectX::SimpleMath::Vector3::UnitZ}
	,m_target{DirectX::SimpleMath::Vector3::Zero}
	,m_up{DirectX::SimpleMath::Vector3::Up}
	,m_view{}
	,m_projection{}
	,m_forwardVector{ DirectX::SimpleMath::Vector3::Forward }

{

	using namespace DirectX::SimpleMath;

	//�r���[�s��̌v�Z
	m_view = Matrix::CreateLookAt(m_eye, m_target, m_up);


	//�v���W�F�N�V�����s��v�Z
	RECT rect{ 0,0,Screen::WIDTH,Screen::HEIGHT };
	using namespace DirectX;
	m_projection = Matrix::CreatePerspectiveFieldOfView(
		XMConvertToRadians(45.0f),
		static_cast<float>(rect.right) / static_cast<float>(rect.bottom),
		0.1f, 150.0f
	);



}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Camera::~Camera()
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime"></param>
void Camera::Update(const float& deltaTime)
{

	
	//�J�����̌ʍX�V����
	UpdateCamera(deltaTime);

	//�r���[�s��̌v�Z
	CalculateViewMatrix();

}



/// <summary>
/// �r���[�s��̌v�Z
/// </summary>
void Camera::CalculateViewMatrix()
{

	using namespace DirectX::SimpleMath;

	//�r���[�s��̌v�Z
	m_view = Matrix::CreateLookAt(m_eye, m_target, m_up);

}
