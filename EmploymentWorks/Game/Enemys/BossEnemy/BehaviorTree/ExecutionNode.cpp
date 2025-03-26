#include "pch.h"
#include "ExecutionNode.h"

#include "Game/Player/Player.h"
#include "Game/Enemys/BossEnemy/BossEnemy.h"
#include "Game/CommonResources.h"

using namespace DirectX::SimpleMath;
using namespace DirectX;

static const float ROTATESPEED = 1.0f;
static const float PATROLSPEED = 2.0f;;


/// <summary>
/// 
/// </summary>
/// <param name="player"></param>
/// <param name="enemy"></param>
ExecutionNode::ExecutionNode(Player* player, BossEnemy* enemy)
	:
	m_commonResources{},
	m_palyer{ player },
	m_enemy{ enemy }
{

}

/// <summary>
/// デストラクタ
/// </summary>
ExecutionNode::~ExecutionNode()
{

}

/// <summary>
/// 初期化
/// </summary>
/// <param name="resources">共通リソース</param>
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
	return IBehaviorNode::State::Success;


	//向きたい方向
	DirectX::SimpleMath::Vector3 direction = m_palyer->GetPosition() - m_enemy->GetPosition();
	direction.Normalize();
	//今の敵の前方向
	DirectX::SimpleMath::Vector3 forward = Vector3::Transform(Vector3::Backward,m_enemy->GetRotation());
	//forward.Normalize();
	//回転軸の作成
	DirectX::SimpleMath::Vector3 moveAxis = forward.Cross(direction);

	if (moveAxis.y >= 0.0f)
	{
		//正なら上方向
		moveAxis = DirectX::SimpleMath::Vector3::Up;
	}
	else
	{
		//負なら下方向
		moveAxis = DirectX::SimpleMath::Vector3::Down;
	}

	//角度を求める
	float moveAngle = forward.Dot(direction);


//ラジアン値に変換
	moveAngle = acosf(moveAngle);

	//角度と速度の比較で小さいほうを取得
	moveAngle = std::min(moveAngle, ROTATESPEED * elapsdTime);

	//敵の回転の取得
	DirectX::SimpleMath::Quaternion Rotate = m_enemy->GetRotation();
	//Y軸に対して回転をかける
	Rotate *= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(moveAxis, moveAngle);
	m_enemy->SetRotation(Rotate);

	
	//成功
	return IBehaviorNode::State::Success;
}

/// <summary>
/// ビーム攻撃
/// </summary>
/// <param name="elapsdTime">経過時間</param>
/// <returns>実行結果</returns>
IBehaviorNode::State ExecutionNode::BeamAttack(float elapsdTime)
{
	//プレイヤの方向を向く
	FacingThePlayer(elapsdTime);

	//敵クラスの関数を呼び出す
	return m_enemy->BeamAttack(elapsdTime);
}

//プレイヤに近づく

/// <summary>
/// プレイヤに近づく
/// </summary>
/// <param name="elapsdTime">経過時間</param>
/// <returns>実行結果</returns>
IBehaviorNode::State ExecutionNode::ApproachingThePlayer(float elapsdTime)
{
	//プレイヤの方向を向く
	FacingThePlayer(elapsdTime);


	return m_enemy->Walk(elapsdTime);


}

/// <summary>
/// 近距離攻撃
/// </summary>
/// <param name="elapsdTime"></param>
/// <returns>実行結果</returns>
IBehaviorNode::State ExecutionNode::CloseRangeAttacks(float elapsdTime)
{
	assert(elapsdTime);

	return m_enemy->Pounding(elapsdTime);

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

	//return m_enemy->BeamAttack(elapsdTime);
	return IBehaviorNode::State::Success;

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

/// <summary>
/// ブーメランの攻撃方向を求める
/// </summary>
/// <returns></returns>
IBehaviorNode::State ExecutionNode::FindAttackDirection()
{
	return IBehaviorNode::State::Success;
}

IBehaviorNode::State ExecutionNode::BarrierAction(float elapsdTime)
{
	return m_enemy->BarrierDefense(elapsdTime) ;
}

