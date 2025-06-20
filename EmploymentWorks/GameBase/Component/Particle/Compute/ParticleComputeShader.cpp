//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2025/06/19
// <file>			ParticleComputeShader.cpp
// <概要>		　　パーティクル描画につかうコンピュート(テクスチャセットされていないときに有効)
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"ParticleComputeShader.h"
#include "Libraries/MyLib/BinaryFile.h"

/// <summary>
/// コンストラクタ
/// </summary>
ParticleComputeShader::ParticleComputeShader(DX::DeviceResources* device)
	:
	m_pDR{ device }
{
	Create();
}

/// <summary>
/// デストラクタ
/// </summary>
ParticleComputeShader::~ParticleComputeShader()
{
}

/// <summary>
/// 作成
/// </summary>
void ParticleComputeShader::Create()
{
	auto device = m_pDR->GetD3DDevice();
	// シェーダにデータを渡すためのコンストバッファの生成
	D3D11_BUFFER_DESC bd = {};
	//ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	//bd.CPUAccessFlags = 0;
	device->CreateBuffer(&bd, nullptr, &m_CBuffer);


	// シェーダリソースビューへ渡すためのテクスチャ概要作成
	D3D11_TEXTURE2D_DESC texDesc = {};
	texDesc.Width = 512;
	texDesc.Height = 512;
	texDesc.MipLevels = 1;
	texDesc.ArraySize = 1;
	texDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	texDesc.SampleDesc.Count = 1;
	texDesc.Usage = D3D11_USAGE_DEFAULT;
	texDesc.BindFlags = D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;

	// デバイスに情報を渡して、作成する
	device->CreateTexture2D(&texDesc, nullptr, &m_outputTexture);
	device->CreateUnorderedAccessView(m_outputTexture.Get(), nullptr, &m_outputUAV);
	device->CreateShaderResourceView(m_outputTexture.Get(), nullptr, &m_outputSRV);

	// コンパイルされたシェーダファイルの読み込み
	BinaryFile CSData = BinaryFile::LoadFile(L"Resources/Shaders/ParticleCS.cso");

	// コンピュートシェーダ作成
	if (FAILED(device->CreateComputeShader(CSData.GetData(), CSData.GetSize(), NULL, m_computeShader.ReleaseAndGetAddressOf())))
	{// エラー
		MessageBox(0, L"CreateComputeShader Failed.", NULL, MB_OK);
		return;
	}
}

/// <summary>
/// イメージ画像計算する
/// </summary>
void ParticleComputeShader::CalculateImage()
{
	ID3D11DeviceContext* context = m_pDR->GetD3DDeviceContext();
	// UAVセット
	ID3D11UnorderedAccessView* uavs[1] = { m_outputUAV.Get() };
	context->CSSetUnorderedAccessViews(0, 1, uavs, nullptr);

	// コンピュートシェーダをセット
	context->CSSetShader(m_computeShader.Get(), nullptr, 0);
	//context->CSSetShaderResources(0, 1, m_texture.GetAddressOf());
	// Dispatch
	context->Dispatch(static_cast<UINT>(516 / 16), static_cast<UINT>(516 / 16), 1);

	// 後始末
	ID3D11UnorderedAccessView* nullUAV[1] = { nullptr };
	context->CSSetUnorderedAccessViews(0, 1, nullUAV, nullptr);
	context->CSSetShader(nullptr, nullptr, 0);
}
