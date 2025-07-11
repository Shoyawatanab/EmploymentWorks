/*
	�N���X��     : BoomerangDrop
	����         : �u�[�������̃h���b�v�̏��
	�⑫�E���ӓ_ :
*/
#pragma once
#include "GameBase/Interface/IState.h"

class BoomerangStateMachine;
class Boomerang;

class BoomerangDrop : public IState
{
public:
	//���˕Ԃ�̗�
	static constexpr float BOUNCE_POWER = 3.0f;;

public:
	//�R���X�g���N�^
	BoomerangDrop(BoomerangStateMachine* stateMahine, Boomerang* boomerang);
	//�f�X�g���N�^
	~BoomerangDrop() override;

	// �X�V����
	void Update(const float& deltaTime) override;
	//��Ԃɓ�������
	void Enter() override;
	//��Ԃ𔲂�����
	void Exit() override;

private:
	//�u�[������
	Boomerang* m_boomerang;
	//�X�e�[�g�}�V�[��
	BoomerangStateMachine* m_stateMahine;
};

