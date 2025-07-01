#pragma once
#include "GameBase/StateMachine/StateMachine.h"
#include "GameBase/Messenger/IObserver.h"
#include "Game/Messenger/Scene/SceneMessageType.h"

class PlaySceneCamera;


enum class PlaySceneCameraState
{
	
	TPS              //TPS�J����
	,ENEMY_TARGET	 //�G���^�[�Q�b�g�ɂ����J����
	,STOP			 //��~�J����
};

class PlaySceneCameraStateMachine : public StateMachine<IState, PlaySceneCameraState> , public IObserver<SceneMessageType>
{

public:
	//�R���X�g���N�^
	PlaySceneCameraStateMachine(PlaySceneCamera* camera);
	//�f�X�g���N�^
	~PlaySceneCameraStateMachine() override;

	//�ʒm���ɌĂяo�����
	void Notify(SceneMessageType type, void* datas) override;


};
