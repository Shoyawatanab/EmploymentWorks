#pragma once


#include <unordered_map>
#include <functional>
#include "Game/Observer/EventParams.h"
#include "Game/Interface/IObserver.h"
#include "Libraries/WataLib/Singleton.h"

// Subjectクラスを定義する
class Messenger : public Singleton<Messenger>
{
	

public:

	std::unordered_map<MessageType, std::vector<IObserver*>> m_eventList;


public:


	// 観察者をアタッチ
	void Attach(MessageType type, IObserver* observer);
	// 通知する
	void Notify(MessageType type, void* datas);


public:


	// コンストラクタ
	Messenger();
	~Messenger();


public:


	
};







