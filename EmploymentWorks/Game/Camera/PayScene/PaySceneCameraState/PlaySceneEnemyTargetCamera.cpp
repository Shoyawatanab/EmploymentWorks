#include "pch.h"
#include "PlaySceneEnemyTargetCamera.h"
#include "Game/Camera/PayScene/PlaySceneCamera.h"
#include "GameBase/Component/Components.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="stateMachine">�X�e�[�g�}�V�[��</param>
/// <param name="camera">�J����</param>
PlaySceneEnemyTargetCamera::PlaySceneEnemyTargetCamera(PlaySceneCameraStateMachine* stateMachine, PlaySceneCamera* camera)
	:
	m_stateMAchine{stateMachine}
	,m_camera{camera}
{



}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlaySceneEnemyTargetCamera::~PlaySceneEnemyTargetCamera()
{



}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime">�o�ߎ���</param>
void PlaySceneEnemyTargetCamera::Update(const float& deltaTime)
{

	UNREFERENCED_PARAMETER(deltaTime);

}

/// <summary>
/// ��Ԃɓ�������
/// </summary>
void PlaySceneEnemyTargetCamera::Enter()
{
	using namespace DirectX::SimpleMath;

	//�^�[�Q�b�g�̕ύX
	m_camera->SetTargetPosition(m_camera->GetTarget()->GetTransform()->GetWorldPosition());

	Vector3 forward;

	forward = Vector3::Transform(EYE_DIRECTION, m_camera->GetTransform()->GetRotate());

	m_camera->SetEyePosition(m_camera->GetTarget()->GetTransform()->GetWorldPosition() + forward);

}

/// <summary>
/// ��Ԃ𔲂�����
/// </summary>
void PlaySceneEnemyTargetCamera::Exit()
{
}
