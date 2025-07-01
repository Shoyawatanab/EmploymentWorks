#pragma once
#include "GameBase/Actor.h"
#include "Game/Enemies/BirdEnemy/Bullet/State/BirdEnemyBulletStateMachine.h"

class BirdEnemy;
class SoundComponent;


class  BirdEnemyBullet : public Actor
{
public:

	//�����蔻��̑傫��
	static constexpr float SPHERE_COLLIDER_SIZE = 0.5f;
	static constexpr DirectX::SimpleMath::Vector3  BOX_COLLIDER_SIZE {0.3f, 0.3f, 0.3f};

public:

	//�I�u�W�F�N�g�^�O�̎擾
	ObjectTag GetObjectTag() override { return ObjectTag::BIRD_BULLET; }

	//�X�e�[�g�}�V�[���̎擾
	BirdEnemyBulletStateMachine* GetStateMachine() { return m_stateMachine.get(); }

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
	//������
	SoundComponent* m_explosionSE;

};

