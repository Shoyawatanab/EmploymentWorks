/*
* プレイヤクラス　
*/

#pragma once
#include "Game/Entities/EnemyEntity.h"
#include "Libraries/WataLib/Json.h"
#include "Game/Enemys/EnemyManager.h"
#include "Game/Interface/IObserver.h"

#include "Game/Observer/Messenger.h"
#include "Game/Enemys/BirdEnemy/State/BirdEnemyStateMachine.h"
#include "Libraries/WataLib/Shadow.h"

// 前方宣言
class CommonResources;
class EnemyManager;
class Player;
class BirdEnemyBeam;



namespace WataLib
{
	class Bounding;
}

class BirdEnemy : public EnemyEntity
{

public:

	BirdEnemyStateMachine* GetPlayerStateMachine() { return m_stateMachine.get(); };

	DirectX::SimpleMath::Vector3 GetBeamPosition() { return m_beamPosition; };

	std::vector<std::unique_ptr<BirdEnemyBeam>>& GetBeams() { return m_beam; }


public:

	//コンストラクタ
	BirdEnemy(CommonResources* resources
		, DirectX::SimpleMath::Vector3 scale,
		DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Quaternion rotation);
	//デストラクタ
	~BirdEnemy() override;

	//IObject
		//初期化
	void Initialize() override;
	//描画処理
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;
	//更新処理
	void  Update(const float& elapsedTime) override;


	//タグの取得
	CollisionTag GetCollisionTag() override { return CollisionEntity::CollisionTag::ENEYPARTS; };
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
			{CollisionTag::PLAYERPARTS}
			,{CollisionTag::ENEYPARTS}
			,{CollisionTag::BEAM}
		};
	}
	//押し出しを行わないタグ
	const std::vector<CollisionTag> GetNoExtrusionTag() {
		return  {
		};
	};



	//ICharacter
		//アニメーションの登録
	void SetAnimationData(std::string animationType
		, std::unordered_map<std::string, std::unordered_map<std::string, WataLib::Json::AnimationData>> datas
		, const std::string& partsName = ""
		, bool isNormalAnimation = false) override;
	//アニメーションの変更
	void ChangeAnimation(std::string animationType) override;

	void Rotate(float elapsedTime);

private:
	//宣言
	//敵マネージャー
	EnemyManager* m_enemyManager;
	//プレイヤ
	Player* m_player;
	//影
	std::unique_ptr<WataLib::Shadow> m_shadow;
	//Hp
	int m_hp;

	//パンチ攻撃の時間
	float m_punchTime;


	//ステートマシン
	std::unique_ptr<BirdEnemyStateMachine>  m_stateMachine;
	//ビームの生成座標
	DirectX::SimpleMath::Vector3 m_beamPosition;
	//ビーム
	std::vector<std::unique_ptr<BirdEnemyBeam>> m_beam;



};


