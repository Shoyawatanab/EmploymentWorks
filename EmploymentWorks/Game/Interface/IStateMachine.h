/*
* �X�e�[�ƃp�^�[���̃C���^�[�t�F�[�X
*/
#pragma once
#include "pch.h"

class IState;
class CommonResources;


template<typename T>
class IStateMachine
{
public:
	//�f�X�g���N�^
	virtual ~IStateMachine() = default;
	// �X�V����
	virtual void Update(const float& elapsedTime) = 0;
	//��Ԃ̕ύX
	virtual void ChangeState(T* nextState) = 0;

};
