/*
	�N���X��     : GlobalMessenger
	����         : �V�[�����܂����Ȃ�Messenger
	�⑫�E���ӓ_ :
*/
#include "pch.h"
#include "SceneMessenger.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneMessenger::SceneMessenger()
	:
	m_list{}
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneMessenger::~SceneMessenger()
{
	m_list.clear();
}

/// <summary>
/// ���X�g�ɒǉ�
/// </summary>
/// <param name="types">�o�^����^�C�v�z��</param>
/// <param name="observer">�I�u�U�[�o�[</param>
void SceneMessenger::Rigister(std::vector<SceneMessageType> types, IObserver<SceneMessageType>* observer)
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
void SceneMessenger::Delete(IObserver<SceneMessageType>* observer)
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
void SceneMessenger::Notify(SceneMessageType type, void* datas)
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

/// <summary>
/// �N���A
/// </summary>
void SceneMessenger::Clear()
{
	m_list.clear();
}









