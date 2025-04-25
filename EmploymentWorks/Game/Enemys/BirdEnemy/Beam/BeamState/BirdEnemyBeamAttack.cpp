
#include "pch.h"
#include "BirdEnemyBeamAttack.h"

#include "Game/CommonResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "Game/Enemys/BirdEnemy/Beam/BirdEnemyBeam.h"
#include "Game/Enemys/BirdEnemy/Beam/BirdEnemyBeamEnergyBall.h"
#include "Game/Enemys/BirdEnemy/BirdEnemy.h"

#include "Game/Params.h"


/// <summary>
/// コンストラクタ
/// </summary>
BirdEnemyBeamAttack::BirdEnemyBeamAttack(Player* player, BirdEnemy* birdEnemy, BirdEnemyBeam* beam)
	:
	m_commonResources{},
	m_player{player}
	,m_birdEnemy{birdEnemy}
	,m_beam{beam}
	,m_moveDirectiion{}
	,m_initialSpeed{}
	,m_finalSpeed{}
	,m_decelerationTime{}
	,m_time{}
{
}


/// <summary>
/// デストラクタ
/// </summary>
BirdEnemyBeamAttack::~BirdEnemyBeamAttack()
{

}


/// <summary>
/// 初期化
/// </summary>
/// <param name="resoure">共通リソース</param>
void BirdEnemyBeamAttack::Initialize(CommonResources* resoure)
{
	m_commonResources = resoure;

	//初期化
	m_initialSpeed = Params::BIRDENEMY_BEAM_BALL_INITIAL_SPEED;
	m_finalSpeed = Params::BIRDENEMY_BEAM_BALL_FAINAL_SPEED;
	m_decelerationTime = Params::BIRDENEMY_BEAM_BALL_DECELERATION_TIME;

}



/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void BirdEnemyBeamAttack::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	//ビームの座標の取得
	Vector3 position = m_beam->GetPosition();
	//補間のための時間を求める　　経過時間が減速時間になるまでは０～１の間　経過時間が減速時間を超えると１
	float t = std::min(m_time,m_decelerationTime) / m_decelerationTime;
	//初速と終速で補間して移動速度を求める
	float moveSpeed =  Lerp(m_initialSpeed,m_finalSpeed,t);
	//方向ベクトルに経過時間　速度をかけて位置を更新
	position += m_moveDirectiion * elapsedTime * moveSpeed;
	//更新した座標を設定
	m_beam->SetPosition(position);
	//経過時間の加算
	m_time += elapsedTime;
	
}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="projection">射影行列</param>
void BirdEnemyBeamAttack::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	UNREFERENCED_PARAMETER(view);
	UNREFERENCED_PARAMETER(projection);

}


/// <summary>
/// 状態に入った時
/// </summary>
void BirdEnemyBeamAttack::Enter()
{
	//ビームの回転を取得
	m_beam->SetRotation(m_birdEnemy->GetRotation());
	//ビームの座標の取得
 	DirectX::SimpleMath::Vector3 position = m_beam->GetPosition();
	//動く方向を決定
	m_moveDirectiion =  m_beam->GetTarget() - m_beam->GetPosition()  ;
	//正規化
	m_moveDirectiion.Normalize();
	//時間の初期化
	m_time = 0;
	//鳥の敵のステートをアイドルに変更
	m_birdEnemy->GetPlayerStateMachine()->ChangeState(m_birdEnemy->GetPlayerStateMachine()->GetBirdEnemyldling());
}

/// <summary>
/// 状態を抜けた時
/// </summary>
void BirdEnemyBeamAttack::Exit()
{



}



float BirdEnemyBeamAttack::Lerp(float start, float end, float t)
{
	return start + t * (end - start);
}

