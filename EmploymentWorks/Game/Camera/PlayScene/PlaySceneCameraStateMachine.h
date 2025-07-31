/*
	�N���X��     : PlaySceneCameraStateMachine
	����         : �v���C�V�[���J�����̃X�e�[�g�}�V�[��
	�⑫�E���ӓ_ : 
*/
#pragma once
#include "GameBase/StateMachine/StateMachine.h"
#include "Game/Messenger/Scene/SceneMessageType.h"

class PlaySceneCamera;

//�X�e�[�g�̏��
enum class PlaySceneCameraState
{
	
	TPS              //TPS�J����
	,ENEMY_TARGET	 //�G���^�[�Q�b�g�ɂ����J����
	,STOP			 //��~�J����
};

class PlaySceneCameraStateMachine : public StateMachine<IState, PlaySceneCameraState>
{

public:
	//�R���X�g���N�^
	PlaySceneCameraStateMachine(PlaySceneCamera* camera);
	//�f�X�g���N�^
	~PlaySceneCameraStateMachine() override;

	//�ʒm���ɌĂяo�����
	void Notify(SceneMessageType type, void* datas) ;


};
