/*
* �J������State�̃C���^�[�t�F�[�X
*/
#pragma once
#include "pch.h"
#include "Game/Interface/IState.h"


class ICamera : public IState
{
public:
	//�f�X�g���N�^
	virtual ~ICamera() = default;
	//Matrix�̎擾
	virtual const DirectX::SimpleMath::Matrix& GetViewMatrix() = 0;

};
