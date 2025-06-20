/*
* �v���C���̒ʏ��ԃN���X
*/
#pragma once
#include "GameBase/Interface/IState.h"

class PlayerStateMachine;
class Player;
class CommonResources;

class PlayerIdle : public IState 
{
public:
	//�R���X�g���N�^
	PlayerIdle(PlayerStateMachine* stateMachine,Player* player) ;
	//�f�X�g���N�^
	~PlayerIdle() override;

	// �X�V����
	void Update(const float& deltaTime) override;
	//��Ԃɓ�������
	void Enter() override;
	//��Ԃ𔲂�����
	void Exit() override;


private:
	//�v���C��
	Player* m_player;

	PlayerStateMachine* m_stateMahine;
	
};