
#include "pch.h"
#include "BirdEnemyIdling.h"

#include "Game/CommonResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "Game/Enemys/BirdEnemy/BirdEnemy.h"

#include <random>

#include "Game/Params.h"
#include "Game/InstanceRegistry.h"
#include "Game/Observer/Messenger.h"

/// <summary>
/// コンストラクタ
/// </summary>
BirdEnemyldling::BirdEnemyldling(BirdEnemy* owner)
	:
	m_player{}
	,m_time{}
	,m_attackInterval{}
	, m_birdEnemy{ owner }
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
void BirdEnemyldling::Initialize()
{
	
	m_player = InstanceRegistry::GetInstance()->GetRegistryInstance<Player>("Player");

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


			Messenger::GetInstance()->Notify<EnemyMessageType>(m_birdEnemy->GetID(), EnemyMessageType::MOVEING);
			
		}
		else
		{


			Messenger::GetInstance()->Notify<EnemyMessageType>(m_birdEnemy->GetID(), EnemyMessageType::BEAM_ATTACK);

		}
	}


	m_time += elapsedTime;


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



