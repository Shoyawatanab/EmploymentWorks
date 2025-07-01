#include "pch.h"
#include "PlaySceneCameraStop.h"
#include "Game/Camera/PayScene/PlaySceneCamera.h"
#include "GameBase/Component/Components.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="stateMachine">�X�e�[�g�}�V�[��</param>
/// <param name="camera">�J����</param>
PlaySceneCameraStop::PlaySceneCameraStop(PlaySceneCameraStateMachine* stateMachine, PlaySceneCamera* camera)
	:
	m_stateMAchine{ stateMachine }
	, m_camera{ camera }
{



}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlaySceneCameraStop::~PlaySceneCameraStop()
{



}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime">�o�ߎ���</param>
void PlaySceneCameraStop::Update(const float& deltaTime)
{

	UNREFERENCED_PARAMETER(deltaTime);

}

/// <summary>
/// ��Ԃɓ�������
/// </summary>
void PlaySceneCameraStop::Enter()
{
	using namespace DirectX::SimpleMath;


}

/// <summary>
/// ��Ԃ𔲂�����
/// </summary>
void PlaySceneCameraStop::Exit()
{
}
