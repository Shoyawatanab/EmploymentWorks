/*
* �v���C���̒ʏ��ԃN���X
*/
#pragma once
#include "Game/Interface/IState.h"

class PlayerStateMachine;
class Player2;
class RigidbodyComponent;


class PlayerWalk : public IState
{
public:
	//�R���X�g���N�^
	PlayerWalk(PlayerStateMachine* stateMachine, Player2* player);
	//�f�X�g���N�^
	~PlayerWalk() override;
	// �X�V����
	void Update(const float& deltatime) override;
	//��Ԃɓ�������
	void Enter() override;
	//��Ԃ𔲂�����
	void Exit() override;

private:
	//�ړ�
	void Move(const float& deltatime);
	//��]
	void Rotate(const float& deltatime);
private:
	//�v���C��
	Player2* m_player;
	//�X�e�[�g�}�V�[��
	PlayerStateMachine* m_stateMahine;
	//���W�b�g�{�f�B�[
	RigidbodyComponent* m_rigidbody;

	//�ړ���
	DirectX::SimpleMath::Vector3 m_moveDirection;


};