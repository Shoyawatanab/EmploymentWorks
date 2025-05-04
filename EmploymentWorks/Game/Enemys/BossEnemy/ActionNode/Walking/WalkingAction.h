/*
	@file	WalkingAction.h
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


class WalkingAction : public IAction
{

public:

	static  constexpr float ROTATESPEED = 1.0f;


public:




public:
	WalkingAction(CommonResources* resources,
		CharacterEntity* own
		, CharacterEntity* target);
	//�f�X�g���N�^
	~WalkingAction() override ;

	void Initialize() override;

	ActionState Update(const float& elapsedTime)  override ;
	//��Ԃɓ�������
	void Enter() override ;
	//��Ԃ𔲂�����
	void Exit() override;



private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;

	CharacterEntity* m_target;

	CharacterEntity* m_own;
	
	float m_time;
};
