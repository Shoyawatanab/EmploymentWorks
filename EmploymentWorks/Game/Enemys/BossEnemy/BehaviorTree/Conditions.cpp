#include "pch.h"
#include "Conditions.h"

#include "Game/Player/Player.h"
#include "Game/Enemies/BossEnemy/BossEnemy.h"
#include "Game/CommonResources.h"
#include "Game/Params.h"
#include <random>
#include "Game/Weapon/Boomerang/Boomerang.h"
#include "Game/Weapon/Boomerang/State/BoomerangStateMachine.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
/// <param name="player">プレイヤ</param>
/// <param name="enemy">ボス敵</param>
Conditions::Conditions(CommonResources* resources, Player* player, BossEnemy* enemy)
	:
	m_commonResources{ resources },
	m_palyer{ player },
	m_enemy{ enemy },
	m_attackCoolTime{}
{

}

/// <summary>
/// デストラクタ
/// </summary>
Conditions::~Conditions()
{

}





/// <summary>
/// 近距離攻撃範囲内かどうか
/// </summary>
/// <returns>ture 範囲内  false　範囲外　</returns>
bool Conditions::IsInCloseRangeAttack()
{


	////座標の取得
	//Vector3 PlayerPosition = m_palyer->GetPosition();
	//Vector3 EnemyPosition = m_enemy->GetPosition();

	////Y座標を統一する
	//PlayerPosition.y = 0;
	//EnemyPosition.y = 0;

	////距離を求める
	//float Distance = Vector3::Distance(PlayerPosition, EnemyPosition);

	////攻撃範囲内かどうか
	//if(Distance < CLOSERANGE_ATTACK_DISTANCE)
	//{
	//	return true;
	//}

	return false;
}

/// <summary>
/// 遠距離攻撃範囲内かどうか
/// </summary>
/// <returns>true  範囲内  false　範囲外　</returns>
bool Conditions::IsInLongRangeAttack()
{
	////座標の取得
	//Vector3 PlayerPosition = m_palyer->GetPosition();
	//Vector3 EnemyPosition = m_enemy->GetPosition();

	////Y座標を統一する
	//PlayerPosition.y = 0;
	//EnemyPosition.y = 0;

	////距離を求める
	//float Distance = Vector3::Distance(PlayerPosition, EnemyPosition);

	////攻撃範囲内かどうか
	//if (Distance < LONGRANGE_ATTACK_DISTANCE)
	//{
	//	return true;
	//}


	return false;
}

/// <summary>
/// ジャンプ攻撃範囲内かどうか
/// </summary>
/// <returns>ture : 範囲内  false :　範囲外</returns>
bool Conditions::IsJumpAttackRange()
{
	////座標の取得
	//Vector3 PlayerPosition = m_palyer->GetPosition();
	//Vector3 EnemyPosition = m_enemy->GetPosition();

	////Y座標を統一する
	//PlayerPosition.y = 0;
	//EnemyPosition.y = 0;

	////距離を求める
	//float Distance = Vector3::Distance(PlayerPosition, EnemyPosition);

	////攻撃範囲内かどうか
	//if (Distance < JUMP_ATTACK_DISTANCE)
	//{
	//	return true;
	//}


	return false;

}


/// <summary>
///  敵がプレイヤの視界に入っているかどうか
/// </summary>
/// <param name="playerPos">プレイヤ座標</param>
/// <param name="playerForward">プレイヤの向いている方向</param>
/// <param name="enemyPos">敵座標</param>
/// <returns>true ：ない　false 外</returns>
bool Conditions::IsEnemyInview(const DirectX::SimpleMath::Vector3& playerPos, const DirectX::SimpleMath::Vector3& playerForward, const DirectX::SimpleMath::Vector3& enemyPos)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;
	//角度をラジアンに変換
	float radianViewAngle = XMConvertToRadians(ANGLE);
	float cosViewAngle = cos(radianViewAngle / 2);

	//敵へのベクトルの計算
	Vector3 enemyVector = enemyPos - playerPos;
	enemyVector.Normalize();
	enemyVector.y = 0.0f;

	//ドット積の計算
	float dotProduct = enemyVector.Dot(playerForward);

	return dotProduct >= cosViewAngle;

}

/// <summary>
/// HPが最大かどうか
/// </summary>
/// <returns>ture : 最大 false:最大じゃない</returns>
bool Conditions::IsMaxHp()
{

	//return false;


	//if (m_enemy->GetHP() == Params::BOSSENEMY_MAX_HP)
	//{
	//	return true;
	//}

	return false;
}

/// <summary>
/// HPが半分以上かどうか
/// </summary>
/// <returns>true : 半分以上 false :半分未満</returns>
bool Conditions::IsHPMoreThanHalf()
{

	//return false;

	//if (m_enemy->GetHP() >= Params::BOSSENEMY_MAX_HP / 2)
	//{
	//	return true;
	//}

	//
	return false;
}

/// <summary>
/// 攻撃するかどうか
/// </summary>
/// <returns>ture : 攻撃　false : 攻撃しない</returns>
bool Conditions::IsAttack()
{

	//	完全なランダムをハードウェア的に生成するためのクラスの変数
	std::random_device seed;
	//	上記の完全なランダムは動作が遅いため、seed値の決定のみに使用する
	//	※「default_random_engine」はusingで「mt19937」となっている
	std::default_random_engine engine(seed());
	//	生成して欲しいランダムの範囲をDistributionに任せる。今回は0〜2PI
	std::uniform_real_distribution<> dist(0, 100);

	float ratio = static_cast<float>(dist(engine));

	if (ratio >= 30)
	{
		return true;
	}



	return false;
}

bool Conditions::IsUnderAttack()
{

	//std::vector<std::unique_ptr<Boomerang>>* boomerangs = m_palyer->GetBoomerangs();

	//float length = 1000;
	//
	//for (auto& boo : *boomerangs)
	//{
	//	if (boo->GetBoomerangStatemachine()->GetCurrentState() == boo->GetBoomerangStatemachine()->GetBoomerangFrontThrow()
	//		 ||boo->GetBoomerangStatemachine()->GetCurrentState() == boo->GetBoomerangStatemachine()->GetBoomerangRightThrow()
	//		 || boo->GetBoomerangStatemachine()->GetCurrentState() == boo->GetBoomerangStatemachine()->GetBoomerangLeftThrow())
	//	{
	//		float length2 = Vector3::Distance(boo->GetPosition(), m_enemy->GetPosition());

	//		if (length > length2)
	//		{
	//			length = length2;
	//		}

	//	}

	//}

	//if (length <= 10.0f)
	//{
	//	return true;
	//}


	return false;
}


