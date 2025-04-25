#pragma once

#include "EventParams.h"

struct Telegram
{
	// ���b�Z�[�W�^�C�v
	MessageType messageType;
	// �ǉ����
	void* extraInfo;
	

	// �R���X�g���N�^
	Telegram()
		:
		messageType(MessageType::None),
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


		
