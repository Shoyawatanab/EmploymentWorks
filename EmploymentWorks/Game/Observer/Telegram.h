#pragma once

#include "EventParams.h"
//
//struct Telegram
//{
//	// メッセージタイプ
//	GameMessageType messageType;
//	// 追加情報
//	void* extraInfo;
//	
//
//	// コンストラクタ
//	Telegram()
//		:
//		messageType(GameMessageType::None),
//		extraInfo(nullptr)
//	{
//	}
//
//
//
//	// コンストラクタ
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
	// メッセージタイプ
	MessageType messageType;
	// 追加情報
	void* extraInfo;


	// コンストラクタ
	Telegram()
		:
		messageType(),
		extraInfo(nullptr)
	{
	}


	// コンストラクタ
	Telegram(MessageType msg, void* info = nullptr)
		:
		messageType(msg),
		extraInfo(info)
	{
	}


};


		
