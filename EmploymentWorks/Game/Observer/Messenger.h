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
	//�Q�[���C�x���g���X�g
	std::unordered_map<GamePlayMessageType, std::vector<IObserver<GamePlayMessageType>*>> m_gameEventList;

	//�L�����P�̃C�x���g�̕ۑ����X�g
	std::unordered_map<int, IObserver<EnemyMessageType>*> m_characterSingleEventList;


public:


	//�Q�[���C�x���g���X�g�ɒǉ�
	void Rigister(GamePlayMessageType type, IObserver<GamePlayMessageType>* observer);
	//�Q�[���C�x���g�̒ʒm
	void Notify(GamePlayMessageType type, void* datas = nullptr);

	//�L�����N�^�[�C�x���g���X�g�ɒǉ�
	void Rigister(int enemyId, IObserver<EnemyMessageType>* observer);
	//�L�����N�^�[�C�x���g�̒ʒm
	void Notify(int enemyId, EnemyMessageType type, void* datas = nullptr);



	//�C�x���g�̃N���A
	void Clear();

public:


	// �R���X�g���N�^
	Messenger();
	//�f�X�g���N�^
	~Messenger() ;


public:


	
};







