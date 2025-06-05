#pragma once
#include "Game/Enemies/BossEnemy/BossEnemyParts.h"


class BossEnemyLeftThigh : public BossEnemyParts
{
	//パーツ名
	static constexpr const char PARTS_NAME[] = "LeftThigh";

public:
	//コンストラクタ
	BossEnemyLeftThigh(Scene* scene);
	//デストラクタ
	~BossEnemyLeftThigh() override;

};