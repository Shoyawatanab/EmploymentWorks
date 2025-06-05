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
	Actor(scene)
	,m_partsName{partsName}
{

	AddComponent<ModelComponent>(this, modelName);

}

/// <summary>
/// デストラクタ
/// </summary>
BossEnemyParts::~BossEnemyParts()
{
}
