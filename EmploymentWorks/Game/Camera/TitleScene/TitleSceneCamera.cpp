#include "pch.h"
#include "TitleSceneCamera.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="scene"></param>
TitleSceneCamera::TitleSceneCamera(Scene* scene)
	:
	Camera(scene)
	, m_angle{}
	
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
TitleSceneCamera::~TitleSceneCamera()
{
}

/// <summary>
/// �ʃJ�����̍X�V����
/// </summary>
/// <param name="deltaTime"></param>
void TitleSceneCamera::UpdateCamera(const float& deltaTime)
{
	using namespace DirectX::SimpleMath;

	//��]
	m_angle += ROTATION_SPEED * deltaTime;
	
	float x = DISTANCE_TO_TARGET.x * cosf(m_angle);
	
	float z = DISTANCE_TO_TARGET.z * sinf(m_angle);

	Vector3 eye = DirectX::SimpleMath::Vector3(x, DISTANCE_TO_TARGET.y, z);

	SetEyePosition(eye);
}
