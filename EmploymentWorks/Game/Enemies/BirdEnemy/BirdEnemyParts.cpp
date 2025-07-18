/*
	クラス名     : BirdEnemyPars
	説明         : 鳥敵のパーツの基底クラス
	補足・注意点 :
*/
#include "pch.h"
#include "BirdEnemyParts.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="scene">シーン</param>
/// <param name="partsName">パーツ名</param>
/// <param name="modelName">モデル名</param>
BirdEnemyPars::BirdEnemyPars(Scene* scene, const std::string& partsName, const std::string& modelName)
	:
	ModelPartsBase(scene,partsName,modelName)
{



}

/// <summary>
/// デストラクタ
/// </summary>
BirdEnemyPars::~BirdEnemyPars()
{
}
