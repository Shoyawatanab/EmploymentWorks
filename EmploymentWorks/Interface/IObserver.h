#pragma once
#ifndef IOBSERVER_DEFINED
#define IOBSERVER_DEFINED
#include "Interface/ISubject.h"

class ISubject;

// IObserver�C���^�[�t�F�[�X���`����
class IObserver
{
public:
	// �L�[����������ꂽ�玞�ɌĂяo�����
	virtual void OnKeyPressed(const DirectX::Keyboard::Keys& key) = 0;

};

#endif	// IOBSERVER_DEFINED
