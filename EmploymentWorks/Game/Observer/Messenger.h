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
	// �ώ@�҂��f�^�b�`����
	static void Detach(std::string name);
	// �ʒm����
	static void Notify(std::string name);

private:

	static std::unordered_map<std::string, std::function<void()>> m_eventList;

public:

	//�C�x���g���̕ϐ�

	//�X���[���o
	static const std::string SLOWMOTION;

	static const std::string SLOWMOTIONEND;
};

#endif	// MESSENGER_DEFINED