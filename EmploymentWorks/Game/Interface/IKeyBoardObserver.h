#pragma once


#include "Game/Observer/EventParams.h"

// IObserver�C���^�[�t�F�[�X���`����
class IKeyBoardObserver
{
public:
	// �L�[����������ꂽ�玞�ɌĂяo�����
	virtual void OnKeyPressed(const DirectX::Keyboard::Keys& key) = 0;

};
