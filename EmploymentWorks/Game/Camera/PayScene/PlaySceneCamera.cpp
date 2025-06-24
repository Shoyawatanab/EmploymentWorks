#include "pch.h"
#include  "PlaySceneCamera.h"
#include "GameBase/Component/Components.h"
#include "Game/Camera/PayScene/PaySceneCameraState/PlaySceneCameraStateMachine.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene">�V�[��</param>
PlaySceneCamera::PlaySceneCamera(Scene* scene)
	:
	Camera(scene)
	,m_stateMachine{}
	, m_rotationX{}
	, m_rotationY{}
{


	SetEyePosition(DirectX::SimpleMath::Vector3(0,5,20));

	m_stateMachine = std::make_unique<PlaySceneCameraStateMachine>(this);

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlaySceneCamera::~PlaySceneCamera()
{

}


/// <summary>
/// �J�����̌ʍX�V����
/// </summary>
/// <param name="deltaTime"></param>
void PlaySceneCamera::UpdateCamera(const float& deltaTime)
{

	m_stateMachine->Update(deltaTime);

}


