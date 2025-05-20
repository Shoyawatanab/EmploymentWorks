/*
	@file	BarrierPreliminaryAction.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "Game/Interface/IActione.h"

// �O���錾
class CommonResources;
class CharacterEntity;
class BarrierDefenseAction;


namespace mylib
{
	class DebugCamera;
	class GridFloor;
}



class BarrierPreliminaryAction : public IAction
{
public:
	//���쎞��
	static constexpr float  PRELOMINARY_TIME = 2.0f;

public:
	//�R���X�g���N�^
	BarrierPreliminaryAction(CommonResources* resources,
		BarrierDefenseAction* barrierDefenseAction,
		CharacterEntity* owner
		);

	//�f�X�g���N�^
	~BarrierPreliminaryAction() override;
	//������
	void Initialize() override;
	// �X�V����
	ActionState Update(const float& elapsedTime) override;
	//��Ԃɓ�������
	void Enter() override;
	//��Ԃ𔲂�����
	void Exit() override;
private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;

	//�o�ߎ���
	float m_time;
	//���L��
	CharacterEntity* m_owner;
	//�R���g���[���[
	BarrierDefenseAction* m_barrierDefenseAction;


};
