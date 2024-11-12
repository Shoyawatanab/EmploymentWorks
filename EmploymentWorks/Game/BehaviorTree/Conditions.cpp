#include "pch.h"
#include "Game/BehaviorTree/Conditions.h"
#include "Conditions.h"

#include "Game/Object/Player/Player.h"
#include "Game/Object/Enemy/Enemy.h"
#include "Game/CommonResources.h"


Conditions::Conditions(CommonResources* resources, Player* player, Enemy* enemy)
	:
	m_commonResources{ resources },
	m_palyer{ player },
	m_enemy{ enemy },
	m_attackCoolTime{}
{

}

Conditions::~Conditions()
{

}



//

/// <summary>
///HPがMAXかどうか 
/// </summary>
/// <returns>true : MAX　false : NotMAX</returns>
bool Conditions::IsHPMax()
{
	//MAXなら
	if (m_enemy->GetMAXHp() == m_enemy->GetHp())
	{
		return true;
	}


	return false;
}

/// <summary>
///攻撃するかどうか 
/// </summary>
/// <param name="elapsdTime"></param>
/// <returns>true : 攻撃　false : 攻撃しない</returns>
bool Conditions::IsAttack(float elapsdTime)
{

	//５秒に一回攻撃
	if (m_attackCoolTime >= 5)
	{
		//どっかでクールタイムのリセットが必要
		m_attackCoolTime = 0;
		//攻撃
		return true;
	}

	m_attackCoolTime += elapsdTime;
	//攻撃しない
	return false;
}

//

/// <summary>
/// HPがHP以上かどうか
/// </summary>
/// <returns>true : 半分以上　false : 半分未満</returns>
bool Conditions::IsHPMoreThanHalf()
{

	float halfHP = m_enemy->GetMAXHp() / 2;


	//半分以上なら
	if (halfHP <= m_enemy->GetHp())
	{
		return true;
	}

	return false;
}

//

/// <summary>
/// 一定の距離より遠いかどうか
/// </summary>
/// <returns>true : 遠い　false :　近い</returns>
bool Conditions::IsFarDistance()
{
	//座標の取得
	DirectX::SimpleMath::Vector3 PlayerPosition = m_palyer->GetPosition();
	DirectX::SimpleMath::Vector3 EnemyPosition = m_enemy->GetPosition();

	//Y座標を統一する
	PlayerPosition.y = 0;
	EnemyPosition.y = 0;

	//距離を求める
	float Distance = DirectX::SimpleMath::Vector3::Distance(PlayerPosition, EnemyPosition);

	//規定値より遠いかどうか
	if (Distance >= 30)
	{
		return true;
	}

	return false;
}

//

///// <summary>
///// 距離が近いかどうか
///// </summary>
///// <returns> true : 近い　false : 近くない</returns>
//bool Conditions::IsCloseDistance()
//{
//
//	//座標の取得
//	DirectX::SimpleMath::Vector3 PlayerPosition = m_palyer->GetPosition();
//	DirectX::SimpleMath::Vector3 EnemyPosition = m_enemy->GetPosition();
//
//	//Y座標を統一する
//	PlayerPosition.y = 0;
//	EnemyPosition.y = 0;
//
//	//距離を求める
//	float Distance = DirectX::SimpleMath::Vector3::Distance(PlayerPosition, EnemyPosition);
//
//	//規定値より近いかどうか
//	if (Distance < 5)
//	{
//		return true;
//	}
//
//
//	return false;
//}

///// <summary>
///// 近距離攻撃かどうか
///// </summary>
///// <returns> true : 近距離攻撃　false : 遠距離攻撃</returns>
//bool Conditions::IsCloseRangeAttack()
//{
//
//	//if (m_commonResources->GetJudgement()->GetLenght(m_palyer->GetPos(), m_enemy->GetPos()) <= 7)
//	//{
//	//	//近距離攻撃
//	//	return true;
//	//}
//
//	//遠距離攻撃
//	return false;
//}

/// <summary>
/// 近距離攻撃範囲内かどうか
/// </summary>
/// <returns></returns>
bool Conditions::IsInCloseRangeAttack()
{


	//座標の取得
	DirectX::SimpleMath::Vector3 PlayerPosition = m_palyer->GetPosition();
	DirectX::SimpleMath::Vector3 EnemyPosition = m_enemy->GetPosition();

	//Y座標を統一する
	PlayerPosition.y = 0;
	EnemyPosition.y = 0;

	//距離を求める
	float Distance = DirectX::SimpleMath::Vector3::Distance(PlayerPosition, EnemyPosition);

	//攻撃範囲内かどうか
	if(Distance < 15.0f)
	{
		return true;
	}

	return false;
}


