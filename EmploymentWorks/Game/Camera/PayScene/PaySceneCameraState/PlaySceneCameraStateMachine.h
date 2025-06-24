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
	//�R���X�g���N�^
	PlaySceneCameraStateMachine(PlaySceneCamera* camera);
	//�f�X�g���N�^
	~PlaySceneCameraStateMachine() override;

	//�ʒm���ɌĂяo�����
	void Notify(MessageType type, void* datas) override;


};
