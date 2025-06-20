/*
* �v���C���N���X�@
*/

#pragma once
#include"GameBase/Actor.h"
#include "GameBase/Messenger/IObserver.h"

class BossBehaviorTree;
class Player;
class RigidbodyComponent;
class AnimatorComponent;
class BossEnemyModel;
class BossEnemyActionManager;



class BossEnemy : public Actor , public IObserver
{
public:
	//���f���̎擾
	BossEnemyModel* GetModel() { return m_model; }

	//���n���Ă��邩�@true�@���n���Ă�@false�@���ĂȂ�
	bool GetIsGround() const { return m_isGround; }

public:
	//�R���X�g���N�^
	BossEnemy(Scene* scene , Player* player);
	//�f�X�g���N�^
	~BossEnemy() override;

	//�I�u�W�F�N�g�ʂ̍X�V����
	void UpdateActor(const float& deltaTime) override;

	//�����������ɌĂяo�����
	void OnCollisionEnter(ColliderComponent* collider);

	//�����葱���Ă���Ƃ��̌Ăяo�����
	void OnCollisionStay(ColliderComponent* collider);

	//�Փ˂��I�������Ƃ��ɌĂяo�����
	void OnCollisionExit(ColliderComponent* collider);



	//�ʒm���ɌĂ΂��֐�
	void Notify(MessageType type,void* datas)  override;

private:
	//���n�����Ƃ�
	void Landing();


private:

	//�r�w�C�r�A�c���[
	std::unique_ptr<BossBehaviorTree> m_behavior;
	//�{�X�G���f��
	BossEnemyModel* m_model;


	//�d��
	RigidbodyComponent* m_rigidBody;
	//�A�j���[�V����
	AnimatorComponent* m_animation;
	//�A�N�V�����}�l�[�W���[
	std::unique_ptr<BossEnemyActionManager> m_actionManager;
	//���n���Ă��邩
	bool m_isGround;



};


