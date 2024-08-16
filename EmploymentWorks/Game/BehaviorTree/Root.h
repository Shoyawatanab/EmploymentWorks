/*
	Root.h
	渡邊翔也
	ビヘイビアツリーのノード
	順番に子を実行する
	全ての子が実行できるとSuccess
	子が失敗したらすぐにFailureを反す
*/
#pragma once
#include "Interface/ICompositeNode.h"


class CommonResources;


class Root : public ICompositeNode
{




private:
	//CommonResources* m_commonResources;

	//子ノード配列
	std::unique_ptr<IBehaviorNode> m_childNode;


public:
	Root();
	~Root() override;

	void Initialize() override;
	IBehaviorNode::State Update(float elapsedTime) override;
	IBehaviorNode::State RunningUpdate(float elapsedTime) override;

	void Render();
	void Finalize() override;

	void AddNode(std::unique_ptr<IBehaviorNode> node)  override;


};