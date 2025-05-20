#include "pch.h"
#include "ItemAcquisition.h"
#include "Libraries/MyLib/InputManager.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/WataLib/DetectionCollision.h"

#include "Libraries/WataLib/Bounding.h"
#include "Game/Player/Player.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
ItemAcquisition::ItemAcquisition()
	:
	m_commonResources{}
	,m_player{}
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ItemAcquisition::~ItemAcquisition()
{
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
		//�A�C�e���ƃv���C���Ƃ̋���
		float lenght = Vector3::Distance(itemPos, playerPos);
		//����\�Ȃ�
		if (lenght <= RECOVERBLE_RADIUS)
		{

			item.State = State::RECOVERABLE;
			recoverableCount++;

		}
		else
		{
			item.State = State::NOT_RECOVERABLE;

		}

	}

	// �L�[�{�[�h�X�e�[�g�g���b�J�[���擾����
	const auto& kbTracker = m_commonResources->GetInputManager()->GetKeyboardTracker();
	
	if (kbTracker->released.F)
	{

		auto it = std::remove_if(m_items.begin(), m_items.end(),
			[](const ItemDatas& item) {
				return item.State == State::RECOVERABLE;  // State����v����ꍇ
			});

		if (it != m_items.end())
		{
			it->ItemEntity->OnAcquired();

		}
		
	}

}

/// <summary>
/// �A�C�e���̒ǉ�
/// </summary>
/// <param name="id">�I�u�W�F�N�gID</param>
/// <param name="item">�A�C�e��</param>
void ItemAcquisition::AddItem(int id,ItemEntity* item)
{

	ItemDatas itemData;
	
	itemData.ID = id;
	itemData.ItemEntity = item;
	itemData.State = State::NOT_RECOVERABLE;

	m_items.push_back(itemData);

}

/// <summary>
/// �A�C�e���̍폜
/// </summary>
/// <param name="id">�I�u�W�F�N�gID</param>
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
