#pragma once
#include "Game/Enemies/BossEnemy/BossEnemyParts.h"


class BossEnemyLeftLeg : public BossEnemyParts
{
	//パーツ名
	static constexpr const char PARTS_NAME[] = "LeftLeg";

public:
	//コンストラクタ
	BossEnemyLeftLeg(Scene* scene);
	//デストラクタ
	~BossEnemyLeftLeg() override;

};