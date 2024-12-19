//--------------------------------------------------------------------------------------
//	File: Fade.h
//
//	パーティクルクラス
//	未拡張の場合はPosition情報のみ
//
//-------------------------------------------------------------------------------------

#pragma once

#include "StepTimer.h"
#include <DeviceResources.h>
#include <SimpleMath.h>
#include <Effects.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <WICTextureLoader.h>
#include <CommonStates.h>
#include <vector>

class Fade
{
public:

	//フェード状態
	enum FadeState
	{
		None,
		FadeIn,
		FadeOut
	};


	//	データ受け渡し用コンスタントバッファ(送信側)
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		DirectX::SimpleMath::Vector4	Diffuse;
		DirectX::SimpleMath::Vector4	time;
	};

public:
	//フェード状態の登録
	void SetFadeState(FadeState state) { m_fadeState = state; }
	//フェード状態の取得
	FadeState GetFadeState() { return m_fadeState; }
	//シーン切り替えをするかの登録
	void SetIsSceneChange(bool is) { m_isSceneChange = is; }
	//シーン切り替えをするかどうかを取得
	bool GetIsSceneChange() { return m_isSceneChange; }



private:
	//コンストバッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_CBuffer;
	//	入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	//	プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;
	//	コモンステート
	std::unique_ptr<DirectX::CommonStates> m_states;
	//	テクスチャハンドル
	std::vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_texture;
	//	テクスチャハンドル
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture2;
	//	使用する頂点シェーダ
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_currentVS;
	//	使用するピクセルシェーダ
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_currentPS;
	//	使用するジオメトリシェーダ
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_currentGS;

	DirectX::SimpleMath::Matrix m_world;
	DirectX::SimpleMath::Matrix m_view;
	DirectX::SimpleMath::Matrix m_proj;

	float m_time;
	FadeState m_fadeState;

	//シーン切り替えをするか
	bool m_isSceneChange;


	ID3D11Device1* m_device ;
	ID3D11DeviceContext* m_context;

	//	通常フェードインピクセルシェーダ
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_normalFadeInPS;
	//	通常フェードアウトピクセルシェーダ
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_normalFadeOutPS;

	//フェード時間
	float m_maxFadeTime;

public:
	//	関数
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;
	//コンストラクタ
	Fade(ID3D11Device1* m_device,ID3D11DeviceContext* m_contect);
	//デストラクタ
	~Fade();
	//初期化処理
	void Initialize();
	//更新処理
	void Update(float elapsdTime);
	//描画処理
	void Render();

	//通常フェードインのスタート関数
	void StartNormalFadeIn();
	//通常フェードアウトのスタート関数
	void StartNormalFadeOut();

private:
	//シェーダーの作成
	void CreateShader();
};


/*
	　FadeInは各シーンのGetNextSceneID関数内でスタートさせる
	FadeOutは各シーンのInitialize関数でスタートさせる
	
*/
