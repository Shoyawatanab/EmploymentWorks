#pragma once
#include "Game/Entities/ItemEntity.h"
#include "Libraries/WataLib/Singleton.h"

// 前方宣言
class CommonResources;
class Player;



class ItemAcquisition : public Singleton<ItemAcquisition>
{

public:

	enum class State
	{
		RECOVERABLE     //回収可能
		,NOT_RECOVERABLE  //回収不可
	};

	struct  ItemDatas
	{
		State State;
		int ID;
		ItemEntity* ItemEntity;
	};

	static constexpr float RECOVERBLE_RADIUS = 2.0f;

public:

	//コンストラクタ
	ItemAcquisition();
	//デストラクタ
	~ItemAcquisition();

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
	//プレイヤ
	Player* m_player;
	//アイテム
	std::vector<ItemDatas> m_items;




private:



};