#pragma once
#include <pch.h>
#include "Interface/IBirdEnemyState.h"
class CommonResources;

class Boomerang;
class Player;
class BirdEnemy;

// BirdEnemyldling�N���X���`����
class BirdEnemyldling : public IBirdEnemyState
{
public:




	void SetResouces(CommonResources* resoure) { m_commonResources = resoure; }

public:
	// �R���X�g���N�^
	BirdEnemyldling();
	// �f�X�g���N�^
	~BirdEnemyldling();
	// ����������
	void Initialize();

	// �X�V����
	void Update(const float& elapsedTime);

	void Enter();
	void Exit();

	//�N���X�ɕK�v�ȏ��i�|�C���^�j�̓o�^
	void RegistrationInformation(CommonResources* resoure, Player* player, BirdEnemy* birdEnemy);


private:

private:

	// ���ʃ��\�[�X
	CommonResources* m_commonResources;

	BirdEnemy* m_birdEnemy;


	Player* m_player;



	float m_graivty;


};

