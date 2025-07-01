#pragma once
#include"Game/Enemies/EnemyBase.h"

class Player;
class BirdEnemyStateMachine;
class BirdEnemyBullet;


class BirdEnemy : public EnemyBase
{


public:

	//�I�u�W�F�N�g�^�O�̎擾
	ObjectTag GetObjectTag() override { return ObjectTag::BIRD_ENEMY; }
	//�^�[�Q�b�g�̃Z�b�g
	void SetTarget(Actor* target) { m_target = target; }
	//�^�[�Q�b�g�̎擾
	Actor* GetTarget() { return m_target; }

	//��A�N�e�B�u�̒e�̎擾
	BirdEnemyBullet* GetInactiveBullet();

	//�X�e�[�g�}�V�[���̎擾
	BirdEnemyStateMachine* GetStateMachine() { return m_stateMachine.get(); }

public:
	//�R���X�g���N
	BirdEnemy(Scene* scene, DirectX::SimpleMath::Vector3 scale
		, DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Quaternion rotation, Player* player);
	//�f�X�g���N�^
	~BirdEnemy() override;

	//�I�u�W�F�N�g�ʂ̍X�V����
	void UpdateActor(const float& deltaTime) override;

	//�����������ɌĂяo�����
	void OnCollisionEnter(ColliderComponent* collider) override;


private:
	//�^�[�Q�b�g�ɑ΂��ĉ�]
	void Rotate(const float& deltaTime);

private:
	//�X�e�[�g�}�V��
	std::unique_ptr<BirdEnemyStateMachine> m_stateMachine;
	//�^�[�Q�b�g
	Actor* m_target;

	//�e�z��
	std::vector<BirdEnemyBullet*> m_bullets;

};


