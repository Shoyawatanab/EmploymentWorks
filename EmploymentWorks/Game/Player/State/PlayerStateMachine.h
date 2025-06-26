/*
* �v���C���̒ʏ��ԃN���X
*/
#pragma once
#include "GameBase/StateMachine/StateMachine.h"
#include "GameBase/Messenger/IObserver.h"
#include "Game/Messenger/Scene/SceneMessageType.h"

class Player;


enum class PlayerState
{
	IDEL                                  //�ʏ�
	, BOOMERANG_ATTACK					  //�u�[�������U��
	, BOOMERANG_GET_READY				  //�u�[�������\��
};

class PlayerStateMachine : public StateMachine<IState,PlayerState>, public IObserver<SceneMessageType>
{

public:
	//�R���X�g���N�^
	PlayerStateMachine(Player* player);
	//�f�X�g���N�^
	~PlayerStateMachine() override;


	//�ʒm���ɌĂяo�����
	void Notify(SceneMessageType type, void* datas) override;

	
};