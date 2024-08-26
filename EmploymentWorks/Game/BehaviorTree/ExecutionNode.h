/*
	ExecutionNode.h
	渡邊翔也
	実行ノードに渡す処理の関数の管理クラス
*/

#pragma once
#include "Interface/IBehaviorNode.h"
#include  <unordered_map>

class CommonResources;
class Player;
class Enemy;


class ExecutionNode
{

public:

	//巡回するときの座標
	struct PatrolPointo
	{
		//座標
		DirectX::SimpleMath::Vector3 Position;
		//隣接するポイント
		//std::vector<PatrolPointo*> m_adjacentPointo;

		std::unordered_map<int, PatrolPointo*> m_adjacentPointo;
		//隣接する番号
		std::vector<int> m_adjacentNumber;

		//隣接のpointと番号の登録
		void SetAdjacentPosint(int number, PatrolPointo* point) { m_adjacentPointo[number] = point; m_adjacentNumber.push_back(number); }

		//隣接の番号を取得 number:隣接の数の範囲でランダムで求めた値
		int GetAdjacentNumber(int number) { return m_adjacentNumber[number]; }
		//Pointの取得　number:隣接の番号
		PatrolPointo* GetAdjacentPointo(int number) { return m_adjacentPointo[number]; }


	};



private:
	CommonResources* m_commonResources;

	Player* m_palyer;
	Enemy* m_enemy;

	//Patrol用変数
	std::vector<std::unique_ptr< PatrolPointo>> m_patrolPoint;
	//目指す座標
	DirectX::SimpleMath::Vector3 m_endPatrolPos;
	//現在のポイント番号　次の進む場所を決めるのに使用
	int m_currentPointNumber;
	//進んでいるポイント番号
	int m_nextPointNumber;


public:
	ExecutionNode(Player* player, Enemy* enmey);
	~ExecutionNode();

	void Initialize(CommonResources* resources);

	void CreatePatrol();

	void DecideNextPosition();

	//巡回
	IBehaviorNode::State Patrol(float elapsdTime);
	//プレイヤのほうに向く
	IBehaviorNode::State FacingThePlayer(float elapsdTime);
	//近距離攻撃
	IBehaviorNode::State CloseRangeAttacks(float elapsdTime);
	//遠距離攻撃
	IBehaviorNode::State RangedAttack(float elapsdTime);
	//何もしない
	IBehaviorNode::State DoNothing();
	//逃げる
	IBehaviorNode::State RunAway(float elapsdTime);
};


/*メモ
　BehaviorTreeクラスでインスタンスしてそのインスタンスをstd::bindでポインタで渡しているのでコンストラクタで渡したプレイヤや敵などを使用することができる
　
*/