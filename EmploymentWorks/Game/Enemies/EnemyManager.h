#pragma once
#include "GameBase/Actor.h"

class Player;

class EnemyManager : public Actor
{
public:
	//�S�Ă̓G��Ԃ�
	std::vector<Actor*> GetEnemys() { return m_enemys; }

public:
	//�R���X�g���N�^
	EnemyManager(Scene* scene, Player* player);
	//�f�X�g���N�^
	~EnemyManager() override;

	//�G�̎��S
	void DeathEnemy(Actor* enemy);

private:

	//�f�[�^�̓ǂݍ���
	void LoadData();


private:

	std::vector<Actor*> m_enemys;

	Player* m_player;

};