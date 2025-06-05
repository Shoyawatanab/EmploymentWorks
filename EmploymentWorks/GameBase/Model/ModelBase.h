/*
	パーツモデルの基底クラス　どんなパーツモデルでも継承する
*/

#pragma once
#include "GameBase/Actor.h"

class ModelBase : public Actor
{
public:

	//名前の取得
	std::string  GetPartsName() const { return m_partsName; }
	//全てのパーツの取得
	const std::vector<ModelBase*>& GetAllChild() { return m_child; }

	void SetParent(ModelBase* parent);

	//自身も含めた子孫モデルを全てを返す
	std::vector<ModelBase*> GetAllDescendants();

private:
	
	void SetChild(ModelBase* child) { m_child.push_back(child); };
	//子の削除
	void RemoveChild(ModelBase* child);

	//再帰敵に子を返す関数
	void CollentDescendants(ModelBase* node, std::vector<ModelBase*>& modelBase);


public:

	//コンストラクタ
	ModelBase(Scene* scene, std::string partsName, std::string modelName);
	//デストラクタ
	~ModelBase();



private:
	//パーツ名
	std::string m_partsName;
	//子オブジェクト
	std::vector<ModelBase*>m_child;
	//親モデル
	ModelBase* m_parent;

};
