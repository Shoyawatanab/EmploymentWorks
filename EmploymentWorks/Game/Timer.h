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
	
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tenTexture;

	// �e�N�X�`���̔����̑傫��
	DirectX::SimpleMath::Vector2 m_tenTexCenter;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_timeTexture;

	// �e�N�X�`���̔����̑傫��
	DirectX::SimpleMath::Vector2 m_timeTexCenter;


	float m_totalTime;

	//1�̔ԍ��̍����ƕ�
	float m_width;
	float m_height;

	DirectX::SimpleMath::Vector2 m_position;
	float m_scale;

	//�b����1����
	int m_secFirstDigit;
	//�b����2����
	int m_secSecondDigit;
	//������1����
	int m_minFirstDigit;
	//������2����
	int m_minSecondDigit;



public:
	Timer();
	~Timer() ;

	void Initialize(CommonResources* resources);
	void Update(float elapsedTime);
	void Render();

	void OneNumberRender(int number , DirectX::SimpleMath::Vector2 Pos,float Scale);
	void TexRender(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& Tex, DirectX::SimpleMath::Vector2& Center, DirectX::SimpleMath::Vector2 Pos, float Scale);

	void CreateNumberTex(const wchar_t* szFileName, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& tex, DirectX::SimpleMath::Vector2& texCenter);
	void CreateTex(const wchar_t* szFileName, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& tex, DirectX::SimpleMath::Vector2& texCenter);

	void TimeCalculation();

	void TimeReset();

private:


};
