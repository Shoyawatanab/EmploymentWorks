#pragma once
/*
	@file	Timer.h.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "pch.h"
#include "Libraries/WataLib/UserInterface.h"

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
	//std::unique_ptr<UserInterface> m_texture;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;

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

	std::unique_ptr<UserInterface> m_numbeers[10];

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

private:


};
