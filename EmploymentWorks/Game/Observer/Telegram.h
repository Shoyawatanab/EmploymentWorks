#pragma once

#include "EventParams.h"

struct Telegram
{
	// メッセージタイプ
	MessageType messageType;
	// 追加情報
	void* extraInfo;
	

	// コンストラクタ
	Telegram()
		:
		messageType(MessageType::None),
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


		
