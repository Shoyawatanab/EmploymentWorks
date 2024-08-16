#pragma once
/*
	@file	Enemy.h.h
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include"Game/Object/Boomerang/Boomerang.h"
#include "Interface/ICollisionObject.h"


// 前方宣言
class CommonResources;
class Bounding;
class BehaviorTree;
class Player;


namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class Enemy : public ICollisionObject

{
public:

	void SetPlayer(Player* player) { m_player = player; }

	DirectX::SimpleMath::Vector3 GetPosition() { return m_position; }
	DirectX::SimpleMath::Quaternion GetRotate() { return m_rotate; }
	float GetScale() { return m_scale; }


private:
	// 共通リソース
	CommonResources* m_commonResources;

	// モデル
	std::unique_ptr<DirectX::Model> m_model;

	DirectX::SimpleMath::Vector3 m_position;
	DirectX::SimpleMath::Quaternion m_rotate;

	std::unique_ptr<Bounding> m_bounding;

	float m_hp;
	int m_maxHP;
	float m_graivty;


	float m_collisionTime;
	bool m_isCollsionTime;

	float m_scale;


	std::unique_ptr<BehaviorTree> m_behavior;

	Player* m_player;


public:
	Enemy();
	~Enemy() ;

	void Initialize(CommonResources* resources, DirectX::SimpleMath::Vector3 position) ;
	void Update(float elapsedTime);
	void Render(DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection) ;
	void Finalize() ;



	void RegistrationCollionManager(CollisionManager* collsionManager) override;

	Bounding* GetBounding() const override { return m_bounding.get(); };

	CollsionObjectTag GetCollsionTag() const override { return CollsionObjectTag::Enemy; }

	void SetPos(DirectX::SimpleMath::Vector3& Pos) override { m_position = Pos; }

	DirectX::SimpleMath::Vector3 GetPos()override { return m_position; }

	float GetHp() { return m_hp; }

	float GetMAXHp() { return m_maxHP; }

	void OnCollision(CollsionObjectTag& PartnerTag) override;

};
