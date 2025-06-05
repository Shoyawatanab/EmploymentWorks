#pragma once
#include "Game/Enemies/BossEnemy/BossEnemyParts.h"


class BossEnemyLeftArmJoint : public BossEnemyParts
{
	//パーツ名
	static constexpr const char PARTS_NAME[] = "LeftArmJoint";

public:
	//コンストラクタ
	BossEnemyLeftArmJoint(Scene* scene);
	//デストラクタ
	~BossEnemyLeftArmJoint() override;

};