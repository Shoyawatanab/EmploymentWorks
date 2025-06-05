/*
* �v���C���̒ʏ��ԃN���X
*/
#pragma once
#include "Game/Interface/IState.h"

class PlayerStateMachine;
class Player2;

class PlayerIdle : public IState 
{
public:
	//�R���X�g���N�^
	PlayerIdle(PlayerStateMachine* stateMachine,Player2* player) ;
	//�f�X�g���N�^
	~PlayerIdle() override;

	// �X�V����
	void Update(const float& elapsedTime) override;
	//��Ԃɓ�������
	void Enter() override;
	//��Ԃ𔲂�����
	void Exit() override;


private:
	//�v���C��
	Player2* m_player;

	PlayerStateMachine* m_stateMahine;
	
};