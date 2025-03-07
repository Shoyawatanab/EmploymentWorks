/*
* �X�e�[�ƃp�^�[���̃C���^�[�t�F�[�X
*/
#pragma once
#include "pch.h"

class IState;
class CommonResources;


class IStateMachine
{
public:
	//�f�X�g���N�^
	virtual ~IStateMachine() = default;
	//������
	virtual void Initialize(CommonResources* resources, IState* startState = nullptr) = 0;
	// �X�V����
	virtual void Update(const float& elapsedTime) = 0;
	//�`��
	virtual void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) = 0;
	//��Ԃ̕ύX
	virtual void ChangeState(IState* nextState) = 0;

};
