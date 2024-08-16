/*
	ExecutionNode.h
	渡邊翔也
	実行ノードに渡す処理の関数の管理クラス
*/

#pragma once
#include "Interface/IBehaviorNode.h"

class CommonResources;
class Player;
class Enemy;

class ExecutionNode 
{




private:
	//CommonResources* m_commonResources;

	Player* m_palyer;
	Enemy* m_enemy;


	//FindToPlayer用変数

	// ReturnToTheStartingPoint用変数
	
	//ChaseToPlayer用変数
	static constexpr float CHASESPEED = 0.5f;

	float m_moveDistance;
	//Rotation用変数
	
	float m_rotationTime;
	DirectX::SimpleMath::Quaternion m_rotate;

	// Wait用変数
	float m_waitTime;

public:
	ExecutionNode(Player* player, Enemy* enmey);
	~ExecutionNode();



	IBehaviorNode::State ChaseToPlayer(float elapsdTime);


	IBehaviorNode::State Wait(float elapsdTime);

	IBehaviorNode::State Patrol(float elapsdTime);

};


/*メモ
　BehaviorTreeクラスでインスタンスしてそのインスタンスをstd::bindでポインタで渡しているのでコンストラクタで渡したプレイヤや敵などを使用することができる
　
*/