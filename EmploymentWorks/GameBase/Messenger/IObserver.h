#pragma once
#include "Game/Messenger/MessageParams.h"

// IObserverインターフェースを定義する
class IObserver 
{
public:
	//通知時に呼び出される
	virtual void Notify(MessageType type,void* datas) = 0;

};

