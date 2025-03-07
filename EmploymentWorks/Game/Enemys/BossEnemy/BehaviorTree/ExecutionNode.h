/*
	ExecutionNode.h
	渡邊翔也
	実行ノードに渡す処理の関数の管理クラス
*/

#pragma once
#include "Game/Interface/IBehaviorNode.h"
#include  <unordered_map>

class CommonResources;
class Player;
class BossEnemy;


class ExecutionNode
{

public:
	//コンストラクタ
	ExecutionNode(Player* player, BossEnemy* enmey);
	//デストラクタ
	~ExecutionNode();
	//初期化
	void Initialize(CommonResources* resources);


	//プレイヤのほうに向く
	IBehaviorNode::State FacingThePlayer(float elapsdTime);
	//ビーム攻撃
	IBehaviorNode::State BeamAttack(float elapsdTime);
	
	//プレイヤに近づく
	IBehaviorNode::State ApproachingThePlayer(float elapsdTime);

	//近距離攻撃
	IBehaviorNode::State CloseRangeAttacks(float elapsdTime);
	//遠距離攻撃
	IBehaviorNode::State RangedAttack(float elapsdTime);

	//何もしない
	IBehaviorNode::State DoNothing();

private:
	CommonResources* m_commonResources;

	Player* m_palyer;
	BossEnemy* m_enemy;


};


/*メモ
　BehaviorTreeクラスでインスタンスしてそのインスタンスをstd::bindでポインタで渡しているのでコンストラクタで渡したプレイヤや敵などを使用することができる
　
*/