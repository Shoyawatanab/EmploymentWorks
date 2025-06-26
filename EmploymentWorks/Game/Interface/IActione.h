/*
	IBehaviorNode.h
	�n��Ė�
	�s���̃C���^�t�F�[�X
*/
#pragma once
#include "pch.h"
#include "Game/Interface/IBehaviorNode.h"



class IAction
{
public:
	//�A�N�V�����̏��
	enum class ActionState
	{
		NONE,
		RUNNING,
		END
	};

public:
	//�f�X�g���N�^
	virtual ~IAction() = default;
	//������
	//virtual void Initialize() = 0;
	//�X�V����
	virtual ActionState Update(const float& elapsedTime) = 0;
	//��Ԃɓ�������
	virtual void Enter() = 0;
	//��Ԃ𔲂�����
	virtual void Exit() = 0;

};
