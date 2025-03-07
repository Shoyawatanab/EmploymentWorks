/*
* �X�e�[�ƃp�^�[���̃C���^�[�t�F�[�X
*/
#pragma once
#include "pch.h"
#include "Game/Interface/IBehaviorNode.h"

class CommonResources;


class IActionState
{
public:
	//�f�X�g���N�^
	virtual ~IActionState() = default;
	//������
	virtual void Initialize(CommonResources* resources) = 0;
	// �X�V����
	virtual IBehaviorNode::State Update(const float& elapsedTime) = 0;
	//��Ԃɓ�������
	virtual void Enter() = 0;
	//��Ԃ𔲂�����
	virtual void Exit() = 0;



};
