//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2025/06/19
// <file>			ParticleComputeShader.h
// <概要>		　　パーティクル描画につかうコンピュート(テクスチャセットされていないときに有効)
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include "GameBase/Common/Commons.h"


class ParticleComputeShader
{
public:
	// コンストバッファ
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		DirectX::SimpleMath::Vector4	Diffuse;
	};

	// コンストラクタ、デストラクタ
	ParticleComputeShader(DX::DeviceResources* device);
	~ParticleComputeShader();

	// 画像計算をする
	void CalculateImage();

	// シェーダリソースビュー取得
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetSRV() const { return m_outputSRV; }

private:
	// 作成する
	void Create();


private:
	// デバイスリソース
	DX::DeviceResources* m_pDR;
	// コンピュートシェーダ
	Microsoft::WRL::ComPtr<ID3D11ComputeShader> m_computeShader;
	// 出力用テクスチャ
	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_outputTexture;
	// UAVとSRV
	Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> m_outputUAV;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_outputSRV;
	// コンストバッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_CBuffer;
	// 入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
};
