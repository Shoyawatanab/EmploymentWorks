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
	////������
	//virtual void Initialize() = 0;
	//// �X�V����
	//virtual void Update(const float& elapsedTime) = 0;
	////��Ԃɓ�������
	//virtual void Enter() = 0;
	////��Ԃ𔲂�����
	//virtual void Exit() = 0;
	//Matrix�̎擾
	virtual const DirectX::SimpleMath::Matrix& GetViewMatrix() = 0;

};
