/*
	@file	Bounding.h
	@brief	デバッグ用カメラクラス
*/
#pragma once
class CommonResources;


	// デバッグ用カメラクラス
class Bounding
{
public:
	DirectX::BoundingBox* GetBoundingBox() { return &m_boundingBox; }
	DirectX::BoundingSphere* GetBoundingSphere() { return &m_boundingSphere; }

	void SetIsBoxHit(bool isHit) { m_isBoxHit = isHit; }
	void SetIsSphereHit(bool isHit) { m_isSphereHit = isHit; }

private:

	DirectX::BoundingBox m_boundingBox;
	DirectX::BoundingSphere m_boundingSphere;
	DirectX::BoundingOrientedBox m_orientexBox;

	CommonResources* m_commonResources;


	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_batch;
	std::unique_ptr<DirectX::BasicEffect> m_effect;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_layout;

	bool m_isBoxHit;
	bool m_isSphereHit;


public:
	Bounding();
	~Bounding() = default;


	//void Render(const DirectX::SimpleMath::Vector3 CenterPos, DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection);
	void CreateBoundingSphere(CommonResources* resources, DirectX::SimpleMath::Vector3 CenterPos, float radius);
	void CreateBoundingBox(CommonResources* resources, DirectX::SimpleMath::Vector3 CenterPos, DirectX::SimpleMath::Vector3 Extents);
	void CreateOrientexBox(CommonResources* resources, DirectX::SimpleMath::Vector3 CenterPos, DirectX::SimpleMath::Vector3 Extents, DirectX::SimpleMath::Quaternion rotate);

	void Update(DirectX::SimpleMath::Vector3 Position);
	void OrientexBoxUpdate(DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Quaternion rotate);


	void DrawBoundingSphere(const DirectX::SimpleMath::Vector3 CenterPos, DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection);
	void DrawBoundingBox(const DirectX::SimpleMath::Vector3 CenterPos, DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection);

	void DrawBoundingSphere(DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection);
	void DrawBoundingBox( DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection);
	void DrawOrientexBox(DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection);

};

