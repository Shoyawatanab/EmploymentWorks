#pragma once
#ifndef IOBSERVER_DEFINED
#define IOBSERVER_DEFINED

#include "Game/Observer/Telegram.h"

// IObserver�C���^�[�t�F�[�X���`����
class IObserver
{
public:
	//�ʒm���ɌĂяo�����
	virtual void Notify(const Telegram &telegram) = 0;

};

#endif	// IOBSERVER_DEFINED
