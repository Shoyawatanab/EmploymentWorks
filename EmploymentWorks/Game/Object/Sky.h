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
	void Update(float elapsedTime);
	void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection);
	void Finalize();


private:
};
