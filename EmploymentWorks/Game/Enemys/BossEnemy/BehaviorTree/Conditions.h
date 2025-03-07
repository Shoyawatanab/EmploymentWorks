/*
	Conditions.h
	渡邊翔也
	Decoratorに渡す条件関数の管理クラス
*/

#pragma once
#include "Game/Interface/IBehaviorNode.h"

class CommonResources;
class Player;
class BossEnemy;

class Conditions 
{

public:

	//近距離攻撃の範囲
	static constexpr float CLOSERANGEDISTANCE{ 7.0f };
	//遠距離攻撃の範囲
	static constexpr float LONGRANGEDISTANCE{ 18.0f };

	//敵の視野角
	static constexpr float ANGLE{ 60.0f };



public:
	//コンストラクタ
	Conditions(CommonResources* resources, Player* player, BossEnemy* enmey);
	//デストラクタ
	~Conditions();
	//近距離攻撃範囲内かどうか
	bool IsInCloseRangeAttack();
	//遠距離攻撃範囲内かどうか
	bool IsInLongRangeAttack();
	//視野角内かどうか
	bool WithinViewingAngle();

	//視界ないかどうか
	bool IsEnemyInview(const DirectX::SimpleMath::Vector3& playerPos, const DirectX::SimpleMath::Vector3& playerForward, const DirectX::SimpleMath::Vector3& enemyPos);
private:
	//共通リソース
	CommonResources* m_commonResources;
	//プレイヤ
	Player* m_palyer;
	//ボス敵
	BossEnemy* m_enemy;

	//IsAttack用変数
	float m_attackCoolTime;

};


/*メモ
　BehaviorTreeクラスでインスタンスしてそのインスタンスをstd::bindでポインタで渡しているのでコンストラクタで渡したプレイヤや敵などを使用することができる
　
*/