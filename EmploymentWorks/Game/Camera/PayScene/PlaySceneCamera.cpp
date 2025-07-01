#include "pch.h"
#include  "PlaySceneCamera.h"
#include "GameBase/Component/Components.h"
#include "PlaySceneCameraStateMachine.h"

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


	//�X�e�[�g�}�V�[���̍쐬
	m_stateMachine = std::make_unique<PlaySceneCameraStateMachine>(this);


}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlaySceneCamera::~PlaySceneCamera()
{
	ShowCursor(true);

}



/// <summary>
/// �J�����̌ʍX�V����
/// </summary>
/// <param name="deltaTime"></param>
void PlaySceneCamera::UpdateCamera(const float& deltaTime)
{
	//�X�e�[�g�}�V�[���̍X�V
	m_stateMachine->Update(deltaTime);

}


