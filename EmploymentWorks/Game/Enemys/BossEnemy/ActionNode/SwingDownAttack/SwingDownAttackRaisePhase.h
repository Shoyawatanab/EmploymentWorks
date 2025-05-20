/*
	@file	SwingDownAttackRaisePhase.h
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


class SwingDownAttackRaisePhase : public IAction
{
public:
	//�U��グ����
	static constexpr float RAISE_TIME = 2.0f;

public:
	//�R���X�g���N�^
	SwingDownAttackRaisePhase(CommonResources* resources,
		ActionStateController* controller
		, CharacterEntity* owner
		);
	//�f�X�g���N�^
	~SwingDownAttackRaisePhase() override ;
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
	//����
	float m_time;
	//�R���g���[���[
	ActionStateController* m_controller;


};
