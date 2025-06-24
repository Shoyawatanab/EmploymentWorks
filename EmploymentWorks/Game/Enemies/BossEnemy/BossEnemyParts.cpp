#include "pch.h"
#include "BossEnemyParts.h"
#include "GameBase/Component/Components.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene">シーン</param>
/// <param name="partsName">パーツ名</param>
/// <param name="modelName">モデル名</param>
BossEnemyParts::BossEnemyParts(Scene* scene, std::string partsName, std::string modelName)
	:
	ModelPartsBase(scene,partsName,modelName)
{



}

/// <summary>
/// デストラクタ
/// </summary>
BossEnemyParts::~BossEnemyParts()
{
}
