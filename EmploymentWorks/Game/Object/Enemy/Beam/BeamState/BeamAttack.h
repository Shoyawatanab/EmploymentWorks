#pragma once
#include <pch.h>
#include "Interface/IBeamState.h"
class CommonResources;

class Boomerang;
class Beam;

// BeamAttack�N���X���`����
class BeamAttack : public IBeamState
{
public:





public:
	// �R���X�g���N�^
	BeamAttack();
	// �f�X�g���N�^
	~BeamAttack();
	// ����������
	void Initialize();

	// �X�V����
	void Update(const float& elapsedTime);

	void Enter();
	void Exit();

	//�N���X�ɕK�v�ȏ��i�|�C���^�j�̓o�^
	void RegistrationInformation(CommonResources* resoure, Beam* beam);


private:

private:

	// ���ʃ��\�[�X
	CommonResources* m_commonResources;

	Beam* m_beam;


};

