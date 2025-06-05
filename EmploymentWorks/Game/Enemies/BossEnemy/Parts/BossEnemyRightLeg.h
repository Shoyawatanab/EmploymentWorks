#pragma once
#include "Game/Enemies/BossEnemy/BossEnemyParts.h"


class BossEnemyRightLeg : public BossEnemyParts
{
	//パーツ名
	static constexpr const char PARTS_NAME[] = "RightLeg";

public:
	//コンストラクタ
	BossEnemyRightLeg(Scene* scene);
	//デストラクタ
	~BossEnemyRightLeg() override;

};