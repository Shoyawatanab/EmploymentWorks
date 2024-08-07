﻿/*
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

	CommonResources* m_commonResources;


	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_batch;
	std::unique_ptr<DirectX::BasicEffect> m_effect;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_layout;

	bool m_isBoxHit;
	bool m_isSphereHit;


public:
	Bounding();
	~Bounding() = default;


	void Render(const DirectX::SimpleMath::Vector3 CenterPos, DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection);
	void CreateBoundingSphere(CommonResources* resources, DirectX::SimpleMath::Vector3 CenterPos, float radius);
	void CreateBoundingBox(CommonResources* resources, DirectX::SimpleMath::Vector3 CenterPos, DirectX::SimpleMath::Vector3 Extents);


	void DrawBoundingSphere(const DirectX::SimpleMath::Vector3 CenterPos, DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection);
	void DrawBoundingBox(const DirectX::SimpleMath::Vector3 CenterPos, DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection);
};

