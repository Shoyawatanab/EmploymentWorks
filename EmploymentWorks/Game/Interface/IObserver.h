#pragma once
#ifndef IOBSERVER_DEFINED
#define IOBSERVER_DEFINED

#include "Game/Observer/Telegram.h"
#include "Game/Interface/IBaseObserver.h"

//int m_observerId = 0;

// IObserverインターフェースを定義する
template<typename T>
class IObserver : public IBaseObserver
{
public:
	//通知時に呼び出される
	virtual void Notify(const Telegram<T> &telegram) = 0;

private:

	//static int m_observerId;

};

#endif	// IOBSERVER_DEFINED
