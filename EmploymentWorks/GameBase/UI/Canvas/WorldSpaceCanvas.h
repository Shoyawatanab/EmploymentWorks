/*
	クラス名     : WorldSpaceCanvas
	説明         : 3D空間用のUI用Canvas
	補足・注意点 :
*/
#pragma once
#include "GameBase/UI/Canvas/Canvas.h"

class Camera;

class WorldSpaceCanvas : public Canvas
{
public:

	//インプットレイアウト	
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;


	//データ受け渡し用コンスタントバッファ(送信側)
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;		DirectX::SimpleMath::Vector4    Position;				//座標
		DirectX::SimpleMath::Vector4	Size;					//大きさ
		DirectX::SimpleMath::Vector4    Rotate;                 //回転
		DirectX::SimpleMath::Vector4    Color;					//色
		DirectX::SimpleMath::Vector4    CutRange;				//切り取り範囲
		DirectX::SimpleMath::Vector4    ViewRange;              //表示範囲
		DirectX::SimpleMath::Vector4    FillAmount;				//塗りつぶし量  x 横　y 縦
	};

public:

	// 頂点シェーダの取得
	Microsoft::WRL::ComPtr<ID3D11VertexShader> GetVertexShader() { return m_vertexShader; }
	// ピクセルシェーダの取得
	Microsoft::WRL::ComPtr<ID3D11PixelShader> GetPixelShader() { return m_pixelShader; }
	// ジオメトリシェーダの取得
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> GetGeometryShader() { return m_geometryShader; }

	//ビルボード処理のセット
	void SetIsBillboard(bool isBillboard) { m_isBillboard = isBillboard; }

public:
	//コンストラクタ
	WorldSpaceCanvas(Scene* scene);
	//デストラクタ
	~WorldSpaceCanvas();

	//描画
	void Render(const Camera& camera) override;

private:

	//通常描画
	void NormalRender(const Camera& camera,ImageComponent* comp);

private:

	// プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>> m_batch;
	// 頂点シェーダ
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	// ピクセルシェーダ
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
	// ジオメトリシェーダ
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometryShader;

	//定数バッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_CBuffer;
	// 入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;


	bool m_isBillboard;


};





