/*
	@file	WalkActionComtroller.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "GameBase/Action/ActionController.h"
#include "Game/Enemies/BossEnemy/Action/Walk/WalkAction.h"
#include "Game/Enemies/BossEnemy/Action/Orientation/OrientationAction.h"
#include "GameBase/Actor.h"

// �O���錾
class BossEnemy;


class WalkActionComtroller : public ActionController
{

public:

	static  constexpr float ROTATESPEED = 1.0f;

public:
	//�R���X�g���N
	WalkActionComtroller(BossEnemy* own
		, Actor* target);
	//�f�X�g���N�^
	~WalkActionComtroller() override;

private:
	//�^�[�Q�b�g
	Actor* m_target;
	//���L��
	BossEnemy* m_own;
	//�������
	std::unique_ptr<WalkAction> m_walkingAction;
	//��]���
	std::unique_ptr<OrientationAction> m_orientation;

};
