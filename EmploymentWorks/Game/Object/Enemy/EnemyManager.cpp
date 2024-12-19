/*
	@file	EnemyManager.cpp
	@brief	シーンマネージャクラス
*/
#include "pch.h"
#include "EnemyManager.h"
#include "Game/Screen.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include "Libraries/MyLib/InputManager.h"
#include <cassert>

#include "Libraries/MyLib/Fade.h"
#include "Game/Object/BirdEnemy/BirdEnemy.h"

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
EnemyManager::EnemyManager()
	:
	m_commonResources{}

{
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
EnemyManager::~EnemyManager()
{
	Finalize();
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void EnemyManager::Initialize()
{
	using namespace DirectX::SimpleMath;





}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void EnemyManager::Update(float elapsedTime)
{

	for (auto& enemy : m_enemys)
	{
		enemy->Update(elapsedTime);
	}

}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void EnemyManager::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{
	for (auto& enemy : m_enemys)
	{
		enemy->Render(view,projection);
	}

}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void EnemyManager::Finalize()
{
}


void EnemyManager::Instances(Player* player, CommonResources* resources)
{
	using namespace DirectX::SimpleMath;

	m_commonResources = resources;

	DirectX::SimpleMath::Quaternion rotation = Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0), 0, DirectX::XMConvertToRadians(0));

	float scale = 0.5f;
	auto birdEnemy = std::make_unique<BirdEnemy>(m_commonResources, nullptr, DirectX::SimpleMath::Vector3(scale, scale, scale), Vector3(6, 2, 4), rotation);
	birdEnemy->Instances();
	birdEnemy->RegistrationInformation(player);
	birdEnemy->Initialize();

	m_enemys.push_back(std::move(birdEnemy));


}

