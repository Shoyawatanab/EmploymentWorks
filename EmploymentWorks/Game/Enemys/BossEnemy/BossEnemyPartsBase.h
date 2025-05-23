#pragma once
#include "Game/Entities/CompositeEntity.h"
#include "Game/Observer/EventParams.h"

class CommonResources;
class BossEnemy;

namespace WataLib
{
	class Animation;
}



class BossEnemyPartsBase : public CompositeEntity
{

public:
	//モデルの取得
	DirectX::Model* GetModel() { return m_model; }
	//モデルの登録
	void  SetModel(DirectX::Model* model) { m_model = model; }
	//ルートの主特区
	BossEnemy* GetRoot() { return m_root; }
	//パーツHPの取得
	const int& GetPartsHP() { return m_partsHP; }

	/// <summary>
	/// パーツ破壊されているかどうかの取得
	/// </summary>
	/// <returns>ture:破壊されている false:破壊されていない</returns>
	const bool& GetIsPartDestruction() { return m_isPartDestruction; }
	//パーツ破壊されているかどうかの登録
	void SetIsPartDestruction(bool isPartDestruction) { m_isPartDestruction = isPartDestruction;; }

public:
	// コンストラクタ
	BossEnemyPartsBase(CommonResources* resources
		, BossEnemy* root,
		CharacterEntity* parent,
		DirectX::SimpleMath::Vector3 scale,
		DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Quaternion rotation,
		std::string partsName,
		int partsHP
		, DirectX::SimpleMath::Vector3 boxColliderSize,
		float SphereColliderSize);
	//デストラクタ
	~BossEnemyPartsBase()  override;


	
	//初期化
	void Initialize() override;
	//描画処理
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;
	//タグの取得
	CollisionTag GetCollisionTag() override { return CollisionEntity::CollisionTag::ENEYPARTS; };
	//当たり判定クラスに登録
	void  AddCollision(CollisionManager* collsionManager) override;
	//当たった時に呼び出される
	void OnCollisionEnter(CollisionEntity* object, CollisionTag tag) override;
	//当たり判定の種類の取得
	const CollisionType GetCollisionType() override { return CollisionType::OBB; };
	//押し出しをするかどうか
	const bool GetIsExtrusion() override { return true; };
	//当たり判定を行わないタグ
	const std::vector<CollisionTag> GetNoHitDetectionTag() {
		return  {
			{CollisionTag::PLAYERPARTS}
			,{CollisionTag::ENEMY}
			,{CollisionTag::ENEYPARTS}

		};
	};

	//押し出しを行わないタグ
	const std::vector<CollisionTag> GetNoExtrusionTag() {
		return  {
		};
	};
	//更新処理
	void  Update(const float& elapsedTime) override;


	//アニメーションの登録
	void SetAnimationData(std::string animationType
		, std::unordered_map<std::string, std::unordered_map<std::string, WataLib::Json::AnimationData>> datas
		, const std::string& partsName = ""
		, bool isNormalAnimation = false) override;
	//アニメーションの変更
	void ChangeAnimation(std::string animationType) override;



	//パーツに対してメッセージを送る
	void NotifyParts(PartMessageType type);

private:
	//モデル
	DirectX::Model* m_model;
	//パーツ名
	std::string m_partsName;
	//初期座標
	DirectX::SimpleMath::Vector3 m_initialPosition;
	//初期の大きさ
	DirectX::SimpleMath::Vector3 m_initialScale;
	//初期回転
	DirectX::SimpleMath::Quaternion m_initialRotation;
	//パーツHP
	int m_partsHP;
	//四角の当たり判定の大きさ
	DirectX::SimpleMath::Vector3 m_boxColliderSize;
	//円の当たり判定の大きさ
	float m_sphereColliderSize;
	//根本のクラス
	BossEnemy* m_root;
	//パーツ破壊されているか
	bool m_isPartDestruction;


};
