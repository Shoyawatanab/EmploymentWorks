#pragma once
#ifndef PlayerLeftFeet_DEFINED
#define PlayerLeftFeet_DEFINED
#include "Interface/IComponent.h"
#include "Game/Object/Player/PlayerParts/PlayerBase.h"


// 「砲塔」クラスを定義する
class PlayerLeftFeet : public PlayerBase
{
public:
	//現在の大きさの取得
	DirectX::SimpleMath::Vector3 GetScale() const { return m__currentScale; }
	//// 現在の位置を取得する
	//DirectX::SimpleMath::Vector3 GetPosition() const { return m_currentPosition; }
	//// 現在の位置を設定する
	//void SetPosition(const DirectX::SimpleMath::Vector3& currretPosition) { m_currentPosition = currretPosition; }
	// 現在の回転角を取得する
	DirectX::SimpleMath::Quaternion GetAngle() const { return m_currentAngle; }
	// 現在の回転角を設定する
	void SetAngle(const DirectX::SimpleMath::Quaternion& currentAngle) { m_currentAngle = currentAngle; }
	// モデルを取得する
	DirectX::Model* GetModel() { return nullptr; }
	// ワールド行列を取得する
	DirectX::SimpleMath::Matrix& GetWorldMatrix() { return m_worldMatrix; }



	CollsionObjectTag GetCollsionTag() const override { return CollsionObjectTag::EnemyParts; }

	void SetPosition(DirectX::SimpleMath::Vector3& Pos) override { m_currentPosition = Pos; }

	DirectX::SimpleMath::Vector3 GetPosition() override { return m_currentPosition; }

	void OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos) override;

public:
	// コンストラクタ
	PlayerLeftFeet(CommonResources* resources, IComponent* parent,const  DirectX::SimpleMath::Vector3 scale, const DirectX::SimpleMath::Vector3& positonFromParent, const DirectX::SimpleMath::Quaternion& initialAngleRL);
	// デストラクタ
	~PlayerLeftFeet() override;
	// 初期化する
	void Initialize() override;
	// 更新する
	void Update(const float& elapsdTime) override;
	// 描画する
	void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection) override;
	// 後処理を行う
	void Finalize() override;
	// 砲弾をチャージする
	void ChargeBullets();
	// 砲塔境界スフィアを作成する
	DirectX::BoundingSphere CreateBoundingSphere(const float& radius);
private:

	std::unique_ptr<DirectX::Model> m_model;
	//現在の大きさ
	DirectX::SimpleMath::Vector3 m__currentScale;

	// 現在の位置
	DirectX::SimpleMath::Vector3 m_currentPosition;
	// 現在の回転角
	DirectX::SimpleMath::Quaternion m_currentAngle;
	// 砲塔部品配列
	std::vector<std::unique_ptr<IComponent>> m_PlayerLeftFeetParts;
	//	ワールド行列
	DirectX::SimpleMath::Matrix m_worldMatrix;
	// 砲塔中心点
	DirectX::SimpleMath::Vector3 m_PlayerLeftFeetCenter;
};

#endif		// PlayerLeftFeet_DEFINED
