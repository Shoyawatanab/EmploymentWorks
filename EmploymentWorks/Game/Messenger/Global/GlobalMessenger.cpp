/*
	�N���X��     : GlobalMessenger
	����         : �V�[�����܂���Messenger
	�⑫�E���ӓ_ :
*/
#include "pch.h"
#include "GlobalMessenger.h"

/// <summary>
/// �R���X�g���N
/// </summary>
GlobalMessenger::GlobalMessenger()
	:
	m_list{}
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
GlobalMessenger::~GlobalMessenger()
{
	m_list.clear();
}

/// <summary>
/// ���X�g�ɒǉ�
/// </summary>
/// <param name="types">�o�^����^�C�v�z��</param>
/// <param name="observer">�I�u�U�[�o�[</param>
void GlobalMessenger::Rigister(std::vector<GlobalMessageType> types, IObserver<GlobalMessageType>* observer)
{
	//�^�C�v������
	for (auto& type : types)
	{
		//�ǉ�
		m_list[type].push_back(observer);

	}
}

/// <summary>
/// ���X�g����폜
/// </summary>
/// <param name="observer">�폜����I�u�U�[�o�[</param>
void GlobalMessenger::Delete(IObserver<GlobalMessageType>* observer)
{

	//Type������
	for (auto& type : m_list)
	{
		//Type���ƂɃI�u�U�[�o�[�����邩�T��
		auto it = std::find(type.second.begin(), type.second.end(), observer);

		//���݂����
		if (it != type.second.end())
		{
			//�폜
			type.second.erase(it);
		}
	}

}

/// <summary>
/// �ʒm����
/// </summary>
/// <param name="type">�ʒm�̎��</param>
/// <param name="datas">�ǉ��f�[�^</param>
void GlobalMessenger::Notify(GlobalMessageType type, void* datas)
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

void GlobalMessenger::Clear()
{
	m_list.clear();
}
