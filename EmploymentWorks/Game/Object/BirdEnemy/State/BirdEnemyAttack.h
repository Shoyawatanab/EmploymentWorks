#pragma once
#include <pch.h>
#include "Interface/IBirdEnemyState.h"
class CommonResources;

class Boomerang;
class Player;
class BirdEnemy;

// BirdEnemyAttack�N���X���`����
class BirdEnemyAttack : public IBirdEnemyState
{
public:



	void SetResouces(CommonResources* resoure) { m_commonResources = resoure; }

public:
	// �R���X�g���N�^
	BirdEnemyAttack();
	// �f�X�g���N�^
	~BirdEnemyAttack();
	// ����������
	void Initialize();

	// �X�V����
	void Update(const float& elapsedTime);

	void Enter();
	void Exit();

	//�N���X�ɕK�v�ȏ��i�|�C���^�j�̓o�^
	void RegistrationInformation(CommonResources* resoure, Player* player, BirdEnemy* birdEnemy);


private:
	void Attack(float elapsedTime, DirectX::Keyboard::State key);

private:

	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	BirdEnemy* m_birdEnemy;

	Player* m_player;

	float m_graivty;


};

