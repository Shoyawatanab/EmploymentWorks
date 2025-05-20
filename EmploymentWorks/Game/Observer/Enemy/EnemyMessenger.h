#pragma once


#include <unordered_map>
#include <functional>
#include "Game/Observer/EventParams.h"
#include "Game/Interface/IObserver.h"
#include "Libraries/WataLib/Singleton.h"

// Subjectクラスを定義する
class EnemyMessenger : public Singleton<EnemyMessenger>
{
	

public:

	//イベントの保存リスト
	std::unordered_map<int, IObserver<EnemyMessageType>*> m_eventList;

public:

	// 観察者をアタッチ
	void Rigister(int enemyId, IObserver<EnemyMessageType>* observer);
	// 通知する
	void Notify(int enemyId,EnemyMessageType type, void* datas = nullptr);


public:


	// コンストラクタ
	EnemyMessenger();
	//デストラクタ
	~EnemyMessenger();


public:


	
};







