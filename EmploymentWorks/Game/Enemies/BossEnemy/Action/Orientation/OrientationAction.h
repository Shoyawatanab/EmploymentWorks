/*
	@file	OrientationAction.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "Game/Interface/IActione.h"
#include "GameBase/Actor.h"

// �O���錾
class CommonResources;




class OrientationAction : public IAction
{

public:

	static  constexpr float ROTATESPEED = 1.0f;


public:
	//�R���X�g���N�^
	OrientationAction(Actor* own
		, Actor* target);
	//�f�X�g���N�^
	~OrientationAction() override ;
	//�X�V����
	ActionState Update(const float& elapsedTime)  override ;
	//��Ԃɓ�������
	void Enter() override ;
	//��Ԃ𔲂�����
	void Exit() override;



private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	//�^�[�Q�b�g
	Actor* m_target;
	//���L��
	Actor* m_own;
};
