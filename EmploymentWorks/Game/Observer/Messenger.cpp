#include "pch.h"
#include "Game/Observer/Messenger.h"
#include "Game/Observer/Telegram.h"



Messenger::Messenger()
{
}

Messenger::~Messenger()
{
}


/// <summary>
/// イベントのオブザーバーの追加
/// </summary>
/// <param name="type">イベントの種類</param>
/// <param name="observer">オブザーバー</param>
void Messenger::Rigister(GamePlayMessageType type, IObserver<GamePlayMessageType>* observer)
{

	m_gameEventList[type].push_back(observer);

}

/// <summary>
/// イベントを呼ぶ
/// </summary>
/// <param name="type">イベントの種類</param>
/// <param name="datas">必要なデータ</param>
void Messenger::Notify(GamePlayMessageType type, void* datas)
{

	auto it = m_gameEventList.find(type);

	//あれば
	if (it != m_gameEventList.end())
	{

		for (auto& obsever : it->second)
		{
			Telegram telegram(type, datas);
			obsever->Notify(telegram);

		}

	}

}



void Messenger::Clear()
{

	m_gameEventList.clear();
	m_characterSingleEventList.clear();

}





