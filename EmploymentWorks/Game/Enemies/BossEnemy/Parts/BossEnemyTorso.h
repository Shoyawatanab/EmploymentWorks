/*
	クラス名     : BossEnemyTorso
	説明         : ボス敵の胴体モデル
	補足・注意点 :
*/
#pragma once
#include "Game/Enemies/BossEnemy/BossEnemyParts.h"

class BossEnemy;

class BossEnemyTorso : public BossEnemyParts
{
	//パーツ名
	static constexpr const char PARTS_NAME[] = "Torso";

public:
	//コンストラクタ
	BossEnemyTorso(Scene* scene, BossEnemy* boss);
	//デストラクタ
	~BossEnemyTorso() override;

};