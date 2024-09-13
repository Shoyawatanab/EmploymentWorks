/*
	BehaviorTree.h
	渡邊翔也
	ビヘイビアツリーのRootに当たるクラス
*/
#pragma once
#include "Interface/ICompositeNode.h"

class CommonResources;
class Root;
class Player;
class Enemy;

class ExecutionNode;
class Conditions;

class BehaviorTree
{




private:
	CommonResources* m_commonResources;

	//Rootで定義すると終了時にエラーをはく
	std::unique_ptr<ICompositeNode> m_root;

	Player* m_player;
	Enemy* m_enemy;

	//実行ノードクラス
	std::unique_ptr<ExecutionNode> m_executionNode;
	//条件ノードのクラス
	std::unique_ptr<Conditions> m_conditions;


	//現在の状態
	IBehaviorNode::State m_currentState;
public:
	BehaviorTree();
	~BehaviorTree();

	void Initialize(CommonResources* resources);
	void Update(float elapsedTime);
	void Render() ;
	void Finalize() ;

	void Create();


	//クラスに必要な情報（ポインタ）の登録
	void RegistrationInformation(Player* player, Enemy* enemy);

};

/*メモ
　毎フレーム初めからチェックする
　実行中ノードがあれば終わるまでは実行中のみ動かす
 

 改善するかもな点
 　一定のフレームごとにかえる？　毎フレームではなく
　　この時は実行中があればそれをどう実行していくかを考えなけらばならない
  実行中は毎フレーム実行中を動かしてなければ一定のフレームで更新をするでもよい

*/