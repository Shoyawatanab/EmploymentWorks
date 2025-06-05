#include "pch.h"
#include "PlaySceneCameraStateMachine.h"
#include "Game/Camera/PayScene/PaySceneCameraState/PaySceneCameraStates.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="camera"></param>
PlaySceneCameraStateMachine::PlaySceneCameraStateMachine(PlaySceneCamera* camera)
{

	AddState(PaySceneCameraState::TPS, std::make_unique<PlaySceneCameraTPS>(this,camera));

	SetStartState(PaySceneCameraState::TPS);

}

/// <summary>
/// デストラクタ
/// </summary>
PlaySceneCameraStateMachine::~PlaySceneCameraStateMachine()
{
}
