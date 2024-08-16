/*
	ActionNode.h
	渡邊翔也
	ビヘイビアツリーの実行のみのノード
	子を持たない
*/

#pragma once
#include "Interface/ILeafNode.h"
#include <functional>

class CommonResources;
class ExecutionNode;
class Player;
class Enemy;

class ActionNode : public ILeafNode
{




private:
	//CommonResources* m_commonResources;

	//関数を登録する変数
	std::function<IBehaviorNode::State(float)> m_executionNode;
	
public:
	ActionNode(std::function<IBehaviorNode::State(float)> fun);
	~ActionNode() override;

	void Initialize()override;
	IBehaviorNode::State Update(float elapsedTime) override;
	IBehaviorNode::State RunningUpdate(float elapsedTime) override;


	void Render();
	void Finalize()override;



};
/*メモ
  
  関数の登録変数の（float）を書いているけど登録する関数に引数がなくても正常に動いているので謎
  ()と(float)の２つを作らなきといけないと思ったけどいけてしまった
  BehaviorTreeクラスで引数が必要な関数にはstd::placeholders::_1をいている

　UpdateとRunningUpdateが中身が同じなので直したい
 　ただ実行中ノードがあるならRunningUpdateに入ってUpdateは呼ばれない
*/