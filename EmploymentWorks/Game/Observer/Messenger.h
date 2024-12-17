#pragma once
#ifndef MESSENGER_DEFINED
#define MESSENGER_DEFINED

#include "Interface/ISubject.h"
#include <unordered_map>
#include <functional>


// Subject�N���X���`����
class Messenger : public ISubject
{
public:

	// �ώ@�҂��A�^�b�`����
	static void Attach(std::string name, std::function<void()> eventFunction);
	// �ώ@�҂��A�^�b�`����
	static void Attach2(std::string name, std::function<void(DirectX::SimpleMath::Vector3)> eventFunction);

	// �ώ@�҂��f�^�b�`����
	static void Detach(std::string name);
	// �ʒm����
	static void Notify(std::string name);
	// �ʒm����
	static void Notify2(std::string name,DirectX::SimpleMath::Vector3 pos);

private:



	static std::unordered_map<std::string, std::function<void()>> m_eventList;

	static std::unordered_map<std::string, std::function<void(DirectX::SimpleMath::Vector3)>> m_eventList2;

public:

	//�C�x���g���̕ϐ�

	//�X���[���o
	static const std::string SLOWMOTION;

	static const std::string SLOWMOTIONEND;
	
	static const std::string CREATEHITEFFECTS;
};

#endif	// MESSENGER_DEFINED


//�������Ⴄ������Notify�Ȃǂ����邩��e���v���[�g�Ȃǂ��g���Ĉ�ɂ�����




