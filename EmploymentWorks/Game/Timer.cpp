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

#include "StepTimer.h"


//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
Timer::Timer()
	:
	m_commonResources{},
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
	CreateTex(L"Resources/Textures/ten.png", m_tenTexture, m_tenTexCenter);
	CreateTex(L"Resources/Textures/TimeTex.png", m_timeTexture, m_timeTexCenter);


	//いつの番号ごとの幅と高さが必要
	m_width = 120;   //幅
	m_height = 142;   //高さ

	m_totalTime = 0;
	m_scale = 0.5f;
	m_position = Vector2(640, 320);
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void Timer::Update(float elapsedTime)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	UNREFERENCED_PARAMETER(elapsedTime);

	TimeCalculation();

	m_totalTime += elapsedTime;

}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void Timer::Render()
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;
	//文字の間隔
	int a = 60;

	float gameTime = m_commonResources->GetStepTimer()->GetTotalSeconds();
	//2秒を超えたら0に戻る
	float t = fmodf(gameTime, 2.0f);


	TexRender(m_timeTexture, m_timeTexCenter, Vector2(m_position.x - a * 3, m_position.y), m_scale);
	OneNumberRender(m_minFirstDigit, Vector2(m_position.x - a * 2, m_position.y),m_scale);
	OneNumberRender(m_minSecondDigit, Vector2(m_position.x - a , m_position.y), m_scale);
	if (t <= 1.0f)
	{
		TexRender(m_tenTexture, m_tenTexCenter, m_position, m_scale);
	}
	OneNumberRender(m_secFirstDigit, Vector2(m_position.x + a , m_position.y), m_scale);
	OneNumberRender(m_secSecondDigit, Vector2(m_position.x + a * 2, m_position.y), m_scale);


}

void Timer::PlaySceneRender(DirectX::SimpleMath::Vector2 Pos, float Scale)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;
	//文字の間隔
	int a = 30;

	float gameTime = m_commonResources->GetStepTimer()->GetTotalSeconds();
	//2秒を超えたら0に戻る
	float t = fmodf(gameTime, 2.0f);


	OneNumberRender(m_minFirstDigit, Vector2(Pos.x - a * 2, Pos.y), Scale);
	OneNumberRender(m_minSecondDigit, Vector2(Pos.x - a, Pos.y), Scale);
	if (t <= 1.0f)
	{
		TexRender(m_tenTexture, m_tenTexCenter, Pos, Scale);
	}
	OneNumberRender(m_secFirstDigit, Vector2(Pos.x + a, Pos.y), Scale);
	OneNumberRender(m_secSecondDigit, Vector2(Pos.x + a * 2, Pos.y),Scale);


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

void Timer::TexRender(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& Tex, DirectX::SimpleMath::Vector2& Center, DirectX::SimpleMath::Vector2 Pos, float Scale)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;
	auto states = m_commonResources->GetCommonStates();


	// スプライトバッチの開始：オプションでソートモード、ブレンドステートを指定する
	m_spriteBatch->Begin(SpriteSortMode_Deferred, states->NonPremultiplied());

	// Titleを描画する
	m_spriteBatch->Draw(
		Tex.Get(),	// テクスチャ(SRV)
		Pos,				// スクリーンの表示位置(originの描画位置)
		nullptr,			// 矩形(RECT)
		Colors::White,		// 背景色
		0.0f,				// 回転角(ラジアン)
		Center,		// テクスチャの基準になる表示位置(描画中心)(origin)
		Scale,				// スケール(scale)
		SpriteEffects_None,	// エフェクト(effects)
		0.0f				// レイヤ深度(画像のソートで必要)(layerDepth)
	);


	// スプライトバッチの終わり
	m_spriteBatch->End();

}


void Timer::CreateTex(const wchar_t* szFileName, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& tex, DirectX::SimpleMath::Vector2& texCenter)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;
	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();


	// 画像をロードする
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(
			device,
			szFileName,
			nullptr,
			tex.ReleaseAndGetAddressOf()
		)
	);


	/*
		以下、テクスチャの大きさを求める→テクスチャの中心座標を計算する
	*/
	// 一時的な変数の宣言
	Microsoft::WRL::ComPtr<ID3D11Resource> resource{};
	Microsoft::WRL::ComPtr<ID3D11Texture2D> tex2D{};
	D3D11_TEXTURE2D_DESC desc{};
	Vector2 texSize{};

	// テクスチャの情報を取得する================================
	// テクスチャをID3D11Resourceとして見る
	tex->GetResource(resource.GetAddressOf());

	// ID3D11ResourceをID3D11Texture2Dとして見る
	resource.As(&tex2D);

	// テクスチャ情報を取得する
	tex2D->GetDesc(&desc);

	// テクスチャサイズを取得し、float型に変換する
	texSize.x = static_cast<float>(desc.Width);
	texSize.y = static_cast<float>(desc.Height);

	// テクスチャの中心位置を計算する
	texCenter = texSize / 2.0f;

}

/// <summary>
/// titalTimeから時間を求める
/// </summary>
void Timer::TimeCalculation()
{
	int time = m_totalTime;
	int min = (time % 3600) / 60;
	int sec = time % 60;

	m_minFirstDigit = min / 10;
	m_minSecondDigit = min % 10;
	m_secFirstDigit = sec / 10;
	m_secSecondDigit = sec % 10;
}
