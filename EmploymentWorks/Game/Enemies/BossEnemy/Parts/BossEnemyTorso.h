#pragma once
#include "Game/Enemies/BossEnemy/BossEnemyParts.h"


class BossEnemyTorso : public BossEnemyParts
{
	//パーツ名
	static constexpr const char PARTS_NAME[] = "Torso";

public:
	//コンストラクタ
	BossEnemyTorso(Scene* scene);
	//デストラクタ
	~BossEnemyTorso() override;

};