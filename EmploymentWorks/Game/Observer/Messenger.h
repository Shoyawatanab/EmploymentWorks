#pragma once


#include <unordered_map>
#include <functional>
#include "Game/Observer/EventParams.h"
#include "Game/Interface/IObserver.h"
#include "Libraries/WataLib/Singleton.h"

// Subject�N���X���`����
class Messenger : public Singleton<Messenger>
{
	

public:

	std::unordered_map<MessageType, std::vector<IObserver*>> m_eventList;


public:


	// �ώ@�҂��A�^�b�`
	void Attach(MessageType type, IObserver* observer);
	// �ʒm����
	void Notify(MessageType type, void* datas);


public:


	// �R���X�g���N�^
	Messenger();
	~Messenger();


public:


	
};







