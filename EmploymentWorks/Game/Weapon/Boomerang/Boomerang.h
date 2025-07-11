/*
	�N���X��     : Boomerang
	����         : �u�[������
	�⑫�E���ӓ_ :
*/
#pragma once
#include "Game/Weapon/WeaponBase.h"
#include "Game/Weapon/Boomerang/State/BoomerangStateMachine.h"

class Player;

class Boomerang : public WeaponBase<BoomerangState>
{
public:

	//�I�u�W�F�N�g�^�O�̎擾
	ObjectTag GetObjectTag() override { return ObjectTag::BOOMERANG; }
	//�X�e�[�g�}�V�[���̎擾
	BoomerangStateMachine* GetStateMAchine() { return m_stateMachine.get(); }
	//�P�t���O�̍��W���擾
	const DirectX::SimpleMath::Vector3& GetLastPosition() { return m_lastPosition; }

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
	void ActorChangeState(BoomerangState nextState) override;

private:

	//���
	void PickUp();

private:
	//�X�e�[�g�}�V�[��
	std::unique_ptr<BoomerangStateMachine> m_stateMachine;

	//1�t���O�̍��W
	DirectX::SimpleMath::Vector3 m_lastPosition;


};

