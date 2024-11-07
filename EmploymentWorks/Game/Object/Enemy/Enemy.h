#pragma once
/*
	@file	Enemy.h.h
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include"Game/Object/Boomerang/Boomerang.h"
#include "Interface/ICollisionObject.h"
#include "Interface/IBehaviorNode.h"

#include "Game/Object/Enemy/BossEnemy/BossEnemyBase.h"
#include "Libraries/MyLib/Animation.h"

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


class Enemy : public BossEnemyBase
	
{
public:


	DirectX::SimpleMath::Quaternion GetRotate() { return m_rotate; }
	void SetRotate(DirectX::SimpleMath::Quaternion rotate) { m_rotate = rotate; }
	// GetScale() { return m_scale; }

	DirectX::SimpleMath::Vector3 GetTargetPos() { return m_targetPos; }

	DirectX::SimpleMath::Vector3 Getforward() { return m_forward; }
	void Setforward(DirectX::SimpleMath::Vector3 direction) { m_forward = direction; }


	bool GetIsAttack() { return m_isAttack; }

	Beam* GetBeam() { return m_beam.get(); }

	DirectX::SimpleMath::Vector3 GetBeamStartPosition() { return m_beamStartPosition; }

public:

	//初期のターゲットの座標の距離
	static const DirectX::SimpleMath::Vector3 STAETTAEGETDIRECTION;

	//敵の初期の向いている方向
	static const DirectX::SimpleMath::Vector3 INITIALFORWARD;


private:
	// 共通リソース
	CommonResources* m_commonResources;

	// モデル
	//std::unique_ptr<DirectX::Model> m_model;

	DirectX::SimpleMath::Vector3 m_position;
	DirectX::SimpleMath::Quaternion m_initialRotate;
	DirectX::SimpleMath::Quaternion m_rotate;

	std::unique_ptr<Bounding> m_bounding;

	//	ワールド行列
	DirectX::SimpleMath::Matrix m_worldMatrix;


	float m_hp;
	float m_maxHP;
	float m_graivty;


	float m_collisionTime;
	bool m_isCollsionTime;

	DirectX::SimpleMath::Vector3 m_scale;


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

	DirectX::SimpleMath::Vector3 m_boundingBoxCenter;

	//ビーム攻撃のスタート座標
	DirectX::SimpleMath::Vector3 m_beamStartPosition;

	//ビームを右手で打つ時の敵の中心からの距離
	DirectX::SimpleMath::Vector3 m_rightHandPos;
	//攻撃の予備動作時間
	float m_preliminaryActionTime;

	//Walkに関する関数
	float m_walkSpeed;
	float m_walkAccelration;
	float m_stepDuration;
	float m_stepTime;
	bool m_isStep;

	//ジャンプ関係関数
	//ジャンプの座標　１．初期値　２　中間座標　３最終座標　４　スプライン曲線用に求める
	std::vector<DirectX::SimpleMath::Vector3> m_jumpPosition;
	//ジャンプの高さ
	float m_jumpHeight;
	//
	bool m_isJumpAttack;
	//ジャンプ攻撃座標のインデックス
	int m_jumpAttackIndex;
	//点と点の間の移動割合
	float m_transformRatio;
	float m_jumpAttackTime;

public:
	Enemy(CommonResources* resources, IComponent* parent, const DirectX::SimpleMath::Vector3 initialScale, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle);
	~Enemy() ;

	void Initialize() ;
	void Update(float elapsedTime);
	void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection) ;
	void Finalize() ;

	Animation::AnimationState FallDwonAnimation(float elapsdTime);

	void SetAnimation(std::string name);

	//クラスに必要な情報（ポインタ）を登録する
	void RegistrationInformation(Player* player);

	//クラスのインスタンス
	void Instances();

	void Walk(float elapsdTime);

	IBehaviorNode::State JumpAttack(float elapstTime);

	//遠距離攻撃　ビヘイビアツリーで呼び出す
	IBehaviorNode::State BeamAttack(float elapsdTime);
	//近距離攻撃　ビヘイビアツリーで呼び出す
	IBehaviorNode::State CloseRangeAttack(float elapsdTime);

	void RegistrationCollionManager(CollisionManager* collsionManager) override;

	Bounding* GetBounding() const override { return m_bounding.get(); };

	CollsionObjectTag GetCollsionTag() const override { return CollsionObjectTag::Enemy; }

	void SetPosition(DirectX::SimpleMath::Vector3& Pos) override { m_position = Pos; }

	DirectX::SimpleMath::Vector3 GetPosition()override { return m_position; }

	float GetHp() { return m_hp; }

	float GetMAXHp() { return m_maxHP; }

	void OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos) override;

	//現在の大きさの取得
	DirectX::SimpleMath::Vector3 GetScale() const override { return m_scale; }
	// 現在の位置を取得する
	//DirectX::SimpleMath::Vector3 GetPosition() const { return m_currentPosition; }
	// 現在の位置を設定する
	//void SetPosition(const DirectX::SimpleMath::Vector3& currretPosition) { m_currentPosition = currretPosition; }
	// 現在の回転角を取得する
	DirectX::SimpleMath::Quaternion GetAngle() const override  { return m_rotate; }
	// 現在の回転角を設定する
	void SetAngle(const DirectX::SimpleMath::Quaternion& currentAngle) override { m_rotate = currentAngle; }
	// モデルを取得する
	DirectX::Model* GetModel() override { return nullptr; }
	// ワールド行列を取得する
	DirectX::SimpleMath::Matrix& GetWorldMatrix()  { return m_worldMatrix; }



	//プレイヤのほうに向く  ビヘイビアツリーにもおんなじのがあるからどうにかしたい　攻撃の予備動作中でもプレイヤの方向を向いてほしいからここに追加した
	void  FacingThePlayer(float elapsdTime);

};
