/*
	@file	BirdEnemyBeam.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "BirdEnemyBeam.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>

#include "Libraries/MyLib/BinaryFile.h"
#include "Game/Enemys/BirdEnemy/BirdEnemy.h"
#include "Game/Player/Player.h"
#include "Game/Interface/ICollisionObject.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;


//インプットレイアウト
const std::vector<D3D11_INPUT_ELEMENT_DESC> BirdEnemyBeam::INPUT_LAYOUT =
{
	{ "POSITION",    0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL",      0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TANGENT",     0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",       0, DXGI_FORMAT_R8G8B8A8_UNORM,     0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",    0, DXGI_FORMAT_R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
BirdEnemyBeam::BirdEnemyBeam(CommonResources* resources, Player* player, BirdEnemy* enemy)
	:
	BaseEntity(resources,Vector3::One,Vector3::Zero,Quaternion::Identity),
	m_model{}
	,m_target{}
	,m_enemy{enemy}
	,m_player{player}
	,m_energyBall{}
	,m_stateMachine{}
{
	m_stateMachine = std::make_unique<BirdEnemyBeamStateMachine>(player,enemy,this);
	m_energyBall = std::make_unique<BirdEnemyBeamEnergyBall>(resources,this,this);


}

/// <summary>
/// デストラクタ
/// </summary>
BirdEnemyBeam::~BirdEnemyBeam()
{
	// do nothing.
}

/// <summary>
/// 初期化
/// </summary>
void BirdEnemyBeam::Initialize()
{



	m_target = Vector3(0, 0, 5);


	m_energyBall->Initialize();

	BaseEntity::SetPosition(m_enemy->GetBeamPosition());

	m_stateMachine->Initialize(BaseEntity::GetCommonResources(), m_stateMachine->GetBirdEnemyBeamIdle());

}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="projection">射影行列</param>
void BirdEnemyBeam::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{

	BaseEntity::Render(view, projection);
	m_energyBall->Render(view, projection);

}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void BirdEnemyBeam::Update(const float& elapsedTime)
{
	BaseEntity::Update(elapsedTime);

	m_target = m_player->GetPosition();

	m_stateMachine->Update(elapsedTime);

}


/// <summary>
/// ビームの座標の更新
/// </summary>
void BirdEnemyBeam::UpdateBirdEnemyBeamPosition()
{

	BaseEntity::SetPosition( m_enemy->GetBeamPosition());

	m_energyBall->SetLocalPosition(Vector3::Zero);

}

/// <summary>
/// 当たり判定に追加
/// </summary>
/// <param name="collsionManager"></param>
void BirdEnemyBeam::AddCollision(CollisionManager* collsionManager)
{
	m_energyBall->AddCollision(collsionManager);
}



