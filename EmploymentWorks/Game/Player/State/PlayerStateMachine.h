/*
* �v���C���̒ʏ��ԃN���X
*/
#pragma once

#include "GameBase/StateMachine/StateMachine.h"

class Player2;


enum class PlayerState
{
	IDEL
	, ATTACK
	,WALK
};

class PlayerStateMachine : public StateMachine<IState,PlayerState>//, public IObserver<PlayerMessageType>
{

public:
	//�R���X�g���N�^
	PlayerStateMachine(Player2* player);
	//�f�X�g���N�^
	~PlayerStateMachine();



	//void Notify(const Telegram<PlayerMessageType>& telegram)  override;

	
};