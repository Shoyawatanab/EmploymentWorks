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
	~EnemyManager();

private:

	std::vector<Actor*> m_enemys;


};