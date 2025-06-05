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
	BoomerangRepelled(Boomerang* boomerang);
	// �f�X�g���N�^
	~BoomerangRepelled();
	//������
	void Initialize(CommonResources* resources) ;
	// �X�V����
	void Update(const float& elapsedTime) override;
	//��Ԃɓ�������
	void Enter() override;
	//��Ԃ𔲂�����
	void Exit() override;



private:
	//�u�[������
	Boomerang* m_boomerang;

	// ���[���h�}�g���b�N�X
	DirectX::SimpleMath::Matrix m_worldMatrix;
	//����
	DirectX::SimpleMath::Vector3 m_direction;
	//���W
	DirectX::SimpleMath::Vector3 m_position;
	//�p���[
	float m_pwoer;
	//�d��
	float m_graivty;


};

