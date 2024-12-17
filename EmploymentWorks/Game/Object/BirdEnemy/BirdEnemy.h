#pragma once
#ifndef BirdEnemy_DEFINED
#define BirdEnemy_DEFINED
#include "Interface/IComponent.h"
#include  "Game/Object/BirdEnemy/BirdEnemyBase.h"
#include "Interface/IBirdEnemyState.h"
#include "Game/Object/BirdEnemy/State/BirdEnemyIdling.h"
#include "Game/Object/BirdEnemy/State/BirdEnemyAttack.h"
//#include "Game/Object/BirdEnemy/State/BirdEnemyUsually.h"

class Player;

// 「砲塔」クラスを定義する
class BirdEnemy : public BirdEnemyBase
{
public:
	//現在の大きさの取得
	DirectX::SimpleMath::Vector3 GetScale() const override { return m_scale; }
	// 現在の回転角を取得する
	DirectX::SimpleMath::Quaternion GetAngle() const { return m_rotate; }
	// 現在の回転角を設定する
	void SetAngle(const DirectX::SimpleMath::Quaternion& currentAngle) { m_rotate = currentAngle; }
	// モデルを取得する
	DirectX::Model* GetModel() { return nullptr; }
	// ワールド行列を取得する
	DirectX::SimpleMath::Matrix& GetWorldMatrix() { return m_worldMatrix; }

	//State
	IBirdEnemyState* GetCurrentState() { return m_currentState; }
	BirdEnemyldling* GetIdling() { return m_idling.get(); }
	BirdEnemyAttack* GetAttack() { return m_attack.get(); }

public:
	// コンストラクタ
	BirdEnemy(CommonResources* resources, IComponent* parent, DirectX::SimpleMath::Vector3 initialScale, const DirectX::SimpleMath::Vector3& positonFromParent, const DirectX::SimpleMath::Quaternion& initialAngle);
	// デストラクタ
	~BirdEnemy() override;
	// 初期化する
	void Initialize() override;
	// キーボードイベントを処理する
	inline void HandleKeyboardEvent();
	// 更新する
	void Update(const float& elapsdTime) override;
	// 描画する
	void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection) override;
	// 後処理を行う
	void Finalize() override;
	// 砲塔境界スフィアを作成する
	DirectX::BoundingSphere CreateBoundingSphere(const float& radius);


	void SetAnimation(std::string name);

	//クラスに必要な情報（ポインタ）を登録する
	void RegistrationInformation(Player* player);

	//クラスのインスタンス
	void Instances();


	void RegistrationCollionManager(CollisionManager* collsionManager) override;

	Bounding* GetBounding() const override { return m_bounding.get(); };

	CollsionObjectTag GetCollsionTag() const override { return CollsionObjectTag::Enemy; }

	void SetPosition(DirectX::SimpleMath::Vector3& Pos) override { m_position = Pos; }

	DirectX::SimpleMath::Vector3 GetPosition()override { return m_position; }


	void OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos) override;

	//State


private:


	// 共通リソース
	CommonResources* m_commonResources;

	DirectX::SimpleMath::Vector3 m_position;
	DirectX::SimpleMath::Quaternion m_initialRotate;
	DirectX::SimpleMath::Quaternion m_rotate;
	std::unique_ptr<Bounding> m_bounding;
	DirectX::SimpleMath::Matrix m_worldMatrix;

	DirectX::SimpleMath::Vector3 m_scale;

	Player* m_player;


	//State
	IBirdEnemyState* m_currentState;
	std::unique_ptr<BirdEnemyldling> m_idling;
	std::unique_ptr<BirdEnemyAttack> m_attack;



};

#endif		// BirdEnemy_DEFINED


//BirdEnemy全体の情報を持つ