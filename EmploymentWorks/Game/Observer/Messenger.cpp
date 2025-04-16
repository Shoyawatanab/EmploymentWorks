#include "pch.h"
#include "Game/Observer/Messenger.h"



std::unordered_map<EventParams::EventType, std::vector<IObserver*>> Messenger::m_eventList;


/// <summary>
/// イベントのオブザーバーの追加
/// </summary>
/// <param name="type">イベントの種類</param>
/// <param name="observer">オブザーバー</param>
void Messenger::Attach(EventParams::EventType type, IObserver* observer)
{

	m_eventList[type].push_back(observer);

}

/// <summary>
/// イベントを呼ぶ
/// </summary>
/// <param name="type">イベントの種類</param>
/// <param name="datas">必要なデータ</param>
void Messenger::Notify(EventParams::EventType type, void* datas)
{

	auto it = m_eventList.find(type);

	//あれば
	if (it != m_eventList.end())
	{

		for (auto& obsever : it->second)
		{
			obsever->Notify(type,datas);
		}

	}

}





