#pragma once
#ifndef IOBSERVER_DEFINED
#define IOBSERVER_DEFINED

#include "Game/Observer/EventParams.h"

// IObserverインターフェースを定義する
class IObserver
{
public:
	//通知時に呼び出される
	virtual void Notify(EventParams::EventType type,void* datas) = 0;

};

#endif	// IOBSERVER_DEFINED
