/*
* �X�e�[�ƃp�^�[���̃C���^�[�t�F�[�X
*/
#pragma once
#include "pch.h"

class CommonResources;


class IState
{
public:
	//�f�X�g���N�^
	virtual ~IState() = default;
	//������
	virtual void Initialize(CommonResources* resources) = 0;
	// �X�V����
	virtual void Update(const float& elapsedTime) = 0;
	//�`��
	virtual void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) = 0;
	//��Ԃɓ�������
	virtual void Enter() = 0;
	//��Ԃ𔲂�����
	virtual void Exit() = 0;



};
