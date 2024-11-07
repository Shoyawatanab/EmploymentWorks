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
{

}

ExecutionNode::~ExecutionNode()
{

}

void ExecutionNode::Initialize(CommonResources* resources)
{

	m_commonResources = resources;


}






/// <summary>
/// プレイヤのほうに向く
/// </summary>
/// <returns>true:成功 , false:失敗</returns>
IBehaviorNode::State ExecutionNode::FacingThePlayer(float elapsdTime)
{
	//向きたい方向
	DirectX::SimpleMath::Vector3 direction = m_palyer->GetPosition() - m_enemy->GetPosition();
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
	
	//成功
	return IBehaviorNode::State::Success;
}

//プレイヤに近づく
IBehaviorNode::State ExecutionNode::ApproachingThePlayer(float elapsdTime)
{
	//プレイヤの方向を向く
	FacingThePlayer(elapsdTime);

	//敵の歩きの処理
	m_enemy->Walk(elapsdTime);

	return IBehaviorNode::State::Success;

	////プレイヤの座標の取得
	//DirectX::SimpleMath::Vector3 playerPosition = m_palyer->GetPosition();
	////敵の座標の取得
	//DirectX::SimpleMath::Vector3 enemyPosition = m_enemy->GetPosition();

	////方向を求める
	//DirectX::SimpleMath::Vector3 direction = playerPosition - enemyPosition;

	////正規化
	//direction.Normalize();


	//direction *= std::sin( elapsdTime * 2.0f);

	//enemyPosition += direction;

	//m_enemy->SetPosition(enemyPosition);

	//return IBehaviorNode::State::Success;
}

/// <summary>
/// 近距離攻撃
/// </summary>
/// <param name="elapsdTime"></param>
/// <returns></returns>
IBehaviorNode::State ExecutionNode::CloseRangeAttacks(float elapsdTime)
{
	assert(elapsdTime);

	//プレイヤの方向を向く
	FacingThePlayer(elapsdTime);

	//Enemyクラスの関数を使用
	return m_enemy->CloseRangeAttack(elapsdTime);
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

	return m_enemy->BeamAttack(elapsdTime);

	//攻撃中
	//return IBehaviorNode::State::Runngin;
}

/// <summary>
/// 何もしない
/// </summary>
/// <returns>成功を返す</returns>
IBehaviorNode::State ExecutionNode::DoNothing()
{
	//成功を返す
	return IBehaviorNode::State::Success;
}

