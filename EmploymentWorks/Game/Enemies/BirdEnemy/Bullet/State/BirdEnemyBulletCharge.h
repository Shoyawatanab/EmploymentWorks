#pragma once
#pragma once
#include "GameBase/Interface/IState.h"


class BirdEnemy;
class BirdEnemyBulletStateMachine;
class BirdEnemyBullet;


class BirdEnemyBulletCharge :public IState
{
public:
	//�`���[�W����
	static constexpr float CHARGE_TIME = { 3.0f };

public:
	//�R���X�g���N
	BirdEnemyBulletCharge(BirdEnemyBulletStateMachine* stateMachine, BirdEnemyBullet* bullet,BirdEnemy* birdEnemy);
	//�f�X�g���N�^
	~BirdEnemyBulletCharge() override;

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
	//����
	float m_time;



};

