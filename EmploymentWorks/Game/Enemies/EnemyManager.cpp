#include "pch.h"
#include "EnemyManager.h"
#include "Game/Enemies/Enemys.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"

EnemyManager::EnemyManager(Scene* scene,Player* player)
	:
	Actor(scene)
{

	////ƒ{ƒX“G‚Ìì¬
	//auto bossEnemy = GetScene()->AddActor<BossEnemy>(GetScene(), player);

	//m_enemys.push_back(bossEnemy);


	auto bird = GetScene()->AddActor<BirdEnemy>(GetScene(), player);
	m_enemys.push_back(bird);
}

EnemyManager::~EnemyManager()
{
}
