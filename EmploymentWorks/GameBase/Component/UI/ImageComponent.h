#pragma once
#include "GameBase/Component.h"


//UIのアンカーポイントの列挙数
enum ANCHOR
{
	TOP_LEFT = 0,
	TOP_CENTER,
	TOP_RIGHT,

	MIDDLE_LEFT,
	MIDDLE_CENTER,
	MIDDLE_RIGHT,

	BOTTOM_LEFT,
	BOTTOM_CENTER,
	BOTTOM_RIGHT

};

class ImageComponent : public Component
{

public:	
	//インプットレイアウト	
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;


	//データ受け渡し用コンスタントバッファ(送信側)
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4	windowSize;
		DirectX::SimpleMath::Vector4    diffuse;
	};

public:

	//画像の取得
	ID3D11ShaderResourceView* GetImage() { return m_texture.Get(); }

	//
	void SetRenderRatio(const float& ratio) { m_renderRatio = ratio; }
	//
	float GetRenderRatio() const { return m_renderRatio; }
	//
	void SetRenderRatioOffset(const float& offset) { m_renderRatioOffset = offset; };
	//
	float GetRenderRatioOffset() const { return m_renderRatioOffset; }
	//透明度のセット
	void SetAlphaValue(const float& value) { m_alphaValue = value; }
	//透明度の取得
	float GetAlphaValue() const { return m_alphaValue; }


public:
	//コンストラクタ
	ImageComponent(Actor* owner,std::string textureName);
	//デストラクタ
	~ImageComponent() override;

	//描画
	void Render();

private:

	//画像の読み込み
	void LoadTexture(std::string textureName);

private:
	//画像
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	//定数バッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_CBuffer;
	// 入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	// 頂点シェーダ
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	// ピクセルシェーダ
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
	// ジオメトリシェーダ
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometryShader;

	// プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;


	//画像の大きさ
	int m_textureWidth, m_textureHeight;
	float m_renderRatio;
	float m_renderRatioOffset;

	//画像全体の透明度
	float m_alphaValue;


};