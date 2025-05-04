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




public:
	OrientationAction(CommonResources* resources,
		BaseEntity* own
		, BaseEntity* target);
	//�f�X�g���N�^
	~OrientationAction() override ;

	void Initialize() override;

	ActionState Update(const float& elapsedTime)  override ;
	//��Ԃɓ�������
	void Enter() override ;
	//��Ԃ𔲂�����
	void Exit() override;



private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;

	BaseEntity* m_target;

	BaseEntity* m_own;
};
