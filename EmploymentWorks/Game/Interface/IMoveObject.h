/*
* �����I�u�W�F�N�g�̃C���^�[�t�F�[�X
*/
#pragma once
//#include "pch.h"
#include "Game/Interface/ICollisionObject.h"

class IMoveObject : public ICollisionObject
{
public:
	//�f�X�g���N�^
	virtual ~IMoveObject() = default;
	//�X�V����
	virtual void  Update(const float& elapsedTime) = 0;


};
