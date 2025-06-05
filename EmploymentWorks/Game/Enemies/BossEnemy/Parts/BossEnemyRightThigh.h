#pragma once
#include "Game/Enemies/BossEnemy/BossEnemyParts.h"


class BossEnemyRightThigh : public BossEnemyParts
{
	//パーツ名
	static constexpr const char PARTS_NAME[] = "RightThigh";

public:
	//コンストラクタ
	BossEnemyRightThigh(Scene* scene);
	//デストラクタ
	~BossEnemyRightThigh() override;

};