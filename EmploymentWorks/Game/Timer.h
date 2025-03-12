#pragma once
/*
	@file	Timer.h.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "pch.h"

// 前方宣言

class CommonResources;


class Timer final 

{
public:

	//タイマーの大きさ
	void SetTimerScale(float scale) { m_scale = scale; }
	//タイマーの座標
	void SetTimerPos(DirectX::SimpleMath::Vector2 Pos) { m_position = Pos; }

private:

	CommonResources* m_commonResources;
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;

	// テクスチャの半分の大きさ
	DirectX::SimpleMath::Vector2 m_texCenter;
	
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tenTexture;

	// テクスチャの半分の大きさ
	DirectX::SimpleMath::Vector2 m_tenTexCenter;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_timeTexture;

	// テクスチャの半分の大きさ
	DirectX::SimpleMath::Vector2 m_timeTexCenter;


	float m_totalTime;

	//1つの番号の高さと幅
	float m_width;
	float m_height;

	DirectX::SimpleMath::Vector2 m_position;
	float m_scale;

	//秒数の1桁目
	int m_secFirstDigit;
	//秒数の2桁目
	int m_secSecondDigit;
	//分数の1桁目
	int m_minFirstDigit;
	//分数の2桁目
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
