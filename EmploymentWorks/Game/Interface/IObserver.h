#pragma once
#ifndef IOBSERVER_DEFINED
#define IOBSERVER_DEFINED

#include "Game/Observer/Telegram.h"

// IObserverインターフェースを定義する
class IObserver
{
public:
	//通知時に呼び出される
	virtual void Notify(const Telegram &telegram) = 0;

};

#endif	// IOBSERVER_DEFINED
