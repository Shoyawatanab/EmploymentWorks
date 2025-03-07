/*
* プレイヤクラス　
*/

#pragma once

#include "MoveEntity.h"
#include <unordered_map>
#include "Libraries/WataLib/Json.h"

namespace WataLib
{
	class Animation;
}

class CharacterEntity : public MoveEntity
{
public:


	const std::string& GetCurrentAnimationType() { return m_currentAnimationType; }

	void SetCurrentAnimationType(const std::string& type) { m_currentAnimationType = type; }

	WataLib::Animation* GetAnimation() { return m_animation.get(); }

public:


	CharacterEntity(CommonResources* resources
		,const DirectX::SimpleMath::Vector3& scale
		, const DirectX::SimpleMath::Vector3& position
		, const DirectX::SimpleMath::Quaternion& rotation);

	~CharacterEntity() override;

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




	//アニメーションの登録
	virtual void SetAnimationData(std::string animationType
		, std::unordered_map<std::string, std::unordered_map<std::string, WataLib::Json::AnimationData>> datas
		, const std::string& partsName = ""
		, bool isNormalAnimation = false);
	//アニメーションの変更
	virtual	void ChangeAnimation(std::string animationType);




private:

	//実行アニメーション名
	std::string m_currentAnimationType;

	std::unique_ptr<WataLib::Animation> m_animation;


};


