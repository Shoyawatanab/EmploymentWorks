#include "pch.h"
#include "Messenger.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Messenger::Messenger()
	:
	m_list{}
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Messenger::~Messenger()
{
}

/// <summary>
/// ���X�g�ɒǉ�
/// </summary>
/// <param name="types">�o�^����^�C�v�z��</param>
/// <param name="observer">�I�u�U�[�o�[</param>
void Messenger::Rigister(std::vector<MessageType> types, IObserver* observer)
{
	//�^�C�v������
	for (auto& type : types)
	{
		//�ǉ�
		m_list[type].push_back(observer);

	}
	
}

void Messenger::Notify(MessageType type, void* datas)
{
	//�T��
	auto it = m_list.find(type);
	//�Ȃ����
	if (it == m_list.end())
	{
		return;
	}

	//�I�u�U�[�o�[�ɒʒm
	for (auto& obsever : it->second)
	{
		obsever->Notify(type, datas);
	}


}









