#include "pch.h"
#include "PlaySceneCameraStateMachine.h"
#include "Game/Camera/PayScene/PaySceneCameraState/PaySceneCameraStates.h"
#include "Game/Messenger/Messenger.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="camera"></param>
PlaySceneCameraStateMachine::PlaySceneCameraStateMachine(PlaySceneCamera* camera)
{

	AddState(PaySceneCameraState::TPS, std::make_unique<PlaySceneCameraTPS>(this,camera));
	AddState(PaySceneCameraState::ENEMY_TARGET, std::make_unique<PlaySceneEnemyTargetCamera>(this,camera));

	SetStartState(PaySceneCameraState::TPS);


	Messenger::GetInstance()->Rigister(
		{
			MessageType::BOSS_DEFEATED
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
void PlaySceneCameraStateMachine::Notify(MessageType type, void* datas)
{
	switch (type)
	{
		case MessageType::BOSS_DEFEATED:
			ChangeState(PaySceneCameraState::ENEMY_TARGET);
			break;
		default:
			break;
	}
}
