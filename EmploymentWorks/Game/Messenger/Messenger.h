#pragma once
#include "Libraries/WataLib/Singleton.h"
#include "GameBase/Messenger/IObserver.h"
#include "Game/Messenger/MessageParams.h"
#include <unordered_map>



class Messenger : public Singleton<Messenger>
{
	friend class Singleton<Messenger>;

public:
	//�R���X�g���N�^
	Messenger();
	//�f�X�g���N�^
	~Messenger() override;
	//���X�g�ɓo�^
	void Rigister(std::vector<MessageType> types,IObserver* observer);
	//�ʒm
	void Notify(MessageType type, void* = nullptr);
	//�N���A
	void Clear();

private:

	std::unordered_map<MessageType, std::vector<IObserver*>> m_list;

};




