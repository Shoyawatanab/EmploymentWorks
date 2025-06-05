/*
	���̓G�̃r�[����/�\������N���X
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



// BirdEnemyBeamPreliminaryAction�N���X���`����
class BirdEnemyBeamPreliminaryAction : public IState
{
public:
	// �R���X�g���N�^
	BirdEnemyBeamPreliminaryAction(BirdEnemy* birdEnemy, BirdEnemyBeam* beam);
	// �f�X�g���N�^
	~BirdEnemyBeamPreliminaryAction() override;
	// ����������
	void Initialize();

	// �X�V����
	void Update(const float& elapsedTime) override;
	//��Ԃɓ�������
	void Enter() override;
	//��Ԃ𔲂�����
	void Exit() override;


private:

	//���̓G
	BirdEnemy* m_birdEnemy;
	//�v���C��
	Player* m_player;
	//�r�[��
	BirdEnemyBeam* m_beam;
	//����
	float m_time;

};

