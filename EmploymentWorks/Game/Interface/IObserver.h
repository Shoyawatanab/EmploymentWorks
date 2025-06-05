#pragma once
#ifndef IOBSERVER_DEFINED
#define IOBSERVER_DEFINED

#include "Game/Observer/Telegram.h"
#include "Game/Interface/IBaseObserver.h"

//int m_observerId = 0;

// IObserver�C���^�[�t�F�[�X���`����
template<typename T>
class IObserver : public IBaseObserver
{
public:
	//�ʒm���ɌĂяo�����
	virtual void Notify(const Telegram<T> &telegram) = 0;

private:

	//static int m_observerId;

};

#endif	// IOBSERVER_DEFINED
