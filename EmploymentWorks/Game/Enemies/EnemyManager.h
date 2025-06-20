#pragma once
#include "GameBase/Actor.h"

class Player;

class EnemyManager : public Actor
{
public:
	//全ての敵を返す
	std::vector<Actor*> GetEnemys() { return m_enemys; }

public:
	//コンストラクタ
	EnemyManager(Scene* scene, Player* player);
	//デストラクタ
	~EnemyManager();

private:

	std::vector<Actor*> m_enemys;


};