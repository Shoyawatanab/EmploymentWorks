#pragma once
#include "Game/Enemies/BossEnemy/BossEnemyParts.h"


class BossEnemyRightArm : public BossEnemyParts
{
	//パーツ名
	static constexpr const char PARTS_NAME[] = "RightArm";

public:
	//コンストラクタ
	BossEnemyRightArm(Scene* scene);
	//デストラクタ
	~BossEnemyRightArm() override;

};