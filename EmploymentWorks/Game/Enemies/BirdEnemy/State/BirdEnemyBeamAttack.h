#pragma once
#include "GameBase/Interface/IState.h"

class BirdEnemyStateMachine;
class BirdEnemy;


class BirdEnemyBeamAttack :public IState
{
public:
	//�R���X�g���N
	BirdEnemyBeamAttack(BirdEnemyStateMachine* stateMachine, BirdEnemy* birdEnemy);
	//�f�X�g���N�^
	~BirdEnemyBeamAttack() override;

	// �X�V����
	void Update(const float& deltaTime) override;
	//��Ԃɓ�������
	void Enter() override;
	//��Ԃ𔲂�����
	void Exit() override;

private:
	//���G
	BirdEnemy* m_birdEnemy;
	//�X�e�[�g�}�V��
	BirdEnemyStateMachine* m_stateMahine;

};


