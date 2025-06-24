#pragma once
#include "GameBase/StateMachine/StateMachine.h"
#include "GameBase/Messenger/IObserver.h"

class PlaySceneCamera;


enum class PaySceneCameraState
{
	
	TPS
	,ENEMY_TARGET
};

class PlaySceneCameraStateMachine : public StateMachine<IState,PaySceneCameraState> , public IObserver
{

public:
	//コンストラクタ
	PlaySceneCameraStateMachine(PlaySceneCamera* camera);
	//デストラクタ
	~PlaySceneCameraStateMachine() override;

	//通知時に呼び出される
	void Notify(MessageType type, void* datas) override;


};
