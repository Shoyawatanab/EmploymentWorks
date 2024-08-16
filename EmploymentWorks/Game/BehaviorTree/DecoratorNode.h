/*
	DecoratorNode.h
	渡邊翔也
	ビヘイビアツリーの条件判定のノード
	条件を通れば子のステートを返す
	　　　通らなければFailureを返す
*/
#pragma once
#include "Interface/ICompositeNode.h"

class CommonResources;


class DecoratorNode : public ICompositeNode
{




private:
	//CommonResources* m_commonResources;

	//子ノード配列
	std::unique_ptr<IBehaviorNode> m_childNode;


	//関数を登録する変数
	std::function<bool()> m_condition;


public:
	DecoratorNode(std::function<bool()> fun);
	~DecoratorNode() override;

	void Initialize() override;
	IBehaviorNode::State Update(float elapsedTime) override;
	IBehaviorNode::State RunningUpdate(float elapsedTime) override;

	void Render();
	void Finalize() override ;

	void AddNode(std::unique_ptr<IBehaviorNode> node)  override;

	void AddConditions();

}; 

/*メモ
　UpdateとRunningUpdateが中身が同じなので直したい
 　ただ実行中ノードがあるならRunningUpdateに入ってUpdateは呼ばれない
*/