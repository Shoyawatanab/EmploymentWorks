/*
	@file	WalkingActionComtroller.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "Game/Entities/ActionStateController.h"
#include "Game/Enemys/BossEnemy/ActionNode/Walking/WalkingAction.h"
#include "Game/Enemys/BossEnemy/ActionNode/Orientation/OrientationAction.h"

// �O���錾
class CommonResources;
class CharacterEntity;

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class WalkingActionComtroller : public ActionStateController
{

public:

	static  constexpr float ROTATESPEED = 1.0f;

public:
	//�R���X�g���N
	WalkingActionComtroller(CommonResources* resources,
		CharacterEntity* own
		, CharacterEntity* target);
	//�f�X�g���N�^
	~WalkingActionComtroller();

private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	//�^�[�Q�b�g
	CharacterEntity* m_target;
	//���L��
	CharacterEntity* m_own;
	//�������
	std::unique_ptr<WalkingAction> m_walkingAction;
	//��]���
	std::unique_ptr<OrientationAction> m_orientation;

};
