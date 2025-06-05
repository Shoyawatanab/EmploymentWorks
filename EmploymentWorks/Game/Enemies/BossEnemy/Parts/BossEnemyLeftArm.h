#pragma once
#include "Game/Enemies/BossEnemy/BossEnemyParts.h"


class BossEnemyLeftArm : public BossEnemyParts
{
	//パーツ名
	static constexpr const char PARTS_NAME[] = "LeftArm";

public:
	//コンストラクタ
	BossEnemyLeftArm(Scene* scene);
	//デストラクタ
	~BossEnemyLeftArm() override;

};