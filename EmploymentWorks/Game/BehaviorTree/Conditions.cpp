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



/// <summary>
/// プレイヤを見つけたかどうか
/// </summary>
/// <returns>見つてない:true ,見つけた:false</returns>
bool Conditions::IsFindToPlayer()
{
	//視野角外
	if (!m_commonResources->GetJudgement()->IsWithinTheSector(m_palyer->GetPos(), m_enemy->Getforward(), m_enemy->GetPos(), 20, 90))
	{
		//巡回に行ってほしから見つけていないときにtrue
		return true;
	}

	//Rayのための方向ベクトルの作成
	DirectX::SimpleMath::Vector3 Direction = m_palyer->GetPos() - m_enemy->GetPos();
	//正規化
	Direction.Normalize();

	//Rayの作成
	DirectX::SimpleMath::Ray ray;
	ray.position = m_enemy->GetPos();
	//Rayのdirectionは正規化されていること
	ray.direction = Direction;


	//障害物があるかどうか
	if (m_commonResources->GetJudgement()->IsRayToBoundingBox(ray, 1000))
	{
		return true;
	}

	//攻撃などのノードに行く
	return false;
}

/// <summary>
/// Hpが半分以上かどうか
/// </summary>
/// <returns></returns>
bool Conditions::IsMoreThanHalfHP()
{

	if (m_commonResources->GetJudgement()->GetRatio(m_enemy->GetHp(), m_enemy->GetMAXHp()) >= 0.5f)
	{
		//半分以上
		return true;
	}

	//半分未満
	return false;
}

//攻撃するかどうか
bool Conditions::IsAttack(float elapsdTime)
{

	//５秒に一回攻撃
	if (m_attackCoolTime >= 2)
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

/// <summary>
/// 近距離攻撃かどうか
/// </summary>
/// <returns></returns>
bool Conditions::IsCloseRangeAttack()
{

	//if (m_commonResources->GetJudgement()->GetLenght(m_palyer->GetPos(), m_enemy->GetPos()) <= 7)
	//{
	//	//近距離攻撃
	//	return true;
	//}

	//遠距離攻撃
	return false;
}


