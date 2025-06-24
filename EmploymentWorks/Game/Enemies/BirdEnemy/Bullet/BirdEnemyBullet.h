#pragma once
#include "GameBase/Actor.h"


class BirdEnemy;
class BirdEnemyBulletStateMachine;


class  BirdEnemyBullet : public Actor
{
public:
	//�R���X�g���N
	BirdEnemyBullet(Scene* scene, BirdEnemy* birdEnemy);
	//�f�X�g���N�^
	~BirdEnemyBullet() override;

	//�I�u�W�F�N�g�ʂ̍X�V����
	void UpdateActor(const float& deltaTime) override;

	//�����������ɌĂяo�����
	void OnCollisionEnter(ColliderComponent* collider) override;


private:

	//���L��
	BirdEnemy* m_birdEnemy;
	//�X�e�[�g�}�V��
	std::unique_ptr<BirdEnemyBulletStateMachine> m_stateMachine;

};

