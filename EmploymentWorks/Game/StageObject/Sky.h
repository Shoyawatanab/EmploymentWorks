#pragma once
/*
	@file	Sky.h.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "pch.h"
#include "Game/Entities/BaseEntity.h"

// �O���錾
class CommonResources;




class Sky : public BaseEntity
{


public:
	Sky(CommonResources* resources
		, DirectX::SimpleMath::Vector3 scale,
		DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Quaternion rotation);


	//�f�X�g���N�^
	~Sky() override;

	//IObject
		//������
	void Initialize() override;
	//�`��
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;
	//�X�V����
	void  Update(const float& elapsedTime) override;

private:

	// ���f��
	DirectX::Model* m_model;
};
