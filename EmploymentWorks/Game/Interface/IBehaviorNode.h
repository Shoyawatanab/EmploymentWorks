/*
	IBehaviorNode.h
	�n��Ė�
	�r�w�C�r�A�c���[�̎��s�݂̂̃m�[�h
	�q�������Ȃ�
*/
#pragma once
#include "pch.h"



class IBehaviorNode
{
public:

	//���s���
	enum class State
	{
		SUCCESS,         //����
		FAILURE,      //���s
		RUNNING      //���s��
	};

public:
	//�f�X�g���N�^
	virtual ~IBehaviorNode() = default;
	//������
	virtual void Initialize() = 0;
	//�X�V����
	virtual State Update(float elapsdTime) = 0;

	//���s���̎���Update
	virtual State RunningUpdate(float elapsdTime) = 0;

	virtual void Finalize() = 0;
};
