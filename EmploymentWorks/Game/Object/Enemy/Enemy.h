#pragma once
/*
	@file	Enemy.h.h
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include"Game/Object/Boomerang/Boomerang.h"
#include "Interface/ICollisionObject.h"
#include "Interface/IBehaviorNode.h"


// 前方宣言
class CommonResources;
class Bounding;
class BehaviorTree;
class Player;


namespace mylib
{
	class DebugCamera;
	class GridFloor;
	class CollisionMesh;
}


class Enemy : public ICollisionObject

{
public:


	DirectX::SimpleMath::Vector3 GetPosition() { return m_position; }
	void SetPosition(DirectX::SimpleMath::Vector3 Pos) { m_position = Pos; }
	DirectX::SimpleMath::Quaternion GetRotate() { return m_rotate; }
	void SetRotate(DirectX::SimpleMath::Quaternion rotate) { m_rotate = rotate; }
	float GetScale() { return m_scale; }

	DirectX::SimpleMath::Vector3 GetTargetPos() { return m_targetPos; }

	DirectX::SimpleMath::Vector3 Getforward() { return m_forward; }
	void Setforward(DirectX::SimpleMath::Vector3 direction) { m_forward = direction; }


	bool GetIsAttack() { return m_isAttack; }


public:

	//初期のターゲットの座標の距離
	static const DirectX::SimpleMath::Vector3 STAETTAEGETDIRECTION;

	//敵の初期の向いている方向
	static const DirectX::SimpleMath::Vector3 INITIALFORWARD;


private:
	// 共通リソース
	CommonResources* m_commonResources;

	// モデル
	std::unique_ptr<DirectX::Model> m_model;

	DirectX::SimpleMath::Vector3 m_position;
	DirectX::SimpleMath::Quaternion m_initialRotate;
	DirectX::SimpleMath::Quaternion m_rotate;

	std::unique_ptr<Bounding> m_bounding;

	float m_hp;
	float m_maxHP;
	float m_graivty;


	float m_collisionTime;
	bool m_isCollsionTime;

	float m_scale;


	std::unique_ptr<BehaviorTree> m_behavior;

	Player* m_player;

	//向いている方向
	DirectX::SimpleMath::Vector3 m_forward;


	//ノックバックの方向
	DirectX::SimpleMath::Vector3 m_knockbackDirection;
	float m_acceleration;
	float m_knockbackTime;


	//ブーメランのターゲットの座標
	DirectX::SimpleMath::Vector3 m_targetPos;



	//当たった時の相手のタグ
	CollsionObjectTag m_onCollisionTag;

	bool m_isAttack;

	std::unique_ptr<mylib::CollisionMesh> m_collisionMesh;

public:
	Enemy();
	~Enemy() ;

	void Initialize(CommonResources* resources, DirectX::SimpleMath::Vector3 position) ;
	void Update(float elapsedTime);
	void Render(DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection) ;
	void Finalize() ;

	void ReduceSize(float elapsdTime);

	//クラスに必要な情報（ポインタ）を登録する
	void RegistrationInformation(Player* player);

	//クラスのインスタンス
	void Instances();


	//遠距離攻撃　ビヘイビアツリーで呼び出す
	IBehaviorNode::State BeamAttack(float elapsdTime);


	void RegistrationCollionManager(CollisionManager* collsionManager) override;

	Bounding* GetBounding() const override { return m_bounding.get(); };

	CollsionObjectTag GetCollsionTag() const override { return CollsionObjectTag::Enemy; }

	void SetPos(DirectX::SimpleMath::Vector3& Pos) override { m_position = Pos; }

	DirectX::SimpleMath::Vector3 GetPos()override { return m_position; }

	float GetHp() { return m_hp; }

	float GetMAXHp() { return m_maxHP; }

	void OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos) override;

	mylib::CollisionMesh* GetCollsionMesh() override { return m_collisionMesh.get(); }

};
