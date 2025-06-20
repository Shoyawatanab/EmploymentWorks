#pragma once
#include "GameBase/Interface/IState.h"

class BoomerangStateMachine;
class Boomerang;
class Player;

class BoomerangIdle : public IState
{

public:
	//�R���X�g���N�^
	BoomerangIdle(BoomerangStateMachine* stateMahine,Boomerang* boomerang, Player* player);
	//�f�X�g���N�^
	~BoomerangIdle() override;

	// �X�V����
	void Update(const float& deltaTime) override;
	//��Ԃɓ�������
	void Enter() override;
	//��Ԃ𔲂�����
	void Exit() override;

private:
	//�u�[������
	Boomerang* m_boomerang;
	//�X�e�[�g�}�V�[��
	BoomerangStateMachine* m_stateMahine;
	//
	Player* m_player;
};

