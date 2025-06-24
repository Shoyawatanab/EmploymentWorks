#pragma once
#include "GameBase/Interface/IState.h"

class BirdEnemyStateMachine;
class BirdEnemy;


class BirdEnemyIdle :public IState
{
public:
	//�R���X�g���N
	BirdEnemyIdle(BirdEnemyStateMachine* stateMachine,BirdEnemy* birdEnemy);
	//�f�X�g���N�^
	~BirdEnemyIdle() override;

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

	//����
	float m_time;
	//�C���^�[�o��
	float m_attackInterval;

};

