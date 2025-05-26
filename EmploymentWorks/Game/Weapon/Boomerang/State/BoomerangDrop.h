#pragma once
#include <pch.h>
#include "Game/Interface/IState.h"

class Boomerang;

// BoomerangDrop�N���X���`����
class BoomerangDrop : public IState
{
public:
	//���[���h�s��̎擾
	DirectX::SimpleMath::Matrix GetMatrix() { return m_worldMatrix; }

public:
	// �R���X�g���N�^
	BoomerangDrop(Boomerang* boomerang);
	// �f�X�g���N�^
	~BoomerangDrop();
	//������
	void Initialize(CommonResources* resources) ;
	// �X�V����
	void Update(const float& elapsedTime) override;
	//�`��
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;
	//��Ԃɓ�������
	void Enter() override;
	//��Ԃ𔲂�����
	void Exit() override;	//�N���X�ɕK�v�ȏ��i�|�C���^�j�̓o�^



private:
	//�u�[������
	Boomerang* m_boomerang;


	// ���[���h�}�g���b�N�X
	DirectX::SimpleMath::Matrix m_worldMatrix;

};

