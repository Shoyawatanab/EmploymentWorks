
#include "pch.h"
#include "BirdEnemyBeamPreliminaryAction.h"

#include "Game/CommonResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "Game/Enemys/BirdEnemy/BirdEnemy.h"
#include "Game/Enemys/BirdEnemy/Beam/BirdEnemyBeam.h"
#include "Game/Enemys/BirdEnemy/Beam/BirdEnemyBeamEnergyBall.h"
#include "Game/InstanceRegistry.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="player">プレイヤ</param>
/// <param name="birdEnemy">鳥の敵</param>
/// <param name="beam">ビーム</param>
BirdEnemyBeamPreliminaryAction::BirdEnemyBeamPreliminaryAction(BirdEnemy* birdEnemy, BirdEnemyBeam* beam)
	:
	m_player{}
	,m_time{}
	,m_birdEnemy{birdEnemy}
	,m_beam{beam}
{
}

/// <summary>
/// デストラクタ
/// </summary>
BirdEnemyBeamPreliminaryAction::~BirdEnemyBeamPreliminaryAction()
{

}

/// <summary>
/// 初期化
/// </summary>
/// <param name="resoure">共通リソース</param>
void BirdEnemyBeamPreliminaryAction::Initialize()
{


	m_player = InstanceRegistry::GetInstance()->GetRegistryInstance<Player>("Player");

}


/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void BirdEnemyBeamPreliminaryAction::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	//最大の大きさになるまでの時間の取得
	float maxSizeTime = m_beam->GetBeamEnergyBall()->GetMaxSizeTime();
	//補間の時間の計算
	float t = m_time / maxSizeTime;
	//エネルギー弾の大きさの補間
	Vector3 scale = Vector3::Lerp(m_beam->GetBeamEnergyBall()->GetInitialScale(), m_beam->GetBeamEnergyBall()->GetMaxScale(), t);
	//大きさを適用
	m_beam->GetBeamEnergyBall()->SetLocalScale(scale);
	//経過時間を加算
	m_time += elapsedTime;

	//最大の大きさになったら
	if (m_time >= maxSizeTime)
	{
		m_beam->GetStateMahine()->ChangeState(m_beam->GetStateMahine()->GetBirdEnemyBeamAttack());
	}
	//ビームの座標の更新
	m_beam->UpdateBirdEnemyBeamPosition();


}
/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="projection">射影行列</param>
void BirdEnemyBeamPreliminaryAction::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	UNREFERENCED_PARAMETER(view);
	UNREFERENCED_PARAMETER(projection);

}

/// <summary>
/// 状態に入った時
/// </summary>
void BirdEnemyBeamPreliminaryAction::Enter()
{
	//時間の初期化
	m_time = 0;


}
/// <summary>
/// 状態を抜けた時
/// </summary>
void BirdEnemyBeamPreliminaryAction::Exit()
{

}



