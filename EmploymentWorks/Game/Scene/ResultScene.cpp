/*
	@file	ResultScene.cpp
	@brief	タイトルシーンクラス
*/
#include "pch.h"
#include "ResultScene.h"
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
ResultScene::ResultScene()
	:
	m_commonResources{},
	m_spriteBatch{},
	m_spriteFont{},
	m_texture{},
	m_texCenter{},
	m_isChangeScene{}
{
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
ResultScene::~ResultScene()
{
	// do nothing.
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void ResultScene::Initialize(CommonResources* resources)
{
	assert(resources);
	m_commonResources = resources;

	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();

	// スプライトバッチを作成する
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(context);


	CreateTex(L"Resources/Textures/pushSpace.png", m_texture, m_texCenter);


	// シーン変更フラグを初期化する
	m_isChangeScene = false;
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void ResultScene::Update(float elapsedTime)
{
	// 宣言をしたが、実際は使用していない変数
	UNREFERENCED_PARAMETER(elapsedTime);

	// キーボードステートトラッカーを取得する
	const auto& kbTracker = m_commonResources->GetInputManager()->GetKeyboardTracker();

	// スペースキーが押されたら
	if (kbTracker->released.Space)
	{
		m_isChangeScene = true;
	}
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void ResultScene::Render()
{
	auto states = m_commonResources->GetCommonStates();

	// スプライトバッチの開始：オプションでソートモード、ブレンドステートを指定する
	m_spriteBatch->Begin(SpriteSortMode_Deferred, states->NonPremultiplied());

	// TRIDENTロゴの描画位置を決める
	RECT rect{ m_commonResources->GetDeviceResources()->GetOutputSize() };
	// 画像の中心を計算する
	Vector2 pos{ rect.right / 2.0f, rect.bottom / 2.0f };


	//PushSpaceの描画
	m_spriteBatch->Draw(
		m_texture.Get(),	// テクスチャ(SRV)
		pos + Vector2(0, 150),				// スクリーンの表示位置(originの描画位置)
		nullptr,			// 矩形(RECT)
		Colors::White,		// 背景色
		0.0f,				// 回転角(ラジアン)
		m_texCenter,		// テクスチャの基準になる表示位置(描画中心)(origin)
		0.3f,				// スケール(scale)
		SpriteEffects_None,	// エフェクト(effects)
		0.0f				// レイヤ深度(画像のソートで必要)(layerDepth)
	);

	// スプライトバッチの終わり
	m_spriteBatch->End();


	auto debugString = m_commonResources->GetDebugString();
	debugString->AddString("Result Scene");

}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void ResultScene::Finalize()
{
	// do nothing.
}

//---------------------------------------------------------
// 次のシーンIDを取得する
//---------------------------------------------------------
IScene::SceneID ResultScene::GetNextSceneID() const
{
	// シーン変更がある場合
	if (m_isChangeScene)
	{
		return IScene::SceneID::TITLE;
	}

	// シーン変更がない場合
	return IScene::SceneID::NONE;
}




void ResultScene::CreateTex(const wchar_t* szFileName, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& tex, DirectX::SimpleMath::Vector2& texCenter)
{
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



