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
	std::unordered_map<int, IBaseObserver*> m_characterSingleEventList;


public:


	//ゲームイベントリストに追加
	void Rigister(GamePlayMessageType type, IObserver<GamePlayMessageType>* observer);
	//ゲームイベントの通知
	void Notify(GamePlayMessageType type, void* datas = nullptr);
		

	/// <summary>
	/// キャラクターイベントリストに追加
	/// </summary>
	/// <typeparam name="T">メッセージの種類</typeparam>
	/// <param name="enemyId">自身のオブジェクトID</param>
	/// <param name="observer">自身</param>
	template<typename T>
	void Rigister(int enemyId, IObserver<T>* observer)
	{
		//追加
		m_characterSingleEventList[enemyId] = observer;

	};
		

	/// <summary>
	/// キャラクターイベントの通知
	/// </summary>
	/// <typeparam name="T">メッセージの種類</typeparam>
	/// <param name="enemyId">送りたいオブジェクトID</param>
	/// <param name="type">メッセージの種類</param>
	/// <param name="datas">必要データ</param>
	template<typename T>
	void Notify(int enemyId, T type, void* datas = nullptr)
	{
		//送り先があるか
		auto it = m_characterSingleEventList.find(enemyId);

		//あれば
		if (it != m_characterSingleEventList.end())
		{
			//キャストが成功すれば
			if (auto* observer = dynamic_cast<IObserver<T>*>(it->second))
			{
				Telegram<T> telegram(type, datas);
				observer->Notify(telegram);

			}

		}
	};


	//イベントのクリア
	void Clear();

public:


	// コンストラクタ
	Messenger();
	//デストラクタ
	~Messenger() ;


public:


	
};







