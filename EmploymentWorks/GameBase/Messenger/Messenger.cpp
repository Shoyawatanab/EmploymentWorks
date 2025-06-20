#include "pch.h"
#include "Messenger.h"

/// <summary>
/// コンストラクタ
/// </summary>
Messenger::Messenger()
	:
	m_list{}
{
}

/// <summary>
/// デストラクタ
/// </summary>
Messenger::~Messenger()
{
}

/// <summary>
/// リストに追加
/// </summary>
/// <param name="types">登録するタイプ配列</param>
/// <param name="observer">オブザーバー</param>
void Messenger::Rigister(std::vector<MessageType> types, IObserver* observer)
{
	//タイプだけ回す
	for (auto& type : types)
	{
		//追加
		m_list[type].push_back(observer);

	}
	
}

void Messenger::Notify(MessageType type, void* datas)
{
	//探す
	auto it = m_list.find(type);
	//なければ
	if (it == m_list.end())
	{
		return;
	}

	//オブザーバーに通知
	for (auto& obsever : it->second)
	{
		obsever->Notify(type, datas);
	}


}









