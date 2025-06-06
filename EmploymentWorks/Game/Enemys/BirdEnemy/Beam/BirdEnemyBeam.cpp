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
#include "Game/InstanceRegistry.h"

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
BirdEnemyBeam::BirdEnemyBeam(CommonResources* resources,BirdEnemy* enemy)
	:
	BaseEntity(resources,Vector3::One,Vector3::Zero,Quaternion::Identity),
	m_model{}
	,m_target{}
	,m_enemy{enemy}
	,m_player{}
	,m_energyBall{}
	,m_stateMachine{}
{
	//各ステートの作成
	m_stateMachine = std::make_unique<BirdEnemyBeamStateMachine>(enemy,this);
	m_energyBall = std::make_unique<BirdEnemyBeamEnergyBall>(resources,this,this);

	BaseEntity::SetIsGravity(false);

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

	m_player = InstanceRegistry::GetInstance()->GetRegistryInstance<Player>("Player");

	//初期化
	m_target = Vector3(0, 0, 5);
	m_energyBall->Initialize();
	m_stateMachine->Initialize();
	BaseEntity::SetPosition(m_enemy->GetBeamPosition());


}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="projection">射影行列</param>
void BirdEnemyBeam::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	//基底クラスの描画
	BaseEntity::Render(view, projection);
	//エネルギー弾の描画
	m_energyBall->Render(view, projection);

}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void BirdEnemyBeam::Update(const float& elapsedTime)
{
	//基底クラスの更新
	BaseEntity::Update(elapsedTime);
	//ターゲットの更新
	m_target = m_player->GetPosition();
	//ステートマシーンの更新
	m_stateMachine->Update(elapsedTime);

}


/// <summary>
/// ビームの座標の更新
/// </summary>
void BirdEnemyBeam::UpdateBirdEnemyBeamPosition()
{
	
	BaseEntity::SetPosition( m_enemy->GetBeamPosition());

	//
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



