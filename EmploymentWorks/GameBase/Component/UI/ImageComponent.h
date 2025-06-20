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
		DirectX::SimpleMath::Vector4	windowSize;             //画面サイズ
		DirectX::SimpleMath::Vector4    Position;				//座標
		DirectX::SimpleMath::Vector4	Size;					//大きさ
		DirectX::SimpleMath::Vector4    Color;					//色
		DirectX::SimpleMath::Vector4    CutRange;				//切り取り範囲
		DirectX::SimpleMath::Vector4    FillAmount;				//塗りつぶし量  x 横　y 縦
	};

public:

	//画像の取得
	ID3D11ShaderResourceView* GetImage() { return m_texture.Get(); }

	//切り取り範囲のセット
	void SetCutRange(DirectX::SimpleMath::Vector4 range) { m_cutRange = range; }
	//色のセット
	void SetColor(DirectX::SimpleMath::Vector4 color) { m_color = color; }
	//横の塗りつぶし量　０～１までの範囲
	void SetHorizontalFillAmount(float fillAmount) { m_fillAmount.x = fillAmount; }

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
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>> m_batch;


	//画像の大きさ
	int m_textureWidth, m_textureHeight;
	//色
	DirectX::SimpleMath::Vector4 m_color;
	//切り取り範囲
	DirectX::SimpleMath::Vector4 m_cutRange;
	//塗りつぶし量　x: 横　y :縦
	DirectX::SimpleMath::Vector4 m_fillAmount;
	//




};