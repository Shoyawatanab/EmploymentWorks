#pragma once
#include "GameBase/Interface/IState.h"

class BirdEnemyBulletStateMachine;
class BirdEnemyBullet;
class BirdEnemy;

class BirdEnemyBulletIdle :public IState
{
public:
	//�R���X�g���N
	BirdEnemyBulletIdle(BirdEnemyBulletStateMachine* stateMachine, BirdEnemyBullet* bullet, BirdEnemy* birdEnemy);
	//�f�X�g���N�^
	~BirdEnemyBulletIdle() override;

	// �X�V����
	void Update(const float& deltaTime) override;
	//��Ԃɓ�������
	void Enter() override;
	//��Ԃ𔲂�����
	void Exit() override;

private:
	//�e
	BirdEnemyBullet* m_bullet;
	//�X�e�[�g�}�V��
	BirdEnemyBulletStateMachine* m_stateMahine;
	//���G
	BirdEnemy* m_birdEnemy;
};

