#include "pch.h"
#include "Game/Observer/Enemy/EnemyMessenger.h"
#include "Game/Observer/Telegram.h"


/// <summary>
/// コンストラク
/// </summary>
EnemyMessenger::EnemyMessenger()
{
}

/// <summary>
/// デストラクタ
/// </summary>
EnemyMessenger::~EnemyMessenger()
{
}


/// <summary>
/// イベントのオブザーバーの追加
/// </summary>
/// <param name="type">イベントの種類</param>
/// <param name="observer">オブザーバー</param>
void EnemyMessenger::Rigister(int enemyId, IObserver<EnemyMessageType>* observer)
{
	//追加
	m_eventList[enemyId] = observer;

}

/// <summary>
/// イベントを呼ぶ
/// </summary>
/// <param name="type">イベントの種類</param>
/// <param name="datas">必要なデータ</param>
void EnemyMessenger::Notify(int enemyId, EnemyMessageType type, void* datas)
{
	//送り先があるか
	auto it = m_eventList.find(enemyId);

	//あれば
	if (it != m_eventList.end())
	{		
		Telegram telegram(type, datas);
		it->second->Notify(telegram);
	
	}

}





