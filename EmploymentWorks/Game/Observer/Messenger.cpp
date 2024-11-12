#include "pch.h"
#include "Game/Observer/Messenger.h"
#include "Interface/IObserver.h"



std::unordered_map<std::string, std::function<void()>> Messenger::m_eventList;

//�C�x���g���̐ݒ�

const std::string Messenger::SLOWMOTION = "SlowMotion";

const std::string Messenger::SLOWMOTIONEND = "SlowMotionEnd";

/// <summary>
/// �ώ@�҂��A�^�b�`
/// </summary>
/// <param name="name">�C�x���g��</param>
/// <param name="event">�o�^�֐�</param>
void Messenger::Attach(std::string name, std::function<void()> eventFunction)
{
	//�C�x���g��o�^
	m_eventList[name] = eventFunction;



}

// �ώ@�҂��f�^�b�`����
void Messenger::Detach(std::string name)
{
	//�C�x���g��T��
	auto it = m_eventList.find(name);
	//�C�x���g�����邩�ǂ���
	if (it != m_eventList.end())
	{
		//����ꍇ
		//�C�x���g���폜
		m_eventList.erase(name);

	}



}

// �ώ@�҂ɒʒm����
void Messenger::Notify(std::string name)
{
	//�o�^���ꂽ�֐��̎��s
	m_eventList[name]();
}



