#pragma once
#include "GameBase/Actor.h"



class BossEnemyParts : public Actor
{
public:

	//名前の取得
	std::string  GetPartsName() const { return m_partsName; }


public:
	//コンストラクタ
	BossEnemyParts(Scene* scene, std::string partsName, std::string modelName);
	//デストラクタ
	~BossEnemyParts() override  ;

private:
	//パーツ名
	std::string m_partsName;


};