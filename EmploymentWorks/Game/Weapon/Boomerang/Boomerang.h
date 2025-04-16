#pragma once
#include "Game/Entities/ItemEntity.h"
#include "Game/Weapon/Boomerang/State/BoomerangIdle.h"
#include "Libraries/WataLib/Shadow.h"

using namespace DirectX::SimpleMath;

// 前方宣言
class CommonResources;
class BoomerangStateMachine;
class Player;
class TargetMarker;

namespace WataLib
{
	class Bounding;
	class TPS_Camera;
}



class Boomerang : public ItemEntity
{
public:

	BoomerangStateMachine* GetBoomerangStatemachine() { return m_stateMachine.get(); }

	std::vector<DirectX::SimpleMath::Vector3>& GetThrowBasePosition() { return m_throwbasePosition; }

	const Vector3& GetPrevPosition() { return m_prevPosition; }

public:
	//コンストラクタ
	Boomerang(CommonResources* resources
		, BaseEntity* parent
		, DirectX::SimpleMath::Vector3 scale,
		DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Quaternion rotation);
	//デストラクタ
	~Boomerang() override;

	//IObject
		//初期化
	void Initialize() override;
	//描画
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;
	//更新処理
	void  Update(const float& elapsedTime) override;

	//ICollisionObject
	//タグの取得
	CollisionTag GetCollisionTag() override { return CollisionEntity::CollisionTag::Boomerang; };
	//当たった時に呼び出される
	void OnCollisionEnter(CollisionEntity* object, CollisionTag tag) override;
	//衝突が終了したときに呼び出される
	void OnCollisionExit(CollisionEntity* object, CollisionTag tag);

	//当たり判定の種類の取得
	const CollisionType GetCollisionType() override { return CollisionType::AABB; };
	//押し出しをするかどうか
	const bool GetIsExtrusion() override { return false; };
	//当たり判定を行わないタグ
	const std::vector<CollisionTag> GetNoHitDetectionTag() override {
		return  {
			//{CollisionTag::Player},
			{CollisionTag::PlayerParts}
			,{CollisionTag::Boomerang}
			,{CollisionTag::Enemy}

		};
	};

	//押し出しを行わないタグ
	const std::vector<CollisionTag> GetNoExtrusionTag() {
		return  {
		};
	};


	void OnAcquired() override ;


	//必要なポインタの登録
	void AddPointer(Player* player, TargetMarker* targetMarker, WataLib::TPS_Camera* tpsCamera);

private:
	//親
	BaseEntity* m_parent;
	//モデル
	DirectX::Model* m_model;

	//ステートマシン
	std::unique_ptr<BoomerangStateMachine> m_stateMachine;

	//初期座標
	DirectX::SimpleMath::Vector3 m_initialPosition;
	//
	DirectX::SimpleMath::Vector3 m_initialScale;

	DirectX::SimpleMath::Quaternion m_initialRotation;
	//投げる軌道の基準座標
	std::vector<DirectX::SimpleMath::Vector3> m_throwbasePosition;


	std::unique_ptr<WataLib::Shadow> m_shadow;
	//1フレ前の座標
	DirectX::SimpleMath::Vector3 m_prevPosition;

	bool m_isCatch;

};