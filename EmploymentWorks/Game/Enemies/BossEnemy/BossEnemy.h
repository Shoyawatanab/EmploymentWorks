/*
* �v���C���N���X�@
*/

#pragma once
#include"Game/Enemies/EnemyBase.h"

class BossBehaviorTree;
class Player;
class RigidbodyComponent;
class AnimatorComponent;
class BossEnemyModel;
class BossEnemyActionManager;



class BossEnemy : public EnemyBase 
{
public:

	//���n���Ă��邩�@true�@���n���Ă�@false�@���ĂȂ�
	bool GetIsGround() const { return m_isGround; }


	//�I�u�W�F�N�g�^�O�̎擾
	ObjectTag GetObjectTag() override { return ObjectTag::BOSS_ENEMY; }

	AnimatorComponent* GetAnimation() { return m_animation; }

public:

	//�R���X�g���N�^
	BossEnemy(Scene* scene , DirectX::SimpleMath::Vector3 scale
		,DirectX::SimpleMath::Vector3 position,DirectX::SimpleMath::Quaternion rotation
		,Player* player);
	//�f�X�g���N�^
	~BossEnemy() override;

	//�I�u�W�F�N�g�ʂ̍X�V����
	void UpdateActor(const float& deltaTime) override;

	//�����������ɌĂяo�����
	void OnCollisionEnter(ColliderComponent* collider) override;

	//�����葱���Ă���Ƃ��̌Ăяo�����
	void OnCollisionStay(ColliderComponent* collider) override;

	//�Փ˂��I�������Ƃ��ɌĂяo�����
	void OnCollisionExit(ColliderComponent* collider) override;

	//�_���[�W��H������Ƃ�
	void AddDamage(int damage);

	//��]
	void Rotation(const float& deltaTime);

private:

	//���n�����Ƃ�
	void Landing();

private:

	//�r�w�C�r�A�c���[
	std::unique_ptr<BossBehaviorTree> m_behavior;


	//�d��
	RigidbodyComponent* m_rigidBody;
	//�A�j���[�V����
	AnimatorComponent* m_animation;
	//�A�N�V�����}�l�[�W���[
	std::unique_ptr<BossEnemyActionManager> m_actionManager;
	//���n���Ă��邩
	bool m_isGround;
	//�v���C��
	Player* m_player;
};


