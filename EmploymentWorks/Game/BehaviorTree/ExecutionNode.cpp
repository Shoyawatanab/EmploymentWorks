#include "pch.h"
#include "Game/BehaviorTree/ExecutionNode.h"
#include "ExecutionNode.h"

#include "Game/Object/Player/Player.h"
#include "Game/Object/Enemy/Enemy.h"
#include "Game/CommonResources.h"


static const float ROTATESPEED = 1.0f;
static const float PATROLSPEED = 2.0f;;


ExecutionNode::ExecutionNode(Player* player, Enemy* enemy)
	:
	m_commonResources{},
	m_palyer{ player },
	m_enemy{ enemy }
	,m_currentPointNumber{}
	,m_nextPointNumber{}
{

}

ExecutionNode::~ExecutionNode()
{

}

void ExecutionNode::Initialize(CommonResources* resources)
{

	m_commonResources = resources;
	CreatePatrol();


}

void ExecutionNode::CreatePatrol()
{

	//パトロール座標の生成
	//0.敵の初期地点
	auto Pointo = std::make_unique<PatrolPointo>();
	Pointo->Position = DirectX::SimpleMath::Vector3(0, 5.75f, -10);
	m_patrolPoint.push_back(std::move(Pointo));
	//1.左上
	Pointo = std::make_unique<PatrolPointo>();
	Pointo->Position = DirectX::SimpleMath::Vector3(-16, 5.75f, -14);
	m_patrolPoint.push_back(std::move(Pointo));
	//2.左
	Pointo = std::make_unique<PatrolPointo>();
	Pointo->Position = DirectX::SimpleMath::Vector3(-27, 5.75f, 0);
	m_patrolPoint.push_back(std::move(Pointo));
	//3.左下
	Pointo = std::make_unique<PatrolPointo>();
	Pointo->Position = DirectX::SimpleMath::Vector3(-16, 5.75f, 14);
	m_patrolPoint.push_back(std::move(Pointo));
	//4.プレイヤの初期地点
	Pointo = std::make_unique<PatrolPointo>();
	Pointo->Position = DirectX::SimpleMath::Vector3(0, 2.75f, 10);
	m_patrolPoint.push_back(std::move(Pointo));
	//5.右下
	Pointo = std::make_unique<PatrolPointo>();
	Pointo->Position = DirectX::SimpleMath::Vector3(16, 5.75f, 14);
	m_patrolPoint.push_back(std::move(Pointo));
	//6.右
	Pointo = std::make_unique<PatrolPointo>();
	Pointo->Position = DirectX::SimpleMath::Vector3(27, 5.75f, 0);
	m_patrolPoint.push_back(std::move(Pointo));
	//7.右上
	Pointo = std::make_unique<PatrolPointo>();
	Pointo->Position = DirectX::SimpleMath::Vector3(16, 5.75f, -14);
	m_patrolPoint.push_back(std::move(Pointo));


	//隣接ポイントの登録
	//0に登録
	m_patrolPoint.at(0)->SetAdjacentPosint(1, m_patrolPoint[1].get());
	m_patrolPoint.at(0)->SetAdjacentPosint(2, m_patrolPoint[2].get());
	m_patrolPoint.at(0)->SetAdjacentPosint(4, m_patrolPoint[4].get());
	m_patrolPoint.at(0)->SetAdjacentPosint(6, m_patrolPoint[6].get());
	m_patrolPoint.at(0)->SetAdjacentPosint(7, m_patrolPoint[7].get());
	//1に登録
	m_patrolPoint.at(1)->SetAdjacentPosint(0, m_patrolPoint[0].get());
	m_patrolPoint.at(1)->SetAdjacentPosint(2, m_patrolPoint[2].get());
	m_patrolPoint.at(1)->SetAdjacentPosint(7, m_patrolPoint[7].get());
	//2に登録
	m_patrolPoint.at(2)->SetAdjacentPosint(0, m_patrolPoint[0].get());
	m_patrolPoint.at(2)->SetAdjacentPosint(1, m_patrolPoint[1].get());
	m_patrolPoint.at(2)->SetAdjacentPosint(3, m_patrolPoint[3].get());
	m_patrolPoint.at(2)->SetAdjacentPosint(4, m_patrolPoint[4].get());
	//3に登録
	m_patrolPoint.at(3)->SetAdjacentPosint(2, m_patrolPoint[2].get());
	m_patrolPoint.at(3)->SetAdjacentPosint(4, m_patrolPoint[4].get());
	m_patrolPoint.at(3)->SetAdjacentPosint(5, m_patrolPoint[5].get());
	//4に登録
	m_patrolPoint.at(4)->SetAdjacentPosint(0, m_patrolPoint[0].get());
	m_patrolPoint.at(4)->SetAdjacentPosint(2, m_patrolPoint[2].get());
	m_patrolPoint.at(4)->SetAdjacentPosint(4, m_patrolPoint[4].get());
	m_patrolPoint.at(4)->SetAdjacentPosint(5, m_patrolPoint[5].get());
	m_patrolPoint.at(4)->SetAdjacentPosint(6, m_patrolPoint[6].get());
	//5に登録
	m_patrolPoint.at(5)->SetAdjacentPosint(3, m_patrolPoint[3].get());
	m_patrolPoint.at(5)->SetAdjacentPosint(4, m_patrolPoint[4].get());
	m_patrolPoint.at(5)->SetAdjacentPosint(6, m_patrolPoint[6].get());
	//6に登録
	m_patrolPoint.at(6)->SetAdjacentPosint(0, m_patrolPoint[0].get());
	m_patrolPoint.at(6)->SetAdjacentPosint(4, m_patrolPoint[4].get());
	m_patrolPoint.at(6)->SetAdjacentPosint(5, m_patrolPoint[5].get());
	m_patrolPoint.at(6)->SetAdjacentPosint(7, m_patrolPoint[7].get());
	//7に登録
	m_patrolPoint.at(7)->SetAdjacentPosint(0, m_patrolPoint[0].get());
	m_patrolPoint.at(7)->SetAdjacentPosint(1, m_patrolPoint[1].get());
	m_patrolPoint.at(7)->SetAdjacentPosint(6, m_patrolPoint[6].get());


	//初期地点が0だから
	m_currentPointNumber = 0;
	DecideNextPosition();
}

/// <summary>
/// 次の座標を決める
/// </summary>
void ExecutionNode::DecideNextPosition()
{

	//隣接の数を求める
	int size =  static_cast<int> (m_patrolPoint.at(m_currentPointNumber)->m_adjacentNumber.size() - 1);
	//ポイントの隣接番号の数をもとにランダムで番号の生成
	int number = m_commonResources->GetJudgement()->GetRandom(0, size);
	//番号をもとに次の隣接の番号を求める	
	number = m_patrolPoint.at(m_currentPointNumber)->GetAdjacentNumber(number);

	//number = 4;

	//終了地点に座標を代入する
	m_endPatrolPos = m_patrolPoint.at(m_currentPointNumber)->GetAdjacentPointo(number)->Position;
	//次の番棒の登録
	m_nextPointNumber = number;


}


/// <summary>
/// 巡回ノード
/// </summary>
/// <param name="elapsdTime"></param>
/// <returns></returns>
IBehaviorNode::State ExecutionNode::Patrol(float elapsdTime)
{
	DirectX::SimpleMath::Vector3 EnemyPos = m_enemy->GetPos();

	//進む方向を求める
	DirectX::SimpleMath::Vector3 MoveDirection = m_endPatrolPos - EnemyPos;
	MoveDirection.Normalize();

	MoveDirection *= PATROLSPEED * elapsdTime;

	EnemyPos += MoveDirection;

	m_enemy->SetPos(EnemyPos);

	//距離を求める
	float distance = (m_endPatrolPos - EnemyPos).Length();


	if (distance <= 2.5f)
	{
		//次の座標を
		m_currentPointNumber = m_nextPointNumber;
		DecideNextPosition();
	}


	//方向転換
	//今の敵の前方向
	DirectX::SimpleMath::Vector3 forward = m_enemy->Getforward();

	DirectX::SimpleMath::Vector3 moveAxis = forward.Cross(MoveDirection);

	if (moveAxis.y >= 0.0f)
	{
		moveAxis = DirectX::SimpleMath::Vector3::Up;
	}
	else
	{
		moveAxis = DirectX::SimpleMath::Vector3::Down;
	}

	//角度を求める
	float moveAngle = forward.Dot(MoveDirection);


	//ラジアン値に変換
	moveAngle = acosf(moveAngle);

	//角度と速度の比較で小さいほうを取得
	moveAngle = std::min(moveAngle, ROTATESPEED * elapsdTime);

	//敵の回転の取得
	DirectX::SimpleMath::Quaternion Rotate = m_enemy->GetRotate();
	//Y軸に対して回転をかける
	Rotate *= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(moveAxis, moveAngle);
	m_enemy->SetRotate(Rotate);

	//回転をもとに敵の初期の方向ベクトルの更新
	forward = DirectX::SimpleMath::Vector3::Transform(Enemy::INITIALFORWARD, Rotate);
	forward.Normalize();
	m_enemy->Setforward(forward);



	return IBehaviorNode::State::Success;
}



/// <summary>
/// プレイヤのほうに向く
/// </summary>
/// <returns>true:成功 , false:失敗</returns>
IBehaviorNode::State ExecutionNode::FacingThePlayer(float elapsdTime)
{
	//向きたい方向
	DirectX::SimpleMath::Vector3 direction = m_palyer->GetPos() - m_enemy->GetPos();
	direction.Normalize();
	//今の敵の前方向
	DirectX::SimpleMath::Vector3 forward = m_enemy->Getforward();
	//forward.Normalize();



	DirectX::SimpleMath::Vector3 moveAxis = forward.Cross(direction);

	if (moveAxis.y >= 0.0f)
	{
		moveAxis = DirectX::SimpleMath::Vector3::Up;
	}
	else
	{
		moveAxis = DirectX::SimpleMath::Vector3::Down;
	}

	//角度を求める
	float moveAngle = forward.Dot(direction);

	//if (moveAngle < 0.01f)
	//{
	//	return IBehaviorNode::State::Failure;
	//}

//ラジアン値に変換
	moveAngle = acosf(moveAngle);

	//角度と速度の比較で小さいほうを取得
	moveAngle = std::min(moveAngle, ROTATESPEED * elapsdTime);

	//敵の回転の取得
	DirectX::SimpleMath::Quaternion Rotate = m_enemy->GetRotate();
	//Y軸に対して回転をかける
	Rotate *= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(moveAxis, moveAngle);
	m_enemy->SetRotate(Rotate);

	//回転をもとに敵の初期の方向ベクトルの更新
	forward = DirectX::SimpleMath::Vector3::Transform(Enemy::INITIALFORWARD, Rotate);
	forward.Normalize();
	m_enemy->Setforward(forward);

	return IBehaviorNode::State::Success;
}

/// <summary>
/// 近距離攻撃
/// </summary>
/// <param name="elapsdTime"></param>
/// <returns></returns>
IBehaviorNode::State ExecutionNode::CloseRangeAttacks(float elapsdTime)
{
	assert(elapsdTime);

	return IBehaviorNode::State::Success;
}

/// <summary>
/// 遠距離攻撃
/// </summary>
/// <param name="elapsdTime"></param>
/// <returns></returns>
IBehaviorNode::State ExecutionNode::RangedAttack(float elapsdTime)
{
	assert(elapsdTime);

	//遠距離攻撃はRenderの関係でEnemyクラスで作ったBeamAttackを使用している



	//攻撃中
	return IBehaviorNode::State::Runngin;
}

/// <summary>
/// 何もしない
/// </summary>
/// <returns></returns>
IBehaviorNode::State ExecutionNode::DoNothing()
{
	return IBehaviorNode::State::Success;
}

/// <summary>
/// 逃げる
/// </summary>
/// <param name="elapsdTime"></param>
/// <returns></returns>
IBehaviorNode::State ExecutionNode::RunAway(float elapsdTime)
{
	assert(elapsdTime);

	return IBehaviorNode::State::Success;
}

