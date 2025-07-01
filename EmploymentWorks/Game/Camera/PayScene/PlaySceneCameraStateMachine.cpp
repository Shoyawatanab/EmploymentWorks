#include "pch.h"
#include "PlaySceneCameraStateMachine.h"
#include "PaySceneCameraStates.h"
#include "Game/Messenger/Scene/SceneMessages.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="camera"></param>
PlaySceneCameraStateMachine::PlaySceneCameraStateMachine(PlaySceneCamera* camera)
{
	//�e�X�e�[�g�̒ǉ�
	AddState(PlaySceneCameraState::TPS, std::make_unique<PlaySceneCameraTPS>(this,camera));
	AddState(PlaySceneCameraState::ENEMY_TARGET, std::make_unique<PlaySceneEnemyTargetCamera>(this,camera));
	AddState(PlaySceneCameraState::STOP, std::make_unique<PlaySceneCameraStop>(this,camera));

	//�����X�e�[�g�̐ݒ�
	SetStartState(PlaySceneCameraState::TPS);

	//���b�Z���W���[�ɓo�^
	SceneMessenger::GetInstance()->Rigister(
		{
			SceneMessageType::BOSS_DEFEATED
			,SceneMessageType::GAME_OVER
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
			ChangeState(PlaySceneCameraState::ENEMY_TARGET);
			break;
		case SceneMessageType::GAME_OVER:
			ChangeState(PlaySceneCameraState::STOP);
			break;
		default:
			break;
	}
}
