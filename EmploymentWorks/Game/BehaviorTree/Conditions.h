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
	//CommonResources* m_commonResources;

	Player* m_palyer;
	Enemy* m_enemy;

	//ChasingDistance用変数


	//IsRotation用変数


public:
	Conditions(Player* player, Enemy* enmey);
	~Conditions();

	bool ChasingDistance();

	bool IsRotation();


	bool FindToPlayer();
};


/*メモ
　BehaviorTreeクラスでインスタンスしてそのインスタンスをstd::bindでポインタで渡しているのでコンストラクタで渡したプレイヤや敵などを使用することができる
　
*/