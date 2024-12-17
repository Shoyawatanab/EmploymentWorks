/*
	@file	BeamEnergyBall.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "Interface/ICollisionObject.h"


// 前方宣言
class CommonResources;
class Beam;
class Bounding;


namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class BeamEnergyBall : public ICollisionObject
{
public:

	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
	};


public:

	DirectX::SimpleMath::Vector3 GetPosition() override{ return m_position; }

	void SetPosition(DirectX::SimpleMath::Vector3& Pos)  { m_position = Pos; }

	DirectX::SimpleMath::Vector3 GetTarget()  { return m_target; }
 
	void SetTarget(DirectX::SimpleMath::Vector3 target) { m_target = target; }

	DirectX::SimpleMath::Quaternion GetRotate() { return m_rotate; }

	//void SetRotate(DirectX::SimpleMath::Quaternion rotate) { m_initialRotate = rotate; }

	DirectX::SimpleMath::Vector3 GetScale() { return m_scale; }

	void SetScale(DirectX::SimpleMath::Vector3 scale) { m_scale = scale; }

	DirectX::SimpleMath::Vector3 GetInitialScale() { return m_initialScale; }
	

private:
	// 共通リソース
	CommonResources* m_commonResources;

	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

	//	頂点シェーダ
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	//	ピクセルシェーダ
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;

	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_CBuffer;



	// モデル
	std::unique_ptr<DirectX::Model> m_model;
	
	DirectX::SimpleMath::Vector3 m_position;

	DirectX::SimpleMath::Vector3 m_scale;

	DirectX::SimpleMath::Quaternion m_initialRotate;

	DirectX::SimpleMath::Quaternion m_rotate;
	
	DirectX::SimpleMath::Vector3 m_target;

	DirectX::SimpleMath::Vector3 m_initialScale;

	DirectX::SimpleMath::Vector3 m_maxScale;

	Beam* m_beam;

	float m_maxSizeTime;

	float m_time;

	std::unique_ptr<Bounding> m_bounding;


public:
	BeamEnergyBall();
	~BeamEnergyBall();

	void Initialize() ;
	void Update(float elapsedTime);
	void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection) ;
	void Finalize();
public :
	//クラスに必要な情報（ポインタ）の登録
	void RegistrationInformation(CommonResources* resoure, Beam* beam);

	void RegistrationCollionManager(CollisionManager* collsionManager) override;

	Bounding* GetBounding() const override { return m_bounding.get(); };

	CollsionObjectTag GetCollsionTag() const override { return CollsionObjectTag::Beam; }

	void OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos) override;

};
