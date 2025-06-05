/*
	���̓G�̃r�[���̍U��
*/
#pragma once
#include <pch.h>
#include "Game/Interface/IState.h"

//�O���錾
class CommonResources;
class Boomerang;
class Player;
class BirdEnemy;
class BirdEnemyBeam;

// BirdEnemyBeamAttack�N���X���`����
class BirdEnemyBeamAttack : public IState
{
public:
	// �R���X�g���N�^
	BirdEnemyBeamAttack(BirdEnemy* birdEnemy, BirdEnemyBeam* beam);
	// �f�X�g���N�^
	~BirdEnemyBeamAttack() override;
	// ����������
	void Initialize() ;

	// �X�V����
	void Update(const float& elapsedTime) override;
	//��Ԃɓ�������
	void Enter() override;
	//��Ԃ𔲂�����
	void Exit() override ;



private:

	//���̓G
	BirdEnemy* m_birdEnemy;
	//�v���C��
	Player* m_player;
	//�r�[��
	BirdEnemyBeam* m_beam;
	//��������
	DirectX::SimpleMath::Vector3 m_moveDirectiion;
	//�����̃X�s�[�h
	float m_initialSpeed;
	//�ŏI�X�s�[�h
	float m_finalSpeed;
	//��������
	float m_decelerationTime;
	//����
	float m_time;

};


