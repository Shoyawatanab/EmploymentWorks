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
	//ゲームイベントリスト
	std::unordered_map<GamePlayMessageType, std::vector<IObserver<GamePlayMessageType>*>> m_gameEventList;

	//キャラ単体イベントの保存リスト
	std::unordered_map<int, IObserver<EnemyMessageType>*> m_characterSingleEventList;


public:


	//ゲームイベントリストに追加
	void Rigister(GamePlayMessageType type, IObserver<GamePlayMessageType>* observer);
	//ゲームイベントの通知
	void Notify(GamePlayMessageType type, void* datas = nullptr);

	//キャラクターイベントリストに追加
	void Rigister(int enemyId, IObserver<EnemyMessageType>* observer);
	//キャラクターイベントの通知
	void Notify(int enemyId, EnemyMessageType type, void* datas = nullptr);



	//イベントのクリア
	void Clear();

public:


	// コンストラクタ
	Messenger();
	//デストラクタ
	~Messenger() ;


public:


	
};







