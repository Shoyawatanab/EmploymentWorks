/*
	@file	BeamChargeEffect.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "Game/Entities/BaseEntity.h"


// 前方宣言
class CommonResources;
class Beam;

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class BeamChargeEffect :public BaseEntity
{

public:
	//インプットレイアウト
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

	//初期の大きさ
	static constexpr  DirectX::SimpleMath::Vector3 INITIALSCALE {0.1f, 0.1f, 0.1f};

public:


public:
	//コンストラク
	BeamChargeEffect(CommonResources* resoure, DirectX::SimpleMath::Vector3 scale, DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Quaternion rotate);
	//デストラクタ
	~BeamChargeEffect();
	//初期化
	void Initialize() override ;
	//更新処理
	void Update(const float& elapsedTime) override ;
	//描画処理
	void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection) ;
	//
	void Finalize();

	//クラスに必要な情報（ポインタ）の登録
	void AddPointer(Beam* beam);

private:


	//無効になったら
	void OnDisable() override ;

private:


	//	頂点シェーダ
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	//	ピクセルシェーダ
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
	//インプットレイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	//定数バッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_CBuffer;
	// モデル
	DirectX::Model* m_model;
	//ビーム
	Beam* m_beam;
	//初期座標
	DirectX::SimpleMath::Vector3 m_initialPosition;


};
