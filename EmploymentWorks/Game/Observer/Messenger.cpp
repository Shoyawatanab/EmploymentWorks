#include "pch.h"
#include "Game/Observer/Messenger.h"
#include "Game/Observer/Telegram.h"



Messenger::Messenger()
{
}

Messenger::~Messenger()
{
}


/// <summary>
/// �C�x���g�̃I�u�U�[�o�[�̒ǉ�
/// </summary>
/// <param name="type">�C�x���g�̎��</param>
/// <param name="observer">�I�u�U�[�o�[</param>
void Messenger::Rigister(GamePlayMessageType type, IObserver<GamePlayMessageType>* observer)
{

	m_gameEventList[type].push_back(observer);

}

/// <summary>
/// �C�x���g���Ă�
/// </summary>
/// <param name="type">�C�x���g�̎��</param>
/// <param name="datas">�K�v�ȃf�[�^</param>
void Messenger::Notify(GamePlayMessageType type, void* datas)
{

	auto it = m_gameEventList.find(type);

	//�����
	if (it != m_gameEventList.end())
	{

		for (auto& obsever : it->second)
		{
			Telegram telegram(type, datas);
			obsever->Notify(telegram);

		}

	}

}

void Messenger::Rigister(int enemyId, IObserver<EnemyMessageType>* observer)
{

	//�ǉ�
	m_characterSingleEventList[enemyId] = observer;

}

void Messenger::Notify(int enemyId, EnemyMessageType type, void* datas)
{

	//����悪���邩
	auto it = m_characterSingleEventList.find(enemyId);

	//�����
	if (it != m_characterSingleEventList.end())
	{
		Telegram telegram(type, datas);
		it->second->Notify(telegram);

	}


}

void Messenger::Clear()
{

	m_gameEventList.clear();
	m_characterSingleEventList.clear();

}





