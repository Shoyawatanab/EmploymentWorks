
#include "pch.h"
#include "BirdEnemyBeamIdling.h"

#include "Game/CommonResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "Game/Enemys/BirdEnemy/Beam/BirdEnemyBeam.h"
#include "Game/Enemys/BirdEnemy/Beam/BirdEnemyBeamEnergyBall.h"
#include "Game/Enemys/BirdEnemy/BirdEnemy.h"


/// <summary>
/// コンストラクタ
/// </summary>
BirdEnemyBeamIdling::BirdEnemyBeamIdling(Player* player, BirdEnemy* birdEnemy, BirdEnemyBeam* beam)
	:
	m_commonResources{},
	m_player{player}
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
void BirdEnemyBeamIdling::Initialize(CommonResources* resoure)
{
	m_commonResources = resoure;

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
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="projection">射影行列</param>
void BirdEnemyBeamIdling::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
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



