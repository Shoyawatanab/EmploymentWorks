/*
	�N���X��     : WeaponBase
	����         : ����̃x�[�X�N���X
	�⑫�E���ӓ_ :
*/
#pragma once
#include "GameBase/Actor.h"


template<typename T>
class WeaponBase : public Actor
{
public:

	////���
	//enum class WeaponState
	//{
	//	BOOMERANG_IDLE                                 //�u�[�������ʏ���
	//	,BOOMERANG_GET_READY						   //�u�[�������\�����
	//	,BOOMERANG_THROW							   //�u�[�������������
	//	,BOOMERANG_BOUNCE							   //�u�[���������˕Ԃ���
	//};

public:

	//��Ԃ̎擾
	T GetState() { return m_state; }
	//��Ԃ̃Z�b�g
	void SetState(T state) { m_state = state; }

public:
	//�R���X�g���N�^
	WeaponBase(Scene* scene)
		:
		Actor(scene)
		,m_state{}
	{
	};

	//�f�X�g���N�^
	~WeaponBase() override
	{
	};

	//�X�e�[�g�̕ύX  Factory����̏�ԕω��̒ʒm�p
	void ChangeState(T nextState) 
	{
		//�ʂ̃X�e�[�g�ύX
		ActorChangeState(nextState);

		//��Ԃ̕ύX
		m_state = nextState;
	};

	//�ʂ̃X�e�[�g�ύX
	virtual void ActorChangeState(T nextState) = 0;

private:
	//���
	T m_state;

};

