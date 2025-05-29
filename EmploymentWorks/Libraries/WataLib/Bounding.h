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

		void SetIsBoxHit(const bool& isHit) { m_isBoxHit = isHit; }
		void SetIsSphereHit(const bool& isHit) { m_isSphereHit = isHit; }



	public:
		//コンストラクタ
		Bounding(CommonResources* resources);
		//デストラクタ
		~Bounding();

		//初期化
		void Initialize();
		//更新処理
		void Update(const DirectX::SimpleMath::Vector3& CenterPos);
		//更新処理
		void Update(const DirectX::SimpleMath::Vector3& CenterPos, const DirectX::SimpleMath::Quaternion& rotation);
		//スフィアの作成
		void CreateBoundingSphere(const DirectX::SimpleMath::Vector3& CenterPos, const float& radius);
		//AABBの作成
		void CreateBoundingBox(const DirectX::SimpleMath::Vector3& CenterPos, const DirectX::SimpleMath::Vector3& Extents);
		//OBBの作成
		void CreateBoundingOrientedBox(const DirectX::SimpleMath::Vector3& CenterPos,const DirectX::SimpleMath::Quaternion& rotation,
			const DirectX::SimpleMath::Vector3& Extents);

		//描画
		void Draw(const DirectX::SimpleMath::Vector3& CenterPos, const DirectX::SimpleMath::Quaternion& rotation,
			const DirectX::CXMMATRIX& view, const DirectX::CXMMATRIX& projection);
		//スフィアの描画
		void DrawBoundingSphere(const DirectX::SimpleMath::Vector3& CenterPos, const DirectX::CXMMATRIX& view, const DirectX::CXMMATRIX& projection);
		//AABBの描画
		void DrawBoundingBox(const DirectX::SimpleMath::Vector3& CenterPos, const DirectX::CXMMATRIX& view, const DirectX::CXMMATRIX& projection);
		//OBBの描画
		void DrawBoundingOrientedBox(const DirectX::SimpleMath::Vector3& CenterPos,const  DirectX::SimpleMath::Quaternion& rotation, 
			const DirectX::CXMMATRIX& view, const DirectX::CXMMATRIX& projection);

	private:
		//スフィア
		std::unique_ptr < DirectX::BoundingSphere> m_boundingSphere;
		//OBB
		std::unique_ptr<DirectX::BoundingOrientedBox> m_orientexBox;
		//AABB
		std::unique_ptr<DirectX::BoundingBox> m_boundingBox;
		//共通リソース
		CommonResources* m_commonResources;
		//プリミティブバッチ
		std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_batch;
		//ベーシックエフェクト
		std::unique_ptr<DirectX::BasicEffect> m_effect;
		//インプットレイアウト
		Microsoft::WRL::ComPtr<ID3D11InputLayout> m_layout;
		//ボックスが当たっているか
		bool m_isBoxHit;
		//スフィアが当たっているか
		bool m_isSphereHit;


	};
}

