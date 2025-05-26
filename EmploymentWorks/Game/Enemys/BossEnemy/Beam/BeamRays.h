/*
	@file	BeamRays.h
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


class BeamRays : public BaseEntity 
{
public:

	//コンスタントバッファ
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		DirectX::SimpleMath::Vector4    Color;
	};


public:


	DirectX::SimpleMath::Vector3 GetTarget() { return m_target; }
 
	void SetTarget(DirectX::SimpleMath::Vector3 target) { m_target = target; }

	DirectX::SimpleMath::Quaternion GetRotate() { return m_initialRotate; }

	void SetRotate(DirectX::SimpleMath::Quaternion rotate) { m_initialRotate = rotate; }


	DirectX::SimpleMath::Vector3 GetInitialScale() { return m_initialScale; }

public:
	//コンストラク
	BeamRays(CommonResources* resources, BaseEntity* parent);
	
	//デストラクタ
	~BeamRays() override;

	
	//初期化
	void Initialize() override;
	//描画
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;
	//更新処理
	void  Update(const float& elapsedTime) override;

private:
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

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
	//初期回転
	DirectX::SimpleMath::Quaternion m_initialRotate;
	//ターゲット
	DirectX::SimpleMath::Vector3 m_target;
	//初期の大きさ
	DirectX::SimpleMath::Vector3 m_initialScale;
	//ビームの細さ
	float m_thickness;
	//当たったかどうか
	bool m_isHit;
	//初期座標
	DirectX::SimpleMath::Vector3 m_initialPosition;

};
