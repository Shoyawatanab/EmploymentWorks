#pragma once
#include "GameBase/Interface/IState.h"


class PlayerStateMachine;
class Player;

class PlayerBoomerangGetReady : public IState
{
public:
	//�R���X�g���N�^
	PlayerBoomerangGetReady(PlayerStateMachine* stateMachine, Player* player);
	//�f�X�g���N�^
	~PlayerBoomerangGetReady() override;

	// �X�V����
	void Update(const float& deltaTime) override;
	//��Ԃɓ�������
	void Enter() override;
	//��Ԃ𔲂�����
	void Exit() override;
private:

	//�v���C��
	Player* m_player;
	//�X�e�[�g�}�V�[��
	PlayerStateMachine* m_stateMahine;


};
