//�e����鏈��

#pragma once
#include <pch.h>
#include "Game/Interface/IState.h"

class Boomerang;

// BoomerangRepelled�N���X���`����
class BoomerangRepelled : public IState
{
public:

	DirectX::SimpleMath::Matrix GetMatrix() { return m_worldMatrix; }

public:
	// �R���X�g���N�^
	BoomerangRepelled();
	// �f�X�g���N�^
	~BoomerangRepelled();
	//������
	void Initialize(CommonResources* resources) override;
	// �X�V����
	void Update(const float& elapsedTime) override;
	//�`��
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;
	//��Ԃɓ�������
	void Enter() override;
	//��Ԃ𔲂�����
	void Exit() override;

	//�N���X�ɕK�v�ȏ��i�|�C���^�j�̓o�^
	void AddPointer(Boomerang* boomerang);


private:
	Boomerang* m_boomerang;

	// ���[���h�}�g���b�N�X
	DirectX::SimpleMath::Matrix m_worldMatrix;

	DirectX::SimpleMath::Vector3 m_direction;

	DirectX::SimpleMath::Vector3 m_position;

	float m_pwoer;

	float m_graivty;


};

