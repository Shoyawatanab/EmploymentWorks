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
	std::unordered_map<int, IBaseObserver*> m_characterSingleEventList;


public:


	//�Q�[���C�x���g���X�g�ɒǉ�
	void Rigister(GamePlayMessageType type, IObserver<GamePlayMessageType>* observer);
	//�Q�[���C�x���g�̒ʒm
	void Notify(GamePlayMessageType type, void* datas = nullptr);
		

	/// <summary>
	/// �L�����N�^�[�C�x���g���X�g�ɒǉ�
	/// </summary>
	/// <typeparam name="T">���b�Z�[�W�̎��</typeparam>
	/// <param name="enemyId">���g�̃I�u�W�F�N�gID</param>
	/// <param name="observer">���g</param>
	template<typename T>
	void Rigister(int enemyId, IObserver<T>* observer)
	{
		//�ǉ�
		m_characterSingleEventList[enemyId] = observer;

	};
		

	/// <summary>
	/// �L�����N�^�[�C�x���g�̒ʒm
	/// </summary>
	/// <typeparam name="T">���b�Z�[�W�̎��</typeparam>
	/// <param name="enemyId">���肽���I�u�W�F�N�gID</param>
	/// <param name="type">���b�Z�[�W�̎��</param>
	/// <param name="datas">�K�v�f�[�^</param>
	template<typename T>
	void Notify(int enemyId, T type, void* datas = nullptr)
	{
		//����悪���邩
		auto it = m_characterSingleEventList.find(enemyId);

		//�����
		if (it != m_characterSingleEventList.end())
		{
			//�L���X�g�����������
			if (auto* observer = dynamic_cast<IObserver<T>*>(it->second))
			{
				Telegram<T> telegram(type, datas);
				observer->Notify(telegram);

			}

		}
	};


	//�C�x���g�̃N���A
	void Clear();

public:


	// �R���X�g���N�^
	Messenger();
	//�f�X�g���N�^
	~Messenger() ;


public:


	
};







