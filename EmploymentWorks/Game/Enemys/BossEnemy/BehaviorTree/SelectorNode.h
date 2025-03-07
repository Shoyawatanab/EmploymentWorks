/*
	SelectorNode.h
	渡邊翔也
	ビヘイビアツリーのノード
	成功する子が見つかるまで子を実行する
	見つかったらSuccessを返す
	見つからないとFailureを返す
*/#pragma once
#include "Game/Interface/ICompositeNode.h"

class CommonResources;


class SelectorNode : public ICompositeNode
{

public:
	//コンストラクタ
	SelectorNode();
	//デストラクタ
	~SelectorNode() override;
	//初期化
	void Initialize() override;
	//更新
	IBehaviorNode::State Update(float elapsedTime) override;
	//実行中の更新
	IBehaviorNode::State RunningUpdate(float elapsedTime) override;

	void Finalize()override;
	//ノードの追加
	void AddNode(std::unique_ptr<IBehaviorNode> node)  override;

private:
	//子ノード配列
	std::vector<std::unique_ptr<IBehaviorNode>> m_childNode;

	//実行中ノードの格納変数
	IBehaviorNode* m_runningNode;


}; 
