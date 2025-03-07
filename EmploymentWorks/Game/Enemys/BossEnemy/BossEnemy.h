/*
* プレイヤクラス　
*/

#pragma once
#include "Game/Entities/EnemyEntity.h"
#include "Libraries/WataLib/Json.h"
#include "Game/Weapon/Boomerang/Boomerang.h"
#include "Game/Interface/IWeapon.h"
#include "Game/Enemys/EnemyManager.h"
#include "Game/Enemys/BossEnemy/BehaviorTree/BehaviorTree.h"
#include "Game/Interface/IObserver.h"

#include "Game/Observer/Messenger.h"
#include "Libraries/WataLib/Shadow.h"
#include "Game/Enemys/EnemyManager.h"
#include "Game/Interface/IActione.h"

// 前方宣言
class CommonResources;
class Boomerang;
class EnemyManager;
class BehaviorTree;
class Player;
class Beam;
class StageObjectManager;
class Barrier;


namespace WataLib
{
	class Bounding;
}

class BossEnemy : public EnemyEntity  , public IObserver
{
public:

	static constexpr float PUNCHTIME{ 5.0f };

	enum class AttackState
	{
		None
		,End
		,Beam


	};

public:

	BaseEntity* GetTarget() { return m_target; }

	void SetTarget(BaseEntity* target) { m_target = target; }

public:
	//コンストラクタ
	BossEnemy(CommonResources* resources,
		DirectX::SimpleMath::Vector3 scale,
		DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Quaternion rotation);
	//デストラクタ
	~BossEnemy() override;

	//IObject
	//初期化
	void Initialize() override;
	//描画
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;
	//更新処理
	void  Update(const float& elapsedTime) override;

	//ICollisionObject
		//タグの取得
	CollisionTag GetCollisionTag() override { return CollisionEntity::CollisionTag::Enemy; };
	//当たり判定クラスに登録
	void  AddCollision(CollisionManager* collsionManager) override;

	//当たった時に呼び出される
	void OnCollisionEnter(CollisionEntity* object, CollisionTag tag) override;
	//当たり判定の種類の取得
	const CollisionType GetCollisionType() override { return CollisionType::AABB; }
	//押し出しをするかどうか
	const bool GetIsExtrusion() override { return true; };
	//当たり判定を行わないタグ
	const std::vector<CollisionTag> GetNoHitDetectionTag() {
		return  {
			{CollisionTag::PlayerParts}
			,{CollisionTag::EnemyParts}
			,{CollisionTag::Boomerang}
			,{CollisionTag::Beam}
			,{CollisionTag::Barrier}
		};
	}

	//ICharacter
		//アニメーションの登録
	void SetAnimationData(std::string animationType
		, std::unordered_map<std::string, std::unordered_map<std::string, WataLib::Json::AnimationData>> datas
		, const std::string& partsName = ""
		, bool isNormalAnimation = false) override;
	//アニメーションの変更
	void ChangeAnimation(std::string animationType) override;


//通知時に呼ばれる関数
	void Notify(EventParams::EventType type, void* datas)  override;


	//必要なポインタの登録
	void AddPointer(Player* player, StageObjectManager* stageObjectManager);


	//HPの取得
	int& GetHP() { return m_hp; }

	//ダメージ
	void Damage(int damage) {
		m_hp -= damage;

		if (m_hp <= 0 && m_hp + damage > 0)
		{
			//倒れるアニメーションに切り替える
			ChangeAnimation("FallDown");
			EnemyEntity::GetEnemyManager()->DeleteRemainingEnemy(this);
			Messenger::Notify(EventParams::EventType::GameClear, nullptr);
		}

	}

	//ビヘイビアツリーで使用
	//ビーム攻撃
	IBehaviorNode::State BeamAttack(const float& elapsedTime);
	//歩く
	IBehaviorNode::State Walk(const float& elapsedTime);
	//たたきつけ
	IBehaviorNode::State Pounding(const float& elapsedTime);
	//
	IBehaviorNode::State FacingThePlayer(float elapsdTime);

private:
	//アニメーションデータ
	std::unordered_map<std::string, std::unordered_map<std::string, WataLib::Json::AnimationData>> m_animationDatas;
	//ビヘイビアツリー
	std::unique_ptr<BehaviorTree> m_behavior;
	//プレイヤ
	Player* m_player;
	//ビーム
	std::unique_ptr<Beam> m_beam;
	//攻撃状態
	AttackState m_attackState;
	//影
	std::unique_ptr<WataLib::Shadow> m_shadow;
	//各動作
	std::unordered_map<std::string, std::unique_ptr<IAction>> m_action;

	std::unique_ptr<Barrier> m_barrier;

	//ターゲット
	BaseEntity* m_target;

	StageObjectManager* m_stageObjectmanger;

	float m_gravity;
	//Hp
	int m_hp;

	//パンチ攻撃の時間
	float m_punchTime;

	bool m_isActives;

};


