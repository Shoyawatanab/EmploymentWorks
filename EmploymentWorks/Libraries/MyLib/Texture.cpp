/*
	@file	Texture.cpp
	@brief	タイトルシーンクラス
*/
#include "pch.h"
#include "Texture.h"
#include "Game/Screen.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include "Libraries/MyLib/InputManager.h"
#include <cassert>


#include "Libraries/MyLib/DebugString.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
mylib::Texture::Texture()
	:
	m_commonResources{},
	m_spriteBatch{},
	m_spriteFont{},
	m_texture{},
	m_texCenter{},
	m_position{},
	m_scale{},
	m_rotate{}
{
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
mylib::Texture::~Texture()
{
	// do nothing.
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void mylib::Texture::Initialize(CommonResources* resources, const wchar_t* szFileName, DirectX::SimpleMath::Vector2 Pos, float scale)
{
	assert(resources);
	m_commonResources = resources;
	m_position = Pos;
	m_scale = scale;

	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();


	// スプライトバッチを作成する
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(context);
	// スプライトフォントを作成する
	m_spriteFont = std::make_unique<DirectX::SpriteFont>(
		device,
		L"Resources/Fonts/SegoeUI_18.spritefont"
	);


	// 画像をロードする
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(
			device,
			szFileName,
			nullptr,
			m_texture.ReleaseAndGetAddressOf()
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
	m_texture->GetResource(resource.GetAddressOf());

	// ID3D11ResourceをID3D11Texture2Dとして見る
	resource.As(&tex2D);

	// テクスチャ情報を取得する
	tex2D->GetDesc(&desc);

	// テクスチャサイズを取得し、float型に変換する
	texSize.x = static_cast<float>(desc.Width);
	texSize.y = static_cast<float>(desc.Height);

	// テクスチャの中心位置を計算する
	m_texCenter = texSize / 2.0f;

}


//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void mylib::Texture::Render()
{

	auto states = m_commonResources->GetCommonStates();


	// スプライトバッチの開始：オプションでソートモード、ブレンドステートを指定する
	m_spriteBatch->Begin(SpriteSortMode_Deferred, states->NonPremultiplied());

	// Titleを描画する
	m_spriteBatch->Draw(
		m_texture.Get(),	// テクスチャ(SRV)
		m_position,				// スクリーンの表示位置(originの描画位置)
		nullptr,			// 矩形(RECT)
		Colors::White,		// 背景色
		m_rotate,				// 回転角(ラジアン)
		m_texCenter,		// テクスチャの基準になる表示位置(描画中心)(origin)
		m_scale,				// スケール(scale)
		SpriteEffects_None,	// エフェクト(effects)
		0.0f				// レイヤ深度(画像のソートで必要)(layerDepth)
	);



	// スプライトバッチの終わり
	m_spriteBatch->End();



}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void mylib::Texture::Finalize()
{
	// do nothing.
}


