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



public:
	Artillery();
	~Artillery() ;

	void Initialize(CommonResources* resources, DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector3 Scale ,DirectX::SimpleMath::Vector3 Rotate);
	void Update(float elapsedTime);
	void Render(DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection) ;
	void Finalize() ;

	void RegistrationCollionManager(CollisionManager* collsionManager) override;

	Bounding* GetBounding() const override { return m_bounding.get(); };

	CollsionObjectTag GetCollsionTag() const override { return CollsionObjectTag::Wall; }

	void SetPos(DirectX::SimpleMath::Vector3& Pos) override { m_position = Pos; }

	DirectX::SimpleMath::Vector3 GetPos() override { return DirectX::SimpleMath::Vector3::Zero; }
	void OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos) override;

private:
};
