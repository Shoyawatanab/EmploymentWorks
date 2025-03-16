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
/// ������
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
void ItemAcquisition::Initialize(CommonResources* resources)
{

	m_commonResources = resources;

}

/// <summary>
/// �X�V
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

	// �L�[�{�[�h�X�e�[�g�g���b�J�[���擾����
	const auto& kbTracker = m_commonResources->GetInputManager()->GetKeyboardTracker();
	
	if (kbTracker->released.F)
	{

		auto it = std::remove_if(m_items.begin(), m_items.end(),
			[](const ItemDatas& item) {
				return item.State == State::Recoverable;  // State����v����ꍇ
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


	// ID�Ɉ�v����A�C�e��������
	auto it = std::remove_if(
		m_items.begin(), m_items.end(),
		[id](const ItemDatas& item) 
		{ 
			return item.ID == id; 
		}
	);

	// ���ۂɍ폜
	m_items.erase(it, m_items.end());

}

void ItemAcquisition::AddPlayer(Player* player)
{
	m_player = player;
}
