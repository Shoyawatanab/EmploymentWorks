/*
	Conditions.h
	渡邊翔也
	Decoratorに渡す条件関数の管理クラス
*/

#pragma once
#include "Interface/IBehaviorNode.h"

class CommonResources;
class Player;
class Enemy;

class Conditions 
{




private:
	CommonResources* m_commonResources;

	Player* m_palyer;
	Enemy* m_enemy;

	//IsAttack用変数
	float m_attackCoolTime;


public:
	Conditions(CommonResources* resources, Player* player, Enemy* enmey);
	~Conditions();


	//HPがMAXかどうか
	bool IsHPMax();
	//攻撃するかどうか
	bool IsAttack(float elapsdTime);
	//HPがHP以上かどうか
	bool IsHPMoreThanHalf();
	//距離が遠いかどうか
	bool IsFarDistance();
	//距離が近いかどうか
	//bool IsCloseDistance();
	//近距離攻撃かどうか
	//bool IsCloseRangeAttack();
	//近距離攻撃範囲内かどうか
	bool IsInCloseRangeAttack();

};


/*メモ
　BehaviorTreeクラスでインスタンスしてそのインスタンスをstd::bindでポインタで渡しているのでコンストラクタで渡したプレイヤや敵などを使用することができる
　
*/