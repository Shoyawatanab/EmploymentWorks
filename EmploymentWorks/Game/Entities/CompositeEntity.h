/*
* プレイヤクラス　
*/

#pragma once

#include "CharacterEntity.h"


class CompositeEntity : public CharacterEntity
{
public:


	CompositeEntity(CommonResources* resources
		, const DirectX::SimpleMath::Vector3& scale
		, const DirectX::SimpleMath::Vector3& position
		, const DirectX::SimpleMath::Quaternion& rotation);

	~CompositeEntity() override;

	void AddChild(std::unique_ptr<CharacterEntity> parts);

	std::vector<std::unique_ptr<CharacterEntity>>& GetParts() { return m_parts; }


//BaseEntity
	//初期化
	void Initialize();
	//更新処理
	void  Update(const float& elapsedTime)  override;
	//描画
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection);
//CollisionEntity
		//当たった時に呼び出される
	void OnCollisionEnter(CollisionEntity* object, CollisionTag tag) override;

//CharactorEntity
	//アニメーションの登録
	void SetAnimationData(std::string animationType
		, std::unordered_map<std::string, std::unordered_map<std::string, WataLib::Json::AnimationData>> datas
		, const std::string& partsName = ""
		, bool isNormalAnimation = false) override ;
	//アニメーションの変更
	void ChangeAnimation(std::string animationType) override ;


private:

	//パーツ
	std::vector<std::unique_ptr<CharacterEntity>> m_parts;


};


