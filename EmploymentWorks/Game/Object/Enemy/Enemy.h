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
class Beam;


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
	void SetPosition(DirectX::SimpleMath::Vector3 Pos) { m_position = Pos; }
	DirectX::SimpleMath::Quaternion GetRotate() { return m_rotate; }
	void SetRotate(DirectX::SimpleMath::Quaternion rotate) { m_rotate = rotate; }
	float GetScale() { return m_scale; }

	DirectX::SimpleMath::Vector3 GetTargetPos() { return m_targetPos; }

	DirectX::SimpleMath::Vector3 Getforward() { return m_forward; }
	void Setforward(DirectX::SimpleMath::Vector3 direction) { m_forward = direction; }


	bool GetIsAttack() { return m_isAttack; }

	Beam* GetBeam() { return m_beam.get(); }


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
	int m_maxHP;
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

	//ビームクラス
	std::unique_ptr<Beam> m_beam;


	//当たった時の相手のタグ
	CollsionObjectTag m_onCollisionTag;

	bool m_isAttack;


public:
	Enemy();
	~Enemy() ;

	void Initialize(CommonResources* resources, DirectX::SimpleMath::Vector3 position) ;
	void Update(float elapsedTime);
	void Render(DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection) ;
	void Finalize() ;

	void ReduceSize(float elapsdTime);


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

};
