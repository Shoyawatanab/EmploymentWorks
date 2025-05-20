/*
	@file	SwingDownAttackSwingPhase.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "Game/Interface/IActione.h"

// �O���錾
class CommonResources;
class CharacterEntity;
class ActionStateController;

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class SwingDownAttackSwingPhase : public IAction
{
public:
	//�U�艺�낵����
	static constexpr float SWING_TIME = 3.0f;


public:
	//�R���X�g���N�^
	SwingDownAttackSwingPhase(CommonResources* resources,
		ActionStateController* controller
		, CharacterEntity* owner
		);
	//�f�X�g���N�^
	~SwingDownAttackSwingPhase() override ;
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
	//���L��
	CharacterEntity* m_owner;
	//�R���g���[���[
	ActionStateController* m_controller;


	float m_time;
	

};
