#include "pch.h"
#include "Game/Observer/Messenger.h"
#include "Game/Observer/Telegram.h"


//������
std::unique_ptr<Messenger> Messenger::s_messenger = nullptr;

Messenger::Messenger()
{
}

Messenger* Messenger::GetInstance()
{
	if (s_messenger == nullptr)
	{
		s_messenger = std::unique_ptr<Messenger>(new Messenger());
	}


	return s_messenger.get();
}

void Messenger::DestroyInstance()
{
	s_messenger.reset();
}

/// <summary>
/// �C�x���g�̃I�u�U�[�o�[�̒ǉ�
/// </summary>
/// <param name="type">�C�x���g�̎��</param>
/// <param name="observer">�I�u�U�[�o�[</param>
void Messenger::Attach(MessageType type, IObserver* observer)
{

	m_eventList[type].push_back(observer);

}

/// <summary>
/// �C�x���g���Ă�
/// </summary>
/// <param name="type">�C�x���g�̎��</param>
/// <param name="datas">�K�v�ȃf�[�^</param>
void Messenger::Notify(::MessageType type, void* datas)
{

	auto it = m_eventList.find(type);

	//�����
	if (it != m_eventList.end())
	{

		for (auto& obsever : it->second)
		{
			Telegram telegram(type, datas);
			obsever->Notify(telegram);

		}

	}

}





