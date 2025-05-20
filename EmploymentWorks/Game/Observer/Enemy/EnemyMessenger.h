#pragma once


#include <unordered_map>
#include <functional>
#include "Game/Observer/EventParams.h"
#include "Game/Interface/IObserver.h"
#include "Libraries/WataLib/Singleton.h"

// Subject�N���X���`����
class EnemyMessenger : public Singleton<EnemyMessenger>
{
	

public:

	//�C�x���g�̕ۑ����X�g
	std::unordered_map<int, IObserver<EnemyMessageType>*> m_eventList;

public:

	// �ώ@�҂��A�^�b�`
	void Rigister(int enemyId, IObserver<EnemyMessageType>* observer);
	// �ʒm����
	void Notify(int enemyId,EnemyMessageType type, void* datas = nullptr);


public:


	// �R���X�g���N�^
	EnemyMessenger();
	//�f�X�g���N�^
	~EnemyMessenger();


public:


	
};







