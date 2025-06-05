#include "pch.h"
#include "PlaySceneCameraStateMachine.h"
#include "Game/Camera/PayScene/PaySceneCameraState/PaySceneCameraStates.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="camera"></param>
PlaySceneCameraStateMachine::PlaySceneCameraStateMachine(PlaySceneCamera* camera)
{

	AddState(PaySceneCameraState::TPS, std::make_unique<PlaySceneCameraTPS>(this,camera));

	SetStartState(PaySceneCameraState::TPS);

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlaySceneCameraStateMachine::~PlaySceneCameraStateMachine()
{
}
