#include "pch.h"
#include "BirdEnemyIdle.h"
#include <random>
#include "Game/Params.h"

#include "Game/Messenger/Messenger.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="stateMachine">ステートマシン</param>
/// <param name="birdEnemy">鳥敵</param>
BirdEnemyIdle::BirdEnemyIdle(BirdEnemyStateMachine* stateMachine, BirdEnemy* birdEnemy)
	:
	m_stateMahine{stateMachine}
	,m_birdEnemy{birdEnemy}
	,m_time{}
	,m_attackInterval{}
{
}

BirdEnemyIdle::~BirdEnemyIdle()
{
}

void BirdEnemyIdle::Update(const float& deltaTime)
{

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


			Messenger::GetInstance()->Notify(MessageType::BIRD_MOVE_STATE);

		}
		else
		{

			Messenger::GetInstance()->Notify(MessageType::BIRD_BEAM_ATTACK_STATE);

		}
	}


	m_time += deltaTime;

}

void BirdEnemyIdle::Enter()
{
	//初期化
	m_time = 0;

	//ランダムでインターバルの作成
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(Params::BIRDENEMY_ACTIONS_MIN_TIME, Params::BIRDENEMY_ACTIONS_MAX_TIME);

	m_attackInterval = dis(gen);

}

void BirdEnemyIdle::Exit()
{
}
