#pragma once


#include <unordered_map>
#include <functional>
#include "Game/Observer/EventParams.h"
#include "Game/Interface/IObserver.h"

// Subject�N���X���`����
class Messenger 
{

public:

	std::unordered_map<MessageType, std::vector<IObserver*>> m_eventList;


public:

	static Messenger* GetInstance();

	static void DestroyInstance();

	// �ώ@�҂��A�^�b�`
	void Attach(MessageType type, IObserver* observer);
	// �ʒm����
	void Notify(MessageType type, void* datas);


private:

	// �R�s�[�E���[�u�֎~
	Messenger(const Messenger&) = delete;
	Messenger& operator=(const Messenger&) = delete;
	Messenger(Messenger&&) = delete;
	Messenger& operator=(Messenger&&) = delete;
	// �R���X�g���N�^
	Messenger();


public:

	//
	static std::unique_ptr<Messenger> s_messenger;

	
};







