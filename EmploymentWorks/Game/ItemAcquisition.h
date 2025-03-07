#pragma once
#include "Game/Entities/ItemEntity.h"

// 前方宣言
class CommonResources;
class Player;



class ItemAcquisition
{

public:

	enum class State
	{
		Recoverable     //回収可能
		,NotReturnable  //回収不可
	};

	struct  ItemDatas
	{
		State State;
		int ID;
		ItemEntity* ItemEntity;
	};

public:

	static ItemAcquisition* GetInstance();

	//初期化
	void Initialize(CommonResources* resources);
	//更新
	void Update();
	//アイテムの登録
	void AddItem(int id,ItemEntity* item);
	//アイテムの削除
	void DeleteItem(int id);

	//プレイヤの追加
	void AddPlayer(Player* player);


private:
	// 共通リソース
	CommonResources* m_commonResources;

	Player* m_player;

	std::vector<ItemDatas> m_items;


private:

	//コンストラクタ
	ItemAcquisition() {};

	ItemAcquisition(const ItemAcquisition&) = delete;
	ItemAcquisition& operator=(const ItemAcquisition&) = delete;


};