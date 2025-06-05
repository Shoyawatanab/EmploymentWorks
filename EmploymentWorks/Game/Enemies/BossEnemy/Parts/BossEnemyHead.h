#pragma once
#include "Game/Enemies/BossEnemy/BossEnemyParts.h"


class BossEnemyHead : public BossEnemyParts
{
	//パーツ名
	static constexpr const char PARTS_NAME[] = "Head";

public:
	//コンストラクタ
	BossEnemyHead(Scene* scene);
	//デストラクタ
	~BossEnemyHead() override;

};