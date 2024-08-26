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


private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;

	// ���f��
	std::unique_ptr<DirectX::Model> m_model;


public:
	Sky();
	~Sky();

	void Initialize(CommonResources* resources);
	void Update(float elapsedTime, DirectX::SimpleMath::Quaternion cameraRotation);
	void Render(DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection);
	void Finalize();


private:
};
