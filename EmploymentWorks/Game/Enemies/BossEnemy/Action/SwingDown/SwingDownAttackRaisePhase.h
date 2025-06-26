/*
	@file	SwingDownAttackRaisePhase.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "Game/Interface/IActione.h"
#include "GameBase/Actor.h"

// �O���錾
class CommonResources;
class SwingDownAttackActionController;

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
	SwingDownAttackRaisePhase(SwingDownAttackActionController* controller
		, Actor* owner
		);
	//�f�X�g���N�^
	~SwingDownAttackRaisePhase() override ;
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
	Actor* m_owner;
	//����
	float m_time;
	//�R���g���[���[
	SwingDownAttackActionController* m_controller;


};
