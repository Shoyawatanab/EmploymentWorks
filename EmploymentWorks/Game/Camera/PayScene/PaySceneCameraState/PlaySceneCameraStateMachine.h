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
	//コンストラクタ
	PlaySceneCameraStateMachine(PlaySceneCamera* camera);
	//デストラクタ
	~PlaySceneCameraStateMachine();

};
