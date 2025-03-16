#include "pch.h"
#include "ItemAcquisition.h"
#include "Libraries/MyLib/InputManager.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/WataLib/DetectionCollision.h"

#include "Libraries/WataLib/Bounding.h"
#include "Game/Player/Player.h"

using namespace DirectX::SimpleMath;


ItemAcquisition* ItemAcquisition::GetInstance()
{
	static ItemAcquisition instance;

	return &instance;
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="resources">共通リソース</param>
void ItemAcquisition::Initialize(CommonResources* resources)
{

	m_commonResources = resources;

}

/// <summary>
/// 更新
/// </summary>
void ItemAcquisition::Update()
{

	int recoverableCount = 0;

	for (auto& item : m_items)
	{

		Vector3 itemPos = item.ItemEntity->GetPosition();

		Vector3 playerPos = m_player->GetPosition();

		float lenght = Vector3::Distance(itemPos, playerPos);

		if (lenght <= 2.0f)
		{

			item.State = State::Recoverable;
			recoverableCount++;

		}
		else
		{
			item.State = State::NotReturnable;

		}

	}

	// キーボードステートトラッカーを取得する
	const auto& kbTracker = m_commonResources->GetInputManager()->GetKeyboardTracker();
	
	if (kbTracker->released.F)
	{

		auto it = std::remove_if(m_items.begin(), m_items.end(),
			[](const ItemDatas& item) {
				return item.State == State::Recoverable;  // Stateが一致する場合
			});

		if (it != m_items.end())
		{
			it->ItemEntity->OnAcquired();

		}
		
	}

}

void ItemAcquisition::AddItem(int id,ItemEntity* item)
{

	ItemDatas itemData;
	
	itemData.ID = id;
	itemData.ItemEntity = item;
	itemData.State = State::NotReturnable;

	m_items.push_back(itemData);

}

void ItemAcquisition::DeleteItem(int id)
{


	// IDに一致するアイテムを検索
	auto it = std::remove_if(
		m_items.begin(), m_items.end(),
		[id](const ItemDatas& item) 
		{ 
			return item.ID == id; 
		}
	);

	// 実際に削除
	m_items.erase(it, m_items.end());

}

void ItemAcquisition::AddPlayer(Player* player)
{
	m_player = player;
}
