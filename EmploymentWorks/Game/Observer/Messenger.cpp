#include "pch.h"
#include "Game/Observer/Messenger.h"
#include "Interface/IObserver.h"



std::unordered_map<std::string, std::function<void()>> Messenger::m_eventList;
std::unordered_map<std::string, std::function<void(DirectX::SimpleMath::Vector3)>> Messenger::m_eventList2;

//�C�x���g���̐ݒ�

const std::string Messenger::SLOWMOTION = "SlowMotion";

const std::string Messenger::SLOWMOTIONEND = "SlowMotionEnd";

const std::string Messenger::CREATEHITEFFECTS = "CreateHitEffects";


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

void Messenger::Attach2(std::string name, std::function<void(DirectX::SimpleMath::Vector3)> eventFunction)
{

	//�C�x���g��o�^
	m_eventList2[name] = eventFunction;


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

void Messenger::Notify2(std::string name, DirectX::SimpleMath::Vector3 pos)
{
	m_eventList2[name](pos);
}



