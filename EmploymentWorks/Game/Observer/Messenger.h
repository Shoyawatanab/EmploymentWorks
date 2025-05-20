#pragma once


#include <unordered_map>
#include <functional>
#include "Game/Observer/EventParams.h"
#include "Game/Interface/IObserver.h"
#include "Libraries/WataLib/Singleton.h"

// Subjectクラスを定義する
class Messenger : public Singleton<Messenger>
{
	

private:
	//イベントリスト
	std::unordered_map<GameMessageType, std::vector<IObserver<GameMessageType>*>> m_eventList;


public:


	// 観察者をアタッチ
	void Rigister(GameMessageType type, IObserver<GameMessageType>* observer);
	// 通知する
	void Notify(GameMessageType type, void* datas = nullptr);
	//イベントのクリア
	void Clear();

public:


	// コンストラクタ
	Messenger();
	//デストラクタ
	~Messenger();


public:


	
};







