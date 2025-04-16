#include "pch.h"
#include "Game/Observer/Messenger.h"



std::unordered_map<EventParams::EventType, std::vector<IObserver*>> Messenger::m_eventList;


/// <summary>
/// �C�x���g�̃I�u�U�[�o�[�̒ǉ�
/// </summary>
/// <param name="type">�C�x���g�̎��</param>
/// <param name="observer">�I�u�U�[�o�[</param>
void Messenger::Attach(EventParams::EventType type, IObserver* observer)
{

	m_eventList[type].push_back(observer);

}

/// <summary>
/// �C�x���g���Ă�
/// </summary>
/// <param name="type">�C�x���g�̎��</param>
/// <param name="datas">�K�v�ȃf�[�^</param>
void Messenger::Notify(EventParams::EventType type, void* datas)
{

	auto it = m_eventList.find(type);

	//�����
	if (it != m_eventList.end())
	{

		for (auto& obsever : it->second)
		{
			obsever->Notify(type,datas);
		}

	}

}





