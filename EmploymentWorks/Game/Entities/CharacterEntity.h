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

	//実行中のアニメーションの種類
	const std::string& GetCurrentAnimationType() { return m_currentAnimationType; }
	//実行するアニメーションの登録
	void SetCurrentAnimationType(const std::string& type) { m_currentAnimationType = type; }
	//アニメーションの取得
	WataLib::Animation* GetAnimation() { return m_animation.get(); }

public:
	//コンストラク
	CharacterEntity(CommonResources* resources
		,const DirectX::SimpleMath::Vector3& scale
		, const DirectX::SimpleMath::Vector3& position
		, const DirectX::SimpleMath::Quaternion& rotation);
	//デストラクタ
	~CharacterEntity() override;

//BaseEntity
	//初期化
	void Initialize();
	//更新処理
	void  Update(const float& elapsedTime)  override;
	//描画処理
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection);
//CollisionEntity
	//当たった時に呼び出される
	void OnCollisionEnter(CollisionEntity* object, CollisionTag tag) override;


	//アニメーションの登録
	virtual void SetAnimationData(const std::string& animationType
		, std::unordered_map<std::string, std::unordered_map<std::string, WataLib::Json::AnimationData>> datas
		, const std::string& partsName = ""
		, bool isNormalAnimation = false);
	//アニメーションの変更
	virtual	void ChangeAnimation(const std::string& animationType);

private:

	//実行アニメーション名
	std::string m_currentAnimationType;
	//アニメーション
	std::unique_ptr<WataLib::Animation> m_animation;


};


