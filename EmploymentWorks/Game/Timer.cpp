/*
	@file	Timer.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "Timer.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>



//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
Timer::Timer()
	:
	m_totalTime{},
	m_width{},
	m_height{},
	m_position{},
	m_scale{}
{
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
Timer::~Timer()
{
	// do nothing.
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void Timer::Initialize(CommonResources* resources)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;
	assert(resources);

	m_commonResources = resources;

	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();

	// スプライトバッチを作成する
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(context);


	CreateNumberTex(L"Resources/Textures/Number.png", m_texture, m_texCenter);

	//いつの番号ごとの幅と高さが必要
	m_width = 120;   //幅
	m_height = 142;   //高さ

	m_totalTime = 0;
	m_scale = 0.3f;
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void Timer::Update(float elapsedTime)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	UNREFERENCED_PARAMETER(elapsedTime);


	m_totalTime += elapsedTime;

}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void Timer::Render()
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	int a = 35;

	OneNumberRender(1, Vector2(100 + a, 100),m_scale);
	OneNumberRender(2, Vector2(100 + a * 2, 100), m_scale);
	OneNumberRender(3, Vector2(100 + a * 3, 100), m_scale);
	OneNumberRender(4, Vector2(100 + a * 4, 100), m_scale);


}

void Timer::CreateNumberTex(const wchar_t* szFileName,Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& tex, DirectX::SimpleMath::Vector2& texCenter)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

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
		

		// １つの番号の中心座標
		texCenter = Vector2(m_width,m_height) ;

}

void Timer::OneNumberRender(int number,DirectX::SimpleMath::Vector2 Pos, float Scale)
{

	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	auto states = m_commonResources->GetCommonStates();

	// スプライトバッチの開始：オプションでソートモード、ブレンドステートを指定する
	m_spriteBatch->Begin(SpriteSortMode_Deferred, states->NonPremultiplied());

	//いつの番号ごとの幅と高さが必要
	float Width = 120;   //幅
	float Hight = 142;   //高さ

	RECT NumberRECT{ 0 + number * Width, 1,
			110 + number * Width, Hight };

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

