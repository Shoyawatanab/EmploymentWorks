#pragma once
#include "GameBase/Enemy/EnemyBase.h"


class Player;
class BirdEnemyStateMachine;
class BirdEnemyBullet;

class BirdEnemy : public EnemyBase
{
public:

	//オブジェクトタグの取得
	ObjectTag GetObjectTag() override { return ObjectTag::BIRD_ENEMY; }
	//ターゲットのセット
	void SetTarget(Actor* target) { m_target = target; }
	//ターゲットの取得
	Actor* GetTarget() { return m_target; }

public:
	//コンストラク
	BirdEnemy(Scene* scene, Player* player);
	//デストラクタ
	~BirdEnemy() override;

	//オブジェクト別の更新処理
	void UpdateActor(const float& deltaTime) override;

	//当たった時に呼び出される
	void OnCollisionEnter(ColliderComponent* collider) override;

	//当たり続けているときの呼び出される
	void OnCollisionStay(ColliderComponent* collider) override;

	//衝突が終了したときに呼び出される
	void OnCollisionExit(ColliderComponent* collider) override;

private:
	//ターゲットに対して回転
	void Rotate(const float& deltaTime);

private:
	//ステートマシン
	std::unique_ptr<BirdEnemyStateMachine> m_stateMachine;
	//ターゲット
	Actor* m_target;

	//弾配列
	std::vector<BirdEnemyBullet*> m_bullets;

};


