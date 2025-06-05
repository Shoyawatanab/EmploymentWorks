
#include "pch.h"
#include "BirdEnemyBeamIdling.h"

#include "Game/CommonResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "Game/Enemys/BirdEnemy/Beam/BirdEnemyBeam.h"
#include "Game/Enemys/BirdEnemy/Beam/BirdEnemyBeamEnergyBall.h"
#include "Game/Enemys/BirdEnemy/BirdEnemy.h"
#include "Game/InstanceRegistry.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="player">プレイヤ</param>
/// <param name="birdEnemy">鳥の敵</param>
/// <param name="beam">ビーム</param>
BirdEnemyBeamIdling::BirdEnemyBeamIdling(BirdEnemy* birdEnemy, BirdEnemyBeam* beam)
	:
	m_player{}
	,m_birdEnemy{birdEnemy}
	,m_beam{beam}
{
}

/// <summary>
/// デストラクタ
/// </summary>
BirdEnemyBeamIdling::~BirdEnemyBeamIdling()
{

}

/// <summary>
/// 初期化
/// </summary>
/// <param name="resoure">共通リソース</param>
void BirdEnemyBeamIdling::Initialize()
{

	m_player = InstanceRegistry::GetInstance()->GetRegistryInstance<Player>("Player");

}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void BirdEnemyBeamIdling::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	//ビームの座標を登録
 	m_beam->SetPosition( m_birdEnemy->GetPosition());


}


/// <summary>
/// 状態に入った時
/// </summary>
void BirdEnemyBeamIdling::Enter()
{

}

/// <summary>
/// 状態を抜けた時
/// </summary>
void BirdEnemyBeamIdling::Exit()
{

}



