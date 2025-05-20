#include "pch.h"
#include "Game/Observer/Enemy/EnemyMessenger.h"
#include "Game/Observer/Telegram.h"


/// <summary>
/// �R���X�g���N
/// </summary>
EnemyMessenger::EnemyMessenger()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
EnemyMessenger::~EnemyMessenger()
{
}


/// <summary>
/// �C�x���g�̃I�u�U�[�o�[�̒ǉ�
/// </summary>
/// <param name="type">�C�x���g�̎��</param>
/// <param name="observer">�I�u�U�[�o�[</param>
void EnemyMessenger::Rigister(int enemyId, IObserver<EnemyMessageType>* observer)
{
	//�ǉ�
	m_eventList[enemyId] = observer;

}

/// <summary>
/// �C�x���g���Ă�
/// </summary>
/// <param name="type">�C�x���g�̎��</param>
/// <param name="datas">�K�v�ȃf�[�^</param>
void EnemyMessenger::Notify(int enemyId, EnemyMessageType type, void* datas)
{
	//����悪���邩
	auto it = m_eventList.find(enemyId);

	//�����
	if (it != m_eventList.end())
	{		
		Telegram telegram(type, datas);
		it->second->Notify(telegram);
	
	}

}





