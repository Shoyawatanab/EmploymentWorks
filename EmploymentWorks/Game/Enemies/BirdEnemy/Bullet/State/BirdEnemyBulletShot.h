#pragma once
#include "GameBase/Interface/IState.h"

class BirdEnemyBulletStateMachine;
class BirdEnemyBullet;
class BirdEnemy;

class BirdEnemyBulletShot :public IState
{
public:
	//�R���X�g���N
	BirdEnemyBulletShot(BirdEnemyBulletStateMachine* stateMachine, BirdEnemyBullet* bullet, BirdEnemy* birdEnemy);
	//�f�X�g���N�^
	~BirdEnemyBulletShot() override;

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
	BirdEnemy* m_birdEnemy;
	//����
	float m_time;
	//��������
	DirectX::SimpleMath::Vector3 m_moveDirection;
};

#pragma once
