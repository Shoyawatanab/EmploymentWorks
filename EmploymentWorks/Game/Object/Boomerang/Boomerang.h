#pragma once
/*
	@file	Boomerang.h.h
	@brief	プレイシーンクラス
*/
#pragma once
#include "pch.h"
#include "Interface/IBoomerangState.h"
#include "Game/Object/Boomerang/State/BoomerangIdling.h"
#include "Game/Object/Boomerang/State/BoomerangThrow.h"
#include "Game/Object/Boomerang/State/BoomerangGetReady.h"
#include "Interface/ICollisionObject.h"

// 前方宣言
class CommonResources;
class Player;
class Bounding;


namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class Boomerang : public ICollisionObject
{
public:


public:
	DirectX::SimpleMath::Vector3 GetPosition() { return m_position; };
	void SetPosition(DirectX::SimpleMath::Vector3 Pos) { m_position = Pos; }
	DirectX::SimpleMath::Quaternion GetRotate() { return m_rotate; }
	void SetRotate(DirectX::SimpleMath::Quaternion Rotate) { m_rotate = Rotate; }

	float GetScale() { return m_scale; }

	Player* GetPlayer() { return m_player; }

	IBoomerangState* GetBoomerangState() { return m_currentState; }
	BoomerangIdling* GetBoomerangIdling() { return m_idling.get(); }
	BoomerangThrow* GetBoomerangThrow() { return m_throw.get(); }
	BoomerangGetReady* GetBoomerangGetReady() { return m_getReady.get(); }

private:

	// 共通リソース
	CommonResources* m_commonResources;

	Player* m_player;

	std::unique_ptr<Bounding> m_bounding;

	// モデル
	std::unique_ptr<DirectX::Model> m_model;
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_primitiveBatch;

	//パラメーター
	DirectX::SimpleMath::Vector3 m_position;
	DirectX::SimpleMath::Quaternion m_rotate;
	float m_scale;



	//状態
	IBoomerangState* m_currentState;
	std::unique_ptr<BoomerangIdling> m_idling;
	std::unique_ptr<BoomerangThrow> m_throw;
	std::unique_ptr<BoomerangGetReady> m_getReady;
	Enemy* m_enemy;


public:
	Boomerang(Player* player, Enemy* enemy);
	~Boomerang() ;

	void Initialize(CommonResources* resources) ;
	void Update(float elapsedTime);
	void Render(DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection) ;
	void Finalize() ;

	void ChangeState(IBoomerangState* nextState);

	void RegistrationCollionManager(CollisionManager* collsionManager) override;

	Bounding* GetBounding() const override { return m_bounding.get(); };

	CollsionObjectTag GetCollsionTag() const override { return CollsionObjectTag::Boomerang; }

	void SetPos(DirectX::SimpleMath::Vector3& Pos) override { m_position = Pos; }

	DirectX::SimpleMath::Vector3 GetPos() override { return m_position; }

	void OnCollision() override;


};
