#pragma once
#include "Game/Weapon/WeaponBase.h"

class BoomerangStateMachine;
class Player;

class Boomerang : public WeaponBase
{
public:

	//�I�u�W�F�N�g�^�O�̎擾
	ObjectTag GetObjectTag() override { return ObjectTag::BOOMERANG; }
	//�X�e�[�g�}�V�[���̎擾
	BoomerangStateMachine* GetStateMAchine() { return m_stateMachine.get(); }
public:
	//�R���X�g���N�^
	Boomerang(Scene* scene, Player* player);
	//�f�X�g���N�^
	~Boomerang() override;
	//�I�u�W�F�N�g�ʂ̍X�V����
	void UpdateActor(const float& deltaTime) override;

	//�����������ɌĂяo�����
	void OnCollisionEnter(ColliderComponent* collider);
	//�X�e�[�g�ύX
	void ActorChangeState(WeaponState nextState) override;

private:
	std::unique_ptr<BoomerangStateMachine> m_stateMachine;

};

