/*
* �v���C���̒ʏ��ԃN���X
*/
#pragma once
#include "GameBase/Interface/IState.h"

class PlayerStateMachine;
class Player;

class PlayerBoomerangAttack : public IState //, IObserver<GamePlayMessageType>
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
	PlayerBoomerangAttack(PlayerStateMachine* stateMachine, Player* player) ;
	//�f�X�g���N�^
	~PlayerBoomerangAttack() override;


	// �X�V����
	void Update(const float& deltaTime) override;
	//��Ԃɓ�������
	void Enter() override;
	//��Ԃ𔲂�����
	void Exit() override;

	////�ʒm���ɌĂяo�����
	//void Notify(const Telegram<GamePlayMessageType>& telegram) override;

private:
	//�v���C��
	Player* m_player;
	//�X�e�[�g�}�V�[��
	PlayerStateMachine* m_stateMahine;


	//�����̏��
	ThrowState m_throwState;
	//��������̏��
	ThrowQuantityState m_throwQuantityState;


};