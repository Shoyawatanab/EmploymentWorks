/*
* �v���C���N���X�@
*/

#pragma once
#include"GameBase/Actor.h"



class BossEnemy : public Actor //, public IObserver<GamePlayMessageType> , public IObserver<EnemyMessageType>
{
public:

public:
	//�R���X�g���N�^
	BossEnemy(Scene* scene);
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


//
////�ʒm���ɌĂ΂��֐�
//	void Notify(const Telegram<GamePlayMessageType>& telegram)  override;
//
//	void Notify(const Telegram<EnemyMessageType>& telegram)  override;

private:




	



};


