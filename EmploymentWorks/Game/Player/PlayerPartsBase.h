#pragma once
#include "Game/Entities/CompositeEntity.h"

class Player;


namespace WataLib
{
	class Animation;
}


class PlayerPartsBase : public CompositeEntity
{
public:

	DirectX::Model* GetModel() { return m_model.get(); }
	void  SetModel(std::unique_ptr<DirectX::Model> model) { m_model = std::move(model); }


public:
	PlayerPartsBase(CommonResources* resources
		, CharacterEntity* parent,
		std::string partsName,
		DirectX::SimpleMath::Vector3 scale,
		DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Quaternion rotation);

	~PlayerPartsBase()  override;


	//IObject
	//初期化
	void Initialize() override;
	//描画
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;
	//ICollisionObject
	//タグの取得
	CollisionTag GetCollisionTag() override { return CollisionEntity::CollisionTag::Player; };
	//当たった時に呼び出される
	void OnCollisionEnter(CollisionEntity* object, CollisionTag tag) override;
	//当たり判定の種類の取得
	const CollisionType GetCollisionType() override { return CollisionType::OBB; };
	//押し出しをするかどうか
	const bool GetIsExtrusion() override { return true; };
	//当たり判定を行わないタグ
	const std::vector<CollisionTag> GetNoHitDetectionTag() {
		return  {
			CollisionTag::Player
		};
	};

	//IMoveObject
	//更新処理
	void  Update(const float& elapsedTime) override;

	//ICharacter
	//アニメーションの登録
	void SetAnimationData(std::string animationType
		, std::unordered_map<std::string, std::unordered_map<std::string, WataLib::Json::AnimationData>> datas
		, const std::string& partsName = ""
		, bool isNormalAnimation = false) override;
	//アニメーションの変更
	void ChangeAnimation(std::string animationType) override;



	//継承関係変数
private:

	//親子関係を行うかどうか
	bool m_isParentActive;


	std::unique_ptr<DirectX::Model> m_model;
	//親クラス
	CharacterEntity* m_parent;
	//パーツ名
	std::string m_partsName;

	DirectX::SimpleMath::Vector3 m_initialPosition;

	DirectX::SimpleMath::Vector3 m_initialScale;

	DirectX::SimpleMath::Quaternion m_initialRotation;

};
