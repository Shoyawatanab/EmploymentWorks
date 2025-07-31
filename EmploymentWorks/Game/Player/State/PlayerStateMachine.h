/*
	�N���X��     : PlayerStateMachine
	����         : �v���C���̃u�[�������̃X�e�[�g�}�V�[��
	�⑫�E���ӓ_ :
*/
#pragma once
#include "GameBase/StateMachine/StateMachine.h"
#include "Game/Messenger/Messengers.h"

class Player;


enum class PlayerState
{
	IDEL                                  //�ʏ�
	, BOOMERANG_ATTACK					  //�u�[�������U��
	, BOOMERANG_GET_READY				  //�u�[�������\��
};

class PlayerStateMachine : public StateMachine<IState,PlayerState>
{

public:
	//�R���X�g���N�^
	PlayerStateMachine(Player* player);
	//�f�X�g���N�^
	~PlayerStateMachine() override;


	//�ʒm���ɌĂяo�����
	void Notify(SceneMessageType type, void* datas);

	
};