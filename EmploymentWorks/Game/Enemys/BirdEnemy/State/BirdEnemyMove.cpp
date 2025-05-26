
#include "pch.h"
#include "BirdEnemyMove.h"

#include "Game/CommonResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "Game/Enemys/BirdEnemy/BirdEnemy.h"

#include "Game/Player/Player.h"
#include <cmath>
#include <random>

#include "Game/Params.h"
#include "Game/InstanceRegistry.h"


/// <summary>
/// コンストラクタ
/// </summary>
BirdEnemyMove::BirdEnemyMove()
	:
	m_commonResources{},
	m_player{}
	,m_birdEnemy{}
	,m_startPosition{}
	,m_endPosition{}
	,m_time{}
{



}

/// <summary>
/// デストラクタ
/// </summary>
BirdEnemyMove::~BirdEnemyMove()
{

}

/// <summary>
/// 初期化
/// </summary>
/// <param name="resoure">共通リソース</param>
void BirdEnemyMove::Initialize(CommonResources* resoure,BirdEnemy* owner)
{

	m_commonResources = resoure;

	m_player = InstanceRegistry::GetInstance()->GetRegistryInstance<Player>("Player");

	//初期化
	m_startPosition = m_birdEnemy->GetPosition();
	m_time = 0;

}


/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void BirdEnemyMove::Update(const float& elapsedTime)
{

	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	m_time = std::min(m_time,Params::BIRDENEMY_MOVE_TIME);

	float ratio = m_time / Params::BIRDENEMY_MOVE_TIME;

	DirectX::SimpleMath::Vector3 pos = Vector3::Lerp(m_startPosition, m_endPosition, ratio);

	m_birdEnemy->SetPosition(pos);

	m_birdEnemy->Rotate(elapsedTime);


	m_time += elapsedTime;

	if (ratio == 1.0f)
	{
		m_birdEnemy->GetPlayerStateMachine()->ChangeState(m_birdEnemy->GetPlayerStateMachine()->GetBirdEnemyldling());
	}

}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="projection">射影行列</param>
void BirdEnemyMove::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	UNREFERENCED_PARAMETER(view);
	UNREFERENCED_PARAMETER(projection);

}

/// <summary>
/// 状態に入った時
/// </summary>
void BirdEnemyMove::Enter()
{
	//初期化
	m_startPosition = m_birdEnemy->GetPosition();
	m_time = 0;

	//シード値を生成
	std::random_device rd;
	std::mt19937 gen(rd());
	//等確率に実数を生成
	std::uniform_real_distribution<float> angleDist(0.0f, DirectX::XM_2PI); // 0 ~ 2πの角度を生成

	// ランダムな角度を生成
	float angle = angleDist(gen);

	//移動変数
	DirectX::SimpleMath::Vector3 offsetPosition;
	offsetPosition.x = Params::BIRDENEMY_MOVE_RADIUS * cos(angle);
	offsetPosition.y = Params::BIRDENEMY_MOVE_RADIUS * sin(angle);


	//終わりの座標を求める
	m_endPosition = m_startPosition  + offsetPosition;



}

/// <summary>
/// 状態を抜けた時
/// </summary>
void BirdEnemyMove::Exit()
{

}




