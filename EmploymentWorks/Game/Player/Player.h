/*
* プレイヤクラス　
*/

#pragma once
#include "Game/Entities/CompositeEntity.h"
#include "Libraries/WataLib/Json.h"
#include "Game/Weapon/Boomerang/Boomerang.h"
#include "Game/Weapon/Boomerang/State/BoomerangStateMachine.h"
#include "Game/TargetMarker.h"
#include "Libraries/WataLib/Shadow.h"

// 前方宣言
class CommonResources;
class PlayerUsually;
class PlayerStateMachine;
class Boomerang;


namespace WataLib
{
	class TPS_Camera;
	class Bounding;
}

class Player : public CompositeEntity 
{

public:

	PlayerStateMachine* GetPlayerStateMachine() { return m_stateMachine.get(); };

	std::vector<std::unique_ptr<Boomerang>>* GetBoomerangs() { return &m_boomerangs; }

	/// <summary>
	/// ブーメランの取得（Stateが該当するクラスと同じクラスを）
	/// </summary>
	/// <typeparam name="T">Stateクラス</typeparam>
	/// <returns>該当するクラス（配列の初めの方から調べる）</returns>
	template<typename T>
	Boomerang* GetBoomerang()
	{
		auto it = std::find_if(m_boomerangs.begin(), m_boomerangs.end(),
			[](const std::unique_ptr<Boomerang>& boomerang) {
				return typeid(*boomerang->GetBoomerangStatemachine()->GetCurrentState()) == typeid(T);
			});

		// 見つからない場合は nullptr を返す
		return (it != m_boomerangs.end()) ? it->get() : nullptr;
	};



public:
	//コンストラクタ
	Player(CommonResources* resources);

	//デストラクタ
	~Player() override;


//IObject
	//初期化
	void Initialize() override;

	//void TitleInitialize();

	//描画
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;
	//更新処理
	void  Update(const float& elapsedTime) override;


//ICollisionObject
	//タグの取得
	CollisionTag GetCollisionTag() override { return CollisionEntity::CollisionTag::PLAYER; };
	//当たり判定クラスに登録
	void  AddCollision(CollisionManager* collsionManager) override ;

	//当たった時に呼び出される
	void OnCollisionEnter(CollisionEntity* object, CollisionTag tag) override;
	//当たり続けているときの呼び出される
	void OnCollisionStay(CollisionEntity* object, CollisionTag tag) override;

	//当たり判定の種類の取得
	const CollisionType GetCollisionType() override { return CollisionType::AABB; }
	//押し出しをするかどうか
	const bool GetIsExtrusion() override { return true; };
	//当たり判定を行わないタグ
	const std::vector<CollisionTag> GetNoHitDetectionTag() {
		return  {
			{CollisionTag::PLAYERPARTS}
			//,{CollisionTag::Boomerang}
		};
	}

	//押し出しを行わないタグ
	const std::vector<CollisionTag> GetNoExtrusionTag() {
		return  {
			{CollisionTag::BOOMERANG}
		};
	};


//ICharacter
	//アニメーションの登録
	void SetAnimationData(const std::string& animationType
		,std::unordered_map<std::string, std::unordered_map<std::string, WataLib::Json::AnimationData>> datas
		, const std::string& partsName = ""
		, bool isNormalAnimation = false) override;
	//アニメーションの変更
	void ChangeAnimation(const std::string& animationType) override;

private:
	//宣言

	//動き
	std::unique_ptr<PlayerUsually> m_usually;
	//アニメーションデータ
	std::unordered_map<std::string, std::unordered_map<std::string, WataLib::Json::AnimationData>> m_animationDatas;
	//ステートマシン
	std::unique_ptr<PlayerStateMachine>  m_stateMachine;

	//ブーメラン
	std::vector<std::unique_ptr<Boomerang>> m_boomerangs;
	//使用中のブーメラン
	Boomerang* m_currentBoomerang;
	//HP
	int m_hp;
	// 影オブジェクト
	std::unique_ptr<WataLib::Shadow> m_shadow;

};


