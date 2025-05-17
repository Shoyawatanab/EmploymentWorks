#pragma once

#include "EventParams.h"
//
//struct Telegram
//{
//	// ���b�Z�[�W�^�C�v
//	GameMessageType messageType;
//	// �ǉ����
//	void* extraInfo;
//	
//
//	// �R���X�g���N�^
//	Telegram()
//		:
//		messageType(GameMessageType::None),
//		extraInfo(nullptr)
//	{
//	}
//
//
//
//	// �R���X�g���N�^
//	Telegram(GameMessageType msg, void* info = nullptr)
//		:
//		messageType(msg),
//		extraInfo(info)
//	{
//	}
//	
//
//};

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


		
