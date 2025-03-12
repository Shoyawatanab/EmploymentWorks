/*
	@file	Score.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "Score.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>

using namespace DirectX;
using namespace DirectX::SimpleMath;


//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
Score::Score()
	:
	m_commonResources{},
	m_position{},
	m_scale{}
	,m_score{}
	,m_digit{}
	,m_spriteBatch{}
	,m_time{}
	,m_width{}
	,m_height{}
	,m_digitCount{}
{
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
Score::~Score()
{
	// do nothing.
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void Score::Initialize(CommonResources* resources)
{

	m_commonResources = resources;

	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();

	// スプライトバッチを作成する
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(context);

	CreateNumberTex(L"Resources/Textures/Number.png", m_texture);


	m_width = 120;   //幅
	m_height = 142;   //高さ

	m_position = Vector2(800, 360);
	m_scale = Vector2::One;
	
	Reset();

	m_score = 999;
	
}



/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void Score::Update(float elapsedTime)
{

	float ratio = m_time / ANIMATION_TIME;

	ratio = std::min(ratio, 1.0f);

	int score = m_score * ratio;

	SplitDigits(score);	

	m_time += elapsedTime;

}


/// <summary>
/// 描画
/// </summary>
void Score::Render()
{
	//1桁目
	OneNumberRender(m_digit[3], Vector2(m_position.x - NUMBER_SPACINT * 1.5f, m_position.y), m_scale);
	//2桁目
	OneNumberRender(m_digit[2], Vector2(m_position.x - NUMBER_SPACINT / 2, m_position.y), m_scale);
	//3桁目
	OneNumberRender(m_digit[1], Vector2(m_position.x + NUMBER_SPACINT / 2, m_position.y), m_scale);
	//4桁目
	OneNumberRender(m_digit[0], Vector2(m_position.x + NUMBER_SPACINT * 1.5f, m_position.y), m_scale);

}

void Score::Reset()
{

	m_time = 0.0f;
	
	for (auto& digit : m_digit)
	{
		digit = 0;
	}

}

void Score::CreateNumberTex(const wchar_t* szFileName, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& tex)
{
	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();

	//画像の読み込み
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(
			device,
			szFileName,
			nullptr,
			tex.ReleaseAndGetAddressOf()
		)
	);
}


void Score::OneNumberRender(int number, DirectX::SimpleMath::Vector2 Pos, DirectX::SimpleMath::Vector2 Scale)
{
	auto states = m_commonResources->GetCommonStates();


	// スプライトバッチの開始：オプションでソートモード、ブレンドステートを指定する
	m_spriteBatch->Begin(SpriteSortMode_Deferred, states->NonPremultiplied());

	//いつの番号ごとの幅と高さが必要
	float Width = 120;   //幅
	float Hight = 142;   //高さ

	RECT NumberRECT{ 0 + number * static_cast<LONG>(Width), 1,
			110 + number * static_cast<LONG>(Width), static_cast<LONG>(Hight) };

	//PushSpaceの描画
	m_spriteBatch->Draw(
		m_texture.Get(),	// テクスチャ(SRV)
		Pos,				// スクリーンの表示位置(originの描画位置)
		&NumberRECT,			// 矩形(RECT)
		Colors::White,		// 背景色
		0.0f,				// 回転角(ラジアン)
		Vector2(Width / 2, Hight / 2),		// テクスチャの基準になる表示位置(描画中心)(origin)
		Scale,				// スケール(scale)
		SpriteEffects_None,	// エフェクト(effects)
		0.0f				// レイヤ深度(画像のソートで必要)(layerDepth)
	);

	// スプライトバッチの終わり
	m_spriteBatch->End();


}

void Score::SplitDigits(int number)
{

	m_digitCount =  static_cast<int>( std::log10(std::abs(number))) + 1;

	for (int i = 0; i < m_digitCount; i++)
	{
		m_digit[i] = number % 10;

		number /= 10;
	}

}

