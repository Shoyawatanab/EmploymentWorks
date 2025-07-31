/*
	�N���X��    : ObserverComponent
	����        : �ʒm���󂯎��R���|�[�l���g
	�⑫�E���ӓ_:
*/

#pragma once
#include "GameBase/Component.h"
#include "GameBase/Actor.h"
#include "Game/Messenger/Messenger.h"
#include "Game/Messenger/IObserver2.h"

//�ʒm�̎��
template<typename MessageType>
class ObserverComponent : public Component , public IObserver2<MessageType>
{
public:
	//�R���X�g���N
	ObserverComponent(Actor* owner)
		:
		Component(owner)
	{

	};

	//�f�X�g���N�^
	~ObserverComponent() override
	{
		//�폜
		m_messenger->Delete(this);
	};
	
	/// <summary>
	/// �o�^
	/// </summary>
	/// <param name="types">�ʒm�̎��</param>
	/// <param name="function">�Ăяo���֐�</param>
	void Rigister(std::vector<MessageType> types, std::function<void(MessageType, void*)> function)
	{
		//���b�Z���W���[�̎擾
		m_messenger = Messenger<MessageType>::GetInstance();
		//���b�Z���W���[�ɓo�^
		m_messenger->Rigister(types, this);
		//�Ăяo���֐��̃Z�b�g
		m_notifyFunction = function;

	};


	/// <summary>
	/// �֐����s
	/// </summary>
	/// <param name="type">�ʒm�̎��</param>
	/// <param name="datas">�ǉ��f�[�^</param>
	void FunctionExecution(MessageType type, void* datas) override
	{
		//�֐��̎��s
		m_notifyFunction(type, datas);
	}

private:

	//�Ăяo���֐�
	std::function<void(MessageType , void*)> m_notifyFunction;

	//�}�l�[�W���[
	Messenger<MessageType>* m_messenger;

};