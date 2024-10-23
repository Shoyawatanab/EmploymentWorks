#pragma once
/*
	@file	ArtilleryBullet.h.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "pch.h"
#include "Game/Object/Boomerang/Boomerang.h"
#include "Interface/ICollisionObject.h"

// 前方宣言
class CommonResources;
class Bounding;
class PlayScene;



class ArtilleryBullet : public ICollisionObject

{
public:
	enum  BulletState
	{
		Stock         //ストック状態　
 		,Loading      //装填状態
		,Flying      //飛んでいる状態

	};
public:
	//弾の状態の取得
	BulletState& GetBulletState() { return m_bulletState; }
	//弾の状態を登録
	void SetBulletState(BulletState State) { m_bulletState = State; }


private:
	// 共通リソース
	CommonResources* m_commonResources;

	std::unique_ptr<Bounding> m_bounding;

	// モデル
	std::unique_ptr<DirectX::Model> m_model;

	DirectX::SimpleMath::Vector3 m_initialPosition;
	DirectX::SimpleMath::Vector3 m_position;
	DirectX::SimpleMath::Vector3 m_scale;
	DirectX::SimpleMath::Quaternion m_rotate;

	BulletState m_bulletState;

	PlayScene* m_playScene;

public:
	ArtilleryBullet();
	~ArtilleryBullet() ;

	void Initialize(CommonResources* resources, PlayScene* playScene, DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector3 Scale,DirectX::SimpleMath::Quaternion Rotate);
	void Update(float elapsedTime);
	void Render(DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection) ;
	void Finalize() ;

	void RegistrationCollionManager(CollisionManager* collsionManager) override;

	Bounding* GetBounding() const override { return m_bounding.get(); };

	CollsionObjectTag GetCollsionTag() const override { return CollsionObjectTag::ArtilleryBullet; }

	void SetPosition(DirectX::SimpleMath::Vector3& Pos) override { m_position = Pos; }

	DirectX::SimpleMath::Vector3 GetPosition() override { return DirectX::SimpleMath::Vector3::Zero; }
	void OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos) override;

private:
};
