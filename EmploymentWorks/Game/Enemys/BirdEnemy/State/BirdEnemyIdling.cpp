
#include "pch.h"
#include "BirdEnemyIdling.h"

#include "Game/CommonResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "Game/Enemys/BirdEnemy/BirdEnemy.h"

#include <random>

#include "Game/Params.h"


/// <summary>
/// コンストラクタ
/// </summary>
BirdEnemyldling::BirdEnemyldling()
	:
	m_commonResources{},
	m_player{}
	,m_time{}
	,m_attackInterval{}
	,m_birdEnemy{}
{



}

/// <summary>
/// デストラク
/// </summary>
BirdEnemyldling::~BirdEnemyldling()
{

}

/// <summary>
/// 初期化
/// </summary>
/// <param name="resoure">共通リソース</param>
void BirdEnemyldling::Initialize(CommonResources* resoure)
{
	m_commonResources = resoure;


}


/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void BirdEnemyldling::Update(const float& elapsedTime)
{

	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX;
	using namespace DirectX::SimpleMath;


	//回転の更新
	m_birdEnemy->Rotate(elapsedTime);


	if (m_time >= m_attackInterval)
	{

		//	完全なランダムをハードウェア的に生成するためのクラスの変数
		std::random_device seed;
		//	上記の完全なランダムは動作が遅いため、seed値の決定のみに使用する
		//	※「default_random_engine」はusingで「mt19937」となっている
		std::default_random_engine engine(seed());
		//	生成して欲しいランダムの範囲をDistributionに任せる。今回は0～2PI
		std::uniform_real_distribution<> dist(0, 100);

		float ratio = static_cast<float>(dist(engine));
		
		if (ratio < Params::BIRDENEMY_ATTACK_RATIO)
		{

			m_birdEnemy->GetPlayerStateMachine()->ChangeState(m_birdEnemy->GetPlayerStateMachine()->GetBirdEnemyMove());

		}
		else
		{
			m_birdEnemy->GetPlayerStateMachine()->ChangeState(m_birdEnemy->GetPlayerStateMachine()->GetBirdEnemyAttack());

		}
	}


	m_time += elapsedTime;


}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="projection">射影行列</param>
void BirdEnemyldling::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	UNREFERENCED_PARAMETER(view);
	UNREFERENCED_PARAMETER(projection);

}



/// <summary>
/// 状態に入った時
/// </summary>
void BirdEnemyldling::Enter()
{
	//初期化
	m_time = 0;

	//ランダムでインターバルの作成
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(Params::BIRDENEMY_ACTIONS_MIN_TIME, Params::BIRDENEMY_ACTIONS_MAX_TIME);

	m_attackInterval = dis(gen);

}

/// <summary>
/// 状態を抜けた時
/// </summary>
void BirdEnemyldling::Exit()
{

}

/// <summary>
/// 必要なポインタの追加
/// </summary>
/// <param name="player">プレイヤ</param>
/// <param name="birdEnemy">鳥の敵</param>
void BirdEnemyldling::AddPointer(Player* player, BirdEnemy* birdEnemy)
{
	m_player = player;
	m_birdEnemy = birdEnemy;

}

