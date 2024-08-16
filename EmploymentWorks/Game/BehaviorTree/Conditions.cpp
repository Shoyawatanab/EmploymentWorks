#include "pch.h"
#include "Game/BehaviorTree/Conditions.h"
#include "Conditions.h"

#include "Game/Object/Player.h"
#include "Game/Object/Enemy/Enemy.h"

Conditions::Conditions(Player* player, Enemy* enemy)
	:
	m_palyer{player},
	m_enemy{enemy}
{

}

Conditions::~Conditions()
{

}



/// <summary>
/// プレイヤをどれだけ追いかけたか
/// </summary>
/// <returns>一定値を超えている:true、超えていない:false</returns>
bool Conditions::ChasingDistance()
{

	return false ;
}


/// <summary>
/// 回転できるかどうか
/// </summary>
/// <returns>回転できる：true、できない:false</returns>
bool Conditions::IsRotation()
{



	return false;
}

/// <summary>
/// プレイヤを見つけたかどうか
/// </summary>
/// <returns>見つてない:false ,見つけた:true</returns>
bool Conditions::FindToPlayer()
{

	DirectX::SimpleMath::Vector3 Distance = m_palyer->GetPos() - m_enemy->GetPos();

	//距離が５以内なら
	if (Distance.Length() <= 5)
	{
		return false;
	}

	//見つけてない　巡回に行ってほしいから
	return true;
}


