/*
	���̓G�̍U��
*/
#pragma once
#include <pch.h>
#include "Game/Interface/IState.h"

class CommonResources;

class Boomerang;
class Player;
class BirdEnemy;

// BirdEnemyAttack�N���X���`����
class BirdEnemyAttack : public IState
{
public:
	// �R���X�g���N�^
	BirdEnemyAttack();
	// �f�X�g���N�^
	~BirdEnemyAttack();
	// ����������
	void Initialize(CommonResources* resoure);

	// �X�V����
	void Update(const float& elapsedTime);
	//�`��
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection);

	void Enter();
	void Exit();

	//�N���X�ɕK�v�ȏ��i�|�C���^�j�̓o�^
	void AddPointer(Player* player, BirdEnemy* birdEnemy);



private:

	// ���ʃ��\�[�X
	CommonResources* m_commonResources;

	BirdEnemy* m_birdEnemy;


	Player* m_player;
	//���ߎ���
	float m_accumulationTime;

	float m_shotTime;

	//�łʂ̐�
	int m_bulletCount;

};

