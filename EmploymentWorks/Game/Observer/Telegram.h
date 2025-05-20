#pragma once

#include "EventParams.h"

template<typename MessageType >
struct Telegram
{
	// ���b�Z�[�W�^�C�v
	MessageType messageType;
	// �ǉ����
	void* extraInfo;


	// �R���X�g���N�^
	Telegram()
		:
		messageType(),
		extraInfo(nullptr)
	{
	}


	// �R���X�g���N�^
	Telegram(MessageType msg, void* info = nullptr)
		:
		messageType(msg),
		extraInfo(info)
	{
	}


};


		
