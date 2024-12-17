#include "pch.h"
#include "Game/Observer/Messenger.h"
#include "Interface/IObserver.h"



std::unordered_map<std::string, std::function<void()>> Messenger::m_eventList;
std::unordered_map<std::string, std::function<void(DirectX::SimpleMath::Vector3)>> Messenger::m_eventList2;

//イベント名の設定

const std::string Messenger::SLOWMOTION = "SlowMotion";

const std::string Messenger::SLOWMOTIONEND = "SlowMotionEnd";

const std::string Messenger::CREATEHITEFFECTS = "CreateHitEffects";


/// <summary>
/// 観察者をアタッチ
/// </summary>
/// <param name="name">イベント名</param>
/// <param name="event">登録関数</param>
void Messenger::Attach(std::string name, std::function<void()> eventFunction)
{
	//イベントを登録
	m_eventList[name] = eventFunction;
}

void Messenger::Attach2(std::string name, std::function<void(DirectX::SimpleMath::Vector3)> eventFunction)
{

	//イベントを登録
	m_eventList2[name] = eventFunction;


}

// 観察者をデタッチする
void Messenger::Detach(std::string name)
{
	//イベントを探す
	auto it = m_eventList.find(name);
	//イベントがあるかどうか
	if (it != m_eventList.end())
	{
		//ある場合
		//イベントを削除
		m_eventList.erase(name);
	}
}

// 観察者に通知する
void Messenger::Notify(std::string name)
{
	//登録された関数の実行
	m_eventList[name]();
}

void Messenger::Notify2(std::string name, DirectX::SimpleMath::Vector3 pos)
{
	m_eventList2[name](pos);
}



