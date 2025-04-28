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
	
	IBehaviorNode::State Action();

private:
	CommonResources* m_commonResources;

	Player* m_palyer;
	BossEnemy* m_enemy;


};


/*メモ
　BehaviorTreeクラスでインスタンスしてそのインスタンスをstd::bindでポインタで渡しているのでコンストラクタで渡したプレイヤや敵などを使用することができる
　
*/