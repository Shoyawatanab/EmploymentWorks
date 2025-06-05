#pragma once
#include "Game/Enemies/BossEnemy/BossEnemyParts.h"


class BossEnemyPelvis : public BossEnemyParts
{
	//パーツ名
	static constexpr const char PARTS_NAME[] = "Pelvis";

public:
	//コンストラクタ
	BossEnemyPelvis(Scene* scene);
	//デストラクタ
	~BossEnemyPelvis() override;

};