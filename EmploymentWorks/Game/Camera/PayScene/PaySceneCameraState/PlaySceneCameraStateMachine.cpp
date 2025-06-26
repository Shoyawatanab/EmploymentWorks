#include "pch.h"
#include "PlaySceneCameraStateMachine.h"
#include "Game/Camera/PayScene/PaySceneCameraState/PaySceneCameraStates.h"
#include "Game/Messenger/Scene/SceneMessages.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="camera"></param>
PlaySceneCameraStateMachine::PlaySceneCameraStateMachine(PlaySceneCamera* camera)
{
	//�e�X�e�[�g�̒ǉ�
	AddState(PaySceneCameraState::TPS, std::make_unique<PlaySceneCameraTPS>(this,camera));
	AddState(PaySceneCameraState::ENEMY_TARGET, std::make_unique<PlaySceneEnemyTargetCamera>(this,camera));

	//�����X�e�[�g�̐ݒ�
	SetStartState(PaySceneCameraState::TPS);

	//���b�Z���W���[�ɓo�^
	SceneMessenger::GetInstance()->Rigister(
		{
			SceneMessageType::BOSS_DEFEATED
		}, this
	);

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlaySceneCameraStateMachine::~PlaySceneCameraStateMachine()
{
}

/// <summary>
/// �ʒm���󂯎��֐�
/// </summary>
/// <param name="type">�ʒm�̎��</param>
/// <param name="datas">�ǉ��f�[�^</param>
void PlaySceneCameraStateMachine::Notify(SceneMessageType type, void* datas)
{
	switch (type)
	{
		case SceneMessageType::BOSS_DEFEATED:
			ChangeState(PaySceneCameraState::ENEMY_TARGET);
			break;
		default:
			break;
	}
}
