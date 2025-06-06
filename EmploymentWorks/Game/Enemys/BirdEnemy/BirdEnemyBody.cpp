/*
	@file	BirdEnemyBody.cpp
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
#include "GameBase/Manager/CollisiionManager.h"
#include "BirdEnemyBody.h"
#include"Game/Enemys/BirdEnemy/BirdEnemyFeather.h"
#include "Game/Params.h"




/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
/// <param name="parent">親</param>
/// <param name="scale">大きさ</param>
/// <param name="position">座標</param>
/// <param name="rotation">回転</param>
BirdEnemyBody::BirdEnemyBody(CommonResources* resources,
	CharacterEntity* parent, DirectX::SimpleMath::Vector3 scale, 
	DirectX::SimpleMath::Vector3 position, 
	DirectX::SimpleMath::Quaternion rotation)
	:
	BirdEnemyPartsBase(resources, parent,PARTSNAME,scale,position,rotation)
{

}

/// <summary>
/// デストラクタ
/// </summary>
BirdEnemyBody::~BirdEnemyBody()
{
}

/// <summary>
/// 初期化
/// </summary>
void BirdEnemyBody::Initialize()
{

	using namespace DirectX::SimpleMath;


	// モデルを読み込む
	auto model = BaseEntity::GetCommonResources()->GetGameResources()->GetModel("BirdEnemyBody");

	BirdEnemyPartsBase::SetModel(model);
	//初期化
	BirdEnemyPartsBase::Initialize();

	//左羽の追加
	AddChild(std::make_unique<BirdEnemyFeather>(BaseEntity::GetCommonResources(),
		this,
		Params::BIRDENEMY_LEFTFEATHER_SCALE,
		Params::BIRDENEMY_LEFTFEATHER_POSITION,
		Params::BIRDENEMY_LEFTFEATHER_ROTATION));
	//右羽の追加
	AddChild(std::make_unique<BirdEnemyFeather>(BaseEntity::GetCommonResources(),
		this,
		Params::BIRDENEMY_RIGHTFEATHER_SCALE,
		Params::BIRDENEMY_RIGHTFEATHER_POSITION,
		Params::BIRDENEMY_RIGHTFEATHER_ROTATION));

}


/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void BirdEnemyBody::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	//オブジェクトか更新が無効なら
	if (!BaseEntity::GetIsEntityActive() || !BaseEntity::GetIsUpdateActive())
	{
		return;
	}



	BirdEnemyPartsBase::Update(elapsedTime);

}

