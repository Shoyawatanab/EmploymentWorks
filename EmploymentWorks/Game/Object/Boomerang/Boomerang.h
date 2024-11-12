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
#include "Game/Object/Boomerang/State/BoomerangRepelled.h"
#include "Game/Object/Boomerang/State/BoomerangDrop.h"

// 前方宣言
class CommonResources;
class Player;
class Bounding;
class BoomerangOrbit;
class PlayScene;

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class Boomerang : public ICollisionObject
{
public:

	//使用中かどうか
	enum class UseState
	{

		Stock,    //ストック状態　　　Update・描画なし
		Have,     //持っている状態   Updateなし・描画あり
		GetReady, // 構えている　　　Update・描画あり
		Throw     //使用状態　　　　　Update・描画あり

	};

public:
	DirectX::SimpleMath::Quaternion GetRotate() { return m_rotate; }
	void SetRotate(DirectX::SimpleMath::Quaternion Rotate) { m_rotate = Rotate; }

	float GetScale() { return m_scale; }

	Player* GetPlayer() { return m_player; }

	IBoomerangState* GetBoomerangState() { return m_currentState; }
	BoomerangIdling* GetBoomerangIdling() { return m_idling.get(); }
	BoomerangThrow* GetBoomerangThrow() { return m_throw.get(); }
	BoomerangGetReady* GetBoomerangGetReady() { return m_getReady.get(); }
	BoomerangRepelled* GetBoomerangRepelled() { return m_repelled.get(); }
	BoomerangDrop* GetBoomerangDrop() { return m_drop.get(); }


	BoomerangOrbit* GetOrbit() { return m_orbit.get(); }

	DirectX::SimpleMath::Vector3 GetPreviousFramePos() { return m_previousFramePos; }


	DirectX::SimpleMath::Vector3 GetBounceDirection() { return m_bounceDirection; }
	void SetBounceDirection(DirectX::SimpleMath::Vector3 direction) { m_bounceDirection = direction; }

	UseState GetUseState() { return m_useState; }
	void SetUseState(UseState State) { m_useState = State; }


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


	std::unique_ptr<BoomerangOrbit> m_orbit;

	//状態
	IBoomerangState* m_currentState;
	std::unique_ptr<BoomerangIdling> m_idling;
	std::unique_ptr<BoomerangThrow> m_throw;
	std::unique_ptr<BoomerangGetReady> m_getReady;
	std::unique_ptr<BoomerangRepelled> m_repelled;
	std::unique_ptr<BoomerangDrop> m_drop;


	Enemy* m_enemy;

	PlayScene* m_playScene;

	//当たった時の相手のタグ
	CollsionObjectTag m_onCollisionTag;

	//１フレーム前の座標　弾かれる処理で使用

	DirectX::SimpleMath::Vector3 m_previousFramePos;

	//ブーメランの弾かれる方向
	DirectX::SimpleMath::Vector3 m_bounceDirection;

	//ストック状態か使用状態か
	UseState m_useState;



public:
	Boomerang();
	~Boomerang() ;

	void Initialize(CommonResources* resources) ;
	void Update(float elapsedTime);
	void Render(DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection) ;
	void Finalize() ;

	void ChangeState(IBoomerangState* nextState);

	void DemandBounceDirection(DirectX::SimpleMath::Vector3 pos, CollsionObjectTag& tag);


	void RegistrationCollionManager(CollisionManager* collsionManager) override;

	Bounding* GetBounding() const override { return m_bounding.get(); };

	CollsionObjectTag GetCollsionTag() const override { return CollsionObjectTag::Boomerang; }

	void SetPosition(DirectX::SimpleMath::Vector3& Pos) override { m_position = Pos; }

	DirectX::SimpleMath::Vector3 GetPosition() override { return m_position; }

	void OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos) override;

	//クラスに必要な情報（ポインタ）の登録
	void RegistrationInformation(Player* player, Enemy* enemy,PlayScene* playScene);

	//クラスのインスタンス
	void Instances();

};
