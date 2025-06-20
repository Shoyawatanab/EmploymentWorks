/*
	@file	WalkAction.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "Game/Interface/IActione.h"
#include "GameBase/Actor.h"

// �O���錾
class CommonResources;



class WalkAction : public IAction
{

public:

	static  constexpr float ROTATESPEED = 1.0f;

	//��������
	static constexpr float WALK_TIME = 4.0f;


public:
	//�R���X�g���N�^
	WalkAction(Actor* own
		, Actor* target);
	//�f�X�g���N�^
	~WalkAction() override ;
	//������
	void Initialize() override;
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
	//����
	float m_time;
};
