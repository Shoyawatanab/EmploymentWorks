/*
	@file	BirdEnemyFeather.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include "Libraries/WataLib/GameResources.h"
#include <cassert>
#include "BirdEnemyFeather.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;



/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
/// <param name="parent">親</param>
/// <param name="scale">大きさ</param>
/// <param name="position">座標</param>
/// <param name="rotation">回転</param>
BirdEnemyFeather::BirdEnemyFeather(CommonResources* resources, 
	CharacterEntity* parent, 
	DirectX::SimpleMath::Vector3 scale, 
	DirectX::SimpleMath::Vector3 position, 
	DirectX::SimpleMath::Quaternion rotation)
	: 
	BirdEnemyPartsBase(resources, parent, PARTSNAME, scale, position, rotation)
{
}

/// <summary>
/// デストラク
/// </summary>
BirdEnemyFeather::~BirdEnemyFeather()
{
	// do nothing.
}

/// <summary>
/// 初期化
/// </summary>
void BirdEnemyFeather::Initialize()
{



	// モデルを読み込む
	auto model = BaseEntity::GetCommonResources()->GetGameResources()->GetModel("BirdEnemyFeather");

	BirdEnemyPartsBase::SetModel(model);

	BirdEnemyPartsBase::Initialize();


}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void BirdEnemyFeather::Update(const float& elapsedTime)
{

	//オブジェクトか更新が無効なら
	if (!BaseEntity::GetIsEntityActive() || !BaseEntity::GetIsUpdateActive())
	{
		return;
	}
	
	BirdEnemyPartsBase::Update(elapsedTime);

}

