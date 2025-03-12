#pragma once
/*
	@file	Score.h.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "pch.h"
#include <array>

// �O���錾
class CommonResources;



class Score final 
{
public:

	//�����Ԋu
	static constexpr int NUMBER_SPACINT = 100;

	static constexpr int ANIMATION_TIME = 2;

public:

	void SetScale(DirectX::SimpleMath::Vector2 scale) { m_scale = scale; }

	void SetPosition(DirectX::SimpleMath::Vector2 position) { m_position = position; }

	//�X�R�A���Z
	void AddScore(float score) { m_score += score; }
	//�X�R�A����
	void DecreasedScore(float score) { m_score -= score; }

public:
	
	Score();

	~Score() ;

	void Initialize(CommonResources* resources);

	void Update(float elapsedTime);

	void Render();

	void Reset();

private:

	void CreateNumberTex(const wchar_t* szFileName, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& tex);

	void OneNumberRender(int number, DirectX::SimpleMath::Vector2 Pos, DirectX::SimpleMath::Vector2 Scale);

	void SplitDigits(int number);

private:

	CommonResources* m_commonResources;

	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;

	DirectX::SimpleMath::Vector2 m_position;

	DirectX::SimpleMath::Vector2 m_scale;

	float m_score;

	//1����
	std::array<int,4> m_digit;

	//1�̔ԍ��̍����ƕ�
	float m_width;
	float m_height;

	float m_time;

	//�������邩
	int m_digitCount;

};
