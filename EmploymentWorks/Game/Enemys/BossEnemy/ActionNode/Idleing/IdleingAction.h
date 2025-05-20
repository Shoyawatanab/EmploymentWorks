/*
	@file	IdleingAction.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "Game/Interface/IActione.h"

// �O���錾
class CommonResources;
class CharacterEntity;

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class IdleingAction : public IAction
{

public:



public:
	//�R���X�g���N�^
	IdleingAction(CommonResources* resources,
		CharacterEntity* own
		);
	//�f�X�g���N�^
	~IdleingAction() override ;
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
	CharacterEntity* m_own;
	//����
	float m_time;
};
