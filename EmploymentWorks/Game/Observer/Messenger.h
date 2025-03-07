#pragma once


#include <unordered_map>
#include <functional>
#include "Game/Observer/EventParams.h"
#include "Game/Interface/IObserver.h"

// Subject�N���X���`����
class Messenger 
{

public:

	static std::unordered_map<EventParams::EventType, std::vector<IObserver*>> m_eventList;

public:

	// �ώ@�҂��A�^�b�`
	static void Attach(EventParams::EventType type, IObserver* observer);
	
	// �ʒm����
	static void Notify(EventParams::EventType type,void* datas);

public:

	//�C�x���g���̕ϐ�

	
};







