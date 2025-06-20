/*
* �v���C���̒ʏ��ԃN���X
*/
#pragma once
#include "GameBase/StateMachine/StateMachine.h"
#include "GameBase/Messenger/IObserver.h"

class Player;


enum class PlayerState
{
	IDEL                                  //�ʏ�
	, BOOMERANG_ATTACK					  //�u�[�������U��
	, BOOMERANG_GET_READY				  //�u�[�������\��
};

class PlayerStateMachine : public StateMachine<IState,PlayerState>, public IObserver
{

public:
	//�R���X�g���N�^
	PlayerStateMachine(Player* player);
	//�f�X�g���N�^
	~PlayerStateMachine();


	//�ʒm���ɌĂяo�����
	void Notify(MessageType type, void* datas) override;

	
};