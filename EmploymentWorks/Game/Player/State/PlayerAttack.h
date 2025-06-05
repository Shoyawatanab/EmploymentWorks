/*
* �v���C���̒ʏ��ԃN���X
*/
#pragma once
#include "Game/Interface/IState.h"
#include "Game/Interface/IObserver.h"

class PlayerStateMachine;
class Player2;

class PlayerAttack : public IState , IObserver<GamePlayMessageType>
{
public:

	enum class ThrowState
	{
		RIGHT = 0
		,FRONT
		, LEFT

	};

	enum class ThrowQuantityState
	{
		ONE,     //�P�Ȃ���
		THREE	 //�R�Ȃ���
	};



public:
	//�R���X�g���N�^
	PlayerAttack(PlayerStateMachine* stateMachine, Player2* player) ;
	//�f�X�g���N�^
	~PlayerAttack() override;


	// �X�V����
	void Update(const float& elapsedTime) override;
	//��Ԃɓ�������
	void Enter() override;
	//��Ԃ𔲂�����
	void Exit() override;

	//�ʒm���ɌĂяo�����
	void Notify(const Telegram<GamePlayMessageType>& telegram) override;

private:
	//
	Player2* m_player;
	PlayerStateMachine* m_stateMahine;


	//�����̏��
	ThrowState m_throwState;
	//��������̏��
	ThrowQuantityState m_throwQuantityState;


};