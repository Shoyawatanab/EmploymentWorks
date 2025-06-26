#pragma once
#include "GameBase/StateMachine/StateMachine.h"
#include "GameBase/Messenger/IObserver.h"
#include "Game/Messenger/Scene/SceneMessageType.h"

class PlaySceneCamera;


enum class PaySceneCameraState
{
	
	TPS
	,ENEMY_TARGET
};

class PlaySceneCameraStateMachine : public StateMachine<IState,PaySceneCameraState> , public IObserver<SceneMessageType>
{

public:
	//�R���X�g���N�^
	PlaySceneCameraStateMachine(PlaySceneCamera* camera);
	//�f�X�g���N�^
	~PlaySceneCameraStateMachine() override;

	//�ʒm���ɌĂяo�����
	void Notify(SceneMessageType type, void* datas) override;


};
