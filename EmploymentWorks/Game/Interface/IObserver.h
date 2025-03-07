#pragma once
#ifndef IOBSERVER_DEFINED
#define IOBSERVER_DEFINED

#include "Game/Observer/EventParams.h"

// IObserver�C���^�[�t�F�[�X���`����
class IObserver
{
public:
	// �L�[����������ꂽ�玞�ɌĂяo�����
	virtual void Notify(EventParams::EventType type,void* datas) = 0;

};

#endif	// IOBSERVER_DEFINED
