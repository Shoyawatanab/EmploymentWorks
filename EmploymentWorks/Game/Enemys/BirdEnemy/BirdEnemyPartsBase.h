#pragma once
#include "Game/Entities/CompositeEntity.h"

//前方宣言
class Player;


namespace WataLib
{
	class Animation;
}


class BirdEnemyPartsBase : public CompositeEntity
{

public:
	//モデルの取得
	DirectX::Model* GetModel() { return m_model; }
	//モデルの登録
	void  SetModel(DirectX::Model* model) { m_model = model; }

public:
	//コンストラクタ
	BirdEnemyPartsBase(CommonResources* resources,
		CharacterEntity* parent
		, std::string partsName,
		DirectX::SimpleMath::Vector3 scale,
		DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Quaternion rotation);
	//デストラクタ
	~BirdEnemyPartsBase()  override;

	//初期化
	void Initialize() override;
	//描画処理
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;
	//タグの取得
	CollisionTag GetCollisionTag() override { return CollisionEntity::CollisionTag::ENEYPARTS; };
	//当たった時に呼び出される
	void OnCollisionEnter(CollisionEntity* object, CollisionTag tag) override;
	//当たり判定の種類の取得
	const CollisionType GetCollisionType() override { return CollisionType::OBB; };
	//押し出しをするかどうか
	const bool GetIsExtrusion() override { return true; };
	//当たり判定を行わないタグ
	const std::vector<CollisionTag> GetNoHitDetectionTag() {
		return  {
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

private:
	//モデル
	DirectX::Model* m_model;
	//パーツ名
	std::string m_partsName;
	//初期座標
	DirectX::SimpleMath::Vector3 m_initialPosition;
	//初期スケール
	DirectX::SimpleMath::Vector3 m_initialScale;
	//初期回転
	DirectX::SimpleMath::Quaternion m_initialRotation;





};
