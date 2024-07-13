#pragma once
/*
	@file	Timer.h.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "pch.h"

// �O���錾

class CommonResources;


class Timer final 

{
public:

	//�^�C�}�[�̑傫��
	void SetTimerScale(float scale) { m_scale = scale; }
	//�^�C�}�[�̍��W
	void SetTimerPos(DirectX::SimpleMath::Vector2 Pos) { m_position = Pos; }

private:

	CommonResources* m_commonResources;
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;

	// �e�N�X�`���̔����̑傫��
	DirectX::SimpleMath::Vector2 m_texCenter;
	

	float m_totalTime;

	//1�̔ԍ��̍����ƕ�
	float m_width;
	float m_height;

	DirectX::SimpleMath::Vector2 m_position;
	float m_scale;

public:
	Timer();
	~Timer() ;

	void Initialize(CommonResources* resources);
	void Update(float elapsedTime);
	void Render();
	void OneNumberRender(int number , DirectX::SimpleMath::Vector2 Pos,float Scale);


	void CreateNumberTex(const wchar_t* szFileName, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& tex, DirectX::SimpleMath::Vector2& texCenter);


private:


};
