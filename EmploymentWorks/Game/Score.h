#pragma once
/*
	@file	Score.h.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "pch.h"
#include <array>

// 前方宣言
class CommonResources;



class Score final 
{
public:

	//文字間隔
	static constexpr int NUMBER_SPACINT = 100;

	static constexpr int ANIMATION_TIME = 2;

public:

	void SetScale(DirectX::SimpleMath::Vector2 scale) { m_scale = scale; }

	void SetPosition(DirectX::SimpleMath::Vector2 position) { m_position = position; }

	//スコア加算
	void AddScore(float score) { m_score += score; }
	//スコア減少
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

	//1桁目
	std::array<int,4> m_digit;

	//1つの番号の高さと幅
	float m_width;
	float m_height;

	float m_time;

	//何桁あるか
	int m_digitCount;

};
