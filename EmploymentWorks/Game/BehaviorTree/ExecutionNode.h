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




private:
	CommonResources* m_commonResources;

	Player* m_palyer;
	Enemy* m_enemy;

	////Patrol用変数
	//std::vector<std::unique_ptr< PatrolPointo>> m_patrolPoint;
	////目指す座標
	//DirectX::SimpleMath::Vector3 m_endPatrolPos;
	////現在のポイント番号　次の進む場所を決めるのに使用
	//int m_currentPointNumber;
	////進んでいるポイント番号
	//int m_nextPointNumber;


public:
	ExecutionNode(Player* player, Enemy* enmey);
	~ExecutionNode();

	void Initialize(CommonResources* resources);


	//プレイヤのほうに向く
	IBehaviorNode::State FacingThePlayer(float elapsdTime);
	//ビーム攻撃
	//Enemyクラスの中にある
	
	//プレイヤに近づく
	IBehaviorNode::State ApproachingThePlayer(float elapsdTime);

	//近距離攻撃
	IBehaviorNode::State CloseRangeAttacks(float elapsdTime);
	//遠距離攻撃
	IBehaviorNode::State RangedAttack(float elapsdTime);

	//何もしない
	IBehaviorNode::State DoNothing();
};


/*メモ
　BehaviorTreeクラスでインスタンスしてそのインスタンスをstd::bindでポインタで渡しているのでコンストラクタで渡したプレイヤや敵などを使用することができる
　
*/