#pragma once
#ifndef IOBSERVER_DEFINED
#define IOBSERVER_DEFINED
#include "Game/Messenger/MessageParams.h"

// IObserver�C���^�[�t�F�[�X���`����
class IObserver 
{
public:
	//�ʒm���ɌĂяo�����
	virtual void Notify(MessageType type,void* datas) = 0;

};

#endif	
