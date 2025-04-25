#pragma once


#include <unordered_map>
#include <functional>
#include "Game/Observer/EventParams.h"
#include "Game/Interface/IObserver.h"

// Subjectクラスを定義する
class Messenger 
{

public:

	std::unordered_map<MessageType, std::vector<IObserver*>> m_eventList;


public:

	static Messenger* GetInstance();

	static void DestroyInstance();

	// 観察者をアタッチ
	void Attach(MessageType type, IObserver* observer);
	// 通知する
	void Notify(MessageType type, void* datas);


private:

	// コピー・ムーブ禁止
	Messenger(const Messenger&) = delete;
	Messenger& operator=(const Messenger&) = delete;
	Messenger(Messenger&&) = delete;
	Messenger& operator=(Messenger&&) = delete;
	// コンストラクタ
	Messenger();


public:

	//
	static std::unique_ptr<Messenger> s_messenger;

	
};







