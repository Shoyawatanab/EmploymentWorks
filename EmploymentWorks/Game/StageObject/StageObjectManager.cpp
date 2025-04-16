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

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
StageObjectManager::StageObjectManager(CommonResources* resources)
	:
	m_commonResources{resources}
	,m_stageObjects{}
{



}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
StageObjectManager::~StageObjectManager()
{
	// do nothing.
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void StageObjectManager::Initialize()
{
	using namespace DirectX::SimpleMath;

	for (auto& TypeObjects : m_stageObjects)
	{
		for (auto& object : TypeObjects.second)
		{
			object->Initialize();
		}

	}


}

void StageObjectManager::Update(const float& elapsedTime)
{

	for (auto& TypeObjects : m_stageObjects)
	{
		for (auto& object : TypeObjects.second)
		{
			object->Update(elapsedTime);
		}

	}


}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void StageObjectManager::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	using namespace DirectX::SimpleMath;



	for (auto& TypeObjects : m_stageObjects)
	{
		for (auto& object : TypeObjects.second)
		{
			object->Render(view, projection);
		}

	}

	
}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void StageObjectManager::Finalize()
{
	// do nothing.
}

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





void StageObjectManager::AddObject(std::string objectType, std::unique_ptr<CollisionEntity> object)
{

	m_stageObjects[objectType].push_back(std::move(object));

}




