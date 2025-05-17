/*
	@file	Bounding.h
	@brief	デバッグ用カメラクラス
*/
#pragma once
class CommonResources;

namespace WataLib
{
	// デバッグ用カメラクラス
	class Bounding
	{
	public:
		DirectX::BoundingBox* GetBoundingBox() { return m_boundingBox.get(); }
		DirectX::BoundingSphere* GetBoundingSphere() { return m_boundingSphere.get(); }
		DirectX::BoundingOrientedBox* GetOrientedBox() { return m_orientexBox.get(); }

		void SetIsBoxHit(bool isHit) { m_isBoxHit = isHit; }
		void SetIsSphereHit(bool isHit) { m_isSphereHit = isHit; }



	public:
		Bounding(CommonResources* resources);
		~Bounding();

		//初期化
		void Initialize();

		void Update(DirectX::SimpleMath::Vector3 CenterPos);

		void Update(DirectX::SimpleMath::Vector3 CenterPos, DirectX::SimpleMath::Quaternion rotation);



		void CreateBoundingSphere(DirectX::SimpleMath::Vector3 CenterPos, float radius);
		void CreateBoundingBox(DirectX::SimpleMath::Vector3 CenterPos, DirectX::SimpleMath::Vector3 Extents);
		void CreateBoundingOrientedBox(DirectX::SimpleMath::Vector3 CenterPos,DirectX::SimpleMath::Quaternion rotation,
			DirectX::SimpleMath::Vector3 Extents);

		void Draw(const DirectX::SimpleMath::Vector3 CenterPos, DirectX::SimpleMath::Quaternion rotation,
			DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection);

		void DrawBoundingSphere(const DirectX::SimpleMath::Vector3 CenterPos, DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection);
		void DrawBoundingBox(const DirectX::SimpleMath::Vector3 CenterPos, DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection);
		void DrawBoundingOrientedBox(const DirectX::SimpleMath::Vector3 CenterPos, DirectX::SimpleMath::Quaternion rotation, 
			DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection);

	private:

		std::unique_ptr < DirectX::BoundingSphere> m_boundingSphere;
		std::unique_ptr<DirectX::BoundingOrientedBox> m_orientexBox;
		std::unique_ptr<DirectX::BoundingBox> m_boundingBox;

		CommonResources* m_commonResources;


		std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_batch;
		std::unique_ptr<DirectX::BasicEffect> m_effect;
		Microsoft::WRL::ComPtr<ID3D11InputLayout> m_layout;

		bool m_isBoxHit;
		bool m_isSphereHit;


	};
}

