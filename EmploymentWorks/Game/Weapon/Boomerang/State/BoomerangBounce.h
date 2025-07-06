#pragma once
#include "GameBase/Interface/IState.h"

class BoomerangStateMachine;
class Boomerang;

class BoomerangBounce : public IState
{
public:
	//���˕Ԃ�̗�
	static constexpr float BOUNCE_POWER = 3.0f;;

public:
	//�R���X�g���N�^
	BoomerangBounce(BoomerangStateMachine* stateMahine, Boomerang* boomerang);
	//�f�X�g���N�^
	~BoomerangBounce() override;

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
	//�e��������
	DirectX::SimpleMath::Vector3 m_bounceDirection;
};

