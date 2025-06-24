#pragma once
/*
	@file	Sky.h.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "pch.h"

// �O���錾
class CommonResources;




class Sky 
{
public:


public:
	//�R���X�g���N
	Sky(CommonResources* resources
		, DirectX::SimpleMath::Vector3 scale,
		DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Quaternion rotation);
	//�f�X�g���N�^
	~Sky() ;

	//IObject
		//������
	void Initialize() ;
	//�`��
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) ;
	//�X�V����
	void  Update(const float& elapsedTime) ;

private:

	// ���f��
	DirectX::Model* m_model;
};
