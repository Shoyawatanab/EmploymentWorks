#pragma once
#include "GameBase/StateMachine/StateMachine.h"

class PlaySceneCamera;


enum class PaySceneCameraState
{
	
	TPS

};

class PlaySceneCameraStateMachine : public StateMachine<IState,PaySceneCameraState>
{

public:
	//�R���X�g���N�^
	PlaySceneCameraStateMachine(PlaySceneCamera* camera);
	//�f�X�g���N�^
	~PlaySceneCameraStateMachine();

};
