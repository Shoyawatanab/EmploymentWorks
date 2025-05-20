/*
	@file	StageObjectManager.cpp
	@brief	
*/
#include "pch.h"
#include "StageObjectManager.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include <cassert>

#include "Game/StageObject/Floor.h"
#include "Game/StageObject/Wall.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="resources"></param>
StageObjectManager::StageObjectManager(CommonResources* resources)
	:
	m_commonResources{resources}
	,m_stageObjects{}
{



}

/// <summary>
/// デストラクタ
/// </summary>
StageObjectManager::~StageObjectManager()
{
	// do nothing.
}

/// <summary>
/// 初期化
/// </summary>
void StageObjectManager::Initialize()
{

	//オブジェクトの初期化
	for (auto& TypeObjects : m_stageObjects)
	{
		for (auto& object : TypeObjects.second)
		{
			object->Initialize();
		}

	}


}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void StageObjectManager::Update(const float& elapsedTime)
{

	//オブジェクトの更新
	for (auto& TypeObjects : m_stageObjects)
	{
		for (auto& object : TypeObjects.second)
		{
			object->Update(elapsedTime);
		}

	}


}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="projection">射影行列</param>
void StageObjectManager::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{


	//オブジェクトの描画
	for (auto& TypeObjects : m_stageObjects)
	{
		for (auto& object : TypeObjects.second)
		{
			object->Render(view, projection);
		}

	}

	
}

void StageObjectManager::Finalize()
{
	// do nothing.
}

/// <summary>
/// 当たり判定クラスに追加
/// </summary>
/// <param name="collsionManager">コリジョンマネージャー</param>
void StageObjectManager::AddCollision(CollisionManager* collsionManager)
{

	for (auto& TypeObjects : m_stageObjects)
	{
		for (auto& object : TypeObjects.second)
		{
			object->AddCollision(collsionManager);
		}
	}
}


//オブジェクトの追加
void StageObjectManager::AddObject(std::string objectType, std::unique_ptr<CollisionEntity> object)
{

	m_stageObjects[objectType].push_back(std::move(object));

}




