/*
	SelectorNode.h
	渡邊翔也
	ビヘイビアツリーのノード
	成功する子が見つかるまで子を実行する
	見つかったらSuccessを返す
	見つからないとFailureを返す
*/#pragma once
#include "Interface/ICompositeNode.h"

class CommonResources;


class SelectorNode : public ICompositeNode
{




private:
	//CommonResources* m_commonResources;

	//子ノード配列
	std::vector<std::unique_ptr<IBehaviorNode>> m_childNode;

	//実行中ノードの格納変数
	IBehaviorNode* m_runningNode;


public:
	SelectorNode();
	~SelectorNode() override;

	void Initialize() override;
	IBehaviorNode::State Update(float elapsedTime) override;
	IBehaviorNode::State RunningUpdate(float elapsedTime) override;

	void Render();
	void Finalize()override;

	void AddNode(std::unique_ptr<IBehaviorNode> node)  override;



}; 
