#pragma once


#include <unordered_map>
#include <functional>
#include "Game/Observer/EventParams.h"
#include "Game/Interface/IObserver.h"
#include "Libraries/WataLib/Singleton.h"

// Subject�N���X���`����
class Messenger : public Singleton<Messenger>
{
	

private:
	//�C�x���g���X�g
	std::unordered_map<GameMessageType, std::vector<IObserver<GameMessageType>*>> m_eventList;


public:


	// �ώ@�҂��A�^�b�`
	void Rigister(GameMessageType type, IObserver<GameMessageType>* observer);
	// �ʒm����
	void Notify(GameMessageType type, void* datas = nullptr);
	//�C�x���g�̃N���A
	void Clear();

public:


	// �R���X�g���N�^
	Messenger();
	//�f�X�g���N�^
	~Messenger();


public:


	
};







