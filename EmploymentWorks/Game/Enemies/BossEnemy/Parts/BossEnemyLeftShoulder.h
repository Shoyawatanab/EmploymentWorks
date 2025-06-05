#pragma once
#include "Game/Enemies/BossEnemy/BossEnemyParts.h"


class BossEnemyLeftShoulder : public BossEnemyParts
{
	//パーツ名
	static constexpr const char PARTS_NAME[] = "LeftShoulder";

public:
	//コンストラクタ
	BossEnemyLeftShoulder(Scene* scene);
	//デストラクタ
	~BossEnemyLeftShoulder() override;

};