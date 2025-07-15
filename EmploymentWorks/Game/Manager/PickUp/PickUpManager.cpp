/*
	�N���X��     : PickUpManager
	����         : �E������}�l�[�W���[
	�⑫�E���ӓ_ :
*/
#include "pch.h"
#include "PickUpManager.h"
#include "Game/Component/PickUp/PickableComponent.h"
#include "Game/Component/PickUp/PickerComponent.h"
#include "Game/Component/Components.h"

/// <summary>
/// �R���X�g���N
/// </summary>
PickUpManager::PickUpManager()
{
}



/// <summary>
/// �f�X�g���N�^
/// </summary>
PickUpManager::~PickUpManager()
{
}



/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime"></param>
void PickUpManager::Update(const float& deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	//���郊�X�g������
	for (auto& [type, actors] : m_list)
	{
		//�����
		auto picker = actors.first;

		//����ł��Ȃ��ꍇ
		if (!picker->GetIsPickUp())
		{
			continue;
		}

		//����Ώۂ̃��[�v
		for (auto& pickble : actors.second)
		{
			//����\�łȂ��Ȃ�
			if (!pickble->GetIsPossible())
			{
				continue;
			}

			//���������߂�
			auto distance = DirectX::SimpleMath::Vector3::Distance(picker->GetActor()->GetTransform()->GetWorldPosition(), pickble->GetActor()->GetTransform()->GetWorldPosition());

			//�͈͂Ȃ�
			if (distance <= picker->GetPickUpRadius())
			{
				//����\�łȂ���ԂȂ�
				if (!picker->GetIsRecoverable())
				{
					//����ł���悤�ɂ��������̊֐�
					picker->OnRecoverable();
					//��Ԃ�����\��
					picker->SetIsRecoverable(true);
				}
			}
			else
			{

				//����\��ԂȂ�
				if (picker->GetIsRecoverable())
				{
					//����ł��Ȃ��Ȃ����Ƃ��̊֐�
					picker->OnUnrecoverable();
					//��Ԃ�����s��
					picker->SetIsRecoverable(false);

				}

			}


		}

	}


}

/// <summary>
/// ����̎��s
/// </summary>
void PickUpManager::TryPickUp(PickerComponent* picker)
{
	
	//����\��Ԃ��̔���
	if (!picker->GetIsRecoverable())
	{
		return;
	}

	//�^�C�v�̎擾
	auto type = picker->GetPickUpType();

	//����Ώۂ̎擾
	auto pickables = m_list[type].second;

	//��ԋ߂�����Ώۂ̎擾
	auto pickable = CheckPickUp(picker, pickables);

	//�k����������
	if (!pickable)
	{
		return;
	}


	picker->OnPickUp();
	pickable->OnPickUp();
	picker->OnUnrecoverable();

}

/// <summary>
/// ����҂̒ǉ�
/// </summary>
/// <param name="type">����^�C�v</param>
/// <param name="comp">�R���|�[�l���g</param>
void PickUpManager::AddPicker(PickUpType type, PickerComponent* comp)
{
	auto& typeList = m_list[type];
	typeList.first = comp;
}

/// <summary>
/// �E���镨�̒ǉ�
/// </summary>
/// <param name="type">����^�C�v</param>
/// <param name="comp">�R���|�[�l���g</param>
void PickUpManager::AddPickable(PickUpType type, PickableComponent* comp)
{
	auto& typeList = m_list[type];
	typeList.second.push_back(comp);
}


/// <summary>
/// ����ł��邩
/// </summary>
/// <param name="picker">�����</param>
/// <param name="picktables">����Ώ�</param>
/// <returns>����Ώ� or �k��</returns>
PickableComponent* PickUpManager::CheckPickUp(PickerComponent* picker, std::vector<PickableComponent*> pickables)
{


	using namespace DirectX::SimpleMath;

	//����҂̍��W�擾
	Vector3 pickerPos = picker->GetActor()->GetTransform()->GetWorldPosition();

	//��ԋ߂�����Ώۂ̎擾
	auto it = std::min_element(pickables.begin(), pickables.end(),
		[pickerPos](PickableComponent* a, PickableComponent* b)
		{
			float distA = Vector3::Distance(pickerPos, a->GetActor()->GetTransform()->GetWorldPosition());
			float distB = Vector3::Distance(pickerPos, b->GetActor()->GetTransform()->GetWorldPosition());
			return distA < distB;
		});

	return (it != pickables.end()) ? *it : nullptr;
}


