#pragma once
#include "GameBase/Actor.h"



class WeaponBase : public Actor
{
public:

	//���
	enum class WeaponState
	{
		BOOMERANG_IDLE                                 //�u�[�������ʏ���
		,BOOMERANG_GET_READY						   //�u�[�������\�����
		,BOOMERANG_THROW							   //�u�[�������������
	};

public:

	
	//��Ԃ̎擾
	WeaponState GetWeaponState() { return m_state; }
	//��Ԃ̃Z�b�g
	void SetWeaponState(WeaponState state) { m_state = state; }

public:
	//�R���X�g���N�^
	WeaponBase(Scene* scene);
	//�f�X�g���N�^
	~WeaponBase() override;

	//�X�e�[�g�̕ύX  Factory����̏�ԕω��̒ʒm�p
	void ChangeState(WeaponState nextState);
	//�ʂ̃X�e�[�g�ύX
	virtual void ActorChangeState(WeaponState nextState) = 0;

private:
	//���
	WeaponState m_state;

};

