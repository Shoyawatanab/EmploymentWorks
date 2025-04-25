#include "pch.h"
#include "Game/Observer/Messenger.h"
#include "Game/Observer/Telegram.h"


//初期化
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
/// イベントのオブザーバーの追加
/// </summary>
/// <param name="type">イベントの種類</param>
/// <param name="observer">オブザーバー</param>
void Messenger::Attach(MessageType type, IObserver* observer)
{

	m_eventList[type].push_back(observer);

}

/// <summary>
/// イベントを呼ぶ
/// </summary>
/// <param name="type">イベントの種類</param>
/// <param name="datas">必要なデータ</param>
void Messenger::Notify(::MessageType type, void* datas)
{

	auto it = m_eventList.find(type);

	//あれば
	if (it != m_eventList.end())
	{

		for (auto& obsever : it->second)
		{
			Telegram telegram(type, datas);
			obsever->Notify(telegram);

		}

	}

}





