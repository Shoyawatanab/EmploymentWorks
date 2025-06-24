#pragma once
#include "Libraries/WataLib/Singleton.h"
#include "GameBase/Messenger/IObserver.h"
#include "Game/Messenger/MessageParams.h"
#include <unordered_map>



class Messenger : public Singleton<Messenger>
{
	friend class Singleton<Messenger>;

public:
	//コンストラクタ
	Messenger();
	//デストラクタ
	~Messenger() override;
	//リストに登録
	void Rigister(std::vector<MessageType> types,IObserver* observer);
	//通知
	void Notify(MessageType type, void* = nullptr);
	//クリア
	void Clear();

private:

	std::unordered_map<MessageType, std::vector<IObserver*>> m_list;

};




