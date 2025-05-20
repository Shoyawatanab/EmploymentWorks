/*
	@file	OrientationAction.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "Game/Interface/IActione.h"

// �O���錾
class CommonResources;
class BaseEntity;

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class OrientationAction : public IAction
{

public:

	static  constexpr float ROTATESPEED = 1.0f;


public:
	//�R���X�g���N�^
	OrientationAction(CommonResources* resources,
		BaseEntity* own
		, BaseEntity* target);
	//�f�X�g���N�^
	~OrientationAction() override ;
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
	BaseEntity* m_target;
	//���L��
	BaseEntity* m_own;
};
