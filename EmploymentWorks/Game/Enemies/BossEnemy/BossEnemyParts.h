#pragma once
#include "GameBase/Model/ModelPartsBase.h"



class BossEnemyParts : public ModelPartsBase
{
public:


	//オブジェクトタグの取得
	ObjectTag GetObjectTag() { return ObjectTag::BOSS_ENEMY_PARTS; }

public:
	//コンストラクタ
	BossEnemyParts(Scene* scene, std::string partsName, std::string modelName);
	//デストラクタ
	~BossEnemyParts() override  ;


};