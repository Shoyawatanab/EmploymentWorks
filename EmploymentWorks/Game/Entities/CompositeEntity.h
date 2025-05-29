/*
* プレイヤクラス　
*/

#pragma once

#include "CharacterEntity.h"
#include "Game/Observer/EventParams.h"

class CompositeEntity : public CharacterEntity
{
public:

	//パーツの取得
	std::vector<std::unique_ptr<CompositeEntity>>& GetParts() { return m_parts; }

public:
	//コンストラク
	CompositeEntity(CommonResources* resources
		, const DirectX::SimpleMath::Vector3& scale
		, const DirectX::SimpleMath::Vector3& position
		, const DirectX::SimpleMath::Quaternion& rotation);
	//デストラクタ
	~CompositeEntity() override;
	//子の追加
	void AddChild(std::unique_ptr<CompositeEntity> parts);


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
	void SetAnimationData(const std::string& animationType
		, std::unordered_map<std::string, std::unordered_map<std::string, WataLib::Json::AnimationData>> datas
		, const std::string& partsName = ""
		, bool isNormalAnimation = false) override ;
	//アニメーションの変更
	void ChangeAnimation(const std::string& animationType) override ;

	//パーツに対してメッセージを送る　
	virtual void NotifyParts(PartMessageType type) { UNREFERENCED_PARAMETER(type); };

private:

	//パーツ
	std::vector<std::unique_ptr<CompositeEntity>> m_parts;


};

