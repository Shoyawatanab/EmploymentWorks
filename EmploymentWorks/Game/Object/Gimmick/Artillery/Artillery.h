#pragma once
/*
	@file	Artillery.h.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "pch.h"
#include "Game/Object/Boomerang/Boomerang.h"
#include "Interface/ICollisionObject.h"

// 前方宣言
class CommonResources;
class Bounding;
class ArtilleryBase;
class ArtilleryTurret;
class PlayScene;

class Artillery : public ICollisionObject

{
public:


private:
	// 共通リソース
	CommonResources* m_commonResources;

	std::unique_ptr<Bounding> m_bounding;


	DirectX::SimpleMath::Vector3 m_position;
	DirectX::SimpleMath::Vector3 m_scale;
	DirectX::SimpleMath::Quaternion m_rotate;

	std::unique_ptr<ArtilleryBase> m_base;

	std::unique_ptr<ArtilleryTurret> m_turret;



	/*
	ビルボードの描画に関連するオブジェクト
*/
// ベーシックエフェクト
	std::unique_ptr<DirectX::BasicEffect> m_basicEffect;

	// プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>> m_primitiveBatch;

	// 入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	// 四角形で使用する 頂点情報
	DirectX::VertexPositionTexture	m_vertices[4];

	// テクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;


public:
	Artillery();
	~Artillery() ;

	void Initialize(CommonResources* resources,PlayScene* playScene ,DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector3 Scale ,DirectX::SimpleMath::Vector3 Rotate, float BoundingSphereRadius);
	void Update(float elapsedTime);
	void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection) ;
	void Finalize() ;



	void RegistrationCollionManager(CollisionManager* collsionManager) override;

	Bounding* GetBounding() const override { return m_bounding.get(); };

	CollsionObjectTag GetCollsionTag() const override { return CollsionObjectTag::Artillery; }

	void SetPosition(DirectX::SimpleMath::Vector3& Pos) override { m_position = Pos; }

	DirectX::SimpleMath::Vector3 GetPosition() override { return DirectX::SimpleMath::Vector3::Zero; }
	void OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos) override;

private:
};
