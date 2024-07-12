/*
	@file	TitleScene.h
	@brief	タイトルシーンクラス
*/
#pragma once
#include "IScene.h"

// 前方宣言
class CommonResources;

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class TitleScene final :
    public IScene
{
private:
	// 共通リソース
	CommonResources* m_commonResources;

	// スプライトバッチ
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;

	// スプライトフォント
	std::unique_ptr<DirectX::SpriteFont> m_spriteFont;

	// テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture[2];

	// テクスチャの半分の大きさ
	DirectX::SimpleMath::Vector2 m_texCenter[2];

	// シーンチェンジフラグ
	bool m_isChangeScene;


public:
    TitleScene();
    ~TitleScene() override;

    void Initialize(CommonResources* resources) override;
    void Update(float elapsedTime)override;
    void Render() override;
    void Finalize() override;

    SceneID GetNextSceneID() const;


	void CreateTex(const wchar_t* szFileName, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>&tex, DirectX::SimpleMath::Vector2& texCenter);
};
