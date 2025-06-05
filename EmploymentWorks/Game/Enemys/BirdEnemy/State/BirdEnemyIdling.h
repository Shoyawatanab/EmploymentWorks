/*
* ���̓G�̒ʏ���
*/
#pragma once
#include <pch.h>
#include "Game/Interface/IState.h"

//�O���錾
class CommonResources;
class Boomerang;
class Player;
class BirdEnemy;

// BirdEnemyldling�N���X���`����
class BirdEnemyldling : public IState
{
public:
	// �R���X�g���N�^
	BirdEnemyldling(BirdEnemy* owner);
	// �f�X�g���N�^
	~BirdEnemyldling();
	// ������
	void Initialize()  ;

	// �X�V����
	void Update(const float& elapsedTime);
	//��Ԃɓ�������
	void Enter();
	//��Ԃ𔲂�����
	void Exit();

private:

	//���̓G
	BirdEnemy* m_birdEnemy;
	//�v���C��
	Player* m_player;
	//����
	float m_time;
	//�C���^�[�o��
	float m_attackInterval;


};

