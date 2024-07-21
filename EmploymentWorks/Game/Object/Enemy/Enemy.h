#pragma once
/*
	@file	Enemy.h.h
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include"Game/Object/Boomerang/Boomerang.h"

#include "Interface/IEnemyState.h"
#include "Game/Object/Enemy/State/EnemyIdling.h"
#include "Game/Object/Enemy/State/EnemyMove.h"
#include "Game/Object/Enemy/State/EnemyAttack.h"
#include "Interface/ICollisionObject.h"

// 前方宣言
class CommonResources;
class Bounding;

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class Enemy : public ICollisionObject

{
public:
	DirectX::SimpleMath::Vector3 GetPosition() { return m_position; }
	DirectX::SimpleMath::Quaternion GetRotate() { return m_rotate; }
	float GetScale() { return m_scale; }

	IEnemyState* GetEnemyState() { return m_currentState; }
	EnemyIdling* GetEnemyIdling() { return m_idling.get(); }
	EnemyMove* GetEnemyMove() { return m_move.get(); }
	EnemyAttack* GetEnemyAttack() { return m_attack.get(); }

private:
	// 共通リソース
	CommonResources* m_commonResources;

	// モデル
	std::unique_ptr<DirectX::Model> m_model;

	DirectX::SimpleMath::Vector3 m_position;
	DirectX::SimpleMath::Quaternion m_rotate;

	std::unique_ptr<Bounding> m_bounding;

	float m_hp;
	float m_graivty;


	float m_collisionTime;
	bool m_isCollsionTime;

	float m_scale;


	IEnemyState* m_currentState;
	std::unique_ptr<EnemyIdling> m_idling;
	std::unique_ptr<EnemyMove> m_move;
	std::unique_ptr<EnemyAttack> m_attack;


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
	void OnCollision(CollsionObjectTag& PartnerTag) override;

};
