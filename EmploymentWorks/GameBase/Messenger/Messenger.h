/*
	�N���X��     : Messenger
	����         : ���b�Z�[�W�𑗂�N���X
	�⑫�E���ӓ_ :
*/
#pragma once
#include "GameBase/WataLib/Singleton.h"
#include <unordered_map>
#include "GameBase/Messenger/IObserver.h"

template<typename MessageType>
class IObserver;


template<typename MessageType>
class Messenger : public Singleton<Messenger<MessageType>>
{
	friend class Singleton<Messenger<MessageType>>;

public:
	//�R���X�g���N�^
	Messenger()
		:
		m_list{}
	{

	};

	//�f�X�g���N�^
	~Messenger() override
	{
		//�N���A
		m_list.clear();
	};

	//���X�g�ɓo�^
	void Rigister(std::vector<MessageType> types, IObserver<MessageType>* observer)
	{
		//�^�C�v������
		for (auto& type : types)
		{
			//�ǉ�
			m_list[type].push_back(observer);

		}
	};
	
	//���X�g����폜
	void Delete(IObserver<MessageType>* observer)
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

	};

	//�ʒm
	void Notify(MessageType type, void* datas = nullptr)
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
			obsever->FunctionExecution(type, datas);
		}

	};
	
	//�N���A
	void Clear()
	{
		m_list.clear();

	};

private:

	//���X�g
	std::unordered_map<MessageType, std::vector<IObserver<MessageType>*>> m_list;

};




