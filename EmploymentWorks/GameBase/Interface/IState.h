/*
* �X�e�[�ƃp�^�[���̃C���^�[�t�F�[�X
*/
#pragma once
#include "pch.h"

class CommonResources;


class IState
{
public:
	//�f�X�g���N�^
	virtual ~IState() = default;
	// �X�V����
	virtual void Update(const float& elapsedTime) = 0;
	//��Ԃɓ�������
	virtual void Enter() = 0;
	//��Ԃ𔲂�����
	virtual void Exit() = 0;



};
