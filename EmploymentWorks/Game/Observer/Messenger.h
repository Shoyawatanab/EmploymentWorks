#pragma once


#include <unordered_map>
#include <functional>
#include "Game/Observer/EventParams.h"
#include "Game/Interface/IObserver.h"

// Subjectクラスを定義する
class Messenger 
{

public:

	static std::unordered_map<EventParams::EventType, std::vector<IObserver*>> m_eventList;

public:

	// 観察者をアタッチ
	static void Attach(EventParams::EventType type, IObserver* observer);
	
	// 通知する
	static void Notify(EventParams::EventType type,void* datas);

public:

	//イベント名の変数

	
};







