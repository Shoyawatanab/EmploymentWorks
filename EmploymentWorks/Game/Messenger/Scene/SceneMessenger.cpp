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









